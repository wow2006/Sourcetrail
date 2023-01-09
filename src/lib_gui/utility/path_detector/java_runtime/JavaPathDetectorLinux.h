#ifndef JAVA_PATH_DETECTOR_LINUX_H
#define JAVA_PATH_DETECTOR_LINUX_H

#include "JavaPathDetector.h"

class JavaPathDetectorLinux: public JavaPathDetector
{
public:
	JavaPathDetectorLinux(const std::string javaVersion);

private:
	std::vector<utility::file::FilePath> doGetPaths() const override;
	utility::file::FilePath getJavaInPath() const;
	utility::file::FilePath readLink(const utility::file::FilePath& path) const;
	utility::file::FilePath getJavaInJavaHome() const;
	bool checkVersion(const utility::file::FilePath& path) const;

	utility::file::FilePath getFilePathRelativeToJavaExecutable(utility::file::FilePath& javaExecutablePath) const;
};

#endif	  // JAVA_PATH_DETECTOR_LINUX_H
