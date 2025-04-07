#include "AutoSolver.h"
#include <iostream>

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

	//// row�� �ϼ������� ������ ĭ�� ���� 2(Xǥ��)�� ����
	//for (int i = 0; i < solverDrawing->GetRowCount(); i++)
	//{
	//	if (CheckRow(playScene->GetPlayerDrawing(), drawing, i))
	//	{
	//		for (int j = 0; j < solverDrawing->GetColCount(); j++)
	//		{
	//			if (solverDrawing->GetValue(i, j) == 0)
	//				solverDrawing->SetValue(i, j, 2);
	//		}
	//	}
	//}

	//// col�� �ϼ������� ������ ĭ�� ���� 2(Xǥ��)�� ����
	//for (int i = 0; i < solverDrawing->GetColCount(); i++)
	//{
	//	if (CheckCol(playScene->GetPlayerDrawing(), drawing, i))
	//	{
	//		for (int j = 0; j < solverDrawing->GetRowCount(); j++)
	//		{
	//			if (solverDrawing->GetValue(j, i) == 0)
	//				solverDrawing->SetValue(j, i, 2);
	//		}
	//	}
	//}
	
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
		
		if (IsRowValid(solverDrawing, drawing, rowIndex) && IsColValid(solverDrawing, drawing, colIndex))
		{
			FindAllSolutionDFS(playScene, drawing, solverDrawing, nextRowIndex, nextColIndex);
		}

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
	for (int i = 0; i < sol->GetColCount(); i++)
	{
		if (sol->GetValue(index, i) == 1)
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

	if (solRow != answerRow)
		return false;
	
	return true;
}

bool AutoSolver::CheckCol(Drawing* solverDrawing, Drawing* drawing, int index)
{
	auto sol = solverDrawing;
	vector<int> answerCol = drawing->GetColList()[index];
	vector<int> solCol;
	int count = 0;

	// drawing�� colList ����� ����� �����ϰ� playerCol ����
	for (int i = 0; i < sol->GetRowCount(); i++)
	{
		if (sol->GetValue(i, index) == 1)
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

	if (solCol != answerCol)
		return false;

	return true;
}

bool AutoSolver::IsRowValid(Drawing* solverDrawing, Drawing* drawing, int rowIndex)
{
	auto hint = drawing->GetRowList()[rowIndex];
	vector<int> blocks;
	int count = 0;

	for (int i = 0; i < solverDrawing->GetColCount(); i++)
	{
		int val = solverDrawing->GetValue(rowIndex, i);
		if (val == 1) count++;
		else if (count > 0)
		{
			blocks.push_back(count);
			count = 0;
		}
	}
	if (count > 0) blocks.push_back(count);

	// ��� ���� ��Ʈ���� ������ ������ ��
	if (blocks.size() > hint.size()) return false;

	// ���ݱ��� ������� ����� ��Ʈ�� �ʰ����� �ʴ��� Ȯ��
	for (size_t i = 0; i < blocks.size(); i++)
	{
		if (blocks[i] > hint[i]) return false;
	}

	// ���� ĭ���� ����� ���� �� �ִ��� �Ǵ�
	int remain = 0;
	for (int i = 0; i < solverDrawing->GetColCount(); i++)
	{
		if (solverDrawing->GetValue(rowIndex, i) == 0)
			remain++;
	}

	// ���� ��Ʈ ��� ���� �� + �ּ� ���� ĭ ��
	int totalNeed = 0;
	if (hint.size() > blocks.size())
	{
		for (size_t i = blocks.size(); i < hint.size(); i++)
			totalNeed += hint[i];
		totalNeed += (hint.size() - blocks.size() - 1);
	}

	if (remain < totalNeed) return false;

	return true;
}

bool AutoSolver::IsColValid(Drawing* solverDrawing, Drawing* drawing, int colIndex)
{
	auto hint = drawing->GetColList()[colIndex];
	vector<int> blocks;
	int count = 0;

	for (int i = 0; i < solverDrawing->GetRowCount(); i++)
	{
		int val = solverDrawing->GetValue(i, colIndex);
		if (val == 1) count++;
		else if (count > 0)
		{
			blocks.push_back(count);
			count = 0;
		}
	}
	if (count > 0) blocks.push_back(count);

	// ��� ���� ��Ʈ���� ������ ������ ��
	if (blocks.size() > hint.size()) return false;

	// ���ݱ��� ������� ����� ��Ʈ�� �ʰ����� �ʴ��� Ȯ��
	for (size_t i = 0; i < blocks.size(); i++)
	{
		if (blocks[i] > hint[i]) return false;
	}

	// ���� ĭ���� ����� ���� �� �ִ��� �Ǵ�
	int remain = 0;
	for (int i = 0; i < solverDrawing->GetRowCount(); i++)
	{
		if (solverDrawing->GetValue(i, colIndex) == 0)
			remain++;
	}

	// ���� ��Ʈ ��� ���� �� + �ּ� ���� ĭ ��
	int totalNeed = 0;
	if (hint.size() > blocks.size())
	{
		for (size_t i = blocks.size(); i < hint.size(); i++)
			totalNeed += hint[i];
		totalNeed += (hint.size() - blocks.size() - 1);
	}

	if (remain < totalNeed) return false;

	return true;
}