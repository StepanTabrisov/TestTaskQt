#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view = new QGraphicsView(this);
    scene = new Scene(this);
    Init();
}

MainWindow::~MainWindow()
{
    delete view;
    delete scene;
    delete ui;
}

void MainWindow::Init(){

    view->setMinimumHeight(600);
    view->setMinimumWidth(650);
    scene->setSceneRect(0,0,600,500);
    view->setScene(scene);

    connect(ui->openFileButton, SIGNAL(clicked()), this, SLOT(OpenButtonClick()));
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(ClearButtonClick()));
    connect(ui->drawButton, SIGNAL(clicked()), this, SLOT(DrawButtonClick()));
}


// считывание данных из файла
void MainWindow::OpenButtonClick()
{
    //QString fileName = QFileDialog::getOpenFileName(this, tr("Open json file"), "/home/stepan/qt_projects", tr("Json files (*.json)"));

    QString fileName = "/home/stepan/qt_projects/test1/roads.json";
    QString val;
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8(), &error);

    QString keyName = "road";

    if (doc.isObject())
    {
        QJsonObject json = doc.object();

        for(int i = 0; i < json.keys().size(); i++){

            Road temp;
            QString key = keyName + QString::number(i+1);
            QJsonArray jsonArray = json[key.toStdString().c_str()].toArray();

            foreach (const QJsonValue &value, jsonArray)
            {
                if (value.isObject())
                {
                    QJsonObject obj = value.toObject();
                    QPointF point;
                    point.setX(obj["x"].toInt() * 5);
                    point.setY(obj["y"].toInt() * 5);
                    temp.AddPoint(point);
                }
            }
            roads.push_back(temp);
        }
    }
    scene->SetRoads(roads);
    scene->DrawRoads(roads);
}

void MainWindow::ClearButtonClick()
{
    scene->clear();
}

void MainWindow::DrawButtonClick(){
    scene->DrawRoads(roads);
}
