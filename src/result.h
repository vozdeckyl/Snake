#ifndef RESULT_H
#define RESULT_H

#include <map>
#include "window.h"

typedef unsigned int ObjectID;

using namespace std;

class Result {
    public:
        Result(const map<ObjectID,IDrawable*> & objects)
        {
            m_resultTable = new map<ObjectID,int>();

            for(pair<ObjectID,IDrawable*> pair : objects)
            {
                m_resultTable->insert({
                                        pair.first,
                                        pair.second->getResult()
                                    });
            }
        }

        ~Result()
        {
            delete m_resultTable;
        }

        int getResultOfEelement(ObjectID id)
        {
            return m_resultTable->at(id);
        }

    private:
        map<ObjectID,int> * m_resultTable;
};

#endif