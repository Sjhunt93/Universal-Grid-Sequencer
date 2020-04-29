//
//  GridModelMap.h
//  OpenGrid
//
//  Created by Samuel Hunt on 11/10/2018.
//
//

#ifndef __OpenGrid__GridModelMap__
#define __OpenGrid__GridModelMap__

#include "ControllerBase.h"
#include "IODevice.h"

class Pad;
class GridModelMap {
public:
    //this map defines the coordinate map between device and
    
    /*
     This is just a container of data..
     */
    struct PadModel {
//        Pad (const int _x, const int _y, bool isActive) : x(_x), y(_y), active(isActive)
//        {
//            device = nullptr;
//            pad = nullptr;
//        }
//        Pad () : x(-1), y(-1), active(false)
//        {
//            device = nullptr;
//            pad = nullptr;
//        }
        
//        const int x;
//        const int y;
//        const bool active;
        int x;
        int y;
        bool active;
        
        
        IODevice * device; //correspond device
        Pad * pad; //GUI object.
        ControllerBase * controller;
    };
    struct Row {
        std::vector<PadModel> pads;
    };
    
    
    
    
    GridModelMap (XY size) : gridSize(size)
    {
        grid.resize(size.y);
        for (int y = 0; y < grid.size(); y++) {
            grid[y].pads.reserve(size.x);
//            for (int x = 0; x < size.x; x++) {
//                grid[y].pads.push_back({})
//            }
        }
    }
    
    void registerDevice (XY origin, XY size, IODevice * device)
    {
        for (int x = 0; x < size.x; x++) {
            for (int y = 0; y < size.y; y++) {
                const int nX = x+origin.x;
                const int nY = y+origin.y;
                //switch device out for a call to
                grid[nY].pads[nX] = {nX,nY, device->isXYActive(x, y), device, nullptr, nullptr};
            }
        }
    }
    
    PadModel * getPad (const int x, const int y);
    PadModel * getPad (const int index);
    
    bool isOutsideGrid (const int x, const int y);
    
    
    const XY gridSize;
private:
    std::vector<Row> grid;
};

#endif /* defined(__OpenGrid__GridModelMap__) */
