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
	Drawing* Solution(Drawing* solverDrawing);

	// �ش��� �� ���� true, �ƴϸ� false
	bool CheckUniqueSolution();

	// �׸��� �ϼ��ƴ��� Ȯ��
	bool CheckGameOver(PlayScene* playScene, Drawing* drawing);
	bool CheckRow(PlayScene* playScene, Drawing* drawing, int index);
	bool CheckCol(PlayScene* playScene, Drawing* drawing, int index);

	// �÷��̾� ���� ��Ȳ�� �Ѱܹް� �������� ��ĥ ������ �κ��� ã�� ĥ����
	void GetHint(PlayScene* playScene, Drawing* drawing);
};

