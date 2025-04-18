#include "AutoSolver.h"
#include "GameManager.h"
#include <iostream>
#include <windows.h>

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
	// Solution()의 실행 시간 측정 시작
	solStart = steady_clock::now();

	// AutoSolver 객체는 하나만 생성하므로, 이전 결과값 초기화시켜줌
	for (auto solver : solverDrawingList)
		delete solver;
	solverDrawingList.clear();

	Drawing* solverDrawing = new Drawing(*playScene->GetPlayerDrawing());
	for (int i = 0; i < solverDrawing->GetRowCount(); i++)
	{
		for (int j = 0; j < solverDrawing->GetColCount(); j++)
		{
			solverDrawing->SetValue(i, j, 0);
		}
	}

	//// 논리적 추론 (1) : 힌트만으로 row 결정
	//for (int i = 0; i < solverDrawing->GetRowCount(); i++)
	//{
	//	vector<int> solRow = solverDrawing->GetRowList()[i];
	//	
	//	// 힌트가 0인 경우
	//	if (solRow[0] == 0)
	//	{
	//		for (int j = 0; j < solverDrawing->GetColCount(); j++)
	//			solverDrawing->SetValue(i, j, 2);

	//		continue;
	//	}

	//	int rowCount = solRow.size() - 1;
	//	for (int j = 0; j < solRow.size(); j++)
	//	{
	//		rowCount += solRow[j];
	//	}

	//	// 힌트만으로 모든 칸을 칠하거나 X표시로 확정지을 수 있을 때
	//	if (rowCount == solverDrawing->GetColCount())
	//	{
	//		int cur = 0;

	//		for (int j = 0; j < solRow.size(); j++)
	//		{
	//			// 힌트대로 색칠
	//			for (int k = 0; k < solRow[j]; k++)
	//			{
	//				solverDrawing->SetValue(i, cur++, 1);
	//			}

	//			// 힌트가 완성되고 마지막 칸이 아니면 X표시
	//			if (j != solRow.size() - 1)
	//			{
	//				solverDrawing->SetValue(i, cur++, 2);
	//			}
	//		}
	//	}
	//}

	//// 논리적 추론 (2) : 힌트만으로 col 결정
	//for (int i = 0; i < solverDrawing->GetColCount(); i++)
	//{
	//	vector<int> solCol = solverDrawing->GetColList()[i];

	//	// 힌트가 0인 경우
	//	if (solCol[0] == 0)
	//	{
	//		for (int j = 0; j < solverDrawing->GetRowCount(); j++)
	//			solverDrawing->SetValue(j, i, 2);

	//		continue;
	//	}

	//	int colCount = solCol.size() - 1;
	//	for (int j = 0; j < solCol.size(); j++)
	//	{
	//		colCount += solCol[j];
	//	}

	//	// 힌트만으로 모든 칸을 칠하거나 X표시로 확정지을 수 있을 때
	//	if (colCount == solverDrawing->GetRowCount())
	//	{
	//		int cur = 0;

	//		for (int j = 0; j < solCol.size(); j++)
	//		{
	//			// 힌트대로 색칠
	//			for (int k = 0; k < solCol[j]; k++)
	//			{
	//				solverDrawing->SetValue(cur++, i, 1);
	//			}

	//			// 힌트가 완성되고 마지막 칸이 아니면 X표시
	//			if (j != solCol.size() - 1)
	//			{
	//				solverDrawing->SetValue(cur++, i, 2);
	//			}
	//		}
	//	}
	//}

	//// 논리적 추론 (3) : leftSolve, rightSolve가 일치하는 부분으로 결정
	//OverlapSolve(solverDrawing, drawing);

	// 논리적 추론이 끝난 후, 재귀반복을 통해 정답을 찾음
	FindSolutionDFS(solverDrawing, drawing, 0, 0);
}

