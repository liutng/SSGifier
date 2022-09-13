#pragma once
namespace SDDS {

	class Argument {
	public:
		friend class ArgumentQueue;
		enum class ArgTag { VERSION, INPUT, OUTPUT, HELP, UNKOWN, ERROR,EMPTY,CSS };
		ArgTag getArgTag();
		bool parseArg(const char* switchStr, const char* arg);
		~Argument();
	private:
		SDDS::Argument::ArgTag mArgTag = SDDS::Argument::ArgTag::UNKOWN;
		char* mArg = nullptr;
		char* mSwitchStr = nullptr;
		
		
	};
	class ArgumentQueue {
		Argument** mArgs = new Argument*[0];
		size_t mArgCnt = 0;
		std::string mMessage;
		void convertFile(std::string inputFile, std::string outputFileDir, std::string stylesheet);
	public:
		bool addArg(const char* switchStr, const char* arg);
		bool execute();
		~ArgumentQueue();
	};
}
