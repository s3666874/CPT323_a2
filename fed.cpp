#include <iostream>

using namespace std;

void af(int g)
{
    g++;
    //cout << g;
};

int main(void)
{
        int g = 123;

        cout << "Before: " << g << endl;
        
        af(g);
        
        cout << "After: " << g << endl;
        
        return 0;
}
