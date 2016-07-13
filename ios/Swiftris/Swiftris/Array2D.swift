//
//  Array2D.swift
//  Swiftris
//
//  Created by carol on 7/3/16.
//  Copyright © 2016 mai.wang. All rights reserved.
//

// we're defining  a class named Array2D. 
// Generic arrays in swift are actually of type struct,
// not class, but we need a class in this case such that
// whereever we use the game board array in the project.
// we will manipulate the same data.
// we may pass class objects by reference(same data) whereas
// we must pass sturctures by value(copied data).
// Our game logic will require a single copy of this data
// sturcture to persist across the entire game.
class Array2D<T> {
    let columns: Int
    let rows: Int
    // we declare an actual swift array; It will be the underlying
    // data sturcture which maintains reference to our objects.
    // It's declared with type <T?>. A ? in swift symbolizes an
    // optional value
    // An optional value is just that, optional. Optional variables
    // may or may not contain data, and they may in fact be nil, or
    // empty. nil locations found our game board will represent empty
    // spots where no block is present
    var array: Array<T?>
    
    init(columns: Int, rows: Int) {
        self.columns = columns
        self.rows = rows
        // we instantiate our internal array sturcture with a size of
        // rows * columns. This guarantees that Array2D can store all
        // the objects our game board require, 200 in our case.
        array = Array<T?>(count:rows * columns, repeatedValue: nil)
    }
    
    // we create a custom subscript for Array2D. We mentioned earlier
    // that we wanted to have a subscript capable of supporting
    // array[column, row], this accomplished that. The getter is 
    // self-explanatory. To get the value at a given location we need 
    // to multiply the provided row by the class variable columns, then
    // add the column number to reach the final destination.
    // The setter is the reverse operation of that; we assign newValue 
    // to the location determined by the same algorithm found in the 
    // custom getter.
    subscript(column: Int, row: Int) -> T? {
        get {
            return array[(row * columns) + column]
        }
        set(newValue) {
            array[(row * columns) + column] = newValue
        }
    }
}
