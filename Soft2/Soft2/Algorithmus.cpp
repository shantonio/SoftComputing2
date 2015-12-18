#include "Algorithmus.h"





/*
"GetUniqueScores" geht durch alle Attrubut-Werten und sortiert nach Einzigartigkeit  und gibt die sortierte zurück
Algorithmus ist aus der Bibliothek <algorithm> 
Beispiel input :
10 12 34 65 12 10 65

Beispiel output :
10 2
12 2
34 1
65 2
*/
vector < string > GetUniqueScores(vector < string > Scores)
{	
	sort(Scores.begin(), Scores.end());
	Scores.erase(unique(Scores.begin(), Scores.end()), Scores.end());
	return Scores;
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
		vector <int> Count(Score_Range.size());
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
	double Attribute_SplitInfo = BerechneAttributEntropy(Remain_Matrix, The_Attribute);
	double Attribute_Gain = BerechneAttributEntropyGain(Remain_Matrix, The_Attribute);
	return Attribute_Gain / Attribute_SplitInfo;
}