#ifndef ADOPTIONLISTWINDOW_H
#define ADOPTIONLISTWINDOW_H

#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include "AdoptionListModel.h"

class AdoptionListWindow : public QWidget {
    Q_OBJECT

private:
    QTableView* tableView;
    AdoptionListModel* model;

public:
    explicit AdoptionListWindow(const std::vector<Dog>& dogs, QWidget* parent = nullptr);
    ~AdoptionListWindow();
};

#endif // ADOPTIONLISTWINDOW_H
