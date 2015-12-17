#pragma once
#include "MatrixCls.h"

using namespace std;

class Baum
{
public:
	string msWurzel;
	string msZweig;
	vector < Baum * > Kind;

	Baum * BuildTree(Baum * baum, MatrixCls Remain_Matrix);
	void PrintTree(Baum * tree, int Depth);


	Baum();
	~Baum();
};

