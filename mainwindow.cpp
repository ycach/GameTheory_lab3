#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "DinamicTable.h"
#include "ResultShower/resultwindow.h"
#include "CalcButton.h"
#include "CalcSubGame.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ResultWindow* result_window = new ResultWindow("Окно результата", this);
    result_window->setFixedHeight(600);

    DinamicTable* data_table = new DinamicTable(4, 4, 2, 1, this);

    DinamicTable* subdata_table = new DinamicTable(2, 2, 2, 1, this);

    CalcButton* calc_button = new CalcButton(data_table, result_window, "Рассчитать", this);

    CalcSubGame* calc_subgame = new CalcSubGame(subdata_table, result_window, "Рассчитать 2x2", this);

    ui->main_layout->addWidget(data_table);
    ui->main_layout->addWidget(calc_button);
    ui->main_layout->addWidget(subdata_table);
    ui->main_layout->addWidget(calc_subgame);
    ui->main_layout->addWidget(result_window);

}

MainWindow::~MainWindow()
{
    delete ui;
}
