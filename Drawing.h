#pragma once
#include <vector>
#include "PlayScene.h"

using namespace std;

class Drawing
{
private:
	// 이 그림 객체의 색칠 배열 저장
	// drawing[행][열], 빈 칸이면 값이 0, 색칠(초록)됐으면 값이 1, X(빨강)표시는 2
	vector<vector<int>> drawing; 

	// Row의 숫자 힌트 저장
	vector<vector<int>> rowList; 

	// Col의 숫자 힌트 저장
	vector<vector<int>> colList; 

	int curX; // 현재 커서 X좌표
	int curY; // 현재 커서 Y좌표

public:
	// 인자로 전달받은 그림으로 Drawing 객체 생성
	Drawing(vector<vector<int>> inputDrawing); 

	// 인자로 전달받은 가로, 세로 길이로 랜덤한 배치의 Drawing 객체 생성
	Drawing(int width, int height); 

	// 복사생성자 => PlayScene의 playerDrawing을 생성하는 데 사용
	// 정답 Drawing의 원본데이터는 변경하면 안되므로, 깊은 복사로 진행
	Drawing(const Drawing& drawing); 
	~Drawing();

	vector<vector<int>> GetRowList();
	vector<vector<int>> GetColList();
	void SetRowList(vector<vector<int>> newRowList);
	void SetColList(vector<vector<int>> newColList);

	int GetRowCount();
	int GetColCount();

	int GetCurX();
	int GetCurY();
	void SetCurX(int newCurX);
	void SetCurY(int newCurY);

	void SetValue(int index1, int index2, int value); // drawing[index1][index2]의 값을 value값으로 변경
	int GetValue(int index1, int index2); // drawing[index1][index2]에 저장된 value return
	int GetRowSum(int index);
	int GetColSum(int index);
	int GetAllSum();
	
};

