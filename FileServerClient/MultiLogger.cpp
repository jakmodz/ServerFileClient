#include "MultiLogger.h"
#include <fstream>
MultiLogger::MultiLogger(bool Console) : Console(Console), File("")
{

}

MultiLogger::MultiLogger(bool Console, std::string File):Console(Console), File(File)
{
}

MultiLogger& MultiLogger::operator<<(const std::string& text)
{
	if (Console)
	{
		std::cout << text;
	}
	if (File != "")
	{
		std::ofstream LogFile(File);
		LogFile << text << std::endl;
		LogFile.close();

	}
	return *this;
}
