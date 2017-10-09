#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void newFile();
    bool maybeSave();
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    bool loadFile(const QString &fileName);

private slots:
    void on_actionSaveAs_triggered();

    void on_actionSave_triggered();

    void on_actionNewFile_triggered();

    void on_actionOpenFile_triggered();

    void on_actionClose_triggered();

    void on_actionUndo_triggered();

    void on_actionExit_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

private:
    Ui::MainWindow *ui;
    bool isUntitled;
    QString curFile;
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
