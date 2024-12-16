/*
** EPITECH PROJECT, 2024
** ThreadPool.hpp
** File description:
** Handle threads logic in server
*/

#ifndef THREAD_POOL_H
    #define THREAD_POOL_H

    #include <functional>
    #include <vector>
    #include <thread>
    #include <queue>
    #include <mutex>
    #include <condition_variable>

    class ThreadPool {
        public:
            void Initialize();
            void AddTask(std::function<void()> task);
            void Shutdown();

        private:
            std::vector<std::thread> workers;
            std::queue<std::function<void()>> tasks;
            std::mutex queueMutex;
            std::condition_variable threads_state;
            bool stop = false;

            void WorkerThread();
    };

#endif // THREAD_POOL_H
