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

	num1 := r1.Intn(399) + 100
	num2 := r1.Intn(399) + 100
	return num1, num2
}

func AddGen() string {
	var sum, num1, num2 int
	for {
		num1, num2 = RandDataGen()
		sum = num1 + num2

		if num1 % 10 + num2 % 10 < 10 {
			continue
		}

		if sum > 100 && sum < 1000 {
			break
		}
	}

	result := fmt.Sprintf("%2d + %2d =", num1, num2)
	return result
}

func MinusGen() string {
	var num1, num2 int
	var max, min int
	for {
		num1, num2 = RandDataGen()
		max = Max(num1, num2)
		min = Min(num1, num2)

		if max % 10 < min % 10 {
			break
		}
	}

	result := fmt.Sprintf("%2d - %2d =", max, min)
	return result
}

func MultiplyGen() string {
	num1 := r1.Intn(8) + 2
	num2 := r1.Intn(8) + 2
	result := fmt.Sprintf("%2d × %2d =", num1, num2)
	return result
}

func DivideGen() string {


	var num1, num2, num3 int
	for {
		num1 = r1.Intn(7) + 3
		num2 = r1.Intn(7) + 3
		num3 = r1.Intn(5) + 1
		if num3 != num1 && num3 != num2 && ((num1*num2+num3) < (num1*9)) {
			break
		}

	}

	result := fmt.Sprintf("%2d ÷ %2d =", num1*num2 + num3, num1)
	return result
}


/*
func GenOneDay(day int) {
	seed := time.Now().UnixNano() + (int64)(100*day)
	s1 = rand.NewSource(seed)
	r1 = rand.New(s1)
	fmt.Print("日期：")
	fmt.Print("\t\t\t")
	fmt.Print("用时：")
	fmt.Print("\t\t\t")
	fmt.Print("准确率：")
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
*/
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

func GenOneDay(day int) {
	seed := time.Now().UnixNano() + (int64)(100*day)
	s1 = rand.NewSource(seed)
	r1 = rand.New(s1)
	fmt.Print("日期：")
	fmt.Print("\t\t\t")
	fmt.Print("用时：")
	fmt.Print("\t\t\t")
	fmt.Print("准确率：")
	fmt.Println()
	for i := 0; i < 3; i++ {
		fmt.Printf(AddGen())
		fmt.Printf("\t\t")
	}
	fmt.Println()
	fmt.Println()
	fmt.Println()
	fmt.Println()
	for i := 0; i < 3; i++ {
		fmt.Printf(MinusGen())
		fmt.Printf("\t\t")
	}
	fmt.Println()
	fmt.Println()
	fmt.Println()
	fmt.Println()
	for i := 0; i < 3; i++ {
		fmt.Printf(DivideGen())
		fmt.Printf("\t\t\t")
	}
	fmt.Println()
	fmt.Println()
}

func main() {
	for i := 0; i < 50; i++ {
		GenOneDay(i)
		if i % 2 == 0 {
			//fmt.Println()
			fmt.Println()
		}
	}
}
