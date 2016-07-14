
//  GameScene.swift
//  Swiftris
//
//  Created by carol on 7/2/16.
//  Copyright (c) 2016 mai.wang. All rights reserved.
//

import SpriteKit

// we define the point size of each block sprite, in our case 
// 20.0 * 20.0, the lower of the available resolution option 
// for each block image. We alsodeclare a layer position 
// which will give us an offset from the edge of the screen
let BlockSize:CGFloat = 20.0
// we define a new constant, TickLengthLevelOne. This variable will
// represent the slowest speed at which our shapes will travel.
// We've set it to 600 millisecond, which means that every 6/10ths
// of a second, our shape should descend by one row.
let TickLengthLevelOne = NSTimeInterval(600)

class GameScene: SKScene {
    
    // we've introduced a couple of SKNode(s) which act as 
    // superimposed layer of activity within our scene.
    // The gameLayer sits above the background visuals 
    // and the shapeLayer sits atop that.
    let gameLayer = SKNode()
    let shapeLayer = SKNode()
    let LayerPosition = CGPoint(x: 6, y: -6)
    
    // you can see we've defined some variables. tickLengthMillis and 
    // lastTick look like declaration we've seen before: one being the
    // GameScene's current tick length, set TickLengthLevelOne by default,
    // and the other will track the last time we experienced a tick,
    // an NSDate object.
    // tick:(()->())? looks horifying...tick is what's known as a closure
    // in Swift. A closure is essentially a block of code that performs a
    // funcation, and Swift refers to funcation as closure. In defining tick,
    // its type is (() -> ())? which means that it's a closure which take no
    // parameters and returns nothing. Its question mark indicate that it's 
    // optional and may be nil.
    var tick:(()->())?
    var tickLengthMillis = TickLengthLevelOne
    var lastTick:NSDate?
    var textureCache = Dictionary<String, SKTexture>()
    
    required init(coder aDecoder: NSCoder) {
        fatalError("NSCoder not supported")
    }
    
    override init(size: CGSize) {
        super.init(size: size)
        
        anchorPoint = CGPoint(x: 0, y: 1.0)
        let background = SKSpriteNode(imageNamed: "background")
        background.position = CGPoint(x: 0, y: 0)
        background.anchorPoint = CGPoint(x: 0, y: 1.0)
        addChild(background)
        addChild(gameLayer)
        
        let gameBoardTexture = SKTexture(imageNamed: "gameboard")
        let gameBoard = SKSpriteNode(texture: gameBoardTexture, size: CGSizeMake(BlockSize * CGFloat(NumColumns), BlockSize * CGFloat(NumRows)))
        gameBoard.anchorPoint = CGPoint(x:0, y:1.0)
        gameBoard.position = LayerPosition
        
        shapeLayer.position = LayerPosition
        shapeLayer.addChild(gameBoard)
        gameLayer.addChild(shapeLayer)
    }
    
    override func update(currentTime: CFTimeInterval) {
        /* Called before each frame is rendered */
        // we'll put our new member variables to work. 
        // Swift's guard statement checks the conditions which follow it,
        // let lastTick = lastTick in our case. If the conditions fail,
        // guard executes the else block. if lastTick is missing, the game
        // is in a paused state and not reporting elapsed ticks, so we return.
        // But if lastTick is present, we recover the time passed since the last
        // execution of update by invoking timeIntervalSinceNow on our lastTick
        // object. We multiply the result by -1000 to calcute a positive millisecond
        // value. We invoke functions on object using dot syntax in Swift.
        guard let lastTick = lastTick else {
            return
        }
        let timePassed = lastTick.timeIntervalSinceNow * -1000.0
        // we then check if the time passed has exceeded our tickLengthMillis
        // variable. if enough time has elapsed, we must report a tick. We do 
        // so by first updating our last known tick time to the present and 
        // then invoking our closure.
        // By placing a ? after the variable name, we are asking Swift to first
        // check if tick exist and if so, invoke it with no parameters. It's
        // shorthand for the following statements:
        // if tick != nil {
        //     tick!()
        // }
        if timePassed > tickLengthMillis {
            self.lastTick = NSDate()
            tick?()
        }
    }

