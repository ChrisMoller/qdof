#ifndef CAMERAS_H
#define CAMERAS_H

#include <QtWidgets>
#include <QMetaType>

typedef struct
{
    QString name;
    double coc;
} CameraModel;
Q_DECLARE_METATYPE(CameraModel **)
Q_DECLARE_METATYPE(CameraModel *)

typedef struct
{
    QString name;
    CameraModel **models;
} Mfgr;

class Cameras : public QWidget
{
    Q_OBJECT

public:
    Cameras();
    Mfgr **list;
};


#if 0
#include <QtWidgets>

#include <QMetaType>

typedef struct
{
    QString model;
    double coc;
} Camera;

Q_DECLARE_METATYPE(Camera)

class Cameras : public QWidget
{
    Q_OBJECT
public:
    Cameras();
    QComboBox box;

private:
    Camera c01;
    Camera c02;
    Camera c03;
    Camera d01;
    Camera d02;

    QList<Camera> mfgr_c;
    QList<Camera> mfgr_d;

signals:

public slots:
};

#endif

#endif // CAMERAS_H