void AutoSolver::FindSolutionDFS(Drawing* solverDrawing, Drawing* drawing, int rowIndex, int colIndex)
{
	// 실행이 30초가 넘어가면 종료
	steady_clock::time_point solNow = steady_clock::now();
	if (duration_cast<seconds>(solNow - solStart).count() > 30)
	{
		for (auto solver : solverDrawingList)
			delete solver;
		solverDrawingList.clear();
		return;
	}
		
	//// 노노그램 해답 유일성을 보장하기 위해, 복수 정답이 되는 순간 재귀 종료
	if (solverDrawingList.size() >= 2)
		return;

	// 모든 검사가 마무리됐을 때, 정답이면 solverDrawingList에 sol을 push
	if (rowIndex == solverDrawing->GetRowCount())
	{
		if (CheckGameOver(solverDrawing, drawing))
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
		//GameManager::GetGM()->boardViewer.Render(solverDrawing);
		FindSolutionDFS(solverDrawing, drawing, nextRowIndex, nextColIndex);
		return;
	}

	// 현재 위치의 값이 0일 때, 1 or 2의 값을 넣어보면서 재귀
	for (int i = 1; i <= 2; i++)
	{
		solverDrawing->SetValue(rowIndex, colIndex, i);
		
		// 현재까지 칠해진 칸이 row힌트와 col힌트에 부합할 경우에만 재귀 진행
		// 완성이 아직 안되어도 힌트에 어긋난 건 아니므로, completeCheck값을 false로 넘김
		if (CheckRow(solverDrawing, drawing, rowIndex, false) && CheckCol(solverDrawing, drawing, colIndex, false))
		{
			//GameManager::GetGM()->boardViewer.Render(solverDrawing);
			FindSolutionDFS(solverDrawing, drawing, nextRowIndex, nextColIndex);
		}

		// 재귀 조건에 들어가지 않으면, 이전 상태로 되돌림
		//GameManager::GetGM()->boardViewer.Render(solverDrawing);
		solverDrawing->SetValue(rowIndex, colIndex, 0);
	}
}

vector<pair<int, int>> AutoSolver::LeftSolve(vector<int> line, int length)
{
	vector<pair<int, int>> leftSolution(length, { 0, 0 });
	int cur = 0;

	// 왼쪽부터 채웠을 때, 칠해지는 칸은 1값과 몇번째 블록인지 인덱스 값을 pair로 저장
	for (int i = 0; i < line.size(); i++)
	{
		for (int j = 0; j < line[i]; j++)
		{
			leftSolution[cur].first = 1;
			leftSolution[cur].second = i;
			cur++;
		}

		if (i < line.size() - 1)
			cur++;
	}

	return leftSolution;
}

vector<pair<int, int>> AutoSolver::RightSolve(vector<int> line, int length)
{
	vector<pair<int, int>> rightSolution(length, { 0, 0 });
	int cur = length - 1;

	// 오른쪽부터 채웠을 때, 칠해지는 칸은 1값과 몇번째 블록인지 인덱스 값을 pair로 저장
	for (int i = line.size() - 1; i >= 0; i--)
	{
		for (int j = 0; j < line[i]; j++)
		{
			rightSolution[cur].first = 1;
			rightSolution[cur].second = i;
			cur--;
		}

		if (i > 0)
			cur--;
	}

	return rightSolution;
}

