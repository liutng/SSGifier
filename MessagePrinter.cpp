#include <iostream>
#include "MessagePrinter.h"

void SDDS::MessagePrinter::printHelp()
{
	std::cout
		<< "Usage: ssgifier --input <file/directory path> [optional command]" << std::endl
		<< std::endl
		<< "SSGifier is a commandline application to generate static website from txt or md files." << std::endl
		<< std::endl
		<< "The list below is all the different parameters you can pass to SSGifier." << std::endl
		<< "-o, --output - (Optional) specify the output directory, the directory \" dlist\" is used by default." << std::endl
		<< "-i, --input - (Necessary) specify the input files\\directory, this is an necessary argument." << std::endl
		<< "-s, --stylesheet - (Optional) specify the stylesheet for the HTML pages." << std::endl
		<< "-l, --lang, /l, \\l - (Optional) specify the language that the HTML uses, it will be added to lang attirbute of <html>." << std::endl
		<< "-h, --help - show help." << std::endl
		<< "-v, --version - prints out the version of SSGifier" << std::endl;
}

void SDDS::MessagePrinter::printUnknownSwitch(std::string switchName)
{
	std::cout << "Unkown switch "
		<< "\"" << switchName << "\"." << std::endl
		<< "Use --help or -h for help." << std::endl;
	throw std::exception();
}

void SDDS::MessagePrinter::printVersion()
{
	std::cout << "SSGifier " << SDDS::VERSION_NAME << " by Tong Liu" << std::endl;
}

void SDDS::MessagePrinter::printInputFileNotProvided()
{
	std::cout << "Input file is necessary to be provided." << std::endl;
}

void SDDS::MessagePrinter::printEmptyArg(std::string switchName)
{
	std::cout << "Empty argument for " << '"' << switchName << '"' << " is provided." << std::endl;
}
