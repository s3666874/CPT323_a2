#include <set>
#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <fstream>
#include <cassert>
#include <sstream>
#include <string_view>
#include "datastructure.h"
#pragma once

namespace cpt323::tree
{
        struct node
        {
                std::unique_ptr<node> left;
                std::unique_ptr<node> right;
                std::string data;
                friend class tree;

                node(const std::string& _data) : left(nullptr), right(nullptr), data(_data) {}

                void add(const std::string&);

                void set_left(std::unique_ptr<node>&& newleft)
                {
                        left = std::move(newleft);
                }

                void set_right(std::unique_ptr<node>&& newright)
                {
                        right = std::move(newright);
                }
        };

        struct tree: public cpt323::datastructure::datastructure
        {
                struct iterator
                {
                        node* current;
                        std::stack<node*> nodestack;

                        iterator(void);
                        iterator(node*);
                        std::string& operator*(void) const;
                        iterator operator++(void);
                        iterator operator++(int);
                        void push_nodes(node*);
                        bool operator==(const iterator&);
                        bool operator!=(const iterator&);
                };

                std::unique_ptr<node> root;
                std::size_t num_nodes;

                tree(void);
                void add(const std::string&);
                iterator begin(void) const;
                iterator end(void) const;
                std::size_t size(void);

                void sort(void) {}

                /* reader and saver function declarations */
                static std::unique_ptr<cpt323::tree::tree> readfile(std::string_view);
                static bool savefile(std::string_view, const cpt323::tree::tree&);

                bool empty(void) const
                {
                        return root == nullptr;
                }

                virtual ~tree(void) {}
        };
}