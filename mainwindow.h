#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTextEdit>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>
#include <QFile>
#include <QFileDialog>
#include <QList>
#include <QAction>
#include <QMessageBox>
#include <QString>
#include <QTextStream>
#include <QIODevice>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newFile();
    void saveAs();

private:
    void createActions();
    void createMenus();
    bool okayToContinue();

    QTextEdit *m_textEdit;
    QAction *m_newFileAction;
    QAction *m_saveAsAction;
    QMenu *m_fileMenu;
    QMenu *m_editMenu;
    QString currentFile;
};

#endif // MAINWINDOW_H
