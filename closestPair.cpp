
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;


class Point
{
public:
    int x, y;
    Point(int a, int b) {
        x = a;
        y = b;
    }
    Point(){

    }
};

vector<Point> pointVector;

double distance(Point one, Point two)
{
    return sqrt((one.x-two.x)*(one.x-two.x) + (one.y-two.y)*(one.y-two.y));
}

double* stripvalue(vector<Point> strip, int size, double d)
{
    double minimum = d;
    double a=0.0;
    double b=0.0;
    sort(strip.begin(), strip.end(),
         [](const Point & a, const Point & b) -> bool
         {
             return a.y < b.y;
         });
//    cout<<size<<endl;
    for(int i = 0; i<max((int)strip.size(), (int)strip.size()-15); i++)
    {
        for(int j = i; j< min((int)strip.size(), i+15); j++)
        {
            double temp_dist = distance(strip.at(i), strip.at(j));
            if(temp_dist < minimum)
            {
                minimum = temp_dist;
                a = i;
                b = j;
            }
        }
    }
    auto* ret = new double[3];
    ret[0] = minimum;
    ret[1] = a;
    ret[2] = b;
    return ret;
}

double* stripvalue_slow(vector<Point> strip, int size, double d)
{
    double minimum = d;
    double a=0.0;
    double b=0.0;
//    cout<<size<<endl;
    for(int i = 0; i<strip.size(); i++)
    {
        for(int j = i; j<strip.size(); j++)
        {
            double temp_dist = distance(strip.at(i), strip.at(j));
            if(temp_dist < minimum)
            {
                minimum = temp_dist;
                a = i;
                b = j;
            }
        }
    }
    auto* ret = new double[3];
    ret[0] = minimum;
    ret[1] = a;
    ret[2] = b;
    return ret;
}


vector<double> recursion(int b, int c)
{
    if(c-b<=1){
        vector<double> ret;
        ret.push_back(distance(pointVector.at(b), pointVector.at(c)));
        ret.push_back(b*1.0);
        ret.push_back(c*1.0);
        return ret;
    }
    else if(c-b<=2){
        double d1 = distance(pointVector.at(b), pointVector.at(c));
        double d2 = distance(pointVector.at(b+1), pointVector.at(c));
        double d3 = distance(pointVector.at(b), pointVector.at(b+1));
        vector<double> ret;
        if(d1 < d2 && d1 < d3){
            ret.push_back(d1);
            ret.push_back(b*1.0);
            ret.push_back(c*1.0);
            return ret;
        }
        else if (d2 < d1 && d2 < d3){
            ret.push_back(d2);
            ret.push_back(b*1.0);
            ret.push_back(c*1.0);
            return ret;
        }
        else{
            ret.push_back(d3);
            ret.push_back(b*1.0);
            ret.push_back(c*1.0);
            return ret;
        }
    }
    else{
        int mid = (b+c)/2;
        vector<double> left = recursion(b, mid);
        vector<double> right = recursion(mid, c);

        double d1 = left.at(0);
        double d2 = right.at(0);
        double d = min(d1, d2);
//

        vector<Point> strip;
        int j = 0;
        for(int i = b; i<=c; i++)
        {
            if(abs(pointVector.at(i).x - pointVector.at(mid).x) <= d)
            {
                strip.push_back(pointVector.at(i));
                j++;
            }
        }
        double* strip_ret = stripvalue(strip,j, d);

//        cout << j-1 << endl;
        if(*(strip_ret) < d)
        {
            double a1 = *(strip_ret + 1);
            double b1 = *(strip_ret + 2);
            vector<double> ret;
            ret.push_back(*(strip_ret));
            ret.push_back(b*1.0);
            ret.push_back(c*1.0);
            return ret;
        }
        else
        {
            if(d1==d)
            {
//                double ret[] = {d, *(left+1), *(left+2)};
                vector<double> ret;
                ret.push_back(d);
                ret.push_back(left.at(1));
                ret.push_back(left.at(2));
                return ret;
            }
            else
            {
                vector<double> ret;
                ret.push_back(d);
                ret.push_back(right.at(1));
                ret.push_back(right.at(2));
                return ret;
            }
        }
    }
}

