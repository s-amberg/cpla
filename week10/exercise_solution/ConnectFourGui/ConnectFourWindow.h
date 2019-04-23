#ifndef CONNECTFOURWINDOW_H_
#define CONNECTFOURWINDOW_H_

#include "ConnectFourController.h"
#include "peer/Peers.h"

#include <SFML/Graphics.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <array>
#include <memory>

namespace c4::Color {
	static const sf::Color Black { sf::Color(0, 0, 0) };
	static const sf::Color White { sf::Color(255, 255, 255) };
	static const sf::Color Red { sf::Color(255, 0, 0) };
	static const sf::Color Green { sf::Color(0, 255, 0) };
	static const sf::Color Blue { sf::Color(0, 0, 255) };
	static const sf::Color Yellow { sf::Color(255, 255, 0) };
	static const sf::Color Cyan { sf::Color(0, 255, 255) };
}

struct ConnectFourWindow {
	ConnectFourWindow() : controller{std::make_unique<NullPeer>()} { //Single Player Game
	}

	explicit ConnectFourWindow(unsigned short port) : controller{std::make_unique<ServerPeer>(port)}  { //Server Game

	}

	ConnectFourWindow(sf::IpAddress serverAddress, unsigned short port) : controller{std::make_unique<ClientPeer>(serverAddress, port)}  { //Client Game

	}


	void run();
	void handleEvents();
	void drawBoard();

private:
	Column findColumn(unsigned x) const;
	float squareLength(unsigned x, unsigned y) const;
	void drawChip(float side, Row row, Column column);

	sf::RenderWindow window{sf::VideoMode{800, 600}, "Connect Four", sf::Style::Default, sf::ContextSettings{0, 0, antiAliasing}};
	ConnectFourController controller;
	inline static std::array<sf::Color, 3> const colors{ c4::Color::Green, c4::Color::Red, c4::Color::Yellow };
	inline static sf::Color const latestBorderColor { c4::Color::Cyan };
	constexpr static unsigned antiAliasing = 8;
	constexpr static float circleMarginPercent { 0.05f };
	constexpr static float latestBorderThickness { 5.f };
};

#endif /* CONNECTFOURWINDOW_H_ */
