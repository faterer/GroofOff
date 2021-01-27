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

func RandDataGen2() (int, int) {

	num1 := r1.Intn(99) + 10
	num2 := r1.Intn(99) + 10
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

	result := fmt.Sprintf("%d + %d =", num1, num2)
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

	result := fmt.Sprintf("%d - %d =", max, min)
	return result
}

func DecimalAddGen() string {
	num1 := r1.Intn(79) + 20
	num2 := r1.Intn(79) + 20
	result := fmt.Sprintf("%.1f + %.1f =", float32 (num1)/float32 (10), float32 (num2)/float32 (10))
	return result
}

func DecimalMinusGen() string {
	num1 := r1.Intn(79) + 20
	num2 := r1.Intn(79) + 20
	result := fmt.Sprintf("%.1f - %.1f =", float32 (Max(num1, num2))/float32 (10), float32 (Min(num1, num2))/float32 (10))
	return result
}

func MultiplyGen() string {
	num1 := r1.Intn(50) + 40
	num2 := r1.Intn(8) + 2
	result := fmt.Sprintf("%3d × %3d =", num1, num2)
	return result
}

func MultiplyTwo() string {
	num1 := r1.Intn(50) + 49
	num2 := r1.Intn(50) + 49
	result := fmt.Sprintf("%3d × %3d =", num1, num2)
	return result
}

func DivideGenMod() string {
	var num1, num2, num3 int
	for {
		num1 = r1.Intn(7) + 3
		num2 = r1.Intn(7) + 3
		num3 = r1.Intn(5) + 1
		if num3 != num1 && num3 != num2 && ((num1*num2+num3) < (num1*9)) {
			break
		}

	}

	result := fmt.Sprintf("%3d ÷ %3d =", num1*num2 + num3, num1)
	return result
}

func DivideGen() string {
	num1 := r1.Intn(8) + 2
	num2 := r1.Intn(8) + 2
	result := fmt.Sprintf("%d ÷ %2d =", num1*num2, num2)
	return result
}

func DivideGen100() string {
	num1 := r1.Intn(8) + 2
	num2 := r1.Intn(8) + 2
	result := fmt.Sprintf("%d ÷ %2d =", num1*num2*100, num2)
	return result
}

func ThreeDivideOne() string {
	num1 := r1.Intn(900) + 100
	num2 := r1.Intn(7) + 2
	result := fmt.Sprintf("%d ÷ %3d =", num1, num2)
	return result
}

func Mix1Gen() string {
	var num1, num2, num3 int
	var max, min int
	num1, num2 = RandDataGen2()
	max = Max(num1, num2)
	min = Min(num1, num2)

	num3 = r1.Intn(8) + 2

	result := fmt.Sprintf("(%d-%d)×%d ", max, min, num3)
	return result
}

func Mix2Gen() string {
	var num1, num2, num3 int
	for {
		num1, num2 = RandDataGen2()
		if num1 + num2 < 100 {
			break
		}
	}
	num3 = r1.Intn(8) + 2

	result := fmt.Sprintf("(%d+%d)×%d ", num1, num2, num3)
	return result
}


func Mix3Gen() string {
	var num1, num2, num3 int
	num1 = r1.Intn(99) + 10
	num2 = r1.Intn(8) + 2
	num3 = r1.Intn(8) + 2

	result := fmt.Sprintf("%d+%d÷%d ", num1, num2*num3, num3)
	return result
}

func Mix4Gen() string {
	var num1, num2, num3 int
	num1 = r1.Intn(399) + 10
	num2 = r1.Intn(8) + 2
	num3 = r1.Intn(8) + 2

	result := fmt.Sprintf("%d+%d×%d ", num1, num2*num3, num3)
	return result
}


func MixMinusAddGen() string {
	var num1, num2, num3 int
	var max, min int
	num1, num2 = RandDataGen2()
	max = Max(num1, num2)
	min = Min(num1, num2)


	num3 = r1.Intn(399) + 100

	result := fmt.Sprintf("%d-%d+%d ", max, min, num3)
	return result
}

func MixAddMinusGen() string {
	var sum, num1, num2, num3 int
	for {
		num1, num2 = RandDataGen2()
		sum = num1 + num2
		num3 = r1.Intn(399) + 100
	
		if num3 < sum {
			break
		}
	}

	result := fmt.Sprintf("%d+%d-%d ", num1, num2, num3)
	return result
}

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
	fmt.Print("(一)口算：")
	fmt.Println()
	for j := 0; j < 2; j++ {
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
	}
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
		fmt.Printf(DivideGen100())
		fmt.Printf("\t")
	}
	fmt.Println()
	for i := 0; i < 4; i++ {
		fmt.Printf(MultiplyGen())
		fmt.Printf("\t")
	}
	fmt.Println()
	for i := 0; i < 4; i++ {
		fmt.Printf(DivideGen100())
		fmt.Printf("\t")
	}
	fmt.Println()
	for i := 0; i < 2; i++ {
		fmt.Printf(DecimalAddGen())
		fmt.Printf("\t")
	}
	for i := 0; i < 2; i++ {
		fmt.Printf(DecimalMinusGen())
		fmt.Printf("\t")
	}
	fmt.Println()	
	//for i := 0; i < 2; i++ {
	//	fmt.Printf(Mix1Gen())
	//	fmt.Printf("=\t")
	//}
	//for i := 0; i < 2; i++ {
	//	fmt.Printf(Mix2Gen())
	//	fmt.Printf("=\t")
	//}
	
	//for i := 0; i < 2; i++ {
	//	fmt.Printf(Mix3Gen())
	//	fmt.Printf("=\t\t")
	//}
	//for i := 0; i < 2; i++ {
	//	fmt.Printf(Mix4Gen())
	//	fmt.Printf("=\t")
	//}
	//fmt.Println()
	fmt.Print("(二)脱式计算：")
	fmt.Println()
	fmt.Printf(MixAddMinusGen())
	fmt.Printf("\t\t")
	fmt.Printf(MixMinusAddGen())
	fmt.Printf("\t\t")
	fmt.Printf(Mix4Gen())
	fmt.Printf("\t")
	fmt.Println()
	fmt.Println()
	fmt.Printf(Mix1Gen())
	fmt.Printf("\t\t")
	fmt.Printf(Mix2Gen())
	fmt.Printf("\t\t")
	fmt.Printf(Mix3Gen())
	fmt.Printf("\t")
	fmt.Println()
	fmt.Println()

	fmt.Print("(三)竖式计算：")
	fmt.Println()
	for i := 0; i < 3; i++ {
		//fmt.Printf(DecimalAddGen())
		fmt.Printf(MultiplyTwo())
		fmt.Printf("\t\t")
	}
	fmt.Println()
	fmt.Println()
	fmt.Println()
	for i := 0; i < 3; i++ {
		//fmt.Printf(DecimalMinusGen())
		fmt.Printf(ThreeDivideOne())
		fmt.Printf("\t\t")
	}
	
	fmt.Println()
	fmt.Println()
}

func main() {
	for i := 0; i < 30; i++ {
		GenOneDay(i)
		//fmt.Println()
	}
}
