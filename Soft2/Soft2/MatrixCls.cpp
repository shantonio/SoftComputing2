#include "MatrixCls.h"



MatrixCls::MatrixCls(string Data_File)
{
	Matrix.erase(Matrix.begin(), Matrix.end());
	ifstream Data(Data_File);
	string line;
	string item;
	vector < string > Row;
	while (!Data.eof())
	{
		getline(Data, line);
		istringstream iss(line);
		while (iss.good())
		{
			getline(iss, item, ',');
			Row.push_back(item);
		}

		if (line.length())
		{
			Matrix.push_back(Row);
			Row.erase(Row.begin(), Row.end());
		}
	}
	Data.close();
}

MatrixCls::MatrixCls(vector < vector < string > > A_Matrix)
{
	for (int i = 0; i < A_Matrix.size(); i++)
	{
		Matrix.push_back(A_Matrix[i]);
	}
}

MatrixCls::MatrixCls() { };
MatrixCls::~MatrixCls() { };

string MatrixCls::Element(int i, int j)
{
	return Matrix[i][j];
}

int MatrixCls::SizeX()
{
	return Matrix[0].size();
}

int MatrixCls::SizeY()
{
	return Matrix.size();
}

vector < string > MatrixCls::GetAttributes()
{
	vector < string > Attribute;
	int j;
	for (j = 0; j < Matrix[0].size() - 1; j++)
	{
		Attribute.push_back(Matrix[0][j]);
	}
	return Attribute;
}

map < string, vector < string > > MatrixCls::GetAttributesValues()
{
	map < string, vector < string > > Attributes_Values;
	vector < string > Attribute_Values;
	int i, j;
	for (j = 0; j < Matrix[0].size(); j++)
	{
		for (i = 1; i < Matrix.size(); i++)
		{
			Attribute_Values.push_back(Matrix[i][j]);
		}
		sort(Attribute_Values.begin(), Attribute_Values.end());
		Attribute_Values.erase(unique(Attribute_Values.begin(), Attribute_Values.end()), Attribute_Values.end());
		Attributes_Values[Matrix[0][j]] = Attribute_Values;
		Attribute_Values.erase(Attribute_Values.begin(), Attribute_Values.end());
	}
	return Attributes_Values;
}

vector < string > MatrixCls::GetAttributeValues(string The_Attribute)
{
	return GetAttributesValues()[The_Attribute];
}

vector < string > MatrixCls::GetScoreRange()
{
	return GetAttributesValues()[Matrix[0][SizeX() - 1]];
}

int MatrixCls::AttributeIndex(string The_Attribute)
{
	int Index = 0;
	for (int i = 0; i < SizeX(); i++)
	{
		if (Matrix[0][i].compare(The_Attribute) == 0)
		{
			Index = i;
			break;
		}
	}
	return Index;
}

map < string, vector < string > > MatrixCls::GetAttributeValuesScores(string The_Attribute)
{
	int i, k;
	int Index = AttributeIndex(The_Attribute);
	map < string, vector < string > > Attribute_Values_Scores;
	vector < string > Attribute_Values = GetAttributesValues()[The_Attribute];
	vector < string > Row;
	for (k = 0; k < Attribute_Values.size(); k++)
	{
		for (i = 1; i < SizeY(); i++)
		{
			if (Matrix[i][Index].compare(Attribute_Values[k]) == 0)
			{
				Row.push_back(Matrix[i][SizeX() - 1]);
			}
		}
		Attribute_Values_Scores[Attribute_Values[k]] = Row;
		Row.erase(Row.begin(), Row.end());
	}
	return Attribute_Values_Scores;
}

vector < string > MatrixCls::GetScores()
{
	vector < string > Scores;
	for (int i = 1; i < Matrix.size(); i++)
	{
		Scores.push_back(Matrix[i][Matrix[0].size() - 1]);
	}
	return Scores;
}

MatrixCls MatrixCls::operator() (MatrixCls A_Matrix, string The_Attribute, string The_Value)
{
	Matrix.erase(Matrix.begin(), Matrix.end());
	int i, j, Index = 0;
	vector < string > Row;
	for (j = 0; j < A_Matrix.SizeX(); j++)
	{
		if (A_Matrix.Element(0, j).compare(The_Attribute) != 0)
		{
			Row.push_back(A_Matrix.Element(0, j));
		}
		else if (A_Matrix.Element(0, j).compare(The_Attribute) == 0)
		{
			Index = j;
		}
	}
	if (Row.size() != 0)
	{
		Matrix.push_back(Row);
		Row.erase(Row.begin(), Row.end());
	}

	for (i = 1; i < A_Matrix.SizeY(); i++)
	{
		for (j = 0; j < A_Matrix.SizeX(); j++)
		{
			if (A_Matrix.Element(0, j).compare(The_Attribute) != 0 & A_Matrix.Element(i, Index).compare(The_Value) == 0)
			{
				Row.push_back(A_Matrix.Element(i, j));
			}
		}
		if (Row.size() != 0)
		{
			Matrix.push_back(Row);
			Row.erase(Row.begin(), Row.end());
		}
	}

	return *this;
}

void MatrixCls::Display()
{
	int i, j;
	for (i = 0; i < Matrix.size(); i++)
	{
		for (j = 0; j < Matrix[0].size(); j++)
		{
			cout << " " << Matrix[i][j];
		}
		cout << endl;
	}
}