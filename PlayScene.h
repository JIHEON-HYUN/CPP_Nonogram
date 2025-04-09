#pragma once
#include <vector>
#include <string>
#include "Drawing.h"

using namespace std;
class Drawing;

class PlayScene
{
private:
	// Player�� �Է��� �޾� �׷����� Drawing
	Drawing* playerDrawing;

public:
	// GameManager���� ���� Drawing ��ü�� ���ڷ� ����
	// ���� Drawing ��ü�� ���ӵ� ��ĥ ĭ�� ���� ��ġ�� ���ƾߵǹǷ� ���� ����
	PlayScene(Drawing* drawing);
	~PlayScene();

	Drawing* GetPlayerDrawing();

	int PlayerDraw(); // ���� ���ӿ��θ� Ȯ���ϱ� ���� bool���� return
	void Init();
};

