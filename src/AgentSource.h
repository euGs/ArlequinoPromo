#pragma once

#include "Agent.h"

class AgentSource {
public:
    virtual void setup() = 0;
    virtual void reset() {};
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

// Agents that are positioned in a flat grid of rows and columns. setDimensions must be called
// before setup.
class GridAgentSource : public AgentSource {
public:
    void setDimensions(int cols, int rows, float colWidth, float rowHeight){
        this->cols = cols;
        this->rows = rows;
        this->colWidth = colWidth;
        this->rowHeight = rowHeight;
        this->colIndex = 0;
        this->rowIndex = 0;
    }
    
    virtual void setup() override{
    }
    
    virtual void reset() override{
        this->colIndex = 0;
        this->rowIndex = 0;
    }
    
    virtual unique_ptr<Agent> getAgent() override{
        if (rowIndex >= rows){
            ofLogWarning() << "GridAgentSource::getAgent() Can't return any more Agents. "
            << "Have done the whole grid. (rowIndex >= rows)" << endl;
        }

        unique_ptr<StaticAgent> agent = make_unique<StaticAgent>();
        ofVec3f position(colIndex * colWidth, rowIndex * rowHeight, 0);
        agent->setPosition(position);
        
        colIndex++;
        
        if (colIndex >= cols){
            colIndex = 0;
            rowIndex++;
        }
        
        return move(agent);
    }
    
protected:
    int cols, rows;
    float colWidth, rowHeight;
    int colIndex, rowIndex;
};