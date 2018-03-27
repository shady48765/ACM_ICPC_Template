import java.io.*;
import java.math.*;
import java.util.*;

public class a {
	class Transformation {
		Transformation(BigInteger a, BigInteger b) {
			this.a = a;
			this.b = b;
		}

		BigInteger a, b;
	}

	public void run() throws IOException {
		BigInteger n = new BigInteger(reader.readLine());
		List <Transformation> transformations = new ArrayList <Transformation>();
		transformations.add(new Transformation(BigInteger.ONE, BigInteger.ZERO));
		BigInteger TWO = BigInteger.valueOf(2);
		while (true) {
			Transformation last = transformations.get(transformations.size() - 1);
			if (last.a.add(last.b).compareTo(n) > 0) {
				break;
			}
			transformations.add(new Transformation(last.a.multiply(TWO), last.b.multiply(TWO).add(TWO)));
		}
		BigInteger result = BigInteger.ZERO;
		for (int length = 1; length < transformations.size(); ++ length) {
			// a * x + b >= n + 1
			Transformation t = transformations.get(length);
			BigInteger low = BigInteger.ONE;
			if (t.a.add(t.b).compareTo(n) <= 0) {
				low = n.add(t.a).subtract(t.b).divide(t.a);
			}
			t = transformations.get(length - 1);
			// a * x + b <= n
			BigInteger high = n.subtract(t.b).divide(t.a);
			BigInteger count = high.add(BigInteger.ONE).divide(TWO).subtract(low.divide(TWO));
			if (low.compareTo(TWO) <= 0 && high.compareTo(TWO) >= 0) {
				count = count.add(BigInteger.ONE);
			}
			result = result.add(count.multiply(BigInteger.valueOf(length + 1 >> 1)));
		}
		writer.println(result);
		writer.close();
	}

	a() {
		reader = new BufferedReader(new InputStreamReader(System.in));
		writer = new PrintWriter(System.out);
	}

	public static void main(String[] args) throws IOException {
		new a().run();
	}

	private static void debug(Object...os) {
		System.err.println(Arrays.deepToString(os));
	}

	private BufferedReader reader;
	private PrintWriter writer;
}
