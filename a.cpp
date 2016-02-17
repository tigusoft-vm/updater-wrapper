#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <windows.h>
#include <winbase.h>

//  g++ -o a a.cpp

#ifdef __CYGWIN__
#include <sstream>
namespace std {
template <typename T>
std::string to_string(T val) {
    std::stringstream stream;
    stream << val;
    return stream.str();
}
} // namespace std
#endif


int main() {
	std::string PID = std::to_string(GetCurrentProcessId());
	std::cout << "a.exe: PID " << PID << std::endl;
	std::cout << "a.exe PID size "  << PID.size() << std::endl;
	std::unique_ptr<char[]> pid_arr(new char[PID.size() + 1]);
	PID.copy(pid_arr.get(), PID.size());
	pid_arr[PID.size()] = '\0';
	std::cout << "a.exe pid array " << pid_arr.get() << std::endl;
	/*std::cout << "a.exe: wait for char" << std::endl;
	char a;
	std::cin >> a;*/
	STARTUPINFO info={sizeof(info)};
	PROCESS_INFORMATION processInfo;
	CreateProcess("b.exe", pid_arr.get(), nullptr, nullptr, true, 0, nullptr, nullptr, &info, &processInfo);

	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "a.exe: end" << std::endl;
	return 0;
}