#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>

#include "xmlparser.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void openFileMenu();
    void closeAllFileMenu();
    void exitMenu();
    void contextMenu(const QPoint&);
    void closeFile();
    void newTab();
    QTreeView *getCurrentTabView();
    static XmlParser *getXmlModel(QTreeView*);
    QTreeView *createNewTab(const QString&);

private:
    XmlParser *parser;
    QTreeView *treeView;
    QTabWidget *tabWidget;
    QFile *currentFile;
};

#endif // MAINWINDOW_H
