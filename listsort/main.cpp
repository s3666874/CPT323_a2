#include "main.h"

int main(int argc, char* argv[])
{
        std::string outname;
        std::string filename;

        boost::program_options::options_description desc("options");
        desc.add_options()("help,h", "print help messages")

        ("file,f",
                boost::program_options::value<std::string>(&filename)->required(),
                "the input file name to sort")
        ("output,o",
                boost::program_options::value<std::string>(&outname)->required(),
                "The file to output the sorted data into");
        
        boost::program_options::variables_map vm;

        try
        {
                boost::program_options::store(
                        boost::program_options::command_line_parser(argc, argv)
                                .options(desc)
                                .run(),
                        vm);

                if (vm.count("help") > 0)
                {
                        std::cout << "help text here\n";
                        return EXIT_SUCCESS;
                }

                boost::program_options::notify(vm);

                auto thelist = cpt323::reader::readfile(filename);

                if (thelist)
                {
                        thelist->sort();
                        cpt323::saver::saver::savefile(outname, *thelist);
                }
                else
                {
                        return EXIT_FAILURE;
                }
        }
        catch(std::exception& e)
        {
                std::cerr << e.what() << '\n';
                return EXIT_FAILURE;
        }
        


}