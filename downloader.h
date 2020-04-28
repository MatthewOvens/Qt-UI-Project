#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QFile>
#include <iostream>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QByteArray>

class Downloader : public QObject
{
 Q_OBJECT
 public:
  explicit Downloader(QUrl fileUrl, QObject *parent = 0);

  virtual ~Downloader();

 signals:
  void downloaded();
  void error();

 public slots:

  void fileDownloaded(QNetworkReply* pReply);

 private:
  QNetworkAccessManager manager;
  QString url;
};

#endif // DOWNLOADER_H
