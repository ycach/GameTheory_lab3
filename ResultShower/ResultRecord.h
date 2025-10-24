#ifndef RESULTRECORD_H
#define RESULTRECORD_H

#include <QGroupBox>

class ResultRecord : public QGroupBox{
public:
    ResultRecord(const QString& title = "Результат расчета", QWidget* parent = nullptr);
    ~ResultRecord() = default;
    virtual void CreateRecord() = 0;
    void InitRecord();
};

#endif // RESULTRECORD_H
