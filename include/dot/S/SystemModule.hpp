#pragma once

#include <vector>
#include <memory>

#include "dot/E/Entity.hpp"

namespace dot {
class SystemModule {
public:
    SystemModule() {}

    virtual ~SystemModule() {}

    virtual void add(std::vector<std::shared_ptr<dot::Entity>>& entities) = 0;
    virtual void add(std::shared_ptr<dot::Entity>& entity) = 0;

    virtual void update(float deltaTime) {}
    virtual void lateUpdate(float deltaTime) {}
    virtual void processRemovals() = 0;
private:

}; // class SystemModule 

}; // namespace dot