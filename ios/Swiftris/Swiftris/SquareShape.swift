//
//  SquareShape.swift
//  Swiftris
//
//  Created by carol on 7/5/16.
//  Copyright © 2016 mai.wang. All rights reserved.
//

class SquareShape:Shape {
    // A square shape is the easiest, it will not rotate at all 
    // since its shape is identical at every orientation. 
    // Its bottom blocks will always be the third and fourth 
    // block as described by the comments
    /*
     | 0*| 1 |
     | 2 | 3 |
     marks the row/column indicator for the shape
    */
    
    // The square shape will not rotate
    // we've overridden the blockRowColumnPositions computed property 
    // to provide a full dictionary of tuple arrays. Each index of the 
    // arrays represents one of the four blocks ordered from 
    // block 0 to block 3. For example, the top-left block location – 
    // block 0 – of a square is identical to its row and column location. 
    // The tuple is (0, 0), 0 column difference and 0 row difference. 
    // The second block is always 1 column to the right of the shape's 
    // given column value, so its tuple is always (1, 0).
    override var blockRowColumnPositions: [Orientation : Array<(columnDiff: Int, rowDiff: Int)>] {
        return [
            Orientation.Zero: [(0, 0), (1, 0), (0, 1), (1, 1)],
            Orientation.OneEighty: [(0, 0), (1, 0), (0, 1), (1, 1)],
            Orientation.Ninety: [(0, 0), (1, 0), (0, 1), (1, 1)],
            Orientation.TwoSeventy: [(0, 0), (1, 0), (0, 1), (1, 1)]
        ]
    }
    // we perform a similar override by providing a dictionary of bottom 
    // block arrays. As stated earlier, a square shape does not rotate, 
    // so its bottom-most blocks are consistently the third and fourth 
    // blocks as indicated by the comments.
    override var bottomBlocksForOrientations: [Orientation : Array<Block>] {
        return [
            Orientation.Zero:       [blocks[ThirdBlockIdx], blocks[FourthBlockIdx]],
            Orientation.OneEighty:  [blocks[ThirdBlockIdx], blocks[FourthBlockIdx]],
            Orientation.Ninety:     [blocks[ThirdBlockIdx], blocks[FourthBlockIdx]],
            Orientation.TwoSeventy: [blocks[ThirdBlockIdx], blocks[FourthBlockIdx]]
        ]
    }
}
