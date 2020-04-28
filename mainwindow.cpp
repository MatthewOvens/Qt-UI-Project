#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this); 

    QUrl emiArtistsUrl("http://www.ivl.disco.unimib.it/minisites/cpp/List_of_EMI_artists.txt");
    Downloader *fileCtrlEMI = new Downloader(emiArtistsUrl, this);

    //Quando il file è stato scaricato, fa partire il createGraphics
    connect(fileCtrlEMI, SIGNAL (downloaded()), this, SLOT (displayEMIGraphic()));
    connect(fileCtrlEMI, SIGNAL (error()), this, SLOT (errorSlot()));

    QUrl universalArtistsUrl("http://www.ivl.disco.unimib.it/minisites/cpp/List_of_Universal_artists.txt");
    Downloader *fileCtrlUniversal = new Downloader(universalArtistsUrl, this);

    //Quando il file è stato scaricato, fa partire il createGraphics
    connect(fileCtrlUniversal, SIGNAL (downloaded()), this, SLOT (displayUniGraphic_comparisonGrafic()));
    connect(fileCtrlUniversal, SIGNAL (error()), this, SLOT (errorSlot()));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::displayEMIGraphic() {

        //Lettura file e creazione TextBrowser con elencati tutti gli artisti EMI
        //Ogni nome è linkato alla propria pagina wikipedia (tramite hyperlink)
        //I nomi del file senza l'url di wikipedia sono privati di hyperlink (link = "")
        //Nel caso in cui invece ci fosse l'url ma non il nome, ho preso l'ultima
        //"sezione" della stringa url dopo il secondo '/' usandola come nome


        QFile file("EMI.txt");
        if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            std::cerr << "Cannot open file for reading: " << qPrintable(file.errorString()) << std::endl;
            return;
        }

        //Lista di char nella quale vado a salvare la prima lettera di ogni artista
        QList <QChar> EMIlist;

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();

            QString url = line.section('"', 1, 1);
            QString nameSurname = line.section('"', 2, 2);
            QString link;

            if(nameSurname == ""){
                nameSurname = url.section('/', 2, 2);
            }
            else {
                nameSurname = nameSurname.remove(0,1);
            }

            if(url == ""){
                link = "";
            }
            else {
                if(url.front() == '/'){
                    link = "https://it.wikipedia.org" + url;
                }
                else {
                    link = url;
                }
            }

            EMIlist.append(nameSurname.front().toUpper());

            QLabel *lab = new QLabel(this);

            lab->setTextFormat(Qt::RichText);
            lab->setTextInteractionFlags(Qt::TextBrowserInteraction);
            lab->setOpenExternalLinks(true);

            QString a = "<a href=\"%1\">%2</a>";
            lab->setText(a.arg(link).arg(nameSurname));

            ui->textBrowser_EMI->setOpenExternalLinks(true);
            ui->textBrowser_EMI->append(lab->text());

        }
        file.close();


        //CREAZIONE GRAFICO EMI

        //Per ogni lettera della lista di char andro' a incrementare il rispettivo contatore intero
        //Se il primo carattere del nome di un artista non e' una lettera dell'alfabeto, lo conto
        //come otherArtists
        int aArtist = 0;
        int bArtist = 0;
        int cArtist = 0;
        int dArtist = 0;
        int eArtist = 0;
        int fArtist = 0;
        int gArtist = 0;
        int hArtist = 0;
        int iArtist = 0;
        int jArtist = 0;
        int kArtist = 0;
        int lArtist = 0;
        int mArtist = 0;
        int nArtist = 0;
        int oArtist = 0;
        int pArtist = 0;
        int qArtist = 0;
        int rArtist = 0;
        int sArtist = 0;
        int tArtist = 0;
        int uArtist = 0;
        int vArtist = 0;
        int wArtist = 0;
        int xArtist = 0;
        int yArtist = 0;
        int zArtist = 0;
        int otherArtist = 0;

        for(int i = 0; i < EMIlist.size(); ++i){
            switch (EMIlist.at(i).unicode()) {
                case 'A' : aArtist++; break;
                case 'B' : bArtist++; break;
                case 'C' : cArtist++; break;
                case 'D' : dArtist++; break;
                case 'E' : eArtist++; break;
                case 'F' : fArtist++; break;
                case 'G' : gArtist++; break;
                case 'H' : hArtist++; break;
                case 'I' : iArtist++; break;
                case 'J' : jArtist++; break;
                case 'K' : kArtist++; break;
                case 'L' : lArtist++; break;
                case 'M' : mArtist++; break;
                case 'N' : nArtist++; break;
                case 'O' : oArtist++; break;
                case 'P' : pArtist++; break;
                case 'Q' : qArtist++; break;
                case 'R' : rArtist++; break;
                case 'S' : sArtist++; break;
                case 'T' : tArtist++; break;
                case 'U' : uArtist++; break;
                case 'V' : vArtist++; break;
                case 'W' : wArtist++; break;
                case 'X' : xArtist++; break;
                case 'Y' : yArtist++; break;
                case 'Z' : zArtist++; break;
                default: otherArtist++;
            }
        }

        //I contatori appena creati andranno nella set, cosi' da essere visualizzati sul grafico
        QBarSet *set = new QBarSet("Lettere");

        *set << aArtist << bArtist << cArtist << dArtist << eArtist << fArtist << gArtist << hArtist << iArtist
             << jArtist << kArtist << lArtist << mArtist << nArtist << oArtist << pArtist << qArtist << rArtist
             << sArtist << tArtist << uArtist << vArtist << wArtist << xArtist << yArtist << zArtist << otherArtist;

        set->setColor("red");
        set->setLabelColor("black");

        QBarSeries *series = new QBarSeries();
        series->append(set);

        series->setLabelsVisible(true);
        series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);


        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Artisti EMI per lettera");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        QStringList categories;
        categories << "A" << "B" << "C" << "D" << "E" << "F" << "G" << "H" << "I"
                   << "J" << "K" << "L" << "M" << "N" << "O" << "P" << "Q" << "R"
                   << "S" << "T" << "U" << "V" << "W" << "X" << "Y" << "Z" << "...";

        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0, 100);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        chart->legend()->setVisible(false);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        ui->verticalLayout->addWidget(chartView);
}

