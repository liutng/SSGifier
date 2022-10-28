#ifndef SDDS_UTILS
#define SDDS_UTILS
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include "maddy/parser.h"
#include "json.hpp"

using json = nlohmann::json;

namespace SDDS
{
	const std::string generateHTMLAsStr(const std::string fileName, const std::string content, const std::string stylesheet, const std::string language)
	{
		std::stringstream ss;
		ss << "<!doctype html>"
		   << "<html lang = \"" << (language.empty() ? "en-CA" : language) << "\">"
		   << "<head>";
		if (!stylesheet.empty())
			ss << "<link rel=\"stylesheet\" href=\"" << stylesheet << "\"";
		ss << "<meta charset = \"utf-8\">"
		   << "<title>" << fileName << "</title>"
		   << "<meta name = \"viewport\" content = \"width=device-width, initial-scale=1\">"
		   << "</head>"
		   << "<body>"
		   << "<h1> " << fileName << "</h1>"
		   << "<br>"
		   << "<br>"
		   << content << "</body></html>";

		return ss.str();
	}
	/**
	 *
	 *
	 **/
	const std::string readFileAsHtmlStr(const std::string filePath)
	{
		std::ifstream input(filePath);
		std::string inputStr;
		if (input.good())
		{
			std::getline(input, inputStr);
			inputStr.append("</h1>").append("<br>").append("<br>");
			inputStr = "<h1>" + inputStr;
		}
		while (input.good())
		{
			std::string strTmp;
			std::getline(input, strTmp);
			strTmp = "<p>" + strTmp;
			strTmp.append("</p>");
			inputStr.append(strTmp);
		}
		return inputStr.c_str();
	}
	// Markdown version of read File
	const std::string readFileAsHtmlStrMD(const std::string filePath) // Markdown Conversion
	{
		std::ifstream input(filePath);
		std::string inputStr;
		std::shared_ptr<maddy::ParserConfig> config = std::make_shared<maddy::ParserConfig>();
		std::shared_ptr<maddy::Parser> parser = std::make_shared<maddy::Parser>(config);

		while (input.good())
		{
			std::string strTmp;
			std::getline(input, strTmp);
			// Checks for markdown heading tag
			std::stringstream strStream(strTmp);
			std::string htmlOutput = parser->Parse(strStream);
			inputStr.append(htmlOutput);
		}
		return inputStr.c_str();
	}
	const bool writeHTMLToFile(const std::string filePath, const std::string htmlStr)
	{
		std::ofstream output(filePath);
		if (output.good())
		{
			output << htmlStr;
			output.close();
			return true;
		}
		else
			return false;
	}
	const bool checkIfItsDirectory(const std::string path)
	{
		return std::filesystem::is_directory(path);
	}
	const std::string extractFileName(std::string filePath)
	{
		std::string fileName = filePath;
		if (filePath.find("/") != std::string::npos)
			fileName = filePath.substr(filePath.find_last_of("/") + 1, filePath.length());
		else if (filePath.find("\\") != std::string::npos)
			fileName = filePath.substr(filePath.find_last_of("\\") + 1, filePath.length());
		return fileName;
	}
	const json readJSONContents(std::string config)
	{
		json data;
		try
		{
			std::ifstream input(config);
			data = json::parse(input);
		}
		catch (const std::exception &e)
		{
			throw std::exception();
		}
		return data;
	}
}

#endif // !SDDS_UTIILS