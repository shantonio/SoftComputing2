#pragma once
#include "MatrixCls.h"
#include "Baum.h"





vector < string > GetUniqueScores(vector < string > Scores);
double BerechneEntropy(vector < string > Scores);
double BerechneAttributEntropy(MatrixCls Remain_Matrix, string The_Attribute);
double BerechneAttributEntropyGain(MatrixCls Remain_Matrix, string The_Attribute);
double GainRatio(MatrixCls Remain_Matrix, string The_Attribute);

Baum * BaumErzeugen(Baum * baum, MatrixCls Remain_Matrix);
void ZeichneBaum(Baum * tree, int Depth);