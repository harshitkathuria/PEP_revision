package recursion;

public class nqueens{

    static int[][] dir = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

    public static boolean IsSafeToPlaceQueen(int x, int y, boolean[][] board){
        
        for(int i = 0; i < dir.length; i++){
            for(int rad = 1; rad <= Math.max(x, y); rad++){

                int r = x + rad * dir[i][0];
                int c = y + rad * dir[i][1];

                if(r < 0 || c < 0 || r >= board.length || c >= board[0].length)
                    break;
                if(board[r][c]){
                    return false;
                }
            }
        }
        return true;
    }

    public static int nQueens(boolean[][] board, int qpsf, int tnq, int lpql, String asf){
        
        if(qpsf == tnq){
            System.out.println(asf);
            return 1;
        }
        
        int count = 0;
        for(int i = lpql; i < board.length * board[0].length; i++){
            
            int x = i / board[0].length;
            int y = i % board[0].length;

            if(IsSafeToPlaceQueen(x, y, board)){
                board[x][y] = true;
                count += nQueens(board, qpsf + 1, tnq, i + 1, asf + "q" + (qpsf + 1) + ": (" + x + " " + y + ") ");
                board[x][y] = false;
            }
        }
        return count;
    }

    public static int nQueens_row(boolean[][] board, int row, int tnq, String asf){

        if(row == board.length || tnq == 0){
            if(tnq == 0){
                System.out.println(asf);
                return 1;
            }
            
            return 0;
        }

        int count = 0;
        for(int col = 0; col < board[0].length; col++){
            if(IsSafeToPlaceQueen(row, col, board)){
                board[row][col] = true;
                count += nQueens_row(board, row + 1, tnq - 1, asf + "q" + (row + 1) + ": (" + row + " " + col + ") ");
                board[row][col] = false;
            }
        }
        return count;
    }

    public static int nQueens_col(boolean[][] board, int col, int tnq, String asf){

        if(col == board[0].length || tnq == 0){
            if(tnq == 0){
                System.out.println(asf);
                return 1;
            }       
            return 0;
        }

        int count = 0;
        for(int row = 0; row < board.length; row++){
            if(IsSafeToPlaceQueen(row, col, board)){
                board[row][col] = true;
                count += nQueens_col(board, col + 1, tnq - 1, asf + "q" + (col + 1) + ": (" + row + " " + col + ") ");
                board[row][col] = false;
            }
        }
        return count;
    }

    public static void main(String args[]){

        boolean[][] board = new boolean[4][4];
        // System.out.println(nQueens(board, 0, 4, 0, ""));
        // System.out.println(nQueens_row(board, 0, 4, ""));
        System.out.println(nQueens_col(board, 0, 4, ""));
    }
}