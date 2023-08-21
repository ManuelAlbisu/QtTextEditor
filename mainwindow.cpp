#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_textEdit = new QTextEdit;
    setCentralWidget(m_textEdit);

    createActions();
    createPushButtons();

    createMenus();
    createToolBars();
    createContextMenu();
    createDock();

    readSettings();

    setWindowIcon(QIcon(":/images/icon.ico"));
    setWindowTitle(tr("Text Editor"));
    setCurrentFile("");
}

MainWindow::~MainWindow()
{
    // Destroys main window
}

void MainWindow::createActions()
{
    // New file action
    m_newFileAction = new QAction(tr("&New File..."), this);
    m_newFileAction->setIcon(QIcon(":/images/new.png"));
    m_newFileAction->setShortcut(QKeySequence::New);
    m_newFileAction->setStatusTip(tr("Create a new file."));
    connect(m_newFileAction, SIGNAL(triggered()), this, SLOT(newFile()));

    // Open file action
    m_openFileAction = new QAction(tr("&Open File..."), this);
    m_openFileAction->setIcon(QIcon(":/images/new.png"));
    m_openFileAction->setShortcut(QKeySequence::Open);
    m_openFileAction->setStatusTip(tr("Open a file."));
    connect(m_openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));

    // TODO: Save action

    // Save as action
    m_saveAsAction = new QAction(tr("&Save As..."), this);
    m_saveAsAction->setIcon(QIcon(":/images/save-as.png"));
    m_saveAsAction->setShortcut(QKeySequence::SaveAs);
    m_saveAsAction->setStatusTip(tr("Save file as..."));
    connect(m_saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    // TODO: Open recent file action
    for (int i = 0; i < MaxRecentFiles; ++i)
    {
        m_recentFileActions[i] = new QAction(this);
        m_recentFileActions[i]->setVisible(false);
        connect(m_recentFileActions[i], SIGNAL(triggered()), this, SLOT(openRecentFiles()));
    }

    // Print file action
    m_printAction = new QAction(tr("&Print"), this);
    m_printAction->setIcon(QIcon(":/images/print.ico"));
    m_printAction->setShortcut(QKeySequence::Print);
    m_printAction->setStatusTip(tr("Print file."));
    connect(m_printAction, SIGNAL(triggered()), this, SLOT(printFile()));

    // Exit application action
    m_exitAction = new QAction(tr("&Exit"), this);
    m_exitAction->setIcon(QIcon(":/images/exit.ico"));
    m_exitAction->setShortcut(QKeySequence::Close);
    m_exitAction->setStatusTip(tr("Exit the application."));
    connect(m_exitAction, SIGNAL(triggered()), this, SLOT(exit()));

    // Copy to clipboard action
    m_copyAction = new QAction(tr("&Copy"), this);
    m_copyAction->setIcon(QIcon(":/images/copy.ico"));
    m_copyAction->setShortcut(QKeySequence::Copy);
    m_copyAction->setStatusTip(tr("Copy selected text to clipboard."));
    connect(m_copyAction, SIGNAL(triggered()), this, SLOT(copyToClipboard()));

    // Paste from clipboard action
    m_pasteAction = new QAction(tr("&Paste"), this);
    m_pasteAction->setIcon(QIcon(":/images/paste.png"));
    m_pasteAction->setShortcut(QKeySequence::Paste);
    m_pasteAction->setStatusTip(tr("Paste text from clipboard."));
    connect(m_pasteAction, SIGNAL(triggered()), this, SLOT(pasteFromClipboard()));

    // Cut to clipboard action
    m_cutAction = new QAction(tr("&Cut"), this);
    m_cutAction->setIcon(QIcon(":/images/cut.png"));
    m_cutAction->setShortcut(QKeySequence::Cut);
    m_cutAction->setStatusTip(tr("Cut selected text to clipboard."));
    connect(m_cutAction, SIGNAL(triggered()), this, SLOT(cutToClipboard()));

    // Undo action
    m_undoAction = new QAction(tr("&Undo"), this);
    m_undoAction->setIcon(QIcon(":/images/undo.png"));
    m_undoAction->setShortcut(QKeySequence::Undo);
    m_undoAction->setStatusTip(tr("Undo previous action."));
    connect(m_undoAction, SIGNAL(triggered()), this, SLOT(undo()));

    // Redo action
    m_redoAction = new QAction(tr("&Redo"), this);
    m_redoAction->setIcon(QIcon(":/images/redo.png"));
    m_redoAction->setShortcut(QKeySequence::Redo);
    m_redoAction->setStatusTip(tr("Redo previous action."));
    connect(m_redoAction, SIGNAL(triggered()), this, SLOT(redo()));
}

