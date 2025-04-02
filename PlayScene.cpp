#include "PlayScene.h"
#include <iostream>
#include <conio.h>

PlayScene::PlayScene(Drawing* drawing)
{
	playerDrawing = new Drawing(*drawing);
}

PlayScene::~PlayScene()
{
	delete playerDrawing;
}

Drawing* PlayScene::GetPlayerDrawing()
{
	return playerDrawing;
}

bool PlayScene::PlayerDraw()
{
	cout << "\n\n �̵� : ȭ��ǥ";
	cout << "\n ��ĥ�ϱ� : z";
	cout << "\n Xǥ�� : x";
	cout << "\n �ʱ�ȭ : i (����! �����Ȳ �� ����)";
	cout << "\n �ڷΰ��� : Esc\n";

	char input;
	input = _getch();
	if (input == 224) // ����Ű�� ���
		input = _getch();

	switch (input)
	{
	case 72: // �� ����Ű
		if(playerDrawing->GetCurY() != 0)
			playerDrawing->SetCurY(playerDrawing->GetCurY() - 1);
		break;
	case 80: // �Ʒ� ����Ű
		if (playerDrawing->GetCurY() != playerDrawing->GetRowCount() - 1)
			playerDrawing->SetCurY(playerDrawing->GetCurY() + 1);
		break;
	case 75: // ���� ����Ű
		if (playerDrawing->GetCurX() != 0)
			playerDrawing->SetCurX(playerDrawing->GetCurX() - 1);
		break;
	case 77: // ������ ����Ű
		if (playerDrawing->GetCurX() != playerDrawing->GetColCount() - 1)
			playerDrawing->SetCurX(playerDrawing->GetCurX() + 1);
		break;
	case 'z': // ��ĥ�ϱ�
		if(playerDrawing->GetValue(playerDrawing->GetCurY(), playerDrawing->GetCurX()) == 1)
			playerDrawing->SetValue(playerDrawing->GetCurY(), playerDrawing->GetCurX(), 0); // �̹� ��ĥ������ �������� �����
		else
			playerDrawing->SetValue(playerDrawing->GetCurY(), playerDrawing->GetCurX(), 1);
		break;
	case 'x': // Xǥ���ϱ�
		if (playerDrawing->GetValue(playerDrawing->GetCurY(), playerDrawing->GetCurX()) == 2)
			playerDrawing->SetValue(playerDrawing->GetCurY(), playerDrawing->GetCurX(), 0); // �̹� Xǥ�� ������ �������� �����
		else
			playerDrawing->SetValue(playerDrawing->GetCurY(), playerDrawing->GetCurX(), 2);
		break;
	case 'i': // ���� ��Ȳ �ʱ�ȭ
		Init();
		break;
	case 27: // EscŰ �ڷΰ���
		return false;
		break;
	default:
		break;
	}

	return true;
}

void PlayScene::Init()
{
	// playerDrawing�� Drawing�� ��ġ�� �̿��� ������� ������
	// ��� ���� 0���� �ʱ�ȭ�Ͽ� �ʱ� ���� ����
	for (int i = 0; i < playerDrawing->GetRowCount(); i++)
	{
		for (int j = 0; j < playerDrawing->GetColCount(); j++)
		{
			playerDrawing->SetValue(i, j, 0);
		}
	}

	playerDrawing->SetCurX(0);
	playerDrawing->SetCurY(0);
}