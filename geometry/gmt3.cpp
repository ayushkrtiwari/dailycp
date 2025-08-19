// https://codeforces.com/problemset/problem/166/B

#include<bits/stdc++.h>
using namespace std;
define int long long

template <class F>
struct Point {
    F x, y;
    Point() : x(0), y(0) {}
    Point(const F& x, const F& y) : x(x), y(y) {}

    void swap(Point& other) { using std::swap; swap(x, other.x); swap(y, other.y); }
    template <class F1> explicit operator Point<F1> () const {
        return Point<F1>(static_cast<F1>(x), static_cast<F1>(y)); }
    template <class F1> Point& operator = (const Point<F1>& other) {
        x = other.x; y = other.y; return *this; }
    template <class F1> Point& operator += (const Point<F1>& other) {
        x += other.x; y += other.y; return *this; }
    template <class F1> Point& operator -= (const Point<F1>& other) {
        x -= other.x; y -= other.y; return *this; }
    template <class F1> Point& operator *= (const F1& factor) {
        x *= factor; y *= factor; return *this; }
    template <class F1> Point& operator /= (const F1& factor) {
        x /= factor; y /= factor; return *this; }
};

template <class F> int read(Point<F>& point) { return read(point.x, point.y) / 2; }
template <class F> int write(const Point<F>& point) { return write(point.x, point.y); }

template <class F> istream& operator >> (istream& is, Point<F>& point) {
    return is >> point.x >> point.y; }
template <class F> ostream& operator << (ostream& os, const Point<F>& point) {
    return os << point.x << ' ' << point.y; }

template <class F> inline Point<F> makePoint(const F& x, const F& y) { return Point<F>(x, y); }
template <class F> void swap(Point<F>& lhs, Point<F>& rhs) { lhs.swap(rhs); }

#define FUNC1(name, arg, expr) \
template <class F> inline auto name(const arg) -> decltype(expr) { return expr; }
#define FUNC2(name, arg1, arg2, expr) \
template <class F1, class F2> \
inline auto name(const arg1, const arg2) -> decltype(expr) { return expr; }
#define FUNC3(name, arg1, arg2, arg3, expr) \
template <class F1, class F2, class F3> \
inline auto name(const arg1, const arg2, const arg3) -> decltype(expr) { return expr; }

FUNC1(operator -, Point<F>& point, makePoint(-point.x, -point.y))
FUNC2(operator +, Point<F1>& lhs, Point<F2>& rhs, makePoint(lhs.x + rhs.x, lhs.y + rhs.y))
FUNC2(operator -, Point<F1>& lhs, Point<F2>& rhs, makePoint(lhs.x - rhs.x, lhs.y - rhs.y))
FUNC2(operator *, F1& factor, Point<F2>& rhs, makePoint(factor * rhs.x, factor * rhs.y))
FUNC2(operator *, Point<F1>& lhs, F2& factor, makePoint(lhs.x * factor, lhs.y * factor))
FUNC2(operator /, Point<F1>& lhs, F2& factor, makePoint(lhs.x / factor, lhs.y / factor))

FUNC2(operator *, Point<F1>& lhs, Point<F2>& rhs, lhs.x * rhs.x + lhs.y * rhs.y)
FUNC2(operator ^, Point<F1>& lhs, Point<F2>& rhs, lhs.x * rhs.y - lhs.y * rhs.x)

// < 0 if rhs <- lhs counter-clockwise, 0 if collinear, > 0 if clockwise.
FUNC2(ccw, Point<F1>& lhs, Point<F2>& rhs, rhs ^ lhs)
FUNC3(ccw, Point<F1>& lhs, Point<F2>& rhs, Point<F3>& origin, ccw(lhs - origin, rhs - origin))

FUNC2(operator ==, Point<F1>& lhs, Point<F2>& rhs, lhs.x == rhs.x && lhs.y == rhs.y)
FUNC2(operator !=, Point<F1>& lhs, Point<F2>& rhs, !(lhs == rhs))

FUNC2(operator <, Point<F1>& lhs, Point<F2>& rhs,
    lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x))
FUNC2(operator >, Point<F1>& lhs, Point<F2>& rhs, rhs < lhs)
FUNC2(operator <=, Point<F1>& lhs, Point<F2>& rhs, !(lhs > rhs))
FUNC2(operator >=, Point<F1>& lhs, Point<F2>& rhs, !(lhs < rhs))

