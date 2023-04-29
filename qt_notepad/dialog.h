#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDir>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    void fileTable(const QVector<QDir>&, const QStringList&, const QVector<bool>&);

protected:
    void closeEvent(QCloseEvent*) override;

private:
    QTableWidget *tableWidget;
    QPushButton *okButton;
    QPushButton *noButton;
    QPushButton *cancelButton;
};

#endif // DIALOG_H
