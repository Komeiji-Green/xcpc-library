import java.math.BigInteger;
import java.util.Scanner;

public class QHD {
    private static Scanner sc = new Scanner(System.in);
    public static void solve() {
        BigInteger n = sc.nextBigInteger();
        BigInteger m = sc.nextBigInteger();
        BigInteger one = BigInteger.valueOf(1);
        BigInteger ans = BigInteger.valueOf(0);
        BigInteger a1 = m.shiftLeft(1); // 左移
        BigInteger a2 = m.shiftRight(1); // 右移
        BigInteger a3 = m.multiply(n); // 乘
        BigInteger a4 = m.divide(n); // 除
        BigInteger a5 = m.subtract(n); // 减
        BigInteger a6 = m.add(n); // 加
        BigInteger a7 = m.mod(n); // 模
        
        String ns = n.toString();
        String s = "114514";
        s.substring(1, 3); // -> 145
        
        StringBuilder sb = new StringBuilder(ns);
        sb.append('1');
    }
    public static void main(String[] args) {
        int t = sc.nextInt();
        for(int cas = 1; cas <= t; cas++) {
            solve();
        }
    }
}