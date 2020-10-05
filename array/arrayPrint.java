package array;

import java.util.Scanner;

public class arrayPrint {
    public static Scanner scn = new Scanner(System.in);

    public static void input(int[][] arr){
        for(int i = 0; i < arr.length; i++){
            for(int j = 0; j < arr[0].length; j++){
                arr[i][j] = scn.nextInt();
            }
        }
    }

    public static void display(int[][] arr){
        for(int[] ar : arr){
            for(int ele : ar){
                System.out.print(ele + " ");
            }
            System.out.println();
        }
    }

    public static void wave(int[][] arr){
        for(int i = 0; i < arr.length; i++){
            if(i % 2 == 0){
                for(int j = 0; j < arr[0].length; j++){
                    System.out.print(arr[i][j] + " ");
                }
            }
            else{
                for(int j = arr[0].length - 1; j >= 0; j--){
                    System.out.print(arr[i][j] + " ");
                }
            }
            System.out.println();
        }
    }

    public static void spiral(int[][] arr){
        int minr = 0, minc = 0, maxr = arr.length - 1, maxc = arr[0].length - 1;
        int no_element = (maxr + 1) * (maxc + 1);

        while(no_element-- > 0){

            for(int col = minc; col <= maxc; col++){
                System.out.print(arr[minr][col] + " ");
            }
            minr++;

            for(int row = minr; row <= maxr; row++){
                System.out.print(arr[row][maxc] + " ");
            }
            maxc--;

            for(int col = maxc; col >= minc; col--){
                System.out.print(arr[maxr][col] + " ");
            }
            maxr--;

            for(int row = maxr; row >= minr; row--){
                System.out.print(arr[row][minc] + " ");
            }
            minc++;
        }
    }

    public static void exitPoint(int[][] arr){
        int dir = 0, row = 0, col = 0;

        while(true){
            dir = (dir + arr[row][col]) % 4;

            if(dir == 0){
                col++;
                if(col == arr[0].length){
                    System.out.println(row + ", " + (col - 1));
                    break;
                }
            }
            else if(dir == 1){
                row++;
                if(row == arr.length){
                    System.out.println((row - 1) + ", " + col);
                    break;
                }
            }
            else if(dir == 2){
                col--;
                if(col == -1){
                    System.out.println(row + ", " + (col + 1));
                    break;
                }
            }
            else{
                row--;
                if(row == -1){
                    System.out.println((row + 1) + ", " + col);
                    break;
                }
            }
        }
    }

    public static void main(String args[]){
            
        // int[][] arr = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
        int[][] arr = {{0, 0, 0, 0, 1}, {1, 0, 0, 1, 0}, {0, 1, 1, 0, 0}, {0, 1, 0, 1, 0}, {1, 0, 0, 0, 1}};

        // input(arr);
        // wave(arr);
        // spiral(arr);
        exitPoint(arr);
    }
}