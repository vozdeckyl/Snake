#ifndef RESULT_H
#define RESULT_H

#include <map>
#include "objectid.h"

class IDrawable;

class Result {
    public:
        Result(const std::map<ObjectID,IDrawable*> & objects);

        ~Result();

        int getResultOfEelement(ObjectID id);

    private:
        std::map<ObjectID,int> * m_resultTable;
};

#endif