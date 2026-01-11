#pragma once
#include<bits/stdc++.h>
using namespace std;
#define MOVES 6
class cube
{
public:
	array<int, 8> cp; //permutacja rogow
	array<int, 8> co; //orientacja rogow
	array<int, 12> ep; //permutacja krawedzi
	array<int, 12> eo; //orientacja krawedzi
	//kostka jest reprezentowana wzgledem orientacji: niebieski center z przodu, biały center u góry, pomarańczowy center z prawej
	cube();
	
	void R();
	void L();
	void U();
	void D();
	void B();
	void F();
	
	void print();
	void move(int id);
};
