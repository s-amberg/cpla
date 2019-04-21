#include "ConnectFourWindow.h"

#include <algorithm>

void ConnectFourWindow::run() {
	while (window.isOpen()) {
		handleEvents();
		drawBoard();
		window.display();
	}
}

void ConnectFourWindow::handleEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		} else if (event.type == sf::Event::Resized) {
			window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
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

void ConnectFourWindow::drawChip(float side, Row row, Column column) {
	auto radius = side / (2.f) * (1.f - 2 * circleMarginPercent);
	sf::CircleShape shape { radius };
	auto state = controller.at(row, column);
	auto color = colors[state];
	Row invertedRow = controller.rows() - Row { 1 } - row;
	shape.setFillColor(color);
	shape.setPosition((column.value + circleMarginPercent) * side, (invertedRow.value + circleMarginPercent) * side);
	auto latest = controller.latest();
	if (latest && *latest == Index{row, column}) {
		shape.setOutlineColor(latestBorderColor);
		shape.setOutlineThickness(latestBorderThickness);
	}
	window.draw(shape);
}

void ConnectFourWindow::drawBoard() {
	window.clear(sf::Color::Blue);
	auto size = window.getSize();
	auto width = size.x;
	auto height = size.y;
	auto side = squareLength(width, height);
	for (Row row : ConnectFour::rowList()) {
		for (Column column : ConnectFour::columnList()) {
			drawChip(side, row, column);
		}
	}
}

Column ConnectFourWindow::findColumn(unsigned x) const {
	auto windowWidth = window.getSize().x;
	auto windowHeight = window.getSize().y;
	auto columnWidth = squareLength(windowWidth, windowHeight);
	return Column{static_cast<int>(x / columnWidth)};
}

float ConnectFourWindow::squareLength(unsigned x, unsigned y) const {
	return std::min(x / controller.columns().value, y / controller.rows().value);
}
