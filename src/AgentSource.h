#pragma once

#include "Agent.h"
#include <vector>

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
    
    void setLetterPaths(vector<ofPath> letterPaths, ofVec2f position){
        auto correctionDueToBadTessellation = 7.f;
        
        letterMeshes.clear();
        
        for (auto i=0; i<letterPaths.size(); ++i){
            shared_ptr<ofMesh> mesh = make_shared<ofMesh>(letterPaths[i].getTessellation());
            if (mesh->getNumVertices() == 0){
                continue;
            }
            
            setMeshPosition(mesh, position - ofVec2f(i * correctionDueToBadTessellation, 0));
            letterMeshes.push_back(mesh);
        }
    }
    
    virtual unique_ptr<Agent> getAgent() override{
        if (letterMeshes.size() == 0){
            ofLogWarning() << "TextRovingAgentSource::letterMeshes.size() == 0" << endl;
            return nullptr;
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
            mesh->setVertex(i, mesh->getVertex(i));// + position);
        }
    }
};

class BasicBoundAgentSource : public AgentSource {
public:
    void setup() override{
    }
    
    void setBoundingBox(ofRectangle boundingBox){
        this->boundingBox = boundingBox;
    }

    virtual unique_ptr<Agent> getAgent() override{
        unique_ptr<BasicBoundAgent> agent = make_unique<BasicBoundAgent>();
        agent->setMinimumDistance(10.f);
        agent->setBoundingBox(this->boundingBox);
        
        return move(agent);
    }
    
protected:
    ofRectangle boundingBox;
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
    
    void setPosition(ofVec3f position){
        this->position = position;
    }
    
    void setOrientationEuler(ofVec3f orientationEuler){
        this->orientationEuler = orientationEuler;
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
        ofVec3f agentRelativePosition(colIndex * colWidth - ((cols-1) * colWidth / 2.f), -rowIndex * rowHeight + ((rows-1) * rowHeight / 2.f), 0.f);
        agentRelativePosition.rotate(this->orientationEuler.x, this->orientationEuler.y, this->orientationEuler.z);
        agent->setPosition(this->position + agentRelativePosition);
        agent->setOrientationEuler(orientationEuler);
        
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
    ofVec3f position, orientationEuler;
};

class SimplerTextRovingAgentSource : public AgentSource {
public:
    virtual void setup() override{
        
    }
    
    void setMinimumPointDistance(float minPointDistance){
        this->minPointDistance = minPointDistance;
    }
    
    void setLetterPaths(vector<ofPath> letterPaths, ofVec2f position){
        auto correctionDueToBadTessellation = 7.f;
        
        for (auto i=0; i<letterPaths.size(); ++i){
            ofMesh mesh = letterPaths[i].getTessellation();
            if (mesh.getNumVertices() < 2){
                continue;
            }
            
            vector<ofVec3f> letterPoints;
            
            ofVec3f lastLetterPoint = mesh.getVertex(0);
            letterPoints.emplace_back(lastLetterPoint);
            
            for (ofIndexType j=1; j<mesh.getNumVertices(); ++j){
                auto d = lastLetterPoint.distance(mesh.getVertex(j));
                if ( d > minPointDistance ){
                    ofVec3f point = mesh.getVertex(j);

                    letterPoints.emplace_back(point);
                    lastLetterPoint = point;
                }
            }
            
            auto correction = position - ofVec2f(i * correctionDueToBadTessellation);
            
            for (auto it=letterPoints.begin(); it!=letterPoints.end(); ++it){
                it->set(*it + correction);
            }
            
            textPoints.emplace_back(letterPoints);
        }
    }
    
    virtual unique_ptr<Agent> getAgent() override{
        if (textPoints.size() == 0){
            ofLogWarning() << "SimplerTextRovingAgentSource::lettersPoints.size() == 0" << endl;
            return nullptr;
        }
        
        unique_ptr<VerticesRovingAgent> agent = make_unique<VerticesRovingAgent>();
        agent->setVertices(textPoints[ofRandom(textPoints.size())]);
        agent->setMinimumDistance(10.f);
        
        return move(agent);
        
        return nullptr;
    }
    
protected:
    vector< vector<ofVec3f> > textPoints;
    float minPointDistance;
    
    void setMeshPosition(shared_ptr<ofMesh> mesh, ofVec2f position){
        for (int i=0; i<mesh->getNumVertices(); i++){
            mesh->setVertex(i, mesh->getVertex(i));// + position);
        }
    }
};
