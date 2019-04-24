#ifndef BOARD_H_
#define BOARD_H_

#include "ValueType.h"

#include <array>
#include <cstddef>
#include <functional>
#include <optional>

struct ColumnFullException {
};

struct Row: ValueType<int, Row>, Numeric<Row> {
};

struct Column: ValueType<int, Column>, Numeric<Column> {
};

struct Index {
	Row row { };
	Column column { };

	bool operator==(Index const & other) const {
		return row == other.row && column == other.column;
	}
};

template<std::size_t Rows, std::size_t Columns>
struct Board {

	enum State {
		Free = 0, Red = 1, Yellow = 2
	};

	Row insert(Column column, State color) {
		auto freeRow = firstFreeRow(column);
		data[dataIndex(freeRow, column)] = color;
		return freeRow;
	}

	State at(Row row, Column column) const {
		return data[dataIndex(row, column)];
	}

	std::optional<State> winner(Row row, Column column) const {
		auto rowWinner { check(row) };
		if (rowWinner) {
			return *rowWinner;
		}
		auto columnWinner { check(column) };
		if (columnWinner) {
			return *columnWinner;
		}
		return check(row, column);
	}
private:
	std::size_t dataIndex(Row row, Column column) const {
		return row.value * Columns + column.value;
	}

	struct WinState {
		int inSeries { };
		Board::State state { Free };
	};

	std::optional<State> check(Row row) const {
		return check( { row, Column { 0 } }, [](int &, int & c) {++c;});
	}

	std::optional<State> check(Column column) const {
		return check( { Row { 0 }, column }, [](int & r, int &) {++r;});
	}

	std::optional<State> check(Row row, Column column) const {
		if (auto lowerLeftToUpperRight = check(diagonalStart(row, column), [](int & r, int & c) {++r; ++c;})) {
			return lowerLeftToUpperRight;
		}
		return check(diagonalEnd(row, column), [](int & r, int & c) {++r; --c;});
	}

	std::optional<State> check(Index start, std::function<void(int&, int&)> counter) const {
		WinState winner { };
		auto [row, column] {start};
		for (int r { row.value }, c { column.value }; r < static_cast<Row::value_type>(Rows) && c < static_cast<Column::value_type>(Columns);
				counter(r, c)) {
			auto current { at(Row { r }, Column { c }) };
			if (winner.state != current) {
				winner.state = current;
				winner.inSeries = 1;
			} else {
				winner.inSeries++;
			}
			if (winner.state != Free && winner.inSeries == 4) {
				return winner.state;
			}
		}
		return std::nullopt;
	}

	Index diagonalStart(Row row, Column column) const {
		auto start = column.value - row.value;
		return (start < 0) ? Index { Row { -start }, Column { 0 } } : Index { Row { 0 }, Column { start } };
	}

	Index diagonalEnd(Row row, Column column) const {
		auto end = column.value + row.value;
		auto lastColumnIndex { static_cast<Column::value_type>(Columns) - 1 };
		return (end >= static_cast<Column::value_type>(Columns)) ?
				Index { Row { end - lastColumnIndex }, Column { lastColumnIndex } } :
				Index { Row { 0 }, Column { end } };
	}

	Row firstFreeRow(Column column) const {
		for (Row row { 0 }; row < Row { Rows }; row++) {
			if (at(row, column) == Free) {
				return row;
			}
		}
		throw ColumnFullException { };
	}

	std::array<State, Rows * Columns> data { };
};

#endif /* BOARD_H_ */
