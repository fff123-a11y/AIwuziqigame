#pragma once
#include <graphics.h>
#include <vector>
using namespace std;

//表示落子位置
struct ChessPos {
	int row;
	int col;

	ChessPos(int r = 0, int c = 0) :row(r), col(c) {

	}
};

typedef enum {
	CHESS_WRITE = -1, //白方
	CHESS_BLACK = 1 //黑方
}chess_kind_t;

class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);

	void init();
	
	bool clickBoard(int x, int y, ChessPos *pos);
	
	void chessDown(ChessPos *pos, chess_kind_t kind);
	
	int getGradeSize(); //获取棋盘的大小（13，15，19）
	
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);
	
	bool checkOver(); // 检查棋局是否结束

private:
	IMAGE chessBlackImg;
	IMAGE chessWriteImg;

	int gradeSize;
	int margin_x;
	int margin_y;
	float chessSize;

	//存储当前棋局的棋子分布数据 0:空白 1:黑子 -1:白子
	vector<vector<int>> chessMap;

	//表示现在该谁落子
	bool playerFlag;

	ChessPos lastPos;

	void updateGame(ChessPos* pos);//棋盘布局

	bool checkWin();//如果棋局已经结束,就返回true,否则返回false
};

