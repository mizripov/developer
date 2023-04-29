#include <QDebug>

#include "xmlparser.h"

XmlParser::XmlParser(QObject *parent)
    : QAbstractItemModel(parent)
    , mainRoot(new QStandardItem{})
    , xmlReader(new QXmlStreamReader{})
    , focused()
    , focusedFont() {}

XmlParser::~XmlParser()
{
    delete xmlReader;
}

QVariant XmlParser::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    if (role == Qt::FontRole && index == focused)
    {
        return focusedFont;
    }
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }
    QStandardItem *item = static_cast<QStandardItem*>(index.internalPointer());
    return item->data(0);
}

bool XmlParser::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
    {
        return false;
    }
    auto *item = static_cast<QStandardItem*>(index.internalPointer());
    if (role == Qt::EditRole)
    {
        item->setData(value, Qt::EditRole);
        emit dataChanged(index, index, {role});
        return true;
    }
    if (role == Qt::FontRole)
    {
        focused = index;
        focusedFont = value.value<QFont>();
        return true;
    }
    return false;
}

QModelIndex XmlParser::index(int row, int column, const QModelIndex &parent) const
{
    QStandardItem *parentItem;
    if (!parent.isValid())
    {
        parentItem = mainRoot;
    }
    else
    {
        parentItem = static_cast<QStandardItem*>(parent.internalPointer());
    }
    QStandardItem *descendantItem = parentItem->child(row, column);
    if (descendantItem)
    {
        return createIndex(row, column, descendantItem);
    }
    return QModelIndex();
}

QModelIndex XmlParser::parent(const QModelIndex &descendant) const
{
    if (!descendant.isValid())
    {
        return QModelIndex();
    }
    QStandardItem *descendantItem = static_cast<QStandardItem*>(descendant.internalPointer());
    QStandardItem * parentItem = descendantItem->parent();
    if (parentItem == mainRoot || descendantItem == mainRoot)
    {
        return QModelIndex();
    }
    return createIndex(parentItem->row(), 0, parentItem);
}

Qt::ItemFlags XmlParser::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }
    return QAbstractItemModel::flags(index);
}

QVariant XmlParser::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if (section == 0)
        {
            return QString("Name");
        }
        else if (section == 1)
        {
            return QString("Value");
        }
    }
    return QVariant();
}

QModelIndex XmlParser::firstIndex()
{
    return index(0, 0);
}

int XmlParser::rowCount(const QModelIndex &parent) const
{
    QStandardItem *parentItem;
    if (parent.column() > 0)
    {
        return 0;
    }
    if (!parent.isValid())
    {
        parentItem = mainRoot;
    }
    else
    {
        parentItem = static_cast<QStandardItem*>(parent.internalPointer());
    }
    return parentItem->rowCount();
}


int XmlParser::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return static_cast<QStandardItem*>(parent.internalPointer())->columnCount();
    }
    return mainRoot->columnCount();
}

bool XmlParser::removeRows(int row, int count, const QModelIndex &parent)
{
    QModelIndex correctParent;
    if (parent.isValid())
    {
        correctParent = parent;
    }
    else
    {
        correctParent = QModelIndex();
    }
    auto begin = row;
    auto end = begin + count - 1;
    beginRemoveRows(correctParent, begin, end);
    mainRoot->removeRows(begin, count);
    endRemoveRows();
    return true;
}

void XmlParser::append(const QModelIndex &index)
{
    mainRoot->setColumnCount(2);
    if (!index.isValid())
    {
        return;
    }
    beginResetModel();
    auto *clonedItem = static_cast<QStandardItem*>(index.internalPointer())->clone();
    if (clonedItem)
    {
        if (columnCount(index) == 2)
        {
            auto second = index.model()->index(index.row(), 1, index);
            auto secondClone = static_cast<QStandardItem*>(second.internalPointer())->clone();
            mainRoot->appendRow({clonedItem, secondClone});
        }
        else
        {
            mainRoot->appendRow(clonedItem);
        }
        append(index, clonedItem);
    }
    endResetModel();
}

void XmlParser::loadFile(const QString &filename)
{
    QFile file(filename);
    QFileInfo fileInfo(filename);
    QStack<int> counterStack;
    QStack<int> layerStack;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox message(QMessageBox::Critical, tr("Error!"), tr("Fail to open file!"), QMessageBox::Ok);
        message.exec();
    }
    xmlReader->setDevice(&file);
    auto fileNode = new QStandardItem(fileInfo.fileName());
    mainRoot->appendRow(fileNode);
    mainRoot->setColumnCount(2);
    QStandardItem *currentNode = fileNode;
    QXmlStreamReader::TokenType token = xmlReader->readNext();
    int currentLayer = 0;
    while (not xmlReader->atEnd() and not xmlReader->hasError())
    {
        if (token == QXmlStreamReader::StartElement)
        {
            ++currentLayer;
            auto text = xmlReader->name().toString();
            if (text == "array")
            {
                if (layerStack.isEmpty() || currentLayer != layerStack.top())
                {
                    counterStack.append(0);
                    layerStack.append(currentLayer);
                }
                text = QString("Element %1").arg(counterStack.top() + 1);
                ++counterStack.top();
            }
            auto node = new QStandardItem(text);
            token = xmlReader->readNext();
            if (xmlReader->atEnd() or xmlReader->hasError()) break;
            if (token == QXmlStreamReader::Characters)
            {
                auto text_tmp = xmlReader->text().toString();
                auto node_tmp = new QStandardItem(text_tmp);
                QList<QStandardItem*> column = { node, node_tmp };
                currentNode->appendRow(column);
                if (text == "Name" or text == "FullName")
                {
                    qDebug() << currentNode->text();
                    setData(currentNode->index(), QVariant(text_tmp), Qt::DisplayRole);
                    currentNode->setData(QVariant(text_tmp), Qt::DisplayRole);
                }
            }
            else
            {
                currentNode->appendRow(node);
            }
            currentNode = node;
            continue;
        }
        if (token == QXmlStreamReader::EndElement)
        {
            --currentLayer;
            currentNode = currentNode->parent();
            auto text = xmlReader->name().toString();
            if (text == "array" and currentLayer + 1 != layerStack.top())
            {
                counterStack.pop();
                layerStack.pop();
            }
        }
        token = xmlReader->readNext();
    }
    if (xmlReader->hasError())
    {
        QMessageBox message(QMessageBox::Critical, tr("Parsing error!"), tr("This XML dont be displayed"), QMessageBox::Ok);
        message.exec();
    }
    file.close();
}

void XmlParser::closeAll()
{
    removeRows(0, mainRoot->rowCount(), createIndex(-1, -1, nullptr));
}

void XmlParser::append(const QModelIndex &sourceIndex, QStandardItem *item)
{
    if (not sourceIndex.isValid())
    {
        return;
    }
    for (int i = 0; i < rowCount(sourceIndex); ++i)
    {
        auto child = sourceIndex.model()->index(i, 0, sourceIndex);
        auto *clonedItem = static_cast<QStandardItem*>(child.internalPointer())->clone();
        if (clonedItem)
        {
            if (columnCount(sourceIndex) == 2)
            {
                auto second = sourceIndex.model()->index(i, 1, sourceIndex);
                if (not second.isValid()) return;
                auto secondClone = static_cast<QStandardItem*>(second.internalPointer())->clone();
                item->appendRow({clonedItem, secondClone});
            }
            else
            {
                item->appendRow(clonedItem);
            }

            append(child, clonedItem);
        }
    }
}


