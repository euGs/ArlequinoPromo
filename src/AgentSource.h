#pragma once

#include "Agent.h"

class AgentSource {
public:
    virtual unique_ptr<Agent> getAgent() = 0;
};

// class PlaneRovingAgentSource

class SphereRovingAgentSource : public AgentSource {
public:
    unique_ptr<Agent> getAgent(){
        return move(make_unique<SphereRovingAgent>());
    }
};