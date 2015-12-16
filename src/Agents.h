#pragma once

#include "ofMain.h"
#include "AgentSource.h"
#include "VisualisationSource.h"
#include "Agent.h"
#include "Visualisation.h"

// Handles setting up agents (with their visualisations), generating noise and scaling
// values for agents in the update loop and transitioning all agents from one type to another.
class Agents {
public:
    void setup (AgentSource &agentSource, VisualisationSource &visualisationSource, int maxAgents){
        while (visualisationSource.hasMoreVisualisations() && agents.size() < maxAgents){
            unique_ptr<Agent> agent = move(agentSource.getAgent());

            agent->setVisualisation(move(visualisationSource.getVisualisation()));
            agent->setup();
            agents.push_back(move(agent));
        }
    }

    void update(float scalingFactor){
        // Generate noise values.
        float noiseScale = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 1.f);
        float noiseVel = ofGetElapsedTimef();

        for (int i=0; i<agents.size(); i++){
            MoveData md;
            
            md.normalisedValue1 = ofNoise(i * noiseScale, 1 * noiseScale, noiseVel);
            md.normalisedValue2 = ofNoise(i * noiseScale, 1000 * noiseScale, noiseVel);
            md.globalScaling = .05f + scalingFactor * 8.f;
            agents[i]->update(md);
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