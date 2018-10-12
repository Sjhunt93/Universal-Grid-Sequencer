//
//  Pad.h
//  MusicGrid
//
//  Created by Samuel Hunt on 14/11/2017.
//
//

#ifndef __MusicGrid__Pad__
#define __MusicGrid__Pad__

#include "../JuceLibraryCode/JuceHeader.h"



class Pad : public Component, public DragAndDropTarget {
public:
    
    class Listner
    {
    public:
        virtual ~Listner() {}
        virtual void doSomething (int x, int y, Array<var> * data) = 0;
    };
    
    
    Pad (Listner & listner);
    ~Pad ();
    
    void paint (Graphics & g);
    
    bool isInterestedInDragSource (const SourceDetails& dragSourceDetails);
    void itemDragEnter (const SourceDetails& dragSourceDetails);
    void itemDragMove (const SourceDetails& dragSourceDetails);
    void itemDragExit (const SourceDetails& dragSourceDetails);
    void itemDropped (const SourceDetails& dragSourceDetails);
    
    Colour col;
    int x, y;
private:
    Listner & listner;
};

#endif /* defined(__MusicGrid__Pad__) */
