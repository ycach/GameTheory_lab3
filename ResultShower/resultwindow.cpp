#include "ResultWindow.h"

#include <QHBoxLayout>
#include <QSpacerItem>


ResultWindow::ResultWindow(QString title, QWidget* parent) : QGroupBox(title, parent){
    QVBoxLayout* main_layout = new QVBoxLayout(this);

    QScrollArea* records_box = new QScrollArea(this);
    {
        QWidget *container = new QWidget();
        records_layout = new QVBoxLayout(container);
        records_layout->setContentsMargins(0, 0, 0, 0);


        records_box->setWidgetResizable(true);
        records_box->setWidget(container);
    }

    QHBoxLayout* del_layout = new QHBoxLayout();
    {
        QSpacerItem* spacer = new QSpacerItem(20, 20, QSizePolicy::Maximum,
                                              QSizePolicy::Maximum);
        QPushButton* del_buton = new QPushButton("Отчистить все",this);
        connect(del_buton, &QPushButton::clicked, this, &ResultWindow::DellRecords);
        del_layout->addItem(spacer);
        del_layout->addWidget(del_buton);
    }

    main_layout->addWidget(records_box);
    main_layout->addLayout(del_layout);

    setMinimumHeight(300);
}
void ResultWindow::DellRecords(){
    QLayoutItem* item;
    while ((item = records_layout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    records.clear();
}


void ResultWindow::AddRecord(ResultRecord* record){

    QWidget* record_widget = new QWidget(this);
    QVBoxLayout* widget_layout = new QVBoxLayout(record_widget);
    record->InitRecord();
    widget_layout->addWidget(record);

    QHBoxLayout* del_layout = new QHBoxLayout();
    {
        QSpacerItem* spacer = new QSpacerItem(20, 20, QSizePolicy::Maximum,
                                              QSizePolicy::Maximum);
        DelButton* del_buton = new DelButton(record_widget);
        del_layout->addItem(spacer);
        del_layout->addWidget(del_buton);
    }
    widget_layout->addLayout(del_layout);

    records_layout->insertWidget(0, record_widget);
    records.push_back(record);
}


DelButton::DelButton(QWidget* dell_widget, const QString& text, QWidget* parent) : QPushButton(text, parent){
    this->del_widget = dell_widget;
    connect(this, &QPushButton::clicked, this, &DelButton::DellWidget);
}
void DelButton::DellWidget(){
    delete del_widget;
}
