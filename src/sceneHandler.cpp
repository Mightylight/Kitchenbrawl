#include "sceneHandler.hpp"

SceneHandler::SceneHandler() { }

SceneHandler::~SceneHandler() { }

void SceneHandler::render(sf::RenderWindow& window) const {
//    if(this->scenesStack.size() != 0) {
//        this->scenesStack.top()->render(window);
//    }
    currentScene->render(window);
}

void SceneHandler::update() {
//    if(this->scenesStack.size() != 0) {
//        this->scenesStack.top()->update();
//    }
    currentScene->update();
}

void SceneHandler::addScene(Scene& scene) {
    this->scenes.emplace(scene.getIdentifier(), &scene);
//    if(this->scenes.size() == 1) {
//        this->stackScene(scene.getIdentifier());
//    }
}

void SceneHandler::stackScene(std::string sceneName) {
//    this->scenesStack.push(scenes[sceneName]);
}

void SceneHandler::popScene(void) {
//    this->scenesStack.pop();
}

void SceneHandler::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
//    if(this->scenesStack.size() != 0) {
//        this->scenesStack.top()->handleEvent(event,window);
//    }
    currentScene->handleEvent(event,window);
}

void SceneHandler::LoadScene(std::string identifier) {
    currentScene = scenes.at(identifier);
}

