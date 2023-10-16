#ifndef MYQSORTFILTERPROXYMODEL_H
#define MYQSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class MyQSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit MyQSortFilterProxyModel(QObject *parent = nullptr);

    virtual bool filterAcceptsRow(int source_row, const QModelIndex & source_parent) const override;

    void setRoot(const QModelIndex& root);
private:
    QModelIndex t_root;
};

#endif // MYQSORTFILTERPROXYMODEL_H
