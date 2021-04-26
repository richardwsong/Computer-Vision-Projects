#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

#define Point pair<double, double>
int M = 800;
int N = 800;
int* grid = new int[M*N];

vector<Point> pts;
vector<Point> hull;
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

double distToLine(Point one, Point two, Point target)
{
    return abs ((target.second - one.second) * (two.first - one.first) -
                (two.second - one.second) * (target.first - one.first));
}

int findSide(Point one, Point two, Point target)
{
    double val = (target.second - one.second) * (two.first - one.first) -
                 (two.second - one.second) * (target.first - one.first);
    if(val > 0) return 1;
    if(val < 0) return -1;
    return 0;
}

void quickHullHelper(Point one, Point two, int side)
{
    int index = -1;
    double max = 0;
    for(int i = 0; i<size; i++)
    {
        double temp = distToLine(one, two, pts.at(i));
        if(findSide(one, two, pts.at(i)) == side && temp > max)
        {
            max = temp;
            index = i;
        }
    }
    if(index == -1){
        hull.push_back(one);
        hull.push_back(two);
//        drawLine(one.first*800, two.first*800, one.second*800, two.second*800);
        return;
    }
    quickHullHelper(pts.at(index), one, -findSide(pts.at(index), one, two));
    quickHullHelper(pts.at(index), two, -findSide(pts.at(index), two, one));
}

void quickHull()
{
    int minx = 0;
    int maxx = 0;
    for(int i = 0; i<size; i++){
        if(pts.at(i).first < pts.at(minx).first)
            minx = i;
        if(pts.at(i).first > pts.at(maxx).first)
            maxx = i;
    }
    quickHullHelper(pts.at(minx), pts.at(maxx), 1);
    quickHullHelper(pts.at(minx), pts.at(maxx), -1);
}

void set_pixel(int x, int y)
{
   if(x<=N && x >= 0 && y <= M && y >= 0)
      *(grid + y*M + x) = 1;
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
            quickHull();
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
        cout << P << " " << total_time << endl;
    }
    return 0;
}