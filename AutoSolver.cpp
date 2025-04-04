#include "AutoSolver.h"

AutoSolver::AutoSolver()
{
}

AutoSolver::~AutoSolver()
{
}

vector<Drawing*> AutoSolver::Solution(Drawing* drawing)
{
	

	return solverDrawing;
}

bool AutoSolver::CheckUniqueSolution()
{
	// Solution()���� ����� solverDrawing�� �� ���� �ش��� ������
	if (solverDrawing.size() == 1)
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
	if (playScene->GetPlayerDrawing()->GetValueSum() != drawing->GetValueSum())
	{
		return false;
	}
	else
	{
		auto player = playScene->GetPlayerDrawing();

		// row �˻�
		for (int i = 0; i < player->GetRowCount(); i++)
		{
			vector<int> anwerRow = player->GetRowList()[i];
			vector<int> playerRow;
			int count = 0;

			for (int j = 0; j < player->GetColCount(); j++)
			{
				if (player->GetValue(i, j) == 1)
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

			if (playerRow != anwerRow)
				return false;
		}

		// col �˻�
		for (int i = 0; i < player->GetColCount(); i++)
		{
			vector<int> answerCol = player->GetColList()[i];
			vector<int> playerCol;
			int count = 0;

			for (int j = 0; j < player->GetRowCount(); j++)
			{
				if (player->GetValue(j, i) == 1)
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

			if (playerCol != answerCol)
				return false;
		}

		return true;
	}
}