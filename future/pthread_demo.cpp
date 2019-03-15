#include<pthread.h>
#include<unistd.h>
#include<cstdio>

struct thread_params
{
    int n;
    int result;//不能通过返回值的方式获得线程计算结果
};

void* listingA(void* p)
{
    thread_params* params = static_cast<thread_params*>(p);
    params->result = 0;
    for (int i = 0; i < params->n; ++i)
    {
        params->result += i;
        printf("List A (%d):\t%d\n", i, params->result);
        sleep(1);
    }
    return nullptr;
}

void* listingB(void* p)
{
    thread_params* params = static_cast<thread_params*>(p);
    params->result = 0;
    int m = 1;
    for (int i = 0; i < params->n; ++i)
    {
        params->result += m;
        m *= 2;
        printf("List B (%d):\t%d\n", i, params->result);
        sleep(1);
    }
    return nullptr;
}

int main()
{
    thread_params listingA_params, listingB_params;//传多个参数方式不灵活，需要打包在一个结构体中传递
    listingA_params.n = 10;
    listingB_params.n = 10;

    pthread_t thread_id1;
    pthread_create(&thread_id1, nullptr, listingA, &listingA_params);

    pthread_t thread_id2;
    pthread_create(&thread_id2, nullptr, listingB, &listingB_params);

    pthread_join(thread_id1, nullptr);//不能设置等待超时
    pthread_join(thread_id2, nullptr);

    printf("Listing A return %d\n", listingA_params.result);
    printf("Listing B return %d\n", listingB_params.result);
    return 0;
}