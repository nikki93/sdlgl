#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>

class Scene
{
    public:
        typedef int ID; // hopefully we don't have too many scenes

    private:
        // all
        typedef std::vector<Scene *> SceneVector;
        static SceneVector _scenes;
        static bool _shutdown;
        static ID _currID; // initially -1
        static ID _requestID; // if no request, -1

        //instance
        //ID _id;

    public:
        // --- override -----------------------------------------------------

        virtual void start() {}
        virtual void update(float elapsed) {}
        virtual void draw() {}
        virtual void stop() {}

        // --- manager API --------------------------------------------------

        // manage scenes

        static void add(Scene *scene); // add in order of playback
        static void begin();
        static void shutdown();
        static void cleanup();

        // run scene

        static bool updateCurrent(float elapsed);
        static void drawCurrent();
        static void stopCurrent();
        static void handleRequests();

        // get scene

        static ID getCurrentID();
        static Scene *getCurrentScene(); // 0 if not running

        // change scene

        // request
        static void next(); // shutdown if last
        static void previous();
        static void gotoScene(ID id);

        // immediate
        static void _gotoScene(ID id);
};

// --- inline definitions ---------------------------------------------------

inline void Scene::add(Scene *scene) 
{ 
    _scenes.push_back(scene); 
}

inline void Scene::begin() 
{ 
    gotoScene(0); 
}

inline void Scene::shutdown() 
{ 
    _shutdown = true; 
}

inline bool Scene::updateCurrent(float elapsed)
{
    if (_shutdown)
        return false;

    if (_currID >= 0)
        _scenes[_currID]->update(elapsed);
    return true;
}

inline void Scene::drawCurrent()
{
    if (_currID >= 0)
        _scenes[_currID]->draw();
}

inline void Scene::stopCurrent()
{
    if (_currID >= 0)
        _scenes[_currID]->stop();
}

inline void Scene::handleRequests()
{
    _gotoScene(_requestID); // _gotoScene() checks ID validity
    _requestID = -1;
}

inline Scene::ID Scene::getCurrentID() 
{ 
    return _currID; 
}

inline Scene *Scene::getCurrentScene()
{
    return _currID >= 0 ? _scenes[_currID] : 0;
}

#endif
