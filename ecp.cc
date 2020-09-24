#include <cassert>
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <limits>
#include <cmath>
#include <math.h>
#include <chrono>
using namespace std;

struct Coords
{
  double cordX;
  double cordY;
  Coords(double paramx, double paramy) : cordX(paramx), cordY(paramy) {}
};

double distance(Coords one, Coords two)
{
  double x1 = one.cordX;
  double x2 = two.cordX;
  double y1 = one.cordY;
  double y2 = two.cordY;
  double distanceV = sqrt((pow(x2-x1,2))+(pow(y2-y1, 2)));
  return distanceV;
}

vector <Coords> minPair(vector <Coords> xPair, vector <Coords> yPair)
{
  double minDistX = distance(xPair[0], xPair[1]);
  double minDistY = distance(yPair[0], yPair[1]);
  if(minDistX < minDistY)
  {
    return xPair;
  }
  else if (minDistY < minDistX)
  {
    return yPair;
  }
  else
  {
    return xPair;
  }
}

double minDouble (double oned, double twod)
{
  if(oned<twod)
  {
    return oned;
  }
  else if(twod<oned)
  {
    return twod;
  }
  else
  {
    return oned;
  }
}

vector <Coords> closestPoints(vector <Coords> xSorted, vector <Coords> ySorted)
{
  double dminsq;
  //vector <Coords> theAns;
  if (xSorted.size() < 3)
  {
    double minDistX = numeric_limits<double>::infinity();
    vector <Coords> pairX;
    pairX.push_back(Coords(111110.0, 0.0));
    pairX.push_back(Coords(0.0, 1111110.0));
    for(int i = 1; i < xSorted.size(); i++)
    {
      for(int j = i+1; j < xSorted.size(); j++)
      {
        double dist = distance(xSorted[i], xSorted[j]);
        if (dist < minDistX)
        {
          minDistX = dist;
          pairX[0] = xSorted[i];
          pairX[1] =  xSorted[j];
        }
      }
    }

    double minDistY = numeric_limits<double>::infinity();
    vector <Coords> pairY;
    pairY.push_back(Coords(111110.0, 0.0));
    pairY.push_back(Coords(0.0, 1111110.0));
    for(int i = 1; i < xSorted.size(); i++)
    {
      for(int j = i+1; j < xSorted.size(); j++)
      {
        double dist = distance(ySorted[i], ySorted[j]);
        if (dist < minDistY)
        {
          minDistY = dist;
          pairY[0] = xSorted[i];
          pairY[1] = xSorted[j];
        }
      }
    }
    return minPair(pairX, pairY);
  }
  else
  {
    vector <Coords> leftX;
    vector <Coords> leftY;
    vector <Coords> rightX;
    vector <Coords> rightY;
    for(int i = 0; i < xSorted.size()/2; i++)
    {
      leftX.push_back(xSorted[i]);
    }
    for(int i = 0; i < ySorted.size()/2; i++)
    {
      leftY.push_back(ySorted[i]);
    }
    for(int i = xSorted.size()/2; i < xSorted.size(); i++)
    {
      rightX.push_back(xSorted[i]);
    }
    for(int i = ySorted.size()/2; i < ySorted.size(); i++)
    {
      rightY.push_back(ySorted[i]);
    }
    vector <Coords> dLeft = closestPoints(leftX, leftY);
    vector <Coords> dRight = closestPoints(rightX, rightY);
    //vector <Coords> tempD = minPair(dLeft, dRight);
    //double d = distance(tempD[0], tempD[1]);
    vector <Coords> theAns = minPair(dLeft, dRight);
    double d = distance(theAns[0], theAns[1]);
    double m = xSorted[(xSorted.size()/2)-1].cordX;
    vector <Coords> newYSet;
    for (int i = 0; i<ySorted.size(); i++)
    {
      if(abs(ySorted[i].cordY - m) < d)
      {
        newYSet.push_back(ySorted[i]);
      }
    }
    dminsq = pow(d,2);
    if (newYSet.size()>=2)
    {
    for(int i = 0; i<newYSet.size()-2; i++)
    {
      int k = i+1;
      while((k<=(newYSet.size()-1)) &&
      (pow((newYSet[k].cordY - newYSet[i].cordY),2)<dminsq))
      {
        dminsq = minDouble(((pow((newYSet[k].cordX-newYSet[i].cordX),2))+
        (pow((newYSet[k].cordY-newYSet[i].cordY),2))),dminsq);
        theAns[0] = newYSet[i];
        theAns[1] = newYSet[k];
        k=k+1;
      }
    }
  }
  return theAns;
  }
  //return theAns;
}


int main(int , char *argv[])
{
  ifstream inFile;
  inFile.open (argv[1]);
  assert (inFile);
  vector <Coords> sortX;
  //vector <double> xs;
  //vector <double> ys;
  int points;
  double x;
  double y;

  inFile >> points;


  while (inFile >> x >> y)
  {
    sortX.push_back(Coords(x,y));
  }

  auto start = chrono::high_resolution_clock::now();

  vector <Coords> sortY = sortX;

  double tempX, tempY;
  int sizeX = sortX.size();
  for(int i =0 ; i < sizeX; i++)
   {
     for(int j = 0; j < sizeX-1; j++)
     {
      if(sortX[j].cordX > sortX[j+1].cordX)
       {
        tempX = sortX[j].cordX;
        tempY = sortY[j].cordY;
        sortX[j] = sortX[j+1];
      }
    }
   }

   int sizeY = sortY.size();
   for(int i =0 ; i < sizeY; i++)
    {
      for(int j = 0; j < sizeY-1; j++)
      {
       if(sortY[j].cordY > sortY[j+1].cordY)
        {
         tempX = sortX[j].cordX;
         tempY = sortY[j].cordY;
         sortY[j] = sortY[j+1];
         sortY[j+1] = Coords(tempX, tempY);
        }
      }
    }

/*  cout << "Number of Point: "<< points << endl;
  for (int i = 0; i < points; i++)
  {
    printf("%.4f   %.4f\n", sortX[i].cordX, sortX[i].cordY);
    //cout << xs[i] << "  " << ys[i] << endl;
  }

  cout << "Number of Point: "<< points << endl;
  for (int i = 0; i < points; i++)
  {
    printf("%.4f   %.4f\n", sortY[i].cordX, sortY[i].cordY);
    //cout << xs[i] << "  " << ys[i] << endl;
  }
*/
  vector <Coords> answers =  closestPoints(sortX, sortY);

  auto finish = chrono::high_resolution_clock::now();
  chrono::duration<double> elapsed = finish - start;

  int ansSize = answers.size();
  cout << endl << "Of the " << points << " points, these were the closest:" << endl;
  for (int i = 0; i < ansSize; i++)
  {
    printf("%.4f   %.4f\n", answers[i].cordX, answers[i].cordY);
  }
  double finaldist = distance(answers[0], answers[1]);
  cout << "The distance between these 2 points is: ";
  printf("%.4f\n", finaldist);
  cout << "Elapsed time: " << elapsed.count() << " seconds" <<endl;
  cout << endl;
}
