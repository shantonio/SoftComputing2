#include "Algorithmus.h"


Baum * Baum::BaumErzeugen(Baum * tree, MatrixCls Remain_Matrix)
{
	if (tree == NULL)
	{
		tree = new Baum();
	}

	vector < string > Unique_Scores = GetUniqueScores(Remain_Matrix.GetScores());
	if (Unique_Scores.size() == 1)
	{
		tree->msWurzel = Unique_Scores[0];
		return tree;
	}


	double Max_GainRatio = 0., Temp_GainRatio;
	int j;
	string Max_Attribute;
	vector < string > Attributes = Remain_Matrix.GetAttributes();
	for (j = 0; j < Attributes.size(); j++)
	{
		Temp_GainRatio = GainRatio(Remain_Matrix, Attributes[j]);
		if ((Temp_GainRatio - Max_GainRatio) > 1.e-8)
		{
			Max_GainRatio = Temp_GainRatio;
			Max_Attribute = Attributes[j];
		}
	}

	tree->msWurzel = Max_Attribute;
	vector < string > Values = Remain_Matrix.GetAttributeValues(Max_Attribute);
	int i, k;
	MatrixCls New_Matrix;
	for (k = 0; k < Values.size(); k++)
	{
		New_Matrix = New_Matrix.operator()(Remain_Matrix, Max_Attribute, Values[k]);
		Baum * Neuer_baum = new Baum();
		Neuer_baum->msZweig = Values[k];
		if (New_Matrix.SizeX() != 1)
			BaumErzeugen(Neuer_baum, New_Matrix);		//Rekursive Aufruf

		tree->Kind.push_back(Neuer_baum);
	}

	return tree;
}
void Baum::ZeichneBaum(Baum * baum, int Tiefe = -1)
{
	for (int i = 0; i < Tiefe; i++) cout << "\t";
	if (baum->msZweig.compare("") != 0)
	{
		cout << baum->msZweig << endl;
		for (int i = 0; i < Tiefe + 1; i++) cout << "\t";
	}
	if (Tiefe == -1 & baum->msZweig.compare("") != 0)
	{
		cout << "\t";
	}
	cout << baum->msWurzel << endl;
	for (int i = 0; i < baum->Kind.size(); i++)
	{
		ZeichneBaum(baum->Kind[i], Tiefe + 1);  //Rekursive Aufruf
	}
}



int main()
{
	MatrixCls Matrix;
	Matrix.CSVDateiLesen("Train.csv");
	//Matrix.CSVDateiLesen("TrainGross.csv");
	Baum * baum = new Baum();
	baum = baum->BaumErzeugen(baum, Matrix);
	baum->ZeichneBaum(baum);

	cout << endl;
	delete baum;
}
