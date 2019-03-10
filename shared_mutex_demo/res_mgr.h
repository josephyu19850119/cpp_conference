#include<pthread.h>

class res_mgr
{
    mutable pthread_rwlock_t rwlock;
    int res;

public:

    res_mgr()
    {
        pthread_rwlock_init(&rwlock, nullptr);
    }

    ~res_mgr()
    {
        pthread_rwlock_destroy(&rwlock);
    }

    void Load(int new_res)
    {
        pthread_rwlock_wrlock(&rwlock);
        res = new_res;
        pthread_rwlock_unlock(&rwlock);
    }

    int Get() const
    {
        pthread_rwlock_rdlock(&rwlock);
        int result = res;
        pthread_rwlock_unlock(&rwlock);
        return result;
    }
};