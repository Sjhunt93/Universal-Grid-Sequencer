//
//  GridModelMap.cpp
//  OpenGrid
//
//  Created by Samuel Hunt on 11/10/2018.
//
//

#include "GridModelMap.h"


GridModelMap::PadModel * GridModelMap::getPad (const int x, const int y)
{
//    const CriticalSection criticalSelection;
    return &grid[y].pads[x];
}

bool GridModelMap::isOutsideGrid (const int x, const int y)
{
    return (x < 0 || x >= gridSize.x) || (y < 0 || y >= gridSize.y);

}

GridModelMap::PadModel * GridModelMap::getPad (const int index)
{
    const int x = index % gridSize.x;
    const int y = index / gridSize.x;
    return &grid[y].pads[x];
}
