#pragma once

#include <image_processor/error.hpp>
#include <image_processor/filter.hpp>
#include <string>
#include <vector>

namespace image_processor {

/**
 * @brief Initializes the image processor.
 *
 * This function must be called before using any other functionality of the image
 * processor.
 */
void Initialize();

/**
 * @brief Submit a new image processing task.
 *
 * @param image Path to the image to be processed.
 * @param operations List of filters to be applied on the image.
 * @return A unique task ID representing the submitted task.
 */
std::string SubmitTask(std::string image, std::vector<Filter> operations);

/**
 * @brief Check if a processing task is complete.
 *
 * @param task_id The ID of the task to check.
 * @return true if the task with the given ID is complete, false otherwise.
 */
bool IsTaskComplete(const std::string& task_id);

/**
 * @brief Retrieve the error associated with a processing task.
 *
 * If the task completed without any errors, ImageProcessingError::kNoError will be
 * returned. Once retrieved, the error information for the task will be removed from the
 * internal storage.
 *
 * @param task_id The ID of the task to retrieve the error for.
 * @return The error associated with the task or ImageProcessingError::kNoError if there
 * was no error.
 */
ImageProcessingError GetError(const std::string& task_id);

/**
 * @brief Retrieve the result of a processing task.
 *
 * Once retrieved, the result for the task will be removed from the internal storage.
 *
 * @param task_id The ID of the task to retrieve the result for.
 * @return Path to the processed image or an empty string if the task is not complete.
 */
std::string GetResult(const std::string& task_id);

/**
 * @brief Shut down the image processor.
 *
 * This function cleans up resources associated with the image processor and should be
 * called when the image processing functionality is no longer needed.
 */
void Shutdown();

} // namespace image_processor
