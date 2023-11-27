//SETUP FOR THE GAME INTRO SCREEN

#pragma once

enum introChoice {
	playGame = 1,
	viewRules = 2,
	viewSaves = 3,

};

//prints out game title ["Rock, Paper, Uno"]
void printTitle() {
	printf("\n\n    ____  ____  ________ __      ____                           __  ___   ______  __"
		"\n   \/ __ \\\/ __ \\\/ ____\/ \/\/_\/     \/ __ \\____ _____  ___  _____   \/ \/ \/ \/ | \/ \/ __ \/ \/"
		"\n  \/ \/_\/ \/ \/ \/ \/ \/   \/ ,<       \/ \/_\/ \/ __ `\/ __ \\\/ _ \\\/ ___\/  \/ \/ \/ \/  |\/ \/ \/ \/ \/ \/"
		"\n \/ _, _\/ \/_\/ \/ \/___\/ \/| |_    \/ ____\/ \/_\/ \/ \/_\/ \/  __\/ \/     \/ \/_\/ \/ \/|  \/ \/_\/ \/_\/"
		"\n\/_\/ |_|\\____\/\\____\/_\/ |_( )  \/_\/    \__,_\/ .___\/\\___\/_( )    \\____\/_\/ |_\/\\____(_)"
		"\n                        |\/              \/_\/           |\/\n");
}

