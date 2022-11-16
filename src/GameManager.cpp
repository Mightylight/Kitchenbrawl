#include "GameManager.hpp"
#include <fstream>


GameManager::GameManager(TextObject* playerStats, TextObject* enemyStats, TextObject* playerActions, TextObject* enemyActions, SpriteObject* playerSprite, SpriteObject* enemySprite) {
    this->playerStats = playerStats;
    this->enemyStats = enemyStats;
    this->enemyActions = enemyActions;
    this->playerActions = playerActions;
    this->playerSprite = playerSprite;
    this->enemySprite = enemySprite;
    ConstructEnemy();
}

GameManager::~GameManager(){}

void GameManager::PlayerTurn(options option) {
    if(!isPlayersTurn || isPlayerDead) return;
        switch (option) {
            case Sharpen:
                player.setAttack(player.getAttack() + 3);
                playerAction =
                        player.getName() + " sharpened it's edges. Its attack rose!";
                break;
            case Fortify:
                player.setDefense(player.getDefense() + 3);
                playerAction =
                        player.getName() + " fortified it's defenses. Its defense rose!";
                break;
            case Repair:
                player.setHP(player.getHP() + 3);
                playerAction =
                        player.getName() + " repaired itself. It's looking more shiny now.";
                break;
            case Attack:
                if (player.attackCharacter(enemy)) {
                    ConstructEnemy();
                    enemyAction =
                            "A new enemy approaches, it's " + enemy.getName();
                    isEnemyDead = true;
                    soundPlayer->setBuffer(sounds[2]);
                    soundPlayer->play();
                    highScore++;
                }
                playerAction =
                        player.getName() + " attacked " + enemy.getName() +
                        " for " + std::to_string(player.getAttack() + 3) + " damage.";
                break;
        }
        UpdateText();
        if(isEnemyDead) {
            isEnemyDead = false;
        } else {
            AI();
        }

}

//Make a random choice on what to do next
void GameManager::AI() {
    int random = rand() % 5;
    printf("%d\n",random);
    switch (random) {
        case 0:
            //attack
            if(enemy.attackCharacter(player)){
                GameOver();
            } else {
                enemyAction =
                        enemy.getName() + " attacked " + player.getName()
                        + " for " + std::to_string(enemy.getAttack() +3) + " damage.";
            }

            break;

        case 1:
            //fortify
            enemy.setDefense(enemy.getDefense() + 3);
            enemyAction =
                    enemy.getName() + " fortified it's defense. Its defense rose!";
            break;

        case 2:
            //repair
            enemy.setHP(enemy.getHP() + 3);
            enemyAction =
                    enemy.getName() + " repaired itself. It's looking more shiny now.";
            break;

        case 3:
            //sharpen
            enemy.setAttack(enemy.getAttack() + 3);
            enemyAction =
                    enemy.getName() + " sharpened it's edges. Its attack rose!";
            break;
        case 4:
            //do nothing
            printf("Test\n");
            enemyAction =
                    enemy.getName() + " is recharging, he's pretty slow";
            break;
    }
    UpdateText();
}

void GameManager::UpdateText() {
    playerStats->setText(
            "Name: " + player.getName() + "\n" +
            "Attack: " + std::to_string(player.getAttack())  +
            "   Defense: " + std::to_string(player.getDefense()) +
            "   HP: " + std::to_string(player.getHP())  +"\n"
            );

    enemyStats->setText(
            "Name: " + enemy.getName() + "\n" +
            "Attack: " + std::to_string(enemy.getAttack())  +
            "   Defense: " + std::to_string(enemy.getDefense()) +
            "   HP: " + std::to_string(enemy.getHP())  +"\n"
    );
    playerActions->setText(playerAction);
    enemyActions->setText(enemyAction);
}

void GameManager::ConstructEnemy() {
    maxHealth += 5;
    enemy.setHP(maxHealth);
    maxDef += 5;
    enemy.setDefense(maxDef);
    maxAttack += 5;
    enemy.setAttack(maxAttack);
    enemy.setName(enemyNames[rand() % (arraySize - 1)]);
    int random = rand() % (arraySize - 1);
    enemySprite->SetTexture(sprites[random]);
    enemy.sprite = random;
}

