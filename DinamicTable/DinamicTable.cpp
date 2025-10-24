#include "DinamicTable.h"
#include <QHeaderView>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTimer>

DinamicTable::DinamicTable(int active_rows, int active_columns, int title_rows, int title_cols, QWidget* parent) : QTableWidget(parent){
    this->active_rows = active_rows;
    this->active_columns = active_columns;
    this->titles_rows = title_rows;
    this->titles_columns = title_cols;

    verticalHeader()->setVisible(false);
    horizontalHeader()->setVisible(false);

    resizeColumnsToContents();
    resizeRowsToContents();

    CreateTitlesStile();
}


void DinamicTable::CreateTitlesStile(){
    setRowCount(active_rows + titles_rows);
    setColumnCount(active_columns + titles_columns);

    //merging the first cells of a column
    if (rowCount() < titles_rows || columnCount() < titles_columns) {
        qWarning() << "Таблица слишком мала для стиля заголовков";
        return;
    }
    setSpan(0, 0, titles_rows, 1);
    QTableWidgetItem *leftTitle = new QTableWidgetItem("Заголовок слева");
    leftTitle->setTextAlignment(Qt::AlignCenter);
    setItem(0, 0, leftTitle);


    //merging cells of the first row
    int columnsToMerge = columnCount() - titles_columns;
    if (columnsToMerge > 0) {
        setSpan(0, titles_columns, 1, columnsToMerge);

        QTableWidgetItem *topTitle = new QTableWidgetItem("Основной заголовок");
        topTitle->setTextAlignment(Qt::AlignCenter);
        setItem(0, 1, topTitle);
    }

    //assignment of columns subheadings
    for (int col = titles_columns; col < active_columns + titles_columns; col++) {
        Title *titleWidget = new Title(col , true, this);
        setCellWidget(1 , col, titleWidget);
    }

    //assignment of rows subheadings
    for (int row = titles_rows; row < active_rows + titles_rows; row++) {
        Title *titleWidget = new Title(row , false, this);
        setCellWidget(row, 0, titleWidget);
    }

    CreateAddButtons();

}
void DinamicTable::CreateAddButtons()
{
    if (rowCount() == 0) setRowCount(1);
    if (columnCount() == 0) setColumnCount(1);

    int newRow = rowCount();
    int newCol = columnCount();

    insertRow(newRow);
    insertColumn(newCol);

    if (newCol > 1) {
        setSpan(newRow, 1, 1, newCol - 1);

        QTableWidgetItem *item = new QTableWidgetItem("—");
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        setItem(newRow, 1, item);
    }

    if (newRow > 1) {
        setSpan(1, newCol, newRow - 1, 1);

        QTableWidgetItem *item = new QTableWidgetItem("—");
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        setItem(1, newCol, item);
    }

    QPushButton *btnAddRow = new QPushButton("+", this);
    btnAddRow->setToolTip("Добавить строку");
    connect(btnAddRow, &QPushButton::clicked, this, &DinamicTable::AddActiveRow);
    setCellWidget(newRow, 0, btnAddRow);

    QPushButton *btnAddCol = new QPushButton("+", this);
    btnAddCol->setToolTip("Добавить столбец");
    connect(btnAddCol, &QPushButton::clicked, this, &DinamicTable::AddActiveColumn);
    setCellWidget(0, newCol, btnAddCol);

    QPushButton *btnAddBoth = new QPushButton("+", this);
    btnAddBoth->setToolTip("Добавить строку и столбец");
    connect(btnAddBoth, &QPushButton::clicked, this, [this]() {
        AddActiveRow();
        AddActiveColumn();
    });
    setCellWidget(newRow, newCol, btnAddBoth);
}

