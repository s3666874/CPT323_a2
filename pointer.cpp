#include <iostream>
#include <memory>

using namespace std;

struct Entity
{
        Entity()
        {
                cout << "Entity created" << endl;
        }

        ~Entity()
        {
                cout << "Entity deleted" << endl;
        }

        void Print() {}
};

int main(void)
{
        {
                unique_ptr<Entity> entity = make_unique<Entity>();
                //unique_ptr<Entity> asdf = entity;

                unique_ptr
                
                entity->Print();
        }

        return 0;
}