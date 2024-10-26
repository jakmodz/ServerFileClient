#include "Client.h"
#include "MultiLogger.h"
#include <fstream>
#include "../../FileServer/FileServer/Macro.h"
#include "../../FileServer/FileServer/PingAction.h"
#include "../../FileServer/FileServer/ServerInfoAction.h"
#include "../../FileServer/FileServer/PwdAction.h"
#include "../../FileServer/FileServer/CdAction.h"
#include "../../FileServer/FileServer/ClientSideActionExecutor.h"
#include "../../FileServer/FileServer/FetchAction.h"
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

void Client::DownloadFile(const std::string& FileName)
{
    auto response = ClientSideActionExecutor<FetchAction>::Execute(socket, FetchRequest(FileName));
    std::ofstream File(FileName, std::ios::binary);
    File.write((char*)response->data.get(),response->size);
    File.close();
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
   
}

void Client::Ping()
{
    uint64_t start = NOW_MICROSECONDS();
    auto response = ClientSideActionExecutor<PingAction>::Execute(socket,PingRequest());
    double delta = response->header.creationMoment - start;
    double t = delta / 1000;
    Logger<< "time: " << std::to_string(t) << "\n";
}

void Client::ServerInfo()
{
    auto response = ClientSideActionExecutor<ServerInfoAction>::Execute(socket, ServerInfoRequest());
    Logger<<"wersja servera " << response->version << " computer name: " << response->machineName << "\n";
}

std::string Client::Pwd()
{
    auto response = ClientSideActionExecutor<PwdAction>::Execute(socket, PwdRequest());
    return response->path;
}

void Client::Cd(const std::string PathToAdd)
{
    auto response = ClientSideActionExecutor<CdAction>::Execute(socket, CdRequest(PathToAdd));
    Logger << "currert path: " << response->path<<"\n";
}

std::vector<PathInfo> Client::List(const std::string& Path)
{
    auto response = ClientSideActionExecutor<ListAction>::Execute(socket, ListRequest(Path));
    return response->paths;
}

