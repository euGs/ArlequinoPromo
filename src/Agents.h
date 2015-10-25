#pragma once

#include "ofMain.h"
#include "AgentSource.h"
#include "VisualisationSource.h"
#include "Agent.h"
#include "Visualisation.h"

class Agents {
public:
    void setup (unique_ptr<AgentSource> agentSource, unique_ptr<VisualisationSource> visualisationSource, int maxAgents){        
        while (visualisationSource->hasMoreVisualisations() && agents.size() < maxAgents){
            unique_ptr<Agent> agent = move(agentSource->getAgent());
            unique_ptr<Visualisation> visualisation = move(visualisationSource->getVisualisation());

            agent->setVisualisation(move(visualisation));
            agent->setup();
            agents.push_back(move(agent));
        }
    }

    void update(float scalingFactor){
        // Generate noise values.
        float noiseScale = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 1.f);
        float noiseVel = ofGetElapsedTimef();

        for (int i=0; i<agents.size(); i++){
            float noiseValue1 = ofNoise(i * noiseScale, 1 * noiseScale, noiseVel);
            float noiseValue2 = ofNoise(i * noiseScale, 1000 * noiseScale, noiseVel);
            agents[i]->update(noiseValue1, noiseValue2, .05f + scalingFactor * 8.f);
        }
    }
    
    void draw(){
        for (int i=0; i<agents.size(); i++){
            agents[i]->draw();
        }
    }
    
protected:
    vector< unique_ptr<Agent> > agents;
};