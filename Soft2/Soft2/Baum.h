#pragma once
#include "MatrixCls.h"

using namespace std;

class Baum
{
public:
	string msWurzel;
	string msZweig;
	vector < Baum * > Kind;

	Baum * BaumErzeugen(Baum * baum, MatrixCls Remain_Matrix);
	void ZeichneBaum(Baum * tree, int Depth);


	Baum();
	~Baum();
};

