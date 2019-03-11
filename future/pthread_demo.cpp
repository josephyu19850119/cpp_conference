#include<pthread.h>
#include<unistd.h>
#include<cstdio>

int ret1;
void* listingA(void* p)
{
    int n = *static_cast<int*>(p);
    ret1 = 0;
    for (int i = 0; i < n; ++i)
    {
        ret1 += i;
        printf("List A (%d):\t%d\n", i, ret1);
        sleep(1);
    }
    return nullptr;
}

int ret2;
void* listingB(void* p)
{
    int n = *static_cast<int*>(p);
    ret2 = 0;
    int m = 1;
    for (int i = 0; i < n; ++i)
    {
        ret2 += m;
        m *= 2;
        printf("List B (%d):\t%d\n", i, ret2);
        sleep(1);
    }
    return nullptr;
}

int main()
{
    int n = 10;

    pthread_t thread_id1;
    pthread_create(&thread_id1, nullptr, listingA, &n);

    pthread_t thread_id2;
    pthread_create(&thread_id2, nullptr, listingB, &n);

    pthread_join(thread_id1, nullptr);
    pthread_join(thread_id2, nullptr);

    printf("Listing A return %d\n", ret1);
    printf("Listing B return %d\n", ret2);
    return 0;
}