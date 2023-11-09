// Rock-Paper-Uno.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <vector>
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

std::string indexToColour(const int index) { //converts the index to colour
    switch (index) {

    case 0:
        return "red";
    case 1:
        return "yellow";
    case 2:
        return "green";
    case 3:
        return "blue";
    }
}

struct UnoCard {
    int number = 0; //stores card number
    int colourIndex = 0; //stores card colour
    int powerUpIndex = 0; //stores card power up
}playerCard1, playerCard2, playerCard3, playerCard4, playerCard5, playerCard6, playerCard7, playerCard8, 
cpuCard1, cpuCard2, cpuCard3, cpuCard4, cpuCard5, cpuCard6, cpuCard7, cpuCard8, startingCard;

class participant { //base class for player and cpu

private:
    std::vector<UnoCard> hand; //player hand
    bool isPlayersTurn = false; //stores if its the current instance's turn

public:
    
    /*void generateHand(int(&drawnHand)[8][8]) { //creates a random hand of 8 cards

        //int drawnHand[8][8] = {};

        for (int i = 0; i < 8; i++) {

            for (int j = 0; j < 8; j++) {

                int randomNumber = rand() % 8;
                int randomColour = rand() % 4;

                drawnHand[i][0] = randomColour;
                drawnHand[i][1] = randomNumber;

            }

        }
    }*/

    void generateCard(int& cardColour, int& cardNumber) { //randomly generates a card

        cardColour = rand() % 4;
        cardNumber = rand() % 8;
    }

    std::vector<UnoCard> placeCard(const int& cardIndex, const UnoCard& discardCard){

        UnoCard chosenCard = hand[cardIndex];

        if (chosenCard.colourIndex == discardCard.colourIndex || chosenCard.number == discardCard.number) {

            //hand.empty(hand.begin());
        }

        return hand;

    }

    void addCard() {};
};

class Player : public participant { //dedicated player class

private:
    std::string name; //player name
    std::vector<UnoCard> hand;

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

    std::vector<UnoCard> handSetup(Player& player) { //'draws' 8 random cards

        player.generateCard(playerCard1.colourIndex, playerCard1.number);
        player.generateCard(playerCard2.colourIndex, playerCard2.number);
        player.generateCard(playerCard3.colourIndex, playerCard3.number);
        player.generateCard(playerCard4.colourIndex, playerCard4.number);
        player.generateCard(playerCard5.colourIndex, playerCard5.number);
        player.generateCard(playerCard6.colourIndex, playerCard6.number);
        player.generateCard(playerCard7.colourIndex, playerCard7.number);
        player.generateCard(playerCard8.colourIndex, playerCard8.number);

        hand.push_back(playerCard1);
        hand.push_back(playerCard2);
        hand.push_back(playerCard3);
        hand.push_back(playerCard4);
        hand.push_back(playerCard5);
        hand.push_back(playerCard6);
        hand.push_back(playerCard7);
        hand.push_back(playerCard8);

        return hand;
    }

    void showHand() { //reveals all the cards currently in the players hand

        printf("You currently have %i cards in your hand. They are the following:\n", hand.size());

        for (int i = 0; i < 8; i++) {

            std::cout << "\n" << i+1 << ". " << indexToColour(hand[i].colourIndex) << " " << hand[i].number << ",";

        }
    }

    int chosenAction() {//gets the player's chosen action and validates it

        int action = 0;

        printf("\nWhat would you like to do?\n1.Place a Card\t2.Pick up a Card\n");
        std::cin >> action;

        action = menuInputValidation(action, 2);

        return action;
    }
};

class CPU : public participant {//dedicated cpu class

private:
    std::vector<UnoCard> hand; //CPU hand (8 cards)

public:

    void handSetup(CPU& cpu) { //'draws' 8 random cards
        cpu.generateCard(cpuCard1.colourIndex, cpuCard1.number);
        cpu.generateCard(cpuCard2.colourIndex, cpuCard2.number);
        cpu.generateCard(cpuCard3.colourIndex, cpuCard3.number);
        cpu.generateCard(cpuCard4.colourIndex, cpuCard4.number);
        cpu.generateCard(cpuCard5.colourIndex, cpuCard5.number);
        cpu.generateCard(cpuCard6.colourIndex, cpuCard6.number);
        cpu.generateCard(cpuCard7.colourIndex, cpuCard7.number);
        cpu.generateCard(cpuCard8.colourIndex, cpuCard8.number);

        hand.push_back(cpuCard1);
        hand.push_back(cpuCard2);
        hand.push_back(cpuCard3);
        hand.push_back(cpuCard4);
        hand.push_back(cpuCard5);
        hand.push_back(cpuCard6);
        hand.push_back(cpuCard7);
        hand.push_back(cpuCard8);
    }
};

/*void handSetup(Player& player, Player& cpu) {
    player.generateHand(playerCard1.colourIndex, playerCard1.number);
    player.generateHand(playerCard2.colourIndex, playerCard2.number);
    player.generateHand(playerCard3.colourIndex, playerCard3.number);
    player.generateHand(playerCard4.colourIndex, playerCard4.number);
    player.generateHand(playerCard5.colourIndex, playerCard5.number);
    player.generateHand(playerCard6.colourIndex, playerCard6.number);
    player.generateHand(playerCard7.colourIndex, playerCard7.number);
    player.generateHand(playerCard8.colourIndex, playerCard8.number);

    cpu.generateHand(cpuCard1.colourIndex, cpuCard1.number);
    cpu.generateHand(cpuCard2.colourIndex, cpuCard2.number);
    cpu.generateHand(cpuCard3.colourIndex, cpuCard3.number);
    cpu.generateHand(cpuCard4.colourIndex, cpuCard4.number);
    cpu.generateHand(cpuCard5.colourIndex, cpuCard5.number);
    cpu.generateHand(cpuCard6.colourIndex, cpuCard6.number);
    cpu.generateHand(cpuCard7.colourIndex, cpuCard7.number);
    cpu.generateHand(cpuCard8.colourIndex, cpuCard8.number);
}*/

int main()
{
    //general setup
    srand(time(NULL));
    UnoCard discardCard; //stores the current card to be compared to
    participant* participantCurrentlyPlaying; //points to the participant currently playing

    
    //player information setup
    std::string playerName = "";
    std::vector<UnoCard> playerHand;
    int playerAction = 0;
    int cardToDiscard = 0;


    Player player;
    CPU cpu;


    //game loop setup
    int totalRounds = 0;

    cpu.generateCard(startingCard.colourIndex, startingCard.number);
    discardCard = startingCard;

    while (true) {
        playerName = player.setPlayerName();
        std::cout << "Hello! " << playerName << "\n";

        playerHand = player.handSetup(player);

        std::cout << "Round: " << totalRounds <<
            "\nThe card currently at the top of the discrard pile is a " << indexToColour(discardCard.colourIndex) << " " << discardCard.number << "\n";

        player.showHand();

        playerAction = player.chosenAction();

        switch (playerAction)
        {
        case 1:

            printf("\nEnter the index number of the card you wish to discard: ");
            std::cin >> cardToDiscard;
            cardToDiscard-= 1; //translates choice to maintain code accuracy
            menuInputValidation(cardToDiscard, playerHand.size());
            playerHand = player.placeCard(cardToDiscard-1, discardCard);
            break;
        case 2:
            player.addCard();
            break;
        }

        player.showHand();

        break;
    }
}