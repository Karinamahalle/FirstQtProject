#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <map>

using namespace std;
class Student
{
public:
    int rollno;
    int age;
    string sex;
    string name;

    map<string,int> SubjectsMap;
};

#endif // STUDENT_H
