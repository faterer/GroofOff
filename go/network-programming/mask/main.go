package main

import (
	"fmt"
	"net"
	"os"
)

func main()  {
	if len(os.Args) != 2 {
		fmt.Fprintf(os.Stderr, "Usage: %s dotted-ip-addr\n", os.Args[0])
		os.Exit(1)
	}

	dotAddr := os.Args[1]

	addr := net.ParseIP(dotAddr)
	if addr == nil {
		fmt.Println("Invalid ip address")
		os.Exit(1)
	}

	mask := addr.DefaultMask()
	network := addr.Mask(mask)
	ones, bits := mask.Size()
	fmt.Println("Address is", addr.String(),
				"Default Mask length is", bits,
				"Leading ones count is", ones,
				"Mask is (hex)", mask.String(),
				"Network is", network.String())
	os.Exit(0)
}

//go run main.go 127.0.0.1
//Address is 127.0.0.1 Default Mask length is 32 Leading ones count is 8 Mask is (hex) ff000000 Network is 127.0.0.0
