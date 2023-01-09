#pragma once

#include "RefreshInfo.h"

#include "FilePath.h"
#include "Message.h"

class MessageLoadProject : public Message<MessageLoadProject> {
public:
  MessageLoadProject(const utility::file::FilePath& filePath_,
                     bool settingsChanged_ = false,
                     RefreshMode refreshMode_ = REFRESH_NONE,
                     bool shallowIndexingRequested_ = false)
      : projectSettingsFilePath(filePath_)
      , settingsChanged(settingsChanged_)
      , refreshMode(refreshMode_)
      , shallowIndexingRequested(shallowIndexingRequested_) {}

  static const std::string getStaticType() {
    return "MessageLoadProject";
  }

  virtual void print(std::wostream& os) const {
    os << projectSettingsFilePath.wstr();
    os << L", settingsChanged: " << std::boolalpha << settingsChanged;
    os << L", refreshMode: " << refreshMode;
  }

  const utility::file::FilePath projectSettingsFilePath;
  const bool settingsChanged;
  const RefreshMode refreshMode;
  const bool shallowIndexingRequested;
};
