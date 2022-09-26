#include <iostream>
#include "ArgumentQueue.h"

int main(int argc, char *argv[])
{
	SDDS::ArgumentQueue argQueue;
	if (argc <= 1)
	{
		std::cout << "At least specify an input file. \nPlease run -h or --help for help " << std::endl;
		exit(-1);
	}
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-' || argv[i][0] == '/' || argv[i][0] == '\\')
		{
			if (!argQueue.addArg(argv[i], argv[i + 1]))
				exit(-1);
		}
	}
	argQueue.execute();

	exit(0);
}