#ifndef ADOPTIONLISTMODEL_H
#define ADOPTIONLISTMODEL_H

#include <QAbstractTableModel>
#include "Dog.h"
#include <vector>

class AdoptionListModel : public QAbstractTableModel {
    Q_OBJECT

private:
    std::vector<Dog> dogs;

public:
    explicit AdoptionListModel(const std::vector<Dog>& dogs, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

#endif // ADOPTIONLISTMODEL_H
