#include <boost/filesystem.hpp>
#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>
#include <windows.h>
#include <winbase.h>

//g++ -o b b.cpp -lboost_system -lboost_filesystem -std=c++11

BOOL is_process_running(DWORD pid) {
    HANDLE process = OpenProcess(SYNCHRONIZE, FALSE, pid);
    DWORD ret = WaitForSingleObject(process, 0);
    CloseHandle(process);
    return ret == WAIT_TIMEOUT;
}

int main(int argc, char* argv[]) {
	std::cout << "b.exe argumentrs" << std::endl;
	for (int i = 0; i < argc; ++i) {
		std::cout << "i = " << i << " "<< argv[i] << std::endl;
	}
	
	DWORD PID;
	std::stringstream ss;
	ss << argv[0];
	ss >> PID;
	
	std::cout << "b.exe: wait for PID " << PID << std::endl;
	
	while (is_process_running(PID)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	
	std::cout << "b.exe: end of wait" << std::endl;
	
	boost::filesystem::rename("c.exe", "a.exe");
	STARTUPINFO info={sizeof(info)};
	PROCESS_INFORMATION processInfo;
	CreateProcess("a.exe", nullptr, nullptr, nullptr, true, 0, nullptr, nullptr, &info, &processInfo);
	
	std::cout << "b.exe: end" << std::endl;
}