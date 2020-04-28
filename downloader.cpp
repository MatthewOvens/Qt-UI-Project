#include "downloader.h"


Downloader::Downloader(QUrl fileUrl, QObject *parent) : QObject(parent), url(fileUrl.toString()) {

    QNetworkRequest request(fileUrl);
    manager.get(request);

    connect(
      &manager, SIGNAL (finished(QNetworkReply*)),
      this, SLOT (fileDownloaded(QNetworkReply*))
      );
}


Downloader::~Downloader() { }


void Downloader::fileDownloaded(QNetworkReply *pReply) {


 if(pReply->error()) {
     emit error();
 }
 else {

     QString nomeFile;
     if(url == "http://www.ivl.disco.unimib.it/minisites/cpp/List_of_Universal_artists.txt") {
         nomeFile = "Universal.txt";
     }
     else
         nomeFile = "EMI.txt";

     QFile *file = new QFile(nomeFile);
     if (!file->open(QIODevice::WriteOnly | QFile::Text)) {
         std::cerr << "Cannot open file for writing: " << qPrintable(file->errorString()) << std::endl;
         return;
     }
     else {
         file->write(pReply->readAll());
         file->close();
         //emit a signal
         pReply->deleteLater();
         emit downloaded();
     }

 }

}
