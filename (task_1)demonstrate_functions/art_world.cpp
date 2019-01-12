#include <iostream>
#include "Painters.h"

using namespace std;
int main() {
    vector<Painters> painters;

    Painters Michelangelo("Michelangelo");
    Michelangelo.make_creation(77777777777);
    Painters Van_Gog("Vincent Van Gog", 100, 200, "Michelangelo");
    Painters Monet("Klod Monet", 567);

    painters.push_back(Michelangelo);
    painters.push_back(Van_Gog);
    painters.push_back(Monet);

    cout << "Monet's rang: "<< Monet.getRang() << " Monet's mTeacher: " << Monet.getTeachersName() << "\n";

    Monet.find_teacher(painters);
    Monet.make_creation(Van_Gog, 5678);

    double monet_zeal_d = Monet.inspiration();
    long long monet_zeal_i = Monet.getZeal();

    Painters Malevitch("Kisimir Malevitch", 7695, 778);
    painters.push_back(Malevitch);

    cout << "Malevitch's rang: "<< Malevitch.getRang() << "\n";

    Malevitch.make_creation(Michelangelo, 68888);

    cout << "Malevitch's rang: "<< Malevitch.getRang() << "\n";

    Malevitch.find_student(painters);
    Malevitch.inspiration();

    cout << "Malevitch's count students: " << Malevitch.getCountOfStudents()
         << "\n\tFirst student's name: " << (*Malevitch.getStudentsList().begin())->getName();
    return 0;
}