#pragma once
#include <vector>
#include "Drawing.h"
#include "PlayScene.h"

using namespace std;

class AutoSolver
{
private:
	vector<Drawing*> solverDrawingList;

public:
	AutoSolver();
	~AutoSolver();

	// 노노그램은 반드시 해답이 한 개로 보장되지 않음 => 해답들을 vector에 push하여 반환
	Drawing* Solution(Drawing* solverDrawing);

	// 해답이 한 개면 true, 아니면 false
	bool CheckUniqueSolution();

	// 그림이 완성됐는지 확인
	bool CheckGameOver(PlayScene* playScene, Drawing* drawing);
	bool CheckRow(PlayScene* playScene, Drawing* drawing, int index);
	bool CheckCol(PlayScene* playScene, Drawing* drawing, int index);

	// 플레이어 현재 상황을 넘겨받고 논리적으로 색칠 가능한 부분을 찾아 칠해줌
	void GetHint(PlayScene* playScene, Drawing* drawing);
};