void MainWindow::displayUniGraphic_comparisonGrafic() {

        //Lettura file e creazione TextBrowser con elencati tutti gli artisti Universal
        //Ogni nome è linkato alla propria pagina wikipedia (tramite hyperlink)
        //I nomi del file senza l'url di wikipedia sono privati di hyperlink (link = "")
        //Nel caso in cui invece ci fosse l'url ma non il nome, ho preso l'ultima
        //"sezione" della stringa url dopo il secondo '/' usandola come nome

        QFile file("Universal.txt");
        if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            std::cerr << "Cannot open file for reading: " << qPrintable(file.errorString()) << std::endl;
            return;
        }

        //Lista di char nella quale vado a salvare la prima lettera di ogni artista
        QList <QChar> uniList;

        int numberUniArtists = 0;
        int numberEMIArtists = 0;

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();

            numberUniArtists++;

            QString url = line.section('"', 1, 1);
            QString nameSurname = line.section('"', 2, 2);
            QString link;

            if(nameSurname == ""){
                nameSurname = url.section('/', 2, 2);
            }
            else {
                nameSurname = nameSurname.remove(0,1);
            }

            if(url == ""){
                link = "";
            }
            else {
                if(url.front() == '/'){
                    link = "https://it.wikipedia.org" + url;
                }
                else {
                    link = url;
                }
            }

            uniList.append(nameSurname.front().toUpper());

            QLabel *lab = new QLabel(this);

            lab->setTextFormat(Qt::RichText);
            lab->setTextInteractionFlags(Qt::TextBrowserInteraction);
            lab->setOpenExternalLinks(true);

            QString a = "<a href=\"%1\">%2</a>";
            lab->setText(a.arg(link).arg(nameSurname));

            ui->textBrowser_Uni->setOpenExternalLinks(true);
            ui->textBrowser_Uni->append(lab->text());

        }
        file.close();


        //CREAZIONE GRAFICO UNIVERSAL

        //Per ogni lettera della lusta di char andro' a incrementare il rispettivo contatore intero
        //Se il primo carattere del nome di un artista non e' una lettera dell'alfabeto, lo conto
        //come otherArtists
        int aArtist = 0;
        int bArtist = 0;
        int cArtist = 0;
        int dArtist = 0;
        int eArtist = 0;
        int fArtist = 0;
        int gArtist = 0;
        int hArtist = 0;
        int iArtist = 0;
        int jArtist = 0;
        int kArtist = 0;
        int lArtist = 0;
        int mArtist = 0;
        int nArtist = 0;
        int oArtist = 0;
        int pArtist = 0;
        int qArtist = 0;
        int rArtist = 0;
        int sArtist = 0;
        int tArtist = 0;
        int uArtist = 0;
        int vArtist = 0;
        int wArtist = 0;
        int xArtist = 0;
        int yArtist = 0;
        int zArtist = 0;
        int otherArtist = 0;

        for(int i = 0; i < uniList.size(); ++i){
            switch (uniList.at(i).unicode()) {
                case 'A' : aArtist++; break;
                case 'B' : bArtist++; break;
                case 'C' : cArtist++; break;
                case 'D' : dArtist++; break;
                case 'E' : eArtist++; break;
                case 'F' : fArtist++; break;
                case 'G' : gArtist++; break;
                case 'H' : hArtist++; break;
                case 'I' : iArtist++; break;
                case 'J' : jArtist++; break;
                case 'K' : kArtist++; break;
                case 'L' : lArtist++; break;
                case 'M' : mArtist++; break;
                case 'N' : nArtist++; break;
                case 'O' : oArtist++; break;
                case 'P' : pArtist++; break;
                case 'Q' : qArtist++; break;
                case 'R' : rArtist++; break;
                case 'S' : sArtist++; break;
                case 'T' : tArtist++; break;
                case 'U' : uArtist++; break;
                case 'V' : vArtist++; break;
                case 'W' : wArtist++; break;
                case 'X' : xArtist++; break;
                case 'Y' : yArtist++; break;
                case 'Z' : zArtist++; break;
                default: otherArtist++;
            }
        }

        //I contatori appena creati andranno nella set, cosi' da essere visualizzati sul grafico
        QBarSet *set = new QBarSet("Lettere");

        *set << aArtist << bArtist << cArtist << dArtist << eArtist << fArtist << gArtist << hArtist << iArtist
             << jArtist << kArtist << lArtist << mArtist << nArtist << oArtist << pArtist << qArtist << rArtist
             << sArtist << tArtist << uArtist << vArtist << wArtist << xArtist << yArtist << zArtist << otherArtist;

        set->setColor("royalblue");
        set->setLabelColor("black");

        QBarSeries *series = new QBarSeries();
        series->append(set);

        series->setLabelsVisible(true);
        series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Artisti Universal per lettera");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        QStringList categories;
        categories << "A" << "B" << "C" << "D" << "E" << "F" << "G" << "H" << "I"
                   << "J" << "K" << "L" << "M" << "N" << "O" << "P" << "Q" << "R"
                   << "S" << "T" << "U" << "V" << "W" << "X" << "Y" << "Z" << "...";

        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0, 100);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        chart->legend()->setVisible(false);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        ui->verticalLayout_3->addWidget(chartView);


        //CREAZIONE GRAFICO DI COMPARAZIONE

        //lettura di ogni riga del file per trovare il numero esatto di artisti EMI
        QFile file2("EMI.txt");
        if (!file2.open(QIODevice::ReadOnly | QFile::Text)) {
            std::cerr << "Cannot open file for reading: " << qPrintable(file2.errorString()) << std::endl;
            return;
        }

        QTextStream in2(&file2);
        while (!in2.atEnd()) {
            QString a = in2.readLine();
            numberEMIArtists++;
        }
        file.close();

        int totalArtists = numberUniArtists + numberEMIArtists;

        double percEMI = (double) numberEMIArtists/totalArtists;
        double percUni = (double) numberUniArtists/totalArtists;

        QPieSeries *seriesP = new QPieSeries();
        seriesP->append("EMI Artists " + QString::number(numberEMIArtists), percEMI);
        seriesP->append("Universal Artists " + QString::number(numberUniArtists), percUni);
        seriesP->setLabelsVisible(true);

        QPieSlice *slice0 = seriesP->slices().at(0);
        slice0->setColor("red");
        QPieSlice *slice1 = seriesP->slices().at(1);
        slice1->setColor("royalblue");

        QChart *chartP = new QChart();
        chartP->addSeries(seriesP);
        chartP->setTitle("Artisti per etichetta");

        QChartView *chartViewP = new QChartView(chartP);
        chartView->setRenderHint(QPainter::Antialiasing);

        ui->horizontalLayout_3->addWidget(chartViewP);

}

void MainWindow::errorSlot(){

    std::cerr << "Error in the Reply";
    return;

}

