#include <iostream>

using namespace std;

// Top main namespace
namespace fed 
{
        // Interface
        struct Person {
                protected:
                        int age;
                        int salary;

                public:
                        void setAge(int a);
                        virtual void printAge() = 0;

                        void setSalary(int s) {
                                salary = s;
                        };

                        // Nested interface
                        struct PersonType {
                                char type[50];

                                void setPersonType(char* t) {
                                        strcpy(type, t);
                                };

                                void printPersonType() {
                                        cout << "I am of type " << type << endl;
                                };
                        };
        };

        void Person::setAge(int a) {
                age = a;
        };

        // 
        struct Engineer: public Person {
                public:
                        char role[50];

                        void printRole() {
                                cout << "I am an engineer!" << endl;
                        }

                        void printAge() {
                                cout << "I am " << age << " years old." << endl;
                        }
        };
}


int main(void) {
        fed::Engineer me;

        me.setAge(43);
        me.setSalary(117000);

        me.printAge();
        me.printRole();

        return 0;
}