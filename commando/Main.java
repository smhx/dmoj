public class Main {

    static int pow(int b, int exp) {
        if (exp==0) return 1;
        int h = pow(b, exp/2);
        return ( (exp%2==1) ? b : 1) * h * h;
    }

    
    static int p(int b, int e) {
        dp = new List
        dp[1] = b;

        return 0;
    }
    public static void main(String[] args) {
        System.out.println(p(3, 4));

        // int a, b;
        // a = (a=a+b)-(b=a-b);
        // System.out.println(a);
        // System.out.println(b);
    }
}