#include "Scene.h"

bool Scene::_shutdown = false;
Scene::ID Scene::_currID = -1;
Scene::ID Scene::_requestID = -1;
std::vector<Scene *> Scene::_scenes = std::vector<Scene *>();

void Scene::cleanup()
{
    SceneVector::iterator i = _scenes.begin();
    while (i != _scenes.end())
        delete *i++;
}

void Scene::next()
{
    if (_currID + 1 < _scenes.size())
        gotoScene(_currID + 1);
    else
        shutdown();
}
void Scene::previous()
{
    if (_currID - 1 >= 0)
        gotoScene(_currID - 1);
}
void Scene::gotoScene(ID id)
{
    _requestID = id;
}

void Scene::_gotoScene(ID id)
{
    if (id < 0 || id >= _scenes.size()) // bad ID
        return;

    if (_currID >= 0)
        _scenes[_currID]->stop();
    _currID = id;
    _scenes[_currID]->start();
}
