#include "myqsortfilterproxymodel.h"

#include <QStandardItemModel>

MyQSortFilterProxyModel::MyQSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{

}

bool MyQSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (source_parent == t_root)
    {
        // always filter accept children of rootitem, since we want to filter their children
        return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
    }
    return true;
}

void MyQSortFilterProxyModel::setRoot(const QModelIndex &root)
{
    t_root = root;
}
