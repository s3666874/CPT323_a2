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

std::size_t cpt323::list::list::size(void)
{
        return num_elts;
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

void cpt323::list::list::print(void)
{
        std::ostringstream oss;
        for (auto word : *this)
        {
                oss << word << "\n";
        }
        std::cout << oss.str();
}