#include "ConnectFour.h"

#include <cstddef>

#include <iterator>
#include <numeric>
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

void ConnectFour::drop(Column column) {
	try {
		auto color = turn == Red ? BoardType::Red : BoardType::Yellow;
		auto row = board.insert(column, color);
		lastInsert = {row, column};
		changePlayer();
	} catch (ColumnFullException const &) {
		//ignore
	}
}

std::vector<Column> ConnectFour::columnList() {
	return createIndexVector<Column>(Columns);
}

std::vector<Row> ConnectFour::rowList() {
	return createIndexVector<Row>(Rows);
}

ConnectFour::BoardType& ConnectFour::getBoard() {
	return board;
}

void ConnectFour::changePlayer() {
	if (turn == Player::Red) {
		turn = Player::Yellow;
	} else {
		turn = Player::Red;
	}
}
