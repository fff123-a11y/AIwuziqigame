#include "Man.h"
#include <Windows.h>
#include "AnotherMan.h"

void Man::init(Chess* chess)
{
	this->chess = chess;
}

void Man::go()
{
	//获取鼠标点击消息
	MOUSEMSG msg;
	ChessPos pos;

	while (1) {
		//获取鼠标点击消息
		msg = GetMouseMsg();

		//通过chess对象，来调用 判断落子是否有效，以及落子功能
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos)) {
			break;
		}
	}

	printf("%d, %d\n", pos.row, pos.col);

	//落子
	chess->chessDown(&pos, CHESS_BLACK);
	chess->chessDown(&pos, CHESS_WRITE);
}
