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
        //ID id;

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
        inline static void add(Scene *scene)
        {
            _scenes.push_back(scene);
        }

        inline static void begin()
        {
            gotoScene(0);
        }
        inline static void shutdown()
        {
            _shutdown = true;
        }
        inline static void cleanup()
        {
            SceneVector::iterator i = _scenes.begin();
            while (i != _scenes.end())
                delete *i++;
        }

        inline static bool updateCurrent(float elapsed)
        {
            if (_shutdown)
                return false;

            if (_currID >= 0)
                _scenes[_currID]->update(elapsed);
            return true;
        }
        inline static void drawCurrent()
        {
            if (_currID >= 0)
                _scenes[_currID]->draw();
        }
        inline static void stopCurrent()
        {
            if (_currID >= 0)
                _scenes[_currID]->stop();
        }
        inline static void handleRequests()
        {
            _gotoScene(_requestID); // _gotoScene() checks ID validity
            _requestID = -1;
        }

        // change scene

        // request
        inline static void next() // shutdown if last
        {
            if (_currID + 1 < _scenes.size())
                gotoScene(_currID + 1);
            else
                shutdown();
        }
        inline static void previous()
        {
            if (_currID - 1 >= 0)
                gotoScene(_currID - 1);
        }
        inline static void gotoScene(ID id)
        {
            _requestID = id;
        }

        // immediate
        inline static void _gotoScene(ID id)
        {
            if (id < 0 || id >= _scenes.size()) // bad ID
                return;

            if (_currID >= 0)
                _scenes[_currID]->stop();
            _currID = id;
            _scenes[_currID]->start();
        }

        // get data

        inline static ID getCurrentID() { return _currID; }
        inline static Scene *getCurrentScene() // 0 if not running
        {
            return _currID >= 0 ? _scenes[_currID] : 0;
        }
};

#endif
