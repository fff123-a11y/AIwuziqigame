#include "ChessGame.h"
#include <iostream>
using namespace std;

int main(void) {
	Man man;
	Chess chess(7,17,15,23.3);

	AI ai;
	ChessGame game(&man, &ai, &chess);

	game.play();

	return 0;
}