// Angles and rotations (counter-clockwise).
FUNC1(angle, Point<F>& point, atan2(point.y, point.x))
FUNC2(angle, Point<F1>& lhs, Point<F2>& rhs, atan2(lhs ^ rhs, lhs * rhs))
FUNC3(angle, Point<F1>& lhs, Point<F2>& rhs, Point<F3>& origin,
                angle(lhs - origin, rhs - origin))
FUNC3(rotate, Point<F1>& point, F2& angleSin, F3& angleCos,
      makePoint(angleCos * point.x - angleSin * point.y,
                angleSin * point.x + angleCos * point.y))
FUNC2(rotate, Point<F1>& point, F2& angle, rotate(point, sin(angle), cos(angle)))
FUNC3(rotate, Point<F1>& point, F2& angle, Point<F3>& origin,
                origin + rotate(point - origin, angle))
FUNC1(perp, Point<F>& point, makePoint(-point.y, point.x))

// Distances.
FUNC1(abs, Point<F>& point, point * point)
FUNC1(norm, Point<F>& point, sqrt(abs(point)))
FUNC2(dist, Point<F1>& lhs, Point<F2>& rhs, norm(lhs - rhs))
FUNC2(dist2, Point<F1>& lhs, Point<F2>& rhs, abs(lhs - rhs))
FUNC2(bisector, Point<F1>& lhs, Point<F2>& rhs, lhs * norm(rhs) + rhs * norm(lhs))

// #undef FUNC1
// #undef FUNC2
// #undef FUNC3

template <class F>
struct Line {
    Point<F> a, ab;
    Line() : a(), ab() {}
    Line(const Point<F>& a, const Point<F>& b, bool twoPoints = true)
        : a(a), ab(twoPoints ? b - a : b) {}
    Line(const F& xa, const F& ya, const F& xb, const F& yb)
        : a(xa, ya), ab(xb - xa, yb - ya) {}

    void swap(Line& other) { using std::swap; swap(a, other.a); swap(ab, other.ab); }
    template <class F1> explicit operator Line<F1> () const {
        return Line<F1>(Point<F1>(a), Point<F1>(ab), false); }
    template <class F1> Line& operator = (const Line<F1>& other) {
        a = other.a; ab = other.ab; return *this; }

    Point<F> b() const { return a + ab; }
    operator bool () const { return ab != Point<F>(); }
};

template <class F> int read(Line<F>& line) {
    int res = read(line.a, line.ab) / 2;
    return line.ab -= line.a, res;
}

template <class F>
inline Line<F> makeLine(const Point<F>& a, const Point<F>& b, bool twoPoints = true) {
    return Line<F>(a, b, twoPoints);
}

template <class F> void swap(Line<F>& lhs, Line<F>& rhs) { lhs.swap(rhs); }

template <class F1, class F2>
bool onLine(const Point<F1>& point, const Line<F2>& line) {
    if (!line) return point == line.a;
    return ((point - line.a) ^ line.ab) == 0;
}

template <class F1, class F2>
bool onSegment(const Point<F1>& point, const Line<F2>& seg) {
    if (!seg) return point == seg.a;
    auto vecta = seg.a - point, vectb = seg.b() - point;
    return (vecta ^ vectb) == 0 && (vecta * vectb) <= 0;
}

template <class F1, class F2> using distF = decltype(sqrt(F1() + F2()));

template <class F1, class F2>
distF<F1, F2> distLine(const Point<F1>& point, const Line<F2>& line) {
    if (!line) return dist(point, line.a);
    return abs((point - line.a) ^ line.ab) / norm(line.ab);
}

template <class F1, class F2>
distF<F1, F2> distSegment(const Point<F1>& point, const Line<F2>& seg) {
    if (((point - seg.a) * seg.ab) <= 0) return dist(point, seg.a);
    if (((point - seg.b()) * seg.ab) >= 0) return dist(point, seg.b());
    return distLine(point, seg);
}

template <class F1, class F2, class F3>
void projection(const Point<F1>& point, const Line<F2>& line, Point<F3>& res) {
    res = line.a;
    if (line) res += line.ab * static_cast<F3>((point - line.a) * line.ab) / abs(line.ab);
}

template <class F1, class F2, class F3>
void reflection(const Point<F1>& point, const Line<F2>& line, Point<F3>& res) {
    projection(point, line, res);
    res = 2 * res - point;
}

