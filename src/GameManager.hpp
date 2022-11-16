#pragma once

#include <SFML/Audio.hpp>
#include "character.hpp"
#include "textObject.hpp"
#include "spriteObject.hpp"

class GameManager {
private:
    void ConstructEnemy();
    std::string playerAction;
    std::string enemyAction;

    Character player = Character("Default","Head.png",1,1,1);
    Character enemy = Character("Default","Head.png",1,1,1);

    int maxHealth = 0;
    int maxDef = 0;
    int maxAttack = 0;
    bool isPlayersTurn = true;

    TextObject* playerStats;
    TextObject* enemyStats;
    TextObject* playerActions;
    TextObject* enemyActions;
    SpriteObject* playerSprite;
    SpriteObject* enemySprite;

    bool isEnemyDead;
    int highScore = 0;

    const int arraySize = 5;
    std::string enemyNames[5] = {
            "Billy",
            "Bob",
            "Chris",
            "Karen",
            "Cameron"
    };

    void WriteHighScore();

public:
    sf::Texture sprites[5];
    sf::SoundBuffer sounds[4];
    sf::Sound* soundPlayer;
    sf::Music* fightScreenMusic;

    enum options {Attack,Fortify,Repair,Sharpen};
    enum classes {Chefs_knife,Frying_Pan,Spatula,Pizza_Cutter,Custom};

    GameManager(TextObject* playerStats, TextObject* enemyStats, TextObject* playerActions, TextObject* enemyActions, SpriteObject* playerSprite, SpriteObject* enemySprite);

    void ConstructPlayer(classes classes);
    void UpdateText();
    void PlayerTurn(options option);
    void AI();

    ~GameManager();

    void ResetGame();

    void GameOver();

    void WriteSaveFile();

    bool isPlayerDead;
};
