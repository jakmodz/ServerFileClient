#pragma once
#include <string>
#include <boost/filesystem.hpp>
#include "Client.h"
enum CommandType
{
	Download,
	Cd,
	List,
	Ping,
	Unknow,
};
class CLI
{
public:
	CLI(int port, const std::string& host, boost::asio::io_context& io_context);

	int GetPort();
	std::string GetHost();
	bool TryParse(int argc, char** argv);


	void Update();
	void Start();
	void Connect();


	static CommandType ParseString(std::string&);
private:
	void Download(std::vector<std::string>& files);
	void Cd(std::string& PathToAdd);
	void List(std::vector<std::string>& names);

	std::string host;
	int port;
	boost::filesystem::path path;
	Client client;
	boost::asio::io_context& io_context;
};

