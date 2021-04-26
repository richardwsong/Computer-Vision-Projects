//Richard Song Period 1
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bits/stdc++.h>
#include <map>

using namespace std;
using namespace std::chrono;


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
    void toString()
    {
        cout << x << " " << y<<endl;
    }
};

vector<Point> pointVector;
static int size;
static Point* pa;


double distance(Point one, Point two)
{
    return sqrt((one.x-two.x)*(one.x-two.x) + (one.y-two.y)*(one.y-two.y));
}

Point* knuth_shuffle(Point* arr)
{
    for(int i = 0; i< size; i++)
    {
        int rand_index = (int)((double)rand()/RAND_MAX * (size-i) + i);
        Point a = *(arr + i);
        *(arr + i) = *(arr + rand_index);
        *(arr + rand_index) = a;
    }
    return arr;
}

int hashfunction(double delta, Point p)
{

   double length = delta/2;
   int down = (int)round(p.y/length);
   int across = (int)round(p.x/length);
   return ((int)round(1/length)) * down + across;
}

map<int, vector<Point>> newMap(double delta, int index)
{
    map<int, vector<Point>> smap;
    for(int i = 1; i<=index; i++)
    {
        int hash = hashfunction(delta, *(pa+i));
        if(smap.count(hash) == 0)
        {
            smap.insert(pair<int, vector<Point>>(hash, vector<Point>()));
        }
        smap.at(hash).push_back(*(pa+i));
    }
    return smap;
}

void FindClosestPair()
{
    pa = knuth_shuffle(pa);
    double delta = distance(*(pa+1), *(pa + 2));
    map<int, vector<Point>> smap;
//   smap = newMap(delta, 0);

    Point one;
    Point two;
    auto start = high_resolution_clock::now();
    for (int i = 1; i <= size; i++) {
        int key = hashfunction(delta, *(pa + i));
        double newdelta = delta;
        int rowval = (int) (size / delta / 2);
        for (int x = key - 2 * (int) (size / delta / 2); x <= key + 2 * (int) (size / delta / 2); x += (int) (size / delta / 2)) {
            for (int y = x - 2; y <= x + 2; y++) {
                if (y < 0 || smap.count(y) == 0)
                    continue;
                for (Point p: smap.at(y)) {
                    double newdist = distance(p, *(pa + i));
                    if (newdist < newdelta && newdist != 0) {
                        newdelta = newdist;
                        one = p;
                        two = *(pa + i);
                    }
                }
            }
        }
        if (newdelta < delta) {
            smap = newMap(newdelta, i);
            delta = newdelta;
        } else {
            int hash = hashfunction(delta, *(pa + i));
            if (smap.count(hash) == 0) {
                smap.insert(pair<int, vector<Point>>(hash, vector<Point>()));
            }
            smap.at(hash).push_back(*(pa + i));
        }

    }
    cout << "Closest Distance: " << delta << endl;
    cout << "Point 1: " << one.x << " " << one.y << endl;
    cout << "Point 2: " << two.x << " " << two.y << endl;

}


int main()
{
    ifstream fin ("points.txt");
    if(fin.is_open())
        cout << "open" << endl;
    else
        cout << "not open" << endl;
    fin >> size;
    pa = new Point[size+1];
    double total = 0.0;


        for (int i = 1; i <= size; i++) {
            Point ptemp;
            fin >> ptemp.x;
            fin >> ptemp.y;
            *(pa + i) = ptemp;
        }
    FindClosestPair();
    return 0;
}


