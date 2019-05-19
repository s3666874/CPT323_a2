#include <set>
#include <fstream>
#include <cassert>
#include <sstream>
#include <string_view>
#include "datastructure.h"
#pragma once

namespace cpt323::list
{
        struct node
        {
                std::unique_ptr<node> next;
                std::string data;

                friend struct list;

                node(const std::string& newstr)
                {
                        data = newstr;
                        next = nullptr;
                };

                void set_next(std::unique_ptr<node>&& next);

                virtual ~node() {}
        };

        using nodeptr = std::unique_ptr<node>*;
        using nodeptrpair = std::pair<nodeptr, nodeptr>;

        struct list: public cpt323::datastructure::datastructure
        {
                struct iterator: public cpt323::datastructure::datastructure::iterator
                {
                        node* current;

                        iterator() : current(nullptr) {};

                        iterator(node*);
                        std::string& operator*(void) const;
                        iterator operator++(void);
                        iterator operator++(int);
                        bool operator==(const iterator&);
                        bool operator!=(const iterator&);
                };

                std::unique_ptr<node> head;
                std::size_t num_elts;

                list(void);
                void add(const std::string&);
                std::unique_ptr<iterator> begin(void);
                //std::unique_ptr<cpt323::datastructure::datastructure::iterator> end(void);
                std::size_t size(void);
                void sort(void);

                void print(void);
                nodeptrpair find_min(void);

                /* reader and saver function declarations */
                static std::unique_ptr<cpt323::list::list> readfile(std::string_view);
                static bool savefile(std::string_view, const cpt323::list::list&);

                virtual bool empty(void)
                {
                        return size() == 0;
                }

                virtual ~list(void) {}
        };
}