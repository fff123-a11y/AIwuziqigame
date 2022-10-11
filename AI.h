#pragma once
#include "Chess.h"

class AI
{
public:
	void init(Chess *chess);
	void go();

private:
	Chess* chess;
	vector<vector<int>> scoreMap;

private:
	void calculateScore();
	ChessPos think();
};

