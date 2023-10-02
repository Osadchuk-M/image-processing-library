#pragma once

#include <filesystem>
#include <image_processor/error.hpp>
#include <image_processor/filter.hpp>
#include <opencv2/core.hpp>
#include <vector>

namespace image_processor {

/**
 * @class ImageProcessor
 * @brief A class responsible for processing images based on a series of filter
 * operations.
 *
 * The ImageProcessor class takes in an original image path and a series of filter
 * operations to apply on the image. After processing, the resultant image is saved in the
 * specified directory.
 */
class ImageProcessor {
public:
  /**
   * @brief Constructor for the ImageProcessor class.
   *
   * @param original_image_path Path to the original image to be processed.
   * @param operations List of filter operations to apply on the image.
   * @param processed_images_path Path to save the processed image.
   */
  ImageProcessor(const std::string& original_image_path,
                 const std::vector<Filter>& operations,
                 const std::string& processed_images_path);

  /**
   * @brief Processes the image based on the provided filter operations.
   *
   * @return ImageProcessingError status indicating success or the nature of any error.
   */
  ImageProcessingError ProcessImage();

  /**
   * @brief Retrieves the path where the processed image is saved.
   *
   * @return std::string containing the path to the processed image.
   */
  std::string GetResultImagePath() const;

private:
  /**
   * @brief Validates the provided filter operations and image path.
   *
   * @return ImageProcessingError status indicating success or the nature of any error.
   */
  ImageProcessingError ValidateArguments() const;

  /**
   * @brief Applies the specified filter operations on the image.
   *
   * @return ImageProcessingError status indicating success or the nature of any error.
   */
  ImageProcessingError ApplyFilters();

  /**
   * @brief Saves the processed image to the specified path.
   *
   * @return ImageProcessingError status indicating success or the nature of any error.
   */
  ImageProcessingError SaveImage();

private:
  /**
   * @brief Path to the original image to be processed.
   */
  const std::string& original_image_path_;

  /**
   * @brief List of filter operations to apply on the image.
   */
  const std::vector<Filter>& operations_;

  /**
   * @brief Directory path to save the processed image.
   */
  const std::string& processed_images_path_;

  /**
   * @brief Path where the processed image is saved after processing.
   */
  std::filesystem::path result_image_path_;

  /**
   * @brief OpenCV matrix storing the image data.
   */
  cv::Mat image_;
};

} // namespace image_processor
