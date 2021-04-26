#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;

const int M = 800;
const int N = 800;

double dist(int x1, int y1, int x2, int y2)
{
   return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

void set_pixel(int x, int y, int*grid)
{
  if(x<=N && x >= 0 && y <= M && y >= 0)
     *(grid + y*M + x) = 1;
}

void drawCircle(int h, int k, int radius, int*grid)
{
   int x, y, xmax, y2, y2_new, ty;
   xmax = (int) (radius * 1.0/sqrt(2)); // maximum x at radius/sqrt(2)
   y = radius;
   y2 = y * y;
   ty = (2 * y) - 1; y2_new = y2;
   for (x = 0; x <= xmax+2; x++) {
       if ((y2 - y2_new) >= ty) {
           y2 -= ty;
           y -= 1;
           ty -= 2;
       }
       set_pixel (x+h, y+k, grid);
       set_pixel (x+h, -y+k, grid);
       set_pixel (-x+h, y+k, grid);
       set_pixel (-x+h, -y+k, grid);
       set_pixel (y+h, x+k, grid);
       set_pixel (y+h, -x+k, grid);
       set_pixel (-y+h, x+k, grid);
       set_pixel (-y+h, -x+k, grid);
       y2_new -= (2 * x) - 3;
   }
}

void drawLine(int x1, int x2, int y1, int y2, int* grid){
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


int main() {
   int* grid = new int[800*800]; // c++ way
   srand(time(NULL));
   ofstream fout ("file2.ppm");

   int x1, x2, x3, y1, y2, y3;
   x1 = rand() % 800;
   y1 = rand() % 800;
   x2 = rand() % 800;
   y2 = rand() % 800;
   x3 = rand() % 800;
   y3 = rand() % 800;

   set_pixel(x1, y1, grid);
   set_pixel(x2, y2, grid);
   set_pixel(x3, y3, grid);

   cout << x1 << " " << y1 << endl;
   cout << x2 << " " << y2 << endl;
   cout << x3 << " " << y3 << endl;

   fout << "P3 "<< 800 << " " << 800 << " " << 1 << endl;

   drawLine(x1, x2, y1, y2, grid);
   drawLine(x1, x3, y1, y3, grid);
   drawLine(x2, x3, y2, y3, grid);

   double sa = dist(x1, y1, x2, y2);
   double sb = dist(x1, y1, x3, y3);
   double sc = dist(x2, y2, x3, y3);

   double sp = .5 * (sa + sb + sc);

   int incenter_x = (int) ((sa * x3 + sb * x2 + sc * x1)/(sa + sb + sc));
   int incenter_y = (int) ((sa * y3 + sb * y2 + sc * y1)/(sa + sb + sc));
   int incenter_r = (int) sqrt((sp-sa)*(sp-sb)*(sp-sc)/sp);
   double incenter_r1 = sqrt((sp-sa)*(sp-sb)*(sp-sc)/sp);
   drawCircle(incenter_x, incenter_y, incenter_r, grid);

   double cd = (2*(x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2)));
   int ccenter_x = (int) (1/cd * ((x1*x1 + y1*y1)*(y2 - y3) + (x2*x2 + y2*y2)*(y3-y1) + (x3*x3 + y3*y3)*(y1-y2)));
   int ccenter_y = (int) (1/cd * ((x1*x1 + y1*y1)*(x3 - x2) + (x2*x2 + y2*y2)*(x1-x3) + (x3*x3 + y3*y3)*(x2-x1)));
   int ccenter_r = (int) ((sa*sb*sc)/(4*incenter_r1*sp));

   drawCircle(ccenter_x, ccenter_y, ccenter_r, grid);

   int centroid_x = (int) (1/3. * (x1 + x2 + x3));
   int centroid_y = (int) (1/3. * (y1 + y2 + y3));

   int x12 = (int) (.5*(x1+x2));
   int y12 = (int) (.5*(y1+y2));
   int x13 = (int) (.5*(x1+x3));
   int y13 = (int) (.5*(y1+y3));
   int x23 = (int) (.5*(x2+x3));
   int y23 = (int) (.5*(y2+y3));

   double cd1= (2*(x12*(y13 - y23) + x13*(y23 - y12) + x23*(y12 - y13)));
   int np_x = (int) (1/cd1 * ((x12*x12 + y12*y12)*(y13 - y23) + (x13*x13 + y13*y13)*(y23-y12) + (x23*x23 + y23*y23)*(y12-y13)));
   int np_y = (int) (1/cd1 * ((x12*x12 + y12*y12)*(x23 - x13) + (x13*x13 + y13*y13)*(x12-x23) + (x23*x23 + y23*y23)*(x13-x12)));
   int np_r = (int) (.5 * ccenter_r);
   drawCircle(np_x, np_y, np_r, grid);

   for(int i = 0; i<M; i++)
   {
       for(int j = 0; j<N; j++)
       {
           if(*(grid + i*M + j) != 1) {
               *(grid + i * M + j) = 1;
               if(j!=0)
                   fout << " ";
               fout << 1 << " " << 1 << " " << 1;

           }
           else
           {
               *(grid + i * M + j) = 0;
               if(j!=0)
                   fout << " ";
               fout << 0 << " " << 0 << " " << 0;
           }
       }
       fout << endl;
   }
   cout.flush();
   fout.close();
   return 0;
}

