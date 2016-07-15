//
//  Shape.swift
//  Swiftris
//
//  Created by carol on 7/3/16.
//  Copyright © 2016 mai.wang. All rights reserved.
//
// Without shape, our blocks are aimless colored squares longing 
// for purpose in their short-lived binary lives. Let's put them 
// to use by creating a Shape class. Shape will define the 
// recognizable Tetromino pieces we all know and love. You know 
// the drill; create a new file named Shape.swift and replace 
// its contents with the following:
import SpriteKit

let NumOrientations: UInt32 = 4

// This first piece of code should appear familiar. Once again we 
// created an enumeration helper which will define the shape's 
// orientation. A Tetromino can face one of four directions at any 
// given point, we refer to them as 0, 90, 180 and 270. Imagine a 
// circle whose degrees begin at the top and continue clockwise.
enum Orientation: Int, CustomStringConvertible {
    case Zero = 0, Ninety, OneEighty, TwoSeventy
    
    var description: String {
        switch self {
        case .Zero:
            return "0"
        case .Ninety:
            return "90"
        case .OneEighty:
            return "180"
        case .TwoSeventy:
            return "270"
        }
    }
    
    static func random() -> Orientation {
        return Orientation(rawValue: Int(arc4random_uniform(NumOrientations)))!
    }
    // we provided a method capable of returning the next orientation 
    // when traveling either clockwise or counterclockwise.
    static func rotate(orientation: Orientation, clockwise: Bool) -> Orientation {
        var rotated = orientation.rawValue + (clockwise ? 1 : -1)
        if rotated > Orientation.TwoSeventy.rawValue {
            rotated = Orientation.Zero.rawValue
        } else if rotated < 0 {
            rotated = Orientation.TwoSeventy.rawValue
        }
        return Orientation(rawValue: rotated)!
    }
}

// The number of total shape varieties
let NumShapeTypes: UInt32 = 7

// Shape indexes
let FirstBlockIdx: Int = 0
let SecondBlockIdx: Int = 1
let ThirdBlockIdx: Int = 2
let FourthBlockIdx: Int = 3

class Shape: Hashable, CustomStringConvertible {
    // The color of the shape
    let color: BlockColor
    
    // The blocks comprising the shape
    var blocks = Array<Block>()
    // The current orientation of the shape
    var orientation: Orientation
    // The column and row representing the shape's anchor point
    var column, row: Int
    
    // introduce some Swift tools that you're certain to find interesting. 
    // We have written these two computed properties and left their 
    // results empty. This was on purpose such that our actual shape 
    // classes will override them in their respective implementations. 
    // Subclasses must override this property
    // blockRowColumnPositions defines a computed Dictionary. 
    // We define a dictionary with square braces, […], and use 
    // it to map one object to another. The first object type 
    // listed defines the key and the second, a value. Keys map 
    // one-to-one with values and duplicate keys may not exist.
    var blockRowColumnPositions: [Orientation: Array<(columnDiff: Int, rowDiff: Int)>] {
        return [:]
    }
    
    // Subclasses must override this property
    var bottomBlocksForOrientations: [Orientation: Array<Block>] {
        return [:]
    }
    
    var bottomBlocks:Array<Block> {
        guard let bottomBlocks = bottomBlocksForOrientations[orientation] else {
            return []
        }
        return bottomBlocks
    }
    
    // Hashable
    // we use the 
    // reduce<S : Sequence, U>(sequence: S, initial: U, 
    //                         combine: (U, S.GeneratorType.Element) -> U) -> U 
    // method to iterate through our entire blocks array. 
    // We exclusive-or (XOR) each block's hashValue together to 
    // create a single hashValue for the Shape they comprise.
    var hashValue: Int {
        return blocks.reduce(0) { $0.hashValue ^ $1.hashValue}
    }
    
    // CustomStringConvertible
    var description: String {
        return "\(color) block facing \(orientation): \(blocks[FirstBlockIdx]),\(blocks[SecondBlockIdx]), \(blocks[ThirdBlockIdx]), \(blocks[FourthBlockIdx])"
    }
    
    init(column:Int, row:Int, color: BlockColor, orientation:Orientation) {
        self.color = color
        self.column = column
        self.row = row
        self.orientation = orientation
        initializeBlocks()
    }
    
