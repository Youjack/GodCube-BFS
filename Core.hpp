#pragma once

#include "Model.hpp"
#include <math.h>
#include <ctime>
#include <iostream>
using namespace std;

struct TreeStruct
{
	int8* Tree;
	int8* TreePtr;
	int8* _Tree;
	int8* _TreePtr;

	int* Dad;
	int8* Gene;

	int8 Depth;
	int Head, End;
	int SoluPtr;
} God, Jesus;

int8 path[GodNum + 1]; // path[GodNum] stores the number of steps

void Initialize()
{
	// 69984 = 9 * 6 ^ 5
	Jesus.Tree = new int8[69984 * StateLen];
	Jesus._Tree = new int8[69984 * StateLen];
	// 83980 = 1 + sum(9 * 6 ^ k), k = 0 ~ 5
	Jesus.Dad = new int[83980];
	Jesus.Gene = new int8[83980];
	// 11664 = 9 * 6 ^ 4
	God.Tree = new int8[11664 * StateLen];
	God._Tree = new int8[11664 * StateLen];
	// 13996 = 1 + sum(9 * 6 ^ k), k = 0 ~ 4
	God.Dad = new int[13996];
	God.Gene = new int8[13996];
}

bool Carol(TreeStruct* GTree, TreeStruct* CTree)
{
	int GEnd = GTree->End;
	for (int ptr = GTree->Head; ptr <= GTree->End; ptr++)
	{
		for (int8 gene : Gene)
		{
			if (notAllow(gene, GTree->Gene[ptr])) continue;
			// Transform
			GEnd++;
			GTree->Dad[GEnd] = ptr;
			GTree->Gene[GEnd] = gene;
			Transform(
				&GTree->TreePtr[(ptr - GTree->Head) * StateLen],
				gene,
				&GTree->_TreePtr[(GEnd - GTree->End - 1) * StateLen]);
			// search for the same
			CTree->SoluPtr = Compare(
				&GTree->_TreePtr[(GEnd - GTree->End - 1) * StateLen],
				CTree->TreePtr,
				CTree->End - CTree->Head + 1);
			if (CTree->SoluPtr != -1)
			{
				GTree->SoluPtr = GEnd;
				CTree->SoluPtr += CTree->Head;
				return true;
			}
		}
	}
	GTree->Head = GTree->End + 1;
	GTree->End = GEnd;

	return false;
}

void SearchPath()
{
	path[GodNum] = God.Depth + Jesus.Depth;
	// search in JesusTree
	for (int8 i = 0; i < God.Depth; i++)
	{
		path[God.Depth - 1 - i] = God.Gene[God.SoluPtr];
		God.SoluPtr = God.Dad[God.SoluPtr];
	}
	// search in GodTree
	for (int8 i = 0; i < Jesus.Depth; i++)
	{
		path[God.Depth + i] = GeneInver[Jesus.Gene[Jesus.SoluPtr]];
		Jesus.SoluPtr = Jesus.Dad[Jesus.SoluPtr];
	}
}

int8 *Search(int8 State[StateLen])
{
	// INITIALIZE

	// set the first state
	Jesus.Gene[0] = God.Gene[0] = 9; // an operation which is not exist
	Jesus.Dad[0] = God.Dad[0] = 0; // they don't have a dad at all
	for (int8 i = 0; i < StateLen; i++)
	{
		Jesus.Tree[i] = i * 3;
		God.Tree[i] = State[i];
	}
	Jesus.Depth = God.Depth = 0;
	Jesus.Head = Jesus.End = 0;
	God.Head = God.End = 0;
	
	// set the tree pointer
	Jesus.TreePtr = Jesus.Tree;
	Jesus._TreePtr = Jesus._Tree;
	God.TreePtr = God.Tree;
	God._TreePtr = God._Tree;

	// SOLVE
	bool OK;
	int8 *temp;
	clock_t start_t, end_t;
	start_t = clock();
	while (true)
	{
		Jesus.Depth++;
		OK = Carol(&Jesus, &God);
		// exchange the tree pointer
		temp = Jesus.TreePtr;
		Jesus.TreePtr = Jesus._TreePtr;
		Jesus._TreePtr = temp;
		if (OK) break;

		if (Jesus.Depth == ceil(double(GodNum) / 2))
		{
			cout << "JesusDepth = " << int(Jesus.Depth) << endl;
			return nullptr;
		}

		God.Depth++;
		OK = Carol(&God, &Jesus);
		// exchange the tree pointer
		temp = God.TreePtr;
		God.TreePtr = God._TreePtr;
		God._TreePtr = temp;
		if (OK) break;
	}
	end_t = clock();
	cout << "time: " << (double)(end_t-start_t)/CLOCKS_PER_SEC*1000 << "ms" << endl;

	// RETURN
	SearchPath();
	return path;
}