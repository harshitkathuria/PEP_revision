package hashmap;

import java.util.ArrayList;
import java.util.LinkedList;

public class hashmap_ <K, V>{
    
    public class Node{
        K key;
        V value;

        Node(K key, V value){
            this.key = key;
            this.value = value;
        }

        @Override
        public String toString(){
            return this.key + " = " + this.value;
        }
    }

    private int size = 0;
    private LinkedList<Node>[] buckets = new LinkedList[10];

    public int myGroup(K key){
        return myHashCode(key) % buckets.length;
    }

    public int myHashCode(K key){
        return Math.abs(key.hashCode());
    }

    public void reAssign(){
        for(int i = 0; i < buckets.length; i++){
            buckets[i] = new LinkedList<>();
        }
    }

    public hashmap_(){
        reAssign();
    }

    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("{");

        for(int i = 0; i < buckets.length; i++){
            LinkedList<Node> group = buckets[i];
            if(group.size() > 0){
                int size = group.size();
                while(size-- > 0){
                    Node node = group.removeFirst();
                    sb.append(node + ", ");
                    group.addLast(node);
                }
            }
        }
        sb.deleteCharAt(sb.length() - 1);
        sb.deleteCharAt(sb.length() - 1);

        sb.append("}");

        return sb.toString();
    }

//..........................................................................

    public int size(){
        return this.size;
    }

    public boolean isEmpty(){
        return this.size == 0? true : false;
    }

    public void put(K key, V value){
        int code = myGroup(key);
        LinkedList<Node> group = buckets[code];

        Node node = foundInGroup(group, key);
    
        if(node != null){
            group.getFirst().value = value;
        }
        else{
            group.addLast(new Node(key,value));
            this.size++;
            
            double lambda = (1.0) * (group.size()) / buckets.length;
            if(lambda > 0.3){
                System.out.println("Rehash " + group.size());
                rehash();
            }
        }
    }

    public void rehash(){
        LinkedList<Node>[] oldbuckets = buckets;
        buckets = new LinkedList[2 * buckets.length];
        reAssign();

        for(int i = 0; i < oldbuckets.length; i++){
            if(oldbuckets[i].size() > 0){
                int size = oldbuckets[i].size();
                LinkedList<Node> list = oldbuckets[i];
                while(size-- > 0){
                    Node tnode = list.removeFirst();
                    put(tnode.key, tnode.value);
                }
            }
        }
    }

    public ArrayList<K> keySet(){

        if(isEmpty()){
            return new ArrayList<>();
        }
        
        ArrayList<K> keys = new ArrayList<>();
        
        for(int i = 0; i < buckets.length; i++){
            LinkedList<Node> list = buckets[i];
            if(list.size() > 0){
                int size = list.size();
                while(size-- > 0){
                    keys.add(list.getFirst().key);
                    list.addLast(list.removeFirst());
                }
            }
        }
        return keys;
    }

    public V getOrDefault(K key, V defaultValue){
        int code = myGroup(key);
        LinkedList<Node> group = buckets[code];
        Node node = foundInGroup(group, key);

        return node != null? node.value : defaultValue;
    }

    public V get(K key){
        int code = myGroup(key);
        LinkedList<Node> group = buckets[code];
        Node node = foundInGroup(group, key);

        return (node != null)? node.value : null;
    }

    public Node remove(K key){
        int code = myGroup(key);
        LinkedList<Node> group = buckets[code];
        
        Node node = foundInGroup(group, key);

        if(node != null){
            this.size--;
            return group.removeFirst();
        }
        else{
            System.out.println("Element not found: -1");
            return null;
        }
    }

    public Node foundInGroup(LinkedList<Node> group, K key){
        
        if(group == null){
            return null;
        }

        int s = group.size();
        while(s-- > 0){
            if(group.getFirst().key == key){
                return group.getFirst();
            }
            else{
                group.addLast(group.removeFirst());
            }
        }
        return null;
    } 

    public boolean containsKey(K key){
        int code = myGroup(key);
        LinkedList<Node> group = buckets[code];

        Node node = foundInGroup(group, key);

        return (node == null)? false : true;
    }

}