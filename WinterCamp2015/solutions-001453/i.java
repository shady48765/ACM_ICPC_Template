import java.io.*;
import java.math.*;
import java.util.*;

public class i {
	static int UNIT_LENGTH = 1000000;

	public void run() {
		int n = reader.nextInt();
		int[][] intersection = new int[n][n];
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < n; ++ j) {
				intersection[i][j] = reader.nextInt();
			}
		}
		writer.println(solve(intersection) ? "Yes" : "No");
		writer.close();
	}

	int find(int[] parent, int u) {
		if (parent[u] == -1) {
			return u;
		}
		return parent[u] = find(parent, parent[u]);
	}

	boolean solve(int[][] intersection) {
		int n = intersection.length;
		int[] parent = new int[n];
		Arrays.fill(parent, -1);
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < n; ++ j) {
				if (intersection[i][j] == UNIT_LENGTH && find(parent, i) != find(parent, j)) {
					parent[find(parent, i)] = find(parent, j);
				}
			}
		}
		int m = 0;
		int[] id = new int[n];
		Arrays.fill(id, -1);
		for (int i = 0; i < n; ++ i) {
			if (id[i] == -1) {
				for (int j = 0; j < n; ++ j) {
					if (find(parent, i) == find(parent, j)) {
						id[j] = m;
					}
				}
				m ++;
			}
		}
		int[][] newIntersection = new int[m][m];
		for (int i = 0; i < m; ++ i) {
			Arrays.fill(newIntersection[i], -1);
		}
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < n; ++ j) {
				if (newIntersection[id[i]][id[j]] != -1 && newIntersection[id[i]][id[j]] != intersection[i][j]) {
					return false;
				}
				newIntersection[id[i]][id[j]] = intersection[i][j];
			}
		}
		return check(newIntersection);
	}

	boolean check(int[][] intersection) {
		int n = intersection.length;
		int[] parent = new int[n];
		Arrays.fill(parent, -1);
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < n; ++ j) {
				if (intersection[i][j] > 0 && find(parent, i) != find(parent, j)) {
					parent[find(parent, i)] = find(parent, j);
				}
			}
		}
		boolean[] visited = new boolean[n];
		for (int i = 0; i < n; ++ i) {
			if (!visited[i]) {
				List <Integer> vertices = new ArrayList <Integer>();
				for (int j = 0; j < n; ++ j) {
					if (find(parent, i) == find(parent, j)) {
						visited[j] = true;
						vertices.add(j);
					}
				}
				int m = vertices.size();
				int[][] newIntersection = new int[m][m];
				for (int j = 0; j < m; ++ j) {
					for (int k = 0; k < m; ++ k) {
						newIntersection[j][k] = intersection[vertices.get(j)][vertices.get(k)];
					}
				}
				if (!check2(newIntersection)) {
					return false;
				}
			}
		}
		return true;
	}

	int getIntersection(int x, int y) {
		return Math.max(UNIT_LENGTH - Math.abs(x - y), 0);
	}

	boolean check2(int[][] intersection) {
		int n = intersection.length;
		if (n <= 1) {
			return true;
		}
		int p = 1;
		while (intersection[0][p] == 0) {
			p ++;
		}
		boolean[] visited = new boolean[n];
		visited[0] = visited[p] = true;
		Queue <Integer> queue = new LinkedList <Integer>();
		queue.offer(0);
		queue.offer(p);
		int[] position = new int[n];
		int[] co = new int[n];
		position[0] = 0;
		position[p] = intersection[0][p] - UNIT_LENGTH;
		co[0] = p;
		co[p] = 0;
		while (!queue.isEmpty()) {
			int u = queue.poll();
			for (int v = 0; v < n; ++ v) {
				if (!visited[v] && intersection[u][v] > 0) {
					position[v] = position[u] - (UNIT_LENGTH - intersection[u][v]);
					if (getIntersection(position[v], position[co[u]]) != intersection[v][co[u]]) {
						position[v] = position[u] + UNIT_LENGTH - intersection[u][v];
					}
					co[v] = u;
					visited[v] = true;
					queue.offer(v);
				}
			}
		}
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < n; ++ j) {
				if (getIntersection(position[i], position[j]) != intersection[i][j]) {
					return false;
				}
			}
		}
		return true;
	}

	i() {
		reader = new InputReader(System.in);
		writer = new PrintWriter(System.out);
	}

	public static void main(String[] args) {
		new i().run();
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
