#pragma once
#include <SFML/Window/Event.hpp>
#include <map>
#include <stack>
#include "scene.hpp"

class SceneHandler {
    private:
        std::map<std::string, Scene*> scenes;
        Scene* currentScene;
        std::stack<Scene*> scenesStack;
    public:
        SceneHandler(); 
        ~SceneHandler();
    public:
        void render(sf::RenderWindow& window) const;
        void update();
        void handleEvent(const sf::Event& event, sf::RenderWindow& window);

        void addScene(Scene& scene);
        void stackScene(std::string sceneName);
        void popScene();
        void LoadScene(std::string identifier);

};