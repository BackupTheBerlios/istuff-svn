// PRGeometry.h

#ifndef _PRGEOMETRY_H_
#define _PRGEOMETRY_H_

namespace prlogic {

enum PRSide { PR_NONE, PR_LEFT, PR_RIGHT, PR_TOP, PR_BOTTOM };

template<class T>
struct PRRange {
    T start, end;

    static PRRange Make(T s, T e) { PRRange<T> r(s,e); return r; }

    PRRange() { set(0,0); }
    PRRange(T s, T e) { set(s,e); }
    PRRange(const PRRange<T> &r) { set(r); }
    void set(T s, T e) { start = s; end = e; }
    void set(const PRRange<T> &r) { start = r.start; end = r.end; }
    T length() const { return (end - start); }
    bool contains(T x) const { return ((x >= start) && (x <= end)); }
    bool equals(const PRRange<T> &r) const { return ((start == r.start) && (end == r.end)); }
    const PRRange<T> &operator=(const PRRange<T> &r) { set(r); return r; }
//    friend bool operator==(const PRRange<T> &r1, const PRRange<T> &r2) { return r1.equals(r2); }
    T translate(T x, const PRRange<T> &dest) const
      { return (dest.start + (T)(((float)(x - start) / (float)length()) * (float)dest.length())); }
};
    
template<class T>
struct PRPoint {
    T x,y;

    static PRPoint Make(T newx, T newy) { PRPoint<T> p(newx,newy); return p; }

    PRPoint() { set(0,0); }
    PRPoint(T newx, T newy) { set(newx,newy); }
    PRPoint(const PRPoint<T> &p) { set(p); }
    void set(T newx, T newy) { x = newx; y = newy; }
    void set(const PRPoint<T> &p) { x = p.x; y = p.y; }
    void delta(T dx, T dy) { x += dx; y += dy; }
    bool equals(const PRPoint<T> &p) const { return ((x == p.x) && (y == p.y)); }
    const PRPoint<T> &operator=(const PRPoint<T> &p) { set(p); return p; }
    friend bool operator==(const PRPoint<T> &p1, const PRPoint<T> &p2) { return p1.equals(p2); }
};

template<class T>
struct PRRect {
    PRPoint<T> loc, size;

    static PRRect<T> Make(T x, T y, T w, T h) { PRRect<T> r(x,y,w,h); return r; }
    static PRRect<T> Make(const PRPoint<T> &l, const PRPoint<T> &s) { PRRect r(s,l); return r; }
    
    PRRect() { set(0,0,0,0); }
    PRRect(T x, T y, T w, T h) { set(x,y,w,h); }
    PRRect(const PRRect<T> &r) { set(r); }
    PRRect(const PRPoint<T> &l, const PRPoint<T> &s) { set(l,s); }
    void set(T x, T y, T w, T h) { loc.set(x,y); size.set(w,h); }
    void set(const PRRect<T> &r) { set(r.loc,r.size); }
    void set(const PRPoint<T> &l, const PRPoint<T> &s) { loc = l; size = s; }
    void grow(T dh, T dv) { loc.delta(-dh, -dv); size.delta(2*dh, 2*dv); }
    bool equals(const PRRect<T> &r) const { return ((loc == r.loc) && (size == r.size)); }
    T minX() const { return loc.x; }
    T minY() const { return loc.y; }
    T maxX() const { return loc.x + size.x; }
    T maxY() const { return loc.y + size.y; }
    bool contains(const PRPoint<T> &p) const
      { return ((p.x >= minX()) && (p.x <= maxX()) && (p.y >= minY()) && (p.y <= maxY())); }
    const PRRect<T> &operator=(const PRRect<T> &r) { set(r); return r; }
   // friend bool operator==(const PRRect<T> &r1, const PRRect<T> &r2) { return r1.equals(r2); }
};

} // namespace prlogic

#endif