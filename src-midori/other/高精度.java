import java.math.BigInteger;
import java.util.Scanner;

public class Xiaomi_final_E {

    public static Scanner sc = new Scanner(System.in);

    public static void solve() {
        BigInteger n = sc.nextBigInteger();
        BigInteger x = n.divide(BigInteger.valueOf(2));
        BigInteger y = n.subtract(x);
        StringBuilder a = new StringBuilder(x.toString());
        StringBuilder b = new StringBuilder(y.toString());
        StringBuilder c = new StringBuilder("");
        String sn = n.toString();
        if (a.toString().equals(b.toString())) {
            c.append(a);
        } else {
            if (sn.length() > 1 && sn.charAt(0) == '1' && n.mod(BigInteger.valueOf(11)).compareTo(BigInteger.valueOf(9)) <= 0) {
                BigInteger va = n.divide(BigInteger.valueOf(11));
                BigInteger vb = n.subtract(va);
                a = new StringBuilder(va.toString());
                b = new StringBuilder(vb.toString());
                c = new StringBuilder(va.toString());
            } else if (a.charAt(a.length() - 1) == '9') {
                int len = 0;
                char ch = '4';
                boolean flag = false;

                for (int i = a.length() - 1; i >= 0; i--) {
                    if (a.charAt(i) == '9')
                        ++len;
                    else
                        break;
                }

                if (len < a.length()) {
                    ch = a.charAt(a.length() - 1 - len);
                } else {
                    flag = true;
                }

                a = new StringBuilder(a.substring(0, a.length() - len));
                b = new StringBuilder(b.substring(0, b.length() - len));
                c = new StringBuilder("");

                for (int i = 0; i < a.length(); i++) {
                    if (a.charAt(i) == b.charAt(i))
                        c.append(a.charAt(i));
                    else
                        break;
                }

                for (int i = 0; i < len; i++) {
                    if (i % 2 == 0) {
                        a.append((char)('9' - ch + '0'));
                        b.append(ch);
                        if (i > 0 || !flag) c.append(ch);
                    } else {
                        a.append(ch);
                        b.append((char)('9' - ch + '0'));
                        c.append((char)('9' - ch + '0'));
                    }
                }
            } else {
                c = new StringBuilder(a.substring(0, a.length() - 1));
            }
        }
        if (c.length() == 0) c.append("-");
        System.out.println(a);
        System.out.println(b);
        System.out.println(c);
    }

    public static void main(String[] args) {
        int T = sc.nextInt();
        for (int i = 0; i < T; i++) solve();
    }
}
