package Heap;

public class client {
    
    public static void main(String[] args) {
        
        int[] arr = {10, 20, 30, 40, 50};
        
        heap obj = new heap(arr);
        obj.display();
        obj.push(45);
        obj.pop();
        obj.update(3, 60);
        obj.display();
    }
}