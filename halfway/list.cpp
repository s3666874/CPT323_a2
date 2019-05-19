#include "list.h"

void cpt323::list::node::set_next(std::unique_ptr<node>&& newnext)
{
        next = std::move(newnext);
}

cpt323::list::list::iterator::iterator(cpt323::list::node* anode) : current(anode)
{
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

std::unique_ptr<cpt323::datastructure::datastructure::iterator> cpt323::list::list::begin(void) 
{
        return std::make_unique<cpt323::list::list::iterator>(head.get());
        //return std::make_unique<cpt323::list::list::iterator>(head.get());
}

/*
std::unique_ptr<cpt323::list::list::iterator> end(void)
{
        return std::make_unique<cpt323::list::list::iterator>(nullptr);
}
*/

std::size_t cpt323::list::list::size(void)
{
        return num_elts;
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

bool cpt323::list::list::iterator::operator==(const cpt323::list::list::iterator& it)
{
        return it.current == current;
}

bool cpt323::list::list::iterator::operator!=(const cpt323::list::list::iterator& it)
{
        return !(*this == it);
}

std::unique_ptr<cpt323::list::list> cpt323::list::list::readfile(std::string_view filename)
{
        std::unique_ptr<cpt323::list::list> thelist = nullptr;

        /* open the file and check for errors */
        std::ifstream in(filename.data());
        
        if (!in)
        {
                perror("failed to open file for reading");
                return nullptr;
        }

        /* we should throw an io exception when the fail or bad bits are set
         * on the stream
         */
        in.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
                /* create the list */
                thelist = std::make_unique<cpt323::list::list>();

                /* read each line from the file */
                std::string line;

                while (std::getline(in, line))
                {
                        thelist->cpt323::list::list::add(line);
                }
        }
        catch (std::bad_alloc& ba)
        {
                /* handle the memory allocation errors */
                perror("memory allocation error");
                return nullptr;
        }
        catch (std::ios::failure& iff)
        {
                /* check if we are at the end of the file and if we are not,
                 * display an error appropriate to the io error that has occured
                 */
                if (!in.eof())
                {
                        perror("failed to read file");
                        return nullptr;
                }
        }
        catch (std::exception& ex)
        {
                /* handle any other errors */
                std::cerr << ex.what() << "\n";
        }
        return thelist;
}

cpt323::list::nodeptrpair cpt323::list::list::find_min(void)
{
        nodeptrpair pair(nullptr, nullptr);
        nodeptr current = &head, prev = nullptr;

        while (current != nullptr)
        {
                if (pair.second == nullptr ||
                    (*current)->data < (*(pair.second))->data)
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

bool cpt323::list::list::savefile(std::string_view filename, const cpt323::list::list& thelist)
{
        std::ofstream out(filename.data());
        std::string word;

        if (!out)
        {
                perror("failed to open file for saving");
                return false;
        }

        out.exceptions(std::ios::failbit | std::ios::badbit);

        try
        {
                for (const auto& item : thelist)
                {
                        out << item << "\n";
                }
                out << std::flush;
        }
        catch (std::ios::failure& iff)
        {
                perror("failed to save the file");
                return false;
        }
        return true;
}

void cpt323::list::list::print(void)
{
        std::stringstream oss;
        std::string word;

        while (oss >> word)
        {
                oss << word << "\n";
        }
        std::cout << oss.str();
}



