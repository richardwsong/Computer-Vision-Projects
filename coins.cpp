#include <bits/stdc++.h>

using namespace std;

const float R = 0.299F;
const float G = 0.587F;
const float B = 0.114F;
int M;
int N;
int* img;
int* xcon;
int* strength;
vector<int> voters;
int* votecount;
int* test;
int* grid;

int counter = 0;
vector<pair<int,double>> pixels;  //point, angle

string a;
int b, c, d;

int x [] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
int y [] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
int vc = 1;
//x
//-1 0 1
//-2 0 2
//-1 0 1

//y
//-1 -2 -1
//0 0 0
//1 2 1


int con_val(int dir, int i)
{
    //dir: 0 is x, 1 is y
    if(dir == 0)
        return *(img + i-b-1)*x[0] + *(img + i-b)*x[1] + *(img + i-b+1)*x[2] + *(img + i-1)*x[3] + *(img + i)*x[4] +
                *(img + i+1)*x[5] + *(img + i+b-1)*x[6] + *(img + i+b)*x[7] + *(img + i+b+1)*x[8];
    else
        return *(img + i-b-1)*y[0] + *(img + i-b)*y[1] + *(img + i-b+1)*y[2] + *(img + i-1)*y[3] + *(img + i)*y[4] +
               *(img + i+1)*y[5] + *(img + i+b-1)*y[6] + *(img + i+b)*y[7] + *(img + i+b+1)*y[8];
}
double PI = 3.1415926535;
void hough()
{
    for(int i: voters)
    {
//        if (vc < 5)
//            *(test + i) = 1;
//        double xval = con_val(0, i);
//        double yval = con_val(1, i);
//        double angle = atan(yval/xval);
        int x1 = i%N;
        int y1 = i/N;
//        if(vc < 10)
//            *(votecount + 10 * N + 144) = 1;
        for(int r = 8; r<=14; r++)
        {
            for(int t = 0; t<=360; t+=1)
            {
                int a1 = (int)(x1 - r*cos(t*PI/180));
                int b1 = (int)(y1 - r*sin(t*PI/180));
                if(a1 < 0 || a1 > N || b1 < 0 || b1>M)
                    continue;
                int nval = b1*N + a1;

                *(votecount + nval) += 1;
                *(test + nval) += r;
            }
        }
        vc += 1;
    }
}
void convolutions()
{
//    double max = 0;
    for(int i = 0; i<b*c; i++)
    {
        int xval = 0;
        int yval = 0;
        if(i<b || (i%b)==0 || i>b*(c-1) || ((i+1)%b)==0) {
            *(xcon + i) = 0;
            continue;
        }
        xval = con_val(0, i);
        yval = con_val(1, i);


        double gradient = sqrt(xval*xval + yval*yval);
        if(gradient < 120)
            *(strength + i) = -1;
        else if(120 < gradient && gradient < 200)
            *(strength + i) = 0;
        else
            *(strength + i) = 1;
//        if(gradient > max)
//            max = gradient;
//        if(*(strength + i)==1)
//            *(xcon + i) = 255;
//        if(*(strength + i) == 0)
//            *(xcon + i) = 80;
        if(gradient > 150)
            *(xcon + i) = 255;
        else
            *(xcon + i) = 0;
        double angle;
        if(xval ==0 && yval !=0){
            angle = 3.14159/2;
        }
        else if(xval == 0 && yval == 0)
        {
            angle = 0;
        }
        else
            angle = atan(yval/xval);
        angle = angle * 180/3.14159265358979323846;
        int q = 255;
        int r = 255;
        if ((0 <= angle < 22.5) || (157.5 <= angle)) {
            q = *(img+i+1);
            r = *(img+i-1);
        }
        else if ((22.5 <= angle < 67.5)) {
            q = *(img+i-1+b);
            r = *(img+i+1-b);
        }
        else if ((67.5 <= angle < 112.5)) {
            q = *(img+i+1);
            r = *(img+i-1);
        }
        else if ((112.5 <= angle < 157.5)) {
            q = *(img+i-1-b);
            r = *(img+i+b+1);
        }

        if ((*(img+i) >= q) && (*(img + i) >= r)){
            *(xcon + i) = *(xcon+i);
            if(*(strength + i) == -1)
                *(xcon + i) = 0;
            if(*(strength + i) == 1)
                *(xcon + i) = 255;
        } else{
            *(xcon + i) = 0;
            if(*(strength + i) == 1)
                *(xcon + i) = 255;
//            if(*(strength + i) == 0 && (*(strength+i-b-1)==1 || *(strength+i-b)==1 || *(strength+i-b+1)==1 ||
//                                        *(strength+i-1)==1 || *(strength+i+1)==1 || *(strength+i+b-1)==1 || *(strength+i+b)==1 ||
//                                        *(strength+i+b+1)==1)){
//                *(xcon + i) = 255;
//                *(strength + i) = 1;
//            }
//            else if(*(strength+i) == 0){
//                *(xcon + i) = 0;
//            }
        }
//        if(*(strength + i) == 1)
//            *(xcon + i) = 255;
//
//        else if(*(strength + 1) ==0)
//            *(xcon + i) = 0;
        if(*(xcon + i) == 255) {
            counter++;
            voters.push_back(i);
        }

    }
}

