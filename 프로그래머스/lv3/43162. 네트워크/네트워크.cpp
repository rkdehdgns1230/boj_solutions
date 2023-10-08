#include <bits/stdc++.h>

#define MAX 201

using namespace std;

bool visited[MAX];

void bfs(int x, int n, vector<vector<int>> computers){
    queue<int> q;
    q.push(x);
    
    visited[x] = true;
    
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        
        for(int nxt = 0; nxt < n; nxt++){
            if(computers[cur][nxt] == 0) continue;
            if(visited[nxt]) continue;
            visited[nxt] = true;
            
            q.push(nxt);
        }
    }
    
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    
    fill(visited, visited + n, false);
    
    for(int i = 0; i < n; i++){
        if(!visited[i]){
            bfs(i, n, computers);
            answer++;
        }
    }
    
    return answer;
}