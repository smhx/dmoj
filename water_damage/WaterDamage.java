/*input
2
4
3
..A.
#.#.
###A

2
4
3
..A.
#.#.
###A

2
4
3
..A.
#.#.
###A

4
4
3
..A.
#.#.
###A

5
4
3
..A.
#.#.
###A
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;
public class WaterDamage {
    public static void main(String[] args) throws IOException {
        Scanner scan = new Scanner(System.in);
        BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
        for(int x=0; x<5; x++) {
            // int w = Integer.parseInt(stdin.readLine());
            // int c = Integer.parseInt(stdin.readLine());
            // int r = Integer.parseInt(stdin.readLine());
            int w = scan.nextInt();
            int c = scan.nextInt();
            int r = scan.nextInt();
            char[][] m = new char[r][c];
            for (int i = 0; i < r; i++) {
                // String s = stdin.readLine();
                String s = scan.next();
                for (int j = 0; j < c; j++) {
                    m[i][j] = s.charAt(j);
                }
            }
            int res = 0;
            for (int i = 0; i < w; i++) {
                coord cur = new coord(0, 0);
                while (cur.r < r && cur.c < c) {
                    //System.out.println(cur.r + " " + cur.c);
                    if (cur.r != r - 1 && m[cur.r + 1][cur.c] != '#') {
                        cur.r = cur.r + 1;
                    } else if (cur.c != c - 1 && m[cur.r][cur.c + 1] != '#') {
                        cur.c = cur.c + 1;
                    } else {
                        if (m[cur.r][cur.c] == 'A') {
                            //System.out.println("added");
                            res++;
                        }
                        m[cur.r][cur.c] = '#';
                        break;
                    }
                }
            }
            System.out.println(res);
            // if(x!=4)stdin.readLine();
        }
    }
}
class coord{
    public int r, c;
    public coord(int r, int c) {
        this.r = r;
        this.c = c;
    }
}