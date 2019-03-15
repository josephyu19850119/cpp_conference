#include<iostream>
#include<future>
#include<thread>
#include<chrono>

using namespace std;

int main()
{
	int n = 10;

	std::future<int> listingA = std::async(std::launch::async,
        [] (int n) {//参数传递
		int sum = 0;
		for (int i = 0; i < n; ++i)
		{
			sum += i;
			printf("List A (%d):\t%d\n", i, sum);
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		return sum;
	}, n);

	// std::future_status s = listingA.wait_for(std::chrono::seconds(5));//std::future.wait_for()可以设置超时等待，并获知等待是否超时
	// if (s == std::future_status::ready)
	// {
	// 	printf("Listing A return %d\n", listingA.get());
	// }
	// else if (s == std::future_status::timeout)
	// {
	// 	printf("Listing A time out!\n");
	// }
    // else if (s == std::future_status::deferred)
    // {
	// 	printf("Listing A is deferred!\n");
    // }

	std::future<int> listingB = std::async(std::launch::async,
        [n] {//闭包传递

		int sum = 0;
		int j = 1;
		for (int i = 0; i < n; ++i)
		{
			sum += j;
			j *= 2;
			printf("List B (%d):\t%d\n", i, sum);
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		return sum;
	});

	printf("Listing A return %d\n", listingA.get());//std::future.get()有等待线程完成并获取返回值的双重作用
	printf("Listing B return %d\n", listingB.get());

    return 0;
}