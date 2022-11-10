#ifndef SDDS_UTILS
#define SDDS_UTILS
#include "json.hpp"
#include "maddy/parser.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using json = nlohmann::json;

namespace SDDS {
  const std::string generateHTMLAsStr(const std::string fileName,
                                    const std::string content,
                                    const std::string stylesheet,
                                    const std::string language);
/**
 *
 *
 **/
const std::string readFileAsHtmlStr(const std::string filePath);
// Markdown version of read File
const std::string
readFileAsHtmlStrMD(const std::string filePath); // Markdown Conversion

const bool writeHTMLToFile(const std::string filePath,
                           const std::string htmlStr) ;
const bool checkIfItsDirectory(const std::string path);
const std::string extractFileName(std::string filePath);
const json readJSONContents(std::string config);
} // namespace SDDS

#endif // !SDDS_UTIILS