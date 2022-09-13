#pragma once
#include<string>
#include<iostream>
#include<sstream>
#include<fstream>
#include<filesystem>
namespace SDDS {
	const std::string generateHTMLAsStr(const std::string fileName, const std::string content, const std::string stylesheet) {

		std::stringstream ss;
		ss << "<!doctype html>" <<
			"<html lang = \"en\">" << std::endl <<
			"<head>" << std::endl; 
		if (!stylesheet.empty())
			ss << "<link rel=\"stylesheet\" href=\"" << stylesheet  << "\"" << std::endl;
		ss << "<meta charset = \"utf-8\">" << std::endl <<
			"<title>" << fileName << "</title>" << std::endl <<
			"<meta name = \"viewport\" content = \"width=device-width, initial-scale=1\">" << std::endl <<
			"</head>" << std::endl <<
			"<body>" << std::endl <<
			content <<
			"</html>";

		return ss.str();
	}
	/**
	*
	*
	**/
	const std::string readFileAsHtmlStr(const std::string filePath) {
		std::ifstream input(filePath);
		std::string inputStr;
		while (input.good()) {
			std::string strTmp;
			std::getline(input, strTmp);
			strTmp = "<p>" + strTmp;
			strTmp.append("</p>");
			inputStr.append(strTmp);
			inputStr.append("\n");
		}
		return inputStr.c_str();


	}
	const bool writeHTMLToFile(const std::string filePath, const std::string htmlStr) {
		std::ofstream output(filePath);
		if (output.good()) {
			output << htmlStr;
			output.close();
			return true;
		}
		else
			return false;
	}
	const bool checkIfItsDirectory(const std::string path) {
		return std::filesystem::is_directory(path);
	}
	const std::string extractFileName(std::string filePath) {
		std::string fileName = filePath;
		if (filePath.find("/") != std::string::npos)
			fileName = filePath.substr(filePath.find_last_of("/") + 1, filePath.length());
		else if (filePath.find("\\") != std::string::npos)
			fileName = filePath.substr(filePath.find_last_of("\\") + 1, filePath.length());
		return fileName;

	}
}