/*
** EPITECH PROJECT, 2024
** ThreadPool.cpp
** File description:
** Handle threads logic in server
*/

#include "./includes/ThreadPool.hpp"
#include <iostream>

void ThreadPool::Initialize() {
    stop = false;
    unsigned int numThreads = std::thread::hardware_concurrency();
    for (unsigned int i = 0; i < numThreads; ++i) {
        workers.emplace_back([this]() { WorkerThread(); });
    }
}

void ThreadPool::AddTask(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        tasks.push(task);
    }
    threads_state.notify_one();
}

void ThreadPool::Shutdown() {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        stop = true;
    }
    threads_state.notify_all();
    for (auto& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void ThreadPool::WorkerThread() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            threads_state.wait(lock, [this]() { return stop || !tasks.empty(); });
            if (stop && tasks.empty()) return;
            task = std::move(tasks.front());
            tasks.pop();
        }
        task();
    }
}
