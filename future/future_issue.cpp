#include<iostream>
#include<future>
#include<thread>
#include<chrono>
#include<cassert>

using namespace std;

void worker()
{
	cout << "worker start!" << endl;
	std::future<void> task = std::async(std::launch::async,
		[] {

		cout << "thread start!" << endl;
		std::this_thread::sleep_for(std::chrono::seconds(60));
		cout << "thread done!" << endl;
	});

	std::future_status s = task.wait_for(std::chrono::seconds(30));
	assert(s == std::future_status::timeout);


	cout << "worker done!" << endl;
}
int main()
{
	cout << "main start!" << endl;

	cout << "call worker" << endl;
	worker();
	cout << "worker return" << endl;

	cout << "main done!" << endl;
	return 0;
}