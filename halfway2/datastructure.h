#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <string>
#include <vector>

#ifndef DS_H
#define DS_H

namespace cpt323::datastructure
{
        struct datastructure
        {
                struct iterator
                {
                        virtual std::string& operator*(void) const = 0;
                };

                virtual void add(const std::string&) = 0;
        };
}

#endif
