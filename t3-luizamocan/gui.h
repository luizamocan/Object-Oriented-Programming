#pragma once
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "Controller.h"
#include "domain.h"

class GUI : public QWidget {
    Q_OBJECT

private:
    Controller& controller;

    QListWidget* listWidget;
    QLineEdit* filter_probability;
    QPushButton* filter_button;

    QLineEdit* description_filter;
    QLineEdit* start_time_filter;
    QPushButton* intervals_and_total_time_button;
    QListWidget* intervals_list;
    QLineEdit* total_hours;

    void populateMainList(const std::vector<Interval>& intervals);
    void populateIntervalsList(const std::vector<Interval>& intervals);

    private slots:
        void filter();
    void intervals_and_total_time();

public:
    explicit GUI(Controller& controller, QWidget* parent = nullptr);
};
