#include "merge_sort.hh"
#include "heap_sort.hh"
#include "quicksort.hh"
#include <fstream>
#include <string>
#include <sstream>

bool przeszukaj(string FileName, float * &TabPointer, int &Size) // funkcja tworzaca dynamiczna tablice
{
    int LineNumber;     // numer lini, w naszym otwieranym pliku tsv
    float Rating;       // odczytana wartosc ratingu filmu dodawana do wyjsciowej tablicy
    string Text;        // zmienna string w ktorej zapisywane sa cale linijki z pliku tsv do napotkania znaku '\n'
    string string_number;       // zmienna pomocnicza w ktorej zapisywany jest drugi wyraz z calej linijki - nasz rating
    ifstream File;          // zmienna plikowa           
    File.open(FileName);        // otiweramy plik
    if (File.good() == false) // jezeli plik nie zostal otwarty poprawnie to trzeba zakonczyc dzialanie
    {
        return false;
    }
    while (getline(File, Text))     //getline zwraca 1 gdy uda sie odczytac linijke wiec liczymy ile ich lest
    {
        LineNumber++;
    }
    Size = LineNumber -1 ;          // nie liczymy liniki 1 w ktorej sa zapisane naglowki kolumn
    try
    {
        TabPointer = new float[LineNumber - 1]; // deklarujemy dynamiczna tablice do ktorej bedziemy dodawac liczby
    }
    catch (bad_alloc &exception)        // sprawdzamy czy nie ma bledu alokacji tablicy
    {
        cerr << "bad_alloc detected: " << exception.what();     
    }
    LineNumber = 0;
    File.close();               // musimy zamknac plik i otworzyc ponownie aby po raz kolejny przelecec po kazdej lini lecz tym razem zczytujac liczby
    File.open(FileName);
    if (File.good() == false) // jezeli plik nie zostal otwarty poprawnie to trzeba zakonczyc dzialanie
    {
        return false;
    }
    while (getline(File, Text))
    {
        stringstream s(Text);           // klasa pozwalajaca wykonywac operacje na ciagach znakow - stringach jakby byly strumieniami - dzieki temu mozemy wyizolowac poszczegolne wyrazy
        if (LineNumber > 0)             // nie iteresuje nas pierwsza linijka z naglowkami
        {
            for (int i = 0; i<2; i++) // chcemy wyciagnac drugie slowo z calego napisu
            {
                s >> string_number;         // zapisujemy nasze wyrazy do zmiennej pomocniczej
            }
            Rating = stof(string_number);           //konwertujemy ja na float i dodajemy do tablicy
            TabPointer[LineNumber - 1] = Rating;
        }
        LineNumber++;
    }
    File.close();           
    return true;
}

int main()
{
    float *Pointer;     // wskaznika na dynamicznie zaalokowana pamiec
    int TabSize;        // rozmiar naszej dymanicznie zaalokowanej tablicy
    if (!przeszukaj("/Users/jedrzejkusnierz/Desktop/studia/pamsi/sortowanie - p2/PAMSI_2_SORTOWANIE/Ranking_filmow.tsv", Pointer,TabSize))
    {
        cout << "ERROR" << endl;
        return 0;
    }
    quicksort(Pointer,TabSize, 0);
    delete [] Pointer;
    

    // int n = 8;
    // int tab[8] = {14,1,2,5,4,9,6,6};
    // int tab2[8] = {12,5,2,1,4,3,6,6};
    // int tab3[8] = {10,5,8,1,4,2,9,7};
    // merge_sort(tab,n);
    // for(int z =0;z<n;z++)
    // {
    //    cout << tab[z] << " ";
    // }
    // cout<<endl;
    // sort(tab2,n);
    // for(int z =0;z<n;z++)
    // {
    //    cout << tab2[z] << " ";
    // }
    // cout<<endl;
    // quicksort(tab3, n, 0);
    // for(int z =0;z<n;z++)
    // {
    //    cout << tab3[z] << " ";
    // }
    // return 0;
}