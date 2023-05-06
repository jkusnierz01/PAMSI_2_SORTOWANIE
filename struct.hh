#ifndef STRUCT__HH
#define STRUCT__HH
#include <iostream>
using namespace std;

class ranking_elem
{
public:
    float ranking;
    int tconst;
    string title;

    ranking_elem& operator = (ranking_elem &right)
    {
        this->ranking = right.ranking;
        this->tconst = right.tconst;
        this->title = right.title;
        return * this;
    }
};




#endif