#include "proj2.hpp"
#include "LLQueue.hpp"
#include <vector>
#include <algorithm>

// finding shortest path.
// recursion, have a counter that counts and then return a list of values and take max
// or while loop implmenting a queue to track.

const bool DEBUG = false;

void countPaths(const std::vector< std::vector<unsigned> > & friends, unsigned start, std::vector<unsigned> & pathLengths, std::vector<unsigned> & numShortestPaths)
{
    
    // declarations
    std::vector<unsigned> histVect;
    LLQueue<unsigned> verticesQu;

    // initializations
    unsigned layer = 0; // current layer
    unsigned counter = 0; // tracker number of vertices in layer
    unsigned nodesInLayer = 0; // size of current layer
    verticesQu.enqueue(start);
    histVect.push_back(start);
    numShortestPaths[start] = 1; // first node is always going to have a short path to itself

    while ( !verticesQu.isEmpty() ) {

        pathLengths[start] = layer;
        

        // if new layer, stores number of vertices in the current layer
        if (counter == nodesInLayer) {
            nodesInLayer = verticesQu.size();
        }
        
        // enqueues the neighboring vertices
        for (unsigned i: friends[start]) {

            // checks for shortest path
            for (unsigned j: histVect) {
                if (start == j) {
                    break;
                } else {
                    if (i == j && pathLengths[start] != pathLengths[j]) {
                        numShortestPaths[start] += numShortestPaths[j];
                    }
                }
            }

            // Breadth first search
            if ( std::find(histVect.begin(), histVect.end(), i) == histVect.end() ){
                verticesQu.enqueue(i);
                histVect.push_back(i);
                if (DEBUG) std::cout << i << std::endl;
            }

            
        } // each one added once through accumuliation
        verticesQu.dequeue();
        if ( verticesQu.isEmpty() ) break;
        start = verticesQu.front();

        
        // if no more vertices in current layer, increment layer and reset variables
        counter++;
        if (counter == nodesInLayer) {
            layer++;
            nodesInLayer = 0;
            counter = 0;
        }
        
    }

    // print output
    if (DEBUG) {
        for (unsigned i = 0; i < pathLengths.size(); ++i) {
            std::cout << i << " : " << pathLengths[i] << " | "<< numShortestPaths[i] << std::endl;
        }
    }
        
}
