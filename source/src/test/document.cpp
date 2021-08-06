#include "fvtt/document.hpp"

#include <catch2/catch.hpp>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

#include <stdexcept>

using Catch::Matchers::Equals;

SCENARIO("the raw content of a document can be accessed", "[core][document]")
{
  GIVEN("A default constructed document")
  {
    auto document = fvtt::document{};

    WHEN("the raw content is retrieved")
    {
      auto raw_content = document.raw_content();

      THEN("it is equal to the empty string")
      {
        CHECK_THAT(raw_content, Equals(""));
      }
    }
  }

  GIVEN("an empty JSON object is assigned to a default constructed document")
  {
    auto document = fvtt::document{};
    auto json = nlohmann::json::object();
    document = json;

    WHEN("the raw content is retrieved")
    {
      auto raw_content = document.raw_content();

      THEN("it is equal to the empty string")
      {
        CHECK_THAT(raw_content, Equals(""));
      }
    }
  }
}

SCENARIO("JSON objects can be assigned to a document", "[core][document]")
{
  GIVEN("A default constructed document")
  {
    auto document = fvtt::document{};

    THEN("no exception is thrown")
    {
      WHEN("an empty JSON object is assigned")
      {
        auto json = nlohmann::json::object();
        CHECK_NOTHROW(document = json);
      }
    }

    THEN("std::invalid argument is thrown")
    {
      WHEN("an empty JSON array is assigned")
      {
        auto json = nlohmann::json::array();
        CHECK_THROWS_AS(document = json, std::invalid_argument);
      }
    }

    THEN("std::invalid argument is thrown")
    {
      WHEN("a non-empty JSON array is assigned")
      {
        auto json = nlohmann::json::array({1, 2, 3});
        CHECK_THROWS_AS(document = json, std::invalid_argument);
      }
    }
  }
}

SCENARIO("the ID of a document can be accessed", "[core][document]")
{
  GIVEN("a default constructed document")
  {
    auto document = fvtt::document{};

    WHEN("when the ID is retrieved")
    {
      auto id = document.id();

      THEN("it is equal to the empty string")
      {
        CHECK_THAT(id, Equals(""));
      }
    }
  }
}