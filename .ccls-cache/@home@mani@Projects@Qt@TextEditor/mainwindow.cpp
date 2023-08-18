#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_textEdit = new QTextEdit;
    setCentralWidget(m_textEdit);

    createActions();
    createMenus();
}

MainWindow::~MainWindow()
{
    // Destroys main window
}

void MainWindow::createActions()
{
    // New file action
    m_newFileAction = new QAction("&New", this);
    m_newFileAction->setIcon(QIcon(":/images/new.png"));
    m_newFileAction->setShortcut(QKeySequence::New);
    m_newFileAction->setStatusTip("Create a new file");
    connect(m_newFileAction, SIGNAL(triggered()), this, SLOT(newFile()));

    // Save file action
    m_saveFileAction = new QAction("&Save", this);
    m_saveFileAction->setIcon(QIcon(":/images/save.png"));
    m_saveFileAction->setShortcut(QKeySequence::Save);
    m_saveFileAction->setStatusTip("Save file");
    connect(m_saveFileAction, SIGNAL(triggered()), this, SLOT(saveFile()));
}

// Create menu bar
void MainWindow::createMenus()
{
    m_fileMenu = menuBar()->addMenu("&File");
    m_fileMenu->addAction(m_newFileAction);
    m_fileMenu->addAction(m_saveFileAction);
}

//
void MainWindow::setCurrentFile(const QString &fileName)
{
    currentFile = fileName;
    setWindowModified(false);
    QString shownName = "Untitled";

    if (!currentFile.isEmpty())
    {
        shownName = strippedName(currentFile);
        //recentFiles.removeAll(currentFile);
        //recentFiles.prepend(currentFile);
        //updateRecentFileActions();
    }

    setWindowTitle(("%1[*] - %2").arg(shownName)
                                 .arg("Notepad"));
}

//
QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

// Verifies with the user if it is okay to continue
bool MainWindow::okayToContinue()
{
    if (isWindowModified())
        {
            int r = QMessageBox::warning(this, "Notepad", "The document has been modified.\n"
                                         "Do you want to save your changes?",
                                         QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

            if (r == QMessageBox::Yes)
                return saveFile();
            else if (r == QMessageBox::Cancel)
                return false;
        }

    return true;
}

// Creates a new file TODO: implement okayToContinue() method
void MainWindow::newFile()
{
    //if (okayToContinue())
    //{
        //currentFile.clear();
        //m_textEdit->setText(QString());
    //}

    currentFile.clear();
    m_textEdit->setText(QString());
}

// Checks if file exists to save too
bool MainWindow::save()
{
    if (currentFile.isEmpty())
        return saveAs();
    else
        return saveFile(currentFile);
}

// TODO: Save progress to current file
bool MainWindow::saveFile(const QString &fileName)
{
    if (!m_textEdit->writeFile(fileName));
    {
        statusBar()->showMessage("Saving canceled", 2000);

        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage("File saved", 2000);

    return true;
}
