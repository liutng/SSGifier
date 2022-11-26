#pragma once
#include <string>
namespace SDDS {
static std::string VERSION_NAME = "";
static int VERSION_CODE = 1;
class MessagePrinter {
public:
  void printHelp();
  /**
   * Print unkown switch error meessage.
   */
  void printUnknownSwitch(std::string switchName);
  /**
   * Print current software's version.
   */
  void printVersion();
  /**
   * Print intput file not found error message.
   */
  void printInputFileNotProvided();
  /**
   * Print empty argument error message.
   */
  void printEmptyArg(std::string switchName);
};
} // namespace SDDS
