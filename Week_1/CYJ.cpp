// BOJ_5729_거의최단경로.cpp
// 다 익스트라
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define NMAX (500)
#define MMAX (10000)
#define INF (500000)
#define INFINF (1000000)

int N, M;
int S, D;
typedef pair<int, int> pii;
vector<pii> linkList[NMAX + 10];
vector<int> prevList[NMAX + 10];
int cost[NMAX + 10];
priority_queue<pii, vector<pii>, greater<pii> > pq;
queue<int> que;

int getSol(int t){
    int U, V, P;
    int i;
    pii out;
    int tmp;
    int iout;
    vector<pii>::iterator iter;

    // 초기화
    for(i=0; i<N; i++){
        cost[i] = INFINF;
        linkList[i].clear();
        prevList[i].clear();
    }

    // 입력
    cin >> S >> D;
    while(M--){
        cin >> U >> V >> P;
        linkList[U].push_back(make_pair(P, V));
    }
    
    // 다익스트라 - 최단경로
    cost[S] = INF;
    pq.push(make_pair(0, S));

    while(!pq.empty()){
        out = pq.top(); pq.pop();

        if(cost[out.second] < out.first) continue;

        for(pii vertex : linkList[out.second]){
            tmp = cost[out.second] + vertex.first;
            if(tmp < cost[vertex.second]){
                cost[vertex.second] = tmp;
                pq.push(make_pair(tmp, vertex.second));
                prevList[vertex.second].clear();
                prevList[vertex.second].push_back(out.second);
            }
            else if(tmp == cost[vertex.second]){
                pq.push(make_pair(tmp, vertex.second));
                prevList[vertex.second].push_back(out.second);
            }
        }
    }
    if(cost[D] == INFINF) return -1;

    // 최단 경로 걸러내기
    que.push(D);
    while(!que.empty()){
        iout = que.front(); que.pop();

        for(int next : prevList[iout]){
            for(iter = linkList[next].begin();;iter++){
                if(iter->second == iout){
                    iter->first = INFINF;
                    break;
                }
            }
            if(next == S) continue;
            que.push(next);
        }
    }

    // 다익스트라 - 거의 최단 경로
    cost[S] = 0;
    pq.push(make_pair(0, S));

    while(!pq.empty()){
        out = pq.top(); pq.pop();

        if(cost[out.second] < out.first) continue;

        for(pii vertex : linkList[out.second]){
            tmp = cost[out.second] + vertex.first;
            if(tmp < cost[vertex.second]){
                cost[vertex.second] = tmp;
                pq.push(make_pair(tmp, vertex.second));
            }
        }
    }
    return cost[D] > INF ? -1 : cost[D];
}

int main(){
    int t = 0;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    while(1){
        t++;
        cin >> N >> M;
        if(N == 0 && M == 0) return 0;
        cout << getSol(t) << "\n";
    }
}



// BOJ_1654_랜선자르기.cpp
// binary search
#include <iostream>
using namespace std;
#define KMAX (10000)

int K;
long long N;
long long lines[KMAX + 10];
long long maxLine;

void input(){
    int i;

    cin >> K >> N;
    for(i=0; i<K; i++){
        cin >> lines[i];
        if(lines[i] > maxLine) maxLine = lines[i];
    }
}

int binarySearch(){
    long long s = 1;
    long long e = maxLine + 1;
    long long m;
    long long tmp;
    int i;
    int sol = 1;

    while(s <= e){
        m = (s + e) / 2;
        tmp = 0;
        for(i=0; i<K; i++) tmp += lines[i]/m;
        if(tmp < N) e = m - 1;
        else {
            s = m + 1;
            sol = m;
        }
    }

    return sol;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    input();
    cout << binarySearch() << "\n";
}



// BOJ_10775_공항.cpp
// find-union
#include <iostream>
using namespace std;
#define PMAX (100000)
#define GMAX (100000)

int G, P;
int planes[PMAX + 10];
int gates[GMAX + 10];

void input(){
    int i;

    cin >> G >> P;
    for(i=1; i<=P; i++){
        cin >> planes[i];
    }
}

int findGate(int g){
    if(gates[g] == g) return g;
    return gates[g] = findGate(gates[g]);
}

void unionGate(int g){
    gates[g] = gates[gates[g] - 1];
    
}
int getSol(){
    int i, j;
    int root;

    for(i=1; i<=G; i++) gates[i] = i;

    for(i=1; i<=P; i++){
        root = findGate(planes[i]);
        if(root == 0) break;
        gates[root] = gates[root - 1];
    }

    return i-1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    input();
    cout << getSol() << "\n";
}
