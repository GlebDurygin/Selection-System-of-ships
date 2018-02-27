#include "edge.h"

Edge::Edge(const Edge* element) {
    distance = element->distance;
    destination1 = element->destination1;
    destination2 = element->destination2;
}
void Edge::SetDistance(int Dist) {
    this->distance = Dist;
}
int Edge::GetDistance() const {
    return this->distance;
}
void Edge::SetDestination1(Vertex* destination) {
    this->destination1 = destination;
}
Vertex* Edge::GetDestination1() const {
    return this->destination1;
}
void Edge::SetDestination2(Vertex* destination) {
    this->destination2 = destination;
}
Vertex* Edge::GetDestination2() const {
    return this->destination2;
}

bool Edge::operator==(const Edge* element) const {
    return (this->destination1 == element->destination1 && this->destination2==element->destination2);
}
bool Edge::operator!=(const Edge* element) const {
    return !(this == element);
}
