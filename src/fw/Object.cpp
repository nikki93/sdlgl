#include "Object.h"

Object::ID Object::_newID = 0;
std::map<Object::ID, Object *> Object::_objects = std::map<Object::ID, Object *>();
std::list<Object::ID> Object::_toRemove = std::list<Object::ID>();

void Object::handleRequests()
{
    // handle scheduled removals
    while (!_toRemove.empty())
    {
        ObjectMap::iterator i;
        if ((i = _objects.find(_toRemove.back())) != _objects.end())
        {
            delete i->second;
            _objects.erase(i);
        }
        _toRemove.pop_back();
    }
}

