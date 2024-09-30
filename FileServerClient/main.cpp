#include <iostream>
#include <boost/program_options.hpp>
#include "CLI.h"
using namespace std;


const int DEFEAULT_PORT = 3333;
const string DEAFULT_HOST = "127.0.0.1";
int main(int argc, char** argv)
{
	boost::asio::io_context io_context;
	CLI Cli(DEFEAULT_PORT, DEAFULT_HOST,io_context);
	Cli.TryParse(argc,argv);
	Cli.Start();
	return 0;
}
