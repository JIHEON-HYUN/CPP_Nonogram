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
	GameManager(); // 외부에서 생성자 호출 불가능하게 private 멤버로
	~GameManager();

	vector<Drawing*> drawingList;
	vector<PlayScene*> playScene;
	vector<int> hintCountList;

public:
	AutoSolver autoSolver;
	BoardViewer boardViewer;
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

