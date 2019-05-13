#pragma once

namespace cpt323::reader
{
        std::unique_ptr<cpt323::list::list> readfile(std::string_view);
}