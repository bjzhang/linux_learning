
#include <cstdlib>
#include <iostream>
#include <chrono>

int main(int argc, char *argv[])
{
	int deltaNo;
	std::chrono::steady_clock::time_point now;
	std::chrono::steady_clock::time_point deltaTime;

	if (argc < 2)
		exit(EXIT_FAILURE);

	deltaNo = atoi(argv[1]);

	now = std::chrono::steady_clock::now();
	deltaTime = now - std::chrono::nanoseconds(1000) * deltaNo;
	std::cout << now.time_since_epoch().count() << " - 1000(ns) x " << deltaNo << " = " << deltaTime.time_since_epoch().count() << std::endl;

}

