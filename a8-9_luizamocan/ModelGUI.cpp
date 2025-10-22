#include "ModelGUI.h"

ModelGUI::ModelGUI(std::vector<Dog> dogs, QObject *parent): QAbstractTableModel(parent) {
    this->dogs = dogs;
}

int ModelGUI::rowCount(const QModelIndex &parent) const {
    return dogs.size();
}

int ModelGUI::columnCount(const QModelIndex &parent) const {
    return 4; // Avem 4 coloane: Name, Breed, LinkToPhoto, Age
}

QVariant ModelGUI::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int col = index.column();

    // Verificăm dacă indexul este valid
    if (row >= dogs.size())
        return QVariant();

    const Dog &dog = dogs[row];
    if (role == Qt::DisplayRole) {
        switch (col) {
            case 0:
                return QString::fromStdString(dog.getName());
            case 1:
                return QString::fromStdString(dog.getBreed());
            case 2:
                return QString::fromStdString(dog.getLinkToPhoto());
            case 3:
                return QString::fromStdString(std::to_string(dog.getAge()));
        }
    }
    return QVariant();
}

QVariant ModelGUI::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return QString("Name");
                case 1:
                    return QString("Breed");
                case 2:
                    return QString("LinkToPhoto");
                case 3:
                    return QString("Age");
            }
        }
    }
    return QVariant();
}
