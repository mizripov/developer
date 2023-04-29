#include <QDebug>
#include "notepad.h"

// public
Notepad::Notepad(QWidget *parent) : QMainWindow(parent)
{
    setWindowIcon(QIcon(":/icons/notepad.png"));
    setWindowTitle(tr("Notepad"));
    resize(1440, 1080);
    textEditTab = new QTabWidget;

    fileSystem.setRootPath(QDir::rootPath());

    textTreeView = new QTreeView;
    textTreeView->setModel(&fileSystem);

    textTreeDock = new QDockWidget;
    textTreeDock->setWidget(textTreeView);
    textTreeDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
    textTreeDock->setWindowTitle(tr("Explorer"));
    addDockWidget(Qt::LeftDockWidgetArea, textTreeDock);

    textListView = new QListView;
    textListView->setModel(&stringList);

    textActiveFilesDock = new QDockWidget;
    textActiveFilesDock->setWidget(textListView);
    textActiveFilesDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
    textActiveFilesDock->setWindowTitle(tr("Explorer Open Documents"));
    addDockWidget(Qt::RightDockWidgetArea, textActiveFilesDock);

    createMenu();

    connect(textListView, SIGNAL(clicked(QModelIndex)), this, SLOT(listViewSlot(const QModelIndex&)));
    connect(textTreeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(treeViewDoubleClickedSlot(const QModelIndex&)));

    textEditTab->tabBar()->setTabsClosable(true);

    connect(textEditTab->tabBar(), SIGNAL(tabCloseRequested(int)), SLOT(tabCloseSlot(int)));

    setCentralWidget(textEditTab);

    columnAndRowPos = new QLabel(this);
    statusBar()->addPermanentWidget(columnAndRowPos);

//    extra task
    setMouseTracking(true);
    m_plblX = new QLabel(this);
    m_plblY = new QLabel(this);
    statusBar()->addWidget(m_plblX);
    statusBar()->addWidget(m_plblY);
}

Notepad::~Notepad() {}

// protected
size_t Notepad::newNumForFile = 0;

void Notepad::loadDataFile(const QString &path)
{
    QFile file(path);
    if (not file.open(QIODevice::ReadOnly))
    {
        QErrorMessage *msg = new QErrorMessage(this);
        msg->showMessage(tr("The file with this extension don't open"));
        return;
    }
    QFileInfo fileInfo(file);
    CodeEdit *codeEdit;


    QString commentStartExpression;
    QString commentEndExpression;

    QVector<HighlightingRule> highlightingRule = loadXmlData(path, commentStartExpression, commentEndExpression);

    if (not highlightingRule.isEmpty())
    {
        codeEdit = new CodeEdit(this);
        Highlighter *hightlighter = new Highlighter(codeEdit->document(), highlightingRule);
        hightlighter->setCommentStartExspression(commentStartExpression);
        hightlighter->setCommentEndExspression(commentEndExpression);
        codeEdit->setPlainText(file.readAll());
        textEditTab->addTab(codeEdit, fileInfo.baseName() + tr(".") + fileInfo.completeSuffix());
        connect(codeEdit, SIGNAL(textChanged()), this, SLOT(tabModification()));
    }
    else
    {
        codeEdit = new CodeEdit(this);
        codeEdit->setPlainText(file.readAll());
        textEditTab->addTab(codeEdit, fileInfo.baseName() + tr(".") + fileInfo.completeSuffix());
        connect(codeEdit, SIGNAL(textChanged()), this, SLOT(tabModification()));
    }

    fileNames.push_back(QString(fileInfo.baseName() + tr(".") + fileInfo.completeSuffix()));
    fileDirs.push_back(fileInfo.path());
    stringList.setStringList(fileNames);
    textEditTab->setCurrentIndex(textEditTab->count() - 1);
    file.close();
    exitDocuments.push_back(true);
    changedDocuments.push_back(false);

    columnAndRowPos->setText(QString("Ln 1, Col 1"));
    connect(codeEdit, &CodeEdit::cursorPositionChanged, this, &Notepad::statusBarChange);
}

