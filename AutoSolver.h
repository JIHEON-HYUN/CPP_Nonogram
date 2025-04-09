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

	// ���׷��� �ݵ�� �ش��� �� ���� ������� ���� => �ش���� vector�� push�Ͽ� ��ȯ
	void Solution(PlayScene* playScene, Drawing* drawing);
	void FindSolutionDFS(Drawing* solverDrawing, Drawing* drawing, int rowIndex, int colIndex);
	vector<pair<int, int>> LeftSolve(vector<int> line, int length);
	vector<pair<int, int>> RightSolve(vector<int> line, int length);
	void OverlapSolve(Drawing* solverDrawing, Drawing* drawing);

	// �ش� ���� ��ȯ (��, 2�� �̻��̸� DFS Ż���ϸ鼭 �ش��� 2������ ����)
	int CheckUniqueSolution(PlayScene* playScene, Drawing* drawing);

	// �׸��� �ϼ��ƴ��� Ȯ��
	bool CheckGameOver(Drawing* solverDrawing, Drawing* drawing);
	bool CheckRow(Drawing* solverDrawing, Drawing* drawing, int rowIndex, bool completeCheck);
	bool CheckCol(Drawing* solverDrawing, Drawing* drawing, int colIndex, bool completeCheck);

	// ���� ��� return
	vector<Drawing*> GetSolverDrawingList();

	// �÷��̾� ���� ��Ȳ�� �Ѱܹް� ����� �ٸ� �κ��� ã�� ������
	void GetHint(PlayScene* playScene, Drawing* drawing, int hintCount);
};

