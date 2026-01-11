#include<bits/stdc++.h>
#include "cube.h"
#include "debug.h"
using namespace std;
cube::cube()
{
	iota(cp.begin(), cp.end(), 0);
	iota(ep.begin(), ep.end(), 0);
	for(auto &v : co) v = 0;
	for(auto &v : eo) v = 0;
}
void cube::U() {
    int swp = cp[3];
    cp[3] = cp[2];
    cp[2] = cp[1];
    cp[1] = cp[0];
    cp[0] = swp;

    swp = ep[3];
    ep[3] = ep[2];
    ep[2] = ep[1];
    ep[1] = ep[0];
    ep[0] = swp;
}

void cube::D() {
    int swp = cp[7];
    cp[7] = cp[4];
    cp[4] = cp[5];
    cp[5] = cp[6];
    cp[6] = swp;

    swp = ep[11];
    ep[11] = ep[8];
    ep[8] = ep[9];
    ep[9] = ep[10];
    ep[10] = swp;

}

void cube::R() {
    co[cp[2]] = (co[cp[2]]+2)%3;
    co[cp[3]] = (co[cp[3]]+1)%3;
    co[cp[6]] = (co[cp[6]]+1)%3;
    co[cp[7]] = (co[cp[7]]+2)%3;

    int swp = cp[3];
    cp[3] = cp[7];
    cp[7] = cp[6];
    cp[6] = cp[2];
    cp[2] = swp;

    swp = ep[3];
    ep[3] = ep[7];
    ep[7] = ep[11];
    ep[11] = ep[6];
    ep[6] = swp;

}

void cube::L() {
    co[cp[0]] = (co[cp[0]]+2)%3;
    co[cp[1]] = (co[cp[1]]+1)%3;
    co[cp[4]] = (co[cp[4]]+1)%3;
    co[cp[5]] = (co[cp[5]]+2)%3;

    int swp = cp[0];
    cp[0] = cp[1];
    cp[1] = cp[5];
    cp[5] = cp[4];
    cp[4] = swp;

    swp = ep[1];
    ep[1] = ep[5];
    ep[5] = ep[9];
    ep[9] = ep[4];
    ep[4] = swp;

}

void cube::F() {
    co[cp[0]] = (co[cp[0]]+1)%3;
    co[cp[3]] = (co[cp[3]]+2)%3;
    co[cp[4]] = (co[cp[4]]+2)%3;
    co[cp[7]] = (co[cp[7]]+1)%3;

    eo[ep[0]] ^= 1;
    eo[ep[8]] ^= 1;
    eo[ep[4]] ^= 1;
    eo[ep[7]] ^= 1;

    int swp = cp[0];
    cp[0] = cp[4];
    cp[4] = cp[7];
    cp[7] = cp[3];
    cp[3] = swp;

    swp = ep[0];
    ep[0] = ep[4];
    ep[4] = ep[8];
    ep[8] = ep[7];
    ep[7] = swp;
}

