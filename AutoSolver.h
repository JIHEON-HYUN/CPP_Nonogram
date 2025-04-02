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
	bool CheckUniqueSolution(Drawing* drawing);
	void GetHint(Drawing* drawing, PlayScene* playScene);
};

