#include "Object.h"

Object::ID Object::_newID = 0;
std::map<Object::ID, Object *> Object::_objects = std::map<Object::ID, Object *>();
std::list<Object::ID> Object::_toRemove = std::list<Object::ID>();

void Object::add(Object *object)
{
    // if used, make new [XXX: infinite loop if too many objects!]
    while (_objects.find(_newID) != _objects.end())
        ++_newID;

    _objects.insert(std::make_pair(_newID, object));
    object->_id = _newID++;
}

void Object::removeAll()
{
    for (ObjectMap::iterator i = _objects.begin(); 
            i != _objects.end(); _objects.erase(i++))
        delete i->second;
}

