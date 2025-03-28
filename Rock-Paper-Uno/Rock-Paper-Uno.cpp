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

    srand(time(NULL)); //creates a unique seed for the game
    

    //beginning game functionality code

    playerData = gameIntro(player, playerData, playerSaveData);

    Sleep(500);

    //game setup
    //checks if player chose to play or exit the game
    if (playerData.action == 1) { 

        

        //checks if the player has save data to use
        switch (playerSaveData.noSaveDataExists) {

        case true:
            continueOldGame = 2;
            break;

        case false:

            //asks if the player want's to use their save data
            printf("\nWould you like to continue with your existing game?\n1. Yes   2. No\n> ");
            std::cin >> continueOldGame;

            continueOldGame = menuInputValidation(continueOldGame, 2);

            break;
        }


        //determines if setup is fresh or from a save file
        switch (continueOldGame) {

        case 1: //continue from save

            //imports player hand
            player.createHandFromSaveFile(playerSaveData.hand);
            playerData.handSize = playerSaveData.handCount;

            //imports CPU hands
            cpu.createHandFromSaveFile(playerSaveData.cpuHand);
            cpuHandSize = playerSaveData.cpuHandCount;
            
            //imports round count and discard card
            totalRounds = playerSaveData.totalRounds;
            discardCard = playerSaveData.discardCard;

            break;

        case 2: //start new game

            //creates a new hand of 8 random cards for the player
            player.handSetup(player);
            playerData.handSize = player.updateHandSize();

            //creates a new hand of 8 random cards for the CPU
            cpu.handSetup(cpu);
            cpuHandSize = cpu.updateHandSize();

            //generates a new card to assign as the 'discard card'
            cpu.generateCard(startingCard.colourIndex, startingCard.number, startingCard.powerUpIndex);
            discardCard = startingCard;

            break;
        }

        gameStarted = true;
    }
    

    //game loop
    //runs until the player chooses to exit the game
    //less than allows for intro to all stop game (option is #4)
    while (playerData.action < 3) {

        printf("\n- - - - - ROUND %i - - - - -\n", totalRounds);

        Sleep(500);

        //prints out the discard card
        std::cout << "\n\nThe card currently at the top of the discard pile is a ";
        colouredText(discardCard.colourIndex);
        std::cout << " " << discardCard.number << "\n";

        Sleep(800);
        
        player.showHand();

        currentPlayer = rockPaperScissors(playerData);

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
                    gameFinished = true;
                    playerData.action = 3; //triggers exit clause
                    break;
                }


                break;

            case drawCard: //draw a card

                player.drawCard();
                playerData.handSize = player.updateHandSize();

                playerData.cardsDrawn++;

                
                break;

            case exitGame: //exit game

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
                    gameFinished = true;
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
        // 
        //tracks max hand size during game
        if (playerData.handSize > playerData.maxHandSize) {

            playerData.maxHandSize = playerData.handSize;

        }
        totalRounds++;
    }

    printf("\n\n- - - -  GAME ENDED - - - ");

    //only create save data if the player had started playing the game
    //if the game has started but didn't finish
    if (gameStarted && !gameFinished) {

        printf("\nDo you want to save your game so that you can continue playing later?"
            "\n\nWARNING: Doing so means that your old save data will be OVERWRITTEN!");

        Sleep(900);

        printf("\n\nSave Game?\n1. Yes   2. No\n> ");
        std::cin >> playerData.action;

        playerData.action = menuInputValidation(playerData.action, 2);

        if (playerData.action == 1) {

            dataToWrite = createSaveData(playerSaveData, playerData, player.storeToSaveFile(), cpu.storeToSaveFile(), totalRounds - 1, discardCard);

            updateSaveData(playerData.name, dataToWrite);
        }

    }
    
    //only updates records if someone has won the game
    if (gameFinished) {

        updateRecords(playerRecordData, playerData, playerSaveData, totalRounds-1, currentPlayer, continueOldGame);

        dataToWrite = createRecordData(playerRecordData);

        saveRecordData(playerData.name, dataToWrite);
    }

    printf("\n\nSee ya next time!\n");
}