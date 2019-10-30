/* Copyright 2019 MSDS LLC */

#include <QtWidgets>
#include <QtGlobal>
#include "mainwindow.h"
#include "unitsbox.h"
#include "dlineedit.h"
#include "cameras.h"

#define FOCAL_LENGTH  "focal_length"
#define NEAR_DISTANCE "near_distance"
#define FAR_DISTANCE  "far_distance"
#define FOCAL_UNITS   "focal_units"
#define NEAR_UNITS    "near_units"
#define FAR_UNITS     "far_units"
#define COC           "coc"
#define MFGR          "mfgr"
#define MODEL         "model"


double MainWindow::compute(double fl, double nd, double fd)
{
    double fls = focal_units.currentData ().toDouble ();
    double nds = near_units.currentData ().toDouble ();
    double fds = far_units.currentData ().toDouble ();

    double sfl = fls * fl;
    double snd = nds * nd;
    double sfd = fds * fd;

    double fstop = sfl * sfl / coc;
    if (sfd > 0.0)
      fstop *= (sfd - snd) / (2.0 * sfd * snd);
    else
      fstop /= 2.0 * snd;
    return fstop;
}

void MainWindow::setValue(int)
{
    double fl;
    try { fl = (focal_length->text ()).toDouble (); }
    catch (...) { return; }

    double nd;
    try { nd = (near_distance->text ()).toDouble (); }
    catch (...) { return; }

    QString fdc = far_distance->text ();
    double fd = -1.0;
    if (fdc.length () > 0) fd =  (far_distance->text ()).toDouble ();

    double fstop = compute (fl, nd, fd);
    fval_lbl.setText (QString::number (fstop));

    double fdi = far_units.currentIndex ();
    double ndi = near_units.currentIndex ();
    double fli = focal_units.currentIndex ();

    settings.setValue(FOCAL_LENGTH,  fl);
    settings.setValue(NEAR_DISTANCE, nd);
    settings.setValue(FAR_DISTANCE,  fd);
    settings.setValue(FOCAL_UNITS,   fli);
    settings.setValue(NEAR_UNITS,    ndi);
    settings.setValue(FAR_UNITS,     fdi);
    settings.setValue(COC,           coc);
    settings.setValue (MFGR,         mfgrIndex);
    settings.setValue (MODEL,        modelIndex);
}

void MainWindow::setValue()
{
    setValue(0);
}

void MainWindow::mfgrActivated(int idx)
{
    qInfo() << "mfgrActivated " << idx;
}

