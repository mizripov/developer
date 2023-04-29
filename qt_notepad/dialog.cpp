#include "dialog.h"

Dialog::Dialog(QWidget *parent)
{
    okButton = new QPushButton(tr("Ok"));
    noButton = new QPushButton(tr("No"));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(noButton);

    tableWidget = new QTableWidget;
    tableWidget->setColumnCount(2);
    tableWidget->setHorizontalHeaderLabels(QStringList() << tr("Name") << tr("Path"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tableWidget);
    mainLayout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(noButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(okButton, SIGNAL(clicked()), parent, SLOT(onSaveAllActTriggered()));

    setLayout(mainLayout);
}

void Dialog::fileTable(const QVector<QDir> &fileDirs,
                       const QStringList &fileNames,
                       const QVector<bool> &isChangedDoc)
{
    int tableIndex = 0;
    for (int i = 0; i < fileDirs.count(); ++i)
    {
        if (isChangedDoc.at(i))
        {
            tableWidget->insertRow(tableIndex);
            tableWidget->setItem(tableIndex, 0, new QTableWidgetItem(fileNames[i], Qt::DisplayRole));
            tableWidget->setItem(tableIndex, 1, new QTableWidgetItem(fileDirs[i].path(), Qt::DisplayRole));
            ++tableIndex;
        }
    }
    tableWidget->verticalHeader()->setStretchLastSection(true);
}

void Dialog::closeEvent(QCloseEvent *event)
{
    emit done(-1);
}
