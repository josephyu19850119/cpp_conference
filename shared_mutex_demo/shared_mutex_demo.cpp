#include<thread>
#include<iostream>
// #include"res_mgr.h"
// #include"res_mgr_2.h"
#include"res_mgr_4.h"

using namespace std;



int main()
{
    res_mgr rm;
    rm.Load(666);
    thread t1([&rm]{
        for (int i = 0; i < 1000; ++i)
        {
            rm.Load(rm.Get() + 1);
        }
        });
    thread t2([&rm]{
        for (int i = 0; i < 1000; ++i)
        {
            rm.Load(rm.Get() - 1);
        }
        });

    t1.join();
    t2.join();
    cout<<"rm.Get() return: "<< rm.Get() << endl;
    // res_mgr rm1, rm2;
    // rm1 = rm2;
    return 0;
}