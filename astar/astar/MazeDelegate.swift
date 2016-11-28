//
//  MazeDelegate.swift
//  astar
//
//  Created by André Marques da Silva Rodrigues on 27/11/16.
//  Copyright © 2016 Vergil. All rights reserved.
//

import UIKit

class MazeDelegate: NSObject {
    var masks: [UInt8]
    
    init(masks: [UInt8]) {
        self.masks = masks
        super.init()
    }
}
