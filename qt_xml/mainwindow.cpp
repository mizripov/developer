#include <QTreeWidgetItem>
#include <QDebug>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto menuFile = new QMenu{ tr("Menu") };
    auto actionOpenFile = new QAction{ tr("Open file"), this };
    menuFile->addAction(actionOpenFile);
    connect(actionOpenFile, SIGNAL(triggered()), this, SLOT(openFileMenu()));

    auto actionCloseAllFiles = new QAction{ tr("Close all files"), this };
    menuFile->addAction(actionCloseAllFiles);
    connect(actionCloseAllFiles, SIGNAL(triggered()), this, SLOT(closeAllFileMenu()));

    auto actionExit = new QAction{ tr("Exit"), this };
    menuFile->addAction(actionExit);
    connect(actionExit, SIGNAL(triggered()), this, SLOT(exitMenu()));

    menuBar()->addMenu(menuFile);
    tabWidget = new QTabWidget();
    treeView = new QTreeView(tabWidget);
    treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    parser = new XmlParser(treeView);
    treeView->setModel(parser);
    connect(treeView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenu(QPoint)));
    tabWidget->addTab(treeView, "Tab 1");
    tabWidget->setCurrentIndex(tabWidget->indexOf(treeView));

    resize(640, 480);
    setCentralWidget(tabWidget);
}

void MainWindow::openFileMenu()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose file to open"), QDir::homePath());
    parser->loadFile(filename);
    treeView->reset();
    QFont font;
    font.setBold(true);
    parser->setData(parser->firstIndex(), font, Qt::FontRole);
}

void MainWindow::closeAllFileMenu()
{
    parser->closeAll();
    treeView->reset();

    static int i = 1;
    tabWidget->setCurrentIndex(i);
    while (tabWidget->currentIndex())
    {
        tabWidget->removeTab(tabWidget->currentIndex());
        tabWidget->setCurrentIndex(++i);
    }
    i = 1;
}

void MainWindow::exitMenu()
{
    close();
}

void MainWindow::contextMenu(const QPoint &position)
{
    if (treeView->currentIndex().parent() == treeView->rootIndex())
    {
        QMenu *menu = new QMenu(this);
        auto actionActive = new QAction{ tr("Close"), this };
        menu->addAction(actionActive);
        connect(actionActive, &QAction::triggered, this, &MainWindow::closeFile);
        if (parser->rowCount() >= 2)
        {
            auto newTab = new QAction{ tr("New tab"), this };
            menu->addAction(newTab);
            connect(newTab, &QAction::triggered, this, &MainWindow::newTab);
        }
        menu->popup(treeView->viewport()->mapToGlobal(position));
    }
}

void MainWindow::closeFile()
{
    auto *newTreeView = qobject_cast<QTreeView*>(tabWidget->currentWidget());
    auto *parser = qobject_cast<XmlParser*>(newTreeView->model());
    auto currentIndex = newTreeView->currentIndex();
    parser->removeRow(currentIndex.row());
    treeView->reset();
}

void MainWindow::newTab()
{
    auto *currentTreeView = getCurrentTabView();
    auto *currentModel = getXmlModel(currentTreeView);
    auto currentIndex = currentTreeView->currentIndex();

    auto *newTreeView = createNewTab("Tab ");
    auto *newModel = getXmlModel(newTreeView);
    newTreeView->setModel(newModel);
    newModel->append(currentIndex);
    QFont font;
    font.setBold(true);
    newModel->setData(newModel->index(0,0), font, Qt::FontRole);
    currentModel->removeRow(currentIndex.row());
}

QTreeView *MainWindow::getCurrentTabView()
{
    return qobject_cast<QTreeView*>(tabWidget->currentWidget());
}

XmlParser *MainWindow::getXmlModel(QTreeView *view)
{
    return dynamic_cast<XmlParser*>(view->model());
}

QTreeView *MainWindow::createNewTab(const QString &title)
{
    auto *treeView = new QTreeView(tabWidget);
    auto *model = new XmlParser(treeView);
    treeView->setModel(model);
    static int i = 1;
    tabWidget->addTab(treeView, title + QString::number(++i));
    tabWidget->setCurrentIndex(tabWidget->indexOf(treeView));
    return treeView;
}
