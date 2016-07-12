//
//  GameViewController.swift
//  Swiftris
//
//  Created by carol on 7/2/16.
//  Copyright (c) 2016 mai.wang. All rights reserved.
//

import UIKit
import SpriteKit


class GameViewController: UIViewController {
    var scene: GameScene!
    var swiftris: Swiftris!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let skView = view as! SKView
        skView.multipleTouchEnabled = false
        
        scene = GameScene(size: skView.bounds.size)
        scene.scaleMode = .AspectFill
        
        // we've set a closure for the tick property of GameScene.swift. Remember that functions are closures
        // with names. In our case, we've used a function named didTick(). All it does is lower the falling
        // shape by one row and then asks GameScene to redraw the shape at its new location.
        scene.tick = didTick
        swiftris = Swiftris()
        swiftris.beginGame()
        
        skView.presentScene(scene)
        
        // we add nextShape to the game layer at the preview location. When that animation completes, we
        // reposition the underlying Shape object at the starting row and staring column before we ask 
        // GameScene to move it from the preview location to its staring position. Once that completes,
        // we ask Swiftris for a new shape, begin ticking, and add the newly established upcoming piece to
        // the preview area.
        // Run Swiftris and observe the majesty of an ever-falling shape as it exceeds the limits of our
        // imaginary digital boundaries!
        scene.addPreviewShapeToScene(swiftris.nextShape!) {
            self.swiftris.nextShape?.moveTo(StartingColumn, row: StartingRow)
            self.scene.movePreviewShape(self.swiftris.nextShape!) {
                let nextShapes = self.swiftris.newShape()
                self.scene.startTicking()
                self.scene.addPreviewShapeToScene(nextShapes.nextShape!) {}
            }
            
        }
    }

    override func shouldAutorotate() -> Bool {
        return true
    }

    override func prefersStatusBarHidden() -> Bool {
        return true
    }
    
    func didTick() {
        swiftris.fallingShape?.lowerShapeByOneRow()
        scene.redrawShape(swiftris.fallingShape!, completion: {})
    }
}
