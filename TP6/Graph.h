/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"


template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
    T info;						// content of the vertex
    std::vector<Edge<T> > adj;		// outgoing edges

    double dist = 0;
    Vertex<T> *path = NULL;
    int queueIndex = 0; 		// required by MutablePriorityQueue

    bool visited = false;		// auxiliary field
    bool processing = false;	// auxiliary field

    void addEdge(Vertex<T> *dest, double w);

public:
    Vertex(T in);
    T getInfo() const;
    double getDist() const;
    Vertex *getPath() const;

    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex<T> *d, double w);
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;    // vertex set

public:
    Vertex<T> *findVertex(const T &in) const;
    bool addVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w);
    int getNumVertex() const;
    std::vector<Vertex<T> *> getVertexSet() const;
    std::vector<std::pair<Vertex<T>*,Edge<T>>> getEdges() const;

    // Fp06 - single source
    void unweightedShortestPath(const T &s);    //TODO...
    void dijkstraShortestPath(const T &s);      //TODO...
    void bellmanFordShortestPath(const T &s);   //TODO...
    std::vector<T> getPath(const T &origin, const T &dest) const;   //TODO...

    // Fp06 - all pairs
    void floydWarshallShortestPath();   //TODO...
    std::vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    std::queue<Vertex<T>*> vertexQueue;

    Vertex<T> * origVertex = findVertex(orig);
    Vertex<T> * newVertex, * nextVertex;
    if(origVertex == NULL) return;

    for(Vertex<T> * vertex : vertexSet) {
        vertex->visited = false;
        vertex->path = nullptr;
    }

    vertexQueue.push(origVertex);
    origVertex->visited = true;

    while(!vertexQueue.empty()) {
        newVertex = vertexQueue.front();
        vertexQueue.pop();

        for(Edge<T> edge : newVertex->adj) {
            nextVertex = edge.dest;

            if(!nextVertex->visited) {
                nextVertex->visited = true;
                nextVertex->path = newVertex;

                vertexQueue.push(nextVertex);
            }
        }
    }
}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    MutablePriorityQueue<Vertex<T>> vertexQueue;

    Vertex<T> * origVertex = findVertex(origin);
    Vertex<T> * newVertex, * nextVertex;
    double newDist;
    if(origVertex == NULL) return;

    for(Vertex<T> * vertex : vertexSet) {
        vertex->visited = false;
        vertex->path = nullptr;
        vertex->dist = INF;
    }

    origVertex->dist = 0;
    vertexQueue.insert(origVertex);

    while(!vertexQueue.empty()) {
        newVertex = vertexQueue.extractMin();

        for(Edge<T> edge : newVertex->adj) {
            nextVertex = edge.dest;

            newDist = newVertex->dist + edge.weight;
            if(nextVertex->dist > newDist) {
                nextVertex->dist = newDist;
                nextVertex->path = newVertex;

                if(!nextVertex->visited) {
                    vertexQueue.insert(nextVertex);

                    nextVertex->visited = true;
                } else vertexQueue.decreaseKey(nextVertex);
            }
        }
    }
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    Vertex<T> * origVertex = findVertex(orig);
    Vertex<T> * sourceVertex, * destVertex;
    std::vector<std::pair<Vertex<T>*,Edge<T>>> edges = getEdges();
    double newDist, weight;
    if(origVertex == NULL) return;

    for(Vertex<T> * vertex : vertexSet) {
        vertex->path = nullptr;
        vertex->dist = INF;
    }

    origVertex->dist = 0;

    for(size_t i = 0; i < getNumVertex(); i++) {
        for(std::pair<Vertex<T>*, Edge<T>> edge : edges) {
            sourceVertex = edge.first;
            destVertex = edge.second.dest;
            weight = edge.second.weight;

            newDist = sourceVertex->dist + weight;

            if(destVertex->dist > newDist) {
                destVertex->dist = newDist;
                destVertex->path = sourceVertex;
            }
        }
    }

    for(std::pair<Vertex<T>*, Edge<T>> edge : edges) {
        sourceVertex = edge.first;
        destVertex = edge.second.dest;
        weight = edge.second.weight;

        if(sourceVertex->dist + weight < destVertex->dist) {
            origVertex->dist = INF;
        }
    }
}


template<class T>
std::vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
    std::vector<T> res;

    Vertex<T>* origVertex = findVertex(origin);
    if(origVertex == NULL) return {};
    Vertex<T>* destVertex = findVertex(dest);
    if(destVertex == NULL) return {};

    Vertex<T>* nextVertex;

    res.push_back(destVertex->info);

    while(destVertex != origVertex) {
        destVertex = destVertex->path;
        if(destVertex == NULL) return res;

        res.insert(res.begin(), destVertex->info);
    }

    return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    // TODO implement this
}

template<class T>
std::vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
    std::vector<T> res;
    // TODO implement this
    return res;
}

template<class T>
std::vector<std::pair<Vertex<T>*,Edge<T>>> Graph<T>::getEdges() const {
    std::vector<std::pair<Vertex<T>*,Edge<T>>> edges;

    for(Vertex<T>* vertex: vertexSet) {
        for(Edge<T> edge : vertex->adj) {
            edges.push_back(std::make_pair(vertex, edge));
        }
    }

    return edges;
}


#endif /* GRAPH_H_ */
