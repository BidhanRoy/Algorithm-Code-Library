struct Point {
	double x, y, z;
	Point() {}

	Point(double xx, double yy, double zz) : x(xx), y(yy), z(zz) {}

	//The difference between the two vectors
	Point operator -(const Point p1) {
		return Point(x - p1.x, y - p1.y, z - p1.z);
	}

	//The sum of two vectors
	Point operator +(const Point p1) {
		return Point(x + p1.x, y + p1.y, z + p1.z);
	}

	//cross
	Point operator *(const Point p) {
		return Point(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
	}

	Point operator *(double d) {
		return Point(x * d, y * d, z * d);
	}

	Point operator /(double d) {
		return Point(x / d, y / d, z / d);
	}

	//Dot
	double operator ^(Point p) {
		return (x * p.x + y * p.y + z * p.z);
	}
};
