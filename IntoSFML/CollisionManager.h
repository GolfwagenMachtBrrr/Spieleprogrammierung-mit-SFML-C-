#pragma once
#include <vector>
#include "GameObject.h"

class CollisionManager {
private:
    std::vector<GameObject*> m_objects;
public:
    
    void checkCollisions() {
        for (size_t i = 0; i < m_objects.size(); ++i) {
            for (size_t j = i + 1; j < m_objects.size(); ++j) {
                if (m_objects[i]->GetBoundingBox().intersects(m_objects[j]->GetBoundingBox())) {

                    m_objects[i]->OnCollision(*m_objects[j]);
                    m_objects[j]->OnCollision(*m_objects[i]);
                }
            }
        }
    }

    void addObject(GameObject* obj) {
        obj->objectID = m_objects.size(); 
        m_objects.push_back(obj);
    }

    void clearObjects() {
        m_objects.clear();
    }

};
