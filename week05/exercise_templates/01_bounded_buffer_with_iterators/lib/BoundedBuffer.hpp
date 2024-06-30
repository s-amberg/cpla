#ifndef BOUNDEDBUFFER_HPP_
#define BOUNDEDBUFFER_HPP_

#include <compare>
#include <cstddef>
#include <iterator>
#include <memory>
#include <numeric>
#include <stdexcept>
#include <utility>
#include <vector>
#include <ranges>
#include <boost/operators.hpp>
#include <algorithm> 

// namespace buffy {

    template<typename T> 
    class BoundedBuffer {

        public:

        using container_type = std::unique_ptr<std::byte[]>;
        using value_type = T;
        using reference = value_type &;
        using const_reference = value_type const &;
        using size_type = size_t;


        BoundedBuffer() : BoundedBuffer{10} { };
        BoundedBuffer(size_type size) : max_size{size} {
            if(size <= 0) throw std::invalid_argument{"size must be greater 0"};
            allocate(size);
        };
        BoundedBuffer(const BoundedBuffer & other) : front_index{other.front_index}, item_count{other.item_count}, max_size(other.max_size) {
            allocate(max_size);

            if(!empty()){
                std::ranges::for_each(item_range(), [this, & other](auto index) {
                    auto calculated_index = calculate_index(index);
                    std::construct_at(&element_at(calculated_index), other.element_at(calculated_index));
                });
            }
        }
        BoundedBuffer(BoundedBuffer && other) noexcept {
            this->swap(other);
        }

        template <typename Iter>
        BoundedBuffer(Iter begin, Iter end) {
            max_size = std::distance(begin, end);

            allocate(max_size);

            std::for_each(begin, end, [this](auto element) {
                push(element);
            });
        };

        ~BoundedBuffer() noexcept {
            del();
        }

        private:

        container_type content;
        size_type front_index = 0; //between 0 and max_size, always points to first element
        size_type item_count = 0; //between 0 and max_size
        size_type max_size = 0; //between 0 and max_size

        [[nodiscard]] auto calculate_index(size_type index) const noexcept -> size_type {
            return index % max_size;
        }
        [[nodiscard]] auto back_index() const noexcept -> size_type {
            return calculate_index(front_index + item_count - 1);
        }
        [[nodiscard]] auto push_index() const noexcept -> size_type {
            return calculate_index(front_index + item_count);
        }

        template<typename THead, typename... TRest>
        auto push_many(THead && current_value, TRest && ...values) -> void {
            push(std::forward<THead>(current_value));

            if constexpr(sizeof...(values) == 0) return;
            push_many(std::forward<TRest>(values)...);
        }


        auto allocate(size_t size) -> void {
            content = std::make_unique<std::byte[]>(sizeof(value_type) * size);
        }
        auto item_range() {
            auto numbers = std::vector<int>(size());
            std::iota(numbers.begin(), numbers.end(), front_index);
            return numbers;
        }

        auto del() noexcept -> void {
            
            std::ranges::for_each(item_range(), [this](size_type index) {
                value_type * element = &element_at(calculate_index(index));
                std::destroy_at(element);
            });
        }

        auto element_at(size_type index) -> reference {
            return reinterpret_cast<value_type *>(content.get())[index];
        }

        auto element_at(size_type index) const -> const_reference {
            return reinterpret_cast<value_type *>(content.get())[index];
        }

        public:

        [[nodiscard]] auto empty() const noexcept -> bool {
            return size() == 0;
        }
        [[nodiscard]] auto full() const noexcept -> bool{
            return size() == max_size;
        }
        [[nodiscard]] auto size() const noexcept -> size_type {
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
        class RABuffIterator : boost::random_access_iterator_helper<RABuffIterator<V>, typename BoundedBuffer<V>::value_type>{

            public:
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::random_access_iterator_tag;
            using value_type = BoundedBuffer::value_type;
            using reference = BoundedBuffer::value_type &;
            using pointer = BoundedBuffer::value_type *;

            
            RABuffIterator(BoundedBuffer<V> & buffer, difference_type index) : buffer{buffer}, index{index} {
                
            }

            auto operator++() -> RABuffIterator {
                throwOnFull(index+1);
                index++;
                return *this;
            }

            auto operator--() -> RABuffIterator {
                throwOnEmpty(index-1);
                index--;
                return *this;
            }

            auto operator==(RABuffIterator const& rhs) const -> bool {
                return this->index == rhs.index && std::addressof(rhs.buffer) == std::addressof(this->buffer);
            };

            auto operator+=(difference_type diff) const -> RABuffIterator & {
                throwOnFull(index+diff);
                return *this;
            };

            auto operator*() const -> BoundedBuffer<T>::reference{ 
                throwOnFull(index+1);
                return buffer.element_at(buffer.calculate_index(buffer.front_index + index)); 
            }

            auto operator-=(difference_type diff) -> RABuffIterator & {
                throwIfEmpty(index - diff); 
                index =  index - diff;
                return *this;
            };
            
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
                return buffer.element_at(buffer.calculate_index(i + index)); 
            }
            auto operator->() -> T* { return &(this->buffer.element_at(buffer.calculate_index(buffer.front_index + index))); }


            private:
            BoundedBuffer<T> & buffer;
            difference_type index;

            auto throwOnFull(difference_type diff) const -> void {
                if(diff > this->buffer.size()) throw std::logic_error{"full"};
            }
            
            auto throwOnEmpty(difference_type diff) const -> void {
                if(diff < 0) throw std::logic_error{"empty"};
            }
        };

        template<typename V>
        class ConstRABuffIterator : boost::random_access_iterator_helper<ConstRABuffIterator<V>, typename BoundedBuffer<T>::value_type>{

            public:
            using difference_type = ::ptrdiff_t;
            using iterator_category = std::random_access_iterator_tag;
            using value_type = BoundedBuffer::value_type const;
            using reference = BoundedBuffer::value_type const &;
            using pointer = BoundedBuffer::value_type *;
            
            
            explicit ConstRABuffIterator(BoundedBuffer<V> const& buffer, difference_type index) : buffer{buffer}, index{index} {
            }

            auto operator++() -> ConstRABuffIterator const {
                throwOnFull(index + 1);
                index++;
                return *this;
            }
            auto operator--() -> ConstRABuffIterator {
                throwOnEmpty(index-1);
                index--;
                return *this;
            }
            auto throwOnFull(difference_type diff) const -> void {
                if(diff > this->buffer.size()) throw std::logic_error{"full"};
            }
            
            auto throwOnEmpty(difference_type diff) const -> void {
                if(diff < 0) throw std::logic_error{"empty"};
            }
            auto operator==(ConstRABuffIterator const& rhs) const -> bool {
                return this->index == rhs.index && std::addressof(rhs.buffer) == std::addressof(this->buffer);
            };

            auto operator+=(difference_type diff) -> ConstRABuffIterator & {
                throwOnFull(index + diff); 
                index =  index + diff;
                return *this;
            };            

            auto operator-=(difference_type diff) -> ConstRABuffIterator & {
                throwOnEmpty(index - diff); 
                index =  index - diff;
                return *this;
            };
            auto operator*() const -> typename BoundedBuffer<T>::const_reference { 
                throwOnFull(index+1);
                return buffer.element_at(buffer.calculate_index(buffer.front_index + index)); 
            };
            auto operator-(const ConstRABuffIterator & other) const -> difference_type { 
                if(std::addressof(other.buffer) != this->buffer) throw std::logic_error{"wrong reference"};
                throwOnEmpty(index-other.index); 
                return index-other.index; 
            }

            auto operator<=>(ConstRABuffIterator const & rhs) const -> std::strong_ordering{
                if(std::addressof(rhs.buffer) != this->buffer) throw std::logic_error{"wrong reference"};
                return index <=> rhs.index;
            }            

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

    template <typename Iter>
    BoundedBuffer(Iter begin, Iter end) -> BoundedBuffer<typename std::iterator_traits<Iter>::value_type>;


#endif /* BOUNDEDBUFFER_HPP_ */
