#pragma once
#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;


namespace PolygonalLibrary {

struct PolygonalMesh
{
    unsigned int NumberCell0D = 0; //NUMERO DI PUNTI
    vector<unsigned int> Cell0DId = {}; //VETTORE STATICO DEGLI ID DEI PUNTI
    vector<Vector2d> Cell0DCoordinates = {}; // VETTORE DI VETTORI DI COORDINATE DEI PUNTI
    map<unsigned int, list<unsigned int>> Cell0DMarkers = {}; // MAPPA DI ASSOCIAZIONE DEL MARKER AD OGNI ID DEI PUNTI

    unsigned int NumberCell1D = 0; // NUMERO DI SEGMENTI
    vector<unsigned int> Cell1DId = {}; // VETTORE STATICO DEGLI ID DEI SEGMENTI SEGMENTI
    vector<Vector2i> Cell1DVertices = {}; // VETTORE DI VETTORI DEGLI ID DEI VERTICI SEGMENTI (ORIGIN.END)
    map<unsigned int, list<unsigned int>> Cell1DMarkers = {}; //MAPPA DI ASSOCIAZIONE DEL MARKER AD OGNI ID DEI SEGMENTI

    unsigned int NumberCell2D = 0; // NUMERO DI CELLE
    vector<unsigned int> Cell2DId = {}; // VETTORE STATICO DEGLI ID DELLE CELLE
    vector<vector<unsigned int>> Cell2DVertices = {};
    vector<vector<unsigned int>> Cell2DEdges = {};
    vector<unsigned int> NumberVerticesEdges = {};
    vector<vector<unsigned int>> TrianglesVerticesId = {};
    unsigned int NumberOfTriangles = 0;

};

}
