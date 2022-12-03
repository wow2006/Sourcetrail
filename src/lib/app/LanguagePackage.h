#pragma once

#include <memory>
#include <vector>

class IndexerBase;

class LanguagePackage
{
public:
	virtual ~LanguagePackage() = default;
	virtual std::vector<std::shared_ptr<IndexerBase>> instantiateSupportedIndexers() const = 0;
};

