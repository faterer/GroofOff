package main

import "sort"
import "fmt"

//Sometimes we’ll want to sort a collection by something other than its natural order. For example, suppose we wanted to sort strings by their length instead of alphabetically. Here’s an example of custom sorts in Go.

//In order to sort by a custom function in Go, we need a corresponding type. Here we’ve created a byLength type that is just an alias for the builtin []string type.
type byLength []string

