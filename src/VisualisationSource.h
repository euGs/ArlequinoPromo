#pragma once

#include "Visualisation.h"

class VisualisationSource {
public:
    virtual unique_ptr<Visualisation> getVisualisation() = 0;
    virtual bool hasMoreVisualisations() = 0;
};

class SphereVisualisationSource : public VisualisationSource {
public:
    unique_ptr<Visualisation> getVisualisation(){
        return move(make_unique<SphereVisualisation>());
    }
    
    bool hasMoreVisualisations(){
        return true;
    }
};

class SpriteVisualisationSource : public VisualisationSource {
public:
    SpriteVisualisationSource(){
        ofImage source;
        
        source.load("Cover01.jpg");
        
        cols = 30, rows = 20;
        colWidth = source.getWidth() / cols;
        rowHeight = source.getHeight() / rows;
        
        visualisations.reserve(cols * rows);

        for (int col=0; col<cols; col++){
            for (int row=0; row<rows; row++){
                createSprite(source, col, row);
            }
        }
    }
    
    void createSprite(ofImage & source, int col, int row){
        ofImage texture;
        setUpTexture(texture, source, col, row);
        ofPlanePrimitive plane;
        setUpPlane(plane, texture, col, row);
        addVisualisation(plane, texture);
    }
    
    void setUpTexture(ofImage & texture, ofImage & source, int col, int row){
        ofPixels & sourcePixels = source.getPixels();
        
        texture.allocate(colWidth, rowHeight, OF_IMAGE_COLOR);
        ofPixels & texturePixels = texture.getPixels();
        
        for (int i=0; i<colWidth; i++){
            for (int j=0; j<rowHeight; j++){
                ofColor c = sourcePixels.getColor(colWidth*col + i, rowHeight*row + j);
                texturePixels.setColor(i, j, c);
            }
        }
        
        texture.update();
    }
    
    void setUpPlane(ofPlanePrimitive & plane, ofImage & texture, int col, int row){
        plane.set(colWidth, rowHeight, 2, 2);
        plane.mapTexCoords(0, 0, texture.getWidth(), texture.getHeight());
        plane.setPosition((col-cols/2.f) * texture.getWidth(), (row-rows/2.f) * texture.getHeight(), 0);
    }
    
    virtual void addVisualisation(ofPlanePrimitive & plane, ofImage & texture){
        unique_ptr<SpriteVisualisation> visualisation = make_unique<SpriteVisualisation>();
        visualisation->setup(plane, texture);
        
        visualisations.push_back(move(visualisation));
    }
    
    virtual unique_ptr<Visualisation> getVisualisation(){
        return move(visualisations[index++]);
    }
    
    bool hasMoreVisualisations(){
        return index < visualisations.size();
    }
    
protected:
    int index;
    int cols, rows, colWidth, rowHeight;
    
    vector< unique_ptr<SpriteVisualisation> > visualisations;
};

class TornPaperVisualisationSource : public SpriteVisualisationSource {
    
};
