/** @file main.cpp
 *  @brief Plik główny programu solvera.
 *  @details Obsługuje argumenty wiersza poleceń i steruje procesem rozwiązywania.
 */
#include "debug.h"
#include "cube.h"
#include "ida_star.h"
#include <chrono>
int main(int argc, char* argv[])
{
	if(argc == 1)
	{
		cerr<<"Wczytano heurystyki"<<endl;
		cube state;
		state.read();
		cerr<<"Udane wczytanie stanu kostki"<<endl;
		auto seq = ida_star(state, 1);
		for(auto& v : seq)
		{		
			state.print();
			cout<<"----"<<endl;
			state.move(v);
			cerr<<v<<" ";
		}
		seq = ida_star(state, 2);
		for(auto& v : seq)
		{
			state.print();
			cout<<"---"<<endl;
			state.move(v);
			cerr<<v<<" ";
		}
		state.print();
		return 0;
	}
	if(argc == 2 && strcmp(argv[1], "--moves") == 0)
	{
		#ifndef DEBUG
		cout<<"Podaj liczbę ruchów: ";
		#endif
		int n;
		cin>>n;
		assert(0 <= n && n <= 1000);
		cube state;
		for(int i=0;i<n;i++)
		{
			#ifndef DEBUG
			cout<<"Podaj ruch: ";
			#endif
			string move;
			cin>>move;
			state.move(move);
		}
		#ifndef DEBUG
		cout<<"Rozpoczynanie fazy pierwszej\n";
		#endif
		auto solving_seq = ida_star(state, 1);
		#ifndef DEBUG
		cout<<"Zakończono fazę pierwszą\n";
		cout<<"Ruchy fazy pierwszej: \n";
		#endif
		for(auto& v : solving_seq)
			state.move(v), cout<<v<<" ";
		#ifndef DEBUG 
		cout<<"Rozpoczynanie fazy drugiej\n";
		#endif
		solving_seq = ida_star(state, 2);
		#ifndef DEBUG
		cout<<"Zakończenie fazy drugiej\n";
		cout<<"Ruchy fazy drugiej: \n";
		#endif	
		for(auto& v : solving_seq)
			cout<<v<<" ";
		return 0;
	}
	if(argc == 2 && strcmp(argv[1], "--test") == 0)
	{
		int t;
		cout<<"Podaj liczbę testów: "<<endl;
		cin>>t;
		for(int s=0;s<t;s++)
		{
			int n = rand()%100;
			cube state;
			vector<string> moves = {"R", "U", "D", "F", "B", "L"};
			vector<string> scramble;
			for(int i=0;i<n;i++)
			{
				int id = rand()%6;
				state.move(moves[id]);
				scramble.push_back(moves[id]);
			}
			auto start = chrono::steady_clock::now();
			vector<string> seq = ida_star(state, 1);
			for(auto& v : seq) state.move(v);
			seq = ida_star(state, 2);
			auto end = chrono::steady_clock::now();
			for(auto& v : seq) state.move(v);
			bool ok = 1;
			for(int i=0;i<12;i++)
				if(!(state.ep[i] == i && state.eo[i] == 0))
					ok = false;
			for(int i=0;i<8;i++)
				if(!(state.cp[i] == i && state.co[i] == 0))
					ok = false;
			if(!ok)
			{
				cout<<s<<" test nie przszedł. ";
				cout<<"Sekwencja mieszająca to: ";
				for(auto& v : scramble) cout<<v<<" ";
				cout<<endl;
				return 0;
			}
			chrono::duration<double> elapsed = end - start;
			cout<<s<<" test przeszedł w czasie: "<<elapsed.count()<<endl;
		}
		return 0;
	}
	cerr<<"Nie rozpoznano flag!\n";
}