template <class F1, class F2, class F3>
void closest(const Point<F1>& point, const Line<F2>& seg, Point<F3>& res) {
    if (((point - seg.a) * seg.ab) <= 0) res = seg.a;
    else if (((point - seg.b()) * seg.ab) >= 0) res = seg.b();
    else projection(point, seg, res);
}

template <int TYPE> struct EndpointChecker {};
template <> struct EndpointChecker<0> {  // no endpoint (ray)
    template <class F> bool operator ()(const F& a, const F& b) const { return true; }};
template <> struct EndpointChecker<1> {  // closed endpoint
    template <class F> bool operator ()(const F& a, const F& b) const { return a <= b; }};
template <> struct EndpointChecker<2> {  // open endpoint
    template <class F> bool operator ()(const F& a, const F& b) const { return a < b; }};

template <int LA, int LB, int RA, int RB, class F1, class F2, class F3>
bool intersectLines(const Line<F1>& lhs, const Line<F2>& rhs, Point<F3>& res) {
    assert(lhs && rhs);
    auto s = lhs.ab ^ rhs.ab;
    if (s == 0) return false;
    auto ls = (rhs.a - lhs.a) ^ rhs.ab;
    auto rs = (rhs.a - lhs.a) ^ lhs.ab;
    if (s < 0) s = -s, ls = -ls, rs = -rs;
    bool intersect =
        EndpointChecker<LA>()(decltype(ls)(0), ls) && EndpointChecker<LB>()(ls, s) &&
        EndpointChecker<RA>()(decltype(rs)(0), rs) && EndpointChecker<RB>()(rs, s);
    if (intersect) res = lhs.a + lhs.ab * static_cast<F3>(ls) / s;
    return intersect;
}

template <class F1, class F2, class F3>
bool intersectClosedSegments(const Line<F1>& lhs, const Line<F2>& rhs, Point<F3>& res) {
    return intersectLines<1, 1, 1, 1>(lhs, rhs, res);
}

template <class F1, class F2, class F3>
bool intersectSegments(const Line<F1>& lhs, const Line<F2>& rhs, Line<F3>& res) {
    auto s = lhs.ab ^ rhs.ab;
    auto ls = (rhs.a - lhs.a) ^ rhs.ab;
    if (s == 0) {
        if (ls != 0) return false;
        auto lhsa = lhs.a, lhsb = lhs.b();
        auto rhsa = rhs.a, rhsb = rhs.b();
        if (lhsa > lhsb) swap(lhsa, lhsb);
        if (rhsa > rhsb) swap(rhsa, rhsb);
        res = Line<F3>(max(lhsa, rhsa), min(lhsb, rhsb));
        return res.ab >= Point<F3>();
    }
    auto rs = (rhs.a - lhs.a) ^ lhs.ab;
    if (s < 0) s = -s, ls = -ls, rs = -rs;
    bool intersect = 0 <= ls && ls <= s && 0 <= rs && rs <= s;
    if (intersect)
        res = Line<F3>(lhs.a + lhs.ab * static_cast<F3>(ls) / s, Point<F3>());
    return intersect;
}

template <class F>
struct AngleCompare {
    const Point<F> origin;
    const bool zero;

    AngleCompare(const Point<F>& origin = Point<F>())
        : origin(origin), zero(origin == Point<F>()) {}

    template <class F1, class F2>
    bool operator () (const Point<F1>& lhs, const Point<F2>& rhs) const {
        return zero ? ccw(lhs, rhs) < 0 : ccw(lhs, rhs, origin) < 0;
    }
};

template <class Iterator, class F>
void sortByAngle(Iterator first, Iterator last, const Point<F>& origin) {
    first = partition(first, last, [&origin](const decltype(*first)& point) {
        return point == origin; });
    auto pivot = partition(first, last, [&origin](const decltype(*first)& point) {
        return point > origin; });
    AngleCompare<F> acmp(origin);
    sort(first, pivot, acmp);
    sort(pivot, last, acmp);
}

template <class F> using Polygon = vector<Point<F>>;
inline int prev(int i, int n) { return i == 0 ? n-1 : i-1; }
inline int next(int i, int n) { return i == n-1 ? 0 : i+1; }
template <class T> inline int sgn(const T& x) { return (T(0) < x) - (x < T(0)); }

template <class F>
F area(const Polygon<F>& poly) {
    int n = static_cast<int>(poly.size());
    F area = F(0);
    for (int i = 0; i < n; ++i)
        area += poly[i].x * (poly[next(i, n)].y - poly[prev(i, n)].y);
    return area;
}

