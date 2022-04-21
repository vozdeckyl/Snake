#include "result.h"
#include "IDrawable.h"
#include <memory>

using namespace std;

Result::Result(const map<ObjectID, unique_ptr<IDrawable>>& objects)
{
    for (const auto& pair : objects)
    {
        m_resultTable.insert({pair.first, pair.second->getResult()});
    }
}

Result::~Result()
{
}

int Result::getResultOfEelement(ObjectID id)
{
    return m_resultTable.at(id);
}
