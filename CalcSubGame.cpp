#include "CalcSubGame.h"

#include "CalcFunctions.h"
#include "Schedule/ScheduleGame.h"
#include "CastomRecord/CastomRecord.h"

CalcSubGame::CalcSubGame(DinamicTable* table, ResultWindow* result_window, QString text, QWidget* parent) : QPushButton(text, parent){
    this->table_data = table;
    this->result_window = result_window;

    lock = false;

    connect(table_data, &DinamicTable::ErrorGetData, this, &CalcSubGame::Lock);
    connect(this, &QPushButton::clicked, this, &CalcSubGame::Calculate);
}

void CalcSubGame::Lock(){
    lock = true;
}
void CalcSubGame::Unlock(){
    lock = false;
}

void CalcSubGame::Calculate(){
    Matrix<double> data = table_data->GetData();
    if(!lock){
        CalcFunc::X_Points_Dense points = CalcFunc::X_Points_Dense();

        /*double acrossing = CalcFunc::Acrosing2x2(data);

        if(acrossing < CalcFunc::ACCURACY){
             CastomRecord* new_record = new CastomRecord(
                "ошибка результатов", result_window);
            result_window->AddRecord(new_record);
        }else{*/
            ScheduleGame* game_schedule = new ScheduleGame("Подигра игра");
            std::vector<double> upper_envelope = CalcFunc::GetUpperEnvelope(data, points);
            CalcFunc::Point optium_point_game = CalcFunc::GetOptium(CalcFunc::Optium::Upper, upper_envelope,  points);
            std::vector<std::pair<double, double>> equation_coefficients_game = CalcFunc::GetEquationCoefficients(data);
            game_schedule->PlotGame2xN(data);
            game_schedule->PlotEnvelope(upper_envelope, points);
            game_schedule->PlotoptiumPoint(optium_point_game);

            CastomRecord* new_record = new CastomRecord(
                game_schedule, equation_coefficients_game, optium_point_game,
                "Графические результаты игры", result_window
                );

            result_window->AddRecord(new_record);

        //}
    }
    lock = false;
}