// Creates clickable buttons
void MainWindow::createPushButtons()
{
    // New file button
    m_newFileButton = new QPushButton(tr("&New File"));
    m_newFileButton->setStatusTip(tr("Open a new file."));
    connect(m_newFileButton, SIGNAL(clicked()), this, SLOT(newFile()));

    // Open file button
    m_openFileButton = new QPushButton(tr("&Open File"), this);
    m_openFileButton->setStatusTip(tr("Open a file."));
    connect(m_openFileButton, SIGNAL(clicked()), this, SLOT(openFile()));

    // Save as button
    m_saveAsButton = new QPushButton(tr("&Save As"), this);
    m_saveAsButton->setStatusTip(tr("Save file as..."));
    connect(m_saveAsButton, SIGNAL(clicked()), this, SLOT(saveAs()));

    // Print button
    m_printButton = new QPushButton(tr("&Print"), this);
    m_printButton->setStatusTip(tr("Print file."));
    connect(m_printButton, SIGNAL(clicked()), this, SLOT(printFile()));

    // Exit Button
    m_exitButton = new QPushButton(tr("&Exit"), this);
    m_exitButton->setStatusTip(tr("Exit application."));
    connect(m_exitButton, SIGNAL(clicked()), this, SLOT(exit()));
}

// Create menu bar
void MainWindow::createMenus()
{
    // File menu
    m_fileMenu = menuBar()->addMenu(tr("&File"));
    m_fileMenu->addAction(m_newFileAction);
    m_fileMenu->addAction(m_openFileAction);
    m_fileMenu->addAction(m_saveAsAction);

    m_separatorAction = m_fileMenu->addSeparator();

    for (int i = 0; i < MaxRecentFiles; ++i)
        m_fileMenu->addAction(m_recentFileActions[i]);

    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_printAction);

    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAction);

    // Edit menu
    m_editMenu = menuBar()->addMenu(tr("&Edit"));
    m_editMenu->addAction(m_copyAction);
    m_editMenu->addAction(m_pasteAction);
    m_editMenu->addAction(m_cutAction);

    m_editMenu->addSeparator();

    m_editMenu->addAction(m_undoAction);
    m_editMenu->addAction(m_redoAction);

    // View Menu
    m_viewMenu = menuBar()->addMenu("&View");
}

// Creates a movable tool bar
void MainWindow::createToolBars()
{
    // File tool bar
    m_fileToolBar = addToolBar(tr("&File"));
    m_fileToolBar->addAction(m_newFileAction);
    m_fileToolBar->addAction(m_openFileAction);
    m_fileToolBar->addAction(m_saveAsAction);

    m_fileToolBar->addSeparator();
    m_fileToolBar->addAction(m_printAction);

    // Edit tool bar
    m_editToolBar = addToolBar(tr("&Edit"));
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

//
void MainWindow::createDock()
{
    QDockWidget *m_fileDockWidget = new QDockWidget(tr("File Options"));
    m_fileDockWidget->setObjectName("fileDockWidget");
    m_fileDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, m_fileDockWidget);
    m_viewMenu->addAction(m_fileDockWidget->toggleViewAction());

    m_vLayout = new QVBoxLayout;
    m_vLayout->addWidget(m_newFileButton);
    m_vLayout->addWidget(m_openFileButton);
    m_vLayout->addWidget(m_saveAsButton);
    m_vLayout->addWidget(m_printButton);
    m_vLayout->addWidget(m_exitButton);

    m_fileButtonWidgets = new QWidget;
    m_fileButtonWidgets->setLayout(m_vLayout);
    m_fileDockWidget->setWidget(m_fileButtonWidgets);
}

