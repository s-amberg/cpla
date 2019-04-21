#ifndef CONNECTFOURWINDOW_H_
#define CONNECTFOURWINDOW_H_

#include "ConnectFour.h"

#include <SFML/Graphics.hpp>
#include <array>


struct ConnectFourWindow {
	void run();
	void handleEvents();
	void drawBoard();

private:
	Column findColumn(unsigned x) const;
	float squareLength(unsigned x, unsigned y) const;
	void drawChip(float side, Row row, Column column);

	sf::RenderWindow window{sf::VideoMode{800, 600}, "Connect Four", sf::Style::Default, sf::ContextSettings{0, 0, antiAliasing}};
	ConnectFour game{};
	inline static std::array<sf::Color, 3> const colors{sf::Color::Black, sf::Color::Red, sf::Color::Yellow};
	inline static sf::Color const latestBorderColor { sf::Color::Cyan };
	constexpr static unsigned antiAliasing = 8;
	constexpr static float circleMarginPercent { 0.05f };
	constexpr static float latestBorderThickness { 5.f };
};

#endif /* CONNECTFOURWINDOW_H_ */
