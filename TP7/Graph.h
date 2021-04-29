/*
 * Graph.h.
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_set>
#include "MutablePriorityQueue.h"

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
    friend double spanningTreeCost(const std::vector<Vertex<int>*> &);
	T info;                 // contents
	std::vector<Edge<T> *> adj;  // outgoing edges

	bool visited;
	double dist = 0;
	Vertex<T> *path = nullptr;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	// Fp07 - minimum spanning tree (Kruskal)
	int id;
	int rank;

	Edge<T> * addEdge(Vertex<T> *dest, double w);
public:
	Vertex(T in);
	bool operator<(const Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;
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
Edge<T> *Vertex<T>::addEdge(Vertex<T> *d, double w) {
	Edge<T> *e = new Edge<T>(this, d, w);
	adj.push_back(e);
	return e;
}

template <class T>
bool Vertex<T>::operator<(const Vertex<T> & vertex) const {
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
	Vertex<T> *orig; 		    // Fp07
	Vertex<T> * dest;           // destination vertex
	double weight;              // edge weight
	bool selected = false;      // Fp07
	Edge<T> *reverse = nullptr; // Fp07
public:
	Edge(Vertex<T> *o, Vertex<T> *d, double w);
    Edge();
	friend class Graph<T>;
	friend class Vertex<T>;
    bool operator<(const Edge<T> & edge) const;

	double getWeight() const;
	Vertex<T> *getOrig() const;
	Vertex<T> *getDest() const;
};

template <class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, double w): orig(o), dest(d), weight(w) {}

template <class T>
double Edge<T>::getWeight() const {
	return weight;
}

template <class T>
Vertex<T> *Edge<T>::getOrig() const {
	return orig;
}

template <class T>
Vertex<T> *Edge<T>::getDest() const {
	return dest;
}
template<class T>
bool Edge<T>::operator<(const Edge<T> &edge) const {
    return weight > edge.weight;
}


/*************************** Graph  **************************/

template<class T>
struct CmpEdgePtrs {
    bool operator()(const Edge<T> * lhs, const Edge<T> * rhs) const {
        return lhs->getWeight() > rhs->getWeight();
    }
};

template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;    // vertex set

	// Fp07 (Kruskal's algorithm)
	void makeSet(Vertex<T> * x);
	Vertex<T> * findSet(Vertex<T> * x);
	void linkSets(Vertex<T> * x, Vertex<T> * y);
	void dfsKruskalPath(Vertex<T> *v);
    std::priority_queue<Edge<T>*, std::vector<Edge<T>*>, CmpEdgePtrs<T>> edgesToQueue();


public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool addBidirectionalEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
    std::vector<Vertex<T> *> getVertexSet() const;
	~Graph();

	// Fp07 - minimum spanning tree
	std::vector<Vertex<T>*> calculatePrim();
	std::vector<Vertex<T>*> calculateKruskal();
};

template<class T>
Edge<T>::Edge() {
    orig = nullptr;
    dest = nullptr;
}


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
	return nullptr;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if (findVertex(in) != nullptr)
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
	if (v1 == nullptr || v2 == nullptr)
		return false;
	v1->addEdge(v2, w);
	return true;
}

template <class T>
bool Graph<T>::addBidirectionalEdge(const T &sourc, const T &dest, double w) {
    Vertex<T>* sourceVertex = findVertex(sourc);
    if(sourceVertex == nullptr) return false;
    Vertex<T>* destVertex = findVertex(dest);
    if(destVertex == nullptr) return false;

    Edge<T>* sourceDest = sourceVertex->addEdge(destVertex, w);
    Edge<T>* destSource = destVertex->addEdge(sourceVertex, w);

    sourceDest->reverse = destSource;
    destSource->reverse = sourceDest;

    return true;
}

template <class T>
Graph<T>::~Graph() {
    /*
	for (auto v : vertexSet) {
		for (auto e : v->adj)
			delete e;
		delete v;
	}
    */
}

/**************** Minimum Spanning Tree  ***************/

