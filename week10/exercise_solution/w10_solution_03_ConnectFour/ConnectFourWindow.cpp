#include "ConnectFourWindow.h"

#include "game/Board.h"
#include "game/ConnectFour.h"

#include "SFML/Graphics.hpp"

#include <algorithm>
#include <optional>
#include <string>

void ConnectFourWindow::run() {
	while (window.isOpen()) {
		checkConnection();
		handleEvents();
		checkMailbox();
		drawBoard();
		drawStatus();
		drawWinner();
		window.display();
	}
	controller.disconnect();
}

void ConnectFourWindow::handleEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		} else if (event.type == sf::Event::Resized) {
			sf::Vector2f size { static_cast<float>(event.size.width), static_cast<float>(event.size.height) };
			sf::Vector2f pos { 0, 0 };
			window.setView(sf::View(sf::FloatRect(pos, size)));
		} else if (event.type == sf::Event::MouseButtonReleased) {
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				auto mousePosition = sf::Mouse::getPosition(window);
				auto column = findColumn(mousePosition.x);
				if (column < controller.columns()) {
					controller.drop(column);
				}
			}
		}
	}
}

void ConnectFourWindow::drawChip(float side, Row row, Column column, ConnectFour::BoardType board, std::optional<Index> latest) {
	auto radius = side / (2.f) * (1.f - 2 * circleMarginPercent);
	sf::CircleShape shape { radius };
	auto state = board.at(row, column);
	auto color = colors[state];
	Row invertedRow = controller.rows() - Row { 1 } - row;
	shape.setPosition((column.value + circleMarginPercent) * side, (invertedRow.value + circleMarginPercent) * side);
	shape.setFillColor(color);
	if (latest && *latest == Index { row, column }) {
		shape.setOutlineColor(latestBorderColor);
		shape.setOutlineThickness(latestBorderThickness);
	}
	window.draw(shape);
}

void ConnectFourWindow::drawWinner() {
	auto winner = controller.gameState().winner;
	if (!winner) {
		return;
	}
	auto size { window.getSize() };
	auto side { std::min(size.x, size.y) };
	auto border { side / 8 };
	auto rectSide { side - 2.f * border };
	auto ratio { 6.f / 7.f };
	sf::RectangleShape rectangle { sf::Vector2f { rectSide, ratio * rectSide } };
	rectangle.setPosition(1.3 * border, border);
	bool redWins = *winner == ConnectFour::Player::Red;
	if (redWins) {
		rectangle.setFillColor(c4::Color::RedTransparent);
	} else {
		rectangle.setFillColor(c4::Color::YellowTransparent);
	}
	rectangle.setOutlineColor(c4::Color::Black);
	rectangle.setOutlineThickness(1.f);
	window.draw(rectangle);
	if (font) {
		sf::Text text { };
		text.setFont(*font);
		text.setPosition(border + (ratio / 1.5) * border, side / 2 - 1.2 * border);
		text.setString(std::string { "    You" } + std::string { controller.gameState().peerState.player == *winner ? " win!" : " lose!" });
		text.setCharacterSize(border);
		text.setFillColor(c4::Color::White);
		text.setOutlineColor(c4::Color::Black);
		text.setOutlineThickness(1.f);
		text.setStyle(sf::Text::Bold);
		window.draw(text);
	}
}

void ConnectFourWindow::drawStatus() {
	auto gameState { controller.gameState() };
	auto size { window.getSize() };
	auto side { std::min(size.x, size.y) };
	auto border { side / 8 };
	if (font) {
		sf::Text text { };
		auto fontSize { border / 4 };
		text.setFont(*font);
		text.setPosition(0, size.y - 1.2 * fontSize);
		text.setString(gameState.toString());
		text.setCharacterSize(fontSize);
		text.setFillColor(c4::Color::White);
		text.setOutlineColor(c4::Color::Black);
		text.setOutlineThickness(1.f);
		window.draw(text);
	}

}

void ConnectFourWindow::drawBoard() {
	window.clear(c4::Color::ConnectFourBlue);
	auto size = window.getSize();
	auto width = size.x;
	auto height = size.y;
	auto side = squareLength(width, height);
	auto board = controller.board();
	auto latest = controller.latest();
	for (Row row : ConnectFour::rowList()) {
		for (Column column : ConnectFour::columnList()) {
			drawChip(side, row, column, board, latest);
		}
	}
}

void ConnectFourWindow::checkMailbox() {
	if (auto mail = mailbox.tryGet()) {
		controller.dropLocal(*mail);
	}
}

void ConnectFourWindow::checkConnection() {
	if (!controller.gameState().peerState.connected()) {
		controller.resetGame();
	}
}

Column ConnectFourWindow::findColumn(unsigned x) const {
	auto windowWidth = window.getSize().x;
	auto windowHeight = window.getSize().y;
	auto columnWidth = squareLength(windowWidth, windowHeight);
	return Column { static_cast<Column::value_type>(x / columnWidth) };
}

float ConnectFourWindow::squareLength(unsigned x, unsigned y) const {
	return std::min(x / controller.columns().value, y / controller.rows().value);
}
