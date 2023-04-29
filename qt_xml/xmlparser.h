#ifndef __XML_PARSER_H__
#define __XML_PARSER_H__

#include <QAbstractItemModel>
#include <QStandardItem>
#include <QXmlStreamReader>
#include <QVariant>
#include <QFile>
#include <QFileInfo>
#include <QStack>
#include <QMessageBox>

class XmlParser : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit XmlParser(QObject *parent = nullptr);
    ~XmlParser();

    QVariant data(const QModelIndex&, int) const override;
    bool setData(const QModelIndex&, const QVariant&, int role = Qt::EditRole) override;
    QModelIndex index(int, int, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex&) const override;
    Qt::ItemFlags flags(const QModelIndex&) const override;
    QVariant headerData(int, Qt::Orientation, int) const override;

    QModelIndex firstIndex();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parrent = QModelIndex()) const override;
    bool removeRows(int, int, const QModelIndex &parent = QModelIndex()) override;

    void append(const QModelIndex&);
    void loadFile(const QString&);
    void closeAll();

private:
    void append(const QModelIndex&, QStandardItem*);

    QStandardItem *mainRoot;
    QXmlStreamReader *xmlReader;
    QPersistentModelIndex focused;
    QFont focusedFont;
};

#endif