template <class T>
std::vector<Vertex<T>* > Graph<T>::calculatePrim() {
    if(vertexSet.empty()) return vertexSet;

    for(Vertex<T>* vertex : vertexSet) {
        vertex->visited = false;
        vertex->path = nullptr;
        vertex->dist = std::numeric_limits<double>::infinity();
    }

    MutablePriorityQueue<Vertex<T>> priorityQueue;
    Vertex<T>* curVertex, *nextVertex;

    curVertex = vertexSet.front();
    curVertex->dist = 0;
    priorityQueue.insert(curVertex);


    while(!priorityQueue.empty()) {
        curVertex = priorityQueue.extractMin();
        curVertex->visited = true;

        for(Edge<T>* adjEdge : curVertex->adj) {
            nextVertex = adjEdge->dest;

            if(!nextVertex->visited && adjEdge->weight < nextVertex->dist) {
                nextVertex->dist = adjEdge->weight;

                if(nextVertex->path == nullptr) {
                    priorityQueue.insert(nextVertex);
                } else {
                    priorityQueue.decreaseKey(nextVertex);
                }

                nextVertex->path = curVertex;
            }
        }
    }

    return vertexSet;
}

/**
 * Disjoint sets operations (page 571, Introduction to Algorithms) for Kruskal's algorithm.
 */

template <class T>
void Graph<T>::makeSet(Vertex<T> * x) {
	x->path = x;
	x->rank = 0;
}

template <class T>
void Graph<T>::linkSets(Vertex<T> * x, Vertex<T> * y) {
	if (x->rank > y->rank)
		y->path = x;
	else {
		x->path = y;
		if (x->rank == y->rank)
			y->rank++;
	}
}

template <class T>
Vertex<T> * Graph<T>::findSet(Vertex<T> * x) {
	if (x != x->path)
		x->path = findSet(x->path);
	return x->path;
}



/**
 * Implementation of Kruskal's algorithm to find a minimum
 * spanning tree of an undirected connected graph (edges added with addBidirectionalEdge).
 * It is used a disjoint-set data structure to achieve a running time O(|E| log |V|).
 * The solution is defined by the "path" field of each vertex, which will point
 * to the parent vertex in the tree (nullptr in the root).
 */
template <class T>
std::vector<Vertex<T>*> Graph<T>::calculateKruskal() {
    if(vertexSet.empty()) return vertexSet;
    int edgesAccepted = 0;

    for(Vertex<T>* vertex : vertexSet) {
        vertex->visited = false;
        vertex->path = nullptr;
    }

    std::priority_queue<Edge<T>*, std::vector<Edge<T>*>, CmpEdgePtrs<T>> edgeQueue = edgesToQueue();
    for(Vertex<T>* vertex : vertexSet) {
        makeSet(vertex);
    }

    Edge<T> curEdge;
    while(edgesAccepted < getNumVertex() - 1) {
        Edge<T>* edge = edgeQueue.top();
        Vertex<T>* sourceSet = findSet(edge->orig);
        Vertex<T>* destSet = findSet(edge->dest);

        if(sourceSet != destSet) {
            edge->selected = true;
            edge->reverse->selected = true;
            edgesAccepted++;
            linkSets(sourceSet, destSet);
        }

        edgeQueue.pop();
    }

    dfsKruskalPath(vertexSet.front());

    return vertexSet;
}

#include <stack>

/**
 * Auxiliary function to set the "path" field to make a spanning tree.
 */
template <class T>
void Graph<T>::dfsKruskalPath(Vertex<T> *v) {
    v->path = nullptr;

    std::stack<Vertex<T>*> vertexStack;
    Vertex<T>* curVertex, * nextVertex;
    vertexStack.push(v);

    while(!vertexStack.empty()) {
        Vertex<T>* curVertex = vertexStack.top();
        curVertex->visited = true;
        vertexStack.pop();

        for(Edge<T>* edge : curVertex->adj) {
            if(edge->selected) {
                nextVertex = edge->dest;
                if(nextVertex->visited) continue;

                nextVertex->path = curVertex;
                vertexStack.push(edge->dest);
            }
        }
    }
}

template<class T>
std::priority_queue<Edge<T>*, std::vector<Edge<T>*>, CmpEdgePtrs<T>> Graph<T>::edgesToQueue() {
    std::priority_queue<Edge<T>*, std::vector<Edge<T>*>, CmpEdgePtrs<T>> edgeQueue;

    for(Vertex<T>* vertex : vertexSet) {
        for(Edge<T>* edge : vertex->adj) {
            edgeQueue.push(edge);
        }
    }

    return edgeQueue;
}

#endif /* GRAPH_H_ */
