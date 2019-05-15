#include "datastructure.h"
#pragma once

namespace cpt323::list
{
        struct node
        {
                private:
                        std::unique_ptr<node> next;
                        std::string data;

                friend struct list;

                node(const std::string& newstr)
                {
                        data = newstr;
                        next = nullptr;
                }

                void set_next(std::unique_ptr<node>&& next);

                virtual ~node()
                {
                }
        };

        using nodeptr = std::unique_ptr<node>*;
        using nodeptrpair = std::pair<nodeptr, nodeptr>;

        struct list: public cpt323::datastructure::datastructure
        {
                private:
                        std::unique_ptr<node> head;
                        std::size_t num_elts;

                list(void);
                void add(const std::string&);
                std::unique_ptr<cpt323::list::list> readfile(std::string_view);
                std::size_t size(void);
                void print(void);
                nodeptrpair find_min(void);

                virtual ~list(void)
                {
                }
        };
}