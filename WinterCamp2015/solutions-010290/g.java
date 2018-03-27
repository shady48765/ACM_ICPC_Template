import java.io.*;
import java.math.*;
import java.util.*;

class Poly {
	static int DEGREE;

	Poly() {
		coef = new BigInteger[DEGREE + 1];
		Arrays.fill(coef, BigInteger.ZERO);
	}

	void set(int idx, BigInteger val) {
		coef[idx] = val;
	}

	BigInteger get(int idx) {
		return coef[idx];
	}

	Poly subtract(Poly rhs) {
		Poly res = new Poly();
		for (int i = 0; i <= DEGREE; ++ i) {
			res.set(i, get(i).subtract(rhs.get(i)));
		}
		return res;
	}

	Poly multiply(Poly rhs) {
		Poly res = new Poly();
		for (int i = 0; i <= DEGREE; ++ i) {
			for (int j = 0; i + j <= DEGREE; ++ j) {
				res.set(i + j, res.get(i + j).add(get(i).multiply(rhs.get(j))));
			}
		}
		return res;
	}

	BigInteger[] coef;
}

class Fraction {
	Fraction(BigInteger p, BigInteger q) {
		BigInteger g = p.gcd(q);
		this.p = p.divide(g);
		this.q = q.divide(g);
	}

	Fraction add(Fraction rhs) {
		return new Fraction(p.multiply(rhs.q).add(q.multiply(rhs.p)), q.multiply(rhs.q));
	}

	BigInteger p, q;
}

public class g {
	public void run() {
		int n = reader.nextInt();
		int m = reader.nextInt();
		Poly.DEGREE = m;
		boolean[][] graph = new boolean[n][n];
		for (int i = 0; i < m; ++ i) {
			int a = reader.nextInt() - 1;
			int b = reader.nextInt() - 1;
			graph[a][b] = graph[b][a] = true;
		}
		int[][] cut = new int[1 << n][1 << n];
		for (int mskA = 0; mskA < 1 << n; ++ mskA) {
			for (int mskB = 0; mskB < 1 << n; ++ mskB) {
				if ((mskA & mskB) == 0) {
					for (int i = 0; i < n; ++ i) {
						if ((mskA >> i & 1) == 1) {
							for (int j = 0; j < n; ++ j) {
								if ((mskB >> j & 1) == 1 && graph[i][j]) {
									cut[mskA][mskB] ++;
								}
							}
						}
					}
				}
			}
		}
		Poly one = new Poly();
		one.set(0, BigInteger.ONE);
		Poly[] neg = new Poly[m + 2];
		neg[0] = one;
		neg[1] = new Poly();
		neg[1].set(0, BigInteger.ONE);
		neg[1].set(1, BigInteger.ONE.negate());
		for (int i = 2; i <= m; ++ i) {
			neg[i] = neg[i - 1].multiply(neg[1]);
		}
		Poly[] conn = new Poly[1 << n];
		for (int msk = 0; msk < 1 << n; ++ msk) {
			conn[msk] = one;
			int lb = msk & -msk;
			for (int sub = msk; sub > 0; sub = sub - 1 & msk) {
				if ((sub & lb) == 0) {
					int cc = cut[sub][msk ^ sub];
					conn[msk] = conn[msk].subtract(conn[msk ^ sub].multiply(neg[cc]));
				}
			}
		}
		Fraction res = new Fraction(BigInteger.ZERO, BigInteger.ONE);
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < i; ++ j) {
				if (graph[i][j]) {
					for (int msk = 0; msk < 1 << n; ++ msk) {
						if ((msk >> i & 1) == 1 && (msk >> j & 1) == 0) {
							Poly poly = conn[msk].multiply(neg[cut[msk][(1 << n) - 1 ^ msk] - 1]);
							for (int k = 0; k < m; ++ k) {
								res = res.add(new Fraction(poly.get(k), BigInteger.valueOf(k + 2)));
							}
						}
					}
				}
			}
		}
		writer.println(String.format("%d/%d", res.p, res.q));
		writer.close();
	}

	g() {
		reader = new InputReader(System.in);
		writer = new PrintWriter(System.out);
	}

	public static void main(String[] args) {
		new g().run();
	}

	private static void debug(Object...os) {
		System.err.println(Arrays.deepToString(os));
	}

	private InputReader reader;
	private PrintWriter writer;
}

class InputReader {
	public InputReader(InputStream stream) {
		this.stream = stream;
	}

	public int nextChar() {
		if (charCount == -1) {
			throw new InputMismatchException();
		}
		if (head >= charCount) {
			head = 0;
			try {
				charCount = stream.read(buffer);
			} catch (IOException e) {
				throw new InputMismatchException();
			}
			if (charCount <= 0) {
				return -1;
			}
		}
		return buffer[head ++];
	}

	public int nextInt() {
		int c = nextChar();
		while (isSpaceChar(c)) {
			c = nextChar();
		}
		int sign = 1;
		if (c == '-') {
			sign = -1;
			c = nextChar();
		}
		int result = 0;
		do {
			if (c < '0' || c > '9')
				throw new InputMismatchException();
			result *= 10;
			result += c - '0';
			c = nextChar();
		} while (!isSpaceChar(c));
		return sign * result;
	}

	public boolean isSpaceChar(int c) {
		return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
	}

	private InputStream stream;
	private int head, charCount;
	private byte[] buffer = new byte[1024];
}
