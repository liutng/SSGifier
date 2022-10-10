#include "FileProcessor.h"
#include "Utils.h"

void SDDS::FileProcessor::convertFile(std::string inputFile, std::string outputFileDir, std::string stylesheet, std::string language)
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
		if (outputFileDir.substr(0, 2) == "./" || outputFileDir.substr(0, 2) == ".\\") // remove the ./ or .\ at the begining of the output file directory.
			outputFileDir = outputFileDir.substr(outputFileDir.find(".") + 1, outputFileDir.length());
		if (outputFileDir.find("\\") == std::string::npos && outputFileDir.find("/") == std::string::npos) // Append the output path with "/" if the output arg is not postfixed with /
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

void SDDS::FileProcessor::processFile(std::string inputFile, std::string outputFileDir, std::string styleSheet, std::string language)
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

	if (SDDS::checkIfItsDirectory(inputFile))
	{ // if the input arg is a directory
		for (const auto &entry : std::filesystem::directory_iterator(inputFile))
		{
			chooseFileType(entry.path().string(), outputFileDir, styleSheet, language);
		}
	}
	// added checks for if it is a text file or markdown file
	else
	{
		chooseFileType(inputFile, outputFileDir, styleSheet, language);
	}
}

void SDDS::FileProcessor::parseJSONConfig(std::string configPath, std::string &inputFile, std::string &outputFileDir, std::string &styleSheet, std::string &language)
{
	try
	{
		json data = SDDS::readJSONContents(configPath);

		// goes through the JSON object and fills the options with the correct input
		for (json::iterator it = data.begin(); it != data.end(); ++it)
		{
			if (it.key() == "input")
			{
				inputFile = *it;
			}
			else if (it.key() == "output")
			{
				outputFileDir = *it;
			}
			else if (it.key() == "stylesheet")
			{
				styleSheet = *it;
			}
			else if (it.key() == "lang")
			{
				language = *it;
			}
		}
	}
	catch (const std::exception &e)
	{
		std::cout << "Cannot find config file: " << configPath << std::endl;
		throw std::exception();
	}
}

void SDDS::FileProcessor::convertFileMD(std::string inputFile, std::string outputFileDir, std::string stylesheet, std::string language)
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

void SDDS::FileProcessor::chooseFileType(std::string inputFile, std::string outputFileDir, std::string styleSheet, std::string language)
{
	if (inputFile.find(".txt") != std::string::npos) // checks if it is txt file
		convertFile(inputFile, outputFileDir, styleSheet, language);
	else if (inputFile.find(".md") != std::string::npos) // checks if it is md file
		convertFileMD(inputFile, outputFileDir, styleSheet, language);
	else
		std::cout << "Cannot Find File or Directory" << std::endl;
}
