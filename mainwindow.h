#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTextEdit>
#include <QVBoxLayout>
#include <QTextStream>
#include <QStatusBar>
#include <QToolBar>
#include <QDockWidget>
#include <QMenu>
#include <QMenuBar>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QPrinter>
#include <QPrintDialog>
#include <QApplication>
#include <QMessageBox>
#include <QSettings>
#include <QList>
#include <QIcon>
#include <QAction>
#include <QString>
#include <QIODevice>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void createActions();
    void createMenus();
    void createToolBars();
    void createContextMenu();
    void createDock();
    void createPushButtons();

private slots:
    void newFile();
    void openFile();
    void saveAs();
    void openRecentFiles();
    void printFile();
    void exit();
    void copyToClipboard();
    void pasteFromClipboard();
    void cutToClipboard();
    void undo();
    void redo();

private:
    void readSettings();
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    bool readFile(const QString &fileName);
    bool loadFile(const QString &fileName);
    void updateRecentFileActions();
    //bool okayToContinue();

    QTextEdit *m_textEdit;
    QVBoxLayout *m_vLayout;

    QAction *m_newFileAction;
    QAction *m_openFileAction;
    QAction *m_saveAsAction;
    QAction *m_printAction;

    enum { MaxRecentFiles = 5 };
    QAction *m_recentFileActions[MaxRecentFiles];
    QAction *m_separatorAction;

    QAction *m_exitAction;
    QAction *m_copyAction;
    QAction *m_pasteAction;
    QAction *m_cutAction;
    QAction *m_undoAction;
    QAction *m_redoAction;

    QPushButton *m_newFileButton;
    QPushButton *m_openFileButton;
    QPushButton *m_saveAsButton;
    QPushButton *m_printButton;
    QPushButton *m_exitButton;

    QMenu *m_fileMenu;
    QMenu *m_editMenu;
    QMenu *m_viewMenu;

    QToolBar *m_fileToolBar;
    QToolBar *m_editToolBar;

    QDockWidget *m_fileDockWidget;
    QWidget *m_fileButtonWidgets;

    QString m_currentFile;
    QStringList m_recentFiles;
};

#endif // MAINWINDOW_H
