package huffmanED;

import java.util.HashMap;
import java.util.PriorityQueue;

public class huffman{
    
    private HashMap<String, String> encode = new HashMap<>();
    private HashMap<String, String> decode = new HashMap<>();

    private class Node implements Comparable<Node>{
        String data = "";
        int freq = 0;
        Node left = null;
        Node right = null;
        
        public Node(String data, int freq, Node left, Node right){
            this.data = data;
            this.freq = freq;
            this.left = left;
            this.right = right;
        }

        @Override
        public int compareTo(Node o) {
            return this.freq - o.freq;
        }
    }

    public huffman(String str){
        huffmanTree(str);
    }

    public void huffmanTree(String str){

        PriorityQueue<Node> pq = new PriorityQueue<>();
        int[] freq = new int[26];
        
        for(int i = 0; i < str.length(); i++){
            freq[str.charAt(i) - 'a']++;
        }

        for(int i = 0; i < freq.length; i++){
            if(freq[i] > 0)
                pq.add(new Node((char)('a' + i) + "", freq[i], null, null));
        }

        while(pq.size() > 1){
            Node n1 = pq.poll();
            Node n2 = pq.poll();

            pq.add(new Node(n1.data + n2.data, n1.freq + n2.freq, n1, n2));
        }
        Node root = pq.poll();
        huffmanTraversal(root, "");
    }

    public void huffmanTraversal(Node root, String binaryCode){
        
        // if(root == null){
        //     return;
        // }
        
        if(root.left == null && root.right == null){
            encode.put(root.data, binaryCode);
            decode.put(binaryCode, root.data);
            return;
        }
    
        huffmanTraversal(root.left, binaryCode + '0');
        huffmanTraversal(root.right, binaryCode + '1');
    }

    public String encodeString(String str){
        
        StringBuilder sb = new StringBuilder();
        for(int i = 0; i < str.length(); i++){
            sb.append(encode.get(str.charAt(i) + ""));
        }
        
        return sb.toString(); 
    }

    public String decodeString(String str){

        StringBuilder sb = new StringBuilder();
        int i = 0;
        for(int j = 1; j <= str.length(); j++){
            String s = str.substring(i, j);
            if(decode.containsKey(s) == true){
                sb.append(decode.get(s));
                i = j;
            }
        }

        return sb.toString();
    }
}