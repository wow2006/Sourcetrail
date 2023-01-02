#include "utilityXml.h"

#include "tinyxml.h"

#include "logging.h"
#include "TextAccess.h"

namespace utility {

std::vector<std::string> getValuesOfAllXmlElementsOnPath(const std::shared_ptr<TextAccess>& textAccess,
                                                         const std::vector<std::string>& tags) {
  std::vector<std::string> values;

  const auto text = textAccess->getText();

  TiXmlDocument doc;
  const char* pTest = doc.Parse(text.c_str(), nullptr, TIXML_ENCODING_LEGACY);
  if(pTest != nullptr) {
    TiXmlHandle docHandle(&doc);
    std::vector<std::pair<TiXmlElement*, size_t>> traversalStates;
    traversalStates.emplace_back(docHandle.ToNode()->FirstChildElement(), 0);

    while(!traversalStates.empty()) {
      auto* currentElement = traversalStates.back().first;
      const size_t currentIndex = traversalStates.back().second;
      traversalStates.pop_back();

      if(currentElement != nullptr && currentElement->Value() == tags[currentIndex]) {
        if(currentIndex < tags.size() - 1) {
          auto* nextElement = currentElement->FirstChildElement();

          while(nextElement != nullptr) {
            traversalStates.emplace_back(nextElement, currentIndex + 1);
            nextElement = nextElement->NextSiblingElement();
          }
        } else {
          if(currentElement->FirstChild() != nullptr &&
             currentElement->FirstChild() == currentElement->LastChild() &&
             currentElement->FirstChild()->ToText() != nullptr) {
            values.emplace_back(currentElement->FirstChild()->ToText()->Value());
          }
        }
      }
    }
  } else {
    if(doc.Error()) {
      LOG_ERROR(std::string("Error while parsing XML: ") + doc.ErrorDesc() + " (in line " +
                std::to_string(doc.ErrorRow()) + ": \"" + textAccess->getLine(static_cast<uint32_t>(doc.ErrorRow())) +
                "\")");
    } else {
      LOG_ERROR("Unable to load file.");
    }
  }
  return values;
}

std::vector<TiXmlElement*> getAllXmlTagsByName(TiXmlElement* root, const std::string& tag) {
  std::vector<TiXmlElement*> nodes;

  auto* element = root;

  while(element != nullptr) {
    std::string value = element->Value();

    if(value == tag) {
      nodes.push_back(element);
    }

    if(element->FirstChildElement() != nullptr) {
      element = element->FirstChildElement();
    } else if(element->NextSiblingElement() != nullptr) {
      element = element->NextSiblingElement();
    } else {
      if(element == nullptr) {
      }

      while(element->Parent()->ToElement() != nullptr &&
            element->Parent()->NextSiblingElement() == nullptr) {
        auto* newElement = element->Parent()->ToElement();

        if(newElement == nullptr) {
        }

        element = newElement;
      }
      if(element->Parent() != nullptr && element->Parent()->NextSiblingElement() != nullptr) {
        element = element->Parent()->NextSiblingElement();
      } else {
        break;
      }
    }
  }

  return nodes;
}
}    // namespace utility