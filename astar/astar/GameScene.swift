//
//  GameScene.swift
//  astar
//
//  Created by André Marques da Silva Rodrigues on 21/11/16.
//  Copyright © 2016 Vergil. All rights reserved.
//

import SpriteKit
import GameplayKit

enum MazeSize: Int32 {
    case small = 8
    case medium = 16
    case large = 32
}

class GameScene: SKScene, PathfinderDataSource {
    
    var mazeLayers = [MazeSize.small: Layer(), MazeSize.medium: Layer(), MazeSize.large: Layer()]
    var selectedMazeSize = MazeSize.medium {
        didSet {
            let oldLayer = mazeLayers[oldValue]!
            oldLayer.removeFromParent()
            addChild(currentMazeLayer)
            
            clearPath()
            srcTile = nil
            destTile = nil
        }
    }
    
    var currentMazeLayer: Layer {
        return mazeLayers[selectedMazeSize]!
    }
    
    var tileSize: CGFloat! {
        return frame.size.width/CGFloat(selectedMazeSize.rawValue)
    }
    var layerSize: CGSize!
    let pathfinder = Pathfinder()
    
    var srcTile: MazeTile?
    var destTile: MazeTile?
    
    var pathNode: SKNode?
    
    var path: [MazeTile]?
    
    override func didMove(to view: SKView) {
        
        
        layerSize = CGSize(width: frame.size.width, height: frame.size.width)
        
        pathfinder.dataSource = self
        setupMazeLayers()
        addChild(currentMazeLayer)
        
        generateMaze(mazeSize: MazeSize.small)
        generateMaze(mazeSize: MazeSize.medium)
        generateMaze(mazeSize: MazeSize.large)
    }
    
    func setupMazeLayers() {
        for layerKV in mazeLayers {
            let layer = layerKV.value
            layer.position = CGPoint(x: -frame.size.width/2, y: -frame.size.width/2)
        }
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        let position = touches.first!.location(in: self)
        if let tile = nodes(at: position).first as? MazeTile {
            if let _ = srcTile {
                if let _ = destTile {
                    srcTile = tile
                    srcTile?.highlight()
                    destTile = nil
                    clearPath()
                } else {
                    destTile = tile
                    pathfind()
                }
            } else { //just started
                srcTile = tile
                srcTile?.highlight()
            }
        }
       
    }
    
    func generateMaze(mazeSize: MazeSize) {
        
        let mazeLayer = mazeLayers[mazeSize]!
        
        let numCells = mazeSize.rawValue
        
        let tileSize = frame.size.width/CGFloat(mazeSize.rawValue)
        
        generateMaze(numCells, mazeLayer, tileSize)
    }
    
    var generateMaze: ((_ numCells: Int32, _ mazeLayer: Layer, _ tileSize: CGFloat) -> ()) = { numCells, mazeLayer, tileSize in
        
        mazeLayer.clear()
        Maze.setup(withNumcells: numCells)
        
        let maze = Maze.computeMaze()!;
        
        var desc = ""
        for i in 0..<numCells*numCells {
            
            let x = Int(i%numCells);
            let y = Int(i/numCells);
            
            let mask = maze[Int(i)].uint8Value
            
            let tile = MazeTile(size: tileSize, wallMask: mask, col: x, row: y)
            let pos = CGPoint(x: CGFloat(x)*tileSize + tile.size.width/2, y: CGFloat(y)*tileSize + tile.size.height/2)
            tile.position = pos
            mazeLayer.addChild(tile)
        }
    }
    
    func walkableAdjacentTilesCoords(for tile: MazeTile) -> [MazeTile] {
        let coord = tile.position
        var tiles = [MazeTile]()
        if tile.mask.up {
            let position = CGPoint(x: coord.x, y: coord.y - tileSize)
            tiles.append(currentMazeLayer.nodes(at: position).last as! MazeTile)
        }
        if tile.mask.down {
            let position = CGPoint(x: coord.x, y: coord.y + tileSize)
            tiles.append(currentMazeLayer.nodes(at: position).last as! MazeTile)
        }
        if tile.mask.right {
            let position = CGPoint(x: coord.x + tileSize, y: coord.y)
            tiles.append(currentMazeLayer.nodes(at: position).last as! MazeTile)
            
        }
        if tile.mask.left {
            let position = CGPoint(x: coord.x - tileSize, y: coord.y)
            tiles.append(currentMazeLayer.nodes(at: position).last as! MazeTile)
        }
        return tiles
    }
    
    func costToMove(from tile: MazeTile, to adjacentTile: MazeTile) -> Int {
        return 1
    }
    
    func pathfind() {
        if let path = pathfinder.shortestPath(from: srcTile!, to: destTile!) {
            self.path = path
            self.path?.insert(srcTile!, at: 0)
            showTheWay()
        } else {
            clearPath()
        }
    }
    
    func showTheWay() {
        
        let bezier = UIBezierPath()
        
        if let path = path {
            if path.count > 1 {
                
                bezier.move(to: path[0].position)
                
                for i in 1..<path.count {
                    let dest = path[i].position
                    bezier.addLine(to: dest)
                    bezier.move(to: dest)
                }
                
                let pathNode = SKShapeNode(path: bezier.cgPath)
                pathNode.lineWidth = tileSize/10
                pathNode.strokeColor = .red
                
                self.pathNode = pathNode
                currentMazeLayer.addChild(pathNode)
            }
            path.last?.highlight()
        }
    }
    
    func clearPath() {
        if let path = path {
            for tile in path {
                tile.unhighlight()
            }
            self.path = nil
        } else {
            srcTile?.unhighlight()
            srcTile = nil
            destTile = nil
        }
        if let pathNode = pathNode {
            pathNode.removeFromParent()
        }
    }
    
    func direction(from src:MazeTile, to dest: MazeTile) -> MazeTile.Directions {
        if fabs(src.position.x - dest.position.x) <= 0.1 {
            return src.position.y > dest.position.y ? .down : .up
        } else {
            return src.position.x > dest.position.x ? .left : .right
        }
    }
}
