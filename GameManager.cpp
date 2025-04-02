#include "GameManager.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

GameManager::GameManager()
{
	vector<vector<int>> exam1 =
	{
		{0,0,0,0,1,0,0,0,0,0},
		{0,0,0,1,1,1,0,0,0,0},
		{0,0,1,0,1,1,0,0,0,0},
		{0,1,0,0,1,1,1,0,0,0},
		{0,1,0,0,1,1,1,0,0,0},
		{0,1,1,0,1,1,1,1,0,0},
		{0,0,1,1,1,1,1,1,0,0},
		{0,0,0,0,1,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1},
		{0,1,1,1,1,1,1,1,1,0}
	};

	vector<vector<int>> exam2 =
	{
		{0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{0,0,0,1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1},
		{0,0,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1},
		{0,0,1,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1},
		{0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1},
		{1,1,1,1,0,0,1,1,1,1,1,0,0,0,1,1,0,0,1,1,1},
		{1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1},
		{1,1,0,1,0,0,1,0,1,1,1,1,1,1,0,1,0,0,1,0,1},
		{0,1,0,1,0,1,1,0,1,1,1,1,1,1,0,1,0,1,1,0,1},
		{0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0}
	};

	vector<vector<int>> exam3 =
	{
		{0,0,0,0,0,1,0,0,0,0},
		{0,0,1,0,1,0,1,0,1,0},
		{0,1,0,1,0,1,0,1,0,1},
		{0,1,1,1,0,0,0,1,1,1},
		{0,0,1,0,1,1,1,1,1,0},
		{0,0,1,1,1,1,1,1,1,0},
		{0,0,0,1,1,1,1,1,0,0},
		{0,0,0,0,1,1,1,0,0,0},
		{1,1,0,0,1,1,1,0,0,0},
		{1,1,1,0,0,1,0,0,0,1},
		{0,1,1,1,0,1,0,0,1,1},
		{0,0,0,0,1,1,0,1,1,1},
		{0,0,0,0,0,1,1,1,1,0},
		{0,0,0,0,0,1,0,0,0,0},
		{0,0,0,0,0,1,0,0,0,0}
	};

	vector<vector<int>> exam4 =
	{
		{0,0,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,1,1,1,1,1,1,1,1},
		{0,1,1,1,1,1,1,1,1,0},
		{0,0,0,0,1,1,1,1,0,0}
	};

	vector<vector<int>> exam5 =
	{
		{1,1,1},
		{1,1,1},
		{1,1,0}
	};

	vector<vector<int>> exam6 =
	{
		{1,1,1},
		{0,0,0},
		{1,1,0}
	};

	drawingList.push_back(new Drawing(exam1));
	playScene.push_back(new PlayScene(drawingList[0]));
	drawingList.push_back(new Drawing(exam2));
	playScene.push_back(new PlayScene(drawingList[1]));
	drawingList.push_back(new Drawing(exam3));
	playScene.push_back(new PlayScene(drawingList[2]));
	drawingList.push_back(new Drawing(exam4));
	playScene.push_back(new PlayScene(drawingList[3]));
	drawingList.push_back(new Drawing(exam5));
	playScene.push_back(new PlayScene(drawingList[4]));
	drawingList.push_back(new Drawing(exam6));
	playScene.push_back(new PlayScene(drawingList[5]));
	drawingList.push_back(new Drawing(3, 10));
	playScene.push_back(new PlayScene(drawingList[6]));

	playScene[0]->Init();
	playScene[1]->Init();
	playScene[2]->Init();
	playScene[3]->Init();
	playScene[4]->Init();
	playScene[5]->Init();
	playScene[6]->Init();
}

GameManager::~GameManager()
{
	for (int i = 0; i < drawingList.size(); i++)
		delete drawingList[i];

	for (int i = 0; i < playScene.size(); i++)
		delete playScene[i];
}	

void GameManager::ShowMenu()
{
	AddDrawing(3, 4);
}

void GameManager::ShowGameMenu()
{
	char input;
	int index = 0;

	while (1)
	{
		system("cls");

		boardViewer.Render(playScene[index]->GetPlayerDrawing());
		cout << "그림이동 : 좌/우 화살표\n";
		cout << "선택 : z\n";
		cout << "뒤로가기 : Esc\n";

		input = _getch();

		switch (input)
		{
		case 75: // 왼쪽 방향키
			if (index > 0)
				index--;
			break;
		case 77: // 오른쪽 방향키
			if (index < playScene.size() - 1)
				index++;
			break;
		case 'z': // 그림 선택
			system("cls");
			GameStart(index); // 선택한 그림으로 게임 시작
			break;
		case 27: // Esc키 뒤로가기
			return;
			break;
		default:
			break;
		}
	}
}

void GameManager::ShowEditMenu()
{
}

void GameManager::GameStart(int index)
{
	// PlayerDraw()에서 뒤로가기를 눌렀는지 확인하는 변수
	bool checkContinue = false;

	// 플레이어가 그린 그림이 정답일 때까지 반복
	while (!CheckGameOver(index))
	{
		boardViewer.Render(playScene[index]->GetPlayerDrawing());
		checkContinue = playScene[index]->PlayerDraw();

		if (!checkContinue)
			break;
	}

	// 그림이 완성되면 현재 커서위치를 그림 격자 밖으로 빼서 완성본을 출력
	if (checkContinue)
	{
		system("cls");
		playScene[index]->GetPlayerDrawing()->SetCurX(playScene[index]->GetPlayerDrawing()->GetColCount());
		boardViewer.Render(playScene[index]->GetPlayerDrawing());
		cout << "그림이 완성되었습니다. 축하합니다!\n";
		Sleep(2000);

		// 완성 메세지 이후 해당 그림 초기화
		playScene[index]->Init();
	}
}

void GameManager::AddDrawing(int width, int height)
{
	vector<vector<int>> newBoard(height, vector<int>(width, 0));
	vector<vector<int>> newRowList;
	vector<vector<int>> newColList;
	Drawing* newDrawing = new Drawing(newBoard);
	char input;

	while (1)
	{
		COORD pos = { (SHORT)0, (SHORT)0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

		boardViewer.Render(newDrawing);

		input = _getch();
		if (input == 224) // 방향키일 경우
			input = _getch();

		switch (input)
		{
		case 72: // 위 방향키
			if (newDrawing->GetCurY() > 0)
				newDrawing->SetCurY(newDrawing->GetCurY() - 1);
			break;
		case 80: // 아래 방향키
			if (newDrawing->GetCurY() < height - 1)
				newDrawing->SetCurY(newDrawing->GetCurY() + 1);
			break;
		case 75: // 왼쪽 방향키
			if (newDrawing->GetCurX() > 0)
				newDrawing->SetCurX(newDrawing->GetCurX() - 1);
			break;
		case 77: // 오른쪽 방향키
			if (newDrawing->GetCurX() < width - 1)
				newDrawing->SetCurX(newDrawing->GetCurX() + 1);
			break;
		case 'z': // 색칠하기
			if (newDrawing->GetValue(newDrawing->GetCurY(), newDrawing->GetCurX()) == 0)
				newDrawing->SetValue(newDrawing->GetCurY(), newDrawing->GetCurX(), 1);
			else
				newDrawing->SetValue(newDrawing->GetCurY(), newDrawing->GetCurX(), 0);
			break;
		case 'i': // 다시 그리기
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					newDrawing->SetValue(i, j, 0);
				}
			}
			break;
		case 27: // Esc키 뒤로가기
			return;
			break;
		default:
			break;
		}

		newRowList.resize(newDrawing->GetColCount());
		newColList.resize(newDrawing->GetRowCount());
		int count; // 연속해서 색칠해지는 숫자 값 저장하는 변수

		// newBoard의 각 row별 연속해서 색칠해지는 숫자 값들 저장
		for (int i = 0; i < newRowList.size(); i++)
		{
			count = 0;

			for (int j = 0; j < newBoard[0].size(); j++)
			{
				if (newBoard[i][j] == 1)
					count++;
				else
				{
					if (count != 0)
					{
						newRowList[i].push_back(count);
						count = 0;
					}
				}
			}

			if (count != 0)
				newRowList[i].push_back(count);

			if (newRowList[i].empty())
				newRowList[i].push_back(0);
		}

		// newBoard의 각 col별 연속해서 색칠해지는 숫자 값들 저장
		for (int i = 0; i < newColList.size(); i++)
		{
			count = 0;

			for (int j = 0; j < newBoard.size(); j++)
			{
				if (newBoard[j][i] == 1)
					count++;
				else
				{
					if (count != 0)
					{
						newColList[i].push_back(count);
						count = 0;
					}
				}
			}

			if (count != 0)
				newColList[i].push_back(count);

			if (newColList[i].empty())
				newColList[i].push_back(0);
		}

		newDrawing->SetRowList(newRowList);
		newDrawing->SetColList(newColList);
	}

}

void GameManager::AddRandomDrawing(int width, int height)
{
	Drawing* newDrawing = new Drawing(width,height);
	drawingList.push_back(newDrawing);
}

void GameManager::RemoveDrawing()
{
}

bool GameManager::CheckGameOver(int index)
{
	// 총 칠해진 칸 수가 다르면 검사 돌리지않고 바로 false 반환
	if (playScene[index]->GetPlayerDrawing()->GetValueSum() != drawingList[index]->GetValueSum())
	{
		return false;
	}
	else
	{
		auto player = playScene[index]->GetPlayerDrawing();

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