void GameManager::ConstructPlayer(classes classes){
    switch (classes) {
        case Frying_Pan:
            player.setName("Frying Pan");
            player.setHP(20);
            player.setDefense(6);
            player.setAttack(10);
            player.sprite = 0;
            playerSprite->SetTexture(sprites[0]);
            break;

        case Pizza_Cutter:
            player.setName("Pizza cutter");
            player.setHP(10);
            player.setDefense(6);
            player.setAttack(20);
            player.sprite = 1;
            playerSprite->SetTexture(sprites[1]);
            break;

        case Spatula:
            player.setName("Spatula");
            player.setHP(10);
            player.setDefense(20);
            player.setAttack(6);
            player.sprite = 2;
            playerSprite->SetTexture(sprites[2]);
            break;

        case Chefs_knife:
            player.setName("Chef's Knife");
            player.setHP(12);
            player.setDefense(12);
            player.setAttack(12);
            player.sprite = 3;
            playerSprite->SetTexture(sprites[3]);
            break;

        case Custom:
            std::ifstream savefile;
            savefile.open("savefile.cmgt");
            std::string values[10];
            if(savefile.is_open()){
                std::string line;
                int lineCount = 0;
                while(std::getline(savefile,line)){
                    values[lineCount] = line;
                    lineCount++;
                }
            }
            savefile.close();
            player.setName(values[0]);
            player.setAttack(std::stoi(values[1]));
            player.setDefense(std::stoi(values[2]));
            player.setHP(std::stoi(values[3]));
            playerSprite->SetTexture(sprites[std::stoi(values[4])]);
            enemy.setName(values[5]);
            enemy.setAttack(std::stoi(values[6]));
            enemy.setDefense(std::stoi(values[7]));
            enemy.setHP(std::stoi(values[8]));
            maxAttack = std::stoi(values[6]);
            maxDef = std::stoi(values[7]);
            maxHealth = std::stoi(values[8]);
            enemySprite->SetTexture(sprites[std::stoi(values[9])]);
            //TODO Update the enemy
            break;
    }
    playerAction = "";
    enemyAction = "";
    isPlayerDead = false;
    if(classes != classes::Custom){
        ConstructEnemy();
    }
    UpdateText();
}

void GameManager::ResetGame() {
    maxAttack = 0;
    maxDef = 0;
    maxHealth = 0;
    highScore = 0;
}

void GameManager::GameOver(){
    soundPlayer->setBuffer(sounds[3]);
    soundPlayer->play();
    fightScreenMusic->stop();
    isPlayerDead = true;
    enemyAction = enemy.getName() + " has killed you, your highscore is " + std::to_string(highScore) + ", return to main menu";
    playerAction = "";
    WriteHighScore();
}


void GameManager::WriteHighScore(){
    std::fstream highscoreFile;
    highscoreFile.open("highscore.cmgt", std::ios::in);
    int scores[5] = {0,0,0,0,0};
    if(highscoreFile.is_open()){
        std::string line;
        int lineCount = 0;
        while(std::getline(highscoreFile,line)){
            scores[lineCount] = std::stoi(line);
            lineCount++;
        }
    }
    highscoreFile.close();

    int score = highScore;
    for (int & i : scores) {
        if(i > highScore){
            continue;
        } else {
            int num = i;
            i = score;
            score = num;
        }
    }

    highscoreFile.open("highscore.cmgt", std::ios::out);
    for (int i = 0; i < 5; ++i) {
        highscoreFile << std::to_string(scores[i]) + "\n";
    }

}

void GameManager::WriteSaveFile() {
    std::ofstream saveFile;
    saveFile.open("savefile.cmgt");
    if(saveFile.is_open()){
        saveFile << player.getName() + "\n";
        saveFile << std::to_string(player.getAttack()) + "\n";
        saveFile << std::to_string(player.getDefense()) + "\n";
        saveFile << std::to_string(player.getHP()) + "\n";
        saveFile << std::to_string(player.sprite) + "\n";
        saveFile << enemy.getName() + "\n";
        saveFile << std::to_string(enemy.getAttack()) + "\n";
        saveFile << std::to_string(enemy.getDefense()) + "\n";
        saveFile << std::to_string(enemy.getHP()) + "\n";
        saveFile << std::to_string(enemy.sprite) + "\n";
    }
    saveFile.close();
}




