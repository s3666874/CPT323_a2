#include <iostream>

using namespace std;

namespace fed::datastructure
{
        struct Datastructure
        {
                int what;

                virtual void printWhat() = 0;
        };

        void datastructure::printWhat() {
                cout << "Printing what" << endl;
        }
}


int main()
{
        

        fed::datastructure::datastructure::printWhat();

        return 0;
}