// True if orientation of a simple polygon is counter-clockwise.
template <class F> 
bool orientation(const Polygon<F>& poly) {
    int n = static_cast<int>(poly.size());
    int i = static_cast<int>(min_element(begin(poly), end(poly)) - begin(poly));
    return ccw(poly[prev(i, n)], poly[next(i, n)], poly[i]) > 0;
}

template <class F>
Polygon<F> convexHull(Polygon<F> points) {
    sort(begin(points), end(points));
    Polygon<F> hull;
    hull.reserve(points.size() + 1);
    for (int phase = 0; phase < 2; ++phase) {
        auto start = hull.size();
        for (auto& point : points) {
        while (hull.size() >= start+2 &&
                ccw(point, hull.back(), hull[hull.size()-2]) <= 0)
            hull.pop_back();
        hull.push_back(point);
        }
        hull.pop_back();
        reverse(begin(points), end(points));
    }
    if (hull.size() == 2 && hull[0] == hull[1]) hull.pop_back();
    return hull;
}

template <class F1, class F2>
int pointVsTriangle(const Point<F1>& point, const Polygon<F2>& triangle) {
    assert(triangle.size() == 3);
    int signs[3];
    for (int i = 0; i < 3; ++i)
        signs[i] = sgn(ccw(point, triangle[next(i, 3)], triangle[i]));
    if (signs[0] == signs[1] && signs[1] == signs[2]) return -1;
    for (int i = 0; i < 3; ++i) if (signs[i] * signs[next(i, 3)] == -1) return 1;
    return 0;
}

template <class F1, class F2>
int pointVsConvexPolygon(const Point<F1>& point, const Polygon<F2>& poly, int top) {
    if (point < poly[0] || point > poly[top]) return 1;
    auto orientation = ccw(point, poly[top], poly[0]);
    if (orientation == 0) {
        if (point == poly[0] || point == poly[top]) return 0;
        return top == 1 || top + 1 == poly.size() ? 0 : -1;
    } else if (orientation < 0) {
        auto itRight = lower_bound(begin(poly) + 1, begin(poly) + top, point);
        return sgn(ccw(itRight[0], point, itRight[-1]));
    } else {
        auto itLeft = upper_bound(poly.rbegin(), poly.rend() - top-1, point);
        return sgn(ccw(itLeft == poly.rbegin() ? poly[0] : itLeft[-1], point, itLeft[0]));
    }
}

template <class F1, class F2>
int pointVsPolygon(const Point<F1>& point, const Polygon<F2>& poly) {
    int n = static_cast<int>(poly.size()), windingNumber = 0;
    for (int i = 0; i < n; ++i) {
        if (point == poly[i]) return 0;
        int j = next(i, n);
        if (poly[i].y == point.y && poly[j].y == point.y) {
        if (min(poly[i].x, poly[j].x) <= point.x &&
            point.x <= max(poly[i].x, poly[j].x)) return 0;
        } else {
        bool below = poly[i].y < point.y;
        if (below != (poly[j].y < point.y)) {
            auto orientation = ccw(point, poly[j], poly[i]);
            if (orientation == 0) return 0;
            if (below == (orientation > 0)) windingNumber += below ? 1 : -1;
        }
        }
    }
    return windingNumber == 0 ? 1 : -1;
}

template <class F, class Function>
int extremeVertex(const Polygon<F>& poly, Function direction) {
    int n = static_cast<int>(poly.size()), left = 0, leftSgn;
    auto vertexCmp = [&poly, direction](int i, int j) {
        return sgn(ccw(direction(poly[j]), poly[j] - poly[i])); };
    auto isExtreme = [n, vertexCmp](int i, int& iSgn) {
        return (iSgn = vertexCmp(next(i, n), i)) >= 0 && vertexCmp(i, prev(i, n)) < 0; };
    for (int right = isExtreme(0, leftSgn) ? 1 : n; left + 1 < right;) {
        int middle = (left + right) / 2, middleSgn;
        if (isExtreme(middle, middleSgn)) return middle;
        if (leftSgn != middleSgn ? leftSgn < middleSgn
            : leftSgn == vertexCmp(left, middle)) right = middle;
        else left = middle, leftSgn = middleSgn;
    }
    return left;
}

