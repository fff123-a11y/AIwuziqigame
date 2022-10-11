#include "AI.h"
#include <iostream>

using namespace std;

//初始化AI
void AI::init(Chess* chess)
{
	this->chess = chess;

	int size = chess->getGradeSize();
	for (int i = 0; i < size; i++) {
		vector<int> row;
		for (int j = 0; j < size; j++) {
			row.push_back(0);
		}

		scoreMap.push_back(row);
	}
}

//AI走棋
void AI::go()
{
	ChessPos pos = think();
	//思考时间戳
	Sleep(1000);
	//下棋
	chess->chessDown(&pos, CHESS_WRITE);
}

void AI::calculateScore() {

	int personSum = 0;//黑棋有多少个连续的棋子
	int ainum = 0;//AI方有多少个连续的棋子
	int emptyNum = 0;

	//评分向量数组清零
	for (int i = 0; i < scoreMap.size(); i++) {
		for (int j = 0; j < scoreMap[i].size(); j++) {
			scoreMap[i][j] = 0;
		}
	}

	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			//对每个点进行计算
			if (chess->getChessData(row, col) == 0) {
				continue;
			}
			for (int y = -1; y <= 1; y++) {
				for (int x = -1; x <= 1; x++) {
					if (y == 0 && x == 0) continue;
					if (y == 0 && x != 1) continue;

					//假设黑棋在该位置落子,会构成什么棋形
					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 1) {
							personSum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					//反向继续进行计算
					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;
						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 1) {
							personSum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					if(personSum == 1){ //连2
						scoreMap[row][col] += 10;
					}
					else if (personSum == 2) {
						if (emptyNum == 1) {//死三
							scoreMap[row][col] += 30;
						}
						else if (emptyNum == 2) {//活三
							scoreMap[row][col] += 40;
						}
					}
					else if (personSum == 3) {
						if (emptyNum == 1) {
							scoreMap[row][col] = 60;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] = 200;
						}
					}
					else if (personSum == 4) {
						scoreMap[row][col] = 2000;
					}
					
					//假设白棋在该位置落子,会构成什么棋形
					emptyNum = 0;
					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 1) {
							personSum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}
					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;
						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 1) {
							personSum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					if (personSum == 1) { //连2
						scoreMap[row][col] += 10;
					}
					else if (personSum == 2) {
						if (emptyNum == 1) {//死三
							scoreMap[row][col] += 30;
						}
						else if (emptyNum == 2) {//活三
							scoreMap[row][col] += 40;
						}
					}
					else if (personSum == 3) {
						if (emptyNum == 1) {
							scoreMap[row][col] = 60;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] = 200;
						}
					}
					else if (personSum == 4) {
						scoreMap[row][col] = 2000;
					}
					if (ainum == 0) {
						scoreMap[row][col] += 5;
					}
					else if (ainum == 1) {
						scoreMap[row][col] += 10;
					}
					else if (ainum == 2) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 25;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 50;
						}
					}
					else if (ainum == 3) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 55;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 10000;
						}
					}
					else if (ainum >= 4) {
						scoreMap[row][col] += 30000;
					}
				}
			}
		}
	}
}

//AI思考走棋程序
ChessPos AI::think()
{
	calculateScore();

	vector<ChessPos> maxPoints;
	int maxScore = 0;
	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			if (chess->getChessData(row, col) == 0) {
				if (scoreMap[row][col] > maxScore) {
					maxScore = scoreMap[row][col];
					maxPoints.clear();
					maxPoints.push_back(ChessPos(row, col));
				}
				else if (scoreMap[row][col] == maxScore) {
					maxPoints.push_back(ChessPos(row, col));
				}
			}
		}
	}

	//不加这个程序会报错,导致数据溢出
	int index = rand() % maxPoints.size();
	return maxPoints[index];
}
