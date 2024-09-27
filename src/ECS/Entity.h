#pragma once

class Entity {
public:
    explicit Entity(unsigned int id) : m_id(id) {}
    unsigned int GetID() const { return m_id; }

private:
    unsigned int m_id;
};
