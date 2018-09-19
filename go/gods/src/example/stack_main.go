package main

import (
	"stack"
	"fmt"
)

func main() {
	s := stack.New()
	s.Push(1)
	s.Push(2)
	s.Push(3)
	s.Push(4)
	s.Push(5)
	fmt.Println("stack len:", s.Len())
	for i := s.Len();  i> 0; i-- {
		v := s.Pop()
		fmt.Print(v)
		fmt.Print(" ")
	}
	fmt.Println()
	fmt.Println("stack len:", s.Len())
}