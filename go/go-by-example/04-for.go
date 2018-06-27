package main

import "fmt"

//for is Go's only looping construct. Here are three basic types of for loops
func main() {
	//The most basic type, with single condition
	i := 1
	for i <= 3 {
		fmt.Println(i)
		i = i + 1
	}

	//A classic initial/condition/after for loop
	for j := 7; j <= 9; j++ {
		fmt.Println(j)
	}

	//for without condition will loop repeatedly until you break out of the loop or
	//return from the enclosing function
	for {
		fmt.Println("loop")
		break
	}

	//You can also continue to the next iteration of the loop
	for n := 0; n <= 5; n++ {
		if n%2 == 0 {
			continue
		}
		fmt.Println(n)
	}
}

//We'll see some other for forms later when we look at range statements, channel, and other data structures
