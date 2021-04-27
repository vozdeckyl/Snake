#include "result.h"

Result::Result(const map<ObjectID,IDrawable*> & objects)
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

Result::~Result()
{
    delete m_resultTable;
}

int Result::getResultOfEelement(ObjectID id)
{
    return m_resultTable->at(id);
}