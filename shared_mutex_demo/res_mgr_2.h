#include<shared_mutex>

class res_mgr
{
    mutable std::shared_timed_mutex rwlock;
    int res;

public:

    void Load(int new_res)
    {
        rwlock.lock();
        res = new_res;
        rwlock.unlock();
    }

    int Get() const
    {
        rwlock.lock_shared();
        int result = res;
        rwlock.unlock_shared();
        return result;
    }
};