vector<double> recursion_slow(int b, int c)
{
    if(c-b<=1){
        vector<double> ret;
        ret.push_back(distance(pointVector.at(b), pointVector.at(c)));
        ret.push_back(b*1.0);
        ret.push_back(c*1.0);
        return ret;
    }
    else if(c-b<=2){
        double d1 = distance(pointVector.at(b), pointVector.at(c));
        double d2 = distance(pointVector.at(b+1), pointVector.at(c));
        double d3 = distance(pointVector.at(b), pointVector.at(b+1));
        vector<double> ret;
        if(d1 < d2 && d1 < d3){
            ret.push_back(d1);
            ret.push_back(b*1.0);
            ret.push_back(c*1.0);
            return ret;
        }
        else if (d2 < d1 && d2 < d3){
            ret.push_back(d2);
            ret.push_back(b*1.0);
            ret.push_back(c*1.0);
            return ret;
        }
        else{
            ret.push_back(d3);
            ret.push_back(b*1.0);
            ret.push_back(c*1.0);
            return ret;
        }
    }
    else{
        int mid = (b+c)/2;
        vector<double> left = recursion(b, mid);
        vector<double> right = recursion(mid, c);

        double d1 = left.at(0);
        double d2 = right.at(0);
        double d = min(d1, d2);
//

        vector<Point> strip;
        int j = 0;
        for(int i = b; i<=c; i++)
        {
            if(abs(pointVector.at(i).x - pointVector.at(mid).x) <= d)
            {
                strip.push_back(pointVector.at(i));
                j++;
            }
        }
        double* strip_ret = stripvalue_slow(strip,j, d);

//        cout << j-1 << endl;
        if(*(strip_ret) < d)
        {
            double a1 = *(strip_ret + 1);
            double b1 = *(strip_ret + 2);
            vector<double> ret;
            ret.push_back(*(strip_ret));
            ret.push_back(b*1.0);
            ret.push_back(c*1.0);
            return ret;
        }
        else
        {
            if(d1==d)
            {
//                double ret[] = {d, *(left+1), *(left+2)};
                vector<double> ret;
                ret.push_back(d);
                ret.push_back(left.at(1));
                ret.push_back(left.at(2));
                return ret;
            }
            else
            {
                vector<double> ret;
                ret.push_back(d);
                ret.push_back(right.at(1));
                ret.push_back(right.at(2));
                return ret;
            }
        }
    }
}

void bruteforce(Point pa[], int size)
{
    Point p1;
    Point p2;
    auto start = high_resolution_clock::now();
    double dist = 10000000000;
    for(int i = 0; i<size; i++)
    {
        for(int j = i+1; j<size; j++)
        {
            Point one = pa[i];
//            cout << one.x << " " << one.y << endl;
            Point two = pa[j];
            double t_dist = distance(pa[i], pa[j]);
            if(t_dist < dist)
            {
//                cout << "tru" << endl;
                dist=t_dist;
                p1 = pa[i];
                p2 = pa[j];
            }

        }
    }
}


