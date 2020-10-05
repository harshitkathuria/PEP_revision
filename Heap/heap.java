package Heap;

import java.util.ArrayList;

public class heap {
    
    private ArrayList<Integer> arr;
    private boolean isMax = true;

    public heap(){
        this.arr = new ArrayList<>();
    }

    public heap(boolean isMax){
        this.isMax = isMax;
        this.arr = new ArrayList<>();
    }

    public void createHeap(int[] ar){

        this.arr = new ArrayList<>();
        for(int ele : ar){
            arr.add(ele);
        }

        for(int i = arr.size() - 1; i >= 0; i--){    //O(n) not O(nlogn)
            downheapify(i);
        }
    }

    public heap(int[] arr, boolean isMax){
        this.isMax = isMax;
        createHeap(arr);
    }

    public heap(int[] arr){
        createHeap(arr);
    }

    //util.....................................................

    public void display(){
        System.out.println(arr);
    }

    public int size(){
        return arr.size();
    }

    public void swap(int i, int j){
        int val1 = arr.get(i);
        int val2 = arr.get(j);

        arr.set(i, val2);
        arr.set(j, val1);
    }

    public void downheapify(int pi){
        
        int lci = (pi * 2) + 1;
        int rci = (pi * 2) + 2;
        int maxi = pi;

        if(lci < arr.size() && compareTo(lci, maxi) > 0){
            maxi = lci;
        }
        if(rci < arr.size() && compareTo(rci, maxi) > 0){
            maxi = rci;
        }

        if(maxi != pi){
            swap(maxi, pi);
            downheapify(maxi);
        }
    }

    public void upheapify(int ci){

        int pi = (ci - 1) / 2;
        int maxi = ci;

        if(pi >= 0  && arr.get(pi) < arr.get(maxi)){
            swap(pi, maxi);
            maxi = pi;
        }

        if(maxi != ci){
            upheapify(maxi);
        }
    }

    //API...............................................................

    public void push(int data){
        arr.add(data);
        upheapify(arr.size() - 1);
    }

    public void pop(){
        swap(0, arr.size() - 1);
        arr.remove(arr.size() - 1);
        downheapify(0);
    }

    public void update(int idx, int data){
        arr.set(idx, data);
        upheapify(idx);
        downheapify(idx);
    }

    public int compareTo(int ci, int pi){
        if(isMax){
            return arr.get(ci) - arr.get(pi);
        }
        else{
            return arr.get(pi) - arr.get(ci);
        }
    }
}