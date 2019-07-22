package main

import (
	"fmt"
	"net"
	"os"
)

func main() {
	if len(os.Args) != 2 {
		fmt.Fprintf(os.Stderr, "Usage: %s ip-addr\n", os.Args[0])
		os.Exit(0)
	}

	name := os.Args[1]

	addr := net.ParseIP(name)
	if addr == nil {
		fmt.Println("Invalid ip address")
	} else {
		fmt.Println("This address is", addr.String())
	}
}

//go run main.go 0:0:0:0:0:0:0:1
//This address is  ::1