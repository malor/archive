template<class Iterator>
Iterator max_element(Iterator begin, Iterator end)
{
    Iterator max = begin;

    for (++begin; begin != end; ++begin)
    {
        if (*begin > * max)
            max = begin;
    }

    return max;
}
