#ifndef RESULT_H
#define RESULT_H

#include <map>
#include "IDrawable.h"

typedef unsigned int ObjectID;

using namespace std;

class Result {
    public:
        Result(const map<ObjectID,IDrawable*> & objects);

        ~Result();

        int getResultOfEelement(ObjectID id);

    private:
        map<ObjectID,int> * m_resultTable;
};

#endif