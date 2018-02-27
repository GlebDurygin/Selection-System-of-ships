#ifndef EDGE_H
#define EDGE_H

#include "Vertex.h"

class Edge {
private:
    int distance;
    Vertex* destination1;
    Vertex* destination2;
public:
    Edge() : distance(0), destination1(NULL), destination2(NULL) {}
    Edge(const Edge* element);
    ~Edge() {}

    void SetDistance(int Dist);
    void SetDestination1(Vertex* destination);
    void SetDestination2(Vertex* destination);

    int GetDistance() const;
    Vertex* GetDestination1() const;
    Vertex* GetDestination2() const;

    bool operator==(const Edge* element) const;
    bool operator!=(const Edge* element) const;
};

#endif // EDGE_H
