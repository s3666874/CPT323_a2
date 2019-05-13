#ifndef DS_H
#define DS_H

namespace cpt323
{
        namespace datastructure
        {
                struct datastructure
                {

                        struct iterator
                        {
                                virtual void iteratorPrint() = 0;
                        };

                        virtual void printHello() = 0;
                        virtual void printArgument(int a) = 0;
                };
        };
}

#endif