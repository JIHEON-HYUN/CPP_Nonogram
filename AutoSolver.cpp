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
	// Solution()에서 저장된 solverDrawing이 한 개면 해답이 유일함
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
	// 총 칠해진 칸 수가 다르면 검사 돌리지않고 바로 false 반환
	if (playScene->GetPlayerDrawing()->GetAllSum() != drawing->GetAllSum())
	{
		return false;
	}
	else
	{
		auto player = playScene->GetPlayerDrawing();

		// row 검사
		for (int i = 0; i < player->GetRowCount(); i++)
		{
			if (!CheckRow(playScene, drawing, i))
				return false;
		}

		// col 검사
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

	// drawing의 rowList 만드는 방법과 동일하게 playerRow 생성
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

	// playerRow와 answerRow가 다르면 false 반환
	if (playerRow != answerRow)
		return false;
	
	// playerRow와 answerRow가 같으면 true 반환
	return true;
}

bool AutoSolver::CheckCol(PlayScene* playScene, Drawing* drawing, int index)
{
	auto player = playScene->GetPlayerDrawing();
	vector<int> answerCol = player->GetColList()[index];
	vector<int> playerCol;
	int count = 0;

	// drawing의 colList 만드는 방법과 동일하게 playerCol 생성
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

	// playerCol과 answerCol이 다르면 false 반환
	if (playerCol != answerCol)
		return false;
	
	// playerCol과 answerCol이 다르면 true 반환
	return true;
}
