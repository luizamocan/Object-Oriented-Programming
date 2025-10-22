

#ifndef MODELGUI_H
#define MODELGUI_H
#include "Dog.h"
#include <QAbstractTableModel>
class ModelGUI : public QAbstractTableModel {

    Q_OBJECT
    public:
    std::vector<Dog> dogs;
    ModelGUI(std::vector<Dog> dogs,QObject *parent=nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};
#endif //MODELGUI_H
