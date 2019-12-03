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
        thr = std::thread(&WorkerThread::workerThreadLoop, this);
    }

    ~WorkerThread()
    {
        threadLooping->store(false);
        if(thr.joinable()) thr.join();
    }

    std::future<std::any> pushWork(std::packaged_task<std::any()>&& func)
    {
        std::lock_guard<std::mutex> workQueueGuard(workQueueMutex);
        auto ret = func.get_future();
        workQueue.push(std::move(func));
        return ret;
    }

private:
    
    std::queue<std::packaged_task<std::any()>> workQueue;
    std::mutex workQueueMutex;

    std::thread thr;
    std::atomic_bool* threadLooping;

    void workerThreadLoop()
    {
        while(threadLooping->load())
        {
            {
                std::lock_guard<std::mutex> workQueueGuard{workQueueMutex};

                for(
                    auto work = &workQueue.front(); 
                    !workQueue.empty(); 
                    workQueue.pop(), 
                    work = &workQueue.front()
                ){
                    (*work)();
                }
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
    Actor<T>(T&& newSelf) : self{newSelf} {} 

    ~Actor<T>() = default;

    template<typename ... ArgT, typename RetT>
    ActorReturn<RetT> call(RetT (T::*mthd) (ArgT...), ArgT ... args)
    {
        std::packaged_task<std::any()> mthdPacked{[=]() {return std::any((self.*mthd)(args...));}};
        return ActorReturn<RetT>{thr.pushWork(std::move(mthdPacked))};
    }

    template<typename ... ArgT>
    std::future<std::any> call(void (T::*mthd) (ArgT...), ArgT ... args)
    {
        std::packaged_task<std::any()> mthdPacked{[=]() {
            (self.*mthd)(args...);
            return std::any();
        }};
        return thr.pushWork(std::move(mthdPacked));
    }

private:
    T self;
    WorkerThread thr;
};

