#include "SetupFunctions.h"

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
    std::vector<int>::iterator iterator; //allows for vector iteration

    UnoCard discardCard; //stores the current card to be compared to
    UnoCard startingCard;

    participant* participantCurrentlyPlaying; //points to the participant currently playing

    
    //player information setup

    std::string playerName = ""; //stores player name
    //std::vector<UnoCard> playerHand; //stores a copy of the player's hand
    int playerAction = 0;
    int cardToDiscard = 0;
    int playerHandSize = 0;


    Player player;
    CPU cpu;


    //game loop setup

    int totalRounds = 0;

    cpu.generateCard(startingCard.colourIndex, startingCard.number);
    discardCard = startingCard;

    
    //beginning game functionality code

    playerName = player.setPlayerName();
    std::cout << "Hello, " << playerName << "!\n";

    Sleep(500);

    player.handSetup(player);
    playerHandSize = player.updateHandSize();

    Sleep(600);    

    //game loop
    //runs until the player chooses to exit the game
    while (playerAction != 3) {

        std::cout << "\nRound: " << totalRounds;

        Sleep(500);

        //prints out the discard card
        std::cout << "\n\nThe card currently at the top of the discrard pile is a ";
        printColour(discardCard.colourIndex);
        std::cout << indexToColour(discardCard.colourIndex);
        printColour(-1); 
        std::cout << " " << discardCard.number << "\n";
        
        Sleep(500);

        player.showHand();

        //playerAction = player.chosenAction();

        printf("\n\nWhat would you like to do?\n1. Place a card   2. Pick up a card   3. Exit Game\n> ");
        std::cin >> playerAction;

        playerAction = menuInputValidation(playerAction, 3);

        //player's turn
        switch (playerAction)
        {
        case 1: //place a card

            printf("\nEnter the index number of the card you wish to discard\n> ");
            
            std::cin >> cardToDiscard;
            menuInputValidation(cardToDiscard, playerHandSize);
            cardToDiscard -= 1; //translates choice to maintain code accuracy
            
            discardCard = player.placeCard(cardToDiscard, discardCard, iterator);

            switch (playerHandSize) //checks if player is about to/has one
            {
            case 1: //player has one card left
                std::cout << "\n" << playerName << " has an UNO!\n";
                break;

            case 0:
                std::cout << "\n" << playerName << " has no cards left! THEY WIN!!!\n";
                playerAction = 3; //triggers exit clause
                break;
            }

            
            break;

        case 2: //draw a card

            player.drawCard();
            break;

        case 3: //exit game

            printf("\nYou've choosen to end the game. Goodbye!\n");
            break;

        }

        //cpu's turn

        //updates tracker variables
        totalRounds++;
        playerHandSize = player.updateHandSize();
    }
}