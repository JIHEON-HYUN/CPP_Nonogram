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
	// AutoSolver 객체는 하나만 생성하므로, 이전 결과값 초기화시켜줌
	for (auto solver : solverDrawingList)
		delete solver;
	solverDrawingList.clear();

	Drawing* solverDrawing = new Drawing(*playScene->GetPlayerDrawing());
	
	// row가 완성됐으면 나머지 칸의 값은 2(X표시)로 설정
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

	// col이 완성됐으면 나머지 칸의 값은 2(X표시)로 설정
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

	// left, right solve가 일치하는 부분 색칠

	// 논리적 추론이 끝난 후, 재귀반복을 통해 정답을 찾음
	FindAllSolutionDFS(playScene, drawing, solverDrawing, 0, 0);

	// playScene 기준으로 값을 바꿨으므로, 저장될 때는 다시 playScene을 초기화
	playScene->Init();
}

void AutoSolver::FindAllSolutionDFS(PlayScene* playScene, Drawing* drawing, Drawing* solverDrawing, int rowIndex, int colIndex)
{
	// 모든 검사가 마무리됐을 때, 정답이면 solverDrawingList에 sol을 push
	if (rowIndex == solverDrawing->GetRowCount())
	{
		if (CheckGameOver(playScene, drawing))
		{
			Drawing* sol = new Drawing(*solverDrawing);
			solverDrawingList.push_back(sol);
		}
		
		return;
	}

	// colIndex가 마지막 col의 인덱스 값이면 rowIndex에 1을 더함
	int nextRowIndex = rowIndex + (colIndex + 1) / solverDrawing->GetColCount();
	// colIndex의 값을 1씩 더하되, colIndex가 마지막 col의 인덱스 값이면 0이 됨
	int nextColIndex = (colIndex + 1) % solverDrawing->GetColCount();

	// 현재 위치의 값이 0이 아니면 다음 검사로 넘어감
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

		// 재귀 완료 후에, 이전 상태로 되돌림 (현재 위치의 값이 0이었음)
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

	// Solution(playScene, drawing)에서 저장된 solverDrawing이 한 개면 해답이 유일함
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
	vector<int> answerRow = drawing->GetRowList()[index];
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
	vector<int> answerCol = drawing->GetColList()[index];
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
