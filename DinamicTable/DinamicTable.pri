# editable_table.pri
INCLUDEPATH += $$PWD

HEADERS +=  \
    $$PWD/DinamicTable.h \
    $$PWD/MatrixData/Matrix.h \
    $$PWD/MatrixData/MatrixRow.h
SOURCES +=  \
    $$PWD/DinamicTable.cpp

QT += widgets
