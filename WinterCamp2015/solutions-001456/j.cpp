//#include<bits/stdc++.h>
#include <iostream>
#include <map>
#include <vector>
#include <cstdio>
using namespace std;

const int N = 1000006;

vector< vector<int> > key_sentences[N];
int speech[N], n;
bool draw;

/*
* key_sentences[k] to wektor zdan kluczowych o dlugosci k
* speech to tablica na wejsciu
* n to rozmiar tablicy na wejsciu
* already_checked to mapa w celu zopcenia rozwiazania
*/

//b, e oznaczaja przedzial [b, e)

bool check(int b, int e)
{
	//funkcja check dziala w O(suma dlugosci slow o dlugosci e - b)
	//zwraca true jesli podslowo(b, e - 1) jest zdaniem kluczowym
	//dla ustalonej dlugosci jest wywolywana malo razy (co najwyzej jakies 4)
	//dla jednego przedzialu jest wywolywana co najwyzej raz, bo mapa
	//zatem cale rozwiazanie jest liniowe
	
	if(e == b) 
	{
		return draw;
	}
	
	int interval_length = e - b;
	for(int i = 0; i < key_sentences[interval_length].size(); i++)
	{
		bool ok = true;
		for(int j = 0; j < key_sentences[interval_length][i].size(); j++)
		{
			if(key_sentences[interval_length][i][j] != speech[b + j])
			{
				ok = false;
				break;
			}
		}
		if(ok) 
		{
			return true;
		}
	}
	return false;
}

bool win(int b, int e)
{
	//return !draw jesli ja wykonam ruch zabierajacy ostatnie slowo
	//return draw jesli przeciwnik wykona ten ruch
	//return false jesli ja wygram
	//return true jesli przeciwnik wygra
	
	if(b == e) return !draw; //przedzial pusty, bedzie remis
	
	if(check(b, e)) return false; //zdanie kluczowe
	
	if(b + 1 == e) return draw; //jedno slowo, bedzie remis
	
	if(check(b + 1, e) || check(b, e - 1)) return true; //moge zjesc literke tak zeby bylo zdanie kluczowe
	
	if(b + 2 == e) return !draw; //dwa slowa, bedzie remis
	
	if(check(b + 2, e)) return !win(b, e - 1); //jesli takie zdanie jest kluczowe, to jak pojde w [b + 1, e), to niechybnie przegram, zatem na pewno ide w [b, e - 1)
	
	if(check(b, e - 2)) return !win(b + 1, e); //jak wyzej, tylko ze w druga strone ide
	
	if(check(b + 1, e - 1)) return false; //jesli zdanie [b + 1, e - 1) jest kluczowe, to z pewnoscia przegralem

	if(b + 3 == e) return draw; //trzy slowa
	
	if(check(b + 2, e - 1) || check(b + 1, e - 2)) return true; //jesli ktores z tych zdan jest kluczowe, to moge tak pojsc, zeby wygrac
	
	//otoz jesli sie nie skonczylismy jeszcze, to znaczy, ze pozycja [i, j) ma taka sama wygrywalnosc jak [i + 1, j - 1)
	//a czemu? no bo sprawdzanie przypadkow
	//jak [i + 1, j - 1) jest przegrywajaca, to w oczywisty sposob [i, j) tez jest
	//jak [i + 1, j - 1) jest wygrywajaca, to [i + 2, j - 1) lub [i + 1, j - 2) jest przegrywajaca
	//wiec jak b.s.o zaloze, ze to ta pierwsza, to zjadam literke i, a nastepnie niezaleznie od ruchow przeciwnika doprowadze go do [i + 2, j - 1)
	
	return win(b + 1, e - 1); 
}

void clean()
{
	for(int i = 0; i < n; i++)
	{
		key_sentences[i].clear();
	}
}

int get_result()
{
	bool res[2];
	draw = true;
	for(int i = 0; i < 2; i++)
	{
		res[i] = win(0, n);
		draw ^= 1;
	}
	if (res[0] & res[1])
	{
		return 0;
	}
	if (res[0] | res[1])
	{
		return 1;
	}
	return 2;
}

string answers[] = {"FIRST", "DRAW", "SECOND"};

void solve()
{
    scanf("%d", &n);
	clean();
	for(int i=0; i < n; i++)
	{
		int x;
		scanf("%d", &x);
		speech[i] = x;
	}
	
	int number_of_sentences;
    scanf("%d", &number_of_sentences);
	
	for(int i = 0; i < number_of_sentences; i++)
	{
		int sentence_length;
		scanf("%d", &sentence_length);
		
		vector<int> v;
		
		for(int j = 0; j < sentence_length; j++)
		{
			int x;
			scanf("%d", &x);
			v.push_back(x);
		}
		
		if(sentence_length < n)
		{
			key_sentences[sentence_length].push_back(v);
		}
	}
	
	string s = answers[get_result()];
	printf("%s\n", s.c_str());
}

int main()
{
  int TT;
  scanf("%d", &TT);
  while(TT--)
  {
      solve();
  }
}
