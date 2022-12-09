#ifndef QT_PROJECT_WIZARD_CONTENT_CPP_STANDARD
#define QT_PROJECT_WIZARD_CONTENT_CPP_STANDARD

#include "QtProjectWizardContent.h"

class QComboBox;
class SourceGroupSettingsWithCppStandard;

class QtProjectWizardContentCppStandard : public QtProjectWizardContent {
  Q_OBJECT

 public:
  QtProjectWizardContentCppStandard(std::shared_ptr<SourceGroupSettingsWithCppStandard> sourceGroupSettings,
                                    QtProjectWizardWindow* window);

  // QtProjectWizardContent implementation
  virtual void populate(QGridLayout* layout, int& row) override;

  virtual void load() override;
  virtual void save() override;

 private:
  std::shared_ptr<SourceGroupSettingsWithCppStandard> m_sourceGroupSettings;

  QComboBox* m_standard;
};

#endif  // QT_PROJECT_WIZARD_CONTENT_CPP_STANDARD