template <class F1, class F2>
pair<int, int> tangentsConvex(const Point<F1>& point, const Polygon<F2>& poly) {
    return {
        extremeVertex(poly, [&point](const Point<F2>& q) { return q - point; }),
        extremeVertex(poly, [&point](const Point<F2>& q) { return point - q; })
    };
}

template <class F1, class F2, class F3>
bool stabConvexPolygon(const Line<F1>& line, const Polygon<F2>& poly, Line<F3>& res) {
    assert(line);
    int right = extremeVertex(poly, [&line](const Point<F2>&) { return line.ab; });
    int left = extremeVertex(poly, [&line](const Point<F2>&) { return -line.ab; });
    auto vertexCmp = [&line](const Point<F2>& vertex) {
        return sgn(ccw(line.ab, vertex - line.a)); };
    int rightSgn = vertexCmp(poly[right]), leftSgn = vertexCmp(poly[left]);
    if (rightSgn < 0 || leftSgn > 0) return false;
    auto intersectChain = [&line, &poly, vertexCmp](int first, int last,
                                                    int firstSgn, Point<F3>& res) {
        int n = static_cast<int>(poly.size());
        while (next(first, n) != last) {
        int middle = (first + last + (first < last ? 0 : n)) / 2;
        if (middle >= n) middle -= n;
        if (vertexCmp(poly[middle]) == firstSgn) first = middle;
        else last = middle;
        }
        intersectLines<0, 0, 0, 0>(line, makeLine(poly[first], poly[last]), res);
    };
    intersectChain(left, right, leftSgn, res.a);
    intersectChain(right, left, rightSgn, res.ab);
    res.ab -= res.a;
    return true;
}

template <class F1, class F2, class F = distF<F1, F2>>
F stabPolygonLength(const Line<F1>& line, const Polygon<F2>& poly) {
    assert(line);
    F tSum = F(0);
    int n = static_cast<int>(poly.size());
    auto vertexSgn = [&line, &poly](int i) { return sgn(line.ab ^ (poly[i] - line.a)); };
    int prevSgn = vertexSgn(n - 1), iSgn = vertexSgn(0), nextSgn;
    for (int i = 0; i < n; ++i, prevSgn = iSgn, iSgn = nextSgn) {
        nextSgn = vertexSgn(next(i, n));
        if (iSgn == 0) {
        if (prevSgn == 0) {
            if (nextSgn != 0 && nextSgn == sgn((poly[i] - poly[prev(i, n)]) * line.ab))
            tSum += nextSgn * static_cast<F>((poly[i] - line.a) * line.ab) / abs(line.ab);
        } else {
            if ((nextSgn != 0 && nextSgn != prevSgn) ||
                (nextSgn == 0 && prevSgn == sgn((poly[next(i, n)] - poly[i]) * line.ab)))
            tSum -= prevSgn * static_cast<F>((poly[i] - line.a) * line.ab) / abs(line.ab);
        }
        } else if (nextSgn == -iSgn) {
        auto vect = poly[next(i, n)] - poly[i];
        tSum += nextSgn * static_cast<F>((poly[i] - line.a) ^ vect) / (line.ab ^ vect);
        }
    }
    return tSum * norm(line.ab);
}

template <class F>
F maxDist2(const Polygon<F>& poly) {
    int n = static_cast<int>(poly.size());
    F res = F(0);
    for (int i = 0, j = n < 2 ? 0 : 1; i < j; ++i)
        for (;; j = next(j, n)) {
        res = max(res, dist2(poly[i], poly[j]));
        if (ccw(poly[i+1] - poly[i], poly[next(j, n)] - poly[j]) >= 0) break;
        }
    return res;
}

/**
bool point_in_convex_strict(const vector<P>& A, const P& Q){
    int n = A.size();
    // must lie strictly left of A[0]->A[1]
    if ((A[1] - A[0]) ^ (Q - A[0]) <= 0) return false;
    // must lie strictly right of A[0]->A[n-1]
    if ((A[n-1] - A[0]) ^ (Q - A[0]) >= 0) return false;
    // fan‐binary search
    int lo = 1, hi = n-1;
    while (hi - lo > 1) {
        int mid = (lo + hi) >> 1;
        if (((A[mid] - A[0]) ^ (Q - A[0])) > 0) lo = mid;
        else hi = mid;
    }
    // must lie strictly left of edge A[lo]->A[hi]
    return ((A[hi] - A[lo]) ^ (Q - A[lo])) > 0;
}
*/

