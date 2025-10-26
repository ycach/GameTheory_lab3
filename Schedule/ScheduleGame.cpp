#include "ScheduleGame.h"

#include <QVBoxLayout>
#include  <QtCharts/QScatterSeries>


ScheduleGame::ScheduleGame(const QString &title,
                           QWidget *parent) : QWidget(parent){

    QVBoxLayout *layout = new QVBoxLayout(this);

    chart = new QChart();
    setFixedSize(QSize(800, 400));
    chart->setTitle(title);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(chartView);
}


void ScheduleGame::SetRenderType(QPainter::RenderHints render_hints){
    chartView->setRenderHints(render_hints);
}
void ScheduleGame::SetLegendPosition(Qt::Alignment alignment){
    chart->legend()->setAlignment(alignment);
}
void ScheduleGame::SetTitle(const QString &title){
    chart->setTitle(title);
}

void ScheduleGame::PlotGame2xN(Matrix<double>& data){
    chart->removeAllSeries();

    if(data.GetRowsCount() != 2){
        data.Transpose();
    }

    if(data.GetRowsCount() != 2){
        return;
    }
    //OX
    axisX = new QValueAxis();
    axisX->setTitleText("Стратегии игрока 1");
    axisX->setRange(0, 1);
    axisX->setLabelFormat("%.1f");
    // OY
    double max_value = data[0][0];

    double min_value = data[0][0];
    for (int i = 0; i < data.GetRowsCount(); i++) {
        double max_value_row = data[i][0];
        double min_value_row = data[i][0];
        for (int j = 0; j < data.GetColumnsCount(); j++) {
            if(data[i][j] > max_value_row)
                max_value_row = data[i][j];
            if(data[i][j] < min_value_row)
                min_value_row = data[i][j];
        }
        if(max_value < max_value_row)
            max_value = max_value_row;

        if(min_value > min_value_row)
            min_value = min_value_row;
    }

    double margin = (max_value - min_value) * 0.1;
    double minY = min_value - margin;
    double maxY = max_value + margin;

    axisY = new QValueAxis();
    axisY->setTitleText("Выигрыш игрока 2");
    axisY->setRange((minY < 0) ? minY - 0.5 : 0, maxY + 0.5);
    axisY->setLabelFormat("%d");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    for (int j = 0; j < data.GetColumnsCount(); j++) {
        QLineSeries *series = new QLineSeries();
        series->setName(QString("B%1").arg(j + 1));

        for (int i = 0; i < data.GetRowsCount(); i++) {
            series->append(i, data[i][j]);
        }

        series->setPointsVisible(true);
        series->setMarkerSize(8);
        chart->addSeries(series);
    }

    for (QAbstractSeries *s : chart->series()) {
        s->attachAxis(axisX);
        s->attachAxis(axisY);
    }
}

void ScheduleGame::PlotEnvelope(std::vector<double> lower_envelope, CalcFunc::X_Points_Dense x_dense){
    if (!axisX || !axisY) {
        return;
    }

    //Lower envelope
    QLineSeries *envelope = new QLineSeries();
    envelope->setName("Нижняя огибающая");
    QPen pen_env = envelope->pen();
    pen_env.setWidth(2);
    pen_env.setStyle(Qt::DashLine);
    pen_env.setColor(Qt::black);
    envelope->setPen(pen_env);

    for (int j = 0; j < x_dense.x_dense.size(); j++) {
        envelope->append(x_dense.x_dense[j], lower_envelope[j]);
    }

    chart->addSeries(envelope);
    envelope->attachAxis(axisX);
    envelope->attachAxis(axisY);


}

void ScheduleGame::PlotoptiumPoint(CalcFunc::Point optioum_point){

    if (!axisX || !axisY) {
        return;
    }

    //Optium point
    QScatterSeries *optPoint = new QScatterSeries();
    optPoint->setName(QString("Оптимум: ν = %1").arg(optioum_point.Y, 0, 'f', 3));
    optPoint->setMarkerSize(10);
    optPoint->setColor(Qt::red);
    optPoint->append(optioum_point.X, optioum_point.Y);

    chart->addSeries(optPoint);
    optPoint->attachAxis(axisX);
    optPoint->attachAxis(axisY);


    //price line
    QLineSeries *priceLine = new QLineSeries();
    priceLine->setName(QString("Цена игры ν = %1").arg(optioum_point.Y, 0, 'f', 3));
    QPen pen_price = priceLine->pen();
    pen_price.setWidth(2);
    pen_price.setStyle(Qt::DashDotLine);
    pen_price.setColor(Qt::darkGreen);
    priceLine->setPen(pen_price);
    priceLine->append(0.0, optioum_point.Y);
    priceLine->append(1.0, optioum_point.Y);

    chart->addSeries(priceLine);
    priceLine->attachAxis(axisX);
    priceLine->attachAxis(axisY);


    //optium h
    QLineSeries *verticalLine = new QLineSeries();
    verticalLine->setName(QString("x* = %1").arg(optioum_point.X, 0, 'f', 3));
    QPen pen_vert = verticalLine->pen();
    pen_vert.setWidth(1);
    pen_vert.setStyle(Qt::DashLine);
    pen_vert.setColor(Qt::blue);
    verticalLine->setPen(pen_vert);

    verticalLine->append(optioum_point.X, 0);
    verticalLine->append(optioum_point.X, optioum_point.Y);

    chart->addSeries(verticalLine);
    verticalLine->attachAxis(axisX);
    verticalLine->attachAxis(axisY);
}
