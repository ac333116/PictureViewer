#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>
using namespace std;

class ThreadPool {
public:
    //构造函数
    ThreadPool(int thread_num);

    //析构函数
    ~ThreadPool();

    //添加任务队列
    template<class F,class...Args>
    void addTask(F &&f , Args&&...args)
    {
        function<void()>task = bind(forward<F>(f), forward<Args>(args)...);
        {
            unique_lock<mutex>lock(mtx);
            tasks.emplace(std::move(task));
        }
        condition.notify_one();
    }

private:
    //vector线程组
    vector<thread>threads;
    //创建任务队列
    queue<function<void()>>tasks;

    mutex mtx;
    condition_variable condition;
    bool stop;
};

#endif // THREADPOOL_H
