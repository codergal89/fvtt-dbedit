#include "fvtt/document.hpp"

#include <nlohmann/json.hpp>

#include <stdexcept>
#include <string>

namespace fvtt
{
  auto document::raw_content() const -> std::string
  {
    return "";
  }

  auto document::operator=(nlohmann::json & object) -> document &
  {
    if (object.is_array())
    {
      throw std::invalid_argument("Documents can not be assigned from arrays");
    }

    static_cast<void>(object);
    return *this;
  }
}  // namespace fvtt
