#include <iostream>

using namespace std;

void changeIt(int &i)
{
        i++;
};

int main(void)
{
        int i = 1;

        changeIt(i);

        cout << i << endl;

        return 0;
}