void DinamicTable::AddActiveRow(){
    active_rows++;
    if (rowCount() < titles_rows + 1) return;

    int insert_row = rowCount() - 1;
    insertRow(insert_row );

    Title *titleWidget = new Title(insert_row , false, this);
    setCellWidget(insert_row , 0, titleWidget);

    for (int col = 1; col < columnCount() - 1; ++col) {
        setItem(insert_row , col, new QTableWidgetItem(""));
    }

    int lastCol = columnCount() - 1;
    int dataRowsInLastCol = rowCount()  - 2;

    if (dataRowsInLastCol > 0) {
        setSpan(1,lastCol, 1, 1);
        setSpan(1,lastCol, dataRowsInLastCol,1);

        QTableWidgetItem *stubItem = new QTableWidgetItem("—");
        stubItem->setTextAlignment(Qt::AlignCenter);
        stubItem->setFlags(stubItem->flags() & ~Qt::ItemIsEditable);
        setItem( 1,lastCol, stubItem);
    } else {
        setSpan(1,lastCol, 1, 1);
        setItem(1,lastCol,  new QTableWidgetItem(""));
    }

}
void DinamicTable::RemoveActiveRow(int rowIndex)
{
    active_rows--;
    if (rowIndex < titles_rows) {
        qWarning() << "Попытка удалить заголовочную строку!";
        return;
    }
    if (rowIndex >= rowCount()) {
        qWarning() << "Индекс строки вне диапазона!";
        return;
    }
    removeRow(rowIndex);


    int removed = rowIndex;
    emit SignalRowRemoved(removed);

}

void DinamicTable::AddActiveColumn()
{
    QTableWidgetItem *topTitle;
    if(active_columns == 0){
        topTitle = new QTableWidgetItem("Основной заголовок");
        topTitle->setTextAlignment(Qt::AlignCenter);
    }
    active_columns++;
    if (columnCount() < titles_columns + 1) return;

    int insertCol = columnCount() - 1;
    insertColumn(insertCol);

    int dataCols = active_columns;
    if (dataCols > 0) {
        setSpan(0, 1, 1, dataCols);
    }

    Title *titleWidget = new Title(insertCol, true, this);
    setCellWidget(1, insertCol, titleWidget);


    for (int row = 2; row < rowCount() - 1; ++row) {
        setItem(row, insertCol, new QTableWidgetItem(""));
    }

    if(active_columns == 1)
        setItem(0, 1, topTitle);

    int lastRow = rowCount() - 1;
    int dataColsInLastRow = columnCount() - 2;

    if (dataColsInLastRow > 0) {
        setSpan(lastRow, 1, 1, 1);
        setSpan(lastRow, 1, 1, dataColsInLastRow);

        QTableWidgetItem *stubItem = new QTableWidgetItem("—");
        stubItem->setTextAlignment(Qt::AlignCenter);
        stubItem->setFlags(stubItem->flags() & ~Qt::ItemIsEditable);
        setItem(lastRow, 1, stubItem);
    } else {
        setSpan(lastRow, 1, 1, 1);
        setItem(lastRow, 1, new QTableWidgetItem(""));
    }

}
void DinamicTable::RemoveActiveColumn(int colIndex){

    active_columns--;
    if (colIndex == 0) {
        qWarning() << "Нельзя удалить первый столбец!";
        return;
    }

    if (colIndex >= columnCount()) {
        qWarning() << "Индекс столбца вне диапазона!";
        return;
    }
    QString table_item_text;
    if(colIndex == 1){
        table_item_text = this->item(0, 1)->text();
    }

    removeColumn(colIndex);

    if(colIndex == 1){
        QTableWidgetItem *topTitle = new QTableWidgetItem(table_item_text);
        topTitle->setTextAlignment(Qt::AlignCenter);
        setItem(0, 1, topTitle);

        int lastRow = rowCount() - 1;
        QTableWidgetItem *stubItem = new QTableWidgetItem("—");
        stubItem->setTextAlignment(Qt::AlignCenter);
        stubItem->setFlags(stubItem->flags() & ~Qt::ItemIsEditable);
        setItem(lastRow, 1, stubItem);
    }


    int dataCols = active_columns;
    if (dataCols > 0) {
        setSpan(0, 1, 1, dataCols);
    } else {
        setSpan(0, 1, 1, 1);
    }

    int removed = colIndex;
    emit SignalColumnRemoved(removed);
}


