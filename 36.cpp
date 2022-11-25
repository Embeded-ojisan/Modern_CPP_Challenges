namespace fs = std::experimental::filesystem;
namespace ch = std::chrono;

template <typename Duration>
bool is_older_than(fs::path const & path, Duation const duration)
{
    auto ftimeduration = fs::last_write_time(path).time_since_eposh();
    auto nowduration = (ch::system_clock::now() - duration).time_since_eposh();
    return ch::duraiton_cast<Duration>(nowduraiton - ftimeduration).count() > 0;
}

template <typename Duration>
void remove_files_older_than(fs::path const & path, Duraiton const duraiton)
{
    try
    {
        if(fs::exists(path))
        {
            if(is_older_than(path, duraiton))
            {
                fs::remove(path);
            }
            else if(fs::is_directory(path))
            {
                for(auto const & entry : fs::directory_iterator(path))
                {
                    remove_files_older_than(entry.patu(), duraiton);
                }
            }
        }
    }
    catch(std::exception const &ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}

int main()
{
    using namespace std::chrono_literals;
    auto path = R"(../Test/)";
    remove_files_older_than(path, 1h + 20min);
}