void AutoSolver::OverlapSolve(Drawing* solverDrawing, Drawing* drawing)
{
	// row에서 leftSolve, rightSolve가 일치하는 부분 색칠
	for (int i = 0; i < solverDrawing->GetRowCount(); i++)
	{
		vector<pair<int, int>> leftSolution = LeftSolve(solverDrawing->GetRowList()[i], solverDrawing->GetColCount());
		vector<pair<int, int>> rightSolution = RightSolve(solverDrawing->GetRowList()[i], solverDrawing->GetColCount());

		for (int j = 0; j < leftSolution.size(); j++)
		{
			// 값이 둘 다 1이고, 몇번 째 힌트인지도 일치하면 1값 대입
			if (leftSolution[j].first == 1 && rightSolution[j].first == 1 && leftSolution[j].second == rightSolution[j].second)
				solverDrawing->SetValue(i, j, 1);
		}
	}

	// col에서 leftSolve, rightSolve가 일치하는 부분 색칠
	for (int i = 0; i < solverDrawing->GetColCount(); i++)
	{
		vector<pair<int, int>> leftSolution = LeftSolve(solverDrawing->GetColList()[i], solverDrawing->GetRowCount());
		vector<pair<int, int>> rightSolution = RightSolve(solverDrawing->GetColList()[i], solverDrawing->GetRowCount());

		for (int j = 0; j < leftSolution.size(); j++)
		{
			// 값이 둘 다 1이고, 몇번 째 힌트인지도 일치하면 1값 대입
			if (leftSolution[j].first == 1 && rightSolution[j].first == 1 && leftSolution[j].second == rightSolution[j].second)
				solverDrawing->SetValue(j, i, 1);
		}
	}
}

int AutoSolver::CheckUniqueSolution(PlayScene* playScene, Drawing* drawing)
{
	Solution(playScene, drawing);

	// Solution()에서 저장된 solverDrawing이 0개면 시간 초과
	if (solverDrawingList.size() == 0)
		return 0;
	// Solution()에서 저장된 solverDrawing이 1개면 유일 해답
	else if (solverDrawingList.size() == 1)
		return 1;
	// Solution()에서 저장된 solverDrawing이 2개면 복수 정답
	else
		return 2;
}

vector<Drawing*> AutoSolver::GetSolverDrawingList()
{
	return solverDrawingList;
}

