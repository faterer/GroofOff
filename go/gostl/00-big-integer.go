package main

import (
	"fmt"
	"math/big"
)

func main() {
	bigInteger1 := big.NewInt(9223372036854775807)
	bigInteger2 := big.NewInt(9223372036854775807)
	sum := big.NewInt(0)
	fmt.Println(bigInteger1)
	fmt.Println(sum.Add(bigInteger1, bigInteger2))
	fmt.Println(sum.Mul(bigInteger1, bigInteger2))
}
