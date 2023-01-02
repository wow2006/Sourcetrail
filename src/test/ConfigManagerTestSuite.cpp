#include "catch.hpp"

#include "ConfigManager.h"
#include "TextAccess.h"

namespace {

std::shared_ptr<TextAccess> getConfigTextAccess() {
  std::string text =
      "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n"
      "<config>\n"
      "	<path>\n"
      "		<to>\n"
      "			<bool_that_is_false>0</bool_that_is_false>\n"
      "			<bool_that_is_true>1</bool_that_is_true>\n"
      "			<single_value>42</single_value>\n"
      "		</to>\n"
      "	</path>\n"
      "	<paths>\n"
      "		<nopath>4</nopath>\n"
      "		<path>2</path>\n"
      "		<path>5</path>\n"
      "		<path>8</path>\n"
      "	</paths>\n"
      "</config>\n";
  return TextAccess::createFromString(text);
}

}    // namespace

TEST_CASE("config manager returns true when key is found", "[lib]") {
  auto config = utility::ConfigManager::createAndLoad(getConfigTextAccess());

  float value = {};
  bool success = config->getValue("path/to/single_value", value);

  REQUIRE(success);
}


TEST_CASE("config manager returns false when key is not found", "[lib]") {
  auto config = utility::ConfigManager::createAndLoad(getConfigTextAccess());

  float value = {};
  bool success = config->getValue("path/to/nowhere", value);

  REQUIRE(!success);
}


TEST_CASE("config manager returns correct string for key", "[lib]") {
  auto config = utility::ConfigManager::createAndLoad(getConfigTextAccess());

  std::wstring value;
  config->getValue("path/to/single_value", value);

  REQUIRE(L"42" == value);
}


TEST_CASE("config manager returns correct float for key", "[lib]") {
  constexpr auto FloatValue = 42.0F;
  auto config = utility::ConfigManager::createAndLoad(getConfigTextAccess());

  float value = {};
  config->getValue("path/to/single_value", value);

  REQUIRE(value == Approx(FloatValue));
}

TEST_CASE("config manager returns correct bool for key if value is true", "[lib]") {
  auto config = utility::ConfigManager::createAndLoad(getConfigTextAccess());

  float value = {};
  bool success(config->getValue("path/to/bool_that_is_true", value));

  REQUIRE(success);
  REQUIRE(value);
}

TEST_CASE("config manager returns correct bool for key if value is false", "[lib]") {
  auto config = utility::ConfigManager::createAndLoad(getConfigTextAccess());

  float value = {};
  bool success(config->getValue("path/to/bool_that_is_false", value));

  REQUIRE(success);
  REQUIRE(value == Approx(0));
}

TEST_CASE("config manager adds new key when empty", "[lib]") {
  auto config = utility::ConfigManager::createEmpty();

  config->setValue("path/to/true_bool", true);

  bool value = false;
  bool success(config->getValue("path/to/true_bool", value));

  REQUIRE(success);
  REQUIRE(value);
}

TEST_CASE("config manager adds new key when not empty", "[lib]") {
  auto config = utility::ConfigManager::createAndLoad(getConfigTextAccess());

  config->setValue("path/to/true_bool", true);

  bool value = false;
  bool success(config->getValue("path/to/true_bool", value));

  REQUIRE(success);
  REQUIRE(value);
}

TEST_CASE("config manager returns correct list for key", "[lib]") {
  auto config = utility::ConfigManager::createAndLoad(getConfigTextAccess());

  std::vector<int> values;

  bool success(config->getValues("paths/path", values));

  REQUIRE(success);
  REQUIRE(values.size() == 3);
  REQUIRE(values[0] == 2);
  REQUIRE(values[1] == 5);
  REQUIRE(values[2] == 8);
}

TEST_CASE("config manager save and load configuration and compare", "[lib]") {
  const FilePath path(L"data/ConfigManagerTestSuite/temp.xml");

  auto config = utility::ConfigManager::createAndLoad(getConfigTextAccess());
  config->save(path.str());
  std::shared_ptr<utility::ConfigManager> config2 = utility::ConfigManager::createAndLoad(
      TextAccess::createFromFile(path));
  REQUIRE(config->toString() == config2->toString());
}

TEST_CASE("config manager loads special character", "[lib]") {
  auto config = utility::ConfigManager::createAndLoad(
      TextAccess::createFromFile(FilePath(L"data/ConfigManagerTestSuite/test_data.xml")));
  std::wstring loadedSpecialCharacter;
  config->getValue("path/to/special_character", loadedSpecialCharacter);

  REQUIRE(loadedSpecialCharacter.size() == 1);
  REQUIRE(loadedSpecialCharacter[0] == wchar_t(252));
  ;    // special character needs to be encoded as ASCII code because
       // otherwise python and cxx compiler may be complaining
}

TEST_CASE("config manager save and load special character and compare", "[lib]") {
  constexpr auto SpecialCharacter = static_cast<wchar_t>(252);
  const FilePath path(L"data/ConfigManagerTestSuite/temp.xml");
  std::wstring specialCharacter;
  specialCharacter.push_back(SpecialCharacter);

  auto config = utility::ConfigManager::createEmpty();
  config->setValue("path/to/special_character", specialCharacter);
  config->save(path.str());

  std::shared_ptr<utility::ConfigManager> config2 = utility::ConfigManager::createAndLoad(
      TextAccess::createFromFile(path));
  REQUIRE(config->toString() == config2->toString());
}
