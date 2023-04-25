#ifndef MERGE_SORT_HH
#define MERGE_SORT_HH
#include <iostream>
using namespace std;

void merge(int left_array[], int right_array[], int main_array[], int left_size, int right_size, int main_size);
void merge_sort(int tab[], int rozmiar_tab)
{
    if (rozmiar_tab > 1) // sprawdzenie czy nasza tablica zostala podzielona juz na najmniejsza zawierajaca 1 element
    {
        int middle = rozmiar_tab / 2;      // dzielimy tablice na polowe
        int *left_array = new int[middle]; // tworzymy dwie dynamicznie zaalokowane podtablice - lewa i prawa - wynikajace z podzielenia naszej glownej tablicy
        int *right_array = new int[rozmiar_tab - middle];
        int j = 0;
        for (int i = 0; i < rozmiar_tab; i++) // przypisujemy do podtablic wartosci
        {
            if (i < middle)
            {
                left_array[i] = tab[i];
            }
            else
            {
                right_array[j] = tab[i];
                j++;
            }
        }
        merge_sort(left_array, middle); // rekurencyjnie wywolujemy funkcje dla lewej podtablicy a nastepnie dla prawej
        merge_sort(right_array, (rozmiar_tab - middle));
        merge(left_array, right_array, tab, middle, rozmiar_tab - middle, rozmiar_tab); // wywolujemy funkcje scalajaca
        delete[] left_array;
        delete[] right_array;
    }
}

void merge(int left_array[], int right_array[], int main_array[], int left_size, int right_size, int main_size)
{
    int tmp[main_size];
    int main_iterator = 0;
    int left_iterator = 0;
    int right_iterator = 0;
    while (left_iterator < left_size && right_iterator < right_size) // dopoki sa elementy w obu naszych podtablicach
    {
        if (left_array[left_iterator] < right_array[right_iterator]) // porownujemy je ze soba i w odpowiedniej kolejnosci dodajemy do glownej tablicy
        {
            tmp[main_iterator] = left_array[left_iterator];
            main_iterator++;
            left_iterator++;
        }
        else if (left_array[left_iterator] < right_array[right_iterator])
        {
            tmp[main_iterator] = left_array[left_iterator];
            main_iterator++;
            left_iterator++;
        }
        else
        {
            tmp[main_iterator] = right_array[right_iterator];
            main_iterator++;
            right_iterator++;
        }
    }
    if (left_iterator < left_size) // jezeli zostal jeden element w podtablicy lewej po prostu go dodajemy do glownej tablicy
    {
        tmp[main_iterator] = left_array[left_iterator];
        main_iterator++;
        left_iterator++;
    }
    if (right_iterator < right_size) // analogicznie do tego wyzej
    {
        tmp[main_iterator] = right_array[right_iterator];
        main_iterator++;
        right_iterator++;
    }
    for (int z = 0; z < main_size; z++)
    {
        main_array[z] = tmp[z];
    }
}

#endif