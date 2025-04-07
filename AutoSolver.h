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

	// ���׷��� �ݵ�� �ش��� �� ���� ������� ���� => �ش���� vector�� push�Ͽ� ��ȯ
	void Solution(PlayScene* playScene, Drawing* drawing);
	void FindAllSolutionDFS(PlayScene* playscene, Drawing* drawing, Drawing* solverDrawing, int rowIndex, int colIndex);
	vector<pair<int, int>> LeftSolve(vector<int> line);
	vector<pair<int, int>> RightSolve(vector<int> line);

	// �ش��� �� ���� true, �ƴϸ� false
	bool CheckUniqueSolution(PlayScene* playScene, Drawing* drawing);

	// �׸��� �ϼ��ƴ��� Ȯ��
	bool CheckGameOver(Drawing* solverDrawing, Drawing* drawing);
	bool CheckRow(Drawing* solverDrawing, Drawing* drawing, int index);
	bool CheckCol(Drawing* solverDrawing, Drawing* drawing, int index);

	// ���� ��� return
	vector<Drawing*> GetSolverDrawingList();

	// �÷��̾� ���� ��Ȳ�� �Ѱܹް� ���� ĭ �� ��ĥ ������ �κ��� ã�� ĥ����
	void GetHint(PlayScene* playScene, Drawing* drawing);
};

