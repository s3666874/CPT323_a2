#include "list.h"

void cpt323::list::node::set_next(std::unique_ptr<node>&& newnext)
{
        next = std::move(newnext);
}

cpt323::list::list::list(void) : head(nullptr), num_elts(0)
{
}

void cpt323::list::list::add(const std::string& newstr)
{
        static node* tail = nullptr;
        if (tail)
        {
                tail->set_next(std::make_unique<node>(newstr));
                tail = tail->next.get();
        }
        else
        {
                head = std::make_unique<node>(newstr);
                tail = head.get();
        }
        ++num_elts;
        
}

cpt323::list::list::iterator::iterator(cpt323::list::node* anode) : current(anode)
{
}

std::size_t cpt323::list::list::size(void)
{
        return num_elts;
}

cpt323::list::list::iterator cpt323::list::list::begin(void) const
{
        return iterator(head.get());
}

cpt323::list::list::iterator cpt323::list::list::end(void) const
{
        return iterator(nullptr);
}

std::string& cpt323::list::list::iterator::operator*(void) const
{
        return current->data;
}

cpt323::list::list::iterator cpt323::list::list::iterator::operator++(void)
{
        current = current->next.get();
        return iterator(*this);
}

cpt323::list::list::iterator cpt323::list::list::iterator::operator++(int)
{
        iterator it = *this;
        operator++();
        return iterator(it);
}

cpt323::list::nodeptrpair cpt323::list::list::find_min(void)
{
        nodeptrpair pair(nullptr, nullptr);
        nodeptr current = &head, prev = nullptr;

        while (current != nullptr)
        {
                if (pair.second == nullptr || (*current)->data < (*(pair.second))->data)
                {
                        pair.first = prev;
                        pair.second = current;
                }
                prev = current;

                current = (*current == nullptr || (*current)->next == nullptr)
                              ? nullptr
                              : &((*current)->next);
        }

        return pair;
}

void cpt323::list::list::sort(void)
{
        cpt323::list::list sortedlist;
        nodeptr endptr = nullptr;

        while (!empty())
        {
                nodeptrpair min = find_min();
                std::unique_ptr<node> removed = std::move(*(min.second));

                if (!min.first)
                {
                        if (removed)
                        {
                                if (removed->next)
                                {
                                        head = std::move(removed->next);
                                }
                                else
                                {
                                        head = nullptr;
                                }
                        }
                }
                else
                {
                        (*min.first)->set_next(std::move(removed->next));
                }
                --num_elts;

                if (!endptr)
                {
                        sortedlist.head = std::move(removed);
                        endptr = &sortedlist.head;
                }
                else
                {
                        (*(endptr))->next = std::move(removed);
                        endptr = &(*(endptr))->next;
                }
                ++sortedlist.num_elts;
        }
        assert(empty());

        head = std::move(sortedlist.head);
        num_elts = sortedlist.num_elts;
}

bool cpt323::list::list::iterator::operator==(const cpt323::list::list::iterator& it)
{
        return it.current == current;
}

bool cpt323::list::list::iterator::operator!=(const cpt323::list::list::iterator& it)
{
        return !(*this == it);
}

void cpt323::list::list::print(void)
{
        std::ostringstream oss;
        for (auto word : *this)
        {
                oss << word << "\n";
        }
        std::cout << oss.str();
}