void cube::B() {
    co[cp[1]] = (co[cp[1]]+2)%3;
    co[cp[2]] = (co[cp[2]]+1)%3;
    co[cp[5]] = (co[cp[5]]+1)%3;
    co[cp[6]] = (co[cp[6]]+2)%3;

    eo[ep[2]] ^= 1;
    eo[ep[6]] ^= 1;
    eo[ep[10]] ^= 1;
    eo[ep[5]] ^= 1;

    int swp = cp[1];
    cp[1] = cp[2];
    cp[2] = cp[6];
    cp[6] = cp[5];
    cp[5] = swp;

    swp = ep[2];
    ep[2] = ep[6];
    ep[6] = ep[10];
    ep[10] = ep[5];
    ep[5] = swp;

}
void cube::print()
{
	vector<pair<char, char> > edges = {
	{'W', 'B'}, {'W', 'R'}, {'W', 'G'}, {'W', 'O'},
	{'B', 'R'}, {'G', 'R'}, {'G', 'O'}, {'B', 'O'},
	{'Y', 'B'}, {'Y', 'R'}, {'Y', 'G'}, {'Y', 'O'}};

	vector<vector<char> > corners = {
	{'W', 'R', 'B'}, {'W', 'G', 'R'}, {'W', 'O', 'G'}, {'W', 'B', 'O'},
	{'Y', 'B', 'R'}, {'Y', 'R', 'G'}, {'Y', 'G', 'O'}, {'Y', 'O', 'B'}};

	auto p_cor = [&](int num, int face)
	{
		cout<<corners[cp[num]][(co[cp[num]]+face)%3]<<" ";
	};
	auto p_edg = [&](int num, int flip)
	{
		flip ^= eo[ep[num]];
		if(!flip)
			cout<<edges[ep[num]].first<<" ";
		else	
			cout<<edges[ep[num]].second<<" ";
	};
	//Górna ściana:
	cout<<"U: ";
	p_cor(1, 0); p_edg(2, 0); p_cor(2, 0); cout<<endl;
	p_edg(1, 0); cout<<"W "; p_edg(3, 0); cout<<endl;
	p_cor(0, 0); p_edg(0, 0); p_cor(3, 0); cout<<endl;

	//Dolna ściana:
	cout<<"D: ";
	p_cor(4, 0); p_edg(8, 0); p_cor(7, 0); cout<<endl;
	p_edg(9, 0); cout<<"Y "; p_edg(11, 0); cout<<endl;
	p_cor(5, 0); p_edg(10, 0); p_cor(6, 0); cout<<endl;

	//Przednia ściana:
	cout<<"F: ";
	p_cor(0, 2); p_edg(0, 1); p_cor(3, 1); cout<<endl;
	p_edg(4, 0); cout<<"B "; p_edg(7, 0); cout<<endl;
	p_cor(4, 1); p_edg(8, 1); p_cor(7, 2); cout<<endl;

	//Tylnia ściana:
	cout<<"B: ";	
	p_cor(5, 2); p_edg(10, 1); p_cor(6, 1); cout<<endl;
	p_edg(5, 0); cout<<"G "; p_edg(6, 0); cout<<endl;
	p_cor(1, 1); p_edg(2, 1); p_cor(2, 2); cout<<endl;

	//Lewa ściana:
	cout<<"L: ";
	p_cor(1, 2); p_edg(1, 1); p_cor(0, 1); cout<<endl;
	p_edg(5, 1); cout<<"R "; p_edg(4, 1); cout<<endl;
	p_cor(5, 1); p_edg(9, 1); p_cor(4, 2); cout<<endl;

	//Prawa ściana:
	cout<<"R: ";
	p_cor(3, 2); p_edg(3, 1); p_cor(2, 1); cout<<endl;
	p_edg(7, 1); cout<<"O "; p_edg(6, 1); cout<<endl;
	p_cor(7, 1); p_edg(11, 1); p_cor(6, 2); cout<<endl;

	//Dokładna orientacja ścianki będzie zależeć specyfikacji programu wizualizującego w pythonie
}
void cube::move(string id) {
    if(id=="U") U();
    if(id=="D") D();
    if(id=="R") R();
    if(id=="L") L();
    if(id=="F") F();
    if(id=="B") B();

    if(id=="Up") {U(); U(); U();}
    if(id=="Dp") {D(); D(); D();}
    if(id=="Rp") {R(); R(); R();}
    if(id=="Lp") {L(); L(); L();}
    if(id=="Fp") {F(); F(); F();}
    if(id=="Bp") {B(); B(); B();}

    if(id=="U2") {U(); U();}
    if(id=="D2") {D(); D();}
    if(id=="R2") {R(); R();}
    if(id=="L2") {L(); L();}
    if(id=="F2") {F(); F();}
    if(id=="B2") {B(); B();}
}

