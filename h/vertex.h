#ifndef VERTEX_H
#define VERTEX_H

#include <QString>

class Vertex {
private:
    int id;
    QString name;
    bool pier;
    double coordX;
    double coordY;

public:
    Vertex() : name(""), id(-1), pier(false), coordX(0), coordY(0){}
    Vertex(const Vertex* element);
    ~Vertex() {}

    void SetName(QString Name);
    void SetId(int Id);
    void SetCoordX(double x);
    void SetCoordY(double y);
    void SetPier(bool Pier);

    QString GetName() const;
    int GetId() const;
    double GetCoordX()const;
    double GetCoordY()const;
    bool GetPier() const;

    bool operator==(const Vertex* element) const;
    bool operator!=(const Vertex* element) const;
};
#endif // VERTEX_H
