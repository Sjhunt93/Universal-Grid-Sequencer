//
//  Scales.h
//  MegaMiniSoftware
//
//  Created by Samuel Hunt on 01/06/2015.
//
//

#ifndef __MegaMiniSoftware__Scales__
#define __MegaMiniSoftware__Scales__

#include <iostream>

static const uint8 Major[]          = {0,2,4,5,7,9,11};
static const uint8 Minor[]          = {0,2,3,5,7,8,10};
static const uint8 Dorian[]         = {0,2,3,5,7,9,10};
static const uint8 Mixolydian[]     = {0,2,4,5,7,9,10};
static const uint8 Lydian[]         = {0,2,4,6,7,9,11};
static const uint8 Phrygian[]       = {0,1,3,5,7,8,10};
static const uint8 Locrian[]        = {0,1,3,4,7,8,10};
static const uint8 Diminished[]     = {0,1,3,4,6,7,9,10};
static const uint8 Whole_half[]     = {0,2,3,5,6,8,9,11};
static const uint8 Whole_Tone[]     = {0,2,4,6,8,10};
static const uint8 Minor_Blues[]    = {0,3,5,6,7,10};
static const uint8 Minor_Pentatonic[] ={0,3,5,7,10};
static const uint8 Major_Pentatonic[] = {0,2,4,7,9};


static const uint8 Harmonic_Minor[]     = {0,2,3,5,7,8,11};
static const uint8 Melodic_Minor[]      = {0,2,3,5,7,9,11};
static const uint8 Super_Locrian[]      = {0,1,3,4,6,8,10};
static const uint8 Bhairav[]            = {0,1,4,5,7,8,11};
static const uint8 Hungarian_Minor[]    = {0,2,3,6,7,8,11};
static const uint8 Minor_Gypsy[]        = {0,1,4,5,7,8,10};

static const uint8 Hirojoshi[] = {0,2,3,7,8};
static const uint8 In_Sen[] = {0,1,5,7,10};
static const uint8 Iwato[] = { 0,1,5,6,10};
static const uint8 Kumoi[] = {0,2,3,7,9};
static const uint8 Pelog[] = {0,1,3,4,7,8};
static const uint8 Spanish[] = {0,1,3,4,5,6,8,10};

static const int scaleLengths[] = {7,7,7,7,7,7,7, /*modal*/ 8, 8, 6,6, 5,5, 7,7,7,7,7,7, /*2nd*/ 5,5, 5, 5, 6, 7, 8 };

static void pointToScale(uint8 scale,const uint8 ** ptr, uint8 *len)
{
    switch (scale) {
        case 0:
            *ptr = &Major[0];
            *len = 7;
            break;
        case 1:
            *ptr = &Minor[0];
            *len = 7;
            break;
            
        case 2:
            *ptr = &Dorian[0];
            *len = 7;
            break;
        case 3:
            *ptr = &Mixolydian[0];
            *len = 7;
            break;
            
        case 4:
            *ptr = &Lydian[0];
            *len = 7;
            break;
            
        case 5:
            *ptr = &Phrygian[0];
            *len = 7;
            break;
        case 6:
            *ptr = &Locrian[0];
            *len = 7;
            break;
        case 7:
            *ptr = &Diminished[0];
            *len = 8;
            break;
        case 8:
            *ptr = &Whole_half[0];
            *len = 8;
            break;
        case 9:
            *ptr = &Whole_Tone[0];
            *len = 6;
            break;
        case 10:
            *ptr = &Minor_Blues[0];
            *len = 6;
            break;
        case 11:
            *ptr = &Minor_Pentatonic[0];
            *len = 5;
            break;
        case 12:
            *ptr = &Major_Pentatonic[0];
            *len = 5;
            break;
        case 13:
            *ptr = &Harmonic_Minor[0];
            *len = 7;
            break;
        case 14:
            *ptr = &Melodic_Minor[0];
            *len = 7;
            break;
        case 15:
            *ptr = &Super_Locrian[0];
            *len = 7;
            break;
        case 16:
            *ptr = &Bhairav[0];
            *len = 7;
            break;
        case 17:
            *ptr = &Hungarian_Minor[0];
            *len = 7;
            break;
        default:
            *ptr = &Minor_Gypsy[0];
            *len = 7;
            break;
    }
}

#endif /* defined(__MegaMiniSoftware__Scales__) */
