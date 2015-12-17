#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;


class MatrixCls
{
	private: vector < vector < string > > Matrix;
	
public:
	MatrixCls(string Data_File);
	MatrixCls(vector < vector < string > > A_Matrix);

		
	string Element(int i, int j);

	int SizeX();
	int SizeY();

	vector < string > GetAttributes();

	map < string, vector < string > > GetAttributesValues();

	vector < string > GetAttributeValues(string The_Attribute);

	vector < string > GetScoreRange();
	int AttributeIndex(string The_Attribute);

	map < string, vector < string > > GetAttributeValuesScores(string The_Attribute);

	vector < string > GetScores();

	MatrixCls operator() (MatrixCls A_Matrix, string The_Attribute, string The_Value);

	void Display();

	MatrixCls();
	~MatrixCls();
};

