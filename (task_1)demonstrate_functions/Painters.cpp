#include "Painters.h"

Painters::Painters(std::string name) : mTalent(200), mZeal(100), mName(std::move(name)) {}

Painters::Painters(std::string name, long long talent, long long zeal, std::string teachers_name) :
        mTalent(talent), mZeal(zeal), mName(std::move(name)), mTeacher(std::move(teachers_name)) {}


long long Painters::getZeal() {
    return mZeal;
}

long long Painters::getTalent() {
    return mTalent;
}

long long Painters::getSkills() {
    return mSkills;
}

std::string Painters::getRang() {
    std::string rang;
    if (mSkills <= 7000) {
        rang = "student";
    } else if (mSkills >= 999000) {
        rang = "genius";
    } else {
        rang = "master";
    }
    return rang;
}

std::string Painters::getName() {
    return mName;
}

std::string Painters::getTeachersName() {
    return mTeacher;
}

std::set<Painters*> &Painters::getStudentsList() {
    return mStudents;
}

long long Painters::getCountOfStudents() {
    return mStudents.size();
}

int Painters::find_teacher(std::vector<Painters> &painters) {
    for (int i = 0; i < painters.size(); ++i) {
        if (painters[i].mName != mName) {
            std::string rang = painters[i].getRang();
            if (rang != "student" &&
                mSkills <= painters[i].getSkills() &&
                mTalent * 3 + mZeal >= painters[i].getZeal()) {

                mTeacher = painters[i].mName;
                return i;
            }
        }
    }
    return -1;
}

int Painters::find_student(std::vector<Painters> &painters, long long skills, long long zeal) {
    for (int i = 0; i < painters.size(); ++i)
        if (painters[i].mName != mName) {
            if (painters[i].getRang() == "student" && painters[i].getTeachersName() == "" &&
                    painters[i].getSkills() >= skills && painters[i].getZeal() >= zeal &&
                mStudents.find(&painters[i]) == mStudents.end()) {

                painters[i].mTeacher = mName;
                mStudents.insert(&painters[i]);
                return i;
            }
        }
    return -1;
}

int Painters::find_student(std::vector<Painters> &painters) {
    for (int i = 0; i < painters.size(); ++i) {
        if (painters[i].mName != mName) {
            if (painters[i].getRang() == "student" && painters[i].getTeachersName().empty() &&
                mStudents.find(&painters[i]) == mStudents.end()) {

                painters[i].mTeacher = mName;
                mStudents.insert(&painters[i]);
                return i;
            }
        }
    }
    return -1;
}

void Painters::make_creation() {
    return make_creation(mSkills / 2 + mTalent + mZeal * 2);
}

void Painters::make_creation(long long complexity) {
    mSkills += complexity;
    if (complexity < 500) --mZeal;
    else mZeal += 6;
}

void Painters::make_creation(Painters &partner, long long complexity) {
    long long complex = complexity + mTalent + mZeal * 2 + partner.mTalent + partner.mZeal;
    mSkills += complex;
    partner.mSkills += (complex / 2);
    mZeal += partner.mZeal;
    partner.mZeal += 60;
}

long long Painters::inspiration(long long zeal) {
    this->mZeal += zeal;
    mSkills += 10;
    return zeal;
}

double Painters::inspiration() {
    mZeal += 100;
    mSkills += 20;
    return mZeal;
}