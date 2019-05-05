#include <iostream>

using namespace std;

namespace fed
{
        // Parent struct (class)
        struct A 
        {
                int what;

                void setWhat(int n) {
                        what = n;
                };

                virtual void printWhat() = 0;

                // Nested sub struct (class)
                struct B 
                {
                        int num;
                        char word[50];

                        void setWord(char* w) {
                                strcpy(word, w);
                        };

                        void setNum(int n) {
                                num = n;
                        };

                        virtual void printNum() = 0;
                        virtual void printWord() = 0;
                };
        };
};

struct A1: public fed::A 
{
        void printWhat() {
                cout << what << endl;
        }
};

struct B1: public fed::A::B
{
        void printNum() {
                cout << num << endl;
        }

        void printWord() {
                cout << word << endl;
        }
};

int main(void) {
        char temp[] = "fed";
        A1 ed;
        B1 fed;

        ed.setWhat(12);

        fed.setNum(23);
        fed.setWord(temp);

        ed.printWhat();

        fed.printNum();
        fed.printWord();

        return 0;
}