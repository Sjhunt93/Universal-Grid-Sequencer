//
//  OGTestController.hpp
//  OpenGrid
//
//  Created by Samuel Hunt on 01/05/2020.
//
//

#ifndef OGTestController_hpp
#define OGTestController_hpp


#include "OGController.hpp"


class OGTestController : public OGController {
public:
    
    
    OGTestController (XY size, XY position);
    virtual ~OGTestController ();
    
    void messageReceived (OGDevice::OGInMsg msg);
    void refresh () {}
    
    XY getMinimumSize () {return {1,1};}
    XY getMaximumSize () {return {-1,-1};}
    const int getColoursRequired () {return 1;}
    
    
    void clockPulse (int _1_4, int _1_8, int _1_16, int _1_32);

private:
    
    
};
#endif /* OGTestController_hpp */
