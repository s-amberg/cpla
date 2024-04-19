#ifndef BOUNDEDBUFFER_HPP_
#define BOUNDEDBUFFER_HPP_

#include <ranges>
#include <array>
#include <compare>
#include <cstddef>
#include <memory>
#include <numeric>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <ranges>
#include <boost/operators.hpp>

// namespace buffy {

    template<typename T> 
    class BoundedBuffer {

        public:

        using container_type = std::unique_ptr<std::byte[]>;
        using value_type = T;
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
            
            std::ranges::for_each(item_range(), [this](size_type index) {
                value_type * element = &element_at(calculate_index(index));
                std::destroy_at(element);
            });
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


        template<typename V>
        class RABuffIterator : boost::random_access_iterator_helper<BoundedBuffer<V>, typename BoundedBuffer<V>::value_type>{

            using difference_type = ::ptrdiff_t;

            public:
            explicit RABuffIterator(BoundedBuffer<V> & buffer, difference_type index) : buffer{buffer}, index{index} {
                
            }

            auto operator++() -> RABuffIterator {
                throwOnFull(index+1);
                index++;
                return *this;
            }
            auto operator++(int) -> RABuffIterator {
                auto const old = *this;
                ++*this;
                return old;
            }

            auto operator--() -> RABuffIterator {
                throwOnEmpty(index-1);
                index--;
                return *this;
            }
            auto operator--(int) -> RABuffIterator {
                auto const old = *this;
                --*this;
                return old;
            }
            auto throwOnFull(difference_type diff) const -> void {
                if(diff > this->buffer.size()) throw std::logic_error{"full"};
            }
            
            auto throwOnEmpty(difference_type diff) const -> void {
                if(diff < 0) throw std::logic_error{"empty"};
            }
            auto operator==(RABuffIterator const& rhs) const -> bool {
                return this->buffer.front_index == rhs.buffer.front_index && this->buffer.size() == rhs.buffer.size() && this->index == rhs.index;
            };

            auto operator+=(difference_type diff) const -> RABuffIterator & {
                throwOnFull(index+diff);
                return *this;
            };

            auto operator*() const -> BoundedBuffer<T>::reference{ 
                throwOnFull(index+1);
                return buffer.element_at(buffer.front_index + index); 
            }

            auto operator+(const difference_type diff) const -> RABuffIterator { throwOnFull(index+diff); return RABuffIterator(index + diff); }

            auto operator-=(difference_type diff) -> RABuffIterator & {
                throwIfEmpty(index - diff); 
                index =  index - diff;
                return *this;
            };
            auto operator-(const difference_type diff) const -> RABuffIterator { throwOnEmpty(index-diff); return RABuffIterator(buffer, index - diff); }
            
            auto operator-(RABuffIterator other) -> difference_type { 
                if(std::addressof(other.buffer) != std::addressof(this->buffer)) throw std::logic_error{"wrong reference"};
                throwOnEmpty(index-other.index); 
                return index-other.index; 
            }
            auto operator<=>(RABuffIterator const & rhs) const -> std::strong_ordering{
                if(std::addressof(rhs.buffer) != std::addressof(this->buffer)) throw std::logic_error{"wrong reference"};
                return index <=> rhs.index;
            }
            constexpr auto operator[](std::size_t i) const -> reference { 
                throwOnFull(i + index);
                return buffer.element_at(i + index); 
            }
            auto operator->() -> T* { return &(this->buffer.element_at(buffer.front_index + index)); }


            private:
            BoundedBuffer<T> & buffer;
            difference_type index;
        };

        template<typename V>
        class ConstRABuffIterator : boost::random_access_iterator_helper<BoundedBuffer<V>, typename BoundedBuffer<T>::value_type>{

            using difference_type = ::ptrdiff_t;

            public:
            explicit ConstRABuffIterator(BoundedBuffer<V> const& buffer, difference_type index) : buffer{buffer}, index{index} {
            }

            auto operator++() -> ConstRABuffIterator const {
                throwOnFull(index + 1);
                index++;
                return *this;
            }
            auto operator++(int) -> ConstRABuffIterator const {
                auto const old = *this;
                ++*this;
                return old;
            }
            auto operator--() -> ConstRABuffIterator {
                throwOnEmpty(index-1);
                index--;
                return *this;
            }
            auto operator--(int) -> ConstRABuffIterator {
                auto const old = *this;
                --*this;
                return old;
            }

            auto throwOnFull(difference_type diff) const -> void {
                if(diff > this->buffer.size()) throw std::logic_error{"full"};
            }
            
            auto throwOnEmpty(difference_type diff) const -> void {
                if(diff < 0) throw std::logic_error{"empty"};
            }
            auto operator==(ConstRABuffIterator const& rhs) const -> bool {
                return this->buffer.front_index == rhs.buffer.front_index && this->buffer.size() == rhs.buffer.size() && this->index == rhs.index;
            };

            auto operator+=(difference_type diff) -> ConstRABuffIterator & {
                throwOnFull(index + diff); 
                index =  index + diff;
                return *this;
            };
            auto operator+(const difference_type diff) const -> ConstRABuffIterator { throwOnFull(index+diff); return ConstRABuffIterator(buffer, index + diff); }
            

            auto operator-=(difference_type diff) -> ConstRABuffIterator & {
                throwOnEmpty(index - diff); 
                index =  index - diff;
                return *this;
            };
            auto operator-(const difference_type diff) const -> ConstRABuffIterator { 
                throwOnEmpty(index-diff); 
                return ConstRABuffIterator(buffer, index - diff); 
            }
            auto operator*() const -> typename BoundedBuffer<T>::reference { 
                throwOnFull(index+1);
                return buffer.element_at(buffer.front_index + index); 
            }
            auto operator-(const ConstRABuffIterator & other) const -> difference_type { 
                if(std::addressof(other.buffer) != this->buffer) throw std::logic_error{"wrong reference"};
                throwOnEmpty(index-other.index); 
                return index-other.index; 
            }

            auto operator<=>(ConstRABuffIterator const & rhs) const -> std::strong_ordering{
                if(std::addressof(rhs.buffer) != this->buffer) throw std::logic_error{"wrong reference"};
                return index <=> rhs.index;
            }            
            
            constexpr auto operator[](std::size_t i) const -> reference { 
                throwOnFull(i + index);
                return buffer.element_at(i + index); 
            }

            auto operator->() -> T* { return &(this->buffer.element_at(buffer.front_index + index)); }

            private:
            BoundedBuffer<T> const& buffer;
            difference_type index;
        };

        using iterator = RABuffIterator<T>;
        using const_iterator = ConstRABuffIterator<T>;
                
        auto begin()  -> iterator {
            return iterator(*this, 0);
        }
        auto end()  -> iterator {
            return iterator(*this, this->size());
        }     
        auto begin() const -> const_iterator {
            return const_iterator(*this, 0);
        }
        auto end() const -> const_iterator {
            return const_iterator(*this, this->size());
        }   
        auto cbegin() const -> const_iterator {
            return const_iterator(*this, 0);
        } 
        auto cend() const -> const_iterator {
            return const_iterator(*this, this->size());
        }
            
    };


    template <typename... T>
    auto swap(BoundedBuffer<T...> & lhs, BoundedBuffer<T...> & rhs) noexcept -> void {
        return lhs.swap(rhs);
    }


#endif /* BOUNDEDBUFFER_HPP_ */
