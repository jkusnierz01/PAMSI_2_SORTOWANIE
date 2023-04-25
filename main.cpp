#include "merge_sort.hh"
#include "heap_sort.hh"
#include "quicksort.hh"


int main()
{   
    int n = 8;
    int tab[8] = {14,1,2,5,4,9,6,6};
    int tab2[8] = {12,5,2,1,4,3,6,6};
    merge_sort(tab,n);
    for(int z =0;z<n;z++)
    {
       cout << tab[z] << " "; 
    }
    cout<<endl;
    sort(tab2,n);  
    for(int z =0;z<n;z++)
    {
       cout << tab2[z] << " "; 
    }  
    return 0;
}