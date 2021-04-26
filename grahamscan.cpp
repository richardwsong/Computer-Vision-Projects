#include <bits/stdc++.h>
using namespace std::chrono;
using namespace std;

class Point
{
public:
    double x, y;
    Point(double a, double b) {
        x = a;
        y = b;
    }
    Point(){

    }
};

int M = 800;
int N = 800;
int* grid = new int[M*N];

vector<Point> pts;
vector<Point> hull;

Point p0;
int size = 75;


void drawLine(int x1, int x2, int y1, int y2){
    int dx = x2 - x1;
    int dy = y2 - y1;
    double m = 1.0 * dy/dx;
    double e = abs(m) - 1.0;

    if(abs(dy) >= abs(dx)) //slope > 1 and going up, da is y
    {
        int j = x1;
        m = 1.0 * dx/dy;
        e = abs(m) - 1.0;
        for(int i = y1; i!=y2;)
        {
//            cout << i << " " << j << " " << e<< endl;
            *(grid + i*M + j) = 1;
            if(e >= 1.0) {
                if(dx > 0)
                    j += 1;
                else
                    j-=1;
                e -= 1.0;
            }
            if(dy > 0)
                i+=1;
            else
                i-=1;
            e+=abs(m);
        }
    }
    else
    {
        int j = y1;
        for(int i = x1; i!=x2;)
        {
//            cout << i << " " << j << " " << e<< endl;
            *(grid + j*M + i) = 1;
            if(e >= 1.0) {
                if(dy > 0)
                    j += 1;
                else
                    j-=1;
                e -= 1.0;
            }
            if(dx > 0)
                i+=1;
            else
                i-=1;
            e+=abs(m);
        }
    }
}

void set_pixel(int x, int y)
{
    if(x<=N && x >= 0 && y <= M && y >= 0)
        *(grid + y*M + x) = 1;
}

double distSq(Point p1, Point p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) +
           (p1.y - p2.y)*(p1.y - p2.y);
}


int orientation(Point p, Point q, Point r)
{
    double val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;
    return (val > 0)? 1: 2;
}

int compare(const void *vp1, const void *vp2)
{
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;

    return (o == 2)? -1: 1;
}

void swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

double dist(Point p1, Point p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) +
           (p1.y - p2.y)*(p1.y - p2.y);
}

Point nextToTop(vector<Point> &S)
{
    Point p = S.back();
    S.pop_back();
    Point res = S.back();
    S.push_back(p);
    return res;
}

void grahamscan() {
    int ind = 0;
    for (int i = 1; i < pts.size(); i++) {
        if (pts.at(i).y < pts.at(ind).y || (pts.at(i).y == pts.at(ind).y && pts.at(i).x < pts.at(ind).x))
            ind = i;
    }
    swap(pts[0], pts[ind]);
    p0 = pts[0];
    qsort(&pts[1], size - 1, sizeof(Point), compare);

    hull.push_back(pts[0]);
    hull.push_back(pts[1]);
    hull.push_back(pts[2]);

    for (int i = 3; i < size; i++) {
        while (orientation(nextToTop(hull), hull.back(), pts[i]) != 2) {
//            cout << orientation(nextToTop(hull), hull.top(), pts[i]) << endl;
            hull.pop_back();
        }
        hull.push_back(pts[i]);
    }
//    cout << hull.size() << endl;

    Point t = hull.back();
    Point first = hull.back();
    hull.pop_back();
    while (!hull.empty()) {
        Point one = hull.back();
//        drawLine(t.x*800, one.x*800, t.y*800, one.y*800);
        t = one;
        hull.pop_back();
//    }
//    drawLine(t.x*800, first.x*800, t.y*800, first.y*800);
    }
}
int main()
{
        srand(time(NULL));
//    ofstream fout ("hull.ppm");
        int test[] = {100, 500, 1000, 2000, 5000, 10000, 50000, 100000, 500000, 1000000};
        for (int P: test) {
            size = P;
            double total_time = 0;
            for (int a = 0; a < 10; a++) {
                pts.clear();
                hull.clear();
                for (int i = 0; i < size; i++) {
                    pts.push_back({((double) rand() / (double) RAND_MAX), ((double) rand() / (double) RAND_MAX)});
//                    set_pixel(pts.at(i).x * 800, pts.at(i).y * 800);
                }
                auto start = high_resolution_clock::now();
                grahamscan();
                auto stop = high_resolution_clock::now();
                total_time += ((stop - start).count() / (1000000.));
//    fout << "P3 "<< 800 << " " << 800 << " " << 1 << endl;
//
//    for(int i = 0; i<M; i++)
//    {
//        for(int j = 0; j<N; j++)
//        {
//            if(*(grid + i*M + j) != 1) {
//                *(grid + i * M + j) = 1;
//                if(j!=0)
//                    fout << " ";
//                fout << 1 << " " << 1 << " " << 1;
//
//            }
//            else
//            {
//                *(grid + i * M + j) = 0;
//                if(j!=0)
//                    fout << " ";
//                fout << 0 << " " << 0 << " " << 0;
//            }
//        }
//        fout << endl;
//    }
            }
            total_time /= 10;
            cout <<total_time << endl;
        }
        return 0;
}
