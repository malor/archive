template<class T>
int max_element(T arr[], int len)
{
    int max = 0;

    for (int i = 1; i < len; ++i)
    {
        if (arr[i] > arr[max])
            max = i;
    }

    return max;
}
