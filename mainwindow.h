#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>

#include <Scene.h>
#include <Road.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void Init();

private slots:
    void OpenButtonClick();
    void ClearButtonClick();
    void DrawButtonClick();

private:
    Ui::MainWindow  *ui;
    QGraphicsView   *view;
    Scene           *scene;
    QVector<Road>   roads;
};
#endif // MAINWINDOW_H
