#pragma once


class TextAccess;
class TiXmlElement;

namespace utility {

std::vector<std::string> getValuesOfAllXmlElementsOnPath(const std::shared_ptr<TextAccess>& textAccess,
                                                         const std::vector<std::string>& tags);

std::vector<TiXmlElement*> getAllXmlTagsByName(TiXmlElement* root, const std::string& tag);

}    // namespace utility