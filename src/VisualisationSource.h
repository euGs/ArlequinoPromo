#pragma once

#include "Visualisation.h"

class VisualisationSource {
public:
    virtual unique_ptr<Visualisation> getVisualisation() = 0;
};

class SphereVisualisationSource : public VisualisationSource {
    virtual unique_ptr<Visualisation> getVisualisation(){
        return std::move(make_unique<SphereVisualisation>());
    }
};

// class SpriteVisualisationSource

// setup
// load image
// cut up and cache pieces for get method

// class TornPaperVisualisationSource : public spritevs

// as spritevs
// except returned type is TornPaperVisualisation