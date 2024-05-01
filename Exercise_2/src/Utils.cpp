#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

namespace PolygonalLibrary {
bool ImportMesh(const string& filepath, PolygonalMesh& mesh)
{

    //------------------------------------------------------------------------------------------------------------------------------------------

    if(!ImportCell0Ds(filepath + "/Cell0Ds.csv", mesh))
    {
        return false;
    }
    else
    {
        cout << "Cell0D marker:" << endl;
        for(auto it = mesh.Cell0DMarkers.begin(); it != mesh.Cell0DMarkers.end(); it++)
        {
            cout << "key:\t" << it -> first << "\t values:";
            for(const unsigned int id : it -> second)
                cout << "\t" << id;

            cout << endl;
        }
    }

    //------------------------------------------------------------------------------------------------------------------------------------------

    if(!ImportCell1Ds(filepath + "/Cell1Ds.csv", mesh))
    {
        return false;
    }
    else
    {
        cout << "Cell1D marker:" << endl;
        for(auto it = mesh.Cell1DMarkers.begin(); it != mesh.Cell1DMarkers.end(); it++)
        {
            cout << "key:\t" << it -> first << "\t values:";
            for(const unsigned int id : it -> second)
                cout << "\t" << id;

            cout << endl;
        }
    }

    //------------------------------------------------------------------------------------------------------------------------------------------

    if(!ImportCell2Ds(filepath + "/Cell2Ds.csv", mesh))
    {
        return false;
    }
    else
    {
        cout << "Cell2D: " << endl;

        for(unsigned int i = 0; i != mesh.NumberCell2D; i++ )
        {
            cout << "Cell " << i << ": ";

            cout << "Vertices: ";

            for(unsigned int j = 0; j != mesh.NumberVerticesEdges[i]; j++ )
            {
                cout << mesh.Cell2DVertices[i][j] << " ";
            }

            cout << "\t";

            cout << "Edges: ";

            for(unsigned int j = 0; j != mesh.NumberVerticesEdges[i]; j++ )
            {
                cout << mesh.Cell2DEdges[i][j] << " ";
            }
            cout << endl;

        }

        return true;

    }

}

    //------------------------------------------------------------------------------------------------------------------------------------------

bool ImportCell0Ds(const string &filename, PolygonalMesh& mesh)
{

    ifstream file;
    file.open(filename);

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    listLines.pop_front();

    mesh.NumberCell0D = listLines.size();

    if (mesh.NumberCell0D == 0)
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }

    mesh.Cell0DId.reserve(mesh.NumberCell0D);
    mesh.Cell0DCoordinates.reserve(mesh.NumberCell0D);

    for (string& line : listLines)
    {
        replace(line.begin(),line.end(), ';',' ');
        istringstream converter(line);


        unsigned int id;
        unsigned int marker;
        Vector2d coord;

        converter >>  id >> marker >> coord(0) >> coord(1);

        mesh.Cell0DId.push_back(id);
        mesh.Cell0DCoordinates.push_back(coord);

        if( marker != 0)
        {
            auto ret = mesh.Cell0DMarkers.insert({marker, {id}});
            if(!ret.second)
                (ret.first)->second.push_back(id);
        }

    }
    file.close();
    return true;
}

    //------------------------------------------------------------------------------------------------------------------------------------------

bool ImportCell1Ds(const string &filename, PolygonalMesh& mesh)
{

    ifstream file;
    file.open(filename);

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    listLines.pop_front();

    mesh.NumberCell1D = listLines.size();

    if (mesh.NumberCell1D == 0)
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }

    mesh.Cell1DId.reserve(mesh.NumberCell1D);
    mesh.Cell1DVertices.reserve(mesh.NumberCell1D);

    for (string& line : listLines)
    {
        replace(line.begin(),line.end(), ';',' ');
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2i vertices;

        converter >>  id >> marker >> vertices(0) >> vertices(1);
        if(vertices(0) == vertices(1))
        {           
            cerr << "Zero Lenght Edges" << endl;
            return false;
        }

        mesh.Cell1DId.push_back(id);
        mesh.Cell1DVertices.push_back(vertices);

        if( marker != 0)
        {
            auto ret = mesh.Cell1DMarkers.insert({marker, {id}});
            if(!ret.second)
                (ret.first)->second.push_back(id);
        }
    }



    file.close();

    return true;
}

    //------------------------------------------------------------------------------------------------------------------------------------------

bool ImportCell2Ds(const string &filename, PolygonalMesh& mesh)
{

    ifstream file;
    file.open(filename);

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    listLines.pop_front();

    mesh.NumberCell2D = listLines.size();

    if (mesh.NumberCell2D == 0)
    {
        cerr << "There is no cell 2D" << endl;
        return false;
    }

    mesh.Cell2DId.reserve(mesh.NumberCell2D);
    mesh.NumberVerticesEdges.reserve(mesh.NumberCell2D);

    for (string& line : listLines)
    {
        replace(line.begin(),line.end(), ';',' ');
        istringstream converter(line);
        unsigned int id;
        unsigned int NumberVertices;
        unsigned int NumberEdges;
        unsigned int tmp;
        converter >> id >> tmp;

        converter >> NumberVertices;
        mesh.NumberVerticesEdges.push_back(NumberVertices);
        vector<unsigned int> vertices = {};
        vertices.reserve(NumberVertices);


        for(unsigned int i = 0; i < NumberVertices ; i++)
        {
            converter >> tmp;
            if( count(vertices.begin(),vertices.end(),tmp) !=0 )
            {
                cerr << " Zero Lenght Edges " << endl;
                return false;
            }
            vertices.push_back(tmp);

        }

        converter >> NumberEdges;
        vector<unsigned int> edges = {};
        edges.reserve(NumberEdges);

        for(unsigned int i = 0; i < NumberEdges; i++)
        {
            converter >> tmp;
            edges.push_back(tmp);
        }

        mesh.Cell2DEdges.push_back(edges);
        mesh.Cell2DVertices.push_back(vertices);
        mesh.Cell2DId.push_back(id);

        if(NumberVertices == 3)
        {
            mesh.TrianglesVerticesId.push_back(vertices);
            mesh.NumberOfTriangles ++;
        }

    }
    file.close();
    return true;
}



}

double polygonArea(vector<double> &x, vector<double> &y, int n)
{

    double area = 0.0;

    int j= n - 1;
    for(int i = 0; i<n;i++)
    {
        area += (x[j] + x[i]) * (y[j] - y[i]);
        j = i;
    }

    return abs(area / 2.0);


}