QVector<HighlightingRule> Notepad::loadXmlData(const QString &path,
                                               QString &commentStartExpression,
                                               QString &commentEndExpression)
{
    QFile file(tr(":/highlighter.xml"));
    QFileInfo fileInfo(path);
    QVector<HighlightingRule> highlightingRules;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QXmlStreamReader xmlStream;
        HighlightingRule rule;
        QTextCharFormat format;
        QRegularExpression pattern;

        xmlStream.setDevice(&file);
        while(not xmlStream.atEnd() and (not xmlStream.hasError()))
        {
            xmlStream.readNext();
            if (xmlStream.isStartElement())
            {
                if (xmlStream.name() == tr("syntax"))
                {
                    QXmlStreamAttribute attrib = xmlStream.attributes().at(2);
                    QString exstensions = attrib.value().toString();
                    QStringList exstensionList = exstensions.split(tr(" "));
                    bool isCodeInFile = false;

                    for (auto exstension : exstensionList)
                    {
                        if (fileInfo.completeSuffix() == exstension)
                        {
                            isCodeInFile = true;
                        }
                    }
                    if (not isCodeInFile)
                    {
                        return highlightingRules;
                    }

                    ext_list = attrib.value().toString();
                }

                if (xmlStream.name() == tr("pattern"))
                {
                    QRegularExpression reg(xmlStream.attributes().at(0).value().toString());
                    rule.pattern = reg;
                }
                if (xmlStream.name() == tr("format"))
                {
                    format.setForeground(QBrush(QColor(xmlStream.attributes().at(0).value().toString())));
                    format.setFont(xmlStream.attributes().at(1).value().toString());
                    rule.format = format;
                    highlightingRules.push_back(rule);
                }
                if (xmlStream.name() == tr("startComment"))
                {
                    commentStartExpression = xmlStream.attributes().at(0).value().toString();
                }
                if (xmlStream.name() == tr("endComment"))
                {
                    commentEndExpression = xmlStream.attributes().at(0).value().toString();
                }
            }
        }
    }

    return highlightingRules;
}

void Notepad::removeTab(int index)
{
    if (index == -1)
    {
        index = textEditTab->currentIndex();
    }

    fileDirs.removeAt(index);
    fileNames.removeAt(index);
    exitDocuments.removeAt(index);
    changedDocuments.removeAt(index);
    stringList.setStringList(fileNames);
    textEditTab->removeTab(index);
}

void Notepad::closeEvent(QCloseEvent *closeEvent)
{
    if (not exitSlot())
    {
        closeEvent->ignore();
    }
}

//extra task
void Notepad::mouseMoveEvent(QMouseEvent *pe)
{
    m_plblX->setText("X = " + QString().setNum(pe->x()));
    m_plblY->setText("Y = " + QString().setNum(pe->y()));
}

// private slots
void Notepad::newFileSlot()
{
    QString countTabs;
    countTabs.setNum(++newNumForFile);

    QString fileName = tr("new_") + countTabs + tr(".txt");
    fileNames.push_back(fileName);
    stringList.setStringList(fileNames);
    fileDirs.push_back(QDir(tr("")));
    CodeEdit *textEdit = new CodeEdit(this);

    textEditTab->addTab(textEdit, fileName);
    if (textEditTab->currentIndex() == -1)
    {
        textEditTab->setCurrentIndex(0);
    }
    else
    {
        textEditTab->setCurrentIndex(textEditTab->count() - 1);
    }
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(tabModification()));
    exitDocuments.push_back(false);
    changedDocuments.push_back(false);

    columnAndRowPos->setText(QString("Ln 1, Col 1"));
    connect(textEdit, &CodeEdit::cursorPositionChanged, this, &Notepad::statusBarChange);
}

void Notepad::openFileSlot()
{
    QString openFileName = QFileDialog::getOpenFileName(this, tr("Select file to open"),
                                                        QDir::rootPath(), ext_list);
    loadDataFile(openFileName);
}

void Notepad::saveFileSlot()
{
    QPlainTextEdit *textEdit = qobject_cast<QPlainTextEdit*>(textEditTab->currentWidget());
    if (textEdit == nullptr)
    {
        QErrorMessage *msg = new QErrorMessage(this);
        msg->showMessage(tr("File saving error"));
        return;
    }
    int index = textEditTab->currentIndex();
    if (not exitDocuments.at(index))
    {
        saveAsFileSlot();
        return;
    }
    else
    {
        QString filePath = fileDirs.at(index).absolutePath() + tr("//") + fileNames.at(index);
        QFile file(filePath);
        QTextStream text(&file);
        if (file.open(QIODevice::WriteOnly))
        {
            text << textEdit->toPlainText();
            textEditTab->setTabText(index, textEditTab->tabText(index).remove("*"));
            connect(textEdit, SIGNAL(textChanged()), this, SLOT(tabModification()));
            changedDocuments[index] = false;
        }
        else
        {
            QErrorMessage *msg = new QErrorMessage(this);
            msg->showMessage(tr("File Saving Error"));
            return;
        }
        file.close();
    }
}

