#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
        vector<string> v;
        v.clear();

        cout << "vector size = " << v.size() << endl;

        v.push_back("who");
        v.push_back("what");
        v.push_back("how");

        cout << "extended vector size = " << v.size() << endl;

        for(int i = 0; i < v.size(); i++) {
                cout << v[i] << endl;
        }
        
        return 0;
}