// --- compute signed 2×area of any polygon of Point<F> ---
// For actual area, divide it by 2
// Logic : Think polygon as combination of triangles or parallelograms formed by side vectors
// Cross Product : A ^ B : x1y2 - x2y1, where 1st vector comes first and 2nd comes later in ccw order

template<class F>
auto signed_twicearea(const vector<Point<F>> &P) -> decltype(P[0].x * P[0].y)
{
    using T = decltype(P[0].x * P[0].y);
    T A = 0;
    size_t n = P.size();
    for(int i = 0, j = n - 1; i < n; j = i++)
        A += P[j].x * P[i].y - P[i].x * P[j].y;
    // A = P[n-1]^P[0] + P[0]^P[1] + P[1]^P[2] + P[2]^P[3] + .. + P[n-2]^P[n-1]
    return A;
}

template<class F>
bool point_in_convex_strict(const vector<Point<F>> &P, const Point<F> &Q)
{
    size_t n = (int)P.size();
    // A[0] be our base point or top vertex for all triangles
    if((P[1] - P[0]) ^ (Q - P[0]) <= 0) return false;
    if((P[n - 1] - P[0]) ^ (Q - P[0]) >= 0) return false;
    int high = n - 1, low = 1;
    while(high - low > 1)
    {
        int mid = low + (high - low) >> 1;
        if((P[mid] - P[0]) ^ (Q - P[0]) >= 0) low = mid;
        else high = mid;
    }
    return (P[high] - P[low]) ^ (Q - P[low]) > 0;
}

// --- test that every vertex of B lies strictly inside convex A ---
// F1 and F2 can differ; we cast B’s points into A’s field.

template<class F1, class F2>
bool polygon_in_convex_strict(vector<Point<F1>> &outer, const vector<Point<F2>> &inner)
{
    // ensure A is CCW
    if(signed_twicearea(outer) < 0) reverse(outer.begin(), outer.end());
    for(const auto &p : inner)
    {
        // cast Point<F2> → Point<F1>
        Point<F1> q = static_cast<Point<F1>>(p);
        if(!point_in_convex_strict(outer, q)) return false;
    }
    return true;
}

template<class T>
auto onSegment(const Point<T> &P1, const Point<T> &P2, const Point<T> &Q) -> decltype(2 == 3)
{
    if(min(P1.x, P2.x) <= Q.x and max(P1.x, P2.x) >= Q.x and min(P1.y, P2.y) <= Q.y and max(P1.y, P2.y) >= Q.y) return true;
    return false;
}

int32_t main()
{
    int t;
    cin>>t;
    while(t--)
    {
        Point<int> p1, p2, p3, p4;
        cin>>p1.x>>p1.y>>p2.x>>p2.y>>p3.x>>p3.y>>p4.x>>p4.y;
        int a1 = (p2 - p1) ^ (p3 - p1); // p3 direction to p1p2
        int a2 = (p2 - p1) ^ (p4 - p1); // p4 direction to p1p2
        int a3 = (p2 - p3) ^ (p4 - p3); // p2 direction to p3p4
        int a4 = (p1 - p3) ^ (p4 - p3); // p1 direction to p3p4
        bool intersect = false;
        if(((a1 > 0 and a2 < 0) or (a1 < 0 and a2 > 0)) and ((a3 > 0 and a4 < 0) or (a3 < 0 and a4 > 0)))
        intersect = true;
        else if(a1 == 0 and onSegment(p1, p2, p3)) intersect = true;
        else if(a2 == 0 and onSegment<int>(p1, p2, p4)) intersect = true;
        else if(a3 == 0 and onSegment<int>(p3, p4, p2)) intersect = true;
        else if(a4 == 0 and onSegment<int>(p3, p4, p1)) intersect = true;
        else intersect = false;
        if(intersect) cout<<"YES\n";
        else cout<<"NO\n";
    }
}

// _________________________________________________________________________

// Using template directly

int32_t main()
{
    int t;
    cin>>t;
    while(t--)
    {
        Point<int> p1, p2, p3, p4;
        cin>>p1.x>>p1.y>>p2.x>>p2.y>>p3.x>>p3.y>>p4.x>>p4.y;
        Line<int> l1(p1, p2), l2(p3, p4);
        Line<int> dummy;
        if(intersectSegments(l1, l2, dummy))
        cout<<"YES\n";
        else cout<<"NO\n";
    }
}