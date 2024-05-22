#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <student.h>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void on_AddRecord_clicked();

    void on_Show_clicked();

    void on_Save_clicked();

    void on_Read_clicked();

    void on_Next_Clicked();

    void on_Clear_Clicked();

    //void OnNextclicked();

private slots:
    void on_Clear_clicked();

    void on_Next_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<Student> StudentVec;
    Student stdObj;
    char str[80];
    QString showData = "";
    int currentStudentIndex = 0;
    QString line;
    QStringList data;

};
#endif // MAINWINDOW_H
