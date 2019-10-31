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
  void mfgrActivated(int idx);
  void modelActivated(int idx);
  
private:
    double compute();
    void setCoc(double lcoc);

    DLineEdit *focal_length;
    UnitsBox   focal_units;
    DLineEdit *near_distance;
    UnitsBox   near_units;
    DLineEdit *far_distance;
    UnitsBox   far_units;
    QLabel     fval_lbl;
    QLineEdit *coc_lbl;
    QComboBox *mfgrbox;
    QComboBox *modelbox;
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
