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
    void setup(AgentSource &agentSource, VisualisationSource &visualisationSource, int maxAgents){
        isTransitioning = false;
        
        while (visualisationSource.hasMoreVisualisations() && agents.size() < maxAgents){
            unique_ptr<Agent> agent = move(agentSource.getAgent());

            agent->setVisualisation(move(visualisationSource.getVisualisation()));
            agent->setup();
            agents.push_back(move(agent));
        }
    }

    void update(float scalingFactor){
        if (!isTransitioning){
            // Generate noise values for move data.
            float noiseScale = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 1.f);
            float noiseVel = ofGetElapsedTimef();

            for (int i=0; i<agents.size(); i++){
                MoveData md;
                
                md.normalisedValue1 = ofNoise(i * noiseScale, 1 * noiseScale, noiseVel);
                md.normalisedValue2 = ofNoise(i * noiseScale, 1000 * noiseScale, noiseVel);
                md.globalScaling = .05f + scalingFactor * 8.f;
                agents[i]->update(md);
            }
        } else {
            for (int i=0; i<lerpingAgents.size(); i++){
                MoveData md;
                md.normalisedValue1 = ofGetElapsedTimef() * (endTransitionTime - startTransitionTime);
                lerpingAgents[i].update(md);
            }
            
            if (ofGetElapsedTimef() > endTransitionTime){
                isTransitioning = false;
            }
        }
    }
    
    void transitionAgents(AgentSource &agentSource, float durationMilliseconds){
        lerpingAgents.clear();
        
        for (size_t i = 0; i < agents.size(); i++){
            LerpingAgent lerpingAgent;
            lerpingAgent.setStartPosition(agents[i]->getPosition());
            unique_ptr<Agent> newAgent = move(agentSource.getAgent());
            lerpingAgent.setEndPosition(newAgent->getPosition());
            lerpingAgents.push_back(move(lerpingAgent));
            agents[i] = move(newAgent);
        }
        
        startTransitionTime = ofGetElapsedTimef();
        endTransitionTime = startTransitionTime + durationMilliseconds;
        isTransitioning = true;
    }
    
    void draw(){
        for (int i=0; i<agents.size(); i++){
            agents[i]->draw();
        }
    }
    
protected:
    vector< unique_ptr<Agent> > agents;
    vector< LerpingAgent > lerpingAgents;
    bool isTransitioning;
    float startTransitionTime, endTransitionTime;
};