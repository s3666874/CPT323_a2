#include <iostream>

using namespace std;

struct Test
{
        private:
                int count;

        public:
                Test(): count(5) {}

                Test operator ++() {
                        Test temp;
                        temp.count = ++count;

                        return temp;
                }

                Test operator ++(int) {
                        Test temp;
                        temp.count = count++;

                        return temp;
                }

                void fun() const { 
                        cout << "fun() const called " << endl; 
                }

                void fun() { 
                        cout << "fun() called " << endl; 
                }

                void Display() { 
                        cout << "Count: " << count << endl;
                }
};

int main(void) 
{
        Test t1;
        const Test t2;

        t1.fun();
        t2.fun();

        const int i = 1;
        const int j = 2;
        int k = 3;

        int * const c = &k;

        cout << k << endl;
        cout << c << endl;
        cout << *c << endl;

        k = 4;

        cout << k << endl;
        cout << c << endl;
        cout << *c << endl;
        
/*
        t.Display();
        t1.Display();

        t1 = ++t;
        t.Display();
        t1.Display();

        t1 = t++;
        t.Display();
        t1.Display();

        cout << 3 * 2 << endl;
*/
        return 0;
}
