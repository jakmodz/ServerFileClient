#pragma once
#include <string>
#include <vector>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;
class Client
{
public:
public:
	Client(const std::string& host, const std::string& port, boost::asio::io_context& io_context);
	std::vector<std::string> GetFileNamesFromDir(std::string& Dir);
	void DownloadFile(std::string& FileName);
	void Init();
	void Ping();
	void ServerInfo();
	std::string Pwd();
	std::vector<std::string> ListAllFilesInDir(const std::string& FileName);
private:
	tcp::resolver resolver;
	tcp::socket socket;
	std::string port;
	std::string host;
	tcp::resolver::results_type endpoints;

};

