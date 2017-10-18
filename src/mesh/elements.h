#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <iostream>
#include <vector>
#include "element.h"
#include "nodes.h"
#include "physicalregions.h"
#include "disjointregions.h"
#include <iomanip>
#include <cmath>
#include <algorithm>
#include "orientation.h"
#include "myalgorithm.h"

class nodes;

class elements
{

	private:
        
        nodes* mynodes;
        physicalregions* myphysicalregions;
        disjointregions* mydisjointregions;
        
        // The curvature order of all elements. There can only 
        // be a single curvature order in the mesh.
        int mycurvatureorder = -1;
        
        // subelementsinelements[typenum][subtypenum] gives for element of 
        // uncurved type number 'typenum' the list of all subelements of
        // uncurved type 'subtypenum' (0, 1, 2 or 3) it is made of. 
        // [typenum][0] gives the node list in format [nodesinelement1 
        // nodesinelement2 ...], [typenum][1] the line list, [typenum][2] 
        // the triangle list and [typenum][3] the quadrangle list.
        // The element itself is not included, e.g. [0][0] is empty.
        // For nodes all curved nodes are provided. 
        std::vector<std::vector<std::vector<int>>> subelementsinelements = std::vector<std::vector<std::vector<int>>>(8, std::vector<std::vector<int>>(4,std::vector<int>(0)));
        
        // For speedup: number of subelements (nodes, lines, triangles 
        // and quadrangles) in every element.
        std::vector<std::vector<int>> numberofsubelementsineveryelement = std::vector<std::vector<int>>(8,std::vector<int>(4,0));
        
        // indisjointregion[typenum][i] gives the disjoint region number 
        // in which the ith element of type 'typenum' is.
        std::vector<std::vector<int>> indisjointregion = std::vector<std::vector<int>>(8, std::vector<int>(0));
        
        // totalorientations[typenum][i] gives the total orientation 
        // number for the ith element of type 'typenum'.
        // totalorientations[typenum] is empty if not applicable.
        std::vector<std::vector<int>> totalorientations = std::vector<std::vector<int>>(8, std::vector<int>(0));
        
	public:
        
///////// REWRITE ALL FUNCTIONS THAT ARE SPECIIFIE DFOR NODES LINES TRIANG QUAD IN A LOOP -> MORE COMPACT LESS ERROR PRONE
        
        elements(nodes&, physicalregions&, disjointregions&);
        
        // Add an element defined by its element type number, curvature order and 
        // curved nodes. Return the created element number. Only 'pointsinelements' 
        // is changed. 'elementtypenumber' is the UNCURVED element type number.
        int add(int elementtypenumber, int curvatureorder, std::vector<int>& nodelist);
        
        // 'getsubelement' returns the number of the 'subelementindex'th 
        // subelement of type 'subelementtypenumber' in element number 
        // 'elementnumber' of type 'elementtypenumber'.
        // E.g. getsubelement(0, 3, 245, 1) returns the second node in quadrangle number 245.
        int getsubelement(int subelementtypenumber, int elementtypenumber, int elementnumber, int subelementindex);
        
        int getdisjointregion(int elementtypenumber, int elementnumber);
        int gettotalorientation(int elementtypenumber, int elementnumber);
        
        // Return the number of elements of a given type.
        int count(int elementtypenumber);
        // Return the curvature order:
        int getcurvatureorder(void);
        
        // Print elements data for debug:
        void printnumber(void);
        void printsubelements(void);
        void printtotalorientations(void);
        
        // 'computebarycenters' computes the barycenter coordinates of all 
        // elements of type 'elementtypenumber'. The output vector has format 
        // [coordxelem1 coordyelem1 coordzelem1 coordxelem2 ...].
        // Only the corner element nodes are used.
        std::vector<double> computebarycenters(int elementtypenumber);
        // 'sortbybarycenters' outputs a vector v such 
        // that sortedpointsinelements(v,:) = pointsinelements.
        std::vector<int> sortbybarycenters(int elementtypenumber);
        
        // 'removeduplicates' removes the duplicated elements. 
        // NOTE: the elements must be orderd according to their 
        // barycenters before the call. The output vector v is such 
        // that sortedpointsinelements(v,:) = pointsinelements.
        std::vector<int> removeduplicates(int elementtypenumber);

        // 'renumber' updates the element numbers in 'linesinelements', 
        // 'trianglesinelements' and 'quadranglesinelements'. 'renumberingvector' 
        // is such that linesinelementsrenumbered = renumberingvector(linesinelements).
        void renumber(int elementtypenumber, std::vector<int>& renumberingvector);	
        // 'reorder' is similar to 'renumber' except that it reorders the elements
        // using 'reorderingvector' such that orderedelements = elements(reorderingvector,:);
        void reorder(int elementtypenumber, std::vector<int>& reorderingvector);	

        // 'explode' extract the subelements from the existing ones. The 
        // elements created are lines (the edges) and triangles/quadrangles 
        // (the faces) that are part of the original elements. This function 
        // creates duplicated elements that have to be uniqued afterwards.
        void explode(void);					
        
        
        // To call only after all renumbering and reordering steps:
        void definedisjointregions(void);
        // Reorder and renumber the elements by disjoint regions:
        void reorderbydisjointregions(void);
        void definedisjointregionsranges(void);
        
        // Get a vector whose index i is true if node i is a corner node:
        std::vector<bool> iscornernode(void);
        

        // 'orient' defines 'totalorientations'. Note: 'totalorientations'
        // is untouched in all renumbering and reordering steps and
        // should thus be called last, after all other steps.
        void orient(void);	

};

#endif
