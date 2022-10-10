#pragma once
#include <string>
#include <iostream>
#include "json.hpp"
namespace SDDS
{
	using json = nlohmann::json;
	class FileProcessor
	{
	public:
		void convertFile(std::string inputFile, std::string outputFileDir, std::string stylesheet, std::string language);
		void processFile(std::string inputFile, std::string outputFileDir, std::string styleSheet, std::string language);
		void parseJSONConfig(std::string, std::string &inputFile, std::string &outputFileDir, std::string &styleSheet, std::string &language);
		// Convert MarkDown file to HTML
		void convertFileMD(std::string inputFile, std::string outputFileDir, std::string stylesheet, std::string language);
		void chooseFileType(std::string inputFile, std::string outputFileDir, std::string styleSheet, std::string language);
	};
}
