#ifndef GAMECOMMAND_HPP_
#define GAMECOMMAND_HPP_

#include "Board.h"

#include "asio/buffer.hpp"

#include <array>
#include <charconv>
#include <cmath>
#include <limits>
#include <iterator>

struct GameCommand {
	constexpr static int dataSize { static_cast<int>(std::log10(std::numeric_limits<Column::value_type>::max())) + 2 };

	using dataType = std::array<char, dataSize>;

	GameCommand() = default;

	explicit GameCommand(Column column) :
			data { } {
		std::to_chars(std::begin(data), std::end(data), column.value);
	}

	Column decode() const {
		int value { };
		std::from_chars(std::begin(data), std::end(data), value);
		return Column { value };
	}

	auto asBuffer() {
		return asio::buffer(data.begin(), dataSize);
	}
private:
	dataType data { };
};

#endif /* GAMECOMMAND_HPP_ */
