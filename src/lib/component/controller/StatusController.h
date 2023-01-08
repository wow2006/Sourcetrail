#pragma once

#include "Controller.h"

#include "MessageClearStatusView.h"
#include "MessageListener.h"
#include "MessageShowStatus.h"
#include "MessageStatus.h"
#include "MessageStatusFilterChanged.h"
#include "Status.h"

class StatusView;
class StorageAccess;

class StatusController
    : public Controller
    , public MessageListener<MessageClearStatusView>
    , public MessageListener<MessageShowStatus>
    , public MessageListener<MessageStatus>
    , public MessageListener<MessageStatusFilterChanged> {
public:
  StatusController();

  ~StatusController() override;

private:
  [[nodiscard]] StatusView* getView() const;

  void clear() override;

  void handleMessage(MessageClearStatusView* message) override;
  void handleMessage(MessageShowStatus* message) override;
  void handleMessage(MessageStatus* message) override;
  void handleMessage(MessageStatusFilterChanged* message) override;

  void addStatus(const std::vector<utility::Status>& status);

  std::vector<utility::Status> m_status;
  utility::StatusFilter m_statusFilter;
};
