#pragma once

#include "Agent.h"

class AgentSource {
public:
    virtual unique_ptr<Agent> getAgent() = 0;
};

// class PlaneBoundAgentSource

// get
// return new

class SphereRovingAgentSource : public AgentSource {
public:
    unique_ptr<Agent> getAgent(){
        return move(make_unique<SphereRovingAgent>());
    }
};