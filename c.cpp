#include <chrono>
#include <iostream>
#include <thread>

int main() {
	std::cout << "c.exe start" << std::endl;
	while (true) {
		std::cout << "c.exe" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}