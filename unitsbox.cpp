#include "unitsbox.h"

UnitsBox::UnitsBox()
{
    QComboBox::addItem("mm", QVariant (1.0));
    QComboBox::addItem("cm", QVariant (10.0));
    QComboBox::addItem("m", QVariant (1000.0));
    QComboBox::addItem("in", QVariant (25.4));
    QComboBox::addItem("ft", QVariant (304.8));
}
