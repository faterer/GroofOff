package main

import (
	"fmt"
	"math/rand"
	"time"
)

var s1 rand.Source
var r1 *rand.Rand

func Max(x, y int) int {
	if x > y {
		return x
	}
	return y
}
func Min(x, y int) int {
	if x > y {
		return y
	}
	return x
}

func RandDataGen() (int, int) {

	num1 := r1.Intn(99) + 1
	num2 := r1.Intn(99) + 1
	return num1, num2
}

func AddGen() (string) {
	var sum, num1, num2 int
	for {
		num1, num2 = RandDataGen()
		sum = num1 + num2
		if sum < 100 {
			break;
		}
	}

	result := fmt.Sprintf("%2d + %2d =", num1, num2)
	return result
}

func MinusGen() (string) {
	var num1, num2 int
	num1, num2 = RandDataGen()
	result := fmt.Sprintf("%2d - %2d =", Max(num1, num2), Min(num1, num2))
	return result
}

func MultiplyGen() string {
	num1 := r1.Intn(8) + 2
	num2 := r1.Intn(8) + 2
	result := fmt.Sprintf("%2d × %2d =", num1, num2)
	return result	
}

func DivideGen() string {
	num1 := r1.Intn(8) + 2
	num2 := r1.Intn(8) + 2
	result := fmt.Sprintf("%2d ÷ %2d =", num1 * num2, num1)
	return result		
}

func GenOneDay() {
	s1 = rand.NewSource(time.Now().UnixNano())	
	r1 = rand.New(s1)
	fmt.Print("日期：")
	fmt.Print("\t\t\t")
	fmt.Print("用时：")
	fmt.Print("\t\t\t")
	fmt.Print("准确率：")
	fmt.Println()
	fmt.Println("口算：")
	for i := 0; i < 4; i++ {
		fmt.Printf(AddGen())
		fmt.Printf("\t")
	}
	fmt.Println()
	for i := 0; i < 4; i++ {
		fmt.Printf(MinusGen())
		fmt.Printf("\t")
	}
	fmt.Println()
	for i := 0; i < 4; i++ {
		fmt.Printf(AddGen())
		fmt.Printf("\t")
	}
	fmt.Println()
	for i := 0; i < 4; i++ {
		fmt.Printf(MinusGen())
		fmt.Printf("\t")
	}
	fmt.Println()
	for i := 0; i < 2; i++ {
		fmt.Printf(AddGen())
		fmt.Printf("\t")
	}
	for i := 0; i < 2; i++ {
		fmt.Printf(MinusGen())
		fmt.Printf("\t")
	}
	fmt.Println()	
	for i := 0; i < 4; i++ {
		fmt.Printf(MultiplyGen())
		fmt.Printf("\t")
	}
	fmt.Println()	
	for i := 0; i < 4; i++ {
		fmt.Printf(DivideGen())
		fmt.Printf("\t")
	}
	fmt.Println()
	for i := 0; i < 4; i++ {
		fmt.Printf(MultiplyGen())
		fmt.Printf("\t")
	}
	fmt.Println()	
	for i := 0; i < 4; i++ {
		fmt.Printf(DivideGen())
		fmt.Printf("\t")
	}
	fmt.Println()
	for i := 0; i < 2; i++ {
		fmt.Printf(MultiplyGen())
		fmt.Printf("\t")
	}
	for i := 0; i < 2; i++ {
		fmt.Printf(DivideGen())
		fmt.Printf("\t")
	}
	fmt.Println()	
}
/*
func Backup() {
	fmt.Println("笔算：")
	for i := 0; i < 3; i++ {
		fmt.Printf(AddGen())
		fmt.Printf("\t\t")
	}
	for i := 0; i < 6; i++ {
		fmt.Println()
	}
	for i := 0; i < 3; i++ {
		fmt.Printf(MinusGen())
		fmt.Printf("\t\t")
	}	
	for i := 0; i < 6; i++ {
		fmt.Println()
	}
	for i := 0; i < 3; i++ {
		fmt.Printf(MinusGen())
		fmt.Printf("\t\t")
	}
}
*/

func main() {
	for i:=0;i<1;i++ {
		GenOneDay()
	}
}