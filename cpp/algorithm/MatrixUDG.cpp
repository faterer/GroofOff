/*
* MatrixUDG.cpp
*
*  Created on: Mar 9, 2015
*      Author: mawang
*/
#include <iostream>
#include <vector>

using namespace std;

#define MAX 100

class MatrixUDG
{
public:
	MatrixUDG(char vexs[], int vlen, char edges[][2], int elen);
	~MatrixUDG();
	void print();
private:
	char mVexs[MAX];
	int mVexNum;
	int mEdgNum;
	int mMatrix[MAX][MAX];
	int getPosition(char ch);
};

MatrixUDG::MatrixUDG(char vexs[], int vlen, char edges[][2], int elen)
{
	int i, j, p1, p2;

	mVexNum = vlen;
	mEdgNum = elen;

	for(i=0;i<mVexNum;i++) {
		mVexs[i] = vexs[i];
		for(j=0;j<mVexNum;j++)
			mMatrix[i][j] = 0;
	}

	for(i=0;i<mEdgNum;i++) {
		p1 = getPosition(edges[i][0]);
		p2 = getPosition(edges[i][1]);
		mMatrix[p1][p2] = 1;
		mMatrix[p2][p1] = 1;
	}
}

int MatrixUDG::getPosition(char ch)
{
	int i;
	for(i=0;i<mVexNum;i++)
		if(mVexs[i]==ch)
			return i;

	return -1;
}

void MatrixUDG::print()
{
	int i,j;
	cout << "Matrix Graph: " << endl;
	cout << "  ";
	for(i=0;i<mVexNum;i++)
		cout << mVexs[i] << " ";
	cout << endl;
	for(i=0;i<mVexNum;i++)
	{
		cout << mVexs[i] << " ";
		for(j=0;j<mVexNum;j++)
			cout << mMatrix[i][j] << " ";
		cout << endl;
	}
}

int main()
{
	char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
	char edges[][2] = {{'A', 'C'},{'A', 'D'},{'A', 'F'},
					   {'B', 'C'},{'C', 'D'},{'E', 'G'},
					   {'F', 'G'}};

	int vlen = sizeof(vexs)/sizeof(vexs[0]);
	int elen = sizeof(edges)/sizeof(edges[0]);
	MatrixUDG *pG = new MatrixUDG(vexs, vlen, edges, elen);
	pG->print();
	return 0;

}
