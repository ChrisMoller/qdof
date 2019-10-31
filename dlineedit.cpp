#include "dlineedit.h"
#include "mainwindow.h"
#include "unitsbox.h"

DLineEdit::DLineEdit(UnitsBox *ubx, double inc, QWidget *parent)
{
    mw = parent;
    ub = ubx;
    incr = inc;
}

void DLineEdit::incDec(const QString &txt)
{
    if (txt.length() > 0) {
        int lc = txt.back().cell();
        QString rem = txt.chopped(1);
        switch(lc) {
        case '+':
            {
                try {
                    double val = rem.toDouble() + incr;
                    setText(QString::number (val));
                    reinterpret_cast<MainWindow *>(mw)->setValue();
                }
                catch(...) {
                    // do nothing
                }
            }
            break;
        case '-':
            {
                try {
                    double val = rem.toDouble() - incr;
                    setText(QString::number (val));
                    reinterpret_cast<MainWindow *>(mw)->setValue();
                }
                catch(...) {
                    // do nothing
                }
            }
            break;
        case 'm':
            if (ub != nullptr) ub->setCurrentIndex(UNITS_MILLIMETRE);
            setText(rem);
            reinterpret_cast<MainWindow *>(mw)->setValue();
            break;
        case 'c':
            if (ub != nullptr) ub->setCurrentIndex(UNITS_CENTIMETRE);
            setText(rem);
            reinterpret_cast<MainWindow *>(mw)->setValue();
            break;
        case 'M':
            if (ub != nullptr) ub->setCurrentIndex(UNITS_METRE);
            setText(rem);
            reinterpret_cast<MainWindow *>(mw)->setValue();
            break;
        case 'i':
            if (ub != nullptr) ub->setCurrentIndex(UNITS_INCH);
            setText(rem);
            reinterpret_cast<MainWindow *>(mw)->setValue();
            break;
        case 'f':
            if (ub != nullptr) ub->setCurrentIndex(UNITS_FOOT);
            setText(rem);
            reinterpret_cast<MainWindow *>(mw)->setValue();
            break;
        }
    }
}
