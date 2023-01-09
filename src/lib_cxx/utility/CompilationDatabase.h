#ifndef UTILITY_COMPILATION_DATABASE_H
#define UTILITY_COMPILATION_DATABASE_H

#include <string>
#include <vector>

#include "FilePath.h"

namespace utility
{
class CompilationDatabase
{
public:
	CompilationDatabase(const utility::file::FilePath& filePath);

	std::vector<utility::file::FilePath> getAllHeaderPaths() const;
	std::vector<utility::file::FilePath> getHeaderPaths() const;
	std::vector<utility::file::FilePath> getSystemHeaderPaths() const;
	std::vector<utility::file::FilePath> getFrameworkHeaderPaths() const;

private:
	void init();

	utility::file::FilePath m_filePath;
	std::vector<utility::file::FilePath> m_headers;
	std::vector<utility::file::FilePath> m_systemHeaders;
	std::vector<utility::file::FilePath> m_frameworkHeaders;
};

}	 // namespace utility

#endif	  // UTILITY_COMPILATION_DATABASE_H
