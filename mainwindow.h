#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "unitsbox.h"
#include "dlineedit.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
  void setValue ();
  void setValue(int idx);
  
private:
    double compute(double fl, double nd, double fd);

    DLineEdit *focal_length;
    UnitsBox focal_units;
    DLineEdit *near_distance;
    UnitsBox near_units;
    DLineEdit *far_distance;
    UnitsBox far_units;
    QLabel   fval_lbl;
    QLabel   coc_lbl;
    double coc;
    double dfl;
    double dnd;
    double dfd;
    int    dfli;
    int    dndi;
    int    dfdi;
    int    mfgrIndex;
    int    modelIndex;

    QSettings settings;

signals:
};

#endif // MAINWINDOW_H
