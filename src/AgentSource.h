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
    void setup() override{
    }
    
    unique_ptr<Agent> getAgent() override{
        return move(make_unique<SphereRovingAgent>());
    }
};

class PivotingSphereRovingAgentSource : public AgentSource {
public:
    void setup() override{
    }
    
    unique_ptr<Agent> getAgent() override{
        return move(make_unique<PivotingSphereRovingAgent>());
    }
};

class TextRovingAgentSource : public AgentSource {
public:
    void setup() override{
    }
    
    void setLetterPaths(vector<ofTTFCharacter> letterPaths, ofVec2f position){
        letterMeshes.clear();
        
        for (auto letterPath : letterPaths){
            shared_ptr<ofMesh> mesh = make_shared<ofMesh>(letterPath.getTessellation());
            setMeshPosition(mesh, position);
            letterMeshes.push_back(mesh);
        }
    }
    
    virtual unique_ptr<Agent> getAgent() override{
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
    
    void setMeshPosition(shared_ptr<ofMesh> mesh, ofVec2f position){
        for (int i=0; i<mesh->getNumVertices(); i++){
            mesh->setVertex(i, mesh->getVertex(i) + position);
        }
    }
};

// Agents that just sit around text without moving.
class TextSittingAgentSource : public TextRovingAgentSource {
public:
    virtual void setup() override{
    }
    
    virtual unique_ptr<Agent> getAgent() override{
        if (letterMeshes.size() == 0){
            ofLogWarning() << "TextRovingAgentSource::letterMeshes.size() == 0. Probably forgot to call TextRovingAgentSource::setup()" << endl;
        }
        
        unique_ptr<StaticAgent> agent = make_unique<StaticAgent>();
        ofVec3f vertex = getRandomVertexFromRandomLetter();
        agent->setPosition(vertex);
        
        return move(agent);
    }
    
protected:
    ofVec3f getRandomVertexFromRandomLetter(){
        shared_ptr<const ofMesh> mesh = letterMeshes[ofRandom(letterMeshes.size())];
        
        auto numVertices = mesh->getNumVertices();
        auto randomIndex = ofRandom(numVertices);
        return mesh->getVertex(randomIndex);
    }
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
        ofVec3f position(colIndex * colWidth - (cols * colWidth / 2.f), -rowIndex * rowHeight + (rows * rowHeight / 2.f), 0);
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