void Notepad::saveAsFileSlot()
{
    QString saveFilePath = QFileDialog::getSaveFileName(this,
                                                        tr("Select a File Save ") + textEditTab->tabText(textEditTab->currentIndex()) + tr("?"),
                                                        QDir::rootPath(), ext_list);

    QPlainTextEdit *textEdit = qobject_cast<QPlainTextEdit*>(textEditTab->currentWidget());
    if (textEdit == nullptr)
    {
       QErrorMessage *msg = new QErrorMessage(this);
       msg->showMessage(tr("File Saving Error"));
       return;
    }
    QFile file(saveFilePath);
    QTextStream text(&file);
    if (file.open(QIODevice::WriteOnly))
    {
       text << textEdit->toPlainText();
       int index = textEditTab->currentIndex();
       QString newFilename = saveFilePath.section(tr("/"), -1);
       fileNames[index] = newFilename;
       saveFilePath.chop(newFilename.size() + 1);
       fileDirs[index] = QDir(saveFilePath);
       textEditTab->setTabText(index, newFilename);
       stringList.setStringList(fileNames);
       connect(textEdit, SIGNAL(textChanged()), this, SLOT(tabModification()));

       exitDocuments[index] = true;
       changedDocuments[index] = false;
    }
    else
    {
        QErrorMessage* msg = new QErrorMessage(this);
        msg->showMessage(tr("File Saving Error"));
        return;
    }
    file.close();
}

void Notepad::saveAllFileSlot()
{
    int prevIndex = textEditTab->currentIndex();
        int count = textEditTab->count();
        for (int index = 0; index < count; ++index)
        {
            textEditTab->setCurrentIndex(index);
            if (changedDocuments.at(index))
            {
                saveFileSlot();
            }
        }
        textEditTab->setCurrentIndex(prevIndex);
}

bool Notepad::closeFileSlot()
{
    if (not changedDocuments.at(textEditTab->currentIndex()))
    {
        removeTab();
        return true;
    }

    QMessageBox msgBox;
    msgBox.setText(tr("Do you want to save changes to a file ") + textEditTab->tabText(textEditTab->currentIndex()) + tr(" ?"));
    QPushButton *saveButton = msgBox.addButton(tr("Save"), QMessageBox::ActionRole);
    QPushButton *closeButton = msgBox.addButton(tr("Close"), QMessageBox::ActionRole);
    QPushButton *cancelButton = msgBox.addButton(tr("Cancel"), QMessageBox::ActionRole);

    msgBox.exec();

    if (msgBox.clickedButton() == cancelButton)
    {
        return false;
    }
    else
    {
        if (msgBox.clickedButton() == saveButton)
        {
            saveFileSlot();
        }
        removeTab();
    }
    return true;

}

void Notepad::closeAllSlot()
{
    int count = textEditTab->count();
        int index = 0;
        for (int i = 0; i < count; ++i)
        {
            textEditTab->setCurrentIndex(index);
            if (not closeFileSlot())
            {
                ++index;
            }
        }
}

bool Notepad::exitSlot()
{
    bool isExistChangedDoc = false;
    for (auto changedDoc : changedDocuments)
    {
        if (changedDoc)
        {
            isExistChangedDoc = true;
            break;
        }
    }
    if (not isExistChangedDoc)
    {
        qApp->quit();
        return true;
    }
    else
    {
        Dialog* dialog = new Dialog(this);
        dialog->setWindowTitle(tr("Save files before exiting?"));
        dialog->fileTable(fileDirs, fileNames, changedDocuments);
        dialog->setModal(true);
        int mode = dialog->exec();
        if (mode == QDialog::Accepted)
        {
            closeAllSlot();
            for (auto changedDoc : changedDocuments)
            {
                if (changedDoc)
                {
                    isExistChangedDoc = true;
                    break;
                }
            }
            if (isExistChangedDoc)
            {
                exitSlot();
            }
            qApp->quit();
            return true;
        }
        else
        {
            qApp->quit();
            return false;
        }
    }
}

void Notepad::fileTreeDockVisibility(bool visible)
{
    fileTreeAction->setChecked(visible);
}

void Notepad::activeFilesDockVisibility(bool visible)
{
    activeFilesAction->setChecked(visible);
}

void Notepad::listViewSlot(const QModelIndex &index)
{
    if (not index.isValid())
    {
        QErrorMessage *msg = new QErrorMessage(this);
        msg->showMessage(tr("Error in the Open Document Explorer"));
        return;
    }
    textEditTab->setCurrentIndex(index.row());
}