void MainWindow::modelActivated(int idx)
{
    qInfo() << "modelActivated " << idx;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QSettings settings;
    coc        = settings.value(COC,  0.019).toDouble();

    dfl        = settings.value(FOCAL_LENGTH,  54).toDouble();
    dnd        = settings.value(NEAR_DISTANCE, 26).toDouble();
    dfd        = settings.value(FAR_DISTANCE,  28).toDouble();
    dfli       = settings.value(FOCAL_UNITS,   0).toInt();
    dndi       = settings.value(NEAR_UNITS,    0).toInt();
    dfdi       = settings.value(FAR_UNITS,     0).toInt();
    mfgrIndex  = settings.value (MFGR, 0).toInt ();
    modelIndex = settings.value (MODEL, 0).toInt ();

    QGroupBox *formGroupBox = new QGroupBox("Depth of Field");
    QGridLayout *layout = new QGridLayout;

    coc   = settings.value(COC,  0.019).toDouble();

    int row = 0;




    QRegExp rx("[mcMif0-9.+-]*");
    QValidator *validator = new QRegExpValidator(rx, this);

    // focal length

    focal_units.setCurrentIndex (dfli);
    QObject::connect(&focal_units,
        QOverload<int>::of(&QComboBox::activated),
        this,
        QOverload<int>::of(&MainWindow::setValue));

    focal_length = new DLineEdit(&focal_units, this);
    focal_length->setText (QString::number (dfl));
    focal_length->setPlaceholderText(QObject::tr("Focal length"));
    focal_length->setValidator(validator);
    QObject::connect(focal_length,
                     SIGNAL(returnPressed()),
                     this,
                     SLOT(setValue()));
    QObject::connect(focal_length,
                     QOverload<const QString &>::of(&QLineEdit::textEdited),
                     focal_length,
                     &DLineEdit::incDec);


    layout->addWidget(new QLabel(QObject::tr("Focal Length:")),  row, 0);
    layout->addWidget(focal_length,  row, 1);
    layout->addWidget(&focal_units,  row, 2);

    row++;

    // near distance

    near_units.setCurrentIndex (dndi);
    QObject::connect(&near_units,
        QOverload<int>::of(&QComboBox::activated),
        this,
        QOverload<int>::of(&MainWindow::setValue));

    near_distance = new DLineEdit(&near_units, this);
    near_distance->setText (QString::number (dnd));
    near_distance->setPlaceholderText(QObject::tr("Near distance"));
    near_distance->setValidator(validator);
    QObject::connect(near_distance,
                     SIGNAL(returnPressed()),
                     this,
                     SLOT(setValue()));
    QObject::connect(near_distance,
                     QOverload<const QString &>::of(&QLineEdit::textEdited),
                     near_distance,
                     &DLineEdit::incDec);



    layout->addWidget(new QLabel(QObject::tr("Near Distance:")),  row, 0);
    layout->addWidget(near_distance,  row, 1);
    layout->addWidget(&near_units,  row, 2);

    row++;

    // far distance

    far_units.setCurrentIndex (dfdi);
    QObject::connect(&far_units,
        QOverload<int>::of(&QComboBox::activated),
        this,
        QOverload<int>::of(&MainWindow::setValue));

    far_distance = new DLineEdit(&far_units, this);
    if (dfd < 0.0) far_distance->setText ("");
    else far_distance->setText (QString::number (dfd));
    far_distance->setPlaceholderText(QObject::tr("Far distance"));
    far_distance->setValidator(validator);
    QObject::connect(far_distance,
                     SIGNAL(returnPressed()),
                     this,
                     SLOT(setValue()));
    QObject::connect(far_distance,
                     QOverload<const QString &>::of(&QLineEdit::textEdited),
                     far_distance,
                     &DLineEdit::incDec);


    layout->addWidget(new QLabel(QObject::tr("Far Distance:")),  row, 0);
    layout->addWidget(far_distance,  row, 1);
    layout->addWidget(&far_units,  row, 2);

    row++;

    // compute button

    QString compute_button_style("background-color: yellow; color: red;");
    QFont   compute_button_font("bold");
    QPushButton *compute_button = new QPushButton(QObject::tr("f stop"));
    compute_button->setStyleSheet (compute_button_style);
    compute_button->setFont(compute_button_font);
    compute_button->setToolTip ("Compute f-stop");
    layout->addWidget(compute_button, row, 0);

    double fstop = compute (dfl, dnd, dfd);
    fval_lbl.setText (QString::number (fstop));
    layout->addWidget(&fval_lbl, row, 1);
    QObject::connect(compute_button,
                     SIGNAL(clicked ()),
                     this,
                     SLOT(setValue()));

    row++;

    Cameras *cameras = new Cameras;

    QComboBox *mfgrbox  = new QComboBox();
    QObject::connect(mfgrbox,
                     SIGNAL(activated (int)),
                     this,
                     SLOT(mfgrActivated(int)));

    for (int j = 0; cameras->list[j]; j++) {
        Mfgr *mfgr  = cameras->list[j];
        QString name = mfgr->name;
        CameraModel **models = mfgr->models;
        QVariant v = QVariant::fromValue(models);
        mfgrbox->addItem(name, v);
    }
    mfgrbox->setCurrentIndex (mfgrIndex);

    CameraModel **models = cameras->list[mfgrIndex]->models;
    QComboBox *modelbox = new QComboBox();
    QObject::connect(modelbox,
                     SIGNAL(activated (int)),
                     this,
                     SLOT(modelActivated(int)));
    for (int k = 0; models[k]; k++) {
        CameraModel *model = models[k];
        QString name = model->name;
        double coc = model->coc;
        modelbox->addItem(name, QVariant(coc));
    }
    modelbox->setCurrentIndex (modelIndex);

    layout->addWidget(mfgrbox,  row, 0);
    row++;
    layout->addWidget(modelbox, row, 0);

    formGroupBox->setLayout(layout);
    formGroupBox->show();
}

MainWindow::~MainWindow()
{
}

