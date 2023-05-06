#ifndef HEAP_SORT_HH
#define HEAP_SORT_HH
#include <iostream>
#include "struct.hh"
using namespace std;




void heapify(ranking_elem arr[], int TabSize, int LastRootIndex)        //funkcja tworzaca drzewo binarne
{
    ranking_elem tmp;           // zmienna pomocnicz
    int last = LastRootIndex;       //indeks ostatniego wezla rodzica
    int left = 2 * LastRootIndex + 1;       //indeksy lewego i prawego dziecka ostatniego rodzica
    int right = 2 * LastRootIndex + 2;

    if (left < TabSize && arr[left].ranking > arr[last].ranking)        // porownujemy czy dzieci wieksze od rodzica
        last = left;                                                    // jezeli tak to zamieniamy indeksy zeby potem podmienic elementy

    if (right < TabSize && arr[right].ranking > arr[last].ranking)
        last = right;

    if (last != LastRootIndex) {
        tmp = arr[LastRootIndex];
        arr[LastRootIndex] = arr[last];
        arr[last] = tmp;
        heapify(arr, TabSize, last);
    }
}

void heapSort(ranking_elem arr[], int n)
{
    ranking_elem tmp;
    for (int i = n / 2 - 1; i >= 0; i--)        // wywolujemy petle sprawdzajaca od ostatniego rodzica w gore drzewa
        heapify(arr, n, i);                     

    for (int i = n - 1; i >= 0; i--) {
        tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        heapify(arr, i, 0);
    }
}

#endif