void Notepad::activeFileSlot(bool visible)
{
    if (visible)
    {
        textActiveFilesDock->show();
    }
    else
    {
        textActiveFilesDock->close();
    }
}

void Notepad::fileTreeSlot(bool visible)
{
    if (visible)
    {
        textTreeDock->show();
    }
    else
    {
        textTreeDock->close();
    }
}

void Notepad::cutSlot()
{
    QPlainTextEdit *textEdit = qobject_cast<QPlainTextEdit*>(textEditTab->currentWidget());
    if (textEdit == nullptr)
    {
        QErrorMessage *msg = new QErrorMessage(this);
        msg->showMessage(tr("Cutting error"));
        return;
    }
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(tabModification()));
    textEdit->cut();
}

void Notepad::copySlot()
{
    QPlainTextEdit *textEdit = qobject_cast<QPlainTextEdit*>(textEditTab->currentWidget());
    if (textEdit == nullptr)
    {
        QErrorMessage *msg = new QErrorMessage(this);
        msg->showMessage(tr("Copy error"));
        return;
    }
    textEdit->copy();
}

void Notepad::insertSlot()
{
    QPlainTextEdit *textEdit = qobject_cast<QPlainTextEdit*>(textEditTab->currentWidget());
    if (textEdit == nullptr)
    {
        QErrorMessage *msg = new QErrorMessage(this);
        msg->showMessage(tr("Insertion error"));
        return;
    }
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(tabModification()));
    textEdit->paste();
}

void Notepad::deleteSlot()
{
    QPlainTextEdit *textEdit = qobject_cast<QPlainTextEdit*>(textEditTab->currentWidget());
    if (textEdit == nullptr)
    {
        QErrorMessage *msg = new QErrorMessage(this);
        msg->showMessage(tr("Delite Error"));
        return;
    }
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(tabModification()));
    textEdit->textCursor().removeSelectedText();
}

void Notepad::selectSlot()
{
    QPlainTextEdit *textEdit = qobject_cast<QPlainTextEdit*>(textEditTab->currentWidget());
    if (textEdit == nullptr)
    {
        QErrorMessage *msg = new QErrorMessage(this);
        msg->showMessage(tr("Operation error \" Select All\""));
        return;
    }
    textEdit->selectAll();
}

void Notepad::tabModification()
{
    int index = textEditTab->currentIndex();
    if (not textEditTab->tabText(index).contains("*"))
    {
        textEditTab->setTabText(index, textEditTab->tabText(index) + tr("*"));
        changedDocuments[index] = true;
        statusBarChange();
    }
    else
    {
        QPlainTextEdit *textEdit = qobject_cast<QPlainTextEdit*>(textEditTab->widget(index));
        if (textEdit == nullptr)
        {
            QErrorMessage *msg = new QErrorMessage(this);
            msg->showMessage(tr("Bug fixing the widgets tab"));
            return;
        }
        disconnect(textEdit, SIGNAL(textChanged()), this, SLOT(tabModification()));
    }
}

void Notepad::tabCloseSlot(int index)
{
    if (not changedDocuments.at(index))
    {
        removeTab(index);
        return;
    }
    QMessageBox msgBox;
    msgBox.setText(tr("Do you want to save changes to a file") + textEditTab->tabText(index) + tr(" ?"));
    QPushButton* saveButton = msgBox.addButton(tr("Save"), QMessageBox::ActionRole);
    QPushButton* closeButton = msgBox.addButton(tr("Close"), QMessageBox::ActionRole);
    QPushButton* cancelButton = msgBox.addButton(tr("Cancel"), QMessageBox::ActionRole);
    msgBox.exec();
    if (msgBox.clickedButton() == saveButton)
    {
        int currentIndex = textEditTab->currentIndex();
        textEditTab->setCurrentIndex(index);
        saveFileSlot();
        removeTab(index);
        textEditTab->setCurrentIndex(currentIndex);
    }
    else if (msgBox.clickedButton() == closeButton)
    {
        removeTab(index);
    }
}

void Notepad::treeViewDoubleClickedSlot(const QModelIndex &index)
{
    if (not index.isValid())
    {
        QErrorMessage *msg = new QErrorMessage(this);
        msg->showMessage(tr("File Openning Error"));
    }
    QString path = fileSystem.filePath(index);
    if (path.contains(tr(".")))
    {
        loadDataFile(path);
    }
    else
    {
        return;
    }
}


