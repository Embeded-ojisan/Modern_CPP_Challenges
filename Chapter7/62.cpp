
template <typename Iterator, tyupename F>
auto pprocess(
    Iterator begin,
    Iterator end
)
{
    auto size = std::distance(
        begin,
        end
    );

    if(size <= 10000)
    {
        return std::forward<F>(f)(begin, end);
    }
    else
    {
        int const thread_count = std::hardware_conccurency();
        std::vector<std::thread> threads;
        std::vector<typename std::iterator_traits<Iterator>::value_type> mins(thread_count);

        auto first = begin;
        auto last = first;

        size /= thread_count;

        for(
            int i = 0;
            i < thread_count;
            i++
        )
        {
            first = last;
            if(i == thread_count - 1) last = end;
            else std::advance(last, size);

            threads.emplace_back(
                [first, last, &f, &r=mins[i]](){
                    r = std::forward<F>(f)(first, last);
                } 
            );
        }

        for(auto &t : threads) t.join();

        return std::forward<F>(f)(std::begin(mins), std::end(mins));
    }
}

template <typename Iterator>
auto pmin(
    Iterator begin,
    Itarator end
)
{
    return pprocess(
        begin,
        end,
        [](auto b, auto e){
            return *std::min_element(b, e);
        }
    );
}

template <typename Iterator>
auto pmax(
    Iterator begin,
    Itarator end
)
{
    return pprocess(
        begin,
        end,
        [](auto b, auto e){
            return *std::max_element(b, e);
        }
    );
}

int main()
{
    const size_t count = 10000000;
    std::vector<int> data(count);

    auto rmin = pmin(
        std::cbegin(data),
        std::cend(data)
    );

    auto rmax = pmax(
        std::cbegin(data),
        std::cend(data)
    );
}