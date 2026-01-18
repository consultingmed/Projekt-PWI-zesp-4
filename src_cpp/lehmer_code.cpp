#include "lehmer_code.h"
#include "cube.h"
#include <bits/stdc++.h>
int lehmer_code(vector<int>& perm) //kodowanie Lehmera
{
	const unsigned int sz = perm.size();
	bool used[sz];
	int fact[sz];
	fact[0] = fact[1] = 1;
	used[0] = used[1] = 0;
	for(int i=2;i<sz;i++)
		used[i] = 0, fact[i] = fact[i-1]*i;
	int res = 0;
	for(int i=0;i<sz;i++)
	{
		int smaller = 0;
		for(int j=0;j<perm[i];j++)
			if(!used[j]) smaller++;
		res += smaller * fact[sz-1-i];
		used[perm[i]] = true;
	}
	return res;
}
