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

	// ���׷��� �ݵ�� �ش��� �� ���� ������� ����
	// drawing�� �ش��� �� ������ ã�� �޼ҵ�
	bool CheckUniqueSolution();

	// �׸��� �ϼ��ƴ��� Ȯ��
	bool CheckGameOver(PlayScene* playScene, Drawing* drawing);

	// �÷��̾� ���� ��Ȳ�� �Ѱܹް� �������� ��ĥ ������ �κ��� ã�� ĥ����
	void GetHint(PlayScene* playScene, Drawing* drawing);
};

