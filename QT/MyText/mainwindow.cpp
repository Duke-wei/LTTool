#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isUntitled = true;
    curFile = tr("uname.txt");
    setWindowTitle(curFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile(){
    if(maybeSave()){
        isUntitled = true;
        curFile = tr("uname.txt");
        setWindowTitle(curFile);
        ui->textEdit->clear();
        ui->textEdit->setVisible(true);
    }
}

bool MainWindow::maybeSave(){
    if(ui->textEdit->document()->isModified()){
        QMessageBox box;
        box.setWindowTitle(tr("warning"));
        box.setIcon(QMessageBox::Warning);
        box.setText(curFile+tr("not save,if save?"));
        QPushButton *yesBtn = box.addButton(tr("yes(&y)"),QMessageBox::YesRole);
        box.addButton(tr("No(&n)"),QMessageBox::NoRole);
        QPushButton *cancelBut = box.addButton(tr("cancel"),QMessageBox::RejectRole);
        box.exec();
        if(box.clickedButton()==yesBtn)
            return save();
        else if(box.clickedButton()==cancelBut)
            return false;
    }
    return true;
}

bool MainWindow::save(){
    if(isUntitled){
        return saveAs();
    }else{
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs(){
    QString fileName = QFileDialog::getSaveFileName(this,tr("Saveas"),curFile);
    if(fileName.isEmpty()) return false;
    return saveFile(fileName);
}

bool MainWindow::saveFile(const QString &fileName)
{
   QFile file(fileName);

   if (!file.open(QFile::WriteOnly | QFile::Text)) {

       // %1和%2分别对应后面arg两个参数，/n起换行的作用
       QMessageBox::warning(this, tr("多文档编辑器"),
                   tr("无法写入文件 %1：/n %2")
                  .arg(fileName).arg(file.errorString()));
       return false;
   }
   QTextStream out(&file);
   // 鼠标指针变为等待状态
   QApplication::setOverrideCursor(Qt::WaitCursor);
   out << ui->textEdit->toPlainText();
   // 鼠标指针恢复原来的状态
   QApplication::restoreOverrideCursor();
   isUntitled = false;
   // 获得文件的标准路径
   curFile = QFileInfo(fileName).canonicalFilePath();
   setWindowTitle(curFile);
   return true;
}

bool MainWindow::loadFile(const QString &fileName){
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, tr("多文档编辑器"),
                     tr("无法读取文件 %1:\n%2.")
                     .arg(fileName).arg(file.errorString()));
           return false; // 只读方式打开文件，出错则提示，并返回false
    }
    QTextStream in(&file); // 新建文本流对象
    QApplication::setOverrideCursor(Qt::WaitCursor);
        // 读取文件的全部文本内容，并添加到编辑器中
    ui->textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();
       // 设置当前文件
    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);
    return true;
}

void MainWindow::on_actionSaveAs_triggered()
{
    saveAs();
}

void MainWindow::on_actionSave_triggered()
{
    save();
}

void MainWindow::on_actionNewFile_triggered()
{
    newFile();
}

void MainWindow::on_actionOpenFile_triggered()
{
   if(maybeSave()){
       QString fileName = QFileDialog::getOpenFileName(this);
       if(!fileName.isEmpty()){
           loadFile(fileName);
           ui->textEdit->setVisible(true);
       }
   }
}

void MainWindow::on_actionClose_triggered()
{
   if(maybeSave()){
       ui->textEdit->setVisible(false);
   }
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionExit_triggered()
{
   on_actionClose_triggered();
   qApp->quit();
}

void MainWindow::on_actionCopy_triggered()
{
   ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
   ui->textEdit->paste();
}

void MainWindow::closeEvent(QCloseEvent *event){
    if(maybeSave()){
        event->accept();
    }else{
        event->ignore();
    }
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}
