#ifndef MATRIX_H
#define MATRIX_H

#include "MatrixRow.h"


template<typename T>
class Matrix{
public:
    explicit Matrix(int rows, int columns){



        if (rows <= 0 || columns <= 0){
            this->rows = 1;
            this->columns = 1;
        }
        else{
            this->rows = static_cast<size_t>(rows);
            this->columns = static_cast<size_t>(columns);
        }



        matrix.reserve(this->rows);
        for (int i = 0; i < this->rows; i++) {
            matrix.emplace_back(MatrixRow<T>(this->columns));
        }

    }
    ~Matrix() = default;
public:
    MatrixRow<T>& operator[](size_t index) {
        return matrix[index];
    }

    const MatrixRow<T>& operator[](size_t index) const {
        return matrix[index];
    }

    inline std::vector<T> GetColumn(int idx) const{
        std::vector<T> column;
        for(int i = 0; i < rows; i++){
            column.push_back(matrix[i][idx]);
        }

        return column;
    }
    inline std::vector<T> GetRow(int idx) const{
        std::vector<T> row;
        for(int i = 0; i < columns; i++){
            row.push_back(matrix[idx][i]);
        }

        return row;
    }

    inline void RemoveRow(int idx){
        matrix.erase(matrix.begin() + idx);
        rows--;
    }

    inline void RemoveColumn(int idx){
        for(int i = 0; i < rows; i++){
            matrix[i].RemoveItem(idx);
        }
        columns--;
    }

    inline size_t GetColumnsCount() const{
        return columns;
    }
    inline size_t GetRowsCount() const{
        return rows;
    }


private:
    std::vector<MatrixRow<T>> matrix;
    size_t rows;
    size_t columns;
};
#endif // MATRIX_H
