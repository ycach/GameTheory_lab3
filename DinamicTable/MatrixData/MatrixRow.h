#ifndef MATRIXROW_H
#define MATRIXROW_H
#include <vector>
#include <algorithm>
template<typename T>
class MatrixRow{
public:
    explicit MatrixRow(int columns){
        if(columns >=0)
            elms = static_cast<size_t>(columns);
        else
            elms = 1;

        for(int i = 0; i < this->elms; i++)
            row.emplace_back(T{});
    }
    ~MatrixRow() = default;
public:
    T& operator[](int index) {
        return row[index];
    }

    const T& operator[](int index) const {
        return row[index];
    }

    size_t GetSize() const {
        return row.size();
    }

    inline void RemoveItem(int idx){
        row.erase(row.begin() + idx);
        elms--;
    }
private:
    std::vector<T> row;
    size_t elms;

};
#endif // MATRIXROW_H
