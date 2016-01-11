#pragma once

#include "Agent.h"

class AgentSource {
public:
    virtual void setup() = 0;
    virtual unique_ptr<Agent> getAgent() = 0;
};

class SphereRovingAgentSource : public AgentSource {
public:
    void setup(){
    }
    
    unique_ptr<Agent> getAgent(){
        return move(make_unique<SphereRovingAgent>());
    }
};

class PivotingSphereRovingAgentSource : public AgentSource {
public:
    void setup(){
    }
    
    unique_ptr<Agent> getAgent(){
        return move(make_unique<PivotingSphereRovingAgent>());
    }
};

class TextRovingAgentSource : public AgentSource {
public:
    void setup(){
        ofTrueTypeFont font;
        font.load("Ubuntu-R.ttf", 600, true, false, true);
        
        vector<ofTTFCharacter> letterPaths = font.getStringAsPoints("ARLEQUINO", false);
        
        for (auto letterPath : letterPaths){
            shared_ptr<ofMesh> mesh = make_shared<ofMesh>(letterPath.getTessellation());
            letterMeshes.push_back(mesh);
        }
    }
    
    unique_ptr<Agent> getAgent(){
        if (letterMeshes.size() == 0){
            ofLogWarning() << "TextRovingAgentSource::letterMeshes.size() == 0. Probably forgot to call TextRovingAgentSource::setup()" << endl;
        }
        
        unique_ptr<MeshRovingAgent> agent = make_unique<MeshRovingAgent>();
        agent->setMesh(letterMeshes[ofRandom(letterMeshes.size())]);
        agent->setMinimumDistance(10.f);
        
        return move(agent);
    }
    
protected:
    vector< shared_ptr<ofMesh> > letterMeshes;
};