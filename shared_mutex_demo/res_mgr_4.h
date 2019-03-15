#include<atomic>

class res_mgr
{
    std::atomic<int> res;

public:

    void Load(int new_res)
    {
        res = new_res;
    }

    int Get() const
    {
        return res;
    }
};