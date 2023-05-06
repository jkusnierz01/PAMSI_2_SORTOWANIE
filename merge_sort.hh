#ifndef MERGE_SORT_HH
#define MERGE_SORT_HH
#include "struct.hh"
#include <iostream>
using namespace std;

void merge(ranking_elem left_array[], ranking_elem right_array[], ranking_elem array[], int sizeof_left, int sizeof_right)
{
    int i = 0, j = 0, k = 0;
    while (sizeof_left > 0 && sizeof_right > 0)
    {

        if (left_array[i].ranking <= right_array[j].ranking)
        {
            array[k] = left_array[i];
            k++;
            i++;
            sizeof_left--;
        }
        else
        {
            array[k] = right_array[j];
            k++;
            j++;
            sizeof_right--;
        }
    }
    while (sizeof_left > 0)
    {
        array[k] = left_array[i];
        k++;
        i++;
        sizeof_left--;
    }
    while (sizeof_right > 0)
    {
        array[k] = right_array[j];
        k++;
        j++;
        sizeof_right--;
    }
}
void mergeSort(ranking_elem array[], int size)
{

    if (size > 1)
    {
        int middle, i;
        middle = size / 2;
        ranking_elem *left_array = new ranking_elem[middle];
        ranking_elem *right_array = new ranking_elem[size - middle];
        for (i = 0; i < middle; i++)
        {
            left_array[i] = array[i];
        }
        for (int j = 0; j < size-middle; j++)
        {
            right_array[j] = array[i];
            i++;
        }
        mergeSort(left_array, middle);
        mergeSort(right_array, size - middle);
        merge(left_array,right_array,array, middle,size-middle);
        delete[] left_array;
        delete[] right_array;
    }
    else
        return;
}

#endif