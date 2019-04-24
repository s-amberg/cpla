#ifndef CONNECTFOUR_H_
#define CONNECTFOUR_H_

#include "Board.h"

#include <cstddef>
#include <optional>
#include <vector>

struct ConnectFour {
	static constexpr std::size_t Rows = 6;
	static constexpr std::size_t Columns = 7;

	enum Player {
		Red = 1, //
		Yellow = 2 //
	};

	using BoardType = Board<Rows, Columns>;

	std::optional<Player> drop(Column column);
	std::optional<Index> latest() const {
		return lastInsert;
	}
	bool hasStarted() const { return modified; }

	Row rows() const;
	Column columns() const;
	BoardType const & getBoard() const;

	static std::vector<Row> rowList();
	static std::vector<Column> columnList();

private:
	void changePlayer();
	Player turn = Player::Red;
	BoardType board { };
	std::optional<Index> lastInsert { };
	bool modified { true };
};

#endif /* CONNECTFOUR_H_ */
