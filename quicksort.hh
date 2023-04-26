#ifndef QUICKSORT_HH
#define QUICKSORT_HH
#include <iostream>
using namespace std;

void quicksort(int tab[], int tab_size, int first)
{
    if (tab_size > 1)
    {
        int right = tab_size - 2;
        int left = first;
        int tmp;
        int pivot = (first + tab_size) / 2;
        tmp = tab[tab_size - 1];
        tab[tab_size - 1] = tab[pivot];
        tab[pivot] = tmp;
        while (left <= right)
        {
            while (tab[right] > tab[tab_size - 1])
            {
                right--;
            }
            while (tab[left] < tab[tab_size - 1])
            {
                left++;
            }
            tmp = tab[left];
            tab[left] = tab[right];
            tab[right] = tmp;
            right--;
            left++;
        }
        tmp = tab[tab_size - 1];
        tab[tab_size - 1] = tab[left];
        tab[left] = tmp;
        quicksort(tab, right+1, first);
        quicksort(tab, tab_size, left);
    }
}

#endif