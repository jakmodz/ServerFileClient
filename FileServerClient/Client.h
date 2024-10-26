#pragma once
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "../../FileServer/FileServer/ListAction.h"
using boost::asio::ip::tcp;
class Client
{
public:
public:
	Client(const std::string& host, const std::string& port, boost::asio::io_context& io_context);
	std::vector<std::string> GetFileNamesFromDir(std::string& Dir);
	void DownloadFile(const  std::string& FileName);
	void Init();
	void Ping();
	void ServerInfo();
	std::string Pwd();
	void Cd(const std::string PathToAdd);
	std::vector<PathInfo> List(const std::string& Path);
private:
	tcp::resolver resolver;
	tcp::socket socket;
	std::string port;
	std::string host;
	tcp::resolver::results_type endpoints;

};

