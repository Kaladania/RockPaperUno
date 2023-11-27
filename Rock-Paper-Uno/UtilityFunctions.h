//SETUP FOR UTILITY FUNCTIONS

#pragma once

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

    std::string colourName = ""; //stores the translated colour name

    switch (index) {

    case 0:
        return "Red";
    case 1:
        return "Yellow";
    case 2:
        return "Green";
    case 3:
        return "Blue";
    case 4:
        return "Power UP Card: Reveal Opponent's Card";
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

    case 4:
        //grey - powercard
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        break;

    default:
        //white - returns text to default white colour
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        break;
    };
}

//prints out a card in colour
void colouredText(const int colour) {

    
    printColour(colour);
    std::cout << indexToColour(colour);
    printColour(-1);
    

}

//prints the card's power up ability
void printPowerUP(const int powerUPIndex) {

    switch (powerUPIndex) // runs only if there's an ability
    {
    case 1:
        printf(" : Power up - Reveal ONE of the Opponent's Cards");
        break;

    default: //nothing prints if no ability
        break;
    }

}