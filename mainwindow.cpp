#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    authorization(0), manager(0), QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    authorization = new Authorization(DB);
    QPalette pal = authorization->palette();
    pal.setColor(QPalette::Background, Qt::green);
    authorization->setPalette(pal);
    ui->horizontalLayout->addWidget(authorization);

    connect(authorization, &Authorization::logged, this, &MainWindow::logged);
}

MainWindow::~MainWindow()
{
    if(authorization != 0) delete authorization;
    if(manager != 0) delete manager;

    delete ui;
}

void MainWindow::logged(QString nickname)
{
    manager = new Manager();
    QPalette pal = manager->palette();
    pal.setColor(QPalette::Background, Qt::green);
    manager->setPalette(pal);
    ui->horizontalLayout->addWidget(manager);

    delete authorization; authorization = 0;
}
