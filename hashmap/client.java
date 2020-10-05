package hashmap;

public class client {
    public static void main(String[] args) {
        hashmap_<Integer, String> map = new hashmap_<>();
        map.put(19, "A");
        map.put(29, "B");
        map.put(39, "C");
        map.put(49, "D");

        // for(int keys : map.keySet()){
        //     System.out.print(keys + " ");
        // }

        System.out.println(map);

        System.out.println(map.get(29));
    }
}