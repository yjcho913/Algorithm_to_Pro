// 1504번: 특정한 최단거리 
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std; 

#define INF (98765432)
typedef pair<int, int> PII;
vector<PII> edges[802];
int d[3][802];
int N, E, a, b, c, X, Y, ans;

void Dij(int idx, int s)
{
	priority_queue<PII, vector<PII>, greater<PII>> pq;
	d[idx][s] = 0;
	pq.push({0, s});
			
	while (!pq.empty())
	{
		PII now = pq.top(); pq.pop();
		for (PII next : edges[now.second])
		{
			int tmp = d[idx][now.second] + next.first;
			if (d[idx][next.second] > tmp)
			{
				pq.push(next);
				d[idx][next.second] = tmp;
			}
		}
	}
}

int main()
{
	scanf("%d %d", &N, &E);
	for (int e = 0; e < E; e++)
	{
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back({c, b});
		edges[b].push_back({c, a});
	}
	scanf("%d %d", &X, &Y);
	
	for (int n = 1; n <= N; n++)
		d[0][n] = d[1][n] = d[2][n] = INF;

	Dij(0, 1); // idx 0 => 1에서 최단거리
	Dij(1, X); // idx 1 => X에서 최단거리 
	Dij(2, Y); // idx 2 => Y에서 최단거리 
	
	ans = min(d[0][X] + d[1][Y] + d[2][N], d[0][Y] + d[2][X] + d[1][N]);
	
	if (ans >= INF) printf("-1");
	else printf("%d\n", ans);
	
	return 0;
}


/***************************************************************************************************/
// 1654번: 랜선자르기 
#include <stdio.h>
#include <algorithm>
using namespace std;

long long K, N, ans, cnt, s = 1, e = -1, m, Len[10002];

int main()
{
	scanf("%lld %lld", &K, &N);
	for (int k = 1; k <= K; k++)
	{
		scanf("%lld", &Len[k]);
		e = max(e, Len[k]);
	}
	
	while (s <= e)
	{
		cnt = 0ll;
		m = (s + e) >> 1ll;
		for (int k = 1; k <= K; k++)
			cnt += (Len[k] / m);
		if (cnt >= N) { ans = max(ans, m); s = m + 1; }
		else e = m - 1;
	}
	
	printf("%lld\n", ans);
	
	return 0;
}


/***************************************************************************************************/
// 10775번: 공항 
#include <stdio.h>

int G, P, a, res, p, gate[100002];

int find(int a)
{
	if (gate[a] == a) return a;
	return gate[a] = find(gate[a]);
}

int main()
{
	scanf("%d %d", &G, &P);
	for (int g = 1; g <= G; g++)
		gate[g] = g;
	for (p = 1; p <= P; p++)
	{
		scanf("%d", &a);
		res = find(a);
		if (res == 0) 
			break;
		else
			gate[res] = res - 1;
	}
	
	printf("%d\n", p - 1);
	
	return 0;
}
