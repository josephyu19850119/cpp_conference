#include <iostream>
#include <signal.h>
#include <exception>
#include <cstdlib>

void signal_handler(int signum)
{
	switch(signum)
	{
		case SIGUSR1:
			std::cout << "catch SIGUSR1" << std::endl;
			break;
		case SIGUSR2:
			std::cout << "catch SIGUSR2" << std::endl;
			break;
		case SIGTERM:
			std::cout << "catch SIGTERM" << std::endl;
			std::terminate();
			// exit(0);
		case SIGINT:
			std::cout << "catch SIGINT" << std::endl;
			std::terminate();
			// exit(0);
		case SIGTSTP:
			std::cout << "catch SIGTSTP" << std::endl;
			std::terminate();
			// exit(0);
		default:
			std::cout << "catch other signal: " << signum << std::endl;
			break;
	}
}

void ExitHandler()
{
	std::cout << "ExitHandler()" << std::endl;
}
void TerminateHandler()
{
	std::cout << "TerminateHandler()" << std::endl;
}

int main(int argc, char **argv)
{
	if (signal(SIGUSR1, signal_handler) == SIG_ERR)
	{
		std::cout<<"signal(SIGUSR1, signal_handler) == SIG_ERR"<<std::endl;
		return -1;
	};
	if (signal(SIGUSR2, signal_handler) == SIG_ERR)
	{
		std::cout<<"signal(SIGUSR2, signal_handler) == SIG_ERR"<<std::endl;
		return -1;
	};
	if (signal(SIGTERM, signal_handler) == SIG_ERR)
	{
		std::cout<<"signal(SIGTERM, signal_handler) == SIG_ERR"<<std::endl;
		return -1;
	};
	if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
		std::cout<<"signal(SIGINT, signal_handler) == SIG_ERR"<<std::endl;
		return -1;
	};
	if (signal(SIGTSTP, signal_handler) == SIG_ERR)
	{
		std::cout<<"signal(SIGTSTP, signal_handler) == SIG_ERR"<<std::endl;
		return -1;
	};

	atexit(ExitHandler);
	std::set_terminate(TerminateHandler);

	while(true)
	{
		char c = getchar();
		if (c == 'e')
		{
			throw std::exception();
		}
		else if (c == 'q')
		{
			break;
		}	
	}

	return 0;
}