// private
void Notepad::createMenu()
{
    fileMenu = new QMenu(tr("File"), this);

    newAction = new QAction(tr("New File"), this);
    newAction->setShortcut(Qt::CTRL | Qt::Key_N);
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFileSlot()));
    fileMenu->addAction(newAction);

    openAction = new QAction(tr("Open File"), this);
    openAction->setShortcut(Qt::CTRL | Qt::Key_O);
    connect(openAction, SIGNAL(triggered()), this, SLOT(openFileSlot()));
    fileMenu->addAction(openAction);

    saveAction = new QAction(tr("Save File"), this);
    saveAction->setShortcut(Qt::CTRL | Qt::Key_S);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveFileSlot()));
    fileMenu->addAction(saveAction);

    saveAsAction = new QAction(tr("Save File As"), this);
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAsFileSlot()));
    fileMenu->addAction(saveAsAction);

    saveAllAction = new QAction(tr("Save All Files"), this);
    saveAllAction->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_S);
    connect(saveAllAction, SIGNAL(triggered()), this, SLOT(saveAllFileSlot()));
    fileMenu->addAction(saveAllAction);

    closeAction = new QAction(tr("Close File"), this);
    connect(closeAction, SIGNAL(triggered()), this, SLOT(closeFileSlot()));
    fileMenu->addAction(closeAction);

    closeAllAction = new QAction(tr("Close All Files"), this);
    connect(closeAllAction, SIGNAL(triggered()), this, SLOT(closeAllSlot()));
    fileMenu->addAction(closeAllAction);

    exitAction = new QAction(tr("Exit"), this);
    exitAction->setShortcut(Qt::CTRL | Qt::Key_Q);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(exitSlot()));
    fileMenu->addAction(exitAction);

    menuBar()->addMenu(fileMenu);

    // correct menu
    correctMenu = new QMenu(tr("Edit"), this);

    cutAction = new QAction(tr("Cut"), this);
    cutAction->setShortcut(Qt::CTRL | Qt::Key_X);
    connect(cutAction, SIGNAL(triggered()), this, SLOT(cutSlot()));
    correctMenu->addAction(cutAction);

    copyAction = new QAction(tr("Copy"), this);
    copyAction->setShortcut(Qt::CTRL | Qt::Key_C);
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copySlot()));
    correctMenu->addAction(copyAction);


    insertAction = new QAction(tr("Insert"), this);
    insertAction->setShortcut(Qt::CTRL | Qt::Key_V);
    connect(insertAction, SIGNAL(triggered()), this, SLOT(insertSlot()));
    correctMenu->addAction(insertAction);


    deleteAction = new QAction(tr("Delete"), this);
    deleteAction->setShortcut(Qt::CTRL | Qt::Key_R);
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteSlot()));
    correctMenu->addAction(deleteAction);


    selectAllAction = new QAction(tr("Select All"), this);
    selectAllAction->setShortcut(Qt::CTRL | Qt::Key_A);
    connect(selectAllAction, SIGNAL(triggered()), this, SLOT(selectSlot()));
    correctMenu->addAction(selectAllAction);

    menuBar()->addMenu(correctMenu);

    // view menu
    viewMenu = new QMenu(tr("View"), this);

    fileTreeAction = new QAction(tr("Show Explorer"), this);
    fileTreeAction->setCheckable(true);
    fileTreeAction->setChecked(true);
    connect(fileTreeAction, SIGNAL(toggled(bool)), this, SLOT(fileTreeSlot(bool)));
    viewMenu->addAction(fileTreeAction);

    activeFilesAction = new QAction(tr("Show Open Document Explorer"), this);
    activeFilesAction->setCheckable(true);
    activeFilesAction->setChecked(true);
    connect(activeFilesAction, SIGNAL(toggled(bool)), this, SLOT(activeFileSlot(bool)));
    viewMenu->addAction(activeFilesAction);

    menuBar()->addMenu(viewMenu);

    // tool bar
    toolBar = new QToolBar(this);

    newAction->setIcon(QPixmap(tr(":/icons/newfile.png")));
    openAction->setIcon(QPixmap(tr(":/icons/open.png")));
    saveAction->setIcon(QPixmap(tr(":/icons/save.png")));
    saveAllAction->setIcon(QPixmap(tr(":icons/saveall.png")));

    toolBar->addAction(newAction);
    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(saveAllAction);


    addToolBar(Qt::TopToolBarArea, toolBar);
}

void Notepad::statusBarChange()
{
    CodeEdit *current = qobject_cast<CodeEdit*>(textEditTab->currentWidget());
    int row = current->textCursor().blockNumber() + 1;
    int column = current->textCursor().columnNumber() + 1;
    columnAndRowPos->setText(QString("Ln %1, Col %2").arg(row).arg(column));
}