//converts the saveData information into a UnoCard type card
UnoCard dataToCard(const std::string cardData) {

	std::array<int,3> stringData= {0, 0, 0}; //stores the fetched indexes
	int iterator = 0; //array iterator
	UnoCard newCard; //empty card instance

	std::istringstream ss(cardData); //creates a string stream from data
	std::string index = ""; //stores individual characters fetched
	
	//converts the characters to intergers and stores them in an array
	//
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

//displays the game rules
void showRules() {

	printf("\n- - - - - - - RULES - - - - - - -"
		"\n\nRock, Paper, Uno is just like your classic Uno game!"
		"\n\nAt the beggining of your turn, you have the choice to either place or draw a card: "
		"\n- You can only place a card down if it matches either the COLOUR or NUMBER of the card currently at the top of the discard pile"
		"\n- If you don't have a card you can discard, then you MUST draw a card from the discard pile"
		"\n- (You can also choose to draw a card at any time if you want to be strategic)"
		"\n\nSometimes, cards can have special properties:"
		"\n- Reveal a Card: A card from the opponent's hand is revealed"
		"\n- Wild Card: Choose the colour of the card the player needs to place in the next round"
		"\n- Draw 2 Cards: Force the opponent to draw 2 cards from the discard pile"
		"\n- Draw 4 Cards: Force the opponent to draw 4 cards from the discard pile"
		"\n\nWhen either player is down to their last card, an UNO is declared as a warning that they are about to win"
		"\n\nBUT! There's a twist..."
		"\n\nAt the start of each round, both you and the CPU must battle it out in a classic game of Rock, Paper, Scissors to claim your turn"
		"\nBe careful. With the wrong kind of luck, you could potentially go the entire game without a turn..."
		"\n\nBe smart. Be strategic. And get ready to Rock, Paper, UNO!");

	printf("\n\n\n\n - - - - - - - CONTROLS - - - - - - -"
		   "\n\nJust like you've done to navigate the main menu!"
		   "\n\nEnter the number of the action you'd like to choose."
		   "\n\n\At any time, you're free to exit the game with the option to save you data so that you can return at a later date"
		   "\n\n - - - - - - - - - - - - - - - - - - \n\n");
	
	Sleep(1600);
}

void deleteSaveData(std::string playerName) {

	try {
		if (std::filesystem::remove(playerName))
			std::cout << "file " << playerName << " deleted.\n";
	}
	catch (const std::filesystem::filesystem_error& err) {
		std::cout << "filesystem error: " << err.what() << '\n';
	}
}


//imports player save data
bool getSaveData(PlayerSaveData& saveData) {

	int optionChosen = 0;

	//creates a path to the player's save data [/SaveData/<playerName>.txt]
	std::string fileName = "SaveData\\";
	fileName.append(saveData.name);
	fileName.append(".txt");

	std::ifstream saveFile = std::ifstream(fileName); //opens save file

	std::string cardData = ""; //stores the card data stored in save file

	if (!saveFile.is_open() || !saveFile.good()) { //checks if the data is saved AND can be accessed

		printf("\n\nYour save data could not be found/accessed.\nA new save file has been created for you.");
		
		//creates a new save file 
		std::ofstream newSaveFile = std::ofstream(fileName);
		//newSaveFile << saveData.name;
		newSaveFile.close();

		return false;

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

	return true;

}

//displays player save data
void showSaveData(const PlayerSaveData& saveData) {

	Sleep(500);

	std::cout << "\nPlayer name: " << saveData.name;

	Sleep(500);

	printf("\n\nCurrent Round: ROUND %i\n\nCurrent hand:\n", saveData.totalRounds);

	Sleep(500);

	for (int i = 0; i < saveData.hand.size(); i++) {

			std::cout << "\n" << i + 1 << ". ";
			colouredText(saveData.hand[i].colourIndex);
			std::cout << " " << saveData.hand[i].number;
			printPowerUP(saveData.hand[i].powerUpIndex);

			Sleep(200);
	}

	Sleep(500);
}

bool emptySaveFile(const std::string playerName){

	//creates file path
	std::string fileName = "SaveData\\";
	fileName.append(playerName);
	fileName.append(".txt");

	std::ifstream saveFile = std::ifstream(fileName);

	//checks if the file is empty
	if (saveFile.peek() == -1) {
		return true;
	}
	
	return false;
}

//imports player save data
void getPlayerRecord(PlayerRecordData& recordData) {

	int optionChosen = 0;

	//creates a path to the player's save data [/SaveData/<playerName>.txt]
	std::string fileName = "RecordData\\";
	fileName.append(recordData.name);
	fileName.append(".txt");

	std::ifstream recordFile = std::ifstream(fileName); //opens save file

	std::string cardData = ""; //stores the card data stored in save file

	if (!recordFile.is_open() || !recordFile.good()) { //checks if the data is saved AND can be accessed

		printf("\n\nYour records could not be found/accessed.\nA new record file has been created for you.");

		//creates a new record file 
		std::ofstream newRecordFile = std::ofstream(fileName);
		newRecordFile << recordData.name;
		newRecordFile.close();
	}
	else {

		//collects player's stats
		recordFile >> recordData.name;
		recordFile >> recordData.maxRounds;
		recordFile >> recordData.largestHand;
		recordFile >> recordData.maxCardsDrawn;
		recordFile >> recordData.totalGamesWon;
		recordFile >> recordData.totalGamesLost;
		recordFile >> recordData.rpsWon;
		recordFile >> recordData.rpsLost;
		recordFile >> recordData.rpsDrawn;
	}

	recordFile.close();

}

//displays player save data
void showPlayerRecord(const PlayerRecordData& recordData) {

	Sleep(500);

	std::cout << "\nPlayer name: " << recordData.name;
	Sleep(200);
	std::cout << "\nLongest Game: " << recordData.maxRounds << " Rounds";
	Sleep(200);
	std::cout << "\nLargest hand: " << recordData.largestHand << " cards";
	Sleep(200);
	std::cout << "\nMost amount of cards drawn: " << recordData.maxCardsDrawn;
	Sleep(200);
	std::cout << "\nTotal Games Won: " << recordData.totalGamesWon;
	Sleep(200);
	std::cout << "\nTotal Games Lost: " << recordData.totalGamesLost;
	Sleep(200);
	std::cout << "\nTotal Rock, Paper, Scissors Games Won: " << recordData.rpsWon;
	Sleep(200);
	std::cout << "\nTotal Rock, Paper, Scissors Games Lost: " << recordData.rpsLost;
	Sleep(200);
	std::cout << "\nTotal Rock, Paper, Scissors Games Drawn: " << recordData.rpsDrawn;
	Sleep(500);
}


//shows the game main menu
PlayerData gameIntro(Player& player, PlayerData& playerData, PlayerSaveData& playerSaveData) {

	//updates the data and save data trackers with the player's name
	playerData.name = player.setPlayerName();
	playerSaveData.name = playerData.name;
	playerRecordData.name = playerData.name;

	std::cout << "\nHello " << playerData.name << "!\n";

	Sleep(900);

	std::cout << "\nWelcome to:";

	Sleep(900);

	printTitle(); //displays game title

	playerSaveData.noSaveDataExists = emptySaveFile(playerData.name);
	
	getSaveData(playerSaveData);

	getPlayerRecord(playerRecordData);

	Sleep(900);


	do {
		printf("\n\nWhat would you like to do?\n1. Play Game   2. View Rules   3. View Save Data   4. View Player Records   5. Exit Game\n> ");
		std::cin >> playerData.action;

		playerData.action = menuInputValidation(playerData.action, 5);

		switch (playerData.action)
		{
		case 2://View Rules

			showRules();
			break;

		case 3: //View Save Data

			switch (playerSaveData.noSaveDataExists) {

			case true:
				printf("\nNo save data currently exists for you.");

				break;

			case false:
				showSaveData(playerSaveData);
				break;

			default:
				break;
			}

			break;

		
		case 4://View Player Record
			showPlayerRecord(playerRecordData);
			break;

		default:
			break;
		}
	} while (playerData.action != 1 && playerData.action != 5);

	return playerData;

	


}