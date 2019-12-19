#pragma once

#define int8 char
#define nGene 9
#define StateLen 6
#define GodNum 11

const int8 Trans[21][9] = 
{
	{ 12,  3, 10, 15,  6,  4, 18,  9,  7 },
	{ 13,  4, 11, 16,  7,  5, 19, 10,  8 },
	{ 14,  5,  9, 17,  8,  3, 20, 11,  6 },
	{ 10, 12,  0,  8,  2, 17,  3,  3,  3 },
	{ 11, 13,  1,  6,  0, 15,  4,  4,  4 },
	{  9, 14,  2,  7,  1, 16,  5,  5,  5 },
	{  6,  6,  6,  4, 15,  0, 11,  2, 20 },
	{  7,  7,  7,  5, 16,  1,  9,  0, 18 },
	{  8,  8,  8,  3, 17,  2, 10,  1, 19 },
	{  5,  2, 14,  9,  9,  9,  7, 18,  0 },
	{  3,  0, 12, 10, 10, 10,  8, 19,  1 },
	{  4,  1, 13, 11, 11, 11,  6, 20,  2 },
	{  0, 10,  3, 12, 12, 12, 12, 12, 12 },
	{  1, 11,  4, 13, 13, 13, 13, 13, 13 },
	{  2,  9,  5, 14, 14, 14, 14, 14, 14 },
	{ 15, 15, 15,  0,  4,  6, 15, 15, 15 },
	{ 16, 16, 16,  1,  5,  7, 16, 16, 16 },
	{ 17, 17, 17,  2,  3,  8, 17, 17, 17 },
	{ 18, 18, 18, 18, 18, 18,  0,  7,  9 },
	{ 19, 19, 19, 19, 19, 19,  1,  8, 10 },
	{ 20, 20, 20, 20, 20, 20,  2,  6, 11 }
};

const int8 Gene[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
const int8 GeneInver[] = { 0, 2, 1, 3, 5, 4, 6, 8, 7 };

void Transform(int8 *StatePtr, int8 gene, int8 *_StatePtr)
{
	for (int8 i = 0; i < StateLen; i++)
		_StatePtr[i] = Trans[StatePtr[i]][gene];
}

bool notAllow(int8 gene1, int8 gene2)
{
	if (gene1 / 3 == gene2 / 3) return true;
	else return false;
}

int Compare(int8 *StatePtr, int8 *TreePtr, int nState)
{
	for (int ptr = 0; ptr < nState; ptr++, TreePtr += StateLen)
	{
		int8 i;
		for (i = 0; i < StateLen; i++)
			if (StatePtr[i] != TreePtr[i]) break;
		if (i == StateLen) return ptr;
	}
	return -1;
}