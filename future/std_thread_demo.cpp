#include<thread>
#include<iostream>

using namespace std;

int main()
{
    int n = 10;

    int sumA = 0;
    thread listingA([] (int n, int& sum) -> void{//参数传递

        sum = 0;
        for (int i = 0; i < n; ++i)
        {
            sum += i;
            printf("List A (%d):\t%d\n", i, sum);
            this_thread::sleep_for(chrono::seconds(1));
        }
    }, n, std::ref(sumA));//更灵活的参数传递方式，但仍然需要通过引用参数的方式获得线程计算结果

    int sumB = 0;
    thread listingB([n, &sumB] () -> void{//闭包传递

        sumB = 0;
        int m = 1;
        for (int i = 0; i < n; ++i)
        {
            sumB += m;
            m *= 2;
            printf("List B (%d):\t%d\n", i, sumB);
            this_thread::sleep_for(chrono::seconds(1));
        }
    });

    listingA.join();//仍然不能设置等待超时
    listingB.join();

    printf("Listing A return %d\n", sumA);
    printf("Listing B return %d\n", sumB);
    return 0;
}