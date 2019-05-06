#include <iostream>
#include <csignal>
#include <cstdlib>
#include <string>

using namespace std;

struct TestData
{
	TestData(const char *name = "")
		: my_name(name)
	{
	}

	~TestData()
	{
		CleanUp();
	}

	void CleanUp()
	{
		printf("%s is cleaned\n", my_name.c_str());
	}

  private:
	string my_name;
};

TestData global_obj("global_obj");

void AbortHandler()
{
	printf("AbortHandler()\n");
	global_obj.CleanUp();
}

void signal_handler(int signum)
{
	switch (signum)
	{
	case SIGTERM: //确保被kill(未指定signal参数)时，走进程正常退出流程，确保调用各个对象析构函数清理相应资源，且不生成dump core
	case SIGINT:  //确保被ctrl-c时，走进程正常退出流程，确保调用各个对象析构函数清理相应资源，且不生成dump core
	case SIGTSTP: //确保被ctrl-z时，走进程正常退出流程，确保调用各个对象析构函数清理相应资源，且不生成dump core
		std::exit(0);
	case SIGSEGV: //确保非法地址访问导致进程终止时，手动调用资源清理函数，且生成dump core
	case SIGFPE:  //确保被零除导致进程终止时，手动调用资源清理函数，且生成dump core
		std::terminate();
	case SIGABRT:
		AbortHandler();
		break;
	default:
		printf("Catch unexpected signal: %d", signum);
		break;
	}
}

int main(int argc, char **argv)
{
	TestData local_obj("local_obj");

	//确保被kill(未指定signal参数)时，调用相应资源清理函数
	if (signal(SIGTERM, signal_handler) == SIG_ERR)
	{
		printf("Set SIGTERM handler failed");
		return 1;
	};

	//确保被ctrl-c时，调用相应资源清理函数
	if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
		printf("Set SIGINT handler failed");
		return 1;
	};

	//确保被ctrl-z时，调用相应资源清理函数
	if (signal(SIGTSTP, signal_handler) == SIG_ERR)
	{
		printf("Set SIGTSTP handler failed");
		return 1;
	};

	//确保非法地址访问导致进程终止时，调用相应资源清理函数
	if (signal(SIGSEGV, signal_handler) == SIG_ERR)
	{
		printf("Set SIGSEGV handler failed");
		return 1;
	};

	//确保被零除导致进程终止时，调用相应资源清理函数
	if (signal(SIGFPE, signal_handler) == SIG_ERR)
	{
		printf("Set SIGFPE handler failed");
		return 1;
	};

	if (signal(SIGABRT, signal_handler) == SIG_ERR)
	{
		printf("Set SIGABRT handler failed");
		return 1;
	};

	while (true)
	{
		switch (getchar())
		{
		case 'q':
			return 0;
		case 'e':
			throw std::exception();
		case 'n':
		{
			int *p = nullptr;
			*p = 666;
			break;
		}
		case 'z':
		{
			int d = 1 - 1;
			std::cout << 10 / d << std::endl;
			break;
		}
		case 'a':
			std::abort();
		}
	}

	return 0;
}