int main()
{
    ifstream in("coin1p.ppm");
    ofstream out("grayscale_image.ppm");
    ofstream out2("convolution_image.ppm");
    in >> a;
    in >> b;
    in >> c;
    in >> d;

    N = b;
    M = c;

    out << a << " " << b << " " << c << " " << d << endl;
    out2 << a << " " << b << " " << c << " " << d << endl;
    img = new int[b*c];
    xcon = new int[b*c];
    strength = new int[b*c];
    votecount = new int[b*c];
    test = new int[b*c];
    grid = new int[b*c];
    int q = 0;
    for(int i = 0; i < 3*b*c ; i+=3)
    {
        q++;
        int r, g, b1;
        in >> r >> g >> b1;
        int gray = (int)(r*R + g*G + b1*B);
        out << gray << " " << gray << " " << gray << " ";
        if(i!= 0 && (i/3)%(b-1) == 0)
            out << endl;
        *(img + i/3) = gray;
//        *(img + i+1) = gray;
//        *(img + i+2) = gray;
    }
    //    cout << q << endl;
    out.close();
    convolutions();
    hough();

//    cout << counter << endl;

//    int x1 = 200;
//    int y1 = 150;
//    for(int r = 12; r<=12; r++)
//    {
//        for(int t = 0; t<=360; t+=1)
//        {
//            int a1 = (int)(x1 - r*cos(t*PI/180));
//            int b1 = (int)(y1 - r*sin(t*PI/180));
//            if(a1 < 0 || a1 > N || b1 < 0 || b1>M)
//                continue;
//            int nval = b1*N + a1;
//
//            *(test + nval) += 1;
//        }
//    }
    unordered_set<int> set;

    int sum = 0;

    int scale = 21;
    for(int i = 0; i<b*c; i++) {
        if (*(votecount + i) > 651 && set.find(i) == set.end()) {
            int temp = i - scale * N;
            for (int qq = 0; qq < 2*scale; qq++) {
                for (int jj = temp - scale; jj < temp + scale; jj++) {
                    set.insert(jj);
                }
                temp += N;
            }
            double val = (int) (1.0 * (*(test + i)) / (*(votecount + i)));

            int x1 = i%N;
            int y1 = i/N;
            for(int t = 0; t<=360; t+=1)
            {

                int a1 = (int)(x1 - val*cos(t*PI/180));
                int b1 = (int)(y1 - val*sin(t*PI/180));
                if(a1 < 0 || a1 > N || b1 < 0 || b1>M)
                    continue;
                int nval = b1*N + a1;
                *(grid + nval+N+N+1) = 1;
            }

        }
        else if(*(grid + i) != 1)
            *(grid + i) = 0;
    }

    for(int i = 0; i<b*c; i++)
    {
//        if(*(votecount+i) > 651 && set.find(i)==set.end()) {
//            int temp = i-5*N;
//            for(int qq = 0; qq<10; qq++){
//                for(int jj = temp-5; jj<temp+5; jj++){
//                    set.insert(jj);
//                }
//                temp+=N;
//            }
//            double val = (int)(1.0*(*(test + i))/(*(votecount + i)));
//
//            if(val < 8.0)
//                sum+=10;
//            if(val >= 9.0 && val < 10.0)
//                sum+=1;
//            else if(val >= 10.0 && val < 11.0)
//                sum+=1;
//            else if(val >= 11.0 && val < 12.0)
//                sum+=5;
//            else if(val >= 12.0 && val < 13.0)
//                sum+=25;
//            else if(val >= 13.0 && val < 14.0)
//                sum+=50;
//            out2 << 0 << " " << 0 << " " << 0 << " ";
//        }
        if(*(grid + i) == 1){
            out2 << 255 << " " << 0 << " " << 0 << " ";
        }
        else {
            int value = (int) *(img + i);
            out2 << value << " " << value << " " << value << " ";
        }
        if(i%(b-1) == 0)
            out2 << endl;
    }
    cout << "$" << sum/100.0 << endl;
    out2.close();
}