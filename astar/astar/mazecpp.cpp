/**
 * \file Maze.cpp
 * \brief
 *
 * Depth-first Search Random Maze Generator
 *
 * \version 1.0.0
 * \date 27/05/2014
 * \author Sergey Kosarevsky, 2014
 * \author support@linderdaum.com   http://www.linderdaum.com   http://blog.linderdaum.com
 */

/*
 To compile:
	gcc Maze.cpp -std=c++11 -lstdc++
 */

// http://en.wikipedia.org/wiki/Maze_generation_algorithm#Depth-first_search

#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>
#include <fstream>
#include <random>
#include "mazecpp.hpp"

namespace maze {

    ///////////////// User selectable parameters ///////////////////////////////

    int NumCells = 8;

    ////////////////////////////////////////////////////////////////////////////

    const char* Version = "1.0.0 (27/05/2014)";

    unsigned char* g_Maze;

    // current traversing position
    int g_PtX = 0;
    int g_PtY = 0;

    // return the current index in g_Maze
    int CellIdx() {
        return g_PtX + NumCells * g_PtY;
    }

    ////////////////////////////////////////////////////////////////////////////

    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<> dis( 0, NumCells - 1 );
    std::uniform_int_distribution<> dis4( 0, 3 );

    int RandomInt() {
        return static_cast<int>( dis( gen ) );
    }

    int RandomInt4() {
        return static_cast<int>( dis4( gen ) );
    }

    ////////////////////////////////////////////////////////////////////////////

    //                   0  1  2  3  4  5  6  7  8
    //                      U  R     D           L
    int Heading_X[9] = { 0, 0,+1, 0, 0, 0, 0, 0,-1 };
    int Heading_Y[9] = { 0,-1, 0, 0,+1, 0, 0, 0, 0 };
    int Mask[9]      = {
        0,
        eDirection_Down | eDirection_Down << 4,
        eDirection_Left | eDirection_Left << 4,
        0,
        eDirection_Up | eDirection_Up << 4,
        0,
        0,
        0,
        eDirection_Right | eDirection_Right << 4
    };


    ////////////////////////////////////////////////////////////////////////////

    bool IsDirValid( eDirection Dir ) {
        
        int NewX = g_PtX + Heading_X[ Dir ];
        int NewY = g_PtY + Heading_Y[ Dir ];

        if ( !Dir || NewX < 0 || NewY < 0 || NewX >= NumCells || NewY >= NumCells ) return false;
        
        unsigned char v = g_Maze[ NewX + NumCells * NewY ];
        return !v;
    }

    eDirection GetDirection() {
        
        eDirection Dir = eDirection( 1 << RandomInt4() );

        while ( true ) {
            for ( int x = 0; x < 4; x++ ) {
                if ( IsDirValid( Dir ) ) { return eDirection( Dir ); }

                Dir = eDirection( Dir << 1 );

                if ( Dir > eDirection_Left ) { Dir = eDirection_Up; }
            }

            Dir = eDirection( ( g_Maze[ CellIdx() ] & 0xf0 ) >> 4 );

            // nowhere to go
            if ( !Dir ) return eDirection_Invalid;

            g_PtX += Heading_X[ Dir ];
            g_PtY += Heading_Y[ Dir ];

            Dir = eDirection( 1 << RandomInt4() );
        }
    }

    void GenerateMaze() {
        
        int Cells = 0;

        for ( eDirection Dir = GetDirection(); Dir != eDirection_Invalid; Dir = GetDirection() ) {
            // a progress indicator, kind of
            if ( ++Cells % 1000 == 0 ) std::cout << ".";

            g_Maze[ CellIdx() ] |= Dir;

            g_PtX += Heading_X[ Dir ];
            g_PtY += Heading_Y[ Dir ];

            g_Maze[ CellIdx() ] = Mask[ Dir ];
        }

        // std::cout << std::endl;
    }

    #if defined( __GNUC__ )
    # define GCC_PACK(n) __attribute__((packed,aligned(n)))
    #else
    # define GCC_PACK(n) __declspec(align(n))
    #endif // __GNUC__

    // #pragma pack(push, 1)
    // #pragma pack(pop)

    void compute_maze(unsigned short *maze) {
        
        for ( int y = 0; y < NumCells; y++ ) {

            for ( int x = 0; x < NumCells; x++ ) {

                char v = g_Maze[ y * NumCells + x ];
                
                unsigned short *pointer = &maze[y * NumCells + x];

                if (v & eDirection_Up) {
    				*pointer |= eDirection_Up;
    			}
                if (v & eDirection_Right) {
    				*pointer |= eDirection_Right;
    			}
                if (v & eDirection_Down) {
                    *pointer |= eDirection_Down;
    			}
                if (v & eDirection_Left) {
    				*pointer |= eDirection_Left;
    			}
            }
        }
    }
    
    void cleanup() {
        delete [] g_Maze;
        g_PtX = 0;
        g_PtY = 0;
    }

    void setup(int numcells, unsigned int seed) {
        
        cleanup();
        
        dis = std::uniform_int_distribution<>( 0, NumCells - 1 );
        
        NumCells = numcells;

        g_Maze = new unsigned char[ NumCells* NumCells ];
        gen.seed(seed);
        // clear maze
        memset(g_Maze, 0, sizeof(unsigned char) * NumCells * NumCells);

        // setup initial point
        g_PtX = RandomInt();
        g_PtY = RandomInt();

        // traverse
        GenerateMaze();
    }
    
}
