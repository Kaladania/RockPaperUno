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
    
    // game setup

    cpu.generateCard(startingCard.colourIndex, startingCard.number, startingCard.powerUpIndex, 0);
    discardCard = startingCard;

    
    //beginning game functionality code

    playerName = player.setPlayerName();
    std::cout << "Hello, " << playerName << "!\n";

    Sleep(500);

    player.handSetup(player);
    playerHandSize = player.updateHandSize();

    cpu.handSetup(cpu);
    cpuHandSize = cpu.updateHandSize();

    Sleep(600);    



    //game loop
    //runs until the player chooses to exit the game
    while (playerAction != 3) {

        printf("\n- - - - - ROUND %i - - - - -\n", totalRounds);

        Sleep(500);

        //prints out the discard card
        std::cout << "\n\nThe card currently at the top of the discrard pile is a ";
        colouredText(discardCard.colourIndex);
        std::cout << " " << discardCard.number << "\n";

        Sleep(800);
        
        player.showHand();

        currentPlayer = rockPaperScissors();

        Sleep(800);

        if (currentPlayer == "Player") { //player's turn

            //playerAction = player.chosenAction();

            printf("\n\nWhat would you like to do?\n1. Place a card   2. Pick up a card   3. Exit Game\n> ");
            std::cin >> playerAction;

            playerAction = menuInputValidation(playerAction, 3);

            switch (playerAction)
            {
            case placeCard: //place a card

                printf("\nEnter the index number of the card you wish to discard\n> ");

                std::cin >> playerCardToDiscard;
                playerCardToDiscard = menuInputValidation(playerCardToDiscard, playerHandSize);
                playerCardToDiscard -= 1; //translates choice to maintain code accuracy

                discardCard = player.placeCard(playerCardToDiscard, discardCard);

                if (discardCard.powerUpIndex > 0) { //runs a special event if a power-up card is played

                    
                    printf("\nFrom the CPU's hand: ");
                    switch (discardCard.powerUpIndex)
                    {
                    case 1: //reveals a card
                        player.revealCard(cpu);
                        break;

                    default:
                        break;
                    }

                }


                playerHandSize = player.updateHandSize();

                switch (playerHandSize) //checks if player is about to/has won
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

            case drawCard: //draw a card

                player.drawCard();
                playerHandSize = player.updateHandSize();
                break;

            case exitGame: //exit game

                printf("\nYou've choosen to end the game. Goodbye!\n");
                break;

            }
        }

        else { //cpu's turn

            printf("\n - - CPU'S TURN - - \n");

            Sleep(500);
            printf("\n.");
            Sleep(500);
            printf(" .");
            Sleep(500);
            printf(" .\n");
            Sleep(700);

            cpuCardToDiscard = cpu.decideAction(discardCard);

            switch (cpuCardToDiscard)
            {
            case -1:
                cpu.drawCard();
                cpuHandSize = cpu.updateHandSize();
                break;

            default:
                discardCard = cpu.placeCard(cpuCardToDiscard, discardCard);


                //runs a special event if a power-up card is played
                if (discardCard.powerUpIndex > 0) {

                    switch (discardCard.powerUpIndex)
                    {
                    case 1: //reveals a card

                        printf("\nFrom the Player's hand: ");
                        cpu.revealCard(player);
                        break;

                    default:
                        break;
                    }
                }
                

                cpuHandSize = cpu.updateHandSize();

                switch (cpuHandSize) //checks if CPU is about to/has won
                {
                case 1: //cpu has one card left
                    std::cout << "\nThe CPU has an UNO!\n";
                    break;

                case 0:
                    std::cout << "\nThe CPU has no cards left! IT WINS!!!\n";
                    playerAction = 3; //triggers exit clause
                    break;
                }
            }
        }

        printf("\n");
        Sleep(900);

        //updates tracker variables
        totalRounds++;
    }
}