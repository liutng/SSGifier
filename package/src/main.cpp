#include "ArgumentQueue.h"
#include <iostream>

int main(int argc, char *argv[]) {
  SDDS::ArgumentQueue argQueue;
  if (argc <= 1) {
    std::cout
        << "At least specify an input file. \nPlease run -h or --help for help "
        << std::endl;
    return -1;
  }
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' || argv[i][0] == '/' || argv[i][0] == '\\') {
      argQueue.addArg(argv[i], argv[i + 1]);
    }
  }
  try {
    argQueue.execute();
  } catch (std::exception ex) {
    return -1;
  }
  return 0;
}