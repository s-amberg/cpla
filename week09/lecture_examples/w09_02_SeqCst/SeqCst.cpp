#include <atomic>
#include <thread>
#include <iostream>

std::atomic<bool> x, y;
std::atomic<int> z;

void write_x() {
	x.store(true);
}

void write_y() {
	y.store(true);
}

void read_x_then_y() {
	while (!x.load());
	if (y.load()) ++z;
}

void read_y_then_x() {
	while (!y.load());
	if (x.load()) ++z;
}

int main() {
	x = false;
	y = false;
	z = 0;
	auto a = std::thread(write_x);
	auto c = std::thread(read_x_then_y);
	auto b = std::thread(write_y);
	auto d = std::thread(read_y_then_x);
	a.join();
	b.join();
	c.join();
	d.join();
	std::cout << "z == " << z << '\n';
}
