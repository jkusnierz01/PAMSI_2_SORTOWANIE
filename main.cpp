#include "merge_sort.hh"
#include "heap_sort.hh"
#include "quicksort.hh"
#include <fstream>
#include <string>
#include <sstream>

bool CreateRankingTab(string FileName, ranking_elem *&TabPointer, int &Size) // funkcja tworzaca dynamiczna tablice
{
    int LineNumber, t_const_number; // numer lini, w naszym otwieranym pliku tsv
    float Rating;                   // odczytana wartosc ratingu filmu dodawana do wyjsciowej tablicy
    string Text;                    // zmienna string w ktorej zapisywane sa cale linijki z pliku tsv do napotkania znaku '\n'
    string t_const;
    string string_ranking_number; // zmienna pomocnicza w ktorej zapisywany jest drugi wyraz z calej linijki - nasz rating
    ifstream File;                // zmienna plikowa
    File.open(FileName);          // otiweramy plik
    LineNumber = 0;
    if (File.good() == false)     // jezeli plik nie zostal otwarty poprawnie to trzeba zakonczyc dzialanie
    {
        return false;
    }
    if (Size == 0)
    {
        while (getline(File, Text)) // getline zwraca 1 gdy uda sie odczytac linijke wiec liczymy ile ich lest
        {
            LineNumber++;
        }
        Size = LineNumber - 1; // nie liczymy liniki 1 w ktorej sa zapisane naglowki kolumn
        File.close();          // musimy zamknac plik i otworzyc ponownie aby po raz kolejny przelecec po kazdej lini lecz tym razem zczytujac liczby
        File.open(FileName);
        if (File.good() == false) // jezeli plik nie zostal otwarty poprawnie to trzeba zakonczyc dzialanie
        {
            return false;
        }
    }
    try
    {
        TabPointer = new ranking_elem[Size]; // deklarujemy dynamiczna tablice do ktorej bedziemy dodawac liczby
    }
    catch (bad_alloc &exception) // sprawdzamy czy nie ma bledu alokacji tablicy
    {
        cerr << "bad_alloc detected: " << exception.what();
    }
    LineNumber = 0;
    while (getline(File, Text) && LineNumber <= Size + 1)
    {
        stringstream s(Text); // klasa pozwalajaca wykonywac operacje na ciagach znakow - stringach jakby byly strumieniami - dzieki temu mozemy wyizolowac poszczegolne wyrazy
        if (LineNumber > 0)   // nie iteresuje nas pierwsza linijka z naglowkami
        {
            s >> t_const;                         // z calej lini wyciagamy pierwsze oraz drugie slowo
            s >> string_ranking_number;           // zapisujemy nasze wyrazy do zmiennej pomocniczej
            Rating = stof(string_ranking_number); // konwertujemy ja na float i dodajemy do tablicy
            t_const.erase(0, 2);
            t_const_number = stoi(t_const);
            TabPointer[LineNumber - 1].ranking = Rating;
            TabPointer[LineNumber - 1].tconst = t_const_number;
        }
        LineNumber++;
    }
    File.close();
    return true;
}
int binary_search(int t_const_number, ranking_elem *&TitleTabPointer, int TitleTabSize) // funkcja wyszukujaca binarnie indeksu elementu, ktorego zmienna tconst pokrywa sie z szukana
{
    int left = 0;
    int middle = (left + TitleTabSize) / 2;
    while (TitleTabPointer[middle].tconst != t_const_number) // sprawdzamy czy szukany element jest wybranym elementem srodkowym
    {
        if (TitleTabPointer[middle].tconst < t_const_number) // sprawdzamy czy element jest wiekszy czy mniejszy, wiemy ze elementy sa posortowane
        {
            left = middle + 1; // jezeli jest wiekszy niz srodkowy to ograniczamy sie tylko do prawej strony tablicy
        }
        else
        {
            TitleTabSize = middle - 1; // jezeli mniejszy to ograniczamy sie do lewej strony tablicy
        }
        middle = (left + TitleTabSize) / 2;
    }
    return middle;
}
bool CreateTitleTab(string FileName, ranking_elem *&TitleTabPointer, int &TitleTabSize) // funkcja w ktorej otwieramy drugi plik z danymi referencyjnymi - tytulami oraz tconst
{
    ifstream File;                                          // zmienna plikowa do odczytu z pliku
    string Line, t_const_file, title_file, title_type_file; // zmienne pomocnicze sluzace do odczytywania poszczegolnych stringow z pliku                              // wskaznik na dymanicznie alokowowana tablice struktur danych ranking_elem
    int index, t_const_number;                              // 't_const_number zmienna pomocnicza uzywana przy konwersji stringa na inta
    int LineNumber = 0;                                     // zmienna pomocnicza do przemieszania sie po tablicy oraz pozwalajaca wyznaczyc potrzebny rozmiar do alokacji
    File.open(FileName);
    if (File.good() == false) // jezeli plik nie zostal otwarty poprawnie to trzeba zakonczyc dzialanie
    {
        cout << "Opening File Error" << endl;
        return false;
    }
    while (getline(File, Line)) // getline zwraca 1 gdy uda sie odczytac linijke wiec liczymy ile ich jest
    {
        LineNumber++;
    }
    LineNumber--; // nie liczymy liniki 1 w ktorej sa zapisane naglowki kolumn
    TitleTabSize = LineNumber;
    File.close(); // musimy zamknac plik i otworzyc ponownie aby po raz kolejny przelecec po kazdej lini lecz tym razem zczytujac t_const i tytuly
    File.open(FileName);
    if (File.good() == false) // jezeli plik nie zostal otwarty poprawnie to trzeba zakonczyc dzialanie
    {
        return false;
    }
    try
    {
        TitleTabPointer = new ranking_elem[LineNumber]; // deklarujemy dynamiczna tablice 2 wymiarowa w ktorej bedziemy zapisywac t_const i tytuly
    }
    catch (bad_alloc &exception) // sprawdzamy czy nie ma bledu alokacji tablicy
    {
        cerr << "bad_alloc detected: " << exception.what();
    }
    LineNumber = 0;
    while (getline(File, Line)) // uzupełniamy nasza tablice dwuwymiarowa - tconst i tutulami filmow
    {
        getline(File, t_const_file, '\t'); // z kazdej lini odczytujemy po kolei przedzielone tabulatorami stringi - wykorzystujemy 1 i 3 - t_const i title
        getline(File, title_type_file, '\t');
        getline(File, title_file, '\t');
        t_const_file.erase(0, 2);                            // pozbywamy sie z t_const 2 pierwszych znakow aby przekonwertowac na liczbe
        t_const_number = stoi(t_const_file);                 // konwersja stringa na inta
        TitleTabPointer[LineNumber].tconst = t_const_number; // zapisujemy obydwie zmienne do utworzonej tablicy strukur aby dalo sie przeszukiwac binarnie
        TitleTabPointer[LineNumber].title = title_file;
        LineNumber++;
    }
    File.close();

    return true;
}