    // we provide accessor methods to let external classes stop and start the 
    // ticking process, something we'll make use of later to keep pieces from 
    // falling at key moments.
    func startTicking() {
        lastTick = NSDate()
    }
    
    func stopTicking() {
        lastTick = nil
    }
    
    // we've written GameScene's most important function, pointForColumn. 
    // This function returns the precise coordinate on the screen for 
    // where a block sprite belongs based on its row and column position. 
    // The match here looks funky but know that we anchor each sprite as 
    // its center, so we need to find the center coordinates before placing 
    // it in our shapeLayer object
    func pointForColumn(column:Int, row: Int) -> CGPoint {
        let x = LayerPosition.x + (CGFloat(column) * BlockSize) + (BlockSize / 2)
        let y = LayerPosition.y - ((CGFloat(row) * BlockSize) + (BlockSize) / 2)
        return CGPointMake(x, y)
    }
    
    // we've created a method which will add a shape for the first time to
    // the scene as a preview shape. We use a dictionary to store copies of
    // re-usable SKTexture objects since each shape will require more than
    // one copy of the same image.
    func addPreviewShapeToScene(shape:Shape, completion:() -> ()) {
        for block in shape.blocks {
            var texture = textureCache[block.spriteName]
            if texture == nil {
                texture = SKTexture(imageNamed: block.spriteName)
                textureCache[block.spriteName] = texture
            }
            
            let sprite = SKSpriteNode(texture: texture)
            // we use our convenient pointForColumn method to place each block's 
            // sprite in the proper location. We start it at row - 2, such that 
            // the preview piece animates smoothly into place from a higher location
            sprite.position = pointForColumn(block.column, row: block.row - 2)
            shapeLayer.addChild(sprite)
            block.sprite = sprite
            
            // Animation
            sprite.alpha = 0
            // we introduce SKAction objects which are responsible for visually 
            // manipulating SKNode objects Each block will fade and move into 
            // place as it appears as part of the next piece. It will move two 
            // rows down and fade from complete transparency to 70% opacity
            // This small design choice lets the player ignore the preview piece 
            // if they so choose since it will be duller than the active moving 
            // piece. The remaining two methods make use of the same SKAction 
            // objects to move and redraw each block for a given shape.
            let moveAction = SKAction.moveTo(pointForColumn(block.column, row: block.row), duration: NSTimeInterval(0.2))
            moveAction.timingMode = .EaseOut
            let fadeInAction = SKAction.fadeAlphaTo(0.7, duration: 0.4)
            fadeInAction.timingMode = .EaseOut
            sprite.runAction(SKAction.group([moveAction, fadeInAction]))
        }
        runAction(SKAction.waitForDuration(0.4), completion: completion)
    }
    
    func movePreviewShape(shape:Shape, completion:() -> ()) {
        for block in shape.blocks {
            let sprite = block.sprite!
            let moveTo = pointForColumn(block.column, row:block.row)
            let moveToAction:SKAction = SKAction.moveTo(moveTo, duration: 0.2)
            moveToAction.timingMode = .EaseOut
            sprite.runAction(
                SKAction.group([moveToAction, SKAction.fadeAlphaTo(1.0, duration: 0.2)]), completion: {})
        }
        runAction(SKAction.waitForDuration(0.2), completion: completion)
    }
    
    func redrawShape(shape:Shape, completion:() -> ()) {
        for block in shape.blocks {
            let sprite = block.sprite!
            let moveTo = pointForColumn(block.column, row: block.row)
            let moveToAction:SKAction = SKAction.moveTo(moveTo, duration: 0.05)
            moveToAction.timingMode = .EaseOut
            if block == shape.blocks.last {
                sprite.runAction(moveToAction, completion: completion)
            } else {
                sprite.runAction(moveToAction)
            }
        }
    }
}