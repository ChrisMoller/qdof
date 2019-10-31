#ifndef DLINEEDIT_H
#define DLINEEDIT_H

#include <QtWidgets>
#include "unitsbox.h"

class DLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    DLineEdit(UnitsBox *ubx, double inc, QWidget *parent = nullptr);
    void incDec(const QString &text);

private:
    QWidget *mw;
    UnitsBox *ub;
    double incr;

signals:
    void textEdited(const QString &text);

public slots:
};


#endif // DLINEEDIT_H
