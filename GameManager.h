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
	vector<Drawing*> drawingList;
	vector<PlayScene*> playScene;
	BoardViewer boardViewer;
	AutoSolver autoSolver;

public:
	GameManager();
	~GameManager();
	void ShowMenu();
	void ShowGameMenu();
	void ShowEditMenu();
	void GameStart(int index); // index��° playScene�� ���ӽ���
	void AddDrawing(int width, int height);
	void AddRandomDrawing(int width, int height);
	void RemoveDrawing();
	bool CheckGameOver(int index);
};

