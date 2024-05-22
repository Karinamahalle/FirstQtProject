#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QString>
#include <student.h>
#include <iostream>
#include <fstream>
#include <QMessageBox>
#include <QCheckBox>
#include <QFile>
#include <QTextStream>
using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("student Details");
    connect(ui->AddRecord,SIGNAL(clicked()),this,SLOT(on_AddRecord_clicked));
    connect(ui->Show,SIGNAL(clicked()),this,SLOT(on_Show_clicked()));
    connect(ui->Save,SIGNAL(clicked()),this,SLOT(on_Save_clicked));
    connect(ui->Read,SIGNAL(clicked()),this,SLOT(on_Read_clicked()));
    connect(ui->Next,SIGNAL(clicked()),this,SLOT(on_Next_Clicked()));
    connect(ui->Clear,SIGNAL(clicked()),this,SLOT(on_Clear_licked()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_AddRecord_clicked()
{
    Student stdObj;

      stdObj.name = ui->Nameline->text().toStdString();
      bool isValidName = true;
      for (char ch : stdObj.name) {
          if (!isalpha(ch))
          {
              isValidName = false;
              break;
          }
      }

      stdObj.rollno = ui->Rollnolabel->text().toInt();
      bool isValidRollno = stdObj.rollno > 0;

      stdObj.age = ui->Agelabel->text().toInt();
      bool isValidAge = stdObj.age > 0;

      if (!isValidName || !isValidRollno || !isValidAge) {
          QMessageBox::warning(this, "Invalid Input", "Please enter valid data.");
          return;
      }

      if (ui->femaleradioButton->isChecked()) {
          stdObj.sex = 'F';
      } else if (ui->maleradioButton->isChecked()) {
          stdObj.sex = 'M';
      }

      stdObj.SubjectsMap["English"] = ui->EnglishText->text().toInt();
      stdObj.SubjectsMap["Maths"] = ui->MathsText->text().toInt();
      stdObj.SubjectsMap["Science"] = ui->ScienceText->text().toInt();
      stdObj.SubjectsMap["History"] = ui->HistoryText->text().toInt();
      stdObj.SubjectsMap["Geog"] = ui->GeogText->text().toInt();

     StudentVec.push_back(stdObj);

      QMessageBox::information(this, "Success", "Student details are saved.");
}

void MainWindow::on_Show_clicked()
{
    QString showData;
        for (unsigned int i = 0; i < StudentVec.size(); ++i)
        {
            const Student& obj = StudentVec[i];

            showData += "\nName of the student\n ";
            showData += "\nName : ";
            showData += obj.name.c_str();
            showData += "\nAge : ";
            showData += QString::number(obj.age);
            showData += "\nRoll No : ";
            showData += QString::number(obj.rollno);
            showData += "\nSex : ";
            showData += obj.sex.c_str();

            showData += "\nMarks of the student\n ";
            //map<string,int>::iterator it;
            for (auto it = obj.SubjectsMap.begin(); it != obj.SubjectsMap.end(); it++)
            {
                showData += "\n";
                showData += it->first.c_str();
                showData += " : ";
                showData += QString::number(it->second);
            }
        }
        ui->Show->setText(showData);
}



void MainWindow::on_Save_clicked()
{
    string line;
       fstream fio;

       fio.open("StudentData.txt", ios::app | ios::out | ios::in);

       for(const auto& obj: StudentVec)
       {
           line += (obj.name + ",");
           line += (to_string(obj.age) + ",");
           line += (to_string(obj.rollno) + ",");
           line += (obj.sex + ",");
           for(const auto &sub : obj.SubjectsMap)
           {
               line += (sub.first.c_str());
               line += (":"+to_string(sub.second) + ",");
           }
           line.pop_back();
           fio << line << endl;
       }
    QMessageBox::information(this,"Student Record","Student details are saved.");
}



void MainWindow::on_Read_clicked()
{

    QFile file("StudentData.txt");
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this, "Error", "Failed to open file.");
            return;
        }

        QTextStream in(&file);
        QString line = in.readLine();
        QStringList parts = line.split(',');

        if (parts.size() >= 5) {
            ui->NameText->setText(parts[0]);
            ui->Agelabel->setText(parts[1]);
            ui->Rollnolabel->setText(parts[2]);

            if (parts[3] == "M")
            {
                ui->maleradioButton->setChecked(true);
            }
            else if (parts[3] == "F")
            {
                ui->femaleradioButton->setChecked(true);
            }

            ui->EnglishText->setText(parts[4]);
            ui->MathsText->setText(parts[5]);
            ui->ScienceText->setText(parts[6]);
            ui->HistoryText->setText(parts[7]);
            ui->GeogText->setText(parts[8]);



        } else {
            QMessageBox::warning(this, "Error", "Invalid data format in the file.");
        }

        file.close();
}

void MainWindow::on_Clear_clicked()
{
    ui->NameText->clear();
       ui->Rollnolabel->clear();
       ui->Agelabel->clear();
       ui->maleradioButton->setEnabled(true);
       ui->femaleradioButton->setEnabled(true);

       ui->maleradioButton->setChecked(false);
       ui->femaleradioButton->setChecked(false);

       ui->EnglishText->clear();
       ui->MathsText->clear();
       ui->ScienceText->clear();
       ui->HistoryText->clear();
       ui->GeogText->clear();
       ui->Show->clearFocus();
}


void MainWindow::on_Next_clicked()
{
    static  int currentRecordIndex = 0;
   Student Stdobj;
   QFile file("StudentData.txt");
   if (!file.isOpen()) {
           if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
               QMessageBox::warning(this, "Error", "Failed to open file.");
               return;
           }
       }

       QTextStream in(&file);

       for (int i = 0; i < currentRecordIndex; ++i) {
           in.readLine();
       }

       if (!in.atEnd()) {
           QString line = in.readLine();
           QStringList info = line.split(',');

           QString studentInfo;
                  studentInfo += "\nName of the student\n ";
                  studentInfo += "\nName : " + info[0];
                  studentInfo += "\nAge : " + info[1];
                  studentInfo += "\nRoll No : " + info[2];
                  studentInfo += "\nSex : " + info[3];

                  studentInfo += "\nMarks of the student\n ";
                  for (int i = 4; i < info.size(); i++) {
                      studentInfo += "\nSubject " + QString::number(i - 3) + ": " + info[i];
                  }

                  ui->Show->setText(studentInfo);

           ui->NameText->setText(info[0]);
           ui->Agelabel->setText(info[1]);
           ui->Rollnolabel->setText(info[2]);

           if (info[3] == "M") {
               ui->maleradioButton->setChecked(true);
               ui->femaleradioButton->setChecked(false);
           } else if (info[3] == "F") {
               ui->maleradioButton->setChecked(false);
               ui->femaleradioButton->setChecked(true);
           }

           ui->EnglishText->setText(info[4]);
           ui->MathsText->setText(info[7]);
           ui->ScienceText->setText(info[8]);
           ui->HistoryText->setText(info[6]);
           ui->GeogText->setText(info[5]);

           ++currentRecordIndex;
       } else {

           file.seek(0);
           currentRecordIndex = 0;
       }
}

