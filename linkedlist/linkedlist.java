package linkedlist;

import java.util.NoSuchElementException;

public class linkedlist {

    private class Node{
        int data = 0;
        Node next = null;

        Node(int data){
            this.data = data;
        }
    }

    private Node head = null;
    private Node tail = null;
    private int nodeCount = 0;

    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("[");
        
        Node curr = this.head;
        while(curr != null){
            sb.append(curr.data + ", ");
            curr = curr.next;
        }

        sb.deleteCharAt(sb.length() - 1);
        sb.deleteCharAt(sb.length() - 1);
        sb.append("]");

        return sb.toString();
    }

    public int size(){
        return this.nodeCount;
    }

    public boolean isEmpty(){
        return this.nodeCount == 0;
    }

    public Node getNodeAt(int idx){
        if(idx < 0 || idx > this.nodeCount){
            throw new NullPointerException();
        }

        Node curr = this.head;
        while(idx-- > 0){
            curr = curr.next;
        }
        return curr;
    }

    //ADD.........................................................
    private void addFirst(Node node){

        if(this.nodeCount == 0){
            this.tail = node;
        }

        node.next = this.head;
        this.head = node;

        this.nodeCount++;
    }

    public void addFirst(int data){
        Node node = new Node(data);
        addFirst(node);
    }

    private void addLast(Node node){

        if(this.nodeCount == 0){
            this.head = node;
            this.tail = node;
        }
        else{
            this.tail.next = node;
            this.tail = node;
        }

        this.nodeCount++;
    }

    public void addLast(int data){
        Node node = new Node(data);
        addLast(node);
    }

    private void addAt_(int idx, Node node){

        if(idx == 0){
            addFirst(node);
        }

        if(idx == this.nodeCount - 1){
            addLast(node);
        }

        Node prev = getNodeAt(idx - 1);
        Node forw = getNodeAt(idx);

        prev.next = node;
        node.next = forw;
        this.nodeCount++;
    }

    public void addAt(int idx, int data){
        if(idx < 0 || idx > this.nodeCount){
            throw new NullPointerException();
        }
        
        Node node = new Node(data);
        addAt_(idx, node);
    }

    //Get...........................................................
    public Node getFirst_(){
        return this.head;
    }

    private int getFirst(){
        if(this.nodeCount == 0){
            throw new NoSuchElementException();
        }
        return getFirst_().data;
    }

    public Node getLast_(){
        return this.tail;
    }

    private int getLast(){
        if(this.nodeCount == 0){
            throw new NoSuchElementException();
        }
        return getLast_().data;
    }

    public Node getAt_(int idx){
        return getNodeAt(idx);
    }

    private int getAt(int idx){
        return getAt_(idx).data;
    }

    //Remove.........................................................
    private Node removeFirst_(){

        Node curr = this.head;
        if(this.nodeCount == 1){
            this.head = null;
            this.tail = null;
        }
        else{
            this.head = this.head.next; 
        }
        
        this.nodeCount--;
        return curr;
    }

    public int removeFirst(){
        if(this.nodeCount == 1){
            throw new NoSuchElementException();
        }
        return removeFirst_().data;
    }

    private Node removeLast_(){
        
        Node curr = this.tail;

        if(this.nodeCount == 0){
            this.head = null;
            this.tail = null;
        }
        else{
            this.tail = getNodeAt(this.nodeCount - 2);
            this.tail.next = null;
        }
        
        this.nodeCount--;
        return curr;
    }

    public int removeLast(){
        if(this.nodeCount == 0){
            throw new NoSuchElementException();
        }
        return removeLast_().data;
    }

    private Node removeAt_(int idx){

        if(idx == 0){
            return removeFirst_();
        }

        if(idx == this.nodeCount - 1){
            return removeLast_();
        }

        Node prev = getNodeAt(idx - 1);
        Node curr = prev.next;
        Node forw = curr.next;

        prev.next = forw;
        curr.next = null;
        this.nodeCount--;

        return curr;
    }

    public int removeAt(int idx){
        if(idx < 0 || idx > this.nodeCount){
            throw new NullPointerException();
        }
        return removeAt_(idx).data;
    }

    //reverse a linked list

    private Node reverseList_(Node node){ // O(n)

        Node prev = null;
        Node curr = this.head;
        Node forw = this.head;

        while(forw != null){

            forw = curr.next;   //backup for curr.next
            curr.next = prev;   //reversing

            prev = curr;
            curr = forw;
        }
        return prev;
    }

    public void reverseList(){
        Node temp = this.head;
        this.head = reverseList_(this.head);
        this.tail = temp;
    }

}