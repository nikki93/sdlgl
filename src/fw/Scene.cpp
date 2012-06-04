#include "Scene.h"

bool Scene::_shutdown = false;
Scene::ID Scene::_currID = -1;
Scene::ID Scene::_requestID = -1;
std::vector<Scene *> Scene::_scenes = std::vector<Scene *>();

