#ifndef QUICKSORT_HH
#define QUICKSORT_HH
#include "struct.hh"
#include <iostream>
using namespace std;


void quicksort(ranking_elem tab[], int tab_size, int first)
{
    float pivot = tab[(first + tab_size-1) / 2].ranking;
    int left = first, right = tab_size - 1;
    ranking_elem tmp;
    while (left <= right)
    {
        while (tab[left].ranking < pivot)
        {
            left++;
        }
        while (tab[right].ranking > pivot)
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