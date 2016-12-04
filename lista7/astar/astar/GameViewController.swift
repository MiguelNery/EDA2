//
//  GameViewController.swift
//  astar
//
//  Created by André Marques da Silva Rodrigues on 21/11/16.
//  Copyright © 2016 Vergil. All rights reserved.
//

import UIKit
import SpriteKit
import GameplayKit

class GameViewController: UIViewController {

    var scene: GameScene?
    @IBOutlet weak var sizeSelectionSegmentedControl: UISegmentedControl!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        if let view = self.view as! SKView? {
            // Load the SKScene from 'GameScene.sks'
            if let scene = SKScene(fileNamed: "GameScene") {
                // Set the scale mode to scale to fit the window
                scene.scaleMode = .aspectFill
                
                // Present the scene
                self.scene = scene as? GameScene
                view.presentScene(scene)
            }
            
            view.ignoresSiblingOrder = true
            
            view.showsFPS = true
            view.showsNodeCount = true
        }
        
        sizeSelectionSegmentedControl.selectedSegmentIndex = 1
    }

    override var shouldAutorotate: Bool {
        return true
    }

    override var supportedInterfaceOrientations: UIInterfaceOrientationMask {
        if UIDevice.current.userInterfaceIdiom == .phone {
            return .allButUpsideDown
        } else {
            return .all
        }
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Release any cached data, images, etc that aren't in use.
    }

    override var prefersStatusBarHidden: Bool {
        return true
    }
    
    var mazeSize: MazeSize {
        switch sizeSelectionSegmentedControl.selectedSegmentIndex {
        case 0: return MazeSize.small
        case 1: return MazeSize.medium
        case 2: return MazeSize.large
        default: return MazeSize.medium
        }
    }
    
    @IBAction func sizeSelected(_ sender: Any) {
        scene?.selectedMazeSize = mazeSize
    }
    
    @IBAction func regenerateMaze(sender: Any) {
        scene?.generateMaze(mazeSize: mazeSize)
    }
}
