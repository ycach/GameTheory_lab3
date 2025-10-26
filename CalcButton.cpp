#include "CalcButton.h"
#include "CastomRecord/CastomRecord.h"
#include "Schedule/ScheduleGame.h"

CalcButton::CalcButton(DinamicTable* table, ResultWindow* result_window, QString text, QWidget* parent) :
            QPushButton(text, parent),
            table_data(table),
            result_window(result_window)
{
    lock = false;

    connect(table, &DinamicTable::ErrorGetData, this, &CalcButton::Lock);
    connect(this, &QPushButton::clicked, this, &CalcButton::Calculate);
}


void CalcButton::Lock(){
    lock = true;
}
void CalcButton::Unlock(){
    lock = false;
}

void CalcButton::Calculate(){
    Matrix<double> data = table_data->GetData();
    if(!lock){
        CalcFunc::X_Points_Dense points = CalcFunc::X_Points_Dense();

        ScheduleGame* game_schedule = new ScheduleGame("Основная игра");
        std::vector<double> lower_envelope = CalcFunc::GetLowerEnvelope(data, points);
        CalcFunc::Point optium_point_game = CalcFunc::GetOptium(CalcFunc::Optium::Lower, lower_envelope,  points);
        std::vector<std::pair<double, double>> equation_coefficients_game = CalcFunc::GetEquationCoefficients(data);
        game_schedule->PlotGame2xN(data);
        game_schedule->PlotEnvelope(lower_envelope, points);
        game_schedule->PlotoptiumPoint(optium_point_game);

        CastomRecord* new_record = new CastomRecord(
            game_schedule, equation_coefficients_game, optium_point_game,
            "Графические результаты игры", result_window
            );
        result_window->AddRecord(new_record);

    }
    lock = false;
}
