package linkedlist;

public class client {
    public static void main(String[] args) {
        linkedlist list = new linkedlist();

        list.addLast(10);
        list.addLast(20);
        list.addLast(30);
        list.addLast(40);
        list.addLast(50);
        list.addAt(2, 25);
        System.out.println(list);   //linklist ka toString call hoga
        
        // System.out.println(list.removeLast());
        // System.out.println(list.removeFirst());
        list.reverseList();

        System.out.println(list);
    }
}