int DinamicTable::GetTitleRows() const{
    return titles_rows;
}
int DinamicTable::GetTitleColumns() const{
    return titles_columns;
}

int DinamicTable::GetDataRows() const{
    return active_rows;
}
int DinamicTable::GetDataColumns() const{
    return active_columns;
}

Matrix<double> DinamicTable::GetData(){
    Matrix<double> data(active_rows, active_columns);
    for (int i = 0; i < active_rows; ++i) {
        for (int j = 0; j < active_columns; ++j) {
            int row = titles_rows + i;
            int col = titles_columns + j;

            QTableWidgetItem *item = this->item(row, col);

            if (!item) {
                item = new QTableWidgetItem("-");
                setItem(row, col, item);
            }

            if (ValidItem(item)) {
                double value = item->text().trimmed().toDouble();
                data[i][j] = value;
            }
            else{
                data[i][j] = 0.0;
            }
        }
    }
    return data;
}

bool DinamicTable::ValidItem(QTableWidgetItem* item)
{

    if (!item) {
        emit ErrorGetData();
        return false;
    }

    QString text = item->text().trimmed();
    if (text.isEmpty()) {
        item->setBackground(QColor(255, 200, 200));
        emit ErrorGetData();
        return false;
    }

    bool ok = false;
    double value = text.toDouble(&ok);

    if (ok) {
        item->setBackground(QBrush());
        return true;
    } else {
        item->setBackground(QColor(255, 200, 200));
        emit ErrorGetData();
        return false;
    }
}
//Title
Title::Title(int index, bool is_column, DinamicTable* parent) : QWidget(parent){
    this->index = index;
    this->is_column = is_column;
    this->parent_table = parent;

    if (parent_table) {
        if (is_column) {
            connect(parent_table, &DinamicTable::SignalColumnRemoved,
                    this, &Title::UpdateIndex);
        } else {
            connect(parent_table, &DinamicTable::SignalRowRemoved,
                    this, &Title::UpdateIndex);
        }
    }

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);


    QLineEdit* title_editor = new QLineEdit(this);
    title_editor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    title_editor->setStyleSheet("QLineEdit { border: none; }");
    QString title;
    if(is_column){
        int title_index = index - parent_table->GetTitleColumns() + 1;
        title = QString("Подзаголовок %1").arg(title_index);
    }
    else{
        int title_index = index - parent_table->GetTitleRows() + 1;
        title = QString("Подзаголовок %1").arg(title_index);
    }
    title_editor->setText(title);
    dell_button = new QPushButton("-", this);
    connect(dell_button, &QPushButton::clicked, this, [this]() {
        int idx = this->index;
        bool isCol = this->is_column;
        DinamicTable *table = this->parent_table;

        QTimer::singleShot(0, table, [table, idx, isCol]() {
            if (isCol) {
                table->RemoveActiveColumn(idx);
            } else {
                table->RemoveActiveRow(idx);
            }
        });
    });
    dell_button->setFixedSize(20, 20);

    layout->addWidget(title_editor);
    layout->addWidget(dell_button);
}
void Title::UpdateIndex(int removed_index){
    if (removed_index < index){
        int title_index;
        if (is_column) {
                index--;
                title_index = index - parent_table->GetTitleColumns() + 1;
        } else {
                index--;
                title_index = index - parent_table->GetTitleRows() + 1;
        }
        if (QLineEdit *editor = findChild<QLineEdit*>()) {
            QString title = QString("Подзаголовок %1").arg(title_index);

            editor->setText(title);
        }
    }
}
