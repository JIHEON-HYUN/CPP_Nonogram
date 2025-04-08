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
	static GameManager* gm; // 싱글톤 인스턴스

	GameManager();
	~GameManager();

	vector<Drawing*> drawingList;
	vector<PlayScene*> playScene;
	BoardViewer boardViewer;
	AutoSolver autoSolver;

public:
	static GameManager* GetGM(); // 싱글톤 인스턴스 접근에 사용
	static void DestroyGM(); // 싱글톤 인스턴스 메모리 해제

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

