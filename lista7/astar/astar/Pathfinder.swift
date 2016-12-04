//
//  Pathfinder.swift
//  astar
//
//  Created by André Marques da Silva Rodrigues on 27/11/16.
//  Copyright © 2016 Vergil. All rights reserved.
//

import SpriteKit

private class ShortestPathStep: Hashable {
    let position: MazeTile
    var parent: ShortestPathStep?
    
    var gScore = 0
    var hScore = 0
    var fScore: Int {
        return gScore + hScore
    }
    
    var hashValue: Int {
        return position.col.hashValue + position.row.hashValue
    }
    
    init(position: MazeTile) {
        self.position = position
    }
    
    func set(_ parent: ShortestPathStep, with moveCost: Int) {
        // The G score is equal to the parent G score + the cost to move from the parent to it
        self.parent = parent
        self.gScore = parent.gScore + moveCost
    }
}

private func ==(lhs: ShortestPathStep, rhs: ShortestPathStep) -> Bool {
    return lhs.position == rhs.position
}

protocol PathfinderDataSource {
    func walkableAdjacentTilesCoords(for tile: MazeTile) -> [MazeTile]
    func costToMove(from tile: MazeTile, to adjacentTile: MazeTile) -> Int
}

class Pathfinder: NSObject {
    
    var dataSource: PathfinderDataSource?
    func shortestPath(from tile: MazeTile, to destination: MazeTile) -> [MazeTile]? {
        // 1
        if self.dataSource == nil {
            return nil
        }
        let dataSource = self.dataSource!
        
        // 2
        var closedSteps = Set<ShortestPathStep>()
        var openSteps = [ShortestPathStep(position: tile)]
        
        while !openSteps.isEmpty {
            // 3
            let currentStep = openSteps.remove(at: 0)
            closedSteps.insert(currentStep)
            
            // 4
            if currentStep.position == destination {
                return convertStepsToShortestPath(lastStep: currentStep)
            }
            
            // 5
            let adjacentTiles = dataSource.walkableAdjacentTilesCoords(for: currentStep.position)
            for tile in adjacentTiles {
                // 6
                let step = ShortestPathStep(position: tile)
                if closedSteps.contains(step) {
                    continue
                }
                let moveCost = dataSource.costToMove(from: currentStep.position, to: step.position)
                
                if let existingIndex = openSteps.index(of: step) {
                    // 7
                    let step = openSteps[existingIndex]
                    
                    if currentStep.gScore + moveCost < step.gScore {
                        step.set(currentStep, with: moveCost)
                        
                        openSteps.remove(at: existingIndex)
                        insert(step, in: &openSteps)
                    }
                    
                } else {
                    // 8
                    step.set(currentStep, with: moveCost)
                    step.hScore = hScore(from: step.position, to: destination)
                    
                    insert(step, in: &openSteps)
                }
            }
            
        }
        
        return nil
    }
    
    private func insert(_ step: ShortestPathStep, in openSteps: inout [ShortestPathStep]) {
        openSteps.append(step)
        openSteps.sort { $0.fScore <= $1.fScore }
    }
    
    func hScore(from tile: MazeTile, to dest: MazeTile) -> Int {
        return abs(dest.col - tile.col) + abs(dest.row - tile.row)
    }
    
    private func convertStepsToShortestPath(lastStep: ShortestPathStep) -> [MazeTile] {
        var shortestPath = [MazeTile]()
        var currentStep = lastStep
        while let parent = currentStep.parent {
            shortestPath.insert(currentStep.position, at: 0)
            currentStep = parent
        }
        return shortestPath
    }

}