    // we introduce a special initializer. A convenience initializer must 
    // call down to a standard initializer or otherwise your class will 
    // fail to compile. We've placed this one here to simplify the 
    // initialization process for users of the Shape class. It assigns the 
    // given row and column values while generating a random color and a 
    // random orientation.
    convenience init(column:Int, row:Int) {
        self.init(column:column, row:row, color:BlockColor.random(), orientation:Orientation.random())
    }
    
    // we defined a final function which means it cannot be overridden by 
    // subclasses. Shape and its subclasses must use this implementation of 
    // initializeBlocks().
    final func initializeBlocks() {
        guard let blocksRowColumnTranslations = blockRowColumnPositions[orientation] else {
            return
        }
        // we use the map function to create the blocks array. map performs 
        // a specific task: it executes the provided code block for each 
        // object found in the array, and in our case, each block must 
        // return a Block object.
        // map adds each Block returned by our code to the blocks array. 
        // map lets us create one array after looping over the contents of another.
        blocks = blocksRowColumnTranslations.map { (diff) -> Block in
            return Block(column: column + diff.columnDiff, row: row + diff.rowDiff, color: color)
        }
    }
    
    final func rotateBlocks(orientation: Orientation) {
        guard let blockRowColumnTranslation:Array<(columnDiff: Int, rowDiff: Int)> = blockRowColumnPositions[orientation] else {
            return
        }
        
        // we introduce the enumerate function. This allows us to iterate through 
        // an array object by defining an index variable, idx, as well as the 
        // contents at that index, diff, which refers to (columnDiff:Int, rowDiff:Int).
        for (idx, diff) in blockRowColumnTranslation.enumerate() {
            blocks[idx].column = column + diff.columnDiff
            blocks[idx].row = row + diff.rowDiff
        }
    }
    
    final func rotateClockwise() {
        let newOrientation = Orientation.rotate(orientation, clockwise: true)
        rotateBlocks(newOrientation)
        orientation = newOrientation
    }
    
    final func rotateCounterClockwise() {
        let newOrientation = Orientation.rotate(orientation, clockwise: false)
        rotateBlocks(newOrientation)
        orientation = newOrientation
    }
    
    final func lowerShapeByOneRow() {
        shiftBy(0, rows:1)
    }
    
    final func raiseShapeByOneRow() {
        shiftBy(0, rows:-1)
    }
    
    final func shiftRightByOneColumn() {
        shiftBy(1, rows:0)
    }
    
    final func shiftLeftByOneColumn() {
        shiftBy(-1, rows:0)
    }
    
    // we've included a simple shiftBy(columns: Int, rows: Int) method 
    // which will adjust each row and column by rows and columns, respectively.
    final func shiftBy(columns: Int, rows: Int) {
        self.column += columns
        self.row += rows
        for block in blocks {
            block.column += columns
            block.row += rows
        }
    }
    // we provide an absolute approach to position modification by setting 
    // the column and row properties before rotating the blocks to their 
    // current orientation which causes an accurate realignment of all blocks 
    // relative to the new row and column properties.
    final func moveTo(column: Int, row: Int) {
        self.column = column
        self.row = row
        rotateBlocks(orientation)
    }
    
    // we've created a method to generate a random Tetromino shape and 
    // you can see that subclasses naturally inherit initializers from 
    // their parent class.
    final class func random(startingColumn:Int, startingRow:Int) -> Shape {
        switch Int(arc4random_uniform(NumShapeTypes)) {
        case 0:
            return SquareShape(column:startingColumn, row:startingRow)
        case 1:
            return LineShape(column: startingColumn, row: startingRow)
        case 2:
            return TShape(column: startingColumn, row: startingRow)
        case 3:
            return LShape(column: startingColumn, row: startingRow)
        case 4:
            return JShape(column: startingColumn, row: startingRow)
        case 5:
            return SShape(column: startingColumn, row: startingRow)
        default:
            return ZShape(column: startingColumn, row: startingRow)
        }
    }
}

func ==(lhs: Shape, rhs: Shape) -> Bool {
    return lhs.row == rhs.row && lhs.column == rhs.column
}












