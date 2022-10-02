#include <iostream>
#include <string>
#include <cstring>
#include <filesystem>
#include "ArgumentQueue.h"
#include "Utils.h"
#include "json.hpp"

using json = nlohmann::json;

bool SDDS::ArgumentQueue::addArg(const char *switchStr, const char *arg)
{
	bool rc;
	Argument *tmpArg = new Argument();
	rc = tmpArg->parseArg(switchStr, arg);
	mArgs[mArgCnt++] = tmpArg;
	return rc;
}
bool SDDS::ArgumentQueue::execute()
{
	bool rc = false;
	bool showVersion = false, showHelp = false, emptyArg = false, unkownArg = false, hasConfig = false;
	std::string unkownSwitchStr;
	std::string emptySwtichStr;
	std::string inputFile;
	std::string outputFileDir;
	std::string styleSheet;
	std::string language;
	std::string config;
	if (mArgCnt == 0)
	{
		mMessage = "Please at least specify an input file.";
	}
	else
	{
		for (size_t i = 0; i < mArgCnt; i++)
		{
			switch (mArgs[i]->getArgTag())
			{
			case Argument::ArgTag::INPUT:
				inputFile = mArgs[i]->mArg;
				break;
			case Argument::ArgTag::OUTPUT:
				outputFileDir = mArgs[i]->mArg;
				break;
			case Argument::ArgTag::VERSION:
				showVersion = !showVersion;
				break;
			case Argument::ArgTag::EMPTY:
				emptyArg = !emptyArg;
				emptySwtichStr = mArgs[i]->mSwitchStr;
				break;
			case Argument::ArgTag::UNKOWN:
				unkownArg = !unkownArg;
				unkownSwitchStr = mArgs[i]->mSwitchStr;
				break;
			case Argument::ArgTag::HELP:
				showHelp = true;
				break;
			case Argument::ArgTag::CSS:
				styleSheet = mArgs[i]->mArg;
				break;
			case Argument::ArgTag::LANGUAGE:
				language = mArgs[i]->mArg;
				break;
			case Argument::ArgTag::CONFIG:
				config = mArgs[i]->mArg;
				hasConfig = true;
				break;
			}
		}
		if (hasConfig)
		{
			try
			{
				json data = SDDS::readJSONContents(config);

				// goes through the JSON object and fills the options with the correct input
				for (json::iterator it = data.begin(); it != data.end(); ++it) {
					if (it.key() == "input")
					{
						inputFile = *it;
					}
					else if(it.key() == "output")
					{
						outputFileDir = *it;
					}
					else if(it.key() == "stylesheet")
					{
						styleSheet = *it;
					}
					else if(it.key() == "lang")
					{
						language = *it;
					}
					
				}
			}
			catch(const std::exception& e)
			{
				std::cout << "Cannot find config file: " << config << std::endl;
				throw std::exception();
			}
		}
		if (unkownArg)
		{
			std::cout << "Unkown switch "
					  << "\"" << unkownSwitchStr << "\"." << std::endl
					  << "Use --help or -h for help." << std::endl;
			throw std::exception();
		}
		else if (showHelp)
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
		else if (showVersion)
			std::cout << "SSGifier V0.1 by Tong Liu" << std::endl;
		else if (emptyArg)
		{
			std::cout << "Empty argument for " << '"' << emptySwtichStr << '"' << " is provided." << std::endl;
			throw std::exception();
		}
		else if (inputFile.empty())
			std::cout << "Input file is necessary to be provided." << std::endl;
		else
		{
			if (outputFileDir.empty())
			{
				std::cout << "Default directory \"dist\" will be used as the output directory." << std::endl;
				outputFileDir = "dist/";
			}
			if (std::filesystem::exists(outputFileDir))
			{ // Clear the output directory first.
				std::filesystem::remove_all(outputFileDir);
			}

			//removes ./ if input has it inside of the command
			if (inputFile.at(0) == '.' && inputFile.at(1) == '/')
			{
				inputFile = inputFile.substr(2);
			}
			//removes ./ if outPutDir has it inside of the command
			if (outputFileDir.at(0) == '.' && outputFileDir.at(1) == '/')
			{
				outputFileDir = outputFileDir.substr(2);
			}

			if (SDDS::checkIfItsDirectory(inputFile))
			{ // if the input arg is a directory
				for (const auto &entry : std::filesystem::directory_iterator(inputFile))
				{
					if (entry.path().string().find(".txt") != std::string::npos) // process .txt files
						convertFile(entry.path().string(), outputFileDir, styleSheet, language);
					else if (entry.path().string().find(".md") != std::string::npos) // process .md files
						convertFileMD(entry.path().string(), outputFileDir, styleSheet, language);
				}
			}
			// added checks for if it is a text file or markdown file
			else if (inputFile.find(".txt") != std::string::npos) // checks if it is txt file
			{
				convertFile(inputFile, outputFileDir, styleSheet, language);
			}
			else if (inputFile.find(".md") != std::string::npos) // checks if it is md file
			{
				convertFileMD(inputFile, outputFileDir, styleSheet, language);
			}
			else
			{
				std::cout << "Cannot Find File or Directory" << std::endl;
			}
		}
	}
	return rc;
}
SDDS::ArgumentQueue::~ArgumentQueue()
{
}
bool SDDS::Argument::parseArg(const char *switchStr, const char *arg)
{
	if (mArg != nullptr)
		delete mArg;
	if (arg != nullptr)
	{
		mArg = new char[std::strlen(arg)];
		std::strcpy(mArg, arg);
	}
	mSwitchStr = new char[std::strlen(switchStr)];
	strcpy(mSwitchStr, switchStr);

	if (std::strcmp(switchStr, "--help") == 0 || std::strcmp(switchStr, "-h") == 0)
	{
		mArgTag = ArgTag::HELP;
	}
	else if (std::strcmp(switchStr, "--input") == 0 || std::strcmp(switchStr, "-i") == 0)
	{
		mArgTag = ArgTag::INPUT;
	}
	else if (std::strcmp(switchStr, "--output") == 0 || std::strcmp(switchStr, "-o") == 0)
	{
		mArgTag = ArgTag::OUTPUT;
	}
	else if (std::strcmp(switchStr, "--version") == 0 || std::strcmp(switchStr, "-v") == 0)
	{
		mArgTag = ArgTag::VERSION;
	}
	else if (std::strcmp(switchStr, "--stylesheet") == 0 || std::strcmp(switchStr, "-s") == 0)
		mArgTag = ArgTag::CSS;
	else if (std::strcmp(switchStr, "--lang") == 0 || std::strcmp(switchStr, "-l") == 0 || std::strcmp(switchStr, "/l") == 0 || std::strcmp(switchStr, "\\l") == 0)
		mArgTag = ArgTag::LANGUAGE;
	else if (std::strcmp(switchStr, "--config") == 0 || std::strcmp(switchStr, "-c") == 0)
	{
		mArgTag = ArgTag::CONFIG;
	}
	else
	{
		mArgTag = ArgTag::UNKOWN;
		return false;
	}
	// check if argument is necessary for the current switch
	if (mArgTag != ArgTag::VERSION && mArgTag != ArgTag::HELP && mArgTag != ArgTag::UNKOWN)
	{
		if (arg == nullptr)
		{
			mArgTag = ArgTag::EMPTY;
			return false;
		}
	}
	return true;
}

