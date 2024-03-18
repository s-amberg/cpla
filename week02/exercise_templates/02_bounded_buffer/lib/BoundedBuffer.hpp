#ifndef BOUNDEDBUFFER_HPP_
#define BOUNDEDBUFFER_HPP_

#include <array>
#include <memory>
#include <stdexcept>
#include <utility>

// namespace buffy {

    template<typename T, size_t N> 
    class BoundedBuffer : std::array<T, N>{
        using class_type = BoundedBuffer<T, N>;
        public:
        using container_type = std::array<T, N>;
        using value_type = typename container_type::value_type;
        using reference = typename container_type::reference;
        using const_reference = typename container_type::const_reference;
        using size_type = typename container_type::size_type;


        BoundedBuffer() = default;
        BoundedBuffer(const BoundedBuffer & other) : content{other.content}, index{other.index}, item_count{other.item_count} {

        };
        BoundedBuffer(BoundedBuffer && other)  {
            this->swap(other);
        };

        private:
        container_type content;
        size_type index = 0; //between 0 and max_size, always points to first element
        size_type item_count = 0; //between 0 and max_size

        auto calculate_index(size_type index) const -> size_type {
            return index % content.max_size();
        }
        auto last_index() const -> size_type {
            return calculate_index(index + item_count - 1);
        }
        auto write_index() const -> size_type {
            return calculate_index(index + item_count);
        }

        public:

        [[nodiscard]] auto empty() const -> bool {
            return size() == 0;
        };
        [[nodiscard]] auto full() const -> bool{
            return size() == content.max_size();
        };
        auto size() const -> size_type {
            return item_count;
        };

        auto front() -> reference {
            if(empty()) throw std::logic_error("buffer is empty");
            return content.at(index);
        };
        auto front() const -> const_reference {
            if(empty()) throw std::logic_error("buffer is empty");
            return content.at(index);
        };

        auto back() -> reference {
            if(empty()) throw std::logic_error("buffer is empty");
            return content.at(last_index());
        };
        auto back() const -> const_reference {
            if(empty()) throw std::logic_error("buffer is empty");
            return content.at(last_index());
        };

        auto push(const value_type& value) -> void {
            if(full()) throw std::logic_error("buffer is full");
            content.at(write_index()) = value;
            item_count++;
        };
        auto push(value_type&& value) -> void {
            if(full()) throw std::logic_error("buffer is full");
            std::swap(content.at(write_index()), value);
            item_count++;
        };

        auto pop() -> void {
            if(empty()) throw std::logic_error("buffer is empty");
            content.at(index) = value_type{};
            index = calculate_index(index + 1);
            item_count--;
        };
        auto swap(class_type & other) noexcept -> void {
            using std::swap;
            swap(content, other.content);
            swap(index, other.index);
            swap(item_count, other.item_count);
        };

        auto operator=(class_type const & other) -> class_type & {
            if(std::addressof(other) != this) {
                content = other.content;
                index = other.index;
                item_count = other.item_count;
            }
            return *this;
        }
        auto operator=(class_type && other) -> class_type & {
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
