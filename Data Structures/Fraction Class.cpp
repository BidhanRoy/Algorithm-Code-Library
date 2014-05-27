class Fraction {
public:
    long long N,D;
    Fraction(long long num=0, long long den=1) : N(num), D(den) {
        long long tmp = __gcd(N,D);
        if ((tmp < 0) != (den < 0))
            tmp = -tmp;
        N /= tmp;
        D /= tmp;
    }
    bool operator<(const Fraction& b) const {
        return (N*b.D < b.N*D);
    }
    bool operator==(const Fraction& b) const {
        return (N == b.N && D == b.D);
    }
    bool operator!=(const Fraction& b) const {
        return (N != b.N || D != b.D);
    }
    Fraction operator+(const Fraction& b) const {
        return Fraction(N*b.D + D*b.N, D*b.D);
    }
    Fraction operator-(const Fraction& b) const {
        return Fraction(N*b.D - D*b.N, D*b.D);
    }
    Fraction operator*(const Fraction& b) const {
        return Fraction(N*b.N, D*b.D);
    }
    Fraction operator/(const Fraction& b) const {
        return Fraction(N*b.D, D*b.N);
    }
};
ostream& operator<<(ostream& out, Fraction& f) {
    out << f.N;
    if (f.D > 1)
        out << "/" << f.D;
    return out;
}
