package hashmap;

import java.util.ArrayList;
import java.util.HashMap;

public class ques {
    public static void main(String[] args) {
        // question_01("ajsnajnsjansjlnksnaajsjn");
        // question_02("harshitkathuria");

        int[] one = {1, 1, 2, 3, 4, 4};
        int[] two = {1, 1, 2, 2, 3};

        getCommomComponents(one, two);
    }

    public static void question_01(String str){
        HashMap<Character, ArrayList<Integer>> map = new HashMap<>();
        for(int i = 0; i < str.length(); i++){
        
            if(!map.containsKey(str.charAt(i)))
                map.put(str.charAt(i), new ArrayList<>());

            map.get(str.charAt(i)).add(i);
            
        }
        for(char ch : map.keySet()){
            System.out.println(ch + " -> " + map.get(ch));
        }
    }

    public static void question_02(String str){
        HashMap<Character, Integer> map = new HashMap<>();
        for(int i = 0; i < str.length(); i++){
            char ch = str.charAt(i);

            // if(map.containsKey(ch)){
            //     map.put(ch, map.get(ch) + 1);
            // }
            // else{
            //     map.put(ch, 1);
            // }

            map.put(ch, map.getOrDefault(ch, 0) + 1);
        }

        for(char ch : map.keySet()){
            System.out.println(ch + " -> " + map.get(ch));
        }
    }

    public static void getCommomComponents(int[] one, int[] two){
        
        HashMap<Integer, Boolean> map = new HashMap<>();
        for(int ele : one){
            if(!map.containsKey(ele)){
                map.put(ele, true);
            }
        }

        for(int ele : two){
            if(map.containsKey(ele)){
                if(map.get(ele))
                System.out.print(ele + " ");
                map.put(ele, false);
            }
        }
    }
}