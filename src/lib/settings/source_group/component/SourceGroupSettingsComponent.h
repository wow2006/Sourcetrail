#pragma once

#include "SourceGroupSettingsBase.h"

namespace utility {
class ConfigManager;
}

class SourceGroupSettingsComponent : virtual public SourceGroupSettingsBase
{
public:
	virtual ~SourceGroupSettingsComponent() = default;

protected:
	virtual void load(const utility::ConfigManager* config, const std::string& key) = 0;
	virtual void save(utility::ConfigManager* config, const std::string& key) = 0;

	virtual bool equals(const SourceGroupSettingsBase* other) const = 0;
};