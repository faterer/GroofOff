package main

import (
	"fmt"
	"net"
	"os"
	"time"
)

func main() {

	service := ":1200"
	udpAddr, err := net.ResolveUDPAddr("udp", service)
	checkError(err)

	conn, err := net.ListenUDP("udp", udpAddr)
	checkError(err)

	for {
		handleClient(conn)
	}

	os.Exit(0)
}

func handleClient(conn *net.UDPConn) {
	var buf [512]byte

	_, addr, err := conn.ReadFromUDP(buf[0:])
	checkError(err)

	daytime := time.Now().String()

	conn.WriteToUDP([]byte(daytime), addr)
}

func checkError(err error) {
	if err != nil {
		fmt.Fprintf(os.Stderr, "Fatal Error: %s", err.Error())
		os.Exit(1)
	}
}