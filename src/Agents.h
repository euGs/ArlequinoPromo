#pragma once

#include "ofMain.h"
#include "AgentSource.h"
#include "VisualisationSource.h"
#include "Agent.h"
#include "Visualisation.h"

class Agents {
public:
    void setup (unique_ptr<AgentSource> agentSource, unique_ptr<VisualisationSource> visualisationSource, int maxAgents){
        unique_ptr<Agent> agent = move(agentSource->getAgent());
        unique_ptr<Visualisation> visualisation = move(visualisationSource->getVisualisation());
        
        while (agent != nullptr && visualisation != nullptr && agents.size() < maxAgents){
            agent->setVisualisation(move(visualisation));
            agents.push_back(move(agent));

            agent = move(agentSource->getAgent());
            visualisation = move(visualisationSource->getVisualisation());
        }
    }

    void update(float globalScaling){
        // Generate noise values.
        float noiseScale = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 1.f);
        float noiseVel = ofGetElapsedTimef();

        for (int i=0; i<agents.size(); i++){
            float noiseValue1 = ofNoise(i * noiseScale, 1 * noiseScale, noiseVel);
            float noiseValue2 = ofNoise(i * noiseScale, 1000 * noiseScale, noiseVel);
            agents[i]->update(noiseValue1, noiseValue2, .1f + globalScaling * 8.f);
        }
    }
    
    void draw(){
        for (int i=0; i<agents.size(); i++){
            agents[i]->draw();
        }
    }
    
private:
    vector< unique_ptr<Agent> > agents;

};