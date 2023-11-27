//SETUP FOR THE GAME INTRO SCREEN

#pragma once


//void gameIntro(const std::string name, int action);
//
//void printTitle();

enum introChoice {
	playGame = 1,
	viewRules = 2,
	viewSaves = 3,

};

void printTitle() {
	printf("\n\n    ____  ____  ________ __      ____                           __  ___   ______  __"
		"\n   \/ __ \\\/ __ \\\/ ____\/ \/\/_\/     \/ __ \\____ _____  ___  _____   \/ \/ \/ \/ | \/ \/ __ \/ \/"
		"\n  \/ \/_\/ \/ \/ \/ \/ \/   \/ ,<       \/ \/_\/ \/ __ `\/ __ \\\/ _ \\\/ ___\/  \/ \/ \/ \/  |\/ \/ \/ \/ \/ \/"
		"\n \/ _, _\/ \/_\/ \/ \/___\/ \/| |_    \/ ____\/ \/_\/ \/ \/_\/ \/  __\/ \/     \/ \/_\/ \/ \/|  \/ \/_\/ \/_\/"
		"\n\/_\/ |_|\\____\/\\____\/_\/ |_( )  \/_\/    \__,_\/ .___\/\\___\/_( )    \\____\/_\/ |_\/\\____(_)"
		"\n                        |\/              \/_\/           |\/\n");
}

//converts the saveData information into a UnoCard type card
UnoCard dataToCard(std::string cardData) {

	int stringData[3] = {0, 0, 0}; //stores the fetched indexes
	int iterator = 0; //array iterator
	UnoCard newCard; //empty card instance

	std::istringstream ss(cardData); //creates a string stream from data
	std::string index = ""; //stores individual characters fetched
	
	//converts the characters to intergers and stores them in an array
	while (std::getline(ss, index, '-')) {
		stringData[iterator] = stoi(index);
		iterator++;
	}

	//creates a card from the save data
	newCard.colourIndex = stringData[0];
	newCard.number = stringData[1];
	newCard.powerUpIndex = stringData[2];

	return newCard;
}

void showRules();

void getSavaData(PlayerSaveData& saveData) {

	int optionChosen = 0;

	//creates a path to the player's save data [/SaveData/<playerName>.txt]
	std::string fileName = "SaveData\\";
	fileName.append(saveData.name);
	fileName.append(".txt");


	std::cout << fileName << "\n";
	std::ifstream saveFile = std::ifstream(fileName);

	std::string cardData = "";

	if (!saveFile.is_open() || !saveFile.good()) { //checks if the data is saved AND can be accessed

		printf("Your save data could not be found/accessed.\nA new save file has been created for you.");
		
		//creates a new save file 
		std::ofstream newSaveFile = std::ofstream(fileName);
		newSaveFile << saveData.name;
		newSaveFile.close();
	}
	else {

		saveFile >> saveData.name;
		saveFile >> saveData.totalRounds;
		saveFile >> saveData.handCount;

		for (int i = 0; i < saveData.handCount; i++) {

			saveFile >> cardData;

			saveData.hand.push_back(dataToCard(cardData)); //adds newly created card to player's hand
		}

		saveFile >> saveData.cpuHandCount;
		for (int i = 0; i < saveData.cpuHandCount; i++) {

			saveFile >> cardData;

			saveData.cpuHand.push_back(dataToCard(cardData)); //adds newly created card to player's hand
		}

		saveFile >> cardData;
		saveData.discardCard = dataToCard(cardData); //assigns newly created card as discard card

		//collects player's stats
		saveFile >> saveData.largestHand;
		saveFile >> saveData.totalCardsDrawn;
		saveFile >> saveData.rpsWon;
		saveFile >> saveData.rpsLost;
		saveFile >> saveData.rpsDrawn;
	}

	saveFile.close();

}

PlayerData gameIntro(Player& player, PlayerData& playerData, PlayerSaveData& playerSaveData) {

	//updates the data and save data trackers with the player's name
	playerData.name = player.setPlayerName();
	playerSaveData.name = playerData.name;

	std::cout << "\nHello " << playerData.name << "!\n";

	Sleep(900);

	std::cout << "\nWelcome to:";

	Sleep(900);

	printTitle(); //displays game title

	Sleep(900);

	printf("\n\nWhat would you like to do?\n1. Play Game   2. View Rules   3. View Save Data   4. Exit Game\n> ");
	std::cin >> playerData.action;

	playerData.action = menuInputValidation(playerData.action, 4);

	switch (playerData.action)
	{

	case 3:
		getSavaData(playerSaveData);
	default:
		return playerData;
	}


}