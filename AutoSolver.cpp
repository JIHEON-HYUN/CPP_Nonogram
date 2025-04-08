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
	
	// left, right solve�� ��ġ�ϴ� �κ� ��ĥ

	// ���� �߷��� ���� ��, ��͹ݺ��� ���� ������ ã��
	FindAllSolutionDFS(playScene, drawing, solverDrawing, 0, 0);
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
		// ���� ��ġ�� ���� 0�� ��, 1 or 2�� ���� �־
		solverDrawing->SetValue(rowIndex, colIndex, i);
		
		// ������� ĥ���� ĭ�� row��Ʈ�� col��Ʈ�� ������ ��쿡�� ��� ����
		// �ϼ��� ���� �ȵǾ ��Ʈ�� ��߳� �� �ƴϹǷ�, completeCheck���� false�� �ѱ�
		if (CheckRow(solverDrawing, drawing, rowIndex, false) && CheckCol(solverDrawing, drawing, colIndex, false))
		{
			FindAllSolutionDFS(playScene, drawing, solverDrawing, nextRowIndex, nextColIndex);
		}

		// ��� ���ǿ� ���� ������, ���� ���·� �ǵ���
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
			// �ϼ� �˻��̹Ƿ�, completeCheck�� ���� true�� �ѱ�
			if (!CheckRow(solverDrawing, drawing, i, true))
				return false;
		}

		// col �˻�
		for (int i = 0; i < sol->GetColCount(); i++)
		{
			// �ϼ� �˻��̹Ƿ�, completeCheck�� ���� true�� �ѱ�
			if (!CheckCol(solverDrawing, drawing, i, true))
				return false;
		}

		return true;
	}
}

bool AutoSolver::CheckRow(Drawing* solverDrawing, Drawing* drawing, int rowIndex, bool completeCheck)
{
	auto sol = solverDrawing;
	vector<int> answerRow = drawing->GetRowList()[rowIndex];
	vector<int> solRow;
	int count = 0;

	// solverDrawing�� rowIndex��°�� ���� ��Ʈ�� ����� �۾�
	for (int i = 0; i < sol->GetColCount(); i++)
	{
		int solValue = solverDrawing->GetValue(rowIndex, i);

		if (solValue == 1) 
			count++;
		else if (count > 0)
		{
			solRow.push_back(count);
			count = 0;
		}
	}

	if (count > 0) 
		solRow.push_back(count);

	// �ϼ� �˻����� Ȯ�� (true�� �ϼ� �˻�, false�� ������� ������� ���� ��Ʈ�� ��߳����� Ȯ��)
	if (completeCheck)
	{
		if (solRow.empty()) solRow.push_back(0);
		return solRow == answerRow;
	}
	else
	{
		// sol�� ���� ��Ʈ�� answer���� ���ų� Ŀ���� ���� ��� false ��ȯ
		if (solRow.size() > answerRow.size()) 
			return false;

		for (int i = 0; i < solRow.size(); i++)
		{
			if (solRow[i] > answerRow[i]) 
				return false;
		}

		// ���� ĭ �� ����
		int remain = 0;
		for (int i = 0; i < sol->GetColCount(); i++)
		{
			if (solverDrawing->GetValue(rowIndex, i) == 0)
				remain++;
		}

		int totalNeed = 0;
		if (answerRow.size() > solRow.size())
		{
			for (int i = solRow.size(); i < answerRow.size(); i++)
				totalNeed += answerRow[i];

			totalNeed += (answerRow.size() - solRow.size() - 1);
		}

		if (remain < totalNeed) 
			return false;

		return true;
	}
}

bool AutoSolver::CheckCol(Drawing* solverDrawing, Drawing* drawing, int colIndex, bool completeCheck)
{
	auto sol = solverDrawing;
	vector<int> answerCol = drawing->GetColList()[colIndex];
	vector<int> solCol;
	int count = 0;

	// solverDrawing�� colIndex��°�� ���� ��Ʈ�� ����� �۾�
	for (int i = 0; i < solverDrawing->GetRowCount(); i++)
	{
		int solValue = solverDrawing->GetValue(i, colIndex);

		if (solValue == 1)
			count++;
		else if (count > 0)
		{
			solCol.push_back(count);
			count = 0;
		}
	}

	if (count > 0)
		solCol.push_back(count);

	// �ϼ� �˻����� Ȯ�� (true�� �ϼ� �˻�, false�� ������� ������� ���� ��Ʈ�� ��߳����� Ȯ��)
	if (completeCheck)
	{
		if (solCol.empty()) solCol.push_back(0);
		return solCol == answerCol;
	}
	else
	{
		// sol�� ���� ��Ʈ�� answer���� ���ų� Ŀ���� ���� ��� false ��ȯ
		if (solCol.size() > answerCol.size())
			return false;

		for (int i = 0; i < solCol.size(); i++)
		{
			if (solCol[i] > answerCol[i]) return false;
		}

		// ���� ĭ �� ����
		int remain = 0;
		for (int i = 0; i < solverDrawing->GetRowCount(); i++)
		{
			if (solverDrawing->GetValue(i, colIndex) == 0)
				remain++;
		}

		int totalNeed = 0;
		if (answerCol.size() > solCol.size())
		{
			for (int i = solCol.size(); i < answerCol.size(); i++)
				totalNeed += answerCol[i];

			totalNeed += (answerCol.size() - solCol.size() - 1);
		}

		if (remain < totalNeed)
			return false;

		return true;
	}
}

void AutoSolver::GetHint(PlayScene* playScene, Drawing* drawing)
{

}