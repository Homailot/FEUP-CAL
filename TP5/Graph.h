/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


/****************** Provided structures  ********************/

template <class T>
class Vertex {
	T info;                // contents
	std::vector<Edge<T> > adj;  // list of outgoing edges
	bool visited;          // auxiliary field used by dfs and bfs
	bool processing;       // auxiliary field used by isDAG
	int indegree;          // auxiliary field used by topsort

	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
public:
	Vertex(T in);
	friend class Graph<T>;
};

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
class Graph {
    std::vector<Vertex<T> *> vertexSet;    // vertex set

	void dfsVisit(Vertex<T> *v,  std::vector<T> & res) const;
	Vertex<T> *findVertex(const T &in) const;
	bool dfsIsDAG(Vertex<T> *v) const;
public:
	int getNumVertex() const;
	bool addVertex(const T &in);
	bool removeVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeEdge(const T &sourc, const T &dest);
    std::vector<T> dfs() const;
    std::vector<T> bfs(const T &source) const;
    std::vector<T> topsort() const;
	int maxNewChildren(const T &source, T &inf) const;
	bool isDAG() const;
};

/****************** Provided constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
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

/****************** 1a) addVertex ********************/

/*
 *  Adds a vertex with a given content/info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if(!findVertex(in)) {
        Vertex<T>* newVertex = new Vertex<T>(in);
        vertexSet.push_back(newVertex);
        return true;
    }

    return false;
}

/****************** 1b) addEdge ********************/

/*
 * Adds an edge to a graph (this), given the contents of the source (sourc) and
 * destination (dest) vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    Vertex<T>* source_vertex = findVertex(sourc);
    Vertex<T>* dest_vertex = findVertex(dest);

    if(source_vertex != NULL && dest_vertex != NULL) {
        source_vertex->addEdge(dest_vertex, w);

        return true;
    }

    return false;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.template emplace_back(d, w);
}


/****************** 1c) removeEdge ********************/

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    Vertex<T>* source_vertex = findVertex(sourc);
    Vertex<T>* dest_vertex = findVertex(dest);

    if(source_vertex != NULL && dest_vertex != NULL) {
        return source_vertex->removeEdgeTo(dest_vertex);
    }

    return false;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    for(auto edgeIt = adj.begin(); edgeIt != adj.end(); edgeIt++) {
        if(edgeIt->dest->info == d->info) {
            adj.erase(edgeIt);
            return true;
        }
    }

    return false;
}


/****************** 1d) removeVertex ********************/

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    Vertex<T>* vertex = findVertex(in);

    if(vertex == NULL) return false;

    for(auto vertexIt = vertexSet.begin(); vertexIt != vertexSet.end();) {
        if((*vertexIt)->info == in) {
            vertexIt = vertexSet.erase(vertexIt);
        } else {
            (*vertexIt)->removeEdgeTo(vertex);
            vertexIt++;
        }
    }
    return true;
}


/****************** 2a) dfs ********************/

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
std::vector<T> Graph<T>::dfs() const {
    std::vector<T> res;
    for(auto vertex : vertexSet) {
        vertex->visited = false;
    }

    for(auto vertex : vertexSet) {
        if (!vertex->visited) {
            dfsVisit(vertex, res);
        }
    }

    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, std::vector<T> & res) const {
    v->visited = true;
    res.push_back(v->info);

    for(auto edge : v->adj) {
        Vertex<T> * vertex = edge.dest;

        if(!vertex->visited) {
            dfsVisit(vertex, res);
        }
    }
}

/****************** 2b) bfs ********************/

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
std::vector<T> Graph<T>::bfs(const T & source) const {
    // TODO (22 lines)

    // HINT: Use the flag "visited" to mark newly discovered vertices .
    // HINT: Use the "queue<>" class to temporarily store the vertices.
    std::vector<T> res;

    Vertex<T> * vertex = findVertex(source);
    Vertex<T> * adj;
    std::queue<Vertex<T>*> vertex_queue;
    if(vertex == NULL) return res;

    for(auto vertex : vertexSet) {
        vertex->visited = false;
    }

    vertex_queue.push(vertex);
    vertex->visited = true;

    while(!vertex_queue.empty()) {
        vertex = vertex_queue.front();
        res.push_back(vertex->info);

        for(auto edge : vertex->adj) {
            adj = edge.dest;

            if(!adj->visited) {
                vertex_queue.push(adj);
                adj->visited = true;
            }
        }

        vertex_queue.pop();
    }

    return res;
}

/****************** 2c) toposort ********************/

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
std::vector<T> Graph<T>::topsort() const {
    std::vector<T> res;
    Vertex<T> * adj;

    for(auto vertex : vertexSet) vertex->indegree = 0;

    for(auto vertex : vertexSet) {
        for(auto edge: vertex->adj) {
            adj = edge.dest;

            adj->indegree++;
        }
    }
    std::queue<Vertex<T>*> candidates;

    for(auto vertex : vertexSet) if(vertex->indegree == 0) candidates.push(vertex);

    Vertex<T>* vertex;

    while(!candidates.empty()) {
        vertex = candidates.front();
        res.push_back(vertex->info);

        for(auto edge : vertex->adj) {
            adj = edge.dest;

            adj->indegree--;
            if(adj->indegree == 0) candidates.push(adj);
        }

        candidates.pop();
    }

    if(res.size() != vertexSet.size()) res.clear();

    return res;
}

/****************** 3a) maxNewChildren (HOME WORK)  ********************/

/*
 * Performs a breadth-first search in a graph (this), starting
 * from the vertex with the given source contents (source).
 * During the search, determines the vertex that has a maximum number
 * of new children (adjacent not previously visited), and returns the
 * contents of that vertex (inf) and the number of new children (return value).
 */

template <class T>
int Graph<T>::maxNewChildren(const T & source, T &inf) const {
    // TODO (28 lines, mostly reused)
    return 0;
}

/****************** 3b) isDAG   (HOME WORK)  ********************/

/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool Graph<T>::isDAG() const {
    // TODO (9 lines, mostly reused)
    // HINT: use the auxiliary field "processing" to mark the vertices in the stack.
    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
    // TODO (12 lines, mostly reused)
    return true;
}

#endif /* GRAPH_H_ */
