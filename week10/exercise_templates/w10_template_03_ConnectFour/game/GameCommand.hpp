#ifndef GAMECOMMAND_HPP_
#define GAMECOMMAND_HPP_

#include "Board.h"

#include "asio/buffer.hpp"

#include <array>
#include <charconv>
#include <limits>
#include <iterator>

struct GameCommand {
	using value_type = uint64_t;
	static_assert(std::numeric_limits<value_type>::max() >= std::numeric_limits<Column::value_type>::max());
	constexpr static auto dataSize { std::numeric_limits<value_type>::digits10 };

	using dataType = std::array<char, dataSize>;

	GameCommand() = default;

	explicit GameCommand(Column column) :
			data { } {
		std::to_chars(std::begin(data), std::end(data), column.value);
	}

	Column decode() const {
		value_type value{};
		std::from_chars(std::begin(data), std::end(data), value);
		return {static_cast<Column::value_type>(value)};
	}

	auto asBuffer() {
		return asio::buffer(data.begin(), dataSize);
	}
private:
	dataType data { };
};

#endif /* GAMECOMMAND_HPP_ */
