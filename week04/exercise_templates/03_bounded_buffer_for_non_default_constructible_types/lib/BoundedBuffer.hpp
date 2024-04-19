#ifndef BOUNDEDBUFFER_HPP_
#define BOUNDEDBUFFER_HPP_

#include <array>
#include <cstddef>
#include <iterator>
#include <memory>
#include <numeric>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <ranges>

// namespace buffy {

    template<typename T> 
    class BoundedBuffer {

        public:
        using value_type = T;
        using container_type = std::unique_ptr<std::byte[]>;
        using reference = value_type &;
        using const_reference = value_type const &;
        using size_type = size_t;

        BoundedBuffer() : BoundedBuffer(10) { };
        BoundedBuffer(size_type size) : max_size{size} {
            if(size <= 0) throw std::invalid_argument("size must be greater 0");
            allocate(size);
        };
        BoundedBuffer(const BoundedBuffer & other) : max_size(other.max_size), front_index{other.front_index}, item_count{other.item_count} {
            allocate(max_size);

            if(!empty()){
                std::ranges::for_each(item_range(), [this, & other](auto index) {
                    auto calculated_index = calculate_index(index);
                    std::construct_at(&element_at(calculated_index), other.element_at(calculated_index));
                });
            }
        }
        BoundedBuffer(BoundedBuffer && other) {
            this->swap(other);
        }

        ~BoundedBuffer(){
            del();
        }

        private:

        container_type content;
        size_type front_index = 0; //between 0 and max_size, always points to first element
        size_type item_count = 0; //between 0 and max_size
        size_type max_size = 0; //between 0 and max_size

        [[nodiscard]] auto calculate_index(size_type index) const -> size_type {
            return index % max_size;
        }
        [[nodiscard]] auto back_index() const -> size_type {
            return calculate_index(front_index + item_count - 1);
        }
        [[nodiscard]] auto push_index() const -> size_type {
            return calculate_index(front_index + item_count);
        }

        auto push_many() -> void {
            return;
        }
        template<typename THead, typename... TRest>
        auto push_many(THead && current_value, TRest && ...values) -> void {
            push(std::forward<THead>(current_value));
            push_many(std::forward<TRest>(values)...);
        }


        auto allocate(size_t size) -> void {
            content = std::make_unique<std::byte[]>(sizeof(value_type[size]));
        }
        auto item_range() {
            auto numbers = std::vector<int>(size());
            std::iota(numbers.begin(), numbers.end(), front_index);
            return numbers;
        }

        auto del() -> void {
            
            if(!empty()){ //prevents iota from going to max int length for some reason
                std::ranges::for_each(item_range(), [this](size_type index) {
                    value_type * element = &element_at(calculate_index(index));
                    std::destroy_at(element);
                });
            }
        }

        auto element_at(size_type index) const -> value_type & {
            return reinterpret_cast<value_type *>(content.get())[index];
        }

        public:

        [[nodiscard]] auto empty() const -> bool {
            return size() == 0;
        }
        [[nodiscard]] auto full() const -> bool{
            return size() == max_size;
        }
        [[nodiscard]] auto size() const -> size_type {
            return item_count;
        }

        auto front() -> reference {
            throwIfEmpty();
            return element_at(front_index);
        }
        auto front() const -> const_reference {
            throwIfEmpty();
            return element_at(front_index);
        }

        auto back() -> reference {
            throwIfEmpty();
            return element_at(back_index());
        }
        auto back() const -> const_reference {
            throwIfEmpty();
            return element_at(back_index());
        }

        auto push(const value_type& value) -> void {
            throwIfFull();
            std::construct_at(&element_at(push_index()), value);
            item_count++;
        }
        auto push(value_type&& value) -> void {
            throwIfFull();
            std::construct_at(&element_at(push_index()), std::forward<value_type>(value));
            item_count++;
        }

        auto pop() -> void {
            throwIfEmpty();
            std::destroy_at(&element_at(front_index));
            front_index = calculate_index(front_index + 1);
            item_count--;
        }

        auto swap(BoundedBuffer & other) noexcept -> void {
            using std::swap;
            swap(content, other.content);
            swap(max_size, other.max_size);
            swap(front_index, other.front_index);
            swap(item_count, other.item_count);
        }

        auto throwIfEmpty() const {
            if(empty()) throw std::logic_error{"buffer is empty"};
        }
        auto throwIfFull() const {
            if(full()) throw std::logic_error{"buffer is full"};
        }

        auto operator=(BoundedBuffer const & other) -> BoundedBuffer & {
            if(std::addressof(other) != this) {
                auto clone = BoundedBuffer{other};
                swap(clone);
            }
            return *this;
        }
        auto operator=(BoundedBuffer && other) -> BoundedBuffer & {
            if(std::addressof(other) != this) {
                swap(other);
            }
            return *this;
        }

        template<typename... TValue>
        static auto make_buffer(TValue &&... values) -> BoundedBuffer {
            auto buffy = BoundedBuffer{sizeof...(values)};
            buffy.push_many(std::forward<TValue>(values)...);
            return buffy;
        }
    }   ;

    template <typename... T>
    auto swap(BoundedBuffer<T...> & lhs, BoundedBuffer<T...> & rhs) noexcept -> void {
        return lhs.swap(rhs);
    }

// }


#endif /* BOUNDEDBUFFER_HPP_ */
