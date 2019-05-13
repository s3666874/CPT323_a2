#include <cassert>
#include <iostream>
#include <memory>
#include <utility>
#include <sstream>
#pragma once

namespace cpt323
{
        namespace list
        {
                class node
                {
                        std::unique_ptr<node> next;
                        std::string data;
                        friend class list;

                        public:
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

                class list
                {
                        std::unique_ptr<node> head;
                        std::size_t num_elts;

                        class iterator
                        {
                                node* current;

                                public:
                                        iterator() : current(nullptr)
                                        {
                                        }

                                        iterator(node*);
                                        std::string& operator*(void) const;
                                        iterator operator++(void);
                                        iterator operator++(int);
                                        bool operator==(const iterator&);
                                        bool operator!=(const iterator&);
                        };

                        public:
                                list(void);
                                void add(const std::string&);
                                iterator begin(void) const;
                                iterator end(void) const;
                                std::size_t size(void);
                                void sort(void);

                                void print(void);
                                nodeptrpair find_min(void);

                                virtual bool empty(void)
                                {
                                        return size() == 0;
                                }

                                virtual ~list(void)
                                {
                                }
                };
        }
}