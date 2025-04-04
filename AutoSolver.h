#pragma once
#include <vector>
#include "Drawing.h"
#include "PlayScene.h"

using namespace std;

class AutoSolver
{
private:
	vector<Drawing*> solverDrawing;

public:
	AutoSolver();
	~AutoSolver();

	vector<Drawing*> Solution(Drawing* drawing);

	// 노노그램은 반드시 해답이 한 개로 보장되지 않음
	// drawing의 해답이 한 개인지 찾는 메소드
	bool CheckUniqueSolution();

	// 그림이 완성됐는지 확인
	bool CheckGameOver(PlayScene* playScene, Drawing* drawing);

	// 플레이어 현재 상황을 넘겨받고 논리적으로 색칠 가능한 부분을 찾아 칠해줌
	void GetHint(PlayScene* playScene, Drawing* drawing);
};

