//
//  mazecpp.hpp
//  astar
//
//  Created by André Marques da Silva Rodrigues on 21/11/16.
//  Copyright © 2016 Vergil. All rights reserved.
//

#ifndef mazecpp_h
#define mazecpp_h

namespace maze {
    
    enum eDirection {
        eDirection_Invalid = 0,
        eDirection_Up      = 0b0001,
        eDirection_Right   = 0b0010,
        eDirection_Down    = 0b0100,
        eDirection_Left    = 0b1000
    };
    
    void setup(int, unsigned int);
    void compute_maze(unsigned short *);
}


#endif /* mazecpp_h */
