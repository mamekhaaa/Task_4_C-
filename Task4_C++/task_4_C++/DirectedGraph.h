
#ifndef UNTITLED_DIRECTEDGRAPH_H
#define UNTITLED_DIRECTEDGRAPH_H

#include <vector>
#include <set>
#include <iostream>
#include <qDebug>

template<typename T>
class Edge;


template<typename T>
class Node {
public:
    explicit Node(T value) : value(value) {};

    T getValue() {
        return value;
    }

    void addEdge(Edge<T> *edge) {
        edges.push_back(edge);
    }

    std::vector<Edge<T> *> getEdges() {
        return edges;
    }

private:
    T value;
    std::vector<Edge<T> *> edges;
};

template<typename T>
class Edge {
public:
    Edge(Node<T> *from, Node<T> *to) : from(from), to(to) {

          };

    Node<T> *getTo() {
        return to;
    };

    Node<T> *getFrom() {
        return from;
    };

private:
    Node<T> *from;
    Node<T> *to;
};


template<typename T>
class DirectedGraph {
public:
    DirectedGraph() {};

    ~DirectedGraph() = default;

    void addNode(Node<T> *node) {
        nodes.push_back(node);
    };

    void addEdge(Node<T> *from, Node<T> *to) {
        Edge<T> *edge = new Edge<T>(from, to);
        from->addEdge(edge);
        edges.push_back(edge);

    };

    std::vector<Node<T> *> getNodes() {
        return nodes;
    }

    std::vector<Edge<T> *> getEdges() {
        return edges;
    }

    void dfsFromFirst() {
        std::set<Node<T> *> visited;
        dfs(nodes.front(), visited);
    }


    void dfs(Node<T> *start, std::set<Node<T> *> &visited) {
       visited.insert(start);
       qDebug() <<  "visit - " << start->getValue();
       std::vector<Edge<T>*> edges = start->getEdges();
        for (Edge<T> *edge: edges) {
            Node<T> *neighbour = edge->getTo();

            if (visited.find(neighbour) == visited.end()) {

                dfs(neighbour, visited);

            }
        }

    }

    void DFS(Node<T> *start, std::set<Node<T> *> &visited, std::vector<Node<T>*> &component) {
        visited.insert(start);
        component.push_back(start);
        for (Edge<T> *edge: start->getEdges()) {
            Node<T> *neighbour = edge->getTo();

            if (visited.find(neighbour) == visited.end()) {
                DFS(neighbour, visited, component);
            }
        }
    }

    std::vector<std::vector<Node<T>*>> findConnectedComponents() {
        std::vector<std::vector<Node<T>*>> connectedComponents;
        std::set<Node<T> *> visited;

        for (Node<T> *node: nodes) {
            if (visited.find(node) == visited.end()) {
                std::vector<Node<T>*> component;
                DFS(node, visited, component);
                connectedComponents.push_back(component);
            }
        }

        return connectedComponents;
    }


    Node<T>* findNodeByValue(T value) {
        for (Node<T>* node : nodes) {
            if (node->getValue() == value) {
                return node;
            }
        }
        Node<T> *node1 = new Node<T>(value);
        addNode(node1);
        return node1;
    }

    void clear(){
        nodes.clear();
        edges.clear();
    }


private:
    std::vector<Node<T> *> nodes;
    std::vector<Edge<T> *> edges;


};


#endif //UNTITLED_DIRECTEDGRAPH_H
