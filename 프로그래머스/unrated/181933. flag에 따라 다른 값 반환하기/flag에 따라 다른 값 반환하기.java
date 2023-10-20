import java.io.*;
import java.util.*;

class Solution {
    public int solution(int a, int b, boolean flag) {
        int answer = 0;
        
        if(flag)
            answer =  a + b;
        else
            answer = a - b;
        
        return answer;
    }
}