#ifndef PEER_SERVERPEER_H_
#define PEER_SERVERPEER_H_


#include "Peer.h"

#include "../game/Board.h"
#include "../game/ConnectFour.h"
#include "../game/GameCommand.hpp"

#include "../state/PeerState.hpp"

#include "asio/error.hpp"
#include "asio/io_context.hpp"
#include "asio/ip/tcp.hpp"
#include "asio/read.hpp"
#include "asio/steady_timer.hpp"
#include "asio/write.hpp"

#include <chrono>
#include <functional>
#include <memory>
#include <optional>
#include <system_error>
#include <utility>

struct ServerPeer: Peer {
	ServerPeer(asio::io_context & context, unsigned short port, std::function<void(Column)> callback)
		: endpoint { asio::ip::tcp::v4(), port }
		, acceptor { context, endpoint }
		, restartTimer { context }
		, callback { callback }
		, state { "Server", ConnectFour::Player::Yellow }
	{

	}

	virtual void send(Column column) override {
		// 1. Wrap the `column` parameter in a new game command
		//    - Hint: Only send a command when our state allows it!
	}

	virtual void start() override {
		// 1. Make sure the acceptor is able to accept new connections
		//    - Hint: Remember that an acceptor needs to be bound to an endpoint.
		//    - Hint: Remember to start `listen`ing for connections

		// 2. Begin to accept new connections
	}

	virtual void stop() override {
		// 1. Stop accepting new connections

		// 2. Close any active connections
	}

	virtual PeerState const & peerState() const override {
		return state;
	}

private:
	asio::ip::tcp::endpoint endpoint;
	asio::ip::tcp::acceptor acceptor;
	asio::steady_timer restartTimer;

	std::function<void(Column)> const callback;
	PeerState state;

	std::optional<asio::ip::tcp::socket> socket { };
	GameCommand receivedCommand { };

	constexpr static std::chrono::seconds restartInterval { 1 };

	void stopAccepting() {
		// 1. Shut down the acceptor
		//    - Make sure to cancel any active connection attempts
	}

	void closeConnection() {
		// 1. If we have an active connection, shut it down and close it
		//    - Hint: Make sure the reset the optional `socket`!

		// 2. Update the state to reflect that we are not connected
		//    - Hint: Remember to prevent sending of new messages!
	}

	void doAccept() {
		// 1. Asynchronously accept a new connection

		// 2. If the operation succeeds, and we don't currently have another connection:
		//    - Hint: Only one connection is allowed at a time. Make sure we stop accepting new connections
		//    - Update the state to reflect that we are connected now
		//    - Begin reading commands from the socket

		// 3. Otherwise ignore the connection attempt
	}

	void doRead() {
		// 1. Asynchronously read a command from the remote peer

		// 2. Notify the UI about the received and decoded command

		// 3. Make sure to allow sending of commands on success. see `doSend`

		// 4. Clean up the state and the connection when the client disconnects
		//    - Hint: You will receive `asio::error::eof` when the connection is closed by the client.

		// 5. Shut down the server if any other error occurs
	}

	void restart() {
		// 1. Start accepting new connections
		//    - Hint: Wait `restartInterval` seconds before accepting a new connection
	}

	void doSend(std::shared_ptr<GameCommand> gc) {
		// 1. Asynchronously write the command to the socket
		//    - Hint: The `GameCommand` class provides a convenience function to create a `asio::buffer`

		// 2. Make sure to disallow sending of further commands on success
		//    - Hint: Only allow sending of new commands once we received a message from the client. see `doRead`

		// 3. Clean up the state and the connection when the client disconnects
		//    - Hint: You will receive `asio::error::eof` when the connection is closed by the client.

		// 4. Shut down the server if any other error occurs
	}
};

#endif /* PEER_SERVERPEER_H_ */
