#pragma once

#include <iostream>
#include <string>
#define FOUNDIN(dataToSearch, itemToFind) (dataToSearch.find(itemToFind) != std::string::npos) //shorthand to make writing code to find existing items easier
#define LENGTHOF(arrayToCheck) sizeof(arrayToCheck) / sizeof(arrayToCheck[0]) //shorthand to quickly determine the length of an array

int menuInputValidation(int optionMax) //validates a user's input
{
    int number = 0;
    int optionChosen = 0;

    std::cout << "Please enter the option you wish to choose: ";
    std::cin >> optionChosen;

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

/*std::string captialize(std::string stringToTitle) {

    stringToTitle = toupper(stringToTitle[0]);
}*/