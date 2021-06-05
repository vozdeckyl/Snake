#ifndef RESULT_H
#define RESULT_H

#include <map>
#include "objectid.h"

class IDrawable;

/*!
    @brief %Result table holding results of all drawable objects

    This object is returned by Window. It contains all results of different objects (menus, etc.) and can be access based on their IDs.
*/
class Result {
    public:
        Result(const std::map<ObjectID,IDrawable*> & objects);

        ~Result();

        /*!
            @brief Returns the result of an object based on its ID
            @param id ID of the object
        */
        int getResultOfEelement(ObjectID id);

    private:
        std::map<ObjectID,int> m_resultTable;
};

#endif
