#include<iostream>
// #include"res_mgr.h"
// #include"res_mgr_2.h"
#include"res_mgr_3.h"

using namespace std;



int main()
{
    // shared_timed_mutex locker;
    // thread t1([&locker]{
    //     locker.lock();
    //     cout<<"thread1 started"<<endl;
    //     cout<<"thread1 done"<<endl;
    //     locker.unlock();
    //     });
    // thread t2([&locker]{
    //     locker.lock();
    //     cout<<"thread2 started"<<endl;
    //     cout<<"thread2 done"<<endl;
    //     locker.unlock();
    //     });

    // locker.lock();
    //     locker.unlock();
    // shared_lock<shared_timed_mutex> l(locker);

    // t1.join();
    // t2.join();
    // cout<<"done"<<endl;
    res_mgr rm;
    return 0;
}