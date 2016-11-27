//
//  MazeTile.swift
//  astar
//
//  Created by André Marques da Silva Rodrigues on 21/11/16.
//  Copyright © 2016 Vergil. All rights reserved.
//

import SpriteKit

class MazeTile: SKSpriteNode {
    
    enum Directions: UInt8 {
        case up = 0b0001
        case right = 0b0010
        case down = 0b0100
        case left = 0b1000
        
        var rad: Double {
            switch self {
            case .up: return M_PI/2
            case .right: return 0
            case .down: return 3*M_PI/2
            case .left: return M_PI
            }
        }
    }
    
    struct WallMask {
        var up = false
        var down = false
        var left = false
        var right = false
        
        init() {
        }
        
        init(mask: UInt8) {
            if mask & Maze.directionUp() {
                up = true
            }
            if mask & Maze.directionDown() {
                down = true
            }
            if mask & Maze.directionLeft() {
                left = true
            }
            if mask & Maze.directionRight() {
                right = true
            }
        }
    }
    
    private var highlightArrow: SKSpriteNode!
    private var highlightNode: SKSpriteNode!
    var mask: WallMask
    var col: Int = 0
    var row: Int = 0
    
    init(size: CGFloat, wallMask: UInt8, col: Int, row: Int) {
        
        mask = WallMask(mask: wallMask)
        self.col = col
        self.row = row
        
        super.init(texture: nil, color: .green, size: CGSize(width: size, height: size))
        
        if !mask.up {
            let b = bar(direction: Maze.directionUp())
            b.position = CGPoint(x: 0, y: -size/2)
            self.addChild(b)
        }
        if !mask.right {
            let b = bar(direction: Maze.directionRight())
            b.position = CGPoint(x: size/2, y: 0)
            self.addChild(b)
        }
        if !mask.down {
            let b = bar(direction: Maze.directionDown())
            b.position = CGPoint(x: 0, y: size/2)
            self.addChild(b)
        }
        if !mask.left {
            let b = bar(direction: Maze.directionLeft())
            b.position = CGPoint(x: -size/2, y: 0)
            self.addChild(b)
        }
        
        highlightArrow = SKSpriteNode(texture: SKTexture(imageNamed: "arrow"), color: .clear, size: CGSize(width: size, height: size))
        highlightNode = SKSpriteNode(texture: nil, color: .red, size: CGSize(width: size/3, height: size/3))
    }
    
    func bar(direction: UInt8) -> SKSpriteNode {
        var bar: SKSpriteNode!
        switch direction {
        case Maze.directionUp(), Maze.directionDown():
            bar = SKSpriteNode(color: .brown, size: CGSize(width: frame.size.width, height: 2))
        case Maze.directionLeft(), Maze.directionRight():
            bar = SKSpriteNode(color: .brown, size: CGSize(width: 2, height: frame.size.height))
        default: assert(false)
        }
        return bar
    }
    
    func highlight(direction: Directions) {
        if let _ = highlightArrow.parent {
            
        } else {
            highlightArrow.zRotation = CGFloat(direction.rad)
            addChild(highlightArrow)
        }
    }
    
    func highlight() {
        if let _ = highlightNode.parent {
            
        } else {
            addChild(highlightNode)
        }
    }
    
    func unhighlight() {
        highlightNode.removeFromParent()
        highlightArrow.removeFromParent()
    }
    
    required init?(coder aDecoder: NSCoder) {
        mask = WallMask()
        super.init(coder: aDecoder)
    }
}

func &(lhs: UInt8, rhs: UInt8) -> Bool {
    return Maze.isDirection(lhs, maskedBy: rhs)
}
