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

        ID getID()
        {
            return _id;
        }

        // --- manager API --------------------------------------------------

        // must be on heap due to 'new': will 'delete' later internally
        static void add(Object *object);
        static void remove(ID id) { _toRemove.push_back(id); }
        static void removeAll()
        {
            for (ObjectMap::iterator i = _objects.begin(); 
                    i != _objects.end(); _objects.erase(i++))
                delete i->second;
        }

        static void updateAll(float elapsed)
        {
            for (ObjectMap::iterator i = _objects.begin(); 
                    i != _objects.end(); ++i)
                i->second->update(elapsed);
        }
        static void drawAll()
        {
            for (ObjectMap::iterator i = _objects.begin(); 
                    i != _objects.end(); ++i)
                i->second->draw();
        }
        static void handleRequests();
};

#endif
