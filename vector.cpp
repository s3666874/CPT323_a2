#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
        vector<int> v(10);

        for (int i = 0; i < 5; ++i)
                v[i] = i + 1;

        v[6] = 23;

        cout << "size: " << v.size() << endl;

        for (int i = 0; i < v.size(); ++i)
                cout << v[i] << endl;
        
        return 0;
}