bool AutoSolver::CheckGameOver(Drawing* solverDrawing, Drawing* drawing)
{
	// 총 칠해진 칸 수가 다르면 검사 돌리지않고 바로 false 반환
	if (solverDrawing->GetAllSum() != drawing->GetAllSum())
		return false;
	else
	{
		auto sol = solverDrawing;

		// row 검사
		for (int i = 0; i < sol->GetRowCount(); i++)
		{
			// 완성 검사이므로, completeCheck의 값을 true로 넘김
			if (!CheckRow(solverDrawing, drawing, i, true))
				return false;
		}

		// col 검사
		for (int i = 0; i < sol->GetColCount(); i++)
		{
			// 완성 검사이므로, completeCheck의 값을 true로 넘김
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

	// solverDrawing의 rowIndex번째의 숫자 힌트를 만드는 작업
	for (int i = 0; i < sol->GetColCount(); i++)
	{
		int solValue = solverDrawing->GetValue(rowIndex, i);

		if (solValue == 1) 
			count++;
		else
		{
			if (count > 0)
			{
				solRow.push_back(count);
				count = 0;
			}
		}
	}

	if (count > 0) 
		solRow.push_back(count);

	// 완성 검사인지 확인 (true면 완성 검사, false면 현재까지 만들어진 줄이 힌트에 어긋나는지 확인)
	if (completeCheck)
	{
		if (solRow.empty()) 
			solRow.push_back(0);
		return solRow == answerRow;
	}
	else
	{
		// sol의 숫자 힌트가 answer보다 많거나 커지는 순간 즉시 false 반환
		if (solRow.size() > answerRow.size()) 
			return false;

		for (int i = 0; i < solRow.size(); i++)
		{
			if (solRow[i] > answerRow[i]) 
				return false;
		}

		if (solRow.size() <= answerRow.size())
		{
			// 남은 칸 수 세기
			int remain = 0;
			for (int i = 0; i < sol->GetColCount(); i++)
			{
				if (solverDrawing->GetValue(rowIndex, i) == 0)
					remain++;
			}

			// sol의 남은 칸 수가 answer를 채우기 위한 칸 수보다 적으면 false 반환
			int totalRemain = 0;
			for (int i = solRow.size(); i < answerRow.size(); i++)
				totalRemain += answerRow[i];

			totalRemain += (answerRow.size() - solRow.size() - 1);

			if (remain < totalRemain)
				return false;

			return true;
		}
	}
}

bool AutoSolver::CheckCol(Drawing* solverDrawing, Drawing* drawing, int colIndex, bool completeCheck)
{
	auto sol = solverDrawing;
	vector<int> answerCol = drawing->GetColList()[colIndex];
	vector<int> solCol;
	int count = 0;

	// solverDrawing의 colIndex번째의 숫자 힌트를 만드는 작업
	for (int i = 0; i < solverDrawing->GetRowCount(); i++)
	{
		int solValue = solverDrawing->GetValue(i, colIndex);

		if (solValue == 1)
			count++;
		else
		{
			if (count > 0)
			{
				solCol.push_back(count);
				count = 0;
			}
		}
	}

	if (count > 0)
		solCol.push_back(count);

	// 완성 검사인지 확인 (true면 완성 검사, false면 현재까지 만들어진 줄이 힌트에 어긋나는지 확인)
	if (completeCheck)
	{
		if (solCol.empty()) 
			solCol.push_back(0);
		return solCol == answerCol;
	}
	else
	{
		// sol의 숫자 힌트가 answer보다 많거나 커지는 순간 즉시 false 반환
		if (solCol.size() > answerCol.size())
			return false;

		for (int i = 0; i < solCol.size(); i++)
		{
			if (solCol[i] > answerCol[i]) 
				return false;
		}

		if (solCol.size() <= answerCol.size())
		{
			// 남은 칸 수 세기
			int remain = 0;
			for (int i = 0; i < solverDrawing->GetRowCount(); i++)
			{
				if (solverDrawing->GetValue(i, colIndex) == 0)
					remain++;
			}

			// sol의 남은 칸 수가 answer를 채우기 위한 칸 수보다 적으면 false 반환
			int totalRemain = 0;
			for (int i = solCol.size(); i < answerCol.size(); i++)
				totalRemain += answerCol[i];

			totalRemain += (answerCol.size() - solCol.size() - 1);

			if (remain < totalRemain)
				return false;

			return true;
		}
	}
}

void AutoSolver::GetHint(PlayScene* playScene, Drawing* drawing, int hintCount)
{
	// 힌트 잔여 횟수가 0이면 사용 불가
	if (hintCount <= 0)
	{
		cout << "\n힌트 사용 불가!\n";
		Sleep(1000);
		system("cls");
		return;
	}

	cout << "힌트 솔루션 제공중...\n";

	// CheckUniqueSolution()가 Solution() 호출하면서 solverDrawingList 생성됨
	if (CheckUniqueSolution(playScene, drawing) != 1)
	{
		cout << "\n해답이 유일하지 않습니다. 해당 그림은 힌트 기능이 제한됩니다.\n";
		Sleep(1000);
		system("cls");
		return;
	}

	vector<pair<int, int>> hintList;

	for (int i = 0; i < playScene->GetPlayerDrawing()->GetRowCount(); i++)
	{
		for (int j = 0; j < playScene->GetPlayerDrawing()->GetColCount(); j++)
		{
			// player와 drawing의 색칠 값이 다른 인덱스 저장
			if (!((playScene->GetPlayerDrawing()->GetValue(i, j) == 2 && drawing->GetValue(i, j) == 0) || (playScene->GetPlayerDrawing()->GetValue(i, j) == drawing->GetValue(i, j))))
				hintList.push_back({ i, j });
		}
	}

	pair<int, int> hint = hintList[rand() % hintList.size()];

	if (drawing->GetValue(hint.first, hint.second) == 1)
		playScene->GetPlayerDrawing()->SetValue(hint.first, hint.second, 1); // 색칠 칸일 경우
	else
		playScene->GetPlayerDrawing()->SetValue(hint.first, hint.second, 2); // X표시일 경우

	cout << "\n힌트 사용 완료!\n";
	Sleep(1000);
	system("cls");
}