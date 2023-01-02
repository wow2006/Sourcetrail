#include "StatusController.h"

#include "ApplicationSettings.h"
#include "StatusView.h"
#include "utility.h"

StatusController::StatusController() {
  m_statusFilter = ApplicationSettings::getInstance()->getStatusFilter();
}

StatusController::~StatusController() = default;

StatusView* StatusController::getView() const {
  return Controller::getView<StatusView>();
}

void StatusController::clear() {}

void StatusController::handleMessage(MessageClearStatusView* /*message*/) {
  m_status.clear();
  getView()->clear();
}

void StatusController::handleMessage(MessageShowStatus* /*message*/) {
  getView()->showDockWidget();
}

void StatusController::handleMessage(MessageStatus* message) {
  if(message->status().empty()) {
    return;
  }

  std::vector<utility::Status> stati;

  for(const auto& status : message->stati()) {
    stati.emplace_back(status, message->isError);
  }

  utility::append(m_status, stati);

  addStatus(stati);
}

void StatusController::handleMessage(MessageStatusFilterChanged* message) {
  m_statusFilter = message->statusFilter;

  getView()->clear();
  addStatus(m_status);

  ApplicationSettings* settings = ApplicationSettings::getInstance().get();
  settings->setStatusFilter(m_statusFilter);
  settings->save();
}

void StatusController::addStatus(const std::vector<utility::Status>& status) {
  std::vector<utility::Status> filteredStatus;

  for(const auto& stat : status) {
    if(stat.type & m_statusFilter) {
      filteredStatus.push_back(stat);
    }
  }

  getView()->addStatus(filteredStatus);
}
