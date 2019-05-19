#include <set>
#include <cassert>
#include <sstream>
#include <iostream>
#include <memory>
#include <utility>
#include <exception>
#include <list>
#include <string>
#include <string_view>
#include <vector>
#include "datastructure.h"

namespace cpt323::list
{
        struct node
        {
                std::unique_ptr<node> next;
                std::string data;

                friend class list;

                node(const std::string& newstr)
                {
                        data = newstr;
                        next = nullptr;
                }

                void set_next(std::unique_ptr<node>&& newnext) {
                        next = std::move(newnext);
                }

                virtual ~node() {}
        };

        using nodeptr = std::unique_ptr<node>*;
        using nodeptrpair = std::pair<nodeptr, nodeptr>;

        struct list: public cpt323::datastructure::datastructure
        {
                std::unique_ptr<node> head;
                std::size_t num_elts;

                struct iterator: public cpt323::datastructure::datastructure::iterator
                {
                        node* current;

                        iterator() : current(nullptr) {}
                        iterator(node* anode): current(anode) {};

                        std::string& operator*(void) const {
                                return current->data;
                        };

                        std::unique_ptr<iterator> operator++(void) {
                                current = current->next.get();
                                return std::make_unique<iterator>(iterator(*this));
                        };

                        std::unique_ptr<iterator>&& operator++(int) {
                                iterator it = *this;
                                operator++();
                                return std::make_unique<iterator>(iterator(it));
                        };

                        bool operator==(const iterator& it) {
                                return it.current == current;
                        };

                        bool operator!=(const iterator& it) {
                                return !(*this == it);
                        };
                };

                list(void): head(nullptr), num_elts(0) {};

                void add(const std::string& newstr) {
                        static node* tail = nullptr;

                        if (tail) {
                                tail->set_next(std::make_unique<node>(newstr));
                                tail = tail->next.get();
                        } else {
                                head = std::make_unique<node>(newstr);
                                tail = head.get();
                        }
                        ++num_elts;
                }

                std::size_t size(void) {
                        return num_elts;
                };

                std::unique_ptr<iterator> begin(void) const {
                        return std::make_unique<iterator>(head.get());
                };

                std::unique_ptr<iterator> end(void) const {
                        return std::make_unique<iterator>(nullptr);
                };

                nodeptrpair find_min(void) {
                        nodeptrpair pair(nullptr, nullptr);
                        nodeptr current = &head, prev = nullptr;

                        while (current != nullptr) {
                                if (pair.second == nullptr || (*current)->data < (*(pair.second))->data) {
                                        pair.first = prev;
                                        pair.second = current;
                                }

                                prev = current;

                                current = (*current == nullptr || (*current)->next == nullptr) ? nullptr : &((*current)->next);
                        }

                        return pair;
                };

                void sort(void) {
                        cpt323::list::list* sortedlist;
                        nodeptr endptr = nullptr;

                        while (!empty()) {
                                nodeptrpair min = find_min();
                                std::unique_ptr<node> removed = std::move(*(min.second));

                                if (!min.first) {
                                        if (removed) {
                                                if (removed->next) {
                                                        head = std::move(removed->next);
                                                } else {
                                                        head = nullptr;
                                                }
                                        }
                                } else {
                                        (*min.first)->set_next(std::move(removed->next));
                                }

                                --num_elts;

                                if (!endptr) {
                                        sortedlist->head = std::move(removed);
                                        endptr = &sortedlist->head;
                                } else {
                                        (*(endptr))->next = std::move(removed);
                                        endptr = &(*(endptr))->next;
                                }

                                ++sortedlist->num_elts;
                        }

                        assert(empty());

                        head = std::move(sortedlist->head);
                        num_elts = sortedlist->num_elts;
                };

                virtual bool empty(void) {
                        return size() == 0;
                }

                /*void print(void) {
                        std::ostringstream oss;

                        for (auto word : *this) {
                                oss << word << "\n";
                        }

                        std::cout << oss.str();
                };*/
        };
};

void printList(const cpt323::list::list& thelist) {
        for (const auto& item : thelist) {
                std::cout << item << std::endl;
        }
};

int main(int argc, char* argv[])
{
        std::string line;
        std::vector<std::string> input;
        std::unique_ptr<cpt323::list::list> thelist = std::make_unique<cpt323::list::list>();

        input.push_back("eric");
        input.push_back("peter");
        input.push_back("anny");
        input.push_back("shelly");
        input.push_back("federick");

        for (auto i : input) {
                thelist->add(i);
        }

        if (thelist) {
                thelist->sort();
                printList(*thelist);
        }

        return 0;
}