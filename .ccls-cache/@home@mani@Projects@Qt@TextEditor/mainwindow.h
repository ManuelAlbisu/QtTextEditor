#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTextEdit>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>
#include <QList>
#include <QAction>
#include <QMessageBox>
#include <QString>
#include <QTextStream>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newFile();
    bool saveFile();

private:
    void createActions();
    void createMenus();
    bool okayToContinue();

    QTextEdit *m_textEdit;
    QAction *m_newFileAction;
    QAction *m_saveFileAction;
    QString currentFile;
    QMenu *m_fileMenu;
    QMenu *m_editMenu;
};

#endif // MAINWINDOW_H
