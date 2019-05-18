#include "tree.h"

cpt323::tree::tree::tree(void) : root(nullptr), num_nodes(0)
{
}

void cpt323::tree::tree::add(const std::string& newstring)
{
        bool error = false;

        try
        {
                if (!root)
                {
                        root = std::make_unique<node>(newstring);
                }
                else
                {
                        root->add(newstring);
                }
        }
        catch (std::bad_alloc& ba)
        {
                perror(ba.what());
                error = true;
        }

        if (!error)
        {
                ++num_nodes;
        }
}

cpt323::tree::tree::iterator cpt323::tree::tree::begin(void) const
{
        return root ? iterator(root.get()) : end();
}

cpt323::tree::tree::iterator cpt323::tree::tree::end(void) const
{
        return iterator(nullptr);
}

std::size_t cpt323::tree::tree::size(void)
{
        return num_nodes;
}

void cpt323::tree::node::add(const std::string& newstring)
{
        if (data < newstring)
        {
                if (left)
                {
                        left->add(newstring);
                }
                else
                {
                        left = std::make_unique<node>(newstring);
                }
        }
        else
        {
                if (right)
                {
                        right->add(newstring);
                }
                else
                {
                        right = std::make_unique<node>(newstring);
                }
        }
}

cpt323::tree::tree::iterator::iterator(void) : current(nullptr)
{
}

cpt323::tree::tree::iterator::iterator(node* newnode) : current(nullptr)
{
        if (newnode)
        {
                push_nodes(newnode);
        }
        else
        {
                return;
        }

        current = nodestack.top();
        nodestack.pop();
}

void cpt323::tree::tree::iterator::push_nodes(node* root)
{
        if (root->left)
        {
                push_nodes(root->left.get());
        }
        nodestack.push(root);
        if (root->right)
        {
                push_nodes(root->right.get());
        }
}

std::string& cpt323::tree::tree::iterator::operator*(void) const
{
        return current->data;
}

cpt323::tree::tree::iterator cpt323::tree::tree::iterator::operator++(void)
{
        if (nodestack.empty())
        {
                current = nullptr;
                return iterator(*this);
        }
        current = nodestack.top();
        nodestack.pop();
        return iterator(*this);
}

cpt323::tree::tree::iterator cpt323::tree::tree::iterator::operator++(int)
{
        iterator it = *this;
        operator++();
        return it;
}

bool cpt323::tree::tree::iterator::operator==(const cpt323::tree::tree::iterator& it)
{
        return it.current == current;
}

bool cpt323::tree::tree::iterator::operator!=(const cpt323::tree::tree::iterator& it)
{
        return !(*this == it);
}

std::unique_ptr<cpt323::tree::tree> cpt323::tree::tree::readfile(std::string_view filename)
{

        std::unique_ptr<cpt323::tree::tree> newtree = nullptr;

        /* open the file and check for errors */
        std::ifstream in(filename.data());
        if (!in)
        {
                perror("failed to open file");
                return nullptr;
        }
        /* specify which exceptions to throw */
        in.exceptions(std::ios::failbit | std::ios::badbit);
        try
        {
                /* create the tree */
                newtree = std::make_unique<cpt323::tree::tree>();
                /* read in each word from the file into our tree */
                std::string line;
                while (std::getline(in, line))
                {
                        newtree->add(line);
                }
        }
        catch (std::bad_alloc& ba)
        {
                /* handle memory allocation errors */
                perror("failed to allocate memory");
                return nullptr;
        }
        catch (std::ios::failure& iff)
        {
                /* handle errors other than if we have reached the end of the
                 * file */
                if (!in.eof())
                {
                        perror("failed to read file");
                        return nullptr;
                }
        }
        catch (std::exception& ex)
        {
                std::cerr << "An error occured: " << ex.what() << "\n";
        }
        return std::move(newtree);
}

bool cpt323::tree::tree::savefile(std::string_view filename,const cpt323::tree::tree& thetree)
{
        /* open the outpt file for writing */
        std::ofstream out(filename.data());

        if (!out)
        {
                perror("failed to open file for saving");
                return false;
        }
        /* specify the io exceptions to throw */
        out.exceptions(std::ios::failbit | std::ios::badbit);

        try
        {
                /* iterate over the tree and write out each line to the file */
                for (const auto& item : thetree)
                {
                        out << item << "\n";
                }
                out << std::flush;
                /* flush data to the file */
        }
        catch (std::ios::failure& iff)
        {
                /* handle all io errors */
                perror("failed to save the file");
                return false;
        }
        return true;
}