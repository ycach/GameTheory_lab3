#ifndef SCHEDULEGAME_H
#define SCHEDULEGAME_H

#include <QWidget>
#include <QPainter>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>

#include "MatrixData/Matrix.h"
#include "CalcFunctions.h"

class ScheduleGame : public QWidget
{
    Q_OBJECT
public:
    explicit ScheduleGame(const QString &title,
                          QWidget *parent = nullptr);

    void SetRenderType(QPainter::RenderHints render_hints = QPainter::Antialiasing);
    void SetLegendPosition(Qt::Alignment alignment = Qt::AlignRight);
    void SetTitle(const QString &title);

    void PlotGame2xN(Matrix<double>& data);
    void PlotEnvelope(std::vector<double> lower_envelope, CalcFunc::X_Points_Dense x_dense);
    void PlotoptiumPoint(CalcFunc::Point optioum_point);
private:
    QChartView *chartView;
    QChart *chart;

    QValueAxis* axisY;
    QValueAxis* axisX;
};

#endif // SCHEDULEGAME_H
