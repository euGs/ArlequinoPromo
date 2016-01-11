#pragma once

#include "Visualisation.h"

class VisualisationSource {
public:
    virtual void setup(){
    }
    
    virtual unique_ptr<Visualisation> getVisualisation() = 0;
    virtual bool hasMoreVisualisations() = 0;
};

class SphereVisualisationSource : public VisualisationSource {
public:
    virtual unique_ptr<Visualisation> getVisualisation() override{
        return move(make_unique<SphereVisualisation>());
    }
    
    virtual bool hasMoreVisualisations() override{
        return true;
    }
};

class SpriteVisualisationSource : public VisualisationSource {
public:
    void setImageFilename(string imageFilename){
        this->imageFilename = imageFilename;
    }
    
    void setGridDimensions(int cols, int rows){
        this->cols = cols;
        this->rows = rows;
    }
    
    virtual void setup(){
        ofImage source;
        
        source.load(imageFilename);
        
        colWidth = source.getWidth() / cols;
        rowHeight = source.getHeight() / rows;
        planeResolution = 4;
        
        visualisations.reserve(cols * rows);

        for (int col=0; col<cols; col++){
            for (int row=0; row<rows; row++){
                createSprite(source, col, row);
            }
        }
        
        index = 0;
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
        plane.set(colWidth, rowHeight, planeResolution, planeResolution);
        plane.mapTexCoords(0, 0, texture.getWidth(), texture.getHeight());
        plane.setPosition((col-cols/2.f) * texture.getWidth(), (row-rows/2.f) * texture.getHeight(), 0);
    }
    
    virtual void addVisualisation(ofPlanePrimitive & plane, ofImage & texture){
        unique_ptr<SpriteVisualisation> visualisation = make_unique<SpriteVisualisation>();
        visualisation->setup(plane, texture);
        
        visualisations.push_back(move(visualisation));
    }
    
    virtual unique_ptr<Visualisation> getVisualisation() override{
        return move(visualisations[index++]);
    }
    
    virtual bool hasMoreVisualisations() override{
        return index < visualisations.size();
    }
    
protected:
    int index;
    string imageFilename;
    int cols, rows;
    float colWidth, rowHeight;
    int planeResolution;
    
    vector< unique_ptr<SpriteVisualisation> > visualisations;
};

class TornPaperVisualisationSource : public SpriteVisualisationSource {
    virtual void addVisualisation(ofPlanePrimitive & plane, ofImage & texture) override{
        unique_ptr<TornPaperVisualisation> visualisation = make_unique<TornPaperVisualisation>();
        visualisation->setup(plane, texture);
        
        visualisations.push_back(move(visualisation));
    }
};

class TornPaperWithParticlesVisualisationSource : public TornPaperVisualisationSource {
    virtual void addVisualisation(ofPlanePrimitive & plane, ofImage & texture) override{
        unique_ptr<TornPaperWithParticlesVisualisation> visualisation = make_unique<TornPaperWithParticlesVisualisation>();
        visualisation->setup(plane, texture);
        
        visualisations.push_back(move(visualisation));
    }
};
