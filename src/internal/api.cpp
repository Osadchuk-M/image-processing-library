#include <image_processor/api.hpp>

#include "task.hpp"
#include "utils.hpp"
#include "worker_pool.hpp"

namespace image_processor {

static tbb::concurrent_queue<Task> task_queue;
static tbb::concurrent_hash_map<std::string, std::string> result_storage;
static tbb::concurrent_hash_map<std::string, ImageProcessingError> error_storage;
static WorkerPool worker_pool(task_queue, result_storage, error_storage);

void Initialize() {
  result_storage.rehash(1048576);
  worker_pool.Start();
}

std::string SubmitTask(std::string image, std::vector<Filter> operations) {

  std::string id = utils::GenerateUUID();
  task_queue.push({id, image, operations});
  return id;
}

bool IsTaskComplete(const std::string& task_id) {
  tbb::concurrent_hash_map<std::string, std::string>::const_accessor accessor;
  return result_storage.find(accessor, task_id);
}

ImageProcessingError GetError(const std::string& task_id) {
  tbb::concurrent_hash_map<std::string, ImageProcessingError>::accessor accessor;
  if (error_storage.find(accessor, task_id)) {
    ImageProcessingError error = accessor->second;
    error_storage.erase(accessor);
    return error;
  }

  return ImageProcessingError::kNoError;
}

std::string GetResult(const std::string& task_id) {
  tbb::concurrent_hash_map<std::string, std::string>::accessor accessor;
  if (result_storage.find(accessor, task_id)) {
    std::string result = accessor->second;
    result_storage.erase(accessor);
    return result;
  }

  return {};
}

void Shutdown() { worker_pool.Stop(); }

} // namespace image_processor