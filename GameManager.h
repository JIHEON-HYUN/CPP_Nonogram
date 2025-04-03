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

	// GameMenu
	void GameStart(int index);
	bool CheckGameOver(int index);

	// EditMenu
	void AddDrawing();
	void AddRandomDrawing();
	void RemoveDrawing();
};

