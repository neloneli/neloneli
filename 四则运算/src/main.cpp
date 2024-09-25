#include"arith.h"


int main(int argc, char* argv[])
{
	try {
		if (argc != 5)
		{
			std::cout << "输入参数不完整" << std::endl;
			return 1;
		}
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
				return 1;
			}
			Generator gen(num, range);
			std::cout << "生成成功";
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
				return 1;
			}

			Generator gen(args[epos].c_str(), args[apos].c_str());
			std::cout << "判题成功" << std::endl;

		}
		else
		{
			std::cout << "输入参数不完整" << std::endl;
			return 1;
		}

		return 0;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception caught:" << e.what() << std::endl;
	}
}