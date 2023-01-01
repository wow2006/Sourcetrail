#include "QtThreadedFunctor.h"


void QtThreadedFunctorHelper::execute() {
  std::function<void(void)> callback = m_callback;
  m_freeCallbacks.release();
  callback();
}

QtThreadedFunctorHelper::QtThreadedFunctorHelper(): m_freeCallbacks(1) {
  QObject::connect(this,
                   &QtThreadedFunctorHelper::signalExecution,
                   this,
                   &QtThreadedFunctorHelper::execute,
                   Qt::QueuedConnection);
}

void QtThreadedFunctorHelper::operator()(std::function<void(void)> callback) {
  if(QThread::currentThread() == this->thread()) {
    callback();
    return;
  }

  m_freeCallbacks.acquire();
  m_callback = std::move(callback);
  emit signalExecution();
}

void QtThreadedFunctorHelper::handleMessage(MessageWindowClosed* /*message*/) {
  // The QT thread probably won't relay signals anymore. So this stops other
  // threads from getting stuck here (if they have less than 1000 open tasks,
  // but that should be a reasonable assumption).
  constexpr auto MaxThasks = 1000;
  m_freeCallbacks.release(MaxThasks);
}

void QtThreadedLambdaFunctor::operator()(std::function<void(void)> callback) {
  m_helper(std::move(callback));
}