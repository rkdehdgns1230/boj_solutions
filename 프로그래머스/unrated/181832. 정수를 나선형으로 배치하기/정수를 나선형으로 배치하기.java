class Solution {
    public int[][] solution(int n) {
        int[][] answer = {};
        answer = new int[n][n];
        int cnt = 1;
        
        for(int i = 0; i < n; i++){
            answer[0][i] = cnt++;
        }
        // 시작 지점
        int x = 0, y = n - 1;
        
        int dx = 1;
        int dy = -1;
        for(int i = n - 1; i > 0; i--){
            // i: 전개할 길이를 의미
            
            for(int j = 0; j < i; j++){
                x += dx;
                answer[x][y] = cnt++;
            }
            dx *= -1; // 다음 이동을 위해 방향을 반대로 전환
            
            for(int j = 0; j < i; j++){
                y += dy;
                answer[x][y] = cnt++;
            }
            dy *= -1; // 마찬가지
        }
        
        return answer;
    }
}