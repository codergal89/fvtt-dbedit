#ifndef FVTTDB_DOCUMENT_HPP
#define FVTTDB_DOCUMENT_HPP

#include <nlohmann/json_fwd.hpp>

#include <string>

namespace fvtt
{

  struct document
  {
    /**
     * @brief Retrieve the raw (JSON serialized) content
     *
     * @return std::string A string containing the content of the document serialized into JSON
     */
    auto virtual raw_content() const -> std::string;

    /**
     * @brief Replace the current content with the one from a JSON object
     *
     * @param[in] object A json object containing a valid document
     * @return document& a reference to this document
     */
    auto virtual operator=(nlohmann::json & object) -> document &;
  };

}  // namespace fvtt

#endif