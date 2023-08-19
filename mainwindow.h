#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTextEdit>
#include <QTextStream>
#include <QStatusBar>
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include <QFile>
#include <QFileDialog>
#include <QApplication>
#include <QMessageBox>
#include <QList>
#include <QIcon>
#include <QAction>
#include <QString>
#include <QIODevice>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newFile();
    void openFile();
    void saveAs();
    void exit();
    void copyToClipboard();
    void pasteFromClipboard();
    void cutToClipboard();
    void undo();
    void redo();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createContextMenu();
    //bool okayToContinue();

    QTextEdit *m_textEdit;

    QAction *m_newFileAction;
    QAction *m_openFileAction;
    QAction *m_saveAsAction;
    QAction *m_exitAction;
    QAction *m_copyAction;
    QAction *m_pasteAction;
    QAction *m_cutAction;
    QAction *m_undoAction;
    QAction *m_redoAction;

    QMenu *m_fileMenu;
    QMenu *m_editMenu;

    QToolBar *m_fileToolBar;
    QToolBar *m_editToolBar;

    QString currentFile;
};

#endif // MAINWINDOW_H
