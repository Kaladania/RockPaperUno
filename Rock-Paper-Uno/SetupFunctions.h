#pragma once
#include "CommonLibraries.h"
#include "UtilityFunctions.h"


#define FOUNDIN(dataToSearch, itemToFind) (dataToSearch.find(itemToFind) != std::string::npos) //shorthand to make writing code to find existing items easier
//#define FOUNDINCOLLECTION(dataToSearch, itemToFind, collectionLength) ((std::find(dataToSearch, dataToSearch+collectionLength, itemToFind)) != std::end(validCommands)) //exclusive FOUNDIN definition for pointers
#define LENGTHOF(arrayToCheck) sizeof(arrayToCheck) / sizeof(arrayToCheck[0]) //shorthand to quickly determine the length of an array

// wanted to enumarate card to increase readability
// decided against it enums are not as flexible as ints (would require a lot of static casting)
//enum cardColour {
//    Red,
//    Yellow,
//    Green,
//    Blue,
//};


// COLLECTION/CLASS SETUP //


struct UnoCard { //Uno Card Structure
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

struct PlayerData { //groups the various main function variables
    
    std::string name = ""; //stores player name
    int action = 0; //stores player's chosen action
    int handSize = 0; //stores the size of the player's hand
    int cardToDiscard = 0; //stores player's chosen card to discard
    int cardsDrawn = 0; //stores the amount of cards drawn during the game

    int rpsWon = 0; //stores how many RPS games won
    int rpsLost = 0; //stores how many RPS games lost
    int rpsDrawn = 0; //stores how many RPS games drawn
};

struct PlayerSaveData { //stores data to recreate the current game at a later date

    bool noSaveDataExists = true; //state if the player currently has an active save

    //stores the current player information to recreate the game
    std::string name = ""; //stores player name
    int handCount = 0; //stores the size of the player's hand
    std::vector<UnoCard> hand = {}; //stores player's hand

    //stores the cpu hand
    int cpuHandCount = 0; //stores the size of the cpu's hand
    std::vector<UnoCard> cpuHand = {}; //stores cpu's hand

    //stores the game information
    UnoCard discardCard; //stores the current discard card
    int totalRounds = 0;

    //stores info needed for accurate record keeping
    int largestHand = 0; //stores the player's largest hand
    int totalCardsDrawn = 0; //stores the total amount of cards drawn
    
    int rpsWon = 0; //stores how many RPS games won
    int rpsLost = 0; //stores how many RPS games lost
    int rpsDrawn = 0; //stores how many RPS games drawn
};

struct PlayerRecordData { //stores data on the player's history in RPU

    //stores the current player information to recreate the game
    std::string name = ""; //stores player name

    int maxRounds = 0;

    //stores info needed for accurate record keeping
    int largestHand = 0; //stores the player's largest hand
    int maxCardsDrawn = 0; //stores the total amount of cards drawn

    int totalGamesWon = 0; //stores how many Games won
    int totalGamesLost = 0; //stores how many Games lost

    int rpsWon = 0; //stores how many RPS games won
    int rpsLost = 0; //stores how many RPS games lost
    int rpsDrawn = 0; //stores how many RPS games drawn
};

struct CPUData { //groups the various main function variables

};

//overides == to allow for UnoCard struct comparisson
bool operator== (const UnoCard& lhs, const UnoCard& rhs) {
    return (lhs.colourIndex == rhs.colourIndex
        && lhs.number == rhs.number
        && lhs.powerUpIndex == rhs.powerUpIndex);
}

class Participant { //base class for player and cpu

protected:
    std::vector<UnoCard> hand; //stores Participant's hand
    bool isPlayersTurn = false; //stores if its the current instance's turn

public:

    //original attempt to create a hand of 8 unique cards using an array
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
    void generateCard(int& cardColour, int& cardNumber, int& cardPowerUP, const int filter) {

        int specialCardProbability = 0; //stores probability of drawing a special card
        

        switch (filter) //determines if game generates any type of card, a normal card or a power up
        {
        case 0: //generate any card

            specialCardProbability = rand() % 101;

            if (specialCardProbability > 95) { //5% of drawing a special card

                cardPowerUP = 1;
                
            }
            else { //95% chance of drawing a normal card

                cardColour = rand() % 4;
                cardNumber = rand() % 8;
            }

        
        //case 1: //generate a normal card
        //    cardColour = rand() % 4;
        //    cardNumber = rand() % 8;

        //    break;

        //case 2: //generate a special card
        //    cardColour = 1;
        //    cardNumber = rand() % 8;

        //    break;

        default:
            break;
        }
    }

