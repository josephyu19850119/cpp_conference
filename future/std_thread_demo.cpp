#include<thread>
#include<iostream>

using namespace std;

int main()
{
    int n = 10;

    int sum1 = 0;
    thread listingA([] (int n, int& sum) -> void{

        sum = 0;
        for (int i = 0; i < n; ++i)
        {
            sum += i;
            printf("List A (%d):\t%d\n", i, sum);
            this_thread::sleep_for(chrono::seconds(1));
        }
    }, n, std::ref(sum1));//更灵活的参数传递方式，但仍然需要通过引用参数的方式获得线程计算结果

    int sum2 = 0;
    thread listingB([] (int n, int& sum) -> void{

        sum = 0;
        int m = 1;
        for (int i = 0; i < n; ++i)
        {
            sum += m;
            m *= 2;
            printf("List B (%d):\t%d\n", i, sum);
            this_thread::sleep_for(chrono::seconds(1));
        }
    }, n, std::ref(sum2));

    listingA.join();//仍然不能设置等待超时
    listingB.join();

    printf("Listing A return %d\n", sum1);
    printf("Listing B return %d\n", sum2);
    return 0;
}