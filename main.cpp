#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "src/scene.hpp"
#include "src/textObject.hpp"
#include "src/character.hpp"
#include "src/button.hpp"
#include "src/quitButton.hpp"
#include "src/sceneHandler.hpp"
#include "src/GameManager.hpp"
#include "src/spriteObject.hpp"

void StartGame();

void UpdateHighScore(TextObject &highscoreText);

int main() {
    std::filesystem::current_path("Assets");
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Gaming moment!", sf::Style::Close);

    SceneHandler handler;
    Scene mainScreen("mainScreen");
    Scene characterSelectionScene("characterSelectionScene");
    Scene fightScreen("fightScreen");


    sf::Font font;
    font.loadFromFile("Minecraft.ttf");


    TextObject playerStats("playerStats",font,"TEST");
    playerStats.setPosition(sf::Vector2f(665,505));
    playerStats.setCharacterSize(28);
    TextObject enemyStats("enemyStats", font, "TEST");
    enemyStats.setPosition(sf::Vector2f(665,625));
    enemyStats.setCharacterSize(28);
    TextObject playerActions("playerActions", font ,"TEST");
    playerActions.setPosition(sf::Vector2f(665,445));
    playerActions.setCharacterSize(20);
    TextObject enemyActions("enemyActions", font, "TEST");
    enemyActions.setPosition(sf::Vector2f(25,445));
    enemyActions.setCharacterSize(20);
    SpriteObject playerSprite("playerSprite", "head.png");
    playerSprite.setPosition(sf::Vector2f(100,80));
    SpriteObject enemySprite("enemySprite", "head.png");
    enemySprite.setPosition(sf::Vector2f(800,80));



    GameManager manager(&playerStats, &enemyStats, &playerActions, &enemyActions, &playerSprite, &enemySprite);
    manager.sprites[0].loadFromFile("Frying_Pan.png");
    manager.sprites[1].loadFromFile("Pizza_Cutter.png");
    manager.sprites[2].loadFromFile("spatula.png");
    manager.sprites[3].loadFromFile("Knife.png");
    manager.sprites[4].loadFromFile("Pizza_Cutter.png");
    manager.sounds[0].loadFromFile("buff.wav");
    manager.sounds[1].loadFromFile("buttonClick.wav");
    manager.sounds[2].loadFromFile("enemyDeath.wav");
    manager.sounds[3].loadFromFile("playerDeath.wav");
    sf::Music mainMenuMusic;
    mainMenuMusic.openFromFile("main-menu.wav");
    mainMenuMusic.setLoop(true);
    mainMenuMusic.play();
    sf::Music fightScreenMusic;
    manager.fightScreenMusic = &fightScreenMusic;
    fightScreenMusic.openFromFile("fightMusic.wav");
    fightScreenMusic.setLoop(true);
    sf::Sound soundPlayer;
    manager.soundPlayer = &soundPlayer;



    std::filesystem::current_path("../");

    TextObject highScoreText("highScoreText", font, "");
    highScoreText.setCharacterSize(32);
    highScoreText.setPosition(sf::Vector2f(50,50));
    UpdateHighScore(highScoreText);

    Button startButton("startButton", font, "START", sf::Vector2f(192.5f,50.0f));
    startButton.setPosition(sf::Vector2f(543.75f,300.0f));
    startButton.setButtonAction([&handler, &characterSelectionScene, &manager](){
        manager.soundPlayer->setBuffer(manager.sounds[1]);
        manager.soundPlayer->play();
        handler.LoadScene(characterSelectionScene.getIdentifier());
    });

    Button eraseButton("eraseButton", font, "ERASE", sf::Vector2f(192.5f,50.0f));
    eraseButton.setPosition(sf::Vector2f(543.75f,420.0f));
    eraseButton.setButtonAction([&highScoreText, &manager](){
        manager.soundPlayer->setBuffer(manager.sounds[1]);
        manager.soundPlayer->play();
        remove("highscore.cmgt");
        remove("savefile.cmgt");
        UpdateHighScore(highScoreText);
    });

    Button continueButton("continueButton", font, "CONTINUE", sf::Vector2f(192.5f,50.0f));
    continueButton.setPosition(sf::Vector2f(543.75f,660.0f));
    continueButton.setButtonAction([&manager,&handler,&fightScreen, &mainMenuMusic, &fightScreenMusic](){
        manager.soundPlayer->setBuffer(manager.sounds[1]);
        manager.soundPlayer->play();
        std::fstream savefile("../");
        savefile.open("savefile.cmgt");
        if(savefile.is_open()) {
            manager.ConstructPlayer(GameManager::classes::Custom);
            mainMenuMusic.stop();
            fightScreenMusic.play();
            handler.LoadScene(fightScreen.getIdentifier());
        }
        savefile.close();
    });

    Button quitButton("quitButton", font, "QUIT", sf::Vector2f(192.5f, 50.0f));
    quitButton.setPosition(sf::Vector2f(543.75f, 540.0f));
    quitButton.setButtonAction([&window](){
        window.close();
    });

    TextObject selection("characterSelection", font, "CHOOSE YOUR CHARACTER");
    selection.setPosition(sf::Vector2f(543.75f,100.0f));
    selection.setCharacterSize(32);

    Button chef_knifeButton("chef_knifeButton", font, "CHEF'S KNIFE", sf::Vector2f(192.5f,50.0f));
    chef_knifeButton.setPosition(sf::Vector2f(543.75f,300.0f));
    chef_knifeButton.setButtonAction([&manager, &handler, &fightScreen, &mainMenuMusic, &fightScreenMusic](){
        manager.soundPlayer->setBuffer(manager.sounds[1]);
        manager.soundPlayer->play();
        manager.ConstructPlayer(GameManager::classes::Chefs_knife);
        mainMenuMusic.stop();
        fightScreenMusic.play();
        handler.LoadScene(fightScreen.getIdentifier());
    });

    Button spatulaButton("spatulaButton", font, "SPATULA", sf::Vector2f(192.5f,50.0f));
    spatulaButton.setPosition(sf::Vector2f(543.75f,375.0f));
    spatulaButton.setButtonAction([&manager, &handler, &fightScreen, &mainMenuMusic, &fightScreenMusic](){
        manager.soundPlayer->setBuffer(manager.sounds[1]);
        manager.soundPlayer->play();
        manager.ConstructPlayer(GameManager::classes::Spatula);
        mainMenuMusic.stop();
        fightScreenMusic.play();
        handler.LoadScene(fightScreen.getIdentifier());
    });

    Button fryingpanButton("fryingpanButton", font, "FRYING PAN", sf::Vector2f(192.5f,50.0f));
    fryingpanButton.setPosition(sf::Vector2f(543.75f,450.0f));
    fryingpanButton.setButtonAction([&manager, &handler, &fightScreen, &mainMenuMusic, &fightScreenMusic](){
        manager.soundPlayer->setBuffer(manager.sounds[1]);
        manager.soundPlayer->play();
        manager.ConstructPlayer(GameManager::classes::Frying_Pan);
        mainMenuMusic.stop();
        fightScreenMusic.play();
        handler.LoadScene(fightScreen.getIdentifier());
    });

    Button pizzacutterButton("pizzacutterButton", font, "PIZZA CUTTER", sf::Vector2f(192.5f,50.0f));
    pizzacutterButton.setPosition(sf::Vector2f(543.75f,525.0f));
    pizzacutterButton.setButtonAction([&manager, &handler, &fightScreen, &mainMenuMusic, &fightScreenMusic](){
        manager.soundPlayer->setBuffer(manager.sounds[1]);
        manager.soundPlayer->play();
        manager.ConstructPlayer(GameManager::classes::Pizza_Cutter);
        mainMenuMusic.stop();
        fightScreenMusic.play();
        handler.LoadScene(fightScreen.getIdentifier());
    });


    Button attackButton("attackButton", font, "ATTACK", sf::Vector2f(319,119));
    attackButton.setPosition(sf::Vector2f(0,480));
    attackButton.setButtonAction([&manager](){
        manager.soundPlayer->setBuffer(manager.sounds[1]);
        manager.soundPlayer->play();
        manager.PlayerTurn(GameManager::options::Attack);
    });

    Button repairButton("repairButton", font, "REPAIR", sf::Vector2f(319,119));
    repairButton.setPosition(sf::Vector2f(320,480));
    repairButton.setButtonAction([&manager](){
        manager.soundPlayer->setBuffer(manager.sounds[0]);
        manager.soundPlayer->play();
        manager.PlayerTurn(GameManager::options::Repair);
    });

    Button sharpenButton("sharpenButton", font, "SHARPEN", sf::Vector2f(319,119));
    sharpenButton.setPosition(sf::Vector2f(0,600));
    sharpenButton.setButtonAction([&manager](){
        manager.soundPlayer->setBuffer(manager.sounds[0]);
        manager.soundPlayer->play();
        manager.PlayerTurn(GameManager::options::Sharpen);
    });

    Button fortifyButton("fortifyButton", font, "FORTIFY", sf::Vector2f(319,119));
    fortifyButton.setPosition(sf::Vector2f(320,600));
    fortifyButton.setButtonAction([&manager](){
        manager.soundPlayer->setBuffer(manager.sounds[0]);
        manager.soundPlayer->play();
        manager.PlayerTurn(GameManager::options::Fortify);
    });

    Button backButton("backButton", font, "QUIT", sf::Vector2f(192.75f,50.0f));
    backButton.setButtonAction([&manager, &handler,&mainScreen, &highScoreText, &mainMenuMusic, &fightScreenMusic](){
        manager.soundPlayer->setBuffer(manager.sounds[1]);
        manager.soundPlayer->play();
        handler.LoadScene(mainScreen.getIdentifier());
        if(!manager.isPlayerDead) {
            manager.WriteSaveFile();
        }
        fightScreenMusic.stop();
        mainMenuMusic.play();
        UpdateHighScore(highScoreText);
        manager.ResetGame();
    });




    mainScreen.addGameObject(startButton);
    mainScreen.addGameObject(quitButton);
    mainScreen.addGameObject(highScoreText);
    mainScreen.addGameObject(eraseButton);
    mainScreen.addGameObject(continueButton);

    characterSelectionScene.addGameObject(selection);
    characterSelectionScene.addGameObject(chef_knifeButton);
    characterSelectionScene.addGameObject(spatulaButton);
    characterSelectionScene.addGameObject(fryingpanButton);
    characterSelectionScene.addGameObject(pizzacutterButton);

    fightScreen.addGameObject(attackButton);
    fightScreen.addGameObject(repairButton);
    fightScreen.addGameObject(fortifyButton);
    fightScreen.addGameObject(sharpenButton);
    fightScreen.addGameObject(playerStats);
    fightScreen.addGameObject(enemyStats);
    fightScreen.addGameObject(enemyActions);
    fightScreen.addGameObject(playerActions);
    fightScreen.addGameObject(playerSprite);
    fightScreen.addGameObject(enemySprite);
    fightScreen.addGameObject(backButton);

    handler.addScene(fightScreen);
    handler.addScene(characterSelectionScene);
    handler.addScene(mainScreen);

    handler.LoadScene(mainScreen.getIdentifier());
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else {
                handler.handleEvent(event,window);
                //if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                //printf(" x = %d\n y = %d\n", sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            }
        }

        window.clear(sf::Color(121, 173, 129));
        handler.update();
        handler.render(window);
        window.display();
    }

    return 0;
}

void UpdateHighScore(TextObject& highscoreText){
    std::fstream highscoreFile;
    highscoreFile.open("highscore.cmgt", std::ios::in);
    std::string scores[5] = {"0", "0", "0", "0", "0"};
    if(highscoreFile.is_open()){
        std::string line;
        int lineCount = 0;
        while(std::getline(highscoreFile,line)){
            scores[lineCount] = line;
            lineCount++;
        }
    }
    highscoreFile.close();

    std::string string;
    string = "Highscores:\n";
    for (int i = 0; i < 5; ++i) {
        string += "   " + std::to_string(i + 1) + ". " + scores[i] + "\n";
    }
    highscoreText.setText(string);
}






