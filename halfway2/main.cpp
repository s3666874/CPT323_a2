#include "main.h"

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
        std::string infile;
        std::string outname;
        std::string datastructure;
        std::vector<std::string> filenames;

        filenames.clear();

        po::options_description desc("options");

        desc.add_options()
            ("help", "produce help message")
            ("input,i", po::value<std::string>(&infile)->required(), "The file to import. Temporary")
            ("datastructure,d", po::value<std::string>(&datastructure)->required(), "The specified datastructure")
            ("output,o", po::value<std::string>(&outname)->required(), "The file to output the sorted data into");

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

                std::cout << infile << std::endl;

/*
                std::cout << outname << std::endl;
                std::cout << datastructure << std::endl;

                for(int i = 0; i < filenames.size(); i++) {
                        std::cout << filenames[i] << std::endl;
                }
*/
/*
                std::ifstream in(filename.data());

                if (!in)
                {
                        std::cout << "File cannot be read" << std::endl;
                        return EXIT_FAILURE;
                }

                std::string line;
                while (std::getline(in, line))
                {
                        std::cout << line << std::endl;
                }
*/
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
        std::cout << "-o followed by a filename path: the filename of the file to output data into.\n";
        std::cout << "any input files you want to include in the merge sorter tool.\n";
}