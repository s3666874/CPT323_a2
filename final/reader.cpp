namespace cpt323::reader
{
        std::unique_ptr<cpt323::list::list> cpt323::reader::readfile(std::string_view filename)
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
                                thelist->add(line);
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
}
