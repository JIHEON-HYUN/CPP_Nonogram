#pragma once
#include <vector>
#include "PlayScene.h"

using namespace std;

class Drawing
{
private:
	// �� �׸� ��ü�� ��ĥ �迭 ����
	// drawing[��][��], �� ĭ�̸� ���� 0, ��ĥ(�ʷ�)������ ���� 1, X(����)ǥ�ô� 2
	vector<vector<int>> drawing; 

	// Row�� ���� ��Ʈ ����
	vector<vector<int>> rowList; 

	// Col�� ���� ��Ʈ ����
	vector<vector<int>> colList; 

	int curX; // ���� Ŀ�� X��ǥ
	int curY; // ���� Ŀ�� Y��ǥ

public:
	// ���ڷ� ���޹��� �׸����� Drawing ��ü ����
	Drawing(vector<vector<int>> inputDrawing); 

	// ���ڷ� ���޹��� ����, ���� ���̷� ������ ��ġ�� Drawing ��ü ����
	Drawing(int width, int height); 

	// ��������� => PlayScene�� playerDrawing�� �����ϴ� �� ���
	// ���� Drawing�� ���������ʹ� �����ϸ� �ȵǹǷ�, ���� ����� ����
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

	void SetValue(int index1, int index2, int value); // drawing[index1][index2]�� ���� value������ ����
	int GetValue(int index1, int index2); // drawing[index1][index2]�� ����� value return
	int GetRowSum(int index);
	int GetColSum(int index);
	int GetAllSum();
	
};

