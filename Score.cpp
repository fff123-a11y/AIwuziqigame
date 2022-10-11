#include <iostream>
#include "Chess.h"

using namespace std;

//统计分数
void getScoreRanking(int score, int rank){
	if (score <= 0) {
		printf("门童");
	}
	else if (score > 0 && score <= 300) {
		printf("初出茅庐");
	}
	else if (score > 300 && score <= 1000) {
		printf("锋芒毕露");
	}
	else if (score > 1000) {
		printf("五子棋高手");
	}
	else {
		printf("大神");
	}

	return getScoreRanking(score, rank);
}
