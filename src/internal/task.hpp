#pragma once

#include <string>
#include <vector>

#include <image_processor/filter.hpp>

namespace image_processor {

/**
 * @struct Task
 * @brief Represents an image processing task.
 *
 * A Task consists of a unique identifier, a path to the source image,
 * and an ordered list of operations (filters) to be applied to the image.
 */
struct Task {

  /**
   * @brief A unique identifier for each task.
   */
  std::string id;

  /**
   * @brief The path to the image that needs processing.
   */
  std::string image;

  /**
   * @brief An ordered list of operations (filters) to apply to the image.
   */
  std::vector<Filter> operations;
};

} // namespace image_processor
