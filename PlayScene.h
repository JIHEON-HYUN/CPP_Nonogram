#pragma once
#include <vector>
#include <string>
#include "Drawing.h"

using namespace std;
class Drawing;

class PlayScene
{
private:
	// Player의 입력을 받아 그려지는 Drawing
	Drawing* playerDrawing;

public:
	// GameManager에서 정답 Drawing 객체를 인자로 전달
	// 정답 Drawing 객체와 연속된 색칠 칸의 숫자 배치가 같아야되므로 복사 생성
	PlayScene(Drawing* drawing);
	~PlayScene();

	Drawing* GetPlayerDrawing();

	int PlayerDraw(); // 게임 지속여부를 확인하기 위해 bool값을 return
	void Init();
};

