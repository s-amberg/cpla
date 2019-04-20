#ifndef CONNECTFOUR_H_
#define CONNECTFOUR_H_

#include "Board.h"

#include <cstddef>
#include <vector>

struct ConnectFour {
	static constexpr std::size_t Rows = 6;
	static constexpr std::size_t Columns = 7;

	enum Player {
		Red = 1,
		Yellow = 2
	};

	using BoardType = Board<Rows, Columns>;

	void drop(Column column);
	Row rows() const;
	Column columns() const;
	static std::vector<Row> rowList();
	static std::vector<Column> columnList();
	BoardType & getBoard();

private:
	void changePlayer();
	Player turn = Player::Red;
	BoardType board{};
};

#endif /* CONNECTFOUR_H_ */
