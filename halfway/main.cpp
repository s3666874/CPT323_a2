#include "main.h"

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
        std::string infile;
        std::string datastructure;
        std::vector<std::string> filenames;

        filenames.clear();

        po::options_description desc("options");

        desc.add_options()
            ("help", "produce help message")
            ("input,i", po::value<std::string>(&infile)->required(), "The file to import. Temporary")
            ("datastructure,d", po::value<std::string>(&datastructure)->required(), "The specified datastructure");

        po::variables_map vm;

        try
        {
                auto parsedOptions = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
                po::store(parsedOptions, vm);

                filenames = po::collect_unrecognized(parsedOptions.options, po::include_positional);

                if (vm.count("help") > 0)
                {
                        display_usage(argv[0]);
                        std::cout << "help text here\n";
                        return EXIT_SUCCESS;
                }

                po::notify(vm);

                if (datastructure.compare("list") == 0) {
                        auto thelist = cpt323::list::list::readfile(infile);

                        if (thelist) {
                                thelist->sort();
                        }
                } else if (datastructure.compare("tree") == 0) {
                        auto thetree = cpt323::tree::tree::readfile(infile);

                        if (thetree) {
                                thetree->sort();
                        }
                }
        }
        catch(const std::exception& e)
        {
                std::cerr << e.what() << "\n\n";
                display_usage(argv[0]);
                return EXIT_FAILURE;
        }
}

void display_usage(std::string_view view)
{
        std::cout << "You should call this program in the following way: \n\t" << view << " [args]\n";
        std::cout << "\nWhere [args] must include the following options: \n\n";
        std::cout << "-d followed by a datastructure type: the datastructure you want to make.\n";
        std::cout << "-i followed by a filename path: the filename of the file that holds the input data.\n";
        std::cout << "any input files you want to include in the merge sorter tool.\n";
}