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

void AutoSolver::Solution(PlayScene* playScene, Drawing* drawing)
{
	// AutoSolver ��ü�� �ϳ��� �����ϹǷ�, ���� ����� �ʱ�ȭ������
	for (auto solver : solverDrawingList)
		delete solver;
	solverDrawingList.clear();

	Drawing* solverDrawing = new Drawing(*playScene->GetPlayerDrawing());
	
	// row�� �ϼ������� ������ ĭ�� ���� 2(Xǥ��)�� ����
	for (int i = 0; i < solverDrawing->GetRowCount(); i++)
	{
		if (CheckRow(playScene, drawing, i))
		{
			for (int j = 0; j < solverDrawing->GetColCount(); j++)
			{
				if (solverDrawing->GetValue(i, j) == 0)
					solverDrawing->SetValue(i, j, 2);
			}
		}
	}

	// col�� �ϼ������� ������ ĭ�� ���� 2(Xǥ��)�� ����
	for (int i = 0; i < solverDrawing->GetColCount(); i++)
	{
		if (CheckCol(playScene, drawing, i))
		{
			for (int j = 0; j < solverDrawing->GetRowCount(); j++)
			{
				if (solverDrawing->GetValue(j, i) == 0)
					solverDrawing->SetValue(j, i, 2);
			}
		}
	}

	// left, right solve�� ��ġ�ϴ� �κ� ��ĥ

	// ���� �߷��� ���� ��, ��͹ݺ��� ���� ������ ã��
	FindAllSolutionDFS(playScene, drawing, solverDrawing, 0, 0);

	// playScene �������� ���� �ٲ����Ƿ�, ����� ���� �ٽ� playScene�� �ʱ�ȭ
	playScene->Init();
}

void AutoSolver::FindAllSolutionDFS(PlayScene* playScene, Drawing* drawing, Drawing* solverDrawing, int rowIndex, int colIndex)
{
	// ��� �˻簡 ���������� ��, �����̸� solverDrawingList�� sol�� push
	if (rowIndex == solverDrawing->GetRowCount())
	{
		if (CheckGameOver(playScene, drawing))
		{
			Drawing* sol = new Drawing(*solverDrawing);
			solverDrawingList.push_back(sol);
		}
		
		return;
	}

	// colIndex�� ������ col�� �ε��� ���̸� rowIndex�� 1�� ����
	int nextRowIndex = rowIndex + (colIndex + 1) / solverDrawing->GetColCount();
	// colIndex�� ���� 1�� ���ϵ�, colIndex�� ������ col�� �ε��� ���̸� 0�� ��
	int nextColIndex = (colIndex + 1) % solverDrawing->GetColCount();

	// ���� ��ġ�� ���� 0�� �ƴϸ� ���� �˻�� �Ѿ
	if (solverDrawing->GetValue(rowIndex, colIndex) != 0)
	{
		FindAllSolutionDFS(playScene, drawing, solverDrawing, nextRowIndex, nextColIndex);
		return;
	}

	for (int i = 1; i <= 2; i++)
	{
		solverDrawing->SetValue(rowIndex, colIndex, i);
		
		if (CheckRow(playScene, solverDrawing, rowIndex) && CheckCol(playScene, solverDrawing, colIndex))
			FindAllSolutionDFS(playScene, drawing, solverDrawing, nextRowIndex, nextColIndex);

		// ��� �Ϸ� �Ŀ�, ���� ���·� �ǵ��� (���� ��ġ�� ���� 0�̾���)
		solverDrawing->SetValue(rowIndex, colIndex, 0);
	}
}

vector<pair<int, int>> AutoSolver::LeftSolve(vector<int> line)
{
	return { {0, 0} };
}

vector<pair<int, int>> AutoSolver::RightSolve(vector<int> line)
{
	return { {0, 0} };
}

bool AutoSolver::CheckUniqueSolution(PlayScene* playScene, Drawing* drawing)
{
	Solution(playScene, drawing);

	// Solution(playScene, drawing)���� ����� solverDrawing�� �� ���� �ش��� ������
	if (solverDrawingList.size() == 1)
		return true;
	else
		return false;
}

vector<Drawing*> AutoSolver::GetSolverDrawingList()
{
	return solverDrawingList;
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
	vector<int> answerRow = drawing->GetRowList()[index];
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
	vector<int> answerCol = drawing->GetColList()[index];
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
