//
//  Maze.m
//  astar
//
//  Created by André Marques da Silva Rodrigues on 21/11/16.
//  Copyright © 2016 Vergil. All rights reserved.
//

#import "Maze.h"
#include "mazecpp.hpp"
#include <cstring>

@implementation Maze

static int _numcells;

+ (void) setupWithNumcells: (int)numcells {
    
    _numcells = numcells;
    maze::setup(numcells, arc4random());
}

+ (NSArray<NSNumber *> *) computeMaze {
    
    [self setupWithNumcells:_numcells];
    
    NSMutableArray<NSNumber *> *maze = [NSMutableArray new];
    unsigned short *m = new unsigned short[_numcells * _numcells];
    memset(m, 0, _numcells * _numcells * sizeof(unsigned short));
    maze::compute_maze(m);
    
    for (int i = 0; i < _numcells * _numcells; ++i) {
        [maze addObject:[NSNumber numberWithInt:m[i]]];
    }
    
    return [NSArray arrayWithArray:maze];
}

+ (u_int8_t) directionUp {
    return maze::eDirection_Up;
}
+ (u_int8_t) directionRight {
    return maze::eDirection_Right;
}
+ (u_int8_t) directionLeft {
    return maze::eDirection_Left;
}
+ (u_int8_t) directionDown {
    return maze::eDirection_Down;
}

+ (bool) isDirection: (u_int8_t)direction maskedBy: (u_int8_t)mask {
    return direction & mask;
}

@end
