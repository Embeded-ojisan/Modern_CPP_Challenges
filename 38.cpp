namespace fs = std::filesystem;

class logger
{
    fs::path        logpath;
    std::ofstream   logfile;

public:
    logger()
    {
        auto name = uuids::to_string(uuids::uuid_random_generator{}());
        logpath = fs::temp_directory_path() / (name + ".tmp");
        logfile.open(logpath.c_str(), std::ios::out | std::ios::trunc);
    }

    ~logger() npxpect
    {
        try
        {
            if(logfile.is_open()) logfile.close();
            if(!logpath.empty()) gs::remove(logpath);
        }
        catch(..){
        }
    }
    
}