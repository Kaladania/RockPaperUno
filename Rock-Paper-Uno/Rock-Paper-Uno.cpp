// Rock-Paper-Uno.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include "SetupFunctions.h"

bool isBanned(std::string playerName) { //checks if player's name is appropriate

    std::string bannedWord = ""; //current banned word to check

    std::ifstream banList;
    banList.open("BannedWords.txt");
    
    //runs through the ban list and checks if the player name includes one of the blacklisted words
    if (banList.is_open()) { 
        while (banList) {
            std::getline(banList, bannedWord);
            
            if (playerName == bannedWord) {
                banList.close();
                return true;
            }
        }
        banList.close();
        return false;
    }
}

struct UnoCard {
    int number; //stores card number
    int colourIndex; //stores card colour
    int powerUpIndex; //stores card power up
};

class Player { //player class

private:
    std::string name; //player name
    UnoCard hand[8]; //player hand
    bool isPlayersTurn; //stores if its the current instance's turn

public:
    std::string setPlayerName() { //sets player name (based on user input)

        bool nameIsInappropriate = false;
        std::string uncheckedName;

        std::cout << "Enter Name: ";
        std::cin >> uncheckedName;
        nameIsInappropriate = isBanned(uncheckedName);

        do {
            switch (nameIsInappropriate) {
            case true:
                printf("That name is banned. Please choose another name: ");
                std::cin >> uncheckedName;
                nameIsInappropriate = isBanned(uncheckedName);
                break;
            case false:
                break;
            }

            
        } while (nameIsInappropriate);


        std::string capitalizedCharacter(1, toupper(uncheckedName[0]));
        uncheckedName.replace(0, 1, capitalizedCharacter); //capitalizes name
        name = uncheckedName;

        return name;
        
    }
    
};

int main()
{
    std::string playerName = "";

    Player player;
    while (true) {
        playerName = player.setPlayerName();
        std::cout << "Hello! " << playerName << "\n";
        break;
    }
}