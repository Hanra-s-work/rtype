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
    }

    // Worker does its work in a loop
    void doWork()
    {
        while (running) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "Worker is working..." << std::endl;
        }
    }

    void stop()
    {
        running = false;
    }

    private:
    std::atomic<bool> running;
};

class Controller {
    public:
    Controller() : worker(std::make_shared<Worker>()) {}

    // Start the worker in a separate thread, but manage the thread in the controller
    void startWorker()
    {
        workerThread = std::thread(&Worker::doWork, worker);
    }

    // Stop the worker and join the thread
    void stopWorker()
    {
        worker->stop();
        if (workerThread.joinable()) {
            workerThread.join();
        }
    }

    // Call a function in Worker (we can expose any Worker functions here)
    void callWorkerFunction()
    {
        std::cout << "Controller calling Worker function..." << std::endl;
        // This could call any worker function, for example:
        worker->stop();
    }

    ~Controller()
    {
        stopWorker();
    }

    private:
    std::shared_ptr<Worker> worker;
    std::thread workerThread;
};

int main()
{
    Controller controller;

    // Start the worker in a separate thread
    controller.startWorker();

    for (unsigned int index = 0; index < 50; index++) {
        std::cout << "Main function of the main thread, loop, index: " << index << std::endl;
        std::cout << "Sleeping for 200 milliseconds" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    // Controller calls a method in the Worker class
    controller.callWorkerFunction();

    // Stop the worker
    std::cout << "Main function of the main thread, stopping child thread via the controller class stop worker" << std::endl;
    controller.stopWorker();

    return 0;
}
