#include "AdoptionListWindow.h"
#include <QHeaderView>
AdoptionListWindow::AdoptionListWindow(const std::vector<Dog>& dogs, QWidget* parent)
    : QWidget(parent) {
    setWindowTitle("Adoption List");
    resize(600, 400);

    tableView = new QTableView(this);
    model = new AdoptionListModel(dogs, this);
    tableView->setModel(model);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(tableView);
    setLayout(layout);
}

AdoptionListWindow::~AdoptionListWindow() {}
