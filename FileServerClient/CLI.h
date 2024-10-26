#pragma once
#include <string>
#include <boost/filesystem.hpp>
#include "Client.h"
enum CommandType
{
	Fetch,
	Cd,
	List,
	Ping,
	Unknow,
	ServerInfo,
	Pwd
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
	void Download(const std::string& file);
	void Cd(const std::string& PathToAdd);
	void List(const std::vector<PathInfo>& paths);

	std::string host;
	int port;
	Client client;
	boost::asio::io_context& io_context;
};

