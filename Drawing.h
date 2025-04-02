#pragma once
#include <vector>
#include "PlayScene.h"

using namespace std;

class Drawing
{
private:
	// 이 그림 객체의 색칠 배열이 저장된 2차원벡터
	// drawing[행][열], 빈 칸이면 값이 0, 색칠(초록)됐으면 값이 1, X(빨강)표시는 2
	vector<vector<int>> drawing; 

	// 각 행마다 연속된 색칠(초록)칸이 몇개인지 저장된 2차원 벡터
	vector<vector<int>> rowList; 

	// 각 열마다 연속된 색칠(초록)칸이 몇개인지 저장된 2차원 벡터
	vector<vector<int>> colList; 

	int curX; // 현재 커서 위치 출력을 위한 X좌표 변수
	int curY; // 현재 커서 위치 출력을 위한 Y좌표 변수

public:
	// 입력받은 그림으로 Drawing 객체 생성
	Drawing(vector<vector<int>> inputDrawing); 

	// 입력받은 가로, 세로 길이로 랜덤한 배치의 Drawing 객체 생성
	Drawing(int width, int height); 

	// 복사생성자 => PlayScene의 playerDrawing을 생성하는 데 사용
	// PlayScene에서 값을 변경할 때, 정답 Drawing의 원본데이터는 변경하면 안되므로, 깊은 복사로 진행
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

	int GetValue(int index1, int index2); // drawing[index1][index2]에 저장된 value return
	int GetValueSum();
	void SetValue(int index1, int index2, int value); // drawing[index1][index2]의 값을 value값으로 변경
};

