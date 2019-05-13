#include <fstream>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <memory>
#include <string_view>
#include <vector>
#include "list.h"

namespace cpt323
{
        namespace reader
        {
                std::unique_ptr<cpt323::list::list> readfile(std::string_view);
        }
}
