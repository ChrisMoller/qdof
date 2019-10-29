#ifndef UNITSBOX_H
#define UNITSBOX_H

#include <QtWidgets>

enum {
    UNITS_MILLIMETRE,
    UNITS_CENTIMETRE,
    UNITS_METRE,
    UNITS_INCH,
    UNITS_FOOT
};

class UnitsBox : public QComboBox
{
    Q_OBJECT

public:
    UnitsBox();

signals:
};

#endif // UNITSBOX_H
