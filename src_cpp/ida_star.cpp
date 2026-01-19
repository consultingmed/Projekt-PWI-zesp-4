#include <bits/stdc++.h>
#include "cube.h"
#include "debug.h"
#include "eoh.h"
#include "eph.h"
#include "cph.h"
using namespace std;
typedef long long LL;

#define inf 1000000000

string moves1[20] = {
"U", "Up", "U2",
"D", "Dp", "D2",
"R", "Rp", "R2",
"L", "Lp", "L2",
"F", "Fp", "F2",
"B", "Bp", "B2"

};

string moves2[10] = {
"U", "Up", "U2",
"D", "Dp", "D2",
"R2", "L2", "F2", "B2"
};

eoh EOH;
cph CPH;
eph EPH;

bool is_goal_phase2(cube& c) {

    // sprawdzamy narożniki
    for (int i = 0; i < 8; i++) {
        if (c.cp[i] != i) return false; // narożnik na złym miejscu
        if (c.co[i] != 0) return false; // złe ustawienie narożnika
    }

    // sprawdzamy krawędzie
    for (int i = 0; i < 12; i++) {
        if (c.ep[i] != i) return false; // krawędź na złym miejscu
        if (c.eo[i] != 0) return false; // złe ustawienie krawędzi
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

int search(cube node, vector <string> &move_path, int price, int bound, int stage){
	
	int f = price + getheuristic(node, stage);
	
	if(f > bound) return f;  // przekroczylony zakres przeszukiwania
	if(stage==1 and is_goal_phase1(node)) return -1;  // znaleziono rozwiązanie
	if(stage==2 and is_goal_phase2(node)) return -1;
	
	int mint = inf, move_count = (stage == 1 ? 18 : 10);
	for (int i = 0; i < move_count; i++){
	
		cube newcube=node;
		string new_move=(stage == 1 ? moves1[i] : moves2[i]);
		
		if (!move_path.empty()) {
    		if (new_move[0]==move_path.back()[0])
        	continue;
		}
		
		newcube.move(new_move);
    	
		move_path.push_back(new_move);

		int t = search(newcube, move_path, price+1, bound, stage);
		if(t == -1) return t;
		mint = min(mint, t);
		
		move_path.pop_back();
	
	}
	return mint;
	
}

pair<vector<string>, int> ida_star(cube root, int stage){
	
	
	int bound=getheuristic(root, stage); //ustawienie początkowego zakresu przeszukiwania
	
	vector <string> move_path;
	
	while(true){
		int t = search(root, move_path, 0, bound, stage); 
		if(t == -1) return {move_path, bound};
		if(t >= inf) return {move_path, -1};
		bound = t;
	}
}
