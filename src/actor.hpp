#pragma once

#include <cstdio>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <functional>
#include <assert.h>
#include <vector>
#include <future>
#include <tuple>
#include <memory>
#include <any>

class WorkerThread
{
public:
    
    WorkerThread()
    {
        threadLooping = new std::atomic_bool(true);
        workQueueEmptyMutex.lock();
        thr = std::thread(&WorkerThread::workerThreadLoop, this);
    }

    ~WorkerThread()
    {
        threadLooping->store(false);
        workQueueEmptyMutex.unlock();
        if(thr.joinable()) thr.join();
    }

    std::future<std::any> pushWork(std::packaged_task<std::any()>&& func)
    {
        workQueueMutex.lock();
        auto ret = func.get_future();
        workQueue.push(std::move(func));
        workQueueEmptyMutex.unlock();
        workQueueMutex.unlock();

        return ret;
    }

private:
    
    std::queue<std::packaged_task<std::any()>> workQueue;
    std::mutex workQueueMutex;      // atomizes workQueue
    std::mutex workQueueEmptyMutex; // blocks thread until work is available. reduces CPU usage.

    std::thread thr;
    std::atomic_bool* threadLooping;

    void workerThreadLoop()
    {
        while(threadLooping->load())
        {
            {
                workQueueEmptyMutex.lock();
                std::lock_guard<std::mutex> workQueueGuard(workQueueMutex);
                workQueueEmptyMutex.unlock();

                for(
                    auto work = &workQueue.front(); 
                    !workQueue.empty(); 
                    workQueue.pop(), 
                    work = &workQueue.front()
                ){
                    (*work)();
                }
                workQueueEmptyMutex.lock();
            }
            std::this_thread::yield();
        }

        delete threadLooping;
    }
};

template<typename RetT>
struct ActorReturn
{
    ActorReturn<RetT>(std::future<std::any>&& nRet) : ret{std::move(nRet)} {};

    std::future<std::any> ret;

    RetT get()
    {return std::any_cast<RetT>(ret.get());}
};

template<typename T>
class Actor
{
public:
    Actor<T>(T* newSelf) : self{newSelf}, thr{new WorkerThread{}} {} 

    ~Actor<T>() = default;

    template<typename ... ArgT, typename RetT>
    ActorReturn<RetT> call(RetT (T::*mthd) (ArgT...), ArgT ... args)
    {
        std::packaged_task<std::any()> mthdPacked{[=]() {return std::any(((*self).*mthd)(args...));}};
        return ActorReturn<RetT>{thr->pushWork(std::move(mthdPacked))};
    }

    template<typename ... ArgT>
    std::future<std::any> call(void (T::*mthd) (ArgT...), ArgT ... args)
    {
        std::packaged_task<std::any()> mthdPacked{[=]() {
            ((*self).*mthd)(args...);
            return std::any();
        }};
        return thr->pushWork(std::move(mthdPacked));
    }

private:
    // as long as shared_ptr's controller is atomic, 
    // there should be little issue. self is only to be
    // touched by thr, and thr's public functions should
    // be atomic.
    std::shared_ptr<T> self;
    std::shared_ptr<WorkerThread> thr;
};

