#include "CLI.h"
#include <iostream>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include "Utility.h"
#include "MultiLogger.h"
#include <stdio.h>
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
    Logger << "connected" << "\n";
    Update();
    
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
        case CommandType::Fetch:
        {
            Download(words[1]);
            Logger << "file downloaded" << "\n";
        }
        break;
        case CommandType::Ping:
        {
            client.Ping();
        }
        break;
        case CommandType::List:
        {
            if (words[1].size() <= 0 )
            {
                return;
            }
           List(client.List(words[1]));

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
        if (command == "fetch") return CommandType::Fetch;
        if (command == "list") return CommandType::List;
        if (command == "ping") return CommandType::Ping;
        if (command == "serverinfo") return CommandType::ServerInfo;
        if (command == "pwd") return CommandType::Pwd;

    return Unknow;
}


    void CLI::Download(const std::string & file)
    {
        client.DownloadFile(file);
    }
    void CLI::Cd(const std::string& PathToAdd)
    {   
    client.Cd(PathToAdd);
    }

void CLI::List(const std::vector<PathInfo>& paths)
{
    for (auto& info : paths)
    {
        char buffer[4096];
        if (info.isDirectory)
        {
            sprintf_s(buffer, sizeof(buffer), "<DIR> %10llu %5s",info.size,info.name.c_str() );
        }
        else
        {
            sprintf_s(buffer, sizeof(buffer), "      %10llu %5s", info.size, info.name.c_str());
        }
        Logger << buffer<<"\n";
       
    }
}


