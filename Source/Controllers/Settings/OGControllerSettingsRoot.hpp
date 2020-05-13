//
//  OGControllerSettingsRoot.hpp
//  OpenGrid
//
//  Created by Samuel Hunt on 13/05/2020.
//
//

#ifndef OGControllerSettingsRoot_hpp
#define OGControllerSettingsRoot_hpp

#include "OGController.hpp"

class OGControllerSettingsRoot : public OGController {
public:
    OGControllerSettingsRoot (XY size, XY position, int type);
    
    
    void setControlMessageForPos (XY position, ControlMessage cm);
    ControlMessage getControlMessageForPos (XY position);
private:
//    std::vector<>
};

#endif /* OGControllerSettingsRoot_hpp */
