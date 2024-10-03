#include "position.h"
// Constructeur
Position::Position(int x, int y) {
    this->m_x = x;
    this->m_y = y;
}
Position::Position() {
    this->m_x = 0;
    this->m_y = 0;
}
// Accesseurs en lecture
int Position::getX() const {
    return m_x;
}
int Position::getY() const {
    return m_y;
}
// Accesseurs en écriture
void Position::setX(int x) {
    this->m_x = x;
}
void Position::setY(int y) {
    this->m_y = y;
}

Position Position::operator+(const Position& other) const {
    return Position(m_x + other.m_x, m_y + other.m_y);
}

bool Position::operator!=(const Position &pos1) {
    return !(m_x==pos1.m_x && m_y==pos1.m_y);
}

