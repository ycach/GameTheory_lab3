#include "CastomRecord.h"

#include <QVBoxLayout>
#include <QLabel>

CastomRecord::CastomRecord(ScheduleGame* game_plot,
            std::vector<std::pair<double, double>> equation_coefficients,
            CalcFunc::Point optium_point,
            const QString& title, QWidget* parent
            )
            : ResultRecord(title, parent),
            game_plot(game_plot),
            equation_coefficients(equation_coefficients),
            optium_point(optium_point)
{
    is_error = false;
}

CastomRecord::CastomRecord(const QString& title, QWidget* parent) : ResultRecord(title, parent){
    is_error = true;
}


void CastomRecord::CreateRecord(){
    QVBoxLayout* main_layout = new QVBoxLayout(this);

    if(!is_error){

        auto result_print = [this](QVBoxLayout* result_layout, std::vector<std::pair<double, double>> e_coeff, CalcFunc::Point o_point){
            for(int i = 0; i < e_coeff.size(); i++){
                QString text = QString("Уравнеие для B%1: f(x) = %2*x + %3")
                                   .arg(i+1)
                                   .arg(e_coeff[i].first)
                                   .arg(e_coeff[i].second);
                QLabel* label = new QLabel(text, this);
                result_layout->addWidget(label);
            }
            QString text = QString("Оптиум* = (%1; %2), nu = %3")
                               .arg(o_point.X)
                               .arg(1 - o_point.X)
                               .arg(o_point.Y);
            QLabel* label = new QLabel(text, this);
            result_layout->addWidget(label);
        };

        QVBoxLayout* result_game_layout = new QVBoxLayout();
        result_game_layout->addWidget(game_plot);
        result_print(result_game_layout, equation_coefficients, optium_point);
        main_layout->addLayout(result_game_layout);
    }
    else{
        QLabel* error_label = new QLabel("Игра не имеет решения в смешанных стратегиях (определитель = 0)",this);
        main_layout->addWidget(error_label);
    }

}
