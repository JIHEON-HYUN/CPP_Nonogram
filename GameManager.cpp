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

	playScene[0]->Init();
	playScene[1]->Init();
	playScene[2]->Init();
	playScene[3]->Init();
	playScene[4]->Init();
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
	ShowGameMenu();
}

void GameManager::ShowGameMenu()
{
	char input;
	int index = 0;

	while (1)
	{
		system("cls");

		boardViewer.Render(playScene[index]->GetPlayerDrawing());
		cout << "�׸��̵� : ��/�� ȭ��ǥ\n";
		cout << "���� : z\n";
		cout << "�ڷΰ��� : Esc\n";

		input = _getch();

		switch (input)
		{
		case 75: // ���� ����Ű
			if (index > 0)
				index--;
			break;
		case 77: // ������ ����Ű
			if (index < playScene.size() - 1)
				index++;
			break;
		case 'z': // �׸� ����
			system("cls");
			GameStart(index); // ������ �׸����� ���� ����
			break;
		case 27: // EscŰ �ڷΰ���
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
	while (1)
	{
		// PlayerDraw()���� �ڷΰ��⸦ �������� Ȯ���ϴ� ����
		bool checkContinue = false;
		
		if (CheckGameOver(index))
		{
			checkContinue = playScene[index]->PlayerDraw();
		}

		// �÷��̾ �׸� �׸��� ������ ������ �ݺ�
		while (!CheckGameOver(index))
		{
			boardViewer.Render(playScene[index]->GetPlayerDrawing());
			checkContinue = playScene[index]->PlayerDraw();

			if (!checkContinue)
				break;
		}

		// �׸��� �ϼ��Ǹ� ���� Ŀ����ġ�� �׸� ���� ������ ���� �ϼ����� ���
		if (checkContinue)
		{
			system("cls");
			playScene[index]->GetPlayerDrawing()->SetCurX(playScene[index]->GetPlayerDrawing()->GetColCount());
			boardViewer.Render(playScene[index]->GetPlayerDrawing());
			cout << "�׸��� �ϼ��Ǿ����ϴ�. �����մϴ�!\n";
			Sleep(2000);

			playScene[index]->GetPlayerDrawing()->SetCurX(0);
			playScene[index]->GetPlayerDrawing()->SetCurY(0);
			break;
		}
	}
	
}

void GameManager::AddDrawing()
{
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
	// �� ĥ���� ĭ ���� �ٸ��� �˻� �������ʰ� �ٷ� false ��ȯ
	if (playScene[index]->GetPlayerDrawing()->GetValueSum() != drawingList[index]->GetValueSum())
	{
		return false;
	}
	else
	{
		auto player = playScene[index]->GetPlayerDrawing();

		// row �˻�
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

		// col �˻�
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
