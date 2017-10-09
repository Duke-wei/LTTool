#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QAction *openAction = new QAction(tr("&Open"),this);
    QIcon icon(":/myPNG/5.png");
    openAction->setIcon(icon);
    openAction->setShortcut(QKeySequence(tr("Ctrl+0")));
    ui->menuFile_F->addAction(openAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}
