#pragma once
#include <string>
#include <iostream>
namespace RBT {
	namespace Logger {
		static void Log(std::string message)
		{
			std::cout << message << std::endl;
		}
	}
}