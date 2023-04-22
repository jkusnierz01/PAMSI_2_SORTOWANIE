#include "merge_sort.hh"


int main()
{   
    int n = 8;
    int tab[8] = {14,1,2,5,4,9,6,6};
    merge_sort(tab,n);
    for(int z =0;z<n;z++)
    {
       cout << tab[z] << " "; 
    }      
    return 0;
}