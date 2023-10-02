#pragma once

namespace image_processor {

/**
 * @enum ImageProcessingError
 * @brief Enumerates potential errors that can arise during image processing.
 *
 * This enum provides a way to indicate and categorize various errors
 * that can occur during image processing operations, ranging from issues
 * with the input image itself to problems encountered during the processing phase.
 */

// clang-format off
enum class ImageProcessingError {
  kNoError,            /**< Indicates that there is no error associated with the image processing task. */
  kInvalidImageFormat, /**< The provided image is not in a supported format (e.g., not JPG, JPEG, or PNG). */
  kImageNotFound,      /**< The specified image could not be found. */
  kImageInaccessible,  /**< The library was unable to access the provided image, possibly due to permissions or other restrictions. */
  kImageSaveError,     /**< The image was processed successfully but encountered an issue when attempting to save the result. */
  kInvalidFilter,      /**< The provided filter for processing is ill-formed or not recognized. */
};
// clang-format on

} // namespace image_processor
