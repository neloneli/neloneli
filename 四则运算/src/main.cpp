#include"arith.h"


int main(int argc, char* argv[])
{
	try {
		std::vector<std::string> args;
		for (int i = 0; i < argc; ++i)
		{
			args.push_back(std::string(argv[i]));
		}

		if (args[1] == "-n" || args[1] == "-r")
		{
			int num, range;
			if (args[1] == "-n" && args[3] == "-r")
			{
				num = std::stoi(args[2]);
				range = std::stoi(args[4]);

			}
			else if (args[3] == "-n" && args[1] == "-r")
			{
				num = std::stoi(args[4]);
				range = std::stoi(args[2]);
			}
			else
			{
				std::cout << "输入参数不完整" << std::endl;
				return 0;
			}
			Generator gen(num, range);
		}
		else if (args[1] == "-e" || args[1] == "-a")
		{
			int epos, apos;
			if (args[1] == "-e" && args[3] == "-a")
			{
				epos = 2;
				apos = 4;
			}
			else if (args[3] == "-e" && args[1] == "-a")
			{
				apos = 2;
				epos = 4;
			}
			else
			{
				std::cout << "输入参数不完整" << std::endl;
				return 0;
			}

			Generator gen(args[epos].c_str(), args[apos].c_str());

		}
		else
		{
			std::cout << "输入参数不完整" << std::endl;
		}

		return 0;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception caught:" << e.what() << std::endl;
	}
}