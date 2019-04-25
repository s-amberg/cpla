#ifndef CONNECTFOURWINDOW_H_
#define CONNECTFOURWINDOW_H_

#include "game/Board.h"
#include "ConnectFourController.h"
#include "peer/Peers.h"
#include "Mailbox.h"

#include "asio/io_context.hpp"
#include "asio/ip/tcp.hpp"

#include "SFML/Graphics.hpp"

#include <array>
#include <memory>
#include <optional>

namespace c4::Color {
	static const sf::Color Black {sf::Color(0, 0, 0)};
	static const sf::Color White {sf::Color(255, 255, 255)};
	static const sf::Color Red {sf::Color(255, 0, 0)};
	static const sf::Color RedTransparent {sf::Color(255, 0, 0, 150)};
	static const sf::Color Green {sf::Color(0, 255, 0)};
	static const sf::Color ConnectFourBlue {sf::Color(3, 143, 222)};
	static const sf::Color Yellow {sf::Color(255, 255, 0)};
	static const sf::Color YellowTransparent {sf::Color(255, 255, 0, 150)};
	static const sf::Color Cyan {sf::Color(0, 255, 255)};
	static const sf::Color DarkerBlue {sf::Color(0,89,227)};
}

struct ConnectFourWindow {
	ConnectFourWindow() :
			controller { std::make_unique<NullPeer>() } {
	}

	ConnectFourWindow(asio::io_context & context, unsigned short port) :
			controller { std::make_unique<ServerPeer>(context, port, [this] (Column column) {mailbox.put(column);}) } {
	}
	ConnectFourWindow(asio::io_context & context, asio::ip::tcp::resolver::results_type const & endpoints) :
			controller { std::make_unique<ClientPeer>(context, endpoints, [this] (Column column) {mailbox.put(column);}) } {
	}
	void run();
	void handleEvents();
	void drawWinner();
	void drawBoard();
	void drawStatus();
	void checkMailbox();
	void checkConnection();

private:
	Column findColumn(unsigned x) const;
	float squareLength(unsigned x, unsigned y) const;
	void drawChip(float side, Row row, Column column, ConnectFour::BoardType board, std::optional<Index> latest);

	ConnectFourController controller;
	Mailbox<Column> mailbox;
	std::optional<sf::Font> const font { []() -> std::optional<sf::Font> {
		sf::Font font {};
		if (!font.loadFromFile("fonts/Calibri.ttf")) {
			return std::nullopt;
		}
		return font;
	}() };
	sf::RenderWindow window { sf::VideoMode { 800, 710 }, "Connect Four (" + controller.gameState().peerState.name + ")", sf::Style::Default,
			sf::ContextSettings { 0, 0, antiAliasing } };
	inline static std::array<sf::Color, 3> const colors { c4::Color::White, c4::Color::Red, c4::Color::Yellow };
	inline static sf::Color const latestBorderColor { c4::Color::DarkerBlue };
	constexpr static unsigned antiAliasing = 8;
	constexpr static float circleMarginPercent { 0.05f };
	constexpr static float latestBorderThickness { 5.f };
};

#endif /* CONNECTFOURWINDOW_H_ */
