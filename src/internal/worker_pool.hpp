#pragma once

#include "task.hpp"
#include <atomic>
#include <image_processor/error.hpp>
#include <tbb/concurrent_hash_map.h>
#include <tbb/concurrent_queue.h>
#include <thread>
#include <vector>

namespace image_processor {

/**
 * @class WorkerPool
 * @brief Manages a pool of worker threads to process image tasks concurrently.
 *
 * This class represents a pool of worker threads designed to pick and execute image
 * processing tasks from a concurrent queue. The results and errors from the image
 * processing are stored in concurrent hash maps for further retrieval.
 */
// clang-format off
class WorkerPool {
public:
    /**
     * @brief Constructs the WorkerPool with references to a task queue, result storage, and error storage.
     * 
     * @param task_queue A concurrent queue from which worker threads will pick tasks for execution.
     * @param result_storage A concurrent hash map to store the results of successfully processed images.
     * @param error_storage A concurrent hash map to store errors encountered during image processing.
     */
    WorkerPool(tbb::concurrent_queue<Task>& task_queue,
               tbb::concurrent_hash_map<std::string, std::string>& result_storage,
               tbb::concurrent_hash_map<std::string, ImageProcessingError> error_storage);

    /**
     * @brief Destructor for the WorkerPool class.
     *
     * This destructor ensures that the worker pool is stopped properly 
     * before the object is destroyed. If the worker pool is still running 
     * upon object destruction, it will automatically trigger the Stop() 
     * function to gracefully shut down the worker threads.
     */
    ~WorkerPool();
 
    /**
     * @brief Starts all worker threads to begin processing tasks from the queue.
     * 
     * This function initializes and starts the worker threads to pick and process tasks. 
     * Each thread will run the HandleTaskQueue method.
     * 
     * @throw std::runtime_error if the worker threads are already running when attempting to start them.
     */
    void Start();

    /**
     * @brief Stops all worker threads gracefully.
     * 
     * This function signals the worker threads to stop processing and waits for their completion.
     * 
     * @throw std::runtime_error if the worker threads are already stopped when attempting to stop them.
     */
    void Stop();


private:
    /**
     * @brief Function executed by each worker thread to process tasks from t   he queue.
     * 
     * The worker thread will continually try to dequeue tasks from the task queue and process them 
     * until the pool is signaled to stop.
     */
    void HandleTaskQueue();

    /**
     * @brief Atomic flag indicating the running status of worker threads.
     */
    std::atomic<bool> is_running_;

    /**
     * @brief Vector to store the worker threads.
     */
    std::vector<std::thread> workers_;

    /**
     * @brief Reference to the task queue from which tasks are consumed.
     */
    tbb::concurrent_queue<Task>& task_queue_;

    /**
     * @brief Reference to the map where processed results are stored.
     */
    tbb::concurrent_hash_map<std::string, std::string>& result_storage_;

    /**
     * @brief Reference to the map where any processing errors are stored.
     */
    tbb::concurrent_hash_map<std::string, ImageProcessingError>& error_storage_;
};
// clang-format on

} // namespace image_processor
