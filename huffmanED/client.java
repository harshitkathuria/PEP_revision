package huffmanED;

public class client {
    public static void main(String[] args) {
        
        huffman hed = new huffman("aabbccdeeffghghgiijjklmnopqrstuvwxyzjnasadpoewihiuwmcncajnnzlaqwqioqiejfwnslallakfoa");
        
        String en = hed.encodeString("harshit");
        String de = hed.decodeString(en);

        System.out.println(en + " -> " + de);
    }
}