#include "Object.h"

Object::ID Object::_newID = 0;
std::map<Object::ID, Object *> Object::_objects = std::map<Object::ID, Object *>();
std::list<Object::ID> Object::_toRemove = std::list<Object::ID>();

void Object::updateAll(float elapsed)
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

    for (ObjectMap::iterator i = _objects.begin(); i != _objects.end(); ++i)
        i->second->update(elapsed);
}

void Object::drawAll()
{
    for (ObjectMap::iterator i = _objects.begin(); i != _objects.end(); ++i)
        i->second->draw();
}

