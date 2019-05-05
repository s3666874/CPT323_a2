#include <iostream>

using namespace std;

struct Datasource
{
        struct Iterator
        {
                virtual bool operator==(const Iterator&) = 0;
        };
};



int main(void) 
{
        return 0;
}
