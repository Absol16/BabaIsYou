#ifndef POSITION_H
#define POSITION_H

class Position {
private:
    int m_x;
    int m_y;
public:
    // Default constructor, initializes x and y to 0
    Position();

    // Constructor that initializes x and y to given values
    Position(int x, int y);

    // Getter method for x
    int getX() const;

    // Getter method for y
    int getY() const;

    // Setter method for x
    void setX(int x);

    // Setter method for y
    void setY(int y);

    // Overloaded operator+ that returns a new Position object
    // with x and y values added together
    Position operator+(const Position& other) const;

    // Overloaded operator!= that compares the x and y values
    // of two Position objects
    bool operator!=(const Position &pos1);
};

#endif // POSITION_H
