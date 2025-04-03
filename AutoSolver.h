#pragma once
#include <vector>
#include "Drawing.h"
#include "PlayScene.h"

using namespace std;

class AutoSolver
{
private:
	Drawing* solverDrawing;

public:
	AutoSolver();
	~AutoSolver();

	vector<Drawing*> Solution(Drawing* drawing);

	// 노노그램은 반드시 해답이 한 개로 보장되지 않음
	// 입력한 그림의 숫자 힌트가 나왔을 때, 역산하여 해답이 한 개인지 찾는 메소드
	bool CheckUniqueSolution(Drawing* drawing);

	void GetHint(Drawing* drawing, PlayScene* playScene);
};

