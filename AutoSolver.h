#pragma once
#include <vector>
#include <chrono>
#include "Drawing.h"
#include "PlayScene.h"

using namespace std;
using namespace std::chrono;

class AutoSolver
{
private:
	vector<Drawing*> solverDrawingList;
	steady_clock::time_point solStart;

public:
	AutoSolver();
	~AutoSolver();

	// 노노그램은 반드시 해답이 한 개로 보장되지 않음 => 해답들을 vector에 push하여 반환
	void Solution(PlayScene* playScene, Drawing* drawing);
	void FindSolutionDFS(Drawing* solverDrawing, Drawing* drawing, int rowIndex, int colIndex);
	vector<pair<int, int>> LeftSolve(vector<int> line, int length);
	vector<pair<int, int>> RightSolve(vector<int> line, int length);
	void OverlapSolve(Drawing* solverDrawing, Drawing* drawing);

	// 해답 개수 반환 (단, 2개 이상이면 DFS 탈출하면서 해답이 2개에서 끊김)
	int CheckUniqueSolution(PlayScene* playScene, Drawing* drawing);

	// 그림이 완성됐는지 확인
	bool CheckGameOver(Drawing* solverDrawing, Drawing* drawing);
	bool CheckRow(Drawing* solverDrawing, Drawing* drawing, int rowIndex, bool completeCheck);
	bool CheckCol(Drawing* solverDrawing, Drawing* drawing, int colIndex, bool completeCheck);

	// 정답 목록 return
	vector<Drawing*> GetSolverDrawingList();

	// 플레이어 현재 상황을 넘겨받고 정답과 다른 부분을 찾아 고쳐줌
	void GetHint(PlayScene* playScene, Drawing* drawing, int hintCount);
};

