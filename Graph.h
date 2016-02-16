// ----------------------
// projects/graph/Graph.h
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------

#ifndef Graph_h
#define Graph_h

// --------
// includes
// --------

#include <cassert> // assert
#include <cstddef> // size_t
#include <utility> // make_pair, pair
#include <vector>  // vector
#include <set>     // set


// -----
// Graph
// -----

class Graph {
    public:
        // --------
        // typedefs
        // --------

        typedef int vertex_descriptor;  
        typedef std::pair<vertex_descriptor, vertex_descriptor> edge_descriptor;    

        public:
            class vertex_iterator : public std::iterator<std::bidirectional_iterator_tag, vertex_descriptor>{
                public:
                    friend bool operator == (const vertex_iterator& lhs, const vertex_iterator& rhs) {
                        return (lhs._it == rhs._it);}

                    friend bool operator != (const vertex_iterator& lhs, const vertex_iterator& rhs) {
                        return !(lhs == rhs);}

                    friend vertex_iterator operator + (vertex_iterator lhs, int rhs){
                        return lhs += rhs;
                    }

                    friend vertex_iterator operator - (vertex_iterator lhs, int rhs){
                        return lhs -= rhs;
                    }

                private:
                    std::set<vertex_descriptor>::const_iterator _it;

                public:
                    vertex_iterator(std::set<vertex_descriptor>::const_iterator IT) : _it(IT){
                        _it = IT;
                    }

                    vertex_descriptor operator * () const{
                        const vertex_descriptor v = *_it;
                        return v;
                    }
                    vertex_iterator operator ++ (int) {
                        return _it++;
                    }
                    vertex_iterator operator -- (int) {
                        return _it--;
                    }
                    vertex_iterator operator ++ () {
                        return ++_it;
                    }
                    vertex_iterator operator -- () {
                        return --_it;
                    }
                    //This is Linear, bad Andrew, Too slow
                    vertex_iterator& operator += (int d){
                        while(d > 0){
                            ++(*this);
                            --d;
                        }
                        return *this;
                    }
                    vertex_iterator& operator -= (int d){
                        while(d > 0){
                            --(*this);
                            --d;
                        }
                        return *this;
                    }
            };

        typedef std::set<edge_descriptor>::const_iterator edge_iterator;

       

        typedef std::set<vertex_descriptor>::const_iterator adjacency_iterator; 

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;

    public:
        // --------
        // add_edge
        // --------

        /*
        Structure Modification
        Adds edge (u,v) to the graph and returns the edge descriptor for the new edge. For graphs that do not allow parallel 
        edges, if the edge is already in the graph then a duplicate will not be added and the bool flag will be false. When 
        the flag is false, the returned edge descriptor points to the already existing edge.
        */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor u, vertex_descriptor v, Graph& g) {
            bool b;
            edge_descriptor ed;
            
            //If vertex does not excist, create all vertexes up to and including that one
            while((int)(g.list).size() <= v){
                add_vertex(g);
            }
            while((int)(g.list).size() <= u){
                add_vertex(g);
            }

            b = ((g.list)[u].insert(v)).second;

            ed = std::make_pair(u, v);

            (g.edgS).insert(ed);

            return std::make_pair(ed, b);
        }

        // ----------
        // add_vertex
        // ----------

        /*
        Structure Modification
        Adds a vertex to the graph and returns the vertex descriptor for the new vertex.
        */
        friend vertex_descriptor add_vertex (Graph& g) {
            vertex_descriptor v = (g.list).size();
            std::set<vertex_descriptor> s;
            (g.list).push_back(s);
            (g.vecS).insert(v + 1); 
            return v;
        }

        // -----------------
        // adjacent_vertices
        // -----------------

        /*
        Non-Member Function
        Returns an iterator-range providing access to the vertices adjacent to vertex u in graph g. For example, if u -> v is 
        an edge in the graph, then v will be in this iterator-range.
        */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor u, const Graph& g) {
            adjacency_iterator b = (g.list)[u].begin();
            adjacency_iterator e = (g.list)[u].end();
            return std::make_pair(b, e);
        }

        // ----
        // edge
        // ----

        /*
        Non-Member Function
        If an edge from vertex u to vertex v exists, return a pair containing one such edge and true. If there are no edges 
        between u and v, return a pair with an arbitrary edge descriptor and false.
        */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor u, vertex_descriptor v, const Graph& g) {
            edge_descriptor ed = std::make_pair(u, v);
            bool b;
            int size = (g.list).size();

            if((v < size) && (u < size)){
                if((g.list)[u].find(v) != (g.list)[u].end()){
                    b = true;
                }
                else{
                    b = false;
                }
            }
            else{
                b = false;
            }

            return std::make_pair(ed, b);
        }

        // -----
        // edges
        // -----

        /*
        Non-Member Function
        Returns an iterator-range providing access to the edge set of graph g.
        */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& g) {    
            edge_iterator b = (g.edgS).begin();
            edge_iterator e = (g.edgS).end();
            return std::make_pair(b, e);
        }

        // ---------
        // num_edges
        // ---------

        /*
        Non-Member Function
        Returns the number of edges in the graph g.
        */
        friend edges_size_type num_edges (const Graph& g) {
            edges_size_type s = (g.edgS).size(); 
            return s;
        }

        // ------------
        // num_vertices
        // ------------

        /*
        Non-Member Function
        Returns the number of vertices in the graph g.
        */
        friend vertices_size_type num_vertices (const Graph& g) {
            vertices_size_type s = (g.list).size(); 
            return s;
        }

        // ------
        // source
        // ------

        /*
        Non-Member Function
        Returns the source vertex of edge e.
        */
        friend vertex_descriptor source (edge_descriptor e, const Graph& g) {
            vertex_descriptor v = e.first; 
            return v;
        }

        // ------
        // target
        // ------

        /*
        Non-Member Function
        Returns the target vertex of edge e.
        */
        friend vertex_descriptor target (edge_descriptor e, const Graph& g) {
            vertex_descriptor v = e.second; 
            return v;
        }

        // ------
        // vertex
        // ------

        /*
        Non-member Function
        Returns the nth vertex in the graph's vertex list.
        */
        friend vertex_descriptor vertex (vertices_size_type n, const Graph& g) {
            return n;
        }

        // --------
        // vertices
        // --------

        /*
        Non-Member Function
        Returns an iterator-range providing access to the vertex set of graph g.
        */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph& g) {
            vertex_iterator b = (g.vecS).begin();
            vertex_iterator e = --(g.vecS).end();
            return std::make_pair(b, e);
        }

    private:
        // ----
        // data
        // ----

        std::vector< std::set<vertex_descriptor> > list; // something like this, represent the vertex
        std::set< vertex_descriptor > vecS;
        std::set< edge_descriptor> edgS;

        // -----
        // valid
        // -----

        /*
        Determines if the Graph you are operating on is valid.
        */
        bool valid () const {
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /*
        Member Function
        Default Constructor
        Creates an empty graph object with zero vertices and zero edges.
        */
        Graph () {
            vecS.insert(0);
            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };

#endif // Graph_h
