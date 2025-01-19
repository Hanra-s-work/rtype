#include <iostream>
#include <thread>
#include <functional>
#include <memory>
#include <atomic>
#include <chrono>

class Worker {
    public:
    Worker() : running(true)
    {
        std::cout << "Worker created!" << std::endl;
    }

    ~Worker()
    {
        stop();
        if (workerThread.joinable()) {
            workerThread.join();
        }
    }

    // Start the work in a separate thread
    void start()
    {
        workerThread = std::thread([this]() {
            while (running) {
                // Simulate some work
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "Worker is working..." << std::endl;
            }
            });
    }

    // Stop the worker thread
    void stop()
    {
        running = false;
    }

    // Example function to be called from Controller
    void doWork()
    {
        std::cout << "Worker is doing some work!" << std::endl;
    }

    private:
    std::thread workerThread;
    std::atomic<bool> running;
};

class Controller {
    public:
    Controller()
    {
        worker = std::make_shared<Worker>();
    }

    void startWorker()
    {
        worker->start();
    }

    void stopWorker()
    {
        worker->stop();
    }

    void callWorkerFunction()
    {
        worker->doWork();
    }

    // Destructor ensures cleanup
    ~Controller()
    {
        stopWorker();
    }

    private:
    std::shared_ptr<Worker> worker;
};

int main()
{
    Controller controller;

    // Start the worker in a separate thread
    controller.startWorker();

    // Give it some time to "work"
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Call a method in the worker class from the controller
    controller.callWorkerFunction();

    // Stop the worker
    controller.stopWorker();

    // Give it time to clean up
    std::this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}