SDDS::Argument::ArgTag SDDS::Argument::getArgTag()
{
	return mArgTag;
}
SDDS::Argument::~Argument()
{
	// if (mArg != nullptr)
	// delete[] mArg;
}

void SDDS::ArgumentQueue::convertFile(std::string inputFile, std::string outputFileDir, std::string stylesheet, std::string language)
{

	std::string fileContent = SDDS::readFileAsHtmlStr(inputFile).c_str();
	std::filesystem::create_directory(outputFileDir);
	if (fileContent.empty())
	{
		std::cout << "Cannot find file or directory: " << inputFile << std::endl;
		throw std::exception();
	}
	else
	{
		std::string fileName = SDDS::extractFileName(inputFile);
		fileName = fileName.substr(0, fileName.find('.'));
		const std::string HTMLContentStr = SDDS::generateHTMLAsStr(fileName, fileContent, stylesheet, language);
		if (outputFileDir.substr(0, 2) == "./" || outputFileDir.substr(0, 2) == ".\\") // remove the ./ or .\ at the begining of output file directory.
			outputFileDir = outputFileDir.substr(outputFileDir.find(".") + 1, outputFileDir.length());
		if (outputFileDir.find("\\") == std::string::npos && outputFileDir.find("/") == std::string::npos) // Append output path with "/" if the output arg is not postfixed with /
			outputFileDir.append("/");
		std::string filePath = "./" + outputFileDir + fileName + ".html";
		if (SDDS::writeHTMLToFile(filePath, HTMLContentStr))
			std::cout << filePath << " is successfully converted and written." << std::endl;
		else
		{
			std::cout << "Could not write " << filePath << std::endl;
			throw std::exception();
		}
	}
}

// Markdown version of Convert File
void SDDS::ArgumentQueue::convertFileMD(std::string inputFile, std::string outputFileDir, std::string stylesheet, std::string language)
{
	std::string fileContent = SDDS::readFileAsHtmlStrMD(inputFile).c_str();
	std::filesystem::create_directory(outputFileDir);
	if (fileContent.empty())
	{
		std::cout << "Cannot find file or directory: " << inputFile << std::endl;
	}
	else
	{
		std::string fileName = SDDS::extractFileName(inputFile);
		fileName = fileName.substr(0, fileName.find('.'));
		const std::string HTMLContentStr = SDDS::generateHTMLAsStr(fileName, fileContent, stylesheet, language);
		if (outputFileDir.substr(0, 2) == "./" || outputFileDir.substr(0, 2) == ".\\") // remove the ./ or .\ at the begining of output file directory.
			outputFileDir = outputFileDir.substr(outputFileDir.find(".") + 1, outputFileDir.length());
		if (outputFileDir.find("\\") == std::string::npos && outputFileDir.find("/") == std::string::npos) // Append output path with "/" if the output arg is not postfixed with /
			outputFileDir.append("/");
		std::string filePath = "./" + outputFileDir + fileName + ".html";
		if (SDDS::writeHTMLToFile(filePath, HTMLContentStr))
			std::cout << filePath << " is successfully converted and written." << std::endl;
		else
			std::cout << "Could not write " << filePath << std::endl;
	}
}
