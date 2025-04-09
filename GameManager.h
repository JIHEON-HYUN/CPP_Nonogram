#pragma once
#include <vector>
#include "AutoSolver.h"
#include "BoardViewer.h"
#include "Drawing.h"
#include "PlayScene.h"

using namespace std;

class GameManager
{
private:
	static GameManager* gm; // �̱��� �ν��Ͻ�
	GameManager(); // �ܺο��� ������ ȣ�� �Ұ����ϰ� private �����
	~GameManager();

	vector<Drawing*> drawingList;
	vector<PlayScene*> playScene;
	vector<int> hintCountList;

public:
	AutoSolver autoSolver;
	BoardViewer boardViewer;
	static GameManager* GetGM(); // �̱��� �ν��Ͻ� ���ٿ� ���
	static void DestroyGM(); // �̱��� �ν��Ͻ� �޸� ����

	void ShowMenu();
	void ShowGameMenu();
	void ShowEditMenu();

	// GameMenu
	void GameStart(int index);

	// EditMenu
	void AddDrawing();
	void AddRandomDrawing();
	void RemoveDrawing();
};

