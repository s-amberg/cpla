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

	sf::RenderWindow window{sf::VideoMode{800, 600}, "Connect Four", sf::Style::Default, sf::ContextSettings{0, 0, antiAliasing}};
	ConnectFour game{};
	inline static const std::array<sf::Color, 3> colors{sf::Color::Black, sf::Color::Red, sf::Color::Yellow};
	constexpr static unsigned antiAliasing = 8;
};

#endif /* CONNECTFOURWINDOW_H_ */
