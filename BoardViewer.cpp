#include "BoardViewer.h"
#include <iostream>
#include <windows.h>

BoardViewer::BoardViewer()
{
}

BoardViewer::~BoardViewer()
{
}


void BoardViewer::Render(Drawing* drawing)
{
	COORD pos = { (SHORT)0, (SHORT)0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

	auto rowList = drawing->GetRowList();
	auto colList = drawing->GetColList();
	int maxRowCount = 0;
	int maxColCount = 0;

	// rowList 요소 중에 최장 길이 값 구하기
	for (auto row : rowList)
	{
		if (row.size() > maxRowCount)
			maxRowCount = row.size();
	}

	// colList 요소 중에 최장 길이 값 구하기
	for (auto col : colList)
	{
		if (col.size() > maxColCount)
			maxColCount = col.size();
	}

	// colList 출력
	for (int i = 0; i < maxColCount; i++)
	{
		for (int j = 0; j < maxRowCount; j++)
		{
			// 공백은 검은색으로 해서 콘솔창에 가려지게
			// "■"의 크기는 "  "(띄어쓰기 2칸)과 같으므로, 2자릿수까지는 격자 깨짐 방지
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
			cout << "■";
		}

		for (int j = 0; j < drawing->GetColCount(); j++)
		{
			// 해당 격자에 숫자가 없을 경우 공백(검은색) 출력
			if (colList[j].size() < maxColCount - i)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
				cout << "■";
			}
			// 해당 격자에 숫자가 있을 경우 숫자(회색) 출력
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				if(colList[j][colList[j].size() - maxColCount + i] >= 10)
					cout << colList[j][colList[j].size() - maxColCount + i];
				else
					cout << colList[j][colList[j].size() - maxColCount + i] << " ";
			}
		}

		cout << "\n";
	}

	for (int i = 0; i < drawing->GetRowCount(); i++)
	{
		// rowList 출력
		for (int j = 0; j < maxRowCount; j++)
		{
			// 해당 격자에 숫자가 없을 경우 공백(검은색) 출력
			if (rowList[i].size() < maxRowCount - j)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
				cout << "■";
			}
			// 해당 격자에 숫자가 있을 경우 숫자(회색) 출력
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				if(rowList[i][rowList[i].size() - maxRowCount + j] >= 10)
					cout << rowList[i][rowList[i].size() - maxRowCount + j];
				else
					cout << " " << rowList[i][rowList[i].size() - maxRowCount + j];
			}
		}

		// 그림 보드판 출력
		for (int j = 0; j < drawing->GetColCount(); j++)
		{
			switch (drawing->GetValue(i, j))
			{
			case 0:
				if(drawing->GetCurX() == j  && drawing->GetCurY() == i)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); // 현재 커서일 경우 노란색
				else
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 빈 칸 : 하얀색
				cout << "□";
				break;
			case 1:
				if (drawing->GetCurX() == j && drawing->GetCurY() == i)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); // 현재 커서일 경우 노란색
				else
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // 색칠 : 초록색
				cout << "■";
				break;
			case 2:
				
				if (drawing->GetCurX() == j && drawing->GetCurY() == i)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); // 현재 커서일 경우 노란색
				else
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // X : 빨간색
				cout << "■";
				break;
			default:
				break;
			}
		}

		cout << "\n";
	}

	cout << "\n";

	// 모든 요소 출력 후, 다시 흰색으로 색 변경
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
