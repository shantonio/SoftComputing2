#include "MatrixCls.h"
#include "Baum.h"



vector < string > GetUniqueScores(vector < string > Scores)
{
	sort(Scores.begin(), Scores.end());
	Scores.erase(unique(Scores.begin(), Scores.end()), Scores.end());
	return Scores;
}

string GetFrequentScore(vector < string > Scores)
{
	vector < string > Unique_Scores = GetUniqueScores(Scores);
	int Count[20] = { 0 };     
	for (int i = 0; i < Scores.size(); i++)
	{
		for (int k = 0; k < Unique_Scores.size(); k++)
		{
			if (Scores[i].compare(Unique_Scores[k]) == 0)
			{
				Count[k] = Count[k] + 1;
			}
		}
	}

	int Max_Index = 0;
	for (int k = 0; k < Unique_Scores.size(); k++)
	{
		if (Count[k] > Max_Index)
		{
			Max_Index = Count[k];
		}
	}

	return Unique_Scores[Max_Index];
}

double BerechneEntropy(vector < string > Scores)
{
	vector < string > Score_Range = GetUniqueScores(Scores);
	if (Score_Range.size() == 0)
	{
		return 0.;
	}
	else
	{
		double TheEntropy = 0.;
		int i, j;
		int Count[20] = { 0 };

		for (i = 0; i < Scores.size(); i++)
		{
			for (j = 0; j < Score_Range.size(); j++)
			{
				if (Scores[i].compare(Score_Range[j]) == 0)
				{
					Count[j] = Count[j] + 1;
				}
			}
		}

		double Temp_Entropy;
		double Temp_P;
		for (j = 0; j < Score_Range.size(); j++)
		{
			if (Count[j] == 0)
			{
				Temp_Entropy = 0.;
			}
			else {
				Temp_P = (double)Count[j] / (double)(Scores.size());
				Temp_Entropy = -Temp_P*log(Temp_P) / log(2.);
			}
			TheEntropy = TheEntropy + Temp_Entropy;
		}
		return TheEntropy;
	}
}




double BerechneAttributEntropy(MatrixCls Remain_Matrix, string The_Attribute)
{
	vector < string > Values = Remain_Matrix.GetAttributeValues(The_Attribute);
	return BerechneEntropy(Values);
}


double BerechneAttributEntropyGain(MatrixCls Remain_Matrix, string The_Attribute)
{
	double Original_Entropy = 0., Gained_Entropy = 0.;
	vector < string > Scores = Remain_Matrix.GetScores();
	map < string, vector < string > > Values_Scores = Remain_Matrix.GetAttributeValuesScores(The_Attribute);
	Original_Entropy = BerechneEntropy(Scores);
	vector < string > Attribute_Values = Remain_Matrix.GetAttributeValues(The_Attribute);

	double After_Entropy = 0.;
	double Temp_Entropy;
	vector < string > Temp_Scores;
	int i, j;
	for (i = 0; i < Attribute_Values.size(); i++)
	{
		Temp_Scores = Values_Scores[Attribute_Values[i]];
		Temp_Entropy = BerechneEntropy(Temp_Scores)*(double)Temp_Scores.size() / (double)Scores.size();
		After_Entropy = After_Entropy + Temp_Entropy;
	}
	Gained_Entropy = Original_Entropy - After_Entropy;
	return Gained_Entropy;
}

double GainRatio(MatrixCls Remain_Matrix, string The_Attribute)
{
	double Attribute_Entropy_SplitInfo = BerechneAttributEntropy(Remain_Matrix, The_Attribute);
	double Attribute_Entropy_Gain = BerechneAttributEntropyGain(Remain_Matrix, The_Attribute);
	return Attribute_Entropy_Gain / Attribute_Entropy_SplitInfo;
}





Baum * Baum::BuildTree(Baum * tree, MatrixCls Remain_Matrix)
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

	if (Remain_Matrix.SizeX() == 1)
	{
		string Frequent_Score = GetFrequentScore(Remain_Matrix.GetScores());
		tree->msWurzel = Frequent_Score;
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
		if (New_Matrix.SizeX() == 1)
		{
			Neuer_baum->msWurzel = GetFrequentScore(New_Matrix.GetScores());
		}
		else
		{
			BuildTree(Neuer_baum, New_Matrix); //Rekursive Aufruf
		}
		tree->Kind.push_back(Neuer_baum);
	}

	return tree;
}

void Baum::PrintTree(Baum * tree, int Depth = -1)
{
	for (int i = 0; i < Depth; i++) cout << "\t";
	if (tree->msZweig.compare("") != 0)
	{
		cout << tree->msZweig << endl;
		for (int i = 0; i < Depth + 1; i++) cout << "\t";
	}
	if (Depth == -1 & tree->msZweig.compare("") != 0)
	{
		cout << "\t";
	}
	cout << tree->msWurzel << endl;
	for (int i = 0; i < tree->Kind.size(); i++)
	{
		PrintTree(tree->Kind[i], Depth + 1);
	}
}



int main()
{
	MatrixCls Matrix("Train.csv");
	Baum * root = new Baum();
	root = root->BuildTree(root, Matrix);
	root->PrintTree(root);

	cout << endl;
	delete root;
}
