#ifndef PAINTERS_H
#define PAINTERS_H

#include <string>
#include <vector>
#include <set>

class Painters {

    std::string mTeacher = "";
    std::string mName = "";
    long long mTalent;
    long long mZeal;
    long long mSkills = 0;
    std::set<Painters*> mStudents;

public:
    explicit Painters(std::string name);
    Painters(std::string name, long long talent, long long zeal = 3, std::string teachers_name = "");

    ~Painters() = default;

    long long getTalent();
    long long getZeal();
    long long getSkills();

    std::string getRang();
    std::string getName();
    std::string getTeachersName();
    std::set<Painters*> &getStudentsList();
    long long getCountOfStudents();

    long long inspiration(long long zeal);
    double inspiration();

    int find_teacher(std::vector<Painters> &painters);

    int find_student(std::vector<Painters> &painters, long long skills, long long zeal);
    int find_student(std::vector<Painters> &painters);

    void make_creation();
    void make_creation(long long complexity);
    void make_creation(Painters &partner, long long complexity);

};

#endif