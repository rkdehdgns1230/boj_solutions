class Solution {
    public int[] solution(int[] answers) {
        int[] answer = {};
        
        int[] score = {0, 0, 0};
        
        int pick2 = 1;
        int pick_arr[] = {3, 1, 2, 4, 5};
        int pick3 = 0;
        
        for(int i = 0; i < answers.length; i++){
            // 수포자1의 방식
            if(answers[i] == (i % 5 + 1)){
                score[0]++;
            }
            
            // 수포자2의 방식 
            if((i % 2 == 0 && answers[i] == 2) || (i % 2 == 1 && answers[i] == pick2)){
                score[1]++;
            }
            
            if(i % 2 == 1){
                pick2++;
                if(pick2 == 2) pick2++;
                else if(pick2 == 6) pick2 = 1;
            }
            
            // 수포자3의 방식
            if(answers[i] == pick_arr[pick3]){
                score[2]++;
            }
            System.out.print(pick2 + " ");
            if(i % 2 == 1){
                pick3++;
                pick3 %= 5;
            }
        }
        
        int max_score = (score[0] >= score[1]) ? score[0] : score[1];
        max_score = (max_score >= score[2]) ? max_score : score[2];
        int length = 0;
        for(int i = 0; i < 3; i++){
            if(max_score == score[i]){
                length++;
            }
        }
        answer = new int[length];
        int idx = 0;
        for(int i = 0; i < 3; i++){
            System.out.println(score[i]);
            if(max_score == score[i]){
                answer[idx++] = i + 1;
            }
        }
        
        return answer;
    }
}