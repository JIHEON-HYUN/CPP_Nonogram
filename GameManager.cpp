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
	// PlayerDraw()���� �ڷΰ��⸦ �������� Ȯ���ϴ� ����
	bool checkContinue = false;

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

		// �ϼ� �޼��� ���� �ش� �׸� �ʱ�ȭ
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
		if (input == 224) // ����Ű�� ���
			input = _getch();

		switch (input)
		{
		case 72: // �� ����Ű
			if (newDrawing->GetCurY() > 0)
				newDrawing->SetCurY(newDrawing->GetCurY() - 1);
			break;
		case 80: // �Ʒ� ����Ű
			if (newDrawing->GetCurY() < height - 1)
				newDrawing->SetCurY(newDrawing->GetCurY() + 1);
			break;
		case 75: // ���� ����Ű
			if (newDrawing->GetCurX() > 0)
				newDrawing->SetCurX(newDrawing->GetCurX() - 1);
			break;
		case 77: // ������ ����Ű
			if (newDrawing->GetCurX() < width - 1)
				newDrawing->SetCurX(newDrawing->GetCurX() + 1);
			break;
		case 'z': // ��ĥ�ϱ�
			if (newDrawing->GetValue(newDrawing->GetCurY(), newDrawing->GetCurX()) == 0)
				newDrawing->SetValue(newDrawing->GetCurY(), newDrawing->GetCurX(), 1);
			else
				newDrawing->SetValue(newDrawing->GetCurY(), newDrawing->GetCurX(), 0);
			break;
		case 'i': // �ٽ� �׸���
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					newDrawing->SetValue(i, j, 0);
				}
			}
			break;
		case 27: // EscŰ �ڷΰ���
			return;
			break;
		default:
			break;
		}

		newRowList.resize(newDrawing->GetColCount());
		newColList.resize(newDrawing->GetRowCount());
		int count; // �����ؼ� ��ĥ������ ���� �� �����ϴ� ����

		// newBoard�� �� row�� �����ؼ� ��ĥ������ ���� ���� ����
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

		// newBoard�� �� col�� �����ؼ� ��ĥ������ ���� ���� ����
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
