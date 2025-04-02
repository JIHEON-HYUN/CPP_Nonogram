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
	cout << "\n\n 이동 : 화살표";
	cout << "\n 색칠하기 : z";
	cout << "\n X표시 : x";
	cout << "\n 초기화 : i (주의! 진행상황 다 날라감)";
	cout << "\n 뒤로가기 : Esc\n";

	char input;
	input = _getch();
	if (input == 224) // 방향키일 경우
		input = _getch();

	switch (input)
	{
	case 72: // 위 방향키
		if(playerDrawing->GetCurY() != 0)
			playerDrawing->SetCurY(playerDrawing->GetCurY() - 1);
		break;
	case 80: // 아래 방향키
		if (playerDrawing->GetCurY() != playerDrawing->GetRowCount() - 1)
			playerDrawing->SetCurY(playerDrawing->GetCurY() + 1);
		break;
	case 75: // 왼쪽 방향키
		if (playerDrawing->GetCurX() != 0)
			playerDrawing->SetCurX(playerDrawing->GetCurX() - 1);
		break;
	case 77: // 오른쪽 방향키
		if (playerDrawing->GetCurX() != playerDrawing->GetColCount() - 1)
			playerDrawing->SetCurX(playerDrawing->GetCurX() + 1);
		break;
	case 'z': // 색칠하기
		if(playerDrawing->GetValue(playerDrawing->GetCurY(), playerDrawing->GetCurX()) == 1)
			playerDrawing->SetValue(playerDrawing->GetCurY(), playerDrawing->GetCurX(), 0); // 이미 색칠됐으면 공백으로 만들기
		else
			playerDrawing->SetValue(playerDrawing->GetCurY(), playerDrawing->GetCurX(), 1);
		break;
	case 'x': // X표시하기
		if (playerDrawing->GetValue(playerDrawing->GetCurY(), playerDrawing->GetCurX()) == 2)
			playerDrawing->SetValue(playerDrawing->GetCurY(), playerDrawing->GetCurX(), 0); // 이미 X표시 됐으면 공백으로 만들기
		else
			playerDrawing->SetValue(playerDrawing->GetCurY(), playerDrawing->GetCurX(), 2);
		break;
	case 'i': // 진행 상황 초기화
		Init();
		break;
	case 27: // Esc키 뒤로가기
		return false;
		break;
	default:
		break;
	}

	return true;
}

void PlayScene::Init()
{
	// playerDrawing은 Drawing의 배치를 이용해 만들었기 때문에
	// 모든 값을 0으로 초기화하여 초기 상태 만듦
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