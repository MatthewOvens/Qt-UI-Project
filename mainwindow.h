#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "downloader.h"

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QTextBrowser>
#include <QStringList>
#include <QLabel>
#include <QDesktopServices>
#include <QtCharts>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QLegend>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QPieSeries>
#include <QPieSlice>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void displayUniGraphic_comparisonGrafic();
    void displayEMIGraphic();
    void errorSlot();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H