int main()
{
    srand(time(NULL));
    int M = 3000;
    int N = 3000;
    int size = 50000;
    int* grid = new int[M*N]; // c++ way
    Point* pa = new Point[size+1];
//
//    double total_time = 0.0;
//    for(int trial = 0; trial<10; trial++) {
//        for (int i = 1; i <= size; i++) {
//            Point ptemp;
//            ptemp.x = rand()%M;
//            ptemp.y = rand()%M;
//            *(pa + i) = ptemp;
//            pointVector.push_back(*(pa+i));
////        if(i == 0)
////            cout<<pa[i].x << " " <<pa[i].y << endl;
////            *(grid + pa[i].y * M + pa[i].x) = 1;
//        }
//
//        sort(pointVector.begin(), pointVector.end(),
//             [](const Point &a, const Point &b) -> bool {
//                 return a.x < b.x;
//             });
//
//        auto start = high_resolution_clock::now();
//        vector<double> ret = recursion(0, size-1);
//        auto stop = high_resolution_clock::now();
//        total_time += ((stop - start).count() / (1000000000.));
//        cout << "done" << endl;
//    }
//    cout << "FAST RECURSION TIME IN SECONDS : " << total_time/10.0 << endl;
//
//    total_time = 0.0;
//    for(int trial = 0; trial<10; trial++) {
//        for (int i = 1; i <= size; i++) {
//            Point ptemp;
//            ptemp.x = rand()%M;
//            ptemp.y = rand()%M;
//            *(pa + i) = ptemp;
//            pointVector.push_back(*(pa+i));
////        if(i == 0)
////            cout<<pa[i].x << " " <<pa[i].y << endl;
////            *(grid + pa[i].y * M + pa[i].x) = 1;
//        }
//
//        sort(pointVector.begin(), pointVector.end(),
//             [](const Point &a, const Point &b) -> bool {
//                 return a.x < b.x;
//             });
//
//        auto start = high_resolution_clock::now();
//        vector<double> ret = recursion_slow(0, size-1);
//        auto stop = high_resolution_clock::now();
//        total_time += ((stop - start).count() / (1000000000.));
////        cout << "done" << endl;
//    }
//    cout << "SLOW RECURSION TIME IN SECONDS : " << total_time/10.0 << endl;

    double total_time = 0.0;
    for(int trial = 0; trial<1; trial++) {
        for (int i = 1; i <= size; i++) {
            Point ptemp;
            ptemp.x = rand()%M;
            ptemp.y = rand()%M;
            *(pa + i) = ptemp;
            pointVector.push_back(*(pa+i));
//        if(i == 0)
//            cout<<pa[i].x << " " <<pa[i].y << endl;
//            *(grid + pa[i].y * M + pa[i].x) = 1;
        }

        sort(pointVector.begin(), pointVector.end(),
             [](const Point &a, const Point &b) -> bool {
                 return a.x < b.x;
             });

        auto start = high_resolution_clock::now();
        bruteforce(pa, size);
        auto stop = high_resolution_clock::now();
        total_time += ((stop - start).count() / (1000000000.));
//        cout << "done" << endl;
    }
    cout << "BRUTE FORCE TIME IN SECONDS : " << total_time/1.0 << endl;
////    cout << p1.x << p1.y << endl;
//    *(grid + p1.y*M + p1.x) = 2;
////    *(grid + (p1.y+1)*M + p1.x) = 2;
////    *(grid + p1.y*M + p1.x+1) = 2;
////    *(grid + p1.y*M + p1.x-1) = 2;
////    *(grid + (p1.y-1)*M + p1.x) = 2;
////    *(grid + (p1.y+1)*M + p1.x+1) = 2;
////    *(grid + (p1.y+1)*M + p1.x-1) = 2;
////    *(grid + (p1.y-1)*M + p1.x+1) = 2;
////    *(grid + (p1.y-1)*M + p1.x-1) = 2;
//
//    *(grid + p2.y*M + p2.x) = 2;
////    *(grid + (p2.y+1)*M + p2.x) = 2;
////    *(grid + p2.y*M + p2.x+1) = 2;
////    *(grid + p2.y*M + p2.x-1) = 2;
////    *(grid + (p2.y-1)*M + p2.x) = 2;
////    *(grid + (p2.y+1)*M + p2.x+1) = 2;
////    *(grid + (p2.y+1)*M + p2.x-1) = 2;
////    *(grid + (p2.y-1)*M + p2.x+1) = 2;
////    *(grid + (p2.y-1)*M + p2.x-1) = 2;
//    ofstream fout ("closetPair.ppm");
//    fout << "P3 "<< 500 << " " << 500 << " " << 1 << endl;
//    for(int i = 0; i<M; i++)
//    {
//        for(int j = 0; j<N; j++)
//        {
//            if(*(grid + i*M + j) == 2) {
////                *(grid + i * M + j) = 1;
//                if(j!=0)
//                    fout << " ";
//                fout << 1 << " " << 0 << " " << 0;
//
//            }
//            else if(*(grid + i*M + j) != 1) {
////                *(grid + i * M + j) = 1;
//                if(j!=0)
//                    fout << " ";
//                fout << 1 << " " << 1 << " " << 1;
//
//            }
//            else
//            {
////                *(grid + i * M + j) = 0;
//                if(j!=0)
//                    fout << " ";
//                fout << 0 << " " << 0 << " " << 0;
//            }
//        }
//        fout << endl;
//    }
//    fout.close();

    return 0;
}
