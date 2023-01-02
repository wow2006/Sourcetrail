#pragma once

#include <QWidget>

#include "QtThreadedFunctor.h"
#include "StatusView.h"

class QBoxLayout;
class QCheckBox;
class QStandardItemModel;
class QtTable;

class QtStatusView
    : public QWidget
    , public StatusView {
  Q_OBJECT // NOLINT(readability-identifier-length)

public:
  explicit QtStatusView(ViewLayout* viewLayout);

  ~QtStatusView() override;

  // View implementation
  void createWidgetWrapper() override;

  void refreshView() override;

  // Status View Implementation
  void clear() override;

  void addStatus(const std::vector<utility::Status>& status) override;

private:
  enum STATUSVIEW_COLUMN {
    TYPE = 0,
    STATUS = 1,
  };

  QCheckBox* createFilterCheckbox(const QString& name, QBoxLayout* layout, bool checked = false);

  QtThreadedLambdaFunctor m_onQtThread;

  QtTable* m_table;
  QStandardItemModel* m_model;

  std::vector<utility::Status> m_status;

  QCheckBox* m_showErrors;
  QCheckBox* m_showInfo;
};
