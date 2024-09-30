#pragma once
#include <iostream>
#include <string>
class MultiLogger
{
public:
	MultiLogger(bool Console);
	MultiLogger(bool Console,std::string File);
	MultiLogger& operator<<(const std::string& text);
private:
	bool Console;
	std::string File;
};
static MultiLogger Logger(true);