    //sets up a new hand of 8 cards
    void handSetup(Participant& activeParticipant) {

        UnoCard newCard;

        for (int i = 0; i < 8; i++) {

            activeParticipant.generateCard(newCard.colourIndex, newCard.number, newCard.powerUpIndex, 0);
            hand.push_back(newCard);
        }

        //return hand;
    }

    //imports hand from save data
    void createHandFromSaveFile(const std::vector<UnoCard>& saveDataHand) {

        hand = saveDataHand;
    }

    //imports hand from save data
    std::vector<UnoCard> storeToSaveFile() {

        return hand;
    }

    //reveals all the cards currently in the players hand
    void showHand() {


        printf("\nYou currently have %i cards in your hand. They are the following:\n", hand.size());

        for (int i = 0; i < hand.size(); i++) {

            std::cout << "\n" << i + 1 << ". ";
            colouredText(hand[i].colourIndex);
            std::cout << " " << hand[i].number;
            printPowerUP(hand[i].powerUpIndex);

            Sleep(200);

        }
    }

    //discards choosen card from Participant's hand
    UnoCard placeCard(int& cardIndex, UnoCard& discardCard) {

        UnoCard chosenCard; //card to discad

        chosenCard = hand[cardIndex];

        hand.erase(hand.begin() + cardIndex); //removes chosen card from Participant's hand

        std::cout << "\nThe";

        if (chosenCard.powerUpIndex > 0) { //adds a card title if the card is a powerup card
            std::cout << " Power Up ";
        }

        std::cout << " card ";
        colouredText(chosenCard.colourIndex);
        std::cout << " " << chosenCard.number << " was discarded\n";

        return chosenCard;

    }

    void drawCard() {

        UnoCard drawnCard; //card that has been drawn
        generateCard(drawnCard.colourIndex, drawnCard.number, drawnCard.powerUpIndex, 0);

        hand.push_back(drawnCard); //adds a new card to the Participant's hand
        std::cout << "\nThe card ";
        colouredText(drawnCard.colourIndex);
        std::cout << " " << drawnCard.number << " has been drawn.\n";

        //return drawnCard;

    }

    int updateHandSize() {

        return hand.size();
    }

    //reveals a random card from the opponets deck
    void revealCard(const Participant& opponent) {

        int revealIndex = 0;
        UnoCard cardToReveal;

        revealIndex = rand() % opponent.hand.size(); //choses a random card from opponents hand

        cardToReveal = opponent.hand[revealIndex];

        std::cout << "\nThe";

        if (cardToReveal.powerUpIndex > 0) { //adds a card title if the card is a powerup card
            std::cout << " Power Up";
        }

        std::cout << " card ";
        colouredText(cardToReveal.colourIndex);
        std::cout << " " << cardToReveal.number << " was revealed\n";

    }

    void wildCard() {}

    void draw2Cards() {}

    void draw4Cards() {}
};

class Player : public Participant { //dedicated player class

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

        std::cout << "Enter your name: ";
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

