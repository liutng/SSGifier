#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
namespace SDDS
{
	const std::string generateHTMLAsStr(const std::string fileName, const std::string content, const std::string stylesheet)
	{

		std::stringstream ss;
		ss << "<!doctype html>\n"
		   << "<html lang = \"en\">" << std::endl
		   << "<head>" << std::endl;
		if (!stylesheet.empty())
			ss << "<link rel=\"stylesheet\" href=\"" << stylesheet << "\"" << std::endl;
		ss << "<meta charset = \"utf-8\">" << std::endl
		   << "<title>" << fileName << "</title>" << std::endl
		   << "<meta name = \"viewport\" content = \"width=device-width, initial-scale=1\">" << std::endl
		   << "</head>" << std::endl
		   << "<body>" << std::endl
		   << "<h1> " << fileName << "</h1>" << std::endl
		   << "<br>" << std::endl
		   << "<br>" << std::endl
		   << content << "</body>\n</html>";

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
			inputStr.append("</h1>\n").append("<br>\n").append("<br>\n");
			inputStr = "<h1>" + inputStr;
		}
		while (input.good())
		{
			std::string strTmp;
			std::getline(input, strTmp);
			strTmp = "<p>" + strTmp;
			strTmp.append("</p>");
			inputStr.append(strTmp);
			inputStr.append("\n");
		}
		return inputStr.c_str();
	}
	//Markdown version of read File
	const std::string readFileAsHtmlStrMD(const std::string filePath) //Markdown Conversion 
	{
		std::ifstream input(filePath);
		std::string inputStr;
		if (input.good())
		{
			std::getline(input, inputStr);
			inputStr.append("</h1>\n").append("<br>\n").append("<br>\n");
			inputStr = "<h1>" + inputStr;
		}
		while (input.good())
		{
			std::string strTmp;
			std::getline(input, strTmp);
			//Checks for markdown heading tag
			if (strTmp.find("# ") != std::string::npos)
			{
				if (strTmp.at(0) == '#' && strTmp.at(1) == ' ')
				{
					strTmp.replace(0, 2, "");
					strTmp = "<h1>" + strTmp;
					strTmp.append("</h1>");
				}
				else
				{
					strTmp = "<p>" + strTmp;
					strTmp.append("</p>");
				}
			}
			else
			{
				strTmp = "<p>" + strTmp;
				strTmp.append("</p>");
			}

			//Indents the string by finding the astrix
			if (strTmp.find('*') != std::string::npos)
			{
				//Position of the first astrix
				size_t astrix = strTmp.find("*");
				//Position of the last astrix
				size_t pos = 0;

				//Loops through the string to look for the astrix
				for (size_t i = astrix + 1; i < strTmp.size(); i++)
				{
					if (strTmp.at(i) == '*')
						pos = i;
				}

				//Stores the end of the string to add after the indent
				std::string endStr = strTmp.substr(pos + 1);

				std::string newStr = "<i>" + strTmp.substr(astrix + 1, (pos - astrix) - 1) + "</i>";
				strTmp.replace(strTmp.find("*"), newStr.size(), newStr);
				strTmp.append(endStr);
			}

			inputStr.append(strTmp);
			inputStr.append("\n");
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
}