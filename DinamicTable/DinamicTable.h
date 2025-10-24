#ifndef DINAMICTABLE_H
#define DINAMICTABLE_H
#include <QTableWidget>
#include <QPushButton>
#include "MatrixData/Matrix.h"

class DinamicTable : public QTableWidget{
    Q_OBJECT
public:
    DinamicTable(int active_rows = 4, int active_columns = 4, int title_rows = 2, int title_cols = 1, QWidget* parent = nullptr);
    ~DinamicTable() = default;

    virtual void AddActiveRow();
    virtual void RemoveActiveRow(int rowIndex);
    virtual void AddActiveColumn();
    virtual void RemoveActiveColumn(int colIndex);

    int GetTitleRows() const;
    int GetTitleColumns() const;

    int GetDataRows() const;
    int GetDataColumns() const;

    Matrix<double> GetData();

signals:
    void SignalColumnRemoved(int removedIndex);
    void SignalRowRemoved(int removedIndex);

    void ErrorGetData();

protected:
    int active_rows;
    int active_columns;

    int titles_rows;
    int titles_columns;

    virtual void CreateTitlesStile();
    void CreateAddButtons();
private:
    bool ValidItem(QTableWidgetItem* item);

};

class Title : public QWidget{
    Q_OBJECT
public:
    Title(int index, bool is_column, DinamicTable* parent = nullptr);
    ~Title() = default;


private:

    void UpdateIndex(int index);

    int index;
    bool is_column;
    DinamicTable* parent_table;
    QPushButton* dell_button;
};
#endif // DINAMICTABLE_H
