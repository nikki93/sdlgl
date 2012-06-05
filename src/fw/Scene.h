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

        // do this in order of expected playback
        // must be on heap due to 'new': will 'delete' later internally
        static void add(Scene *scene) { _scenes.push_back(scene); }

        static void begin() { gotoScene(0); }
        static void shutdown() { _shutdown = true; }
        static void cleanup();

        // run scenes

        static bool updateCurrent(float elapsed)
        {
            if (_shutdown)
                return false;

            if (_currID >= 0)
                _scenes[_currID]->update(elapsed);
            return true;
        }
        static void drawCurrent()
        {
            if (_currID >= 0)
                _scenes[_currID]->draw();
        }
        static void stopCurrent()
        {
            if (_currID >= 0)
                _scenes[_currID]->stop();
        }
        static void handleRequests()
        {
            _gotoScene(_requestID); // _gotoScene() checks ID validity
            _requestID = -1;
        }

        // change scenes

        // request
        static void next(); // shutdown if last
        static void previous();
        static void gotoScene(ID id);

        // immediate
        static void _gotoScene(ID id);

        // get data

        static ID getCurrentID() { return _currID; }
        static Scene *getCurrentScene() // 0 if not running
        {
            return _currID >= 0 ? _scenes[_currID] : 0;
        }
};

#endif
