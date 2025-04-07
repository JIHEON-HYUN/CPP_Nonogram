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
		if (CheckRow(playScene->GetPlayerDrawing(), drawing, i))
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
		if (CheckCol(playScene->GetPlayerDrawing(), drawing, i))
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
		if (CheckGameOver(solverDrawing, drawing))
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
		
		if (CheckRow(solverDrawing, drawing, rowIndex) && CheckCol(solverDrawing, drawing, colIndex))
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
	// Solution()���� ����� solverDrawing�� �� ���� �ش��� ������
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

bool AutoSolver::CheckGameOver(Drawing* solverDrawing, Drawing* drawing)
{
	// �� ĥ���� ĭ ���� �ٸ��� �˻� �������ʰ� �ٷ� false ��ȯ
	if (solverDrawing->GetAllSum() != drawing->GetAllSum())
	{
		return false;
	}
	else
	{
		auto sol = solverDrawing;

		// row �˻�
		for (int i = 0; i < sol->GetRowCount(); i++)
		{
			if (!CheckRow(solverDrawing, drawing, i))
				return false;
		}

		// col �˻�
		for (int i = 0; i < sol->GetColCount(); i++)
		{
			if (!CheckCol(solverDrawing, drawing, i))
				return false;
		}

		return true;
	}
}

bool AutoSolver::CheckRow(Drawing* solverDrawing, Drawing* drawing, int index)
{
	auto sol = solverDrawing;
	vector<int> answerRow = drawing->GetRowList()[index];
	vector<int> solRow;
	int count = 0;

	// drawing�� rowList ����� ����� �����ϰ� playerRow ����
	for (int j = 0; j < sol->GetColCount(); j++)
	{
		if (sol->GetValue(index, j) == 1)
			count++;
		else
		{
			if (count != 0)
			{
				solRow.push_back(count);
				count = 0;
			}
		}
	}

	if (count != 0)
		solRow.push_back(count);

	if (solRow.empty())
		solRow.push_back(0);

	// solRow�� answerRow�� �ٸ��� false ��ȯ
	if (solRow != answerRow)
		return false;
	
	// solRow�� answerRow�� ������ true ��ȯ
	return true;
}

bool AutoSolver::CheckCol(Drawing* solverDrawing, Drawing* drawing, int index)
{
	auto sol = solverDrawing;
	vector<int> answerCol = drawing->GetColList()[index];
	vector<int> solCol;
	int count = 0;

	// drawing�� colList ����� ����� �����ϰ� playerCol ����
	for (int j = 0; j < sol->GetRowCount(); j++)
	{
		if (sol->GetValue(j, index) == 1)
			count++;
		else
		{
			if (count != 0)
			{
				solCol.push_back(count);
				count = 0;
			}
		}
	}

	if (count != 0)
		solCol.push_back(count);

	if (solCol.empty())
		solCol.push_back(0);

	// solCol�� answerCol�� �ٸ��� false ��ȯ
	if (solCol != answerCol)
		return false;
	
	// playerCol�� answerCol�� �ٸ��� true ��ȯ
	return true;
}
