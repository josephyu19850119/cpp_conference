#include<shared_mutex>

class res_mgr
{
    mutable std::shared_timed_mutex rwlock;
    int res;

public:

    void Load(int new_res)
    {
        std::unique_lock<std::shared_timed_mutex>(rwlock);
        res = new_res;
    }

    int Get() const
    {
        std::shared_lock<std::shared_timed_mutex>(rwlock);
        return res;
    }
};