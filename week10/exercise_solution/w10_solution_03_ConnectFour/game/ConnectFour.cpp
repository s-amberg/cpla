#include "ConnectFour.h"
#include "Board.h"

#include <cstddef>

#include <iterator>
#include <numeric>
#include <optional>
#include <vector>

template <typename T>
static std::vector<T> createIndexVector(std::size_t n) {
	std::vector<T> indices(n);
	std::iota(std::begin(indices), std::end(indices), T{});
	return indices;
}

Column ConnectFour::columns() const {
	return Column { Columns };
}

Row ConnectFour::rows() const {
	return Row { Rows };
}

std::optional<ConnectFour::Player> ConnectFour::drop(Column column) {
	modified = true;
	auto color = turn == Red ? BoardType::Red : BoardType::Yellow;
	auto row = board.insert(column, color);
	lastInsert = {row, column};
	if (auto winner = board.winner(row, column)) {
		return turn;
	}
	changePlayer();
	return std::nullopt;
}

std::vector<Column> ConnectFour::columnList() {
	return createIndexVector<Column>(Columns);
}

std::vector<Row> ConnectFour::rowList() {
	return createIndexVector<Row>(Rows);
}

ConnectFour::BoardType const & ConnectFour::getBoard() const {
	return board;
}

void ConnectFour::changePlayer() {
	if (turn == Player::Red) {
		turn = Player::Yellow;
	} else {
		turn = Player::Red;
	}
}
