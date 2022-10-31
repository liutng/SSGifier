#define _CRT_SECURE_NO_WARNINGS
#include "ArgumentQueue.h"
#include <cstring>
#include <filesystem>
#include <iostream>
#include <string>

bool SDDS::ArgumentQueue::addArg(const char *switchStr, const char *arg) {
  bool rc;
  Argument *tmpArg = new Argument();
  rc = tmpArg->parseArg(switchStr, arg);
  mArgs[mArgCnt++] = tmpArg;
  return rc;
}
bool SDDS::ArgumentQueue::execute() {
  bool rc = false;
  bool showVersion = false, showHelp = false, emptyArg = false,
       unkownArg = false, hasConfig = false;
  std::string unkownSwitchStr;
  std::string emptySwtichStr;
  std::string inputFile;
  std::string outputFileDir;
  std::string styleSheet;
  std::string language;
  std::string config;
  if (mArgCnt == 0) {
    mMessage = "Please at least specify an input file.";
  } else {
    for (size_t i = 0; i < mArgCnt; i++) {
      switch (mArgs[i]->getArgTag()) {
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
      default:
        unkownArg = !unkownArg;
        unkownSwitchStr = mArgs[i]->mSwitchStr;
      }
    }
    if (hasConfig)
      try {
        fileProcessor.parseJSONConfig(config, inputFile, outputFileDir,
                                      styleSheet, language);
      } catch (const std::exception ex) {
        throw std::exception();
      }
    if (unkownArg) {
      messagePrinter.printUnknownSwitch(unkownSwitchStr);
      throw std::exception();
    } else if (showHelp)
      messagePrinter.printHelp();
    else if (showVersion)
      messagePrinter.printVersion();
    else if (emptyArg) {
      messagePrinter.printEmptyArg(emptySwtichStr);
      throw std::exception();
    } else if (inputFile.empty())
      messagePrinter.printInputFileNotProvided();
    else
      fileProcessor.processFile(inputFile, outputFileDir, styleSheet, language);
  }
  return rc;
}
SDDS::ArgumentQueue::ArgumentQueue() {
  fileProcessor = FileProcessor();
  messagePrinter = MessagePrinter();
}
SDDS::ArgumentQueue::~ArgumentQueue() {}
bool SDDS::Argument::parseArg(const char *switchStr, const char *arg) {
  if (mArg != nullptr)
    delete mArg;
  if (arg != nullptr) {
    mArg = new char[std::strlen(arg)];
    std::strncpy(mArg, arg, std::strlen(arg));
  }
  mSwitchStr = new char[std::strlen(switchStr)];
  std::strncpy(mSwitchStr, switchStr, std::strlen(switchStr));

  if (std::strcmp(switchStr, "--help") == 0 ||
      std::strcmp(switchStr, "-h") == 0) {
    mArgTag = ArgTag::HELP;
  } else if (std::strcmp(switchStr, "--input") == 0 ||
             std::strcmp(switchStr, "-i") == 0) {
    mArgTag = ArgTag::INPUT;
  } else if (std::strcmp(switchStr, "--output") == 0 ||
             std::strcmp(switchStr, "-o") == 0) {
    mArgTag = ArgTag::OUTPUT;
  } else if (std::strcmp(switchStr, "--version") == 0 ||
             std::strcmp(switchStr, "-v") == 0) {
    mArgTag = ArgTag::VERSION;
  } else if (std::strcmp(switchStr, "--stylesheet") == 0 ||
             std::strcmp(switchStr, "-s") == 0)
    mArgTag = ArgTag::CSS;
  else if (std::strcmp(switchStr, "--lang") == 0 ||
           std::strcmp(switchStr, "-l") == 0 ||
           std::strcmp(switchStr, "/l") == 0 ||
           std::strcmp(switchStr, "\\l") == 0)
    mArgTag = ArgTag::LANGUAGE;
  else if (std::strcmp(switchStr, "--config") == 0 ||
           std::strcmp(switchStr, "-c") == 0) {
    mArgTag = ArgTag::CONFIG;
  } else {
    mArgTag = ArgTag::UNKOWN;
    return false;
  }
  // check if argument is necessary for the current switch
  if (mArgTag != ArgTag::VERSION && mArgTag != ArgTag::HELP &&
      mArgTag != ArgTag::UNKOWN) {
    if (arg == nullptr) {
      mArgTag = ArgTag::EMPTY;
      return false;
    }
  }
  return true;
}

SDDS::Argument::ArgTag SDDS::Argument::getArgTag() { return mArgTag; }
SDDS::Argument::~Argument() {
  // if (mArg != nullptr)
  // delete[] mArg;
}

// Markdown version of Convert File
