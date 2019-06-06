#include <unistd.h>

#include <csignal>
#include <iostream>
#include <string>
using namespace std;

#include <boost/interprocess/managed_shared_memory.hpp>

class TestData
{
    string res_id;
    boost::interprocess::managed_shared_memory managed_shm;

public:
    ~TestData()
    {
        if (!res_id.empty())
        {
            CleanUp();
        }
    }
    void Load(const string& _res_id, bool open_only)
    {
        if (open_only)
        {
            printf("Try to open shared memory object: [%s]\n", _res_id.c_str());
            managed_shm = boost::interprocess::managed_shared_memory{boost::interprocess::open_only, _res_id.c_str()};
            printf("Open shared memory object: [%s]\n", _res_id.c_str());
        }
        else
        {
            printf("Try to create shared memory object: [%s]\n", _res_id.c_str());
            managed_shm = boost::interprocess::managed_shared_memory{boost::interprocess::create_only, _res_id.c_str(), 1024};
            printf("Create shared memory object: [%s]\n", _res_id.c_str());
        }

        res_id = _res_id;
    }

    bool CleanUp()
    {
        printf("Try to remove shared memory object: [%s]\n", res_id.c_str());

        bool ret = boost::interprocess::shared_memory_object::remove(res_id.c_str());
        
        if (ret)
        {
            printf("Removed shared memory object: [%s]\n", res_id.c_str());
        }
        else
        {
            printf("Failed remove shared memory object: [%s]\n", res_id.c_str());
        }

        return ret;
    }
};

TestData test_data;

void AbortHandler()
{
	printf("AbortHandler()\n");
    test_data.CleanUp();
}

void signal_handler(int signum)
{
	switch (signum)
	{
	case SIGTERM: //确保被kill(未指定signal参数)时，走进程正常退出流程，确保调用各个对象析构函数清理相应资源，且不生成dump core
	case SIGINT:  //确保被ctrl-c时，走进程正常退出流程，确保调用各个对象析构函数清理相应资源，且不生成dump core
	case SIGTSTP: //确保被ctrl-z时，走进程正常退出流程，确保调用各个对象析构函数清理相应资源，且不生成dump core
		std::exit(0);
	case SIGQUIT: //确保被用类似"kill -3"这样的方法终止进程并生成core时，调用相应资源清理函数
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

    //确保被用类似"kill -3"这样的方法终止进程并生成core时，调用相应资源清理函数
	if (signal(SIGQUIT, signal_handler) == SIG_ERR)
	{
		printf("Set SIGQUIT handler failed");
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

    string res_id;
	if (argc > 1)
	{
		res_id = argv[1];
	}
	else
	{
		res_id = "formalize_dict_" + to_string(getpid());
	}

    try
    {
        if (argc > 2 && argv[2] == std::string("remove"))
        {
            bool ret = boost::interprocess::shared_memory_object::remove(res_id.c_str());
            
            if (ret)
            {
                printf("Removed shared memory object: [%s]\n", res_id.c_str());
            }
            else
            {
                printf("Failed remove shared memory object: [%s]\n", res_id.c_str());
            }

            return 0;            
        }

        test_data.Load(res_id, argc > 2 && argv[2] == std::string("open"));

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
    }
    catch (boost::interprocess::interprocess_exception e)
    {
        printf("%s: %s\n", e.what(), res_id.c_str());
    }

    return 0;
}