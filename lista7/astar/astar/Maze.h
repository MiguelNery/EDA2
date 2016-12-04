//
//  Maze.h
//  astar
//
//  Created by André Marques da Silva Rodrigues on 21/11/16.
//  Copyright © 2016 Vergil. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Maze : NSObject

+ (void) setupWithNumcells: (int)numcells;
+ (NSArray<NSNumber *> *) computeMaze;

+ (uint8_t) directionUp;
+ (uint8_t) directionRight;
+ (uint8_t) directionLeft;
+ (uint8_t) directionDown;

+ (bool) isDirection: (u_int8_t)direction maskedBy: (u_int8_t)mask;

@end
