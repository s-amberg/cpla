

#include <any>
#include <iostream>

void anyExample(std::ostream & out) {
	std::any value{};
	out << "has value? " << value.has_value() << '\n';
	value = 5;
	out << std::any_cast<int>(value) << '\n';
	try {
		std::any_cast<long>(value);
	} catch(std::bad_any_cast const &) {
		out << "std::bad_any_cast thrown, "
		       "when accessing int as long!\n";
	}
}



namespace protocol {

struct LedData {
	unsigned const red;
	unsigned const green;
	unsigned const blue;
};

std::ostream & operator << (std::ostream & out, LedData const & led) {
	out << "R: " << led.red << " G: " << led.green << " B: " << led.blue << '\n';
	return out;
}

enum class command {
	connect, disconnect, turnOnLed, turnOffLed
};

struct Message {
	command const cmd;
	std::any const data;
};

void turnOnLed(LedData const & ledData) {
	std::cout << "Turning on LED: " << ledData;
}

struct dispatcher {
	void handle_message(Message const & msg) const {
		auto const & cmd = msg.cmd;
		auto const & data = msg.data;
		switch(cmd) {
		case command::turnOnLed:
		{
			LedData const ledData = std::any_cast<LedData>(data);
			turnOnLed(ledData);
			break;
		}
		//...
		default:
			break;
		}
	}
};

}

int main() {
	anyExample(std::cout);

	std::cout << "----------\n";

	using namespace protocol;
	dispatcher const message_dispatcher{};
	Message const turnLedRed{command::turnOnLed, LedData{255, 0, 0}};
	message_dispatcher.handle_message(turnLedRed);
}
