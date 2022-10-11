#include "ChessGame.h"

ChessGame::ChessGame(Man* man, AI* ai, Chess* chess)
{
	//指针变量
	this->man = man;
	this->ai = ai;
	this->chess = chess;

	man->init(chess);
	ai->init(chess);
}

void ChessGame::play() {
	chess->init();
	while (1) {
		//先由棋手走
		man->go();
		if (chess->checkOver()) {
			chess->init();
			continue;
		}
		// 电脑棋手走
		ai->go();
		if (chess->checkOver()) {
			chess->init();
			continue;
		}
	}
}
