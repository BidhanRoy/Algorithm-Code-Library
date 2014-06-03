struct convexHull3D {
	#define MAXN 400
	struct face {
		//Said convex surface of a three-point packet number
		int a, b, c;
		//Indicates that the plane belongs to the final surface on the convex hull
		bool ok;
	};
	//The initial vertices
	int n;
	//Initial vertex
	Point P[MAXN];
	//The number of convex hull surface triangle
	int num;
	//Triangular convex hull surface
	face F[8 * MAXN];
	//Triangular convex hull surface
	int g[MAXN][MAXN];
	//Vector length
	double vlen(Point a) {
		return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	}
	//Take a fork
	Point cross(const Point &a, const Point &b, const Point &c) {
		return Point((b.y - a.y) * (c.z - a.z) - (b.z - a.z) * (c.y - a.y),
		(b.z - a.z) * (c.x - a.x) - (b.x - a.x) * (c.z - a.z),
		(b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));
	}
	//Triangle Area * 2
	double area(Point a, Point b, Point c) { return vlen((b - a) * (c - a)); }
	//Directed tetrahedron volume * 6
	double volume(Point a, Point b, Point c, Point d) { return (b - a) * (c - a) ^ (d - a); }
	//Positive: point in the same direction as the surface
	double dblcmp(Point &p, face &f) {
		Point m = P[f.b] - P[f.a];
		Point n = P[f.c] - P[f.a];
		Point t = p - P[f.a];
		return (m * n) ^ t;
	}
	void deal(int p, int a, int b) {
		int f = g[a][b]; //Another plane searching the adjacent side
		face add;
		if (F[f].ok) {
			if (dblcmp(P[p], F[f]) > eps)
			dfs(p, f);
			else {
				add.a = b;
				add.b = a;
				add.c = p; //Note here that the order to a right-handed
				add.ok = true;
				g[p][b] = g[a][p] = g[b][a] = num;
				F[num++] = add;
			}
		}
	}
	void dfs(int p, int now) {
		//Recursive search of all should be removed from 
		//the inner surface of the convex hull
		F[now].ok = 0;
		deal(p, F[now].b, F[now].a);
		deal(p, F[now].c, F[now].b);
		deal(p, F[now].a, F[now].c);
	}
	bool same(int s, int t) {
		Point &a = P[F[s].a];
		Point &b = P[F[s].b];
		Point &c = P[F[s].c];
		return fabs(volume(a, b, c, P[F[t].a])) < eps
		&& fabs(volume(a, b, c, P[F[t].b])) < eps
		&& fabs(volume(a, b, c, P[F[t].c])) < eps;
	}
	//Construction of three-dimensional convex hull
	void create() {
		int i, j, tmp;
		face add;
		num = 0;
		if (n < 4) return;
		//**********************************************
		//This section is to ensure that the first four non-coplanar points
		bool flag = true;
		for (i = 1; i < n; i++) {
			if (vlen(P[0] - P[i]) > eps) {
				swap(P[1], P[i]);
				flag = false;
				break;
			}
		}
		if (flag) return;
		flag = true;
		//So that the first three points are not collinear
		for (i = 2; i < n; i++) {
			if (vlen((P[0] - P[1]) * (P[1] - P[i])) > eps) {
				swap(P[2], P[i]);
				flag = false;
				break;
			}
		}
		if (flag) return;
		flag = true;
		//Not four points of the front face
		for (int i = 3; i < n; i++) {
			if (fabs((P[0] - P[1]) * (P[1] - P[2]) ^ (P[0] - P[i])) > eps) {
				swap(P[3], P[i]);
				flag = false;
				break;
			}
		}
		if (flag) return;
		//*****************************************
		for (i = 0; i < 4; i++) {
			add.a = (i + 1) % 4;
			add.b = (i + 2) % 4;
			add.c = (i + 3) % 4;
			add.ok = true;
			if (dblcmp(P[i], add) > 0)
			swap(add.b, add.c);
			g[add.a][add.b] = g[add.b][add.c] = g[add.c][add.a] = num;
			F[num++] = add;
		}
		for (i = 4; i < n; i++) {
			for (j = 0; j < num; j++) {
				if (F[j].ok && dblcmp(P[i], F[j]) > eps) {
					dfs(i, j);
					break;
				}
			}
		}
		tmp = num;
		for (i = num = 0; i < tmp; i++)
		if (F[i].ok)
		F[num++] = F[i];
	}
	//Surface
	double area() {
		double res = 0;
		if (n == 3) {
			Point p = cross(P[0], P[1], P[2]);
			res = vlen(p) / 2.0;
			return res;
		}
		for (int i = 0; i < num; i++)
		res += area(P[F[i].a], P[F[i].b], P[F[i].c]);
		return res / 2.0;
	}
	double volume() {
		double res = 0;
		Point tmp(0, 0, 0);
		for (int i = 0; i < num; i++)
		res += volume(tmp, P[F[i].a], P[F[i].b], P[F[i].c]);
		return fabs(res / 6.0);
	}
	//The number of surface triangles
	int triangle() { return num; }
	//The number of polygons surface
	int polygon() {
		int i, j, res, flag;
		for (i = res = 0; i < num; i++) {
			flag = 1;
			for (j = 0; j < i; j++)
			if (same(i, j)) {
				flag = 0;
				break;
			}
			res += flag;
		}
		return res;
	}
	//Three-dimensional convex hull focus
	Point barycenter() {
		Point ans(0, 0, 0), o(0, 0, 0);
		double all = 0;
		for (int i = 0; i < num; i++) {
			double vol = volume(o, P[F[i].a], P[F[i].b], P[F[i].c]);
			ans = ans + (o + P[F[i].a] + P[F[i].b] + P[F[i].c]) / 4.0 * vol;
			all += vol;
		}
		ans = ans / all;
		return ans;
	}
	//Point to the plane distance
	double ptoface(Point p, int i) {
		return fabs( volume(P[F[i].a], P[F[i].b], P[F[i].c], p)
		/ vlen((P[F[i].b] - P[F[i].a]) * (P[F[i].c] - P[F[i].a])));
	}
	#undef MAXN
};
