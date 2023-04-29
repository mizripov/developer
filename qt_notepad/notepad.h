#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QTabWidget>
#include <QStatusBar>
#include <QTabBar>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QApplication>
#include <QDockWidget>
#include <QTreeView>
#include <QListView>
#include <QFileSystemModel>
#include <QStringListModel>
#include <QErrorMessage>
#include <QFileDialog>
#include <QXmlStreamAttribute>
#include <QTextStream>
#include <QMessageBox>
#include <QLabel>
#include <QTextCursor>
#include <QDebug>

#include "dialog.h"
#include "linenumberarea.h"
#include "highlighter.h"

struct HighlightingRule;

class Notepad : public QMainWindow
{
    Q_OBJECT
    friend class Dialog;

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

protected:
    static size_t newNumForFile;
    QToolBar *toolBar;
    QFileSystemModel fileSystem;
    QStringList fileNames;
    QStringListModel stringList;
    QVector<QDir> fileDirs;

    void loadDataFile(const QString&);
    QVector<HighlightingRule> loadXmlData(const QString&, QString&, QString&);
    void removeTab(int index = -1);

    QVector<bool> exitDocuments;
    QVector<bool> changedDocuments;

    void closeEvent(QCloseEvent*) override;

//    extra task
    virtual void mouseMoveEvent(QMouseEvent *pe);

private slots:
    void newFileSlot();
    void openFileSlot();
    void saveFileSlot();
    void saveAsFileSlot();
    void saveAllFileSlot();
    bool closeFileSlot();
    void closeAllSlot();
    bool exitSlot();

    void fileTreeDockVisibility(bool);
    void activeFilesDockVisibility(bool);
    void listViewSlot(const QModelIndex&);

    void activeFileSlot(bool);
    void fileTreeSlot(bool);

    void cutSlot();
    void copySlot();
    void insertSlot();
    void deleteSlot();
    void selectSlot();


    void tabModification();
    void tabCloseSlot(int);
    void treeViewDoubleClickedSlot(const QModelIndex&);

private:
    QTabWidget *textEditTab;

    QDockWidget *textTreeDock;
    QTreeView *textTreeView;
    QDockWidget *textActiveFilesDock;
    QListView *textListView;

    QMenu *fileMenu;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *saveAllAction;
    QAction *closeAction;
    QAction *closeAllAction;
    QAction *exitAction;

    QMenu *correctMenu;
    QAction *cutAction;
    QAction *copyAction;
    QAction *insertAction;
    QAction *deleteAction;
    QAction *selectAllAction;

    QMenu *viewMenu;
    QAction *fileTreeAction;
    QAction *activeFilesAction;

    QLabel *columnAndRowPos;
    QString ext_list;

    void createMenu();

    void statusBarChange();

//    extra task
    QLabel *m_plblX;
    QLabel *m_plblY;
};

#endif // NOTEPAD_H
