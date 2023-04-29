#ifndef QUICKSORT_HH
#define QUICKSORT_HH
#include <iostream>
using namespace std;


void quicksort(float tab[], int tab_size, int first)
{
    float pivot = tab[(first + tab_size-1) / 2];
    int left = first, right = tab_size - 1;
    float tmp;
    while (left <= right)
    {
        while (tab[left] < pivot)
        {
            left++;
        }
        while (tab[right] > pivot)
        {
            right--;
        }
        if (left <= right)
        {
            tmp = tab[left];
            tab[left] = tab[right];
            tab[right] = tmp;
            left++;
            right--;
        }
    }
    if (first < right)
        quicksort(tab, right + 1, first);
    if (left < tab_size - 1)
        quicksort(tab, tab_size,left );
}
#endif