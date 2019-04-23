#include <iostream>
#include <string>

#include <cstdio>

#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std;

int main()
{
    key_t key = ftok("/mnt/c/workspace/my_repositories/cpp_conference/unix_lab", 0);
    if (key == -1)
    {
        perror("ftok() failed: ");
        return -1;
    }

    int id = shmget(key, 1024 * 1024 * 1024, IPC_CREAT|IPC_EXCL|0600);
    // int id = shmget(key, 1024 * 1024 * 1024, IPC_CREAT|0600);
    if (id == -1)
    {
        perror("shmget() failed: ");
        return -1;
    }

    void * ptr = shmat(id, nullptr, 0);
    if (reinterpret_cast<long long>(ptr) == -1)
    {
        perror("shmat() failed: ");
        return -1;
    }
    cout << ptr << endl;

    getchar();

    if (shmdt(ptr) == -1)
    {
        perror("shmdt() failed: ");
        return -1;
    }

    if (shmctl(id, IPC_RMID, nullptr) == -1)
    {
        perror("shmctl() failed: ");
        return -1;
    }
    return 0;
}