#include "CLI.h"
#include <iostream>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include "Utility.h"
#include "MultiLogger.h"
using namespace boost::program_options;



CLI::CLI(int port, const std::string& host, boost::asio::io_context& io_context) : port(port), 
host(host),
io_context(io_context),
client(host, std::to_string(port), io_context)
{
    
}

int CLI::GetPort()
{
    return port;
}

std::string CLI::GetHost()
{
    return host;
}

void CLI::Start()
{
    Connect();
}

void CLI::Connect()
{
    
    client.Init();
    Update();
    Logger << "connected"<<"\n";
}



bool CLI::TryParse(int argc, char** argv)
{
    int port;
    std::string host;
    std::string path;
    try
    {
        options_description desc("Allowed options: ");
        desc.add_options()
            ("help,h", "prints help page ")
            ("port,p", value<int>(&port)->default_value(port), "port")
            ("address,a", value<std::string>(&host)->default_value(host), "host")
            
            ;
        variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
        return false;
    }
    return true;
}

void CLI::Update()
{
    while (true)
    {
        std::string command;
        std::getline(std::cin, command);
        std::vector<std::string> words = GetWordsFromString(command);

        switch (CLI::ParseString(words[0]))
        {
        case CommandType::Cd:
        {
            Cd(words[1]);
        }
        break;
        case CommandType::Download:
        {
            Download(words);
            Logger << "file(s) downloaded" << "\n";
        }
        break;
        case CommandType::Ping:
        {
            client.Ping();
        }
        break;
        case CommandType::List:
        {
            auto names = client.ListAllFilesInDir(client.Pwd());
            List(names);
        }
        break;
        case CommandType::Unknow:
        {
           Logger << "there is no this kind of command"<<"\n";
        }
        break;
        
        case CommandType::ServerInfo:
        {
            client.ServerInfo();
        }
        break;
        case CommandType::Pwd:
        {
            Logger<<client.Pwd()<<"\n";
        }
        break;
    }
    }
}

CommandType CLI::ParseString(std::string& command)
{
    boost::algorithm::to_lower(command);
        if (command == "cd") return CommandType::Cd;
        if (command == "download") return CommandType::Download;
        if (command == "list") return CommandType::List;
        if (command == "ping") return CommandType::Ping;
        if (command == "serverinfo") return CommandType::ServerInfo;
        if (command == "pwd") return CommandType::Pwd;

    return Unknow;
}


void CLI::Download(std::vector<std::string>& files)
{
    //TODO: pobieranie
    for (int i = 1; i < files.size(); i++)
    {
        client.DownloadFile(files[i]);
    }
}

void CLI::Cd(const std::string& PathToAdd)
{
    //TODO:dodac sprawdzanie czy istnieje dany katalog 
    
    
}

void CLI::List(std::vector<std::string>& names)
{
    for (int  i = 0; i < names.size(); i++)
    {
        Logger << names[i]<<"\n";
    }
}


