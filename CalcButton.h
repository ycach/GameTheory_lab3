#ifndef CALCBUTTON_H
#define CALCBUTTON_H

#include <QPushButton>

#include "DinamicTable.h"
#include "resultwindow.h"

class CalcButton : public QPushButton
{
public:
    CalcButton(DinamicTable* table, ResultWindow* result_window, QString text = "Рассчитать", QWidget* parent = nullptr);

private slots:
    void Calculate();

private:
    DinamicTable* table_data;
    ResultWindow* result_window;
    bool lock;
    void Lock();
    void Unlock();
};

#endif // CALCBUTTON_H
