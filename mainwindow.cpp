#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_textEdit = new QTextEdit;
    setCentralWidget(m_textEdit);

    createActions();
    createMenus();
    createToolBars();
    createContextMenu();
}

MainWindow::~MainWindow()
{
    // Destroys main window
}

void MainWindow::createActions()
{
    // New file action
    m_newFileAction = new QAction("&New File...", this);
    m_newFileAction->setIcon(QIcon(":/images/new.png"));
    m_newFileAction->setShortcut(QKeySequence::New);
    m_newFileAction->setStatusTip("Create a new file.");
    connect(m_newFileAction, SIGNAL(triggered()), this, SLOT(newFile()));

    // Open file action
    m_openFileAction = new QAction("&Open File...", this);
    m_openFileAction->setIcon(QIcon(":/images/new.png"));
    m_openFileAction->setShortcut(QKeySequence::Open);
    m_openFileAction->setStatusTip("Open a file.");
    connect(m_openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));

    // TODO: Save action

    // Save as action
    m_saveAsAction = new QAction("&Save As...", this);
    m_saveAsAction->setIcon(QIcon(":/images/save-as.png"));
    m_saveAsAction->setShortcut(QKeySequence::SaveAs);
    m_saveAsAction->setStatusTip("Save file as...");
    connect(m_saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    // TODO: Open recent file action

    // Exit application action
    m_exitAction = new QAction("&Exit", this);
    m_exitAction->setIcon(QIcon(":/images/exit.png"));
    m_exitAction->setShortcut(QKeySequence::Close);
    m_exitAction->setStatusTip("Exit the application.");
    connect(m_exitAction, SIGNAL(triggered()), this, SLOT(exit()));

    // Copy to clipboard action
    m_copyAction = new QAction("&Copy", this);
    m_copyAction->setIcon(QIcon(":images/copy.png"));
    m_copyAction->setShortcut(QKeySequence::Copy);
    m_copyAction->setStatusTip("Copy selected text to clipboard.");
    connect(m_copyAction, SIGNAL(triggered()), this, SLOT(copyToClipboard()));

    // Paste from clipboard action
    m_pasteAction = new QAction("&Paste", this);
    m_pasteAction->setIcon(QIcon(":images/paste.png"));
    m_pasteAction->setShortcut(QKeySequence::Paste);
    m_pasteAction->setStatusTip("Paste text from clipboard.");
    connect(m_pasteAction, SIGNAL(triggered()), this, SLOT(pasteFromClipboard()));

    // Cut to clipboard action
    m_cutAction = new QAction("&Cut", this);
    m_cutAction->setIcon(QIcon(":images/cut.png"));
    m_cutAction->setShortcut(QKeySequence::Cut);
    m_cutAction->setStatusTip("Cut selected text to clipboard.");
    connect(m_cutAction, SIGNAL(triggered()), this, SLOT(cutToClipboard()));

    // Undo action
    m_undoAction = new QAction("&Undo", this);
    m_undoAction->setIcon(QIcon(":images/undo.png"));
    m_undoAction->setShortcut(QKeySequence::Undo);
    m_undoAction->setStatusTip("Undo previous action.");
    connect(m_undoAction, SIGNAL(triggered()), this, SLOT(undo()));

    // Redo action
    m_redoAction = new QAction("&Redo", this);
    m_redoAction->setIcon(QIcon(":images/redo.png"));
    m_redoAction->setShortcut(QKeySequence::Redo);
    m_redoAction->setStatusTip("Redo previous action.");
    connect(m_redoAction, SIGNAL(triggered()), this, SLOT(redo()));
}

// Create menu bar
void MainWindow::createMenus()
{
    // File menu
    m_fileMenu = menuBar()->addMenu("&File");
    m_fileMenu->addAction(m_newFileAction);
    m_fileMenu->addAction(m_openFileAction);
    m_fileMenu->addAction(m_saveAsAction);

    m_fileMenu->addSeparator();

    m_fileMenu->addAction(m_exitAction);

    // Edit menu
    m_editMenu = menuBar()->addMenu("&Edit");
    m_editMenu->addAction(m_copyAction);
    m_editMenu->addAction(m_pasteAction);
    m_editMenu->addAction(m_cutAction);

    m_editMenu->addSeparator();

    m_editMenu->addAction(m_undoAction);
    m_editMenu->addAction(m_redoAction);
}

// Creates a movable tool bar
void MainWindow::createToolBars()
{
    // File tool bar
    m_fileToolBar = addToolBar("&File");
    m_fileToolBar->addAction(m_newFileAction);
    m_fileToolBar->addAction(m_openFileAction);
    m_fileToolBar->addAction(m_saveAsAction);

    // Edit tool bar
    m_editToolBar = addToolBar("&Edit");
    m_editToolBar->addAction(m_copyAction);
    m_editToolBar->addAction(m_pasteAction);
    m_editToolBar->addAction(m_cutAction);

    m_editToolBar->addSeparator();

    m_editToolBar->addAction(m_undoAction);
    m_editToolBar->addAction(m_redoAction);
}

// Creates a context menu when the user clicks the RMB
void MainWindow::createContextMenu()
{
    m_textEdit->addAction(m_copyAction);
    m_textEdit->addAction(m_pasteAction);
    m_textEdit->addAction(m_cutAction);
    m_textEdit->addAction(m_undoAction);
    m_textEdit->addAction(m_redoAction);
    m_textEdit->setContextMenuPolicy(Qt::ActionsContextMenu);
}

//TODO: Verifies with the user if it is okay to continue
//bool MainWindow::okayToContinue()
//{
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
//}

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

// Open a file from the users system
void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;

    // If unable to open file, return an error message to the user
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        statusBar()->showMessage("Cannot open file: " + file.errorString(), 5000);

        return;
    }

    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    m_textEdit->setText(text);

    file.close();
}

//TODO: Save updated contents to to current file
//void MainWindow::saveFile()
//{

//}

// Saves the file with a file name and path specified by the user
void MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);

    // Display error if unable to write to file
    if (!file.open(QFile::WriteOnly | QFile::Text))
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

//Opens recently edited files
//void MainWindow::openRecentFile()
//{

//}

// Exits the application
void MainWindow::exit()
{
    QApplication::quit();
}

// Copy selected text to clipboard
void MainWindow::copyToClipboard()
{
    m_textEdit->copy();
}

// Paste text from clipboard to application
void MainWindow::pasteFromClipboard()
{
    m_textEdit->paste();
}

// Cut selected text to clipboard
void MainWindow::cutToClipboard()
{
    m_textEdit->cut();
}

// Undo previous action
void MainWindow::undo()
{
    m_textEdit->undo();
}

// Redo previous action
void MainWindow::redo()
{
    m_textEdit->redo();
}
