#ifndef CASTOMRECORD_H
#define CASTOMRECORD_H

#include <ResultRecord.h>
#include "Schedule/ScheduleGame.h"
#include "CalcFunctions.h"
class CastomRecord : public ResultRecord
{
    Q_OBJECT
public:
    CastomRecord(ScheduleGame* game_plot,
                 std::vector<std::pair<double, double>> equation_coefficients,
                 CalcFunc::Point optium_point,
                const QString& title = "Графические результаты", QWidget* parent = nullptr
                );

    CastomRecord(const QString& title = "Результат подигры", QWidget* parent = nullptr);

    void CreateRecord() override;

private:
    bool is_error;
    ScheduleGame* game_plot;
    std::vector<std::pair<double, double>> equation_coefficients;
    CalcFunc::Point optium_point;
};

#endif // CASTOMRECORD_H
