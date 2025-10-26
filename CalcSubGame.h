#ifndef CALCSUBGAME_H
#define CALCSUBGAME_H

#include <QPushButton>
#include "DinamicTable.h"
#include "resultwindow.h"

class CalcSubGame : public QPushButton
{
    Q_OBJECT
public:
    CalcSubGame(DinamicTable* table, ResultWindow* result_window, QString text = "Рассчитать подигру", QWidget* parent = nullptr);


private slots:
    void Calculate();

private:
    DinamicTable* table_data;
    ResultWindow* result_window;
    bool lock;
    void Lock();
    void Unlock();
};

#endif // CALCSUBGAME_H
