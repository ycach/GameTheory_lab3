#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QGroupBox>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>

#include "ResultRecord.h"


class ResultWindow : public QGroupBox{
    Q_OBJECT
public:
    ResultWindow(QString title = "Окно результата", QWidget* parent = nullptr);
    ~ResultWindow() = default;
protected:

public:
    void DellRecords();
    void AddRecord(ResultRecord* record);

private:
    QVBoxLayout* records_layout;
    std::vector<ResultRecord*> records;
};

class DelButton : public QPushButton{
public:
    DelButton(QWidget* dell_widget, const QString& text = "X", QWidget* parent = nullptr);
    ~DelButton() = default;

private:
    QWidget* del_widget;
    void DellWidget();
};
#endif // RESULTWINDOW_H
