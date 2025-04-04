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
	// Solution()에서 저장된 solverDrawing이 한 개면 해답이 유일함
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
	// 총 칠해진 칸 수가 다르면 검사 돌리지않고 바로 false 반환
	if (playScene->GetPlayerDrawing()->GetValueSum() != drawing->GetValueSum())
	{
		return false;
	}
	else
	{
		auto player = playScene->GetPlayerDrawing();

		// row 검사
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

		// col 검사
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