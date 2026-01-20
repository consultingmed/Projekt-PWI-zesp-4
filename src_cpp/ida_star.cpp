/** @file ida_star.cpp
 *  @brief Implementacja algorytmu IDA*.
 *  @details Zawiera logikę przeszukiwania przestrzeni stanów w celu znalezienia rozwiązania.
 */
#include <bits/stdc++.h>
#include "cube.h"
#include "debug.h"
#include "eoh.h"
#include "eph.h"
#include "cph.h"
using namespace std;
#define inf 1000000000
vector<string> moves;

vector<string> moves_phase1 = {
"U",// "Up", "U2", 
"D",// "Dp", "D2", 
"R",// "Rp", "R2", 
"L",// "Lp", "L2", 
"F",// "Fp", "F2", 
"B",// "Bp", "B2"
};

vector<string> moves_phase2 = {
    "U", "Up","U2",
    "D", "Dp","D2",
    "R2","L2","F2","B2"
};

eoh EOH;
cph CPH;
eph EPH;

bool is_goal_phase2(cube& c) {

    // sprawdzamy narożniki
    for (int i = 0; i < 8; i++) {
        if (c.cp[i] != i) return false; // narożnik na złym miejscu
//        if (c.co[i] != 0) return false; // złe ustawienie narożnika
    }

    // sprawdzamy krawędzie
    for (int i = 0; i < 12; i++) {
        if (c.ep[i] != i) return false; // krawędź na złym miejscu
//        if (c.eo[i] != 0) return false; // złe ustawienie krawędzi
    }

    return true; // wszystko poprawnie
}

bool is_goal_phase1(cube& c) {
    // orientacja narożników
    for (int i = 0; i < 8; i++) {
        if (c.co[i] != 0)
            return false;
    }

    //  orientacja krawędzi
    for (int i = 0; i < 12; i++) {
        if (c.eo[i] != 0)
            return false;
    }

    //  krawędzie UD muszą być w warstwach UD
    for (int pos = 0; pos < 12; pos++) {
        int edge = c.ep[pos];

        bool is_ud_edge = (edge <= 3) || (edge >= 8); // oryginalnie UD
        bool is_ud_pos  = (pos  <= 3) || (pos  >= 8); // pozycja UD

        if (is_ud_edge && !is_ud_pos)
            return false;
    }

    return true;
}

int getheuristic(cube &node, int stage){

	if(stage==1) return EOH.get_eoh(node); // gdy faza 1
	return max(CPH.get_cph(node), EPH.get_eph(node)); // gdy faza 2
}
int search(vector<string>& seq, cube node, int price, int bound, int stage){

	int f = price + getheuristic(node, stage);
	
	if(f > bound) return f;  // przekroczylony zakres przeszukiwania
	if(stage==1 and is_goal_phase1(node)) return -1;  // znaleziono rozwiązanie
	if(stage==2 and is_goal_phase2(node)) return -1;
	
	int mint = inf, move_count = 6;
	if(stage == 2) move_count = 10;
	for (int i = 0; i < move_count; i++){
		if(!seq.empty() && seq.back()[0] == moves[i][0]) continue;
		cube newcube=node;
		seq.push_back(moves[i]);
		newcube.move(moves[i]);
		int t = search(seq, newcube, price+1, bound, stage);
		if(t == -1) return t;
		mint = min(mint, t);
		
		seq.pop_back();
	
	}
	return mint;
	
}

vector<string> ida_star(cube root, int stage){
	if(stage == 1)
		moves = moves_phase1;
	else
		moves = moves_phase2;
	if(stage == 2)
		assert(is_goal_phase1(root) == 1);
	int bound=getheuristic(root, stage); //ustawienie początkowego zakresu przeszukiwania
	
	vector<string> seq;	
	while(true){
		int t = search(seq, root, 0, bound, stage); 
		if(t == -1) return seq;
		if(t >= inf) return seq;
		bound = t;
		debug(bound);
	}
}
