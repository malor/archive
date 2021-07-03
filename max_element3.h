template<class T>
const T* max_element(const T* begin, const T* end)
{
    const T* max = begin;

    for (++begin; begin != end; ++begin)
    {
        if (*begin > * max)
            max = begin;
    }

    return max;
}
