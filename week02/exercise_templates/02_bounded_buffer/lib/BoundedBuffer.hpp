#ifndef BOUNDEDBUFFER_HPP_
#define BOUNDEDBUFFER_HPP_

#include <array>
#include <memory>
#include <stdexcept>
#include <utility>

// namespace buffy {

    template<typename T, size_t N> 
    class BoundedBuffer {

        public:

        using container_type = std::array<T, N>;
        using value_type = typename container_type::value_type;
        using reference = typename container_type::reference;
        using const_reference = typename container_type::const_reference;
        using size_type = typename container_type::size_type;


        BoundedBuffer() = default;
        BoundedBuffer(const BoundedBuffer & other) : content{other.content}, front_index{other.front_index}, item_count{other.item_count} {

        };
        BoundedBuffer(BoundedBuffer && other)  {
            this->swap(other);
        };


        private:

        container_type content;
        size_type front_index = 0; //between 0 and max_size, always points to first element
        size_type item_count = 0; //between 0 and max_size

        auto calculate_index(size_type index) const -> size_type {
            return index % content.max_size();
        }
        auto back_index() const -> size_type {
            return calculate_index(front_index + item_count - 1);
        }
        auto push_index() const -> size_type {
            return calculate_index(front_index + item_count);
        }


        public:

        [[nodiscard]] auto empty() const -> bool {
            return size() == 0;
        }
        [[nodiscard]] auto full() const -> bool{
            return size() == content.max_size();
        }
        auto size() const -> size_type {
            return item_count;
        }

        auto front() -> reference {
            throwIfEmpty();
            return content.at(front_index);
        }
        auto front() const -> const_reference {
            throwIfEmpty();
            return content.at(front_index);
        }

        auto back() -> reference {
            throwIfEmpty();
            return content.at(back_index());
        }
        auto back() const -> const_reference {
            throwIfEmpty();
            return content.at(back_index());
        }

        auto push(const value_type& value) -> void {
            throwIfFull();
            content.at(push_index()) = value;
            item_count++;
        }
        auto push(value_type&& value) -> void {
            throwIfFull();
            std::swap(content.at(push_index()), value);
            item_count++;
        }

        auto pop() -> void {
            throwIfEmpty();
            content.at(front_index) = value_type{};
            front_index = calculate_index(front_index + 1);
            item_count--;
        }
        auto swap(BoundedBuffer & other) noexcept -> void {
            using std::swap;
            swap(content, other.content);
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
                content = other.content;
                front_index = other.front_index;
                item_count = other.item_count;
            }
            return *this;
        }
        auto operator=(BoundedBuffer && other) -> BoundedBuffer & {
            if(std::addressof(other) != this) {
                swap(other);
            }
            return *this;
        }

    };

    template <typename... T>
    auto swap(BoundedBuffer<T...> & lhs, BoundedBuffer<T...> & rhs) noexcept -> void {
        return lhs.swap(rhs);
    }

// }


#endif /* BOUNDEDBUFFER_HPP_ */
