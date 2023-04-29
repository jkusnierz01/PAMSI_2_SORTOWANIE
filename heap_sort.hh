#ifndef HEAP_SORT_HH
#define HEAP_SORT_HH
#include <iostream>
using namespace std;

void heapdown(float tab[], int tab_size)
{
    int iterator1 = 0;
    int iterator2 = 1;
    for(int i=0;i<tab_size;i++)
    {
        if(tab[iterator1]<tab[iterator2])
        {

            float tmp = tab[iterator2];
            tab[iterator2] = tab[iterator1];
            tab[iterator1] = tmp;   
            iterator1=0;
            iterator2=0;
            i=0;
        }
        iterator2++;
        if(i%2==1)
        {
            iterator1++;
        }
    } 
}

void sort(float tab[], int tab_size)
{
    float tab2[tab_size];
    int iterator = tab_size;
    for(int i=tab_size;i>1;i--)
    {
    heapdown(tab,i);
    float tmp = tab[0];
    tab[0] = tab[i - 1];
    tab[i - 1] = tmp;
    tab2[iterator] = tmp;
    }
}

#endif