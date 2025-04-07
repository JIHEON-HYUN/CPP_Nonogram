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
	void Solution(PlayScene* playScene, Drawing* drawing);
	void FindAllSolutionDFS(PlayScene* playscene, Drawing* drawing, Drawing* solverDrawing, int rowIndex, int colIndex);
	vector<pair<int, int>> LeftSolve(vector<int> line);
	vector<pair<int, int>> RightSolve(vector<int> line);

	// 해답이 한 개면 true, 아니면 false
	bool CheckUniqueSolution(PlayScene* playScene, Drawing* drawing);

	// 그림이 완성됐는지 확인
	bool CheckGameOver(Drawing* solverDrawing, Drawing* drawing);
	bool CheckRow(Drawing* solverDrawing, Drawing* drawing, int index);
	bool CheckCol(Drawing* solverDrawing, Drawing* drawing, int index);

	// 정답 목록 return
	vector<Drawing*> GetSolverDrawingList();

	// 플레이어 현재 상황을 넘겨받고 남은 칸 중 색칠 가능한 부분을 찾아 칠해줌
	void GetHint(PlayScene* playScene, Drawing* drawing);
};

