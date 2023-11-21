#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <map>
#include <algorithm>
#include <vector>
#define FOUNDIN(dataToSearch, itemToFind) (dataToSearch.find(itemToFind) != std::string::npos) //shorthand to make writing code to find existing items easier
//#define FOUNDINCOLLECTION(dataToSearch, itemToFind, collectionLength) ((std::find(dataToSearch, dataToSearch+collectionLength, itemToFind)) != std::end(validCommands)) //exclusive FOUNDIN definition for pointers
#define LENGTHOF(arrayToCheck) sizeof(arrayToCheck) / sizeof(arrayToCheck[0]) //shorthand to quickly determine the length of an array

//validates menu input
int menuInputValidation(int optionChosen, int optionMax) //validates a user's input
{

    //runs until it gains a valid input
    //checks to see if the input is out of range or not an int
    while ((optionChosen > optionMax) || (optionChosen < 1) || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "That is an invalid input. \nPlease chose a number within the range provided (1 - " << optionMax << "): ";
        std::cin >> optionChosen;
    }

    return optionChosen; //returns the validated input
}

//checks if player's name is appropriate
bool isBanned(std::string playerName) {

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

//converts the index to colour
std::string indexToColour(const int index) {
    switch (index) {

    case 0:
        return "Red";
    case 1:
        return "Yellow";
    case 2:
        return "Green";
    case 3:
        return "Blue";
    }
}

//prints the cards in colour
void printColour(const int colourIndex) {

    switch (colourIndex) {
    case 0:
        //red
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        break;

    case 1:
        //yellow
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        break;

    case 2:
        //green
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        break;

    case 3:
        //blue
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        break;

    case -1:
        //white - returns text to default white colour
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        break;
    };
}

//enum cardColour {
//    Red,
//    Yellow,
//    Green,
//    Blue,
//};


struct UnoCard {
    int number = 0; //stores card number
    int colourIndex = 0; //stores card colour
    int powerUpIndex = 0; //stores card power up

    ////overides = to allow for item assignment
    //UnoCard& operator = (UnoCard& rhs) {
    //    if (this != &rhs) { //makes sure the item isn't reassigned to itself

    //        //replaces the current data in memory
    //        number = rhs.number;
    //        colourIndex = rhs.colourIndex;
    //        powerUpIndex = rhs.powerUpIndex;
    //    }
    //    return *this;
    //}

};

//overides == to allow for UnoCard struct comparisson
bool operator== (const UnoCard& lhs, const UnoCard& rhs) {
    return (lhs.colourIndex == rhs.colourIndex
        && lhs.number == rhs.number
        && lhs.powerUpIndex == rhs.powerUpIndex);
}

bool foundInVector(std::vector<UnoCard>& dataToSearch, const UnoCard itemToFind) {

    std::vector<UnoCard>::iterator index;
    index = std::find(dataToSearch.begin(), dataToSearch.end(), itemToFind);

    if (index != dataToSearch.end()) { //if an index is found for an existing match
        return true;
    }
    else {
        return false;
    }


}


class participant { //base class for player and cpu

protected:
    std::vector<UnoCard> hand; //stores participant's hand
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

    //randomly generates a card
    void generateCard(int& cardColour, int& cardNumber) {

        cardColour = rand() % 4;
        cardNumber = rand() % 8;
    }


    //sets up a new hand of 8 cards
    void handSetup(participant& activeParticipant) {

        UnoCard newCard;

        for (int i = 0; i < 8; i++) {

            activeParticipant.generateCard(newCard.colourIndex, newCard.number);
            hand.push_back(newCard);
        }

        //return hand;
    }

    //discards choosen card from participant's hand
    UnoCard placeCard(int& cardIndex, UnoCard& discardCard) {

        UnoCard chosenCard; //card to discad

        chosenCard = hand[cardIndex];

        hand.erase(hand.begin() + cardIndex); //removes chosen card from participant's hand

        std::cout << "\nThe card ";
        printColour(chosenCard.colourIndex);
        std::cout << indexToColour(chosenCard.colourIndex);
        printColour(-1);
        std::cout << " " << chosenCard.number << " was discarded\n";

        return chosenCard;

    }

    void drawCard() {

        UnoCard drawnCard; //card that has been drawn
        generateCard(drawnCard.colourIndex, drawnCard.number);

        hand.push_back(drawnCard); //adds a new card to the participant's hand
        std::cout << "\nThe card ";
        printColour(drawnCard.colourIndex);
        std::cout << indexToColour(drawnCard.colourIndex);
        printColour(-1);
        std::cout << " " << drawnCard.number << " has been drawn.\n";

        //return drawnCard;

    }


    int updateHandSize() {

        return hand.size();
    }
};

class Player : public participant { //dedicated player class

private:
    std::string name; //player name

public:

   /* Player() {
        
        isPlayersTurn = false;
        setPlayerName();
    }*/

    std::string setPlayerName() { //sets player name (based on user input)

        bool nameIsInappropriate = false; //stores if name was found in banList
        std::string uncheckedName; //holds the player's name input

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

    //'draws' 8 random cards
    /*std::vector<UnoCard> handSetup(Player& player) {

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

        for (int i = 0; i < 8; i++) {

            player.generateCard(newCard.colourIndex, newCard.number);
            hand.push_back(newCard);
        }

        return hand;
    };*/

    //discards choosen card from participant's hand
    UnoCard placeCard(int& cardIndex, UnoCard& discardCard) {

        UnoCard chosenCard; //card to discad


        do {
            chosenCard = hand[cardIndex];

            if (chosenCard.colourIndex == discardCard.colourIndex || chosenCard.number == discardCard.number) {

                hand.erase(hand.begin() + cardIndex); //removes chosen card from participant's hand
                break;
            }

            printf("\nThe card you chose is not the same colour or type as the card at the top of the discard pile."
                "\nPlease choose another card:\n> ");

            std::cin >> cardIndex;
            cardIndex = menuInputValidation(cardIndex, hand.size());
            cardIndex -= 1;
        } while (chosenCard.colourIndex != discardCard.colourIndex || chosenCard.number != discardCard.number); //runs until player discards a valid card

        std::cout << "\nThe card ";
        printColour(chosenCard.colourIndex);
        std::cout << indexToColour(chosenCard.colourIndex);
        printColour(-1);
        std::cout << " " << chosenCard.number << " was discarded\n";

        return chosenCard;

    }


    //reveals all the cards currently in the players hand
    void showHand() {


        printf("\nYou currently have %i cards in your hand. They are the following:\n", hand.size());

        for (int i = 0; i < hand.size(); i++) {

            std::cout << "\n" << i + 1 << ". ";
            printColour(hand[i].colourIndex);
            std::cout << indexToColour(hand[i].colourIndex);
            printColour(-1);
            std::cout << " " << hand[i].number << ",";

            Sleep(200);

        }
    }

    //int chosenAction() {//gets the player's chosen action and validates it
    //    int action = 0;
    //    printf("\nWhat would you like to do?\n1.Place a Card\t2.Pick up a Card\n");
    //    std::cin >> action;
    //    action = menuInputValidation(action, 2);
    //    return action;
    //}
};

class CPU : public participant {//dedicated cpu class

public:

    //decides if CPU should draw or place a card
    int decideAction(UnoCard discardCard) {

        for (int i = 0; i < hand.size(); i++) { //cpu looks to see if there is a card it can draw

            //finds the first card that matches
            if (hand[i].colourIndex == discardCard.colourIndex || hand[i].number == discardCard.number) {

                return i;

            }
        }

        return -1; //returns invalid index if no suitable card was found

    }

    //std::vector<UnoCard> handSetup(CPU& cpu) { //'draws' 8 random cards
    //    /*cpu.generateCard(cpuCard1.colourIndex, cpuCard1.number);
    //    cpu.generateCard(cpuCard2.colourIndex, cpuCard2.number);
    //    cpu.generateCard(cpuCard3.colourIndex, cpuCard3.number);
    //    cpu.generateCard(cpuCard4.colourIndex, cpuCard4.number);
    //    cpu.generateCard(cpuCard5.colourIndex, cpuCard5.number);
    //    cpu.generateCard(cpuCard6.colourIndex, cpuCard6.number);
    //    cpu.generateCard(cpuCard7.colourIndex, cpuCard7.number);
    //    cpu.generateCard(cpuCard8.colourIndex, cpuCard8.number);

    //    hand.push_back(cpuCard1);
    //    hand.push_back(cpuCard2);
    //    hand.push_back(cpuCard3);
    //    hand.push_back(cpuCard4);
    //    hand.push_back(cpuCard5);
    //    hand.push_back(cpuCard6);
    //    hand.push_back(cpuCard7);
    //    hand.push_back(cpuCard8);*/

    //    /*for (int i = 0; i < 8; i++) {

    //        cpu.generateCard(newCard.colourIndex, newCard.number);
    //        hand.push_back(newCard);
    //    }

    //    return hand;*/
    //}
};