#ifndef PATH_DETECTOR_BASE_H
#define PATH_DETECTOR_BASE_H

#include <string>
#include <vector>

namespace utility::file {
class FilePath;
} // namespace class utility::file

class PathDetector
{
public:
	PathDetector(const std::string& name);
	virtual ~PathDetector() = default;

	std::string getName() const;
	std::vector<utility::file::FilePath> getPaths() const;
	bool isWorking() const;

protected:
	const std::string m_name;

private:
	virtual std::vector<utility::file::FilePath> doGetPaths() const = 0;
};

#endif	  // PATH_DETECTOR_BASE_H