    // original hand setup function that manual creates 8 cards
    // felt code was cumbersome so looked to streamline it
    /*std::vector<UnoCard> handSetup(Player& player) {   //'draws' 8 random cards

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


    //discards choosen card from Participant's hand
    UnoCard placeCard(int& cardIndex, UnoCard& discardCard) {

        UnoCard chosenCard; //card to discad


        do {
            chosenCard = hand[cardIndex];

            //runs if its a matching card AND not a special card
            if (chosenCard.powerUpIndex > 0 || chosenCard.colourIndex == discardCard.colourIndex || chosenCard.number == discardCard.number) {

                hand.erase(hand.begin() + cardIndex); //removes chosen card from Participant's hand
                break;
            }

            printf("\nThe card you chose is not the same colour or type as the card at the top of the discard pile."
                "\nPlease choose another card:\n> ");

            std::cin >> cardIndex;
            cardIndex = menuInputValidation(cardIndex, hand.size());
            cardIndex -= 1;
        } while (chosenCard.colourIndex != discardCard.colourIndex || chosenCard.number != discardCard.number); //runs until player discards a valid card

        std::cout << "\nThe";
        
        if (chosenCard.powerUpIndex > 0) { //adds a card title if the card is a powerup card
            std::cout << " Power Up ";
        }

        std::cout << " card ";
        colouredText(chosenCard.colourIndex);
        std::cout << " " << chosenCard.number << " was discarded\n";

        return chosenCard;

    }

    //int chosenAction() {//gets the player's chosen action and validates it
    //    int action = 0;
    //    printf("\nWhat would you like to do?\n1.Place a Card\t2.Pick up a Card\n");
    //    std::cin >> action;
    //    action = menuInputValidation(action, 2);
    //    return action;
    //}
};

class CPU : public Participant {//dedicated cpu class

public:

    //decides if CPU should draw or place a card
    int decideAction(UnoCard discardCard) {

        

        for (int i = 0; i < hand.size(); i++) { //cpu looks to see if there is a card it can draw

            //finds the first card that matches OR the first special card
            if ((hand[i].powerUpIndex > 0) || (hand[i].colourIndex == discardCard.colourIndex || hand[i].number == discardCard.number)) {

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


// finds if element in vector (card in Participant hand)
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


// runs a Rock, Paper, Scissors Minigame
std::string rockPaperScissors(PlayerData& playerData) {

    srand(time(NULL));

    int playerSign = 0; //stores player's choosen sign
    int cpuSign = 0; //stores cpu's choosen sign

    printf("\n\n - - - BATTLE TO CLAIM YOUR TURN! - - - -");
    
    Sleep(500);

    while (true) {


        printf("\n\nWhat would you like to do?\n1. Rock   2. Paper   3. Scissor   4. Exit Game\n> ");
        std::cin >> playerSign;
        playerSign = menuInputValidation(playerSign, 4);
        
        playerSign -= 1; //validates player input

        cpuSign = rand() % 2; //cpu picks a random sign (index)

        Sleep(200);

        //determines game result
        if (playerSign == 0) { //player chose rock

            switch (cpuSign) {

            case 0: //cpu also drew rock
                printf("\nThe CPU drew Rock!\n");
                break;

            case 1: //cpu drew paper
                printf("\nThe CPU drew Paper!\n");
                printf("\nThe CPU Wins!\n");

                playerData.rpsLost++;

                return "CPU";

            case 2: //cpu drew scissors
                printf("\nThe CPU drew Scissors!\n");
                printf("\nThe Player Wins!\n");

                playerData.rpsWon++;

                return "Player";

            }
        }

        else if (playerSign == 1) { //player chose paper

            switch (cpuSign) {

            case 0: //cpu drew rock
                printf("\nThe CPU drew Rock!\n");
                printf("\nThe Player Wins!\n");

                playerData.rpsWon++;

                return "Player";

            case 1: //cpu also drew paper
                printf("\nThe CPU drew Paper!\n");
                break;

            case 2: //cpu drew scissors
                printf("\nThe CPU drew Scissors!\n");
                printf("\nThe CPU Wins!\n");

                playerData.rpsLost++;

                return "CPU";

            }
        }

        else if (playerSign == 2) { //player chose scissors

            switch (cpuSign) {

            case 0: //cpu drew rock
                printf("\nThe CPU drew Rock!\n");
                printf("\nThe CPU Wins!\n");

                playerData.rpsLost++;

                return "CPU";

            case 1: //cpu drew paper
                printf("\nThe CPU drew Paper!\n");
                printf("\nThe Player Wins!\n");

                playerData.rpsWon++;

                return "Player";

            case 2: //cpu also drew scissors
                printf("\nThe CPU drew Scissors!\n");
                break;

            }
        }

        else { //player chooses to exit
            return "exit";
        }

        printf("\nIt's a draw. GO AGAIN!\n");
        playerData.rpsDrawn++;

        Sleep(500);

    }
}


//updates player records
void updateRecord(PlayerRecordData& recordData, const PlayerData& playerData, const PlayerSaveData& saveData, const int totalRounds, const std::string winner, const int continueOldGame){


    //updates longest game stat
    if (totalRounds > recordData.maxRounds) { 

        recordData.maxRounds = totalRounds;
    }

    //updates largest hand stat
    if (playerData.handSize > recordData.largestHand) { 

        recordData.largestHand = playerData.handSize;
    }
    
    //updates no. of cards drawn stat
    if (playerData.cardsDrawn > recordData.maxCardsDrawn) { 

        recordData.maxCardsDrawn = playerData.cardsDrawn;
    }

    //updates win/lose stat
    if (winner == "Player") {

        recordData.totalGamesWon++;
    }
    else {

        recordData.totalGamesLost++;
    }

    //updates RPS win/lose/draw stat
    //checks if game was continued from save to get the total stat
    if (continueOldGame == 1) { 

        recordData.rpsWon = playerData.rpsWon + saveData.rpsWon;
        recordData.rpsLost = playerData.rpsLost + saveData.rpsLost;
        recordData.rpsDrawn = playerData.rpsDrawn + saveData.rpsDrawn;

    }
    else {

        recordData.rpsWon = playerData.rpsWon;
        recordData.rpsLost = playerData.rpsLost;
        recordData.rpsDrawn = playerData.rpsDrawn;

    }

}


//converts the passed UnoCard into a string format for save file
std::string formatCardData(const UnoCard cardToSave) {

    std::string formattedCard = "";

    formattedCard.append(std::to_string(cardToSave.colourIndex) + "-");
    formattedCard.append(std::to_string(cardToSave.number) + "-");
    formattedCard.append(std::to_string(cardToSave.powerUpIndex));
   
    return formattedCard;

}

std::string createSaveData(PlayerSaveData& saveData, const PlayerData& playerData, const std::vector<UnoCard>& playerHand, const std::vector<UnoCard>& cpuHand, const int currentRound, const UnoCard discardCard) {

    std::string formattedText = "";

    //saves player name, current round and hand size
    formattedText.append(playerData.name + " " + std::to_string(currentRound) + " " + std::to_string(playerHand.size()) + " ");

    //saves all the cards in the player's hand
    for (UnoCard card : playerHand) {

        formattedText.append(formatCardData(card) + " ");

    }


    //saves cpu's hand size
    formattedText.append(std::to_string(cpuHand.size()) + " ");

    //saves all the cards in the player's hand
    for (UnoCard card : cpuHand) {

        formattedText.append(formatCardData(card) + " ");

    }

    //saves the current discard card
    formattedText.append(formatCardData(discardCard) + " ");

    //updates the "largest hand size" stat
    if (playerHand.size() > saveData.largestHand) {
        formattedText.append(std::to_string(playerHand.size()) + " ");
    }
    else {
        formattedText.append(std::to_string(saveData.largestHand) + " ");
    }

    //updates the "most amount of cards drawn" stat
    if (playerData.cardsDrawn > saveData.totalCardsDrawn) {
        formattedText.append(std::to_string(playerData.cardsDrawn) + " ");
    }
    else {
        formattedText.append(std::to_string(saveData.totalCardsDrawn) + " ");
    }

    //updates the Rock, Paper, Scissors minigame stats
    formattedText.append(std::to_string(saveData.rpsWon + playerData.rpsWon) + " ");
    formattedText.append(std::to_string(saveData.rpsLost + playerData.rpsLost) + " ");
    formattedText.append(std::to_string(saveData.rpsDrawn + playerData.rpsDrawn) + " ");


    return formattedText;
    
}

void updateSaveData(const std::string playerName, const std::string saveData) {

    //creates file path
	std::string fileName = "SaveData\\";
	fileName.append(playerName);
	fileName.append(".txt");

    //opens the existing save file with the intention to overwrite any data within it
    std::ofstream saveFile = std::ofstream(fileName, std::ios::trunc);

    saveFile << saveData; //overwrites save data

    saveFile.close();

    printf("\n\nYour game data has been saved");

}



enum PlayerAction { //enumarated player actions

    placeCard = 1,
    drawCard = 2,
    exitGame = 3
};

////enum Colour { //enumerated colours
//
//    red,
//    yellow,
//    green,
//    blue,
//    grey,
//    white = -1
//};


// VARIABLE SETUP //

std::vector<int>::iterator iterator; //allows for vector iteration

UnoCard discardCard; //stores the current card to be compared to
UnoCard startingCard;

bool gameFinished = false; //checks if someone has won


int continueOldGame = 0; //states if the player wants to continue from save data
std::string textSaveData = ""; //stores the formatted saveData


//cpu information setup
int cpuCardToDiscard = 0; //stores cpu's chosen card to discard
int cpuHandSize = 0; //stores the size of the cpu's hand


Player player;
CPU cpu;

PlayerData playerData;
PlayerSaveData playerSaveData;
PlayerRecordData playerRecordData;

//Participant* currentParticipant = nullptr;

//game loop setup

int totalRounds = 1;
std::string currentPlayer = "";
bool gameStarted = false;
bool gameEnded = false;