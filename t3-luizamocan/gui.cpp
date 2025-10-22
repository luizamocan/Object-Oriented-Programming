#include "gui.h"
#include <QMessageBox>

GUI::GUI(Controller &controller, QWidget *parent)
    : QWidget(parent), controller(controller) {
    this->controller.readFromFile();

    listWidget = new QListWidget;

    filter_probability = new QLineEdit;
    filter_button = new QPushButton("Filter");

    description_filter = new QLineEdit;
    start_time_filter = new QLineEdit;
    intervals_and_total_time_button = new QPushButton("Show intervals and total time");

    intervals_list = new QListWidget;
    total_hours = new QLineEdit;
    total_hours->setReadOnly(true);


    QHBoxLayout* button_layout = new QHBoxLayout();
    button_layout->addWidget(description_filter);
    button_layout->addWidget(start_time_filter);
    button_layout->addWidget(intervals_and_total_time_button);


    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addWidget(listWidget);
    main_layout->addWidget(filter_probability);
    main_layout->addWidget(filter_button);
    main_layout->addLayout(button_layout);
    main_layout->addWidget(intervals_list);
    main_layout->addWidget(total_hours);

    this->setLayout(main_layout);

    populateMainList(controller.getIntervals());

    QObject::connect(filter_button, &QPushButton::clicked, this, &GUI::filter);
    QObject::connect(intervals_and_total_time_button, &QPushButton::clicked, this, &GUI::intervals_and_total_time);
}

void GUI::populateMainList(const std::vector<Interval>& intervals) {
    listWidget->clear();
    for (const Interval& interval : intervals) {
        listWidget->addItem(QString::fromStdString(interval.toString()));
    }
}

void GUI::populateIntervalsList(const std::vector<Interval>& intervals) {
    intervals_list->clear();
    for (const Interval& interval : intervals) {
        intervals_list->addItem(QString::fromStdString(interval.toString()));
    }
}

void GUI::filter() {
    bool ok;
    int prob = this->filter_probability->text().toInt(&ok);
    if (!ok) return;

    std::vector<Interval> result;
    for (const Interval& interval : this->controller.getIntervals()) {
        if (interval.getProbability() <= prob) {
            result.push_back(interval);
        }
    }

    populateMainList(result);
}

void GUI::intervals_and_total_time() {
    std::string description = this->description_filter->text().toStdString();
    bool ok;
    int start_hour = this->start_time_filter->text().toInt(&ok);
    if (!ok) return;

    std::vector<Interval> result;
    int total = 0;
    for (const Interval& interval : this->controller.getIntervals()) {
        if (interval.getStartHour() >= start_hour &&
            interval.getDescription() == description) {
            total += interval.getEndHour() - interval.getStartHour();
            result.push_back(interval);
        }
    }

    this->total_hours->setText(QString::number(total));
    populateIntervalsList(result);

}