void MainWindow::readSettings()
{
    QSettings settings("ARC Software", tr("Text Editor"));

    restoreGeometry(settings.value("geometry").toByteArray());

    m_recentFiles = settings.value("m_recentFiles").toStringList();
    updateRecentFileActions();
}

// TODO: Verifies with the user if it is okay to continue
//bool MainWindow::okayToContinue()
//{
    //if (isWindowModified())
        //{
            //int r = QMessageBox::warning(this, "Text Editor", "The document has been modified.\n"
                                         //"Do you want to save your changes?",
                                         //QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

            //if (r == QMessageBox::Yes)
                //return saveFile();
            //else if (r == QMessageBox::Cancel)
                //return false;
        //}

    //return true;
//}

// Removes the files path from the file name
QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

// Sets the current file to the one being edited
void MainWindow::setCurrentFile(const QString &fileName)
{
    m_currentFile = fileName;
    setWindowModified(false);
    QString shownName = "Untitled";

    if (!m_currentFile.isEmpty())
    {
        shownName = strippedName(m_currentFile);
        m_recentFiles.removeAll(m_currentFile);
        m_recentFiles.prepend(m_currentFile);
        updateRecentFileActions();
    }
}

// Checks if file is read-only
bool MainWindow::readFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, tr("Text Editor"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));

            return false;
    }

    return true;
}

// Loads files
bool MainWindow::loadFile(const QString &fileName)
{
    if (!readFile(fileName))
    {
            statusBar()->showMessage(tr("Loading canceled"), 5000);

            return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 5000);

    return true;
}

// Creates a new file
// TODO: implement okayToContinue() method
void MainWindow::newFile()
{
    //if (okayToContinue())
    //{
        //m_currentFile.clear();
        //m_textEdit->setText(QString());
    //}

    m_currentFile.clear();
    m_textEdit->setText(QString());
}

// Open a file from the users system
void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open the file"));
    QFile file(fileName);
    m_currentFile = fileName;

    // If unable to open file, return an error message to the user
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
            statusBar()->showMessage(tr("Cannot open file: ") + file.errorString(), 5000);

        return;
    }

    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    m_textEdit->setText(text);

    file.close();
}

// TODO: Save updated contents to to current file
//void MainWindow::saveFile()
//{

//}

// Saves the file with a file name and path specified by the user
void MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as"));
    QFile file(fileName);

    // Display error if unable to write to file
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        statusBar()->showMessage(tr("Cannot save file: ") + file.errorString(), 5000);

            return;
    }

    m_currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = m_textEdit->toPlainText();
    out << text;

    file.close();
}

// TODO: Opens recently edited files
// TODO: Implement okayToContinue()
void MainWindow::openRecentFiles()
{
    QAction *action = qobject_cast<QAction *>(sender());

    if (action)
            loadFile(action->data().toString());
}

// Updates entries in file menu
void MainWindow::updateRecentFileActions()
{
    QMutableStringListIterator i(m_recentFiles);

    while (i.hasNext())
    {
            if (!QFile::exists(i.next()))
                i.remove();
    }

    for (int j = 0; j < MaxRecentFiles; ++j)
    {
            if (j < m_recentFiles.count())
            {
                QString text = tr("&%1 %2")
                                   .arg(j + 1)
                                   .arg(strippedName(m_recentFiles[j]));
                m_recentFileActions[j]->setText(text);
                m_recentFileActions[j]->setData(m_recentFiles[j]);
                m_recentFileActions[j]->setVisible(true);
            }
            else
                m_recentFileActions[j]->setVisible(false);
    }

    m_separatorAction->setVisible(!m_recentFiles.isEmpty());
}

// TODO: Prints contents of current file
void MainWindow::printFile()
{
    QPrinter printer;
    printer.setPrinterName(tr("Printer Name"));
    QPrintDialog pDialog(&printer, this);

    if (pDialog.exec() == QDialog::Rejected)
    {
            statusBar()->showMessage(tr("Cannot access printer"), 5000);

            return;
    }

    m_textEdit->print(&printer);
}

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
