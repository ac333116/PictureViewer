#include "threadpool.h"


ThreadPool::ThreadPool(int thread_num)
{
    stop = false;
    for (int i = 0; i < thread_num; i++)
    {
        threads.emplace_back([this](){
            while (1)
            {
                unique_lock<mutex>lock(mtx);
                condition.wait(lock, [this](){
                    return !tasks.empty() || stop;
                });
                if(tasks.empty() && stop)
                    return;
                function<void()>task(std::move(tasks.front()));
                tasks.pop();
                lock.unlock();
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        unique_lock<mutex>lock(mtx);
        stop = true;
    }
    condition.notify_all();
    for (auto& t : threads) {
        t.join();
    }
}

// template<class F, class...Args>
// void ThreadPool::addTask(F &&f, Args&&...args)
// {
//     function<void()>task = bind(forward<F>(f), forward<Args>(args)...);
//     {
//         unique_lock<mutex>lock(mtx);
//         tasks.emplace(std::move(task));
//     }
//     condition.notify_one();
// }










