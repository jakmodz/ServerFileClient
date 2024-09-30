#include "Client.h"
#include "MultiLogger.h"
#include "../../FileServer/FileServer/PingAction.h"
using namespace boost::asio;
Client::Client(const std::string& host, const std::string& port, boost::asio::io_context& io_context): socket(io_context),
resolver(io_context),
host(host),
port(port)
{
}

std::vector<std::string> Client::GetFileNamesFromDir(std::string& Dir)
{
	return std::vector<std::string>();
}

void Client::DownloadFile(std::string& FileName)
{

}

void Client::Init()
{
    try
    {
        tcp::resolver::results_type endpoints = resolver.resolve(host, port);
        boost::asio::connect(socket, endpoints);
    }
    catch (const boost::system::system_error& e)
    {
        Logger << "Error in Client::Init: " << e.what() << "\n";
    }
    PingAction test;
    write(socket, buffer(&test, sizeof(PingRequest)));
}

std::vector<std::string> Client::ListAllFilesInDir(std::string& FileName)
{
	return std::vector<std::string>();
}
