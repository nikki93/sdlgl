#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <map>
#include <list>

class Object
{
    public:
        typedef unsigned int ID;

    private:
        // all
        typedef std::map<ID, Object *> ObjectMap;
        static ObjectMap _objects;
        static std::list<ID> _toRemove;
        static ID _newID;

        // instance
        ID _id;

    public:
        // --- override -----------------------------------------------------

        virtual void update(float elapsed) {}
        virtual void draw() {}

        // --- object API ---------------------------------------------------

        ID getID();

        // --- manager API --------------------------------------------------

        static void add(Object *object); // will 'delete' internally
        static void remove(ID id);
        static void removeAll();

        static void updateAll(float elapsed);
        static void drawAll();
        static void handleRequests();
};

// --- inline definitions ---------------------------------------------------

inline Object::ID Object::getID()
{
    return _id;
}

inline void Object::remove(ID id)
{ 
    _toRemove.push_back(id); 
}

inline void Object::updateAll(float elapsed)
{
    for (ObjectMap::iterator i = _objects.begin(); 
            i != _objects.end(); ++i)
        i->second->update(elapsed);
}

inline void Object::drawAll()
{
    for (ObjectMap::iterator i = _objects.begin(); 
            i != _objects.end(); ++i)
        i->second->draw();
}

inline void Object::handleRequests()
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

#endif
