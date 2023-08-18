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
    m_newFileAction = new QAction("&New File", this);
    m_newFileAction->setIcon(QIcon(":/images/new.png"));
    m_newFileAction->setShortcut(QKeySequence::New);
    m_newFileAction->setStatusTip("Create a new file");
    connect(m_newFileAction, SIGNAL(triggered()), this, SLOT(newFile()));

    // Save as action
    m_saveAsAction = new QAction("&Save as...", this);
    m_saveAsAction->setIcon(QIcon(":/images/save-as.png"));
    m_saveAsAction->setShortcut(QKeySequence::SaveAs);
    m_saveAsAction->setStatusTip("Save file as...");
    connect(m_saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));
}

// Create menu bar
void MainWindow::createMenus()
{
    m_fileMenu = menuBar()->addMenu("&File");
    m_fileMenu->addAction(m_newFileAction);
    m_fileMenu->addAction(m_saveAsAction);
}

// Verifies with the user if it is okay to continue
bool MainWindow::okayToContinue()
{
    //if (isWindowModified())
        //{
            //int r = QMessageBox::warning(this, "Notepad", "The document has been modified.\n"
                                         //"Do you want to save your changes?",
                                         //QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

            //if (r == QMessageBox::Yes)
                //return saveFile();
            //else if (r == QMessageBox::Cancel)
                //return false;
        //}

    //return true;
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

// Saves the file with a file name and path specified by the user
void MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly) | QFile::Text)
    {
            statusBar()->showMessage("Cannot save file: " + file.errorString(), 5000);

            return;
    }

    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = m_textEdit->toPlainText();
    out << text;

    file.close();
}
