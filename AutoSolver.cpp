#include "AutoSolver.h"

AutoSolver::AutoSolver()
{
}

AutoSolver::~AutoSolver()
{
	for (auto solver : solverDrawingList)
		delete solver;
	solverDrawingList.clear();
}

Drawing* AutoSolver::Solution(Drawing* solverDrawing)
{
	
}

bool AutoSolver::CheckUniqueSolution()
{
	// Solution()���� ����� solverDrawing�� �� ���� �ش��� ������
	if (solverDrawingList.size() == 1)
		return true;
	else
		return false;
}

void AutoSolver::GetHint(PlayScene* playScene, Drawing* drawing)
{
	
}

bool AutoSolver::CheckGameOver(PlayScene* playScene, Drawing* drawing)
{
	// �� ĥ���� ĭ ���� �ٸ��� �˻� �������ʰ� �ٷ� false ��ȯ
	if (playScene->GetPlayerDrawing()->GetAllSum() != drawing->GetAllSum())
	{
		return false;
	}
	else
	{
		auto player = playScene->GetPlayerDrawing();

		// row �˻�
		for (int i = 0; i < player->GetRowCount(); i++)
		{
			if (!CheckRow(playScene, drawing, i))
				return false;
		}

		// col �˻�
		for (int i = 0; i < player->GetColCount(); i++)
		{
			if (!CheckCol(playScene, drawing, i))
				return false;
		}

		return true;
	}
}

bool AutoSolver::CheckRow(PlayScene* playScene, Drawing* drawing, int index)
{
	auto player = playScene->GetPlayerDrawing();
	vector<int> answerRow = player->GetRowList()[index];
	vector<int> playerRow;
	int count = 0;

	// drawing�� rowList ����� ����� �����ϰ� playerRow ����
	for (int j = 0; j < player->GetColCount(); j++)
	{
		if (player->GetValue(index, j) == 1)
			count++;
		else
		{
			if (count != 0)
			{
				playerRow.push_back(count);
				count = 0;
			}
		}
	}

	if (count != 0)
		playerRow.push_back(count);

	if (playerRow.empty())
		playerRow.push_back(0);

	// playerRow�� answerRow�� �ٸ��� false ��ȯ
	if (playerRow != answerRow)
		return false;
	
	// playerRow�� answerRow�� ������ true ��ȯ
	return true;
}

bool AutoSolver::CheckCol(PlayScene* playScene, Drawing* drawing, int index)
{
	auto player = playScene->GetPlayerDrawing();
	vector<int> answerCol = player->GetColList()[index];
	vector<int> playerCol;
	int count = 0;

	// drawing�� colList ����� ����� �����ϰ� playerCol ����
	for (int j = 0; j < player->GetRowCount(); j++)
	{
		if (player->GetValue(j, index) == 1)
			count++;
		else
		{
			if (count != 0)
			{
				playerCol.push_back(count);
				count = 0;
			}
		}
	}

	if (count != 0)
		playerCol.push_back(count);

	if (playerCol.empty())
		playerCol.push_back(0);

	// playerCol�� answerCol�� �ٸ��� false ��ȯ
	if (playerCol != answerCol)
		return false;
	
	// playerCol�� answerCol�� �ٸ��� true ��ȯ
	return true;
}
