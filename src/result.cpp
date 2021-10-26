#include <memory>
#include "IDrawable.h"
#include "result.h"

using namespace std;

Result::Result(const map<ObjectID,unique_ptr<IDrawable>> & objects)
{
    for(const auto & pair : objects)
    {
        m_resultTable.insert({
                                pair.first,
                                pair.second->getResult()
                            });
    }
}

Result::~Result()
{
}

int Result::getResultOfEelement(ObjectID id)
{
    return m_resultTable.at(id);
}