bool OutputFileCreation(ranking_elem *&RankingTabPointer, ranking_elem *&TitleTabPointer, int RatingTabSize, int TitleTabSize, string OutputFileName)
{
    fstream plik_wyj;                        // zmienna plikowa do zapisy pliku wyjsciowego
    int index;                               // zmienna index przechowuje index znalezionego binarnie elementu tablicy
    plik_wyj.open(OutputFileName, ios::out); // otwieramy plik do zapisu
    plik_wyj << "tconst"
             << "\t"
             << "Rating"
             << "\t"
             << "Title" << '\n';
    for (int f = 0; f < RatingTabSize; f++) // w petli zapisujemy do pliku 'tconst', 'rating', 'title'
    {
        index = binary_search(RankingTabPointer[f].tconst, TitleTabPointer, TitleTabSize);
        plik_wyj << RankingTabPointer[f].tconst << '\t' << RankingTabPointer[f].ranking << '\t' << TitleTabPointer[index].title << '\n';
    }
    plik_wyj.close();
    return true;
}

int main()
{
    string sort_method[3] = {"quick", "merge", "heap"};
    int data_size[5] = {10000, 100000, 500000, 1000000, 0};
    int RozmiarTablicyRankingow; // rozmiar naszej dymanicznie zaalokowanej tablicy
    int RozmiarTablicyTytulow = 0;
    string method;
    string nazwa_pliku_wyjsciowego = "xxxx";
    ranking_elem *TablicaTytulowWskaznik;
    if (!CreateTitleTab("/Users/jedrzejkusnierz/Desktop/studia/pamsi/sortowanie - p2/PAMSI_2_SORTOWANIE/referencyjne.tsv", TablicaTytulowWskaznik, RozmiarTablicyTytulow))
    {
        cout << "ERROR DURING TITLE TAB CREATION" << endl;
        return 0;
    }
    for (int k = 0; k < 5; k++)
    {
        RozmiarTablicyRankingow = data_size[k];
        for (int n = 0; n < 3; n++)
        {
            ranking_elem *TablicaRankingWskaznik; // wskaznika na dynamicznie zaalokowana pamiec
            nazwa_pliku_wyjsciowego.erase();
            if (!CreateRankingTab("/Users/jedrzejkusnierz/Desktop/studia/pamsi/sortowanie - p2/PAMSI_2_SORTOWANIE/Ranking_filmow.tsv", TablicaRankingWskaznik, RozmiarTablicyRankingow))
            {
                cout << "ERROR DURING RANKING TAB CREATION" << endl;
                return 0;
            }
            if (n == 0)
            {
                auto start_time = std::chrono::high_resolution_clock::now();
                quicksort(TablicaRankingWskaznik, RozmiarTablicyRankingow, 0);
                auto end_time = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
                cout << "Posortowanie za pomoca QUICKSORT zajelo: " << duration.count() << "ms, bazy danych wielkosci: " << RozmiarTablicyRankingow << " elementow" << endl;
                nazwa_pliku_wyjsciowego = sort_method[n];
                nazwa_pliku_wyjsciowego.append(to_string(RozmiarTablicyRankingow));
                nazwa_pliku_wyjsciowego.append(".tsv");
            }
            else if (n == 1)
            {
                auto start_time = std::chrono::high_resolution_clock::now();
                mergeSort(TablicaRankingWskaznik, RozmiarTablicyRankingow);
                auto end_time = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
                cout << "Posortowanie za pomoca MERGESORT zajelo: " << duration.count() << "ms, bazy danych wielkosci: " << RozmiarTablicyRankingow << " elementow" << endl;
                nazwa_pliku_wyjsciowego = sort_method[n];
                nazwa_pliku_wyjsciowego.append(to_string(RozmiarTablicyRankingow));
                nazwa_pliku_wyjsciowego.append(".tsv");
            }
            else if (n == 2)
            {
                auto start_time = std::chrono::high_resolution_clock::now();
                heapSort(TablicaRankingWskaznik, RozmiarTablicyRankingow);
                auto end_time = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
                cout << "Posortowanie za pomoca HEAPSORT zajelo: " << duration.count() << "ms, bazy danych wielkosci: " << RozmiarTablicyRankingow << " elementow" << endl;
                nazwa_pliku_wyjsciowego = sort_method[n];
                nazwa_pliku_wyjsciowego.append(to_string(RozmiarTablicyRankingow));
                nazwa_pliku_wyjsciowego.append(".tsv");
            }
            if (!OutputFileCreation(TablicaRankingWskaznik, TablicaTytulowWskaznik, RozmiarTablicyRankingow, RozmiarTablicyTytulow, nazwa_pliku_wyjsciowego))
            {
                cout << "ERROR DURING RANKING TAB CREATION" << endl;
                return 0;
            }
            delete[] TablicaRankingWskaznik;
        }
    }
    delete[] TablicaTytulowWskaznik;
    return 0;
}