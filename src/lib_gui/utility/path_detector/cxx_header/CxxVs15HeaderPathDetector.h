#ifndef CXX_VS_15_HEADER_PATH_DETECTOR_H
#define CXX_VS_15_HEADER_PATH_DETECTOR_H

#include "ApplicationArchitectureType.h"
#include "PathDetector.h"

class CxxVs15HeaderPathDetector: public PathDetector
{
public:
	CxxVs15HeaderPathDetector();

private:
	std::vector<utility::file::FilePath> doGetPaths() const override;
};

#endif	  // CXX_VS_15_HEADER_PATH_DETECTOR_H
