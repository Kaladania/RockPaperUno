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

void showRules();

void getSavaData();

PlayerData gameIntro(Player& player, PlayerData& playerData) {

	playerData.name = player.setPlayerName(); //stores player name

	std::cout << "\nHello " << playerData.name << "!\n"
		<< "\nWelcome to";

	Sleep(900);

	printTitle();

	Sleep(900);

	printf("\n\nWhat would you like to do?\n1. Play Game   2. View Rules   3. View Save Data   4. Exit Game\n> ");
	std::cin >> playerData.action;

	playerData.action = menuInputValidation(playerData.action, 4);

	switch (playerData.action)
	{
	default:
		return playerData;
	}


}