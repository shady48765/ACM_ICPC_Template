#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 200000;
const int D = 20;

char buffer[N + 1];
int l[N], r[N], end[N];
std::string text[N];

int go[N][2], fail[N], depth[N], jump[N][D], stamp[N];
std::vector <int> children[N];
std::vector <std::pair <int, int> > updates[N];

void dfs(int& count, int p, int u)
{
	depth[u] = ~p ? depth[p] + 1 : 0;
	jump[u][0] = p;
	for (int i = 0; ~jump[u][i]; ++ i) {
		jump[u][i + 1] = jump[jump[u][i]][i];
	}
	stamp[u] = count ++;
	foreach (it, children[u]) {
		int v = *it;
		dfs(count, u, v);
	}
}

int lca(int u, int v)
{
	if (depth[u] > depth[v]) {
		std::swap(u, v);
	}
	for (int k = D - 1; k >= 0; -- k) {
		if (depth[v] - depth[u] >> k & 1) {
			v = jump[v][k];
		}
	}
	if (u == v) {
		return u;
	}
	for (int k = D - 1; k >= 0; -- k) {
		if (jump[u][k] != jump[v][k]) {
			u = jump[u][k];
			v = jump[v][k];
		}
	}
	return jump[u][0];
}

struct Node;

Node* null;

struct Node {
	Node(Node *left, Node *right) : count(left->count + right->count), left(left), right(right) {}
	Node(int count, Node* left, Node *right) : count(count), left(left), right(right) {}

	Node* insert(int l, int r, int k, int v)
	{
		if (k < l || r <= k) {
			return this;
		}
		if (l + 1 == r) {
			return new Node(count + v, null, null);
		}
		int m = l + r >> 1;
		return new Node(left->insert(l, m, k, v), right->insert(m, r, k, v));
	}

	int query(int l, int r, int a, int b)
	{
		if (b <= l || r <= a) {
			return 0;
		}
		if (a <= l && r <= b) {
			return count;
		}
		int m = l + r >> 1;
		return left->query(l, m, a, b) + right->query(m, r, a, b);
	}

	int count;
	Node *left, *right;
};

Node* merge(Node* p, Node* q)
{
	if (p == null) {
		return q;
	}
	if (q == null) {
		return p;
	}
	return new Node(p->count + q->count, merge(p->left, q->left), merge(p->right, q->right));
}

Node* tree[N];

void prepare(int n, int u)
{
	tree[u] = null;
	foreach (it, updates[u]) {
		tree[u] = tree[u]->insert(0, n, it->first, it->second);
	}
	foreach (it, children[u]) {
		prepare(n, *it);
		tree[u] = merge(tree[u], tree[*it]);
	}
}

int main()
{
	null = new Node(0, NULL, NULL);
	null->left = null->right = null;
	int n, q;
	scanf("%d%d", &n, &q);
	for (int i = 0; i < n; ++ i) {
		scanf("%s", buffer);
		text[i] = buffer;
	}
	int ncount = 1;
	memset(go, -1, sizeof(go));
	for (int i = 0; i < q; ++ i) {
		scanf("%d%d%s", l + i, r + i, buffer);
		l[i] --;
		int len = strlen(buffer);
		int &p = end[i] = 0;
		for (int j = 0; j < len; ++ j) {
			int tk = buffer[j] - 'a';
			if (go[p][tk] == -1) {
				go[p][tk] = ncount ++;
			}
			p = go[p][tk];
		}
	}
	{
		std::queue <int> queue;
		for (int c = 0; c < 2; ++ c) {
			if (~go[0][c]) {
				queue.push(go[0][c]);
				fail[go[0][c]] = 0;
			} else {
				go[0][c] = 0;
			}
		}
		while (!queue.empty()) {
			int u = queue.front();
			queue.pop();
			children[fail[u]].push_back(u);
			for (int c = 0; c < 2; ++ c) {
				int &v = go[u][c];
				if (~v) {
					fail[v] = go[fail[u]][c];
					queue.push(v);
				} else {
					v = go[fail[u]][c];
				}
			}
		}
	}
	memset(jump, -1, sizeof(jump));
	int vcount = 0;
	dfs(vcount, -1, 0);
	for (int i = 0; i < n; ++ i) {
		std::vector <std::pair <int, int> > order;
		for (int j = 0, p = 0; j < (int)text[i].size(); ++ j) {
			p = go[p][text[i][j] - 'a'];
			order.push_back(std::make_pair(stamp[p], p));
		}
		std::sort(order.begin(), order.end());
		int last = -1;
		for (int j = 0; j < (int)order.size(); ++ j) {
			int v = order[j].second;
			updates[v].push_back(std::make_pair(i, 1));
			if (~last) {
				updates[lca(last, v)].push_back(std::make_pair(i, -1));
			}
			last = v;
		}
	}
	prepare(n, 0);
	for (int i = 0; i < q; ++ i) {
		Node* t = tree[end[i]];
		printf("%d\n", t->query(0, n, l[i], r[i]));
	}
	return 0;
}
