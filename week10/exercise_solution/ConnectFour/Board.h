#ifndef BOARD_H_
#define BOARD_H_

#include "ValueType.h"

#include <array>
#include <cstddef>

struct ColumnFullException{};

struct Row : ValueType<int, Row>, Numeric<Row>{};

struct Column : ValueType<int, Column>, Numeric<Column>{};

struct Index {
	Row row{};
	Column column{};

	bool operator==(Index const & other) const {
		return row == other.row && column == other.column;
	}
};

template <std::size_t Rows, std::size_t Columns>
struct Board {

	enum State {
		Free = 0,
		Red = 1,
		Yellow = 2
	};

	Row insert(Column column, State color) {
		auto freeRow = firstFreeRow(column);
		data[dataIndex(freeRow, column)] = color;
		return freeRow;
	}

	State at(Row row, Column column) const {
		return data[dataIndex(row, column)];
	}

private:
	std::size_t dataIndex(Row row, Column column) const {
		return row.value * Columns + column.value;
	}

	Row firstFreeRow(Column column) const {
		for (Row row{0}; row < Row{Rows}; row++) {
			if (at(row, column) == Free) {
				return row;
			}
		}
		throw ColumnFullException{};
	}

	std::array<State, Rows * Columns> data{};
};


#endif /* BOARD_H_ */