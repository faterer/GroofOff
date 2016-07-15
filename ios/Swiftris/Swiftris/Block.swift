//
//  Block.swift
//  Swiftris
//
//  Created by carol on 7/3/16.
//  Copyright © 2016 mai.wang. All rights reserved.
//

import SpriteKit

// As you may have guessed, this isn't everything you'll 
// need to represent a block. The first part of this file 
// defines an enumeration: BlockColor. Swiftris supports 
// six different colors in total.

// we define the number of colors available to Swiftris, six
let NumberOfColors: UInt32 = 6

// we declare the enumeration. Its type is Int and it implements
// the CustomStringConvertible protocol.
enum BlockColor: Int, CustomStringConvertible {
    // we provide the full list of enumerable options, one for each 
    // color beginning with Blue at 0 and ending at 5 with Yellow.
    case Blue = 0, Orange, Purple, Red, Teal, Yellow
    
    // we define a computed property, spriteName. A computed property is 
    // one that behaves like a typical variable, but when accessing it, 
    // a code block generates its value each time. We could have put this 
    // inside of a function named, getSpriteName() but a computed property 
    // is the better design choice.
    // spriteName returns the correct filename for the given color, we use a 
    // simple switch…case statement to achieve this.
    // computed property
    var spriteName: String {
        switch self {
        case .Blue:
            return "blue"
        case .Orange:
            return "orange"
        case .Purple:
            return "purple"
        case .Red:
            return "red"
        case .Teal:
            return "teal"
        case .Yellow:
            return "yellow"
        }
    }
    
    // we declare yet another computed property, description. Adhering to the 
    // CustomStringConvertible property requires us to provide this function. 
    // Without it, our code will fail to compile. It returns the spriteName of 
    // the color to describe the object.
    var description: String {
        return self.spriteName
    }
    
    // we declare a static function named random(). As you may have guessed, 
    // this function returns a random choice among the colors found in BlockColor. 
    // It creates a BlockColor using the rawValue:Int initializer to setup 
    // an enumeration which assigned to the numerical value passed into it, 
    // in our case numbers 0 through 5.
    static func random() -> BlockColor {
        return BlockColor(rawValue:Int(arc4random_uniform(NumberOfColors)))!
    }
}


// It's time to get a little abstract. In programming we use classes
// to represnet real-world objects. In Swiftris, our objects are shapes
// and four independent parts, building blocks if you will, compose each
// shape. Let's represent these independent blocks as objects. We'll do
// so by creating a brand new class named Block.

// Classes, structures and enums that implement CustomStringConvertible are 
// capable of generating human-readable strings when debugging or printing 
// their value to the console.

// we declare Block as a class which implements both the CustomStringConvertible 
// and Hashable protocols. Hashable allows us to store Block in Array2D.
class Block: Hashable, CustomStringConvertible {
    // we define our color property as let, meaning once we assign it, 
    // it can no longer be re-assigned. A block should not be able to change 
    // colors mid-game unless you decide to make Swiftris: Epileptic Adventures.
    let color: BlockColor
    // we declare a column and row. These properties represent the location of 
    // the Block on our game board. The SKSpriteNode will represent the visual 
    // element of the Block which GameScene will use to render and animate each Block.
    var column: Int
    var row: Int
    var sprite: SKSpriteNode?
    // we provided a convenient shortcut for recovering the sprite's file name. 
    // It shortened our code from block.color.spriteName to block.spriteName.
    var spriteName: String {
        return color.spriteName
    }
    // we implemented the hashValue calculated property, which Hashable requires 
    // us to provide. We return the exclusive-or of our row and column properties 
    // to generate a unique integer for each Block.
    var hashValue: Int {
        return self.column ^ self.row
    }
    // we implement description as we must do to adhere to the CustomStringConvertible 
    // protocol. We can place CustomStringConvertible object types in the middle of a 
    // string by surrounding them with \( and ).
    var description: String {
        return "\(color): [\(column), \(row)]"
    }
    
    init(column: Int, row: Int, color: BlockColor) {
        self.column = column
        self.row = row
        self.color = color
    }
}

// we create a custom operator, ==, when comparing one Block with another. 
// It returns true if both Blocks are in the same location and of the same color. 
// The Hashable protocol inherits from the Equatable protocol, which requires us 
// to provide this operator.
func ==(lhs: Block, rhs: Block) -> Bool {
    return lhs.column == rhs.column && lhs.row == rhs.row
        && lhs.color.rawValue == rhs.color.rawValue
}