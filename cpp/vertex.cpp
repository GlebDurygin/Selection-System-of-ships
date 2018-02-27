#include "vertex.h"

Vertex::Vertex(const Vertex* element) {
    name = element->name;
    id = element->id;
    coordX = element->coordX;
    coordY = element->coordY;
}
void Vertex::SetName(QString Name) {
    this->name = Name;
}
void Vertex::SetId(int Id) {
    this->id = Id;
}
void Vertex::SetCoordX(double x) {
    this->coordX = x;
}
void Vertex::SetCoordY(double y) {
    this->coordY = y;
}
void Vertex::SetPier(bool Pier) {
    this->pier = Pier;
}
QString Vertex::GetName() const {
    return this->name;
}
int Vertex::GetId() const {
    return this->id;
}
double Vertex::GetCoordX() const{
    return this->coordX;
}
double Vertex::GetCoordY() const{
    return this->coordY;
}
bool Vertex::GetPier() const{
    return this->pier;
}
bool Vertex::operator==(const Vertex* element) const {
    return (this->id == element->id);
}
bool Vertex::operator!=(const Vertex* element) const {
    return !(this == element);
}
