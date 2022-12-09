#ifndef QT_SOCKET_WRAPPER_H
#define QT_SOCKET_WRAPPER_H

#include <qobject.h>
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <qudpsocket.h>

#include <functional>

class QtTcpWrapper : public QObject {
  Q_OBJECT

 public:
  QtTcpWrapper(QObject* parent, const std::string& ip = "127.0.0.1", const quint16 serverPort = 6667,
               const quint16 clientPort = 6666);
  ~QtTcpWrapper();

  void startListening();
  void stopListening();

  void sendMessage(const std::wstring& message) const;

  void setReadCallback(const std::function<void(const std::wstring&)>& callback);

  quint16 getServerPort() const;
  void setServerPort(const quint16 serverPort);

  quint16 getClientPort() const;
  void setClientPort(const quint16 clientPort);

  bool isListening() const;

 signals:

 public slots:
  void acceptConnection();
  void startRead();

 private:
  quint16 m_serverPort;
  quint16 m_clientPort;
  std::string m_ip;

  std::function<void(const std::wstring&)> m_readCallback;

  QTcpServer* m_tcpServer;
  QTcpSocket* m_tcpClient;
};

#endif  // QT_SOCKET_WRAPPER_H