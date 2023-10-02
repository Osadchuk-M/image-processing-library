#include "worker_pool.hpp"
#include "image_processor.hpp"

#include <stdexcept>
#include <thread>

namespace image_processor {

WorkerPool::WorkerPool(
    tbb::concurrent_queue<Task>& task_queue,
    tbb::concurrent_hash_map<std::string, std::string>& result_storage,
    tbb::concurrent_hash_map<std::string, ImageProcessingError> error_storage)
    : is_running_(false), task_queue_(task_queue), result_storage_(result_storage),
      error_storage_(error_storage) {}

void WorkerPool::HandleTaskQueue() {
  while (is_running_.load()) {
    Task task;
    if (!task_queue_.try_pop(task)) {
      std::this_thread::yield();
      continue;
    }

    ImageProcessor processor(task.image, task.operations, "~/processed_images");
    const auto error_code = processor.ProcessImage();
    if (error_code != ImageProcessingError::kNoError) {
      error_storage_.insert({task.id, error_code});
      continue;
    }

    result_storage_.insert({task.id, processor.GetResultImagePath()});
  }
}

void WorkerPool::Start() {
  bool expected = false;
  if (!is_running_.compare_exchange_strong(expected, true)) {
    throw std::runtime_error("Worker threads are already running.");
  }

  for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i) {
    workers_.emplace_back(&WorkerPool::HandleTaskQueue, this);
  }
}

void WorkerPool::Stop() {
  bool expected = true;
  if (!is_running_.compare_exchange_strong(expected, false)) {
    throw std::runtime_error("Worker threads are already stopped.");
  }

  for (auto& worker : workers_) {
    if (worker.joinable()) {
      worker.join();
    }
  }

  workers_.clear();
}

WorkerPool::~WorkerPool() {
  if (is_running_.load()) {
    Stop();
  }
}

} // namespace image_processor