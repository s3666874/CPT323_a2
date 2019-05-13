#include <fstream>
#include <iostream>
#include <list>
#include <string_view>
#include <set>
#include <vector>
#include "list.h"

#pragma once
namespace cpt323::saver
{
        class saver
        {
                public:
                        static bool savefile(std::string_view, const cpt323::list::list&);
        };
}

        
        