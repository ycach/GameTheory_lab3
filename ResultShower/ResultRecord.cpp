#include "ResultRecord.h"

ResultRecord::ResultRecord(const QString& title, QWidget* parent) : QGroupBox(title, parent){

}

void ResultRecord::InitRecord(){
    CreateRecord();
}
