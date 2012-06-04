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

        inline ID getID()
        {
            return _id;
        }

        // --- manager API --------------------------------------------------

        // must be on heap due to 'new': will 'delete' later internally
        inline static void add(Object *object)
        {
            // if used, make new [XXX: infinite loop if too many objects!]
            while (_objects.find(_newID) != _objects.end())
                ++_newID;

            _objects.insert(std::make_pair(_newID, object));
            object->_id = _newID++;
        }
        inline static void remove(ID id)
        {
            _toRemove.push_back(id);
        }
        inline static void removeAll()
        {
            for (ObjectMap::iterator i = _objects.begin(); 
                    i != _objects.end(); _objects.erase(i++))
                delete i->second;
        }

        inline static void updateAll(float elapsed)
        {
            for (ObjectMap::iterator i = _objects.begin(); i != _objects.end(); ++i)
                i->second->update(elapsed);
        }
        inline static void drawAll()
        {
            for (ObjectMap::iterator i = _objects.begin(); i != _objects.end(); ++i)
                i->second->draw();
        }
        static void handleRequests();
};

#endif
