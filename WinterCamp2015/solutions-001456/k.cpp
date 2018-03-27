#include <cstdio>
#include <vector>
#include <map>
#include <string>
using namespace std;

const int circle = 1;
const int cross = -1;

struct intel 
{
    int winner;
    int draw;
    bool v;
    intel(): v(0) {}
};

map<pair<vector<vector<int> >, int>, intel> m;

vector<int> empty_row() 
{
    vector<int> r;
    for(int i = 0; i < 3; i++)
		r.push_back(0);
    return r;
}

pair<vector<vector<int> >, int> starting() 
{
    vector<vector<int> > r;
    for(int i = 0; i < 3; i++) 
		r.push_back(empty_row());
    return make_pair(r, circle);
}

vector<vector<int> > scan() 
{
    vector<vector<int> > r;
    char buf[5];
    for(int i = 0; i < 3; i++)
    {
        scanf("%s", buf);
        vector<int> t;
        for(int j = 0; j < 3; j++) 
        {
            if(buf[j] == '.') 
			{
				t.push_back(0);
			}
            else 
            {
				t.push_back((buf[j] == 'X') ? cross : circle);
			}
        }
        r.push_back(t);
    }
    return r;
}

int three(int a, int b, int c) //sprawdza czy a=b=c>0, jak tak to zwraca a
{
    if((a) && (a == b) && (b == c)) return a;
    return 0;
}

int winning(pair<vector<vector<int> >, int> s) 
{
    vector<vector<int> > t = s.first;
	#define OP(a,b,c) if(three(a,b,c)) return three(a,b,c)

    for(int i = 0; i < 3; i++) 
    {
		OP(t[i][0], t[i][1], t[i][2]); //bierze wiersze
	}
    
    for(int i = 0; i < 3; i++) 
    {
		OP(t[0][i], t[1][i], t[2][i]); //bierze kolumny
	}
    
    OP(t[0][0], t[1][1], t[2][2]); //bierze przekatne
    OP(t[2][0], t[1][1], t[0][2]); 
    return 0;
}

int drawn(pair<vector<vector<int> >, int> s) 
{
    for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if(s.first[i][j] == 0) 
				return 0;
    return 1;
}

intel f(pair<vector<vector<int> >, int> t) 
{
    if(m.find(t) != m.end()) return m[t];
    intel r;
    if(winning(t)) 
    {
        r.winner = winning(t);
        r.draw = 0;
    } 
    else if(drawn(t)) 
    {
        r.winner = 0;
        r.draw = 1;
    } 
    else 
	{
        int canwin = 0;
        int candraw = 0;
        for(int i = 0; i < 3; i++) 
			for(int j = 0; j < 3; j++)  
				if(!t.first[i][j]) 
				{
					pair<vector<vector<int> >, int> tt(t.first,-t.second);
					tt.first[i][j] = t.second;
					intel ii = f(tt);
					if(ii.draw) candraw = 1;
					if(!ii.draw && ii.winner == t.second) canwin = 1;
				}
		
        if(canwin) 
        {
            r.winner = t.second;
            r.draw = 0;
        } 
        else if(candraw) 
        {
            r.winner = 0;
            r.draw = 1;
        } 
        else 
        {
            r.winner = -t.second;
            r.draw = 0;
        }
    }
    m[t] = r;
    return m[t];
}

void burn(pair<vector<vector<int> >, int> t) 
{
    if(m[t].v) return;
    m[t].v = 1;
    intel i = m[t];
    intel r = i;
    if(drawn(t) || winning(t)) return;
    for(int y = 0; y < 3; y++)  
		for(int x = 0; x < 3; x++) 
			if(!t.first[y][x]) 
			{
				pair<vector<vector<int> >, int> tt(t.first,-t.second);
				tt.first[y][x] = t.second;
				intel ii = m[tt];
				if(i.winner == t.second && ii.winner == t.second) burn(tt);
				else if(i.draw && ii.draw) burn(tt);
				else if(i.winner == -t.second) burn(tt);
			}
}

int cnt_moves(vector<vector<int> > s, int w) 
{
    int r = 0;
    for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if(s[i][j] == w) r++;
    return r;
}

int whose_turn(vector<vector<int> > s) 
{
    if(cnt_moves(s, circle) > cnt_moves(s, cross)) return cross;
    else return circle;
}

string answers[] = {"INVALID", "REACHABLE", "UNREACHABLE"};

int solve()
{
    vector<vector<int> > s = scan();
    pair<vector<vector<int> >, int> t(s, whose_turn(s));
    
    if(m.find(t) == m.end()) return 0;
    if(m[t].v) return 1;
    return 2;
	
}

int main() 
{
    f(starting());
    burn(starting());
    int z; 
    scanf("%d", &z);
    while(z--) 
    {
		string s = answers[solve()];
		printf("%s\n", s.c_str());
    }
    return 0;
}
