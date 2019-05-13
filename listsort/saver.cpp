#include "saver.h"

bool cpt323::saver::saver::savefile(std::string_view filename, const cpt323::list::list& thelist)
{
        /* open the file for output */
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
                /* iterate over the list, writing out each element */
                for (const auto& item : thelist)
                {
                        out << item << "\n";
                }
                out << std::flush;
        }
        catch (std::ios::failure& iff)
        {
                /* handle any errors in writing */
                perror("failed to save the file");
                return false;
        }
        return true;
}