#include "pch.h";
#include <iostream>;
#include <Windows.h>;

void logger(const char* message) {
	std::cout << message << std::endl;
}

void logger(const int message) {
	std::cout << message << std::endl;
}

void logger(const double message) {
	std::cout << message << std::endl;
}

void logger(const DWORD message) {
	std::cout << message << std::endl;
}
