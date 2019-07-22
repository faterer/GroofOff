package main

import (
	"fmt"
	"net"
	"os"
)

func main()  {
	if len(os.Args) != 2 {
		fmt.Fprintf(os.Stderr, "Usage: %s hostname", os.Args[0])
		fmt.Println("Usage: ", os.Args[0], "hostname")
	}

	name := os.Args[1]

	addr, err := net.ResolveIPAddr("ip", name)
	if err != nil {
		fmt.Println("Resolution error", err.Error())
		os.Exit(1)
	}
	fmt.Println("Resolved address is ", addr.String())
	os.Exit(0)
}


//go run main.go www.baidu.com
//Resolved address is  45.113.192.101
