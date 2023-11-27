#include "SetupFunctions.h"
#include "IntroFunctions.h"

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
    


    //beginning game functionality code

    playerData = gameIntro(player, playerData, playerSaveData);

    Sleep(500);



    // GAME SETUP //

    //checks if the player has save data to use
    switch (playerSaveData.noSaveDataExists) { 
        
    case true:
        continueOldGame = 2;
        break;

    case false:

        //asks if the player want's to use their save data
        printf("Would you like to continue with your existing game?"
               "WARNING: If you choose to start a new game, your old save data will be OVERWRITTEN"
               "\n\nContinue with existing game?\n1. Yes\n2. No\n> ");
        std::cin >> continueOldGame;

        continueOldGame = menuInputValidation(continueOldGame, 2);
    }
   
    
    //determines if setup is fresh or from a save file
    switch (continueOldGame) {

    case 1:

        //sets up player and cpu hand
        player.createHandFromSaveFile(playerSaveData.hand);
        playerData.handSize = playerSaveData.handCount;

        cpu.createHandFromSaveFile(playerSaveData.cpuHand);
        cpuHandSize = playerSaveData.cpuHandCount;

        totalRounds = playerSaveData.totalRounds;
        discardCard = playerSaveData.discardCard;
        break;

    case 2:

        player.handSetup(player);
        playerData.handSize = player.updateHandSize();

        

        cpu.handSetup(cpu);
        cpuHandSize = cpu.updateHandSize();

        cpu.generateCard(startingCard.colourIndex, startingCard.number, startingCard.powerUpIndex, 0);
        discardCard = startingCard;
        
        break;
    }

    

    //game loop
    //runs until the player chooses to exit the game
    // less than allows for intro to all stop game (option is #4)
    while (playerData.action < 3) {

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
            std::cin >> playerData.action;

            playerData.action = menuInputValidation(playerData.action, 3);

            switch (playerData.action)
            {
            case placeCard: //place a card

                printf("\nEnter the index number of the card you wish to discard\n> ");

                std::cin >> playerData.cardToDiscard;
                playerData.cardToDiscard = menuInputValidation(playerData.cardToDiscard, playerData.handSize);
                playerData.cardToDiscard -= 1; //translates choice to maintain code accuracy

                discardCard = player.placeCard(playerData.cardToDiscard, discardCard);

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


                playerData.handSize = player.updateHandSize();

                switch (playerData.handSize) //checks if player is about to/has won
                {
                case 1: //player has one card left
                    std::cout << "\n" << playerData.name << " has an UNO!\n";
                    break;

                case 0:
                    std::cout << "\n" << playerData.name << " has no cards left! THEY WIN!!!\n";
                    playerData.action = 3; //triggers exit clause
                    break;
                }


                break;

            case drawCard: //draw a card

                player.drawCard();
                playerData.handSize = player.updateHandSize();
                break;

            case exitGame: //exit game

                printf("\nYou've choosen to end the game. Goodbye!\n");
                break;

            }
        }

        else if (currentPlayer == "CPU") { //cpu's turn

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
                    playerData.action = 3; //triggers exit clause
                    break;
                }
            }
        }

        else {

            playerData.action = 3;

        }

        printf("\n");
        Sleep(900);

        //updates tracker variables
        totalRounds++;
    }

    printf("That's the end of the game. See ya next time!\n");
}