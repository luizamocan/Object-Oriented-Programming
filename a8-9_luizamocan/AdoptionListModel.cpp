#include "AdoptionListModel.h"

AdoptionListModel::AdoptionListModel(const std::vector<Dog>& dogs, QObject* parent)
    : QAbstractTableModel(parent), dogs(dogs) {}

int AdoptionListModel::rowCount(const QModelIndex&) const {
    return static_cast<int>(dogs.size());
}

int AdoptionListModel::columnCount(const QModelIndex&) const {
    return 4;  // name, breed, age, link
}

QVariant AdoptionListModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return {};

    const Dog& dog = dogs[index.row()];
    switch (index.column()) {
        case 0: return QString::fromStdString(dog.getName());
        case 1: return QString::fromStdString(dog.getBreed());
        case 2: return dog.getAge();
        case 3: return QString::fromStdString(dog.getLinkToPhoto());
        default: return {};
    }
}

QVariant AdoptionListModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return {};

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return "Name";
            case 1: return "Breed";
            case 2: return "Age";
            case 3: return "Photo Link";
            default: return {};
        }
    }

    return section + 1;
}
