#include <iostream>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"
#include <climits>
#include <cfloat>

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;

int main()
{
    PolygonalMesh mesh;

    string filepath = "PolygonalMesh";
    if(!ImportMesh(filepath, mesh))
    {
        return 1;
    }

    vector<double> Xcoordinates = {};
    vector<double> Ycoordinates = {};

    double x = 0.0;
    double y = 0.0;
    unsigned int i = 0;
    unsigned int j = 0;

    for(i = 0; i != mesh.NumberOfTriangles; i++)
    {
        for(j = 0; j != 3; j++)
        {
            unsigned int id = 0;
            id = mesh.TrianglesVerticesId[i][j];
            x = mesh.Cell0DCoordinates[id][0];
            y = mesh.Cell0DCoordinates[id][1];
            Xcoordinates.push_back(x);
            Ycoordinates.push_back(y);


        }

        if(polygonArea(Xcoordinates,Ycoordinates,3) <= DBL_EPSILON)
        {
            cerr << "Triangles of zero surface" << endl;
            return false;
        }

        Xcoordinates = {};
        Ycoordinates = {};
    }



}

