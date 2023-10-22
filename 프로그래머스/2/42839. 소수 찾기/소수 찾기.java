import java.io.*;
import java.util.*;

class Solution {
    
    private static final int INF = 100000000;
    private static boolean[] is_prime = new boolean[INF];
    private static int picked_number = 0;
    private static int answer = 0;
    private static boolean[] visited;
    private static Set<Integer> rs = new HashSet<>();
    
    private void thieve_of_eratosthenes(){
        for(int i = 2; i < Math.sqrt(INF); i++){
            if(!is_prime[i]) continue;
            
            for(int j = i + i; j < INF; j += i){
                is_prime[j] = false;
            }
        }
    }
    
    public int solution(String numbers) {
        for(int i = 0; i < INF; i++){
            is_prime[i] = true;
        }
        is_prime[0] = false;
        is_prime[1] = false;
        is_prime[2] = true;
        is_prime[3] = true;
        
        thieve_of_eratosthenes();
        visited = new boolean[numbers.length()];
        for(int i = 0; i < visited.length; i++){
            visited[i] = false;
        }
        
        for(int i = 1; i <= numbers.length(); i++){
            backtracking(0, i, numbers);
        }
        answer = rs.size();
        return answer;
    }
    
    private void backtracking(int cnt, int k, String numbers){
        if(cnt == k){
            if(is_prime[picked_number]){
                rs.add(picked_number);
                //System.out.println(picked_number);
            }
            return;
        }
        
        for(int i = 0; i < numbers.length(); i++){
            if(visited[i]) continue;
            visited[i] = true;
            picked_number *= 10;
            picked_number += (numbers.charAt(i) - '0');
            backtracking(cnt + 1, k, numbers);
            picked_number /= 10;
            visited[i] = false;
        }
    }
}