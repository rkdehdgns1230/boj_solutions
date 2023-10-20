import java.util.*;

class Solution {
    private static int[] d = new int[160001];
    private static final int INF = 32001;
    
    // 최소 8개를 넘어가는 경우 -1을 반환하기 때문에, 더 따질 필요없다.
    private static Set<Integer>[] set = new Set[9];
    
    void dp(int x, int num){
        // 2개의 num으로 만들 수 있는 수
        set[2].add(num + num);
        set[2].add(num * num);
        set[2].add(num / num);
        set[2].add(0);
        
        int tmp = num;
        for(int i = 1; i <= 8; i++){
            set[i].add(tmp);
            tmp *= 10;
            tmp += num;
        }
        
        // 3개 부터는 이전 수들의 조합을 결합해서 만들어야 한다.
        for(int i = 3; i <= 8; i++){
            
            // j, i - j 조합으로 만들 수 있는 수 -> i개의 num으로 만들 수 있는 케이스에 해당
            for(int j = 1; j < i; j++){
                for(int cur1 : set[j]){
                    for(int cur2 : set[i - j]){
                        set[i].add(cur1 + cur2);
                        set[i].add(cur1 - cur2);
                        set[i].add(cur1 * cur2);
                        if(cur2 != 0)
                            set[i].add(cur1 / cur2);
                    }
                }
                
            }
        }
        
        return;
    }
    
    public int solution(int N, int number) {
        int answer = -1;
        
        for(int i = 1; i < 9; i++)
            set[i] = new HashSet<>();
        
        dp(number, N);
        
        for(int i = 1; i <= 8; i++){
            if(set[i].contains(number)){
                answer = i;
                break;
            }
        }
        
        return answer;
    }
}