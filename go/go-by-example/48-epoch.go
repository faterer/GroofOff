package main

import "time"
import "fmt"

//A common requirement in programs is getting the number of seconds, milliseconds, or nanoseconds since the Unix epoch. Here’s how to do it in Go.
func main() {
	//Use time.Now with Unix or UnixNano to get elapsed time since the Unix epoch in seconds or nanoseconds, respectively.
	now := time.Now()
    secs := now.Unix()
    nanos := now.UnixNano()
    fmt.Println(now.UTC())
	//Note that there is no UnixMillis, so to get the milliseconds since epoch you’ll need to manually divide from nanoseconds.
	//	秒			微妙			毫秒					纳秒						皮秒
	//1 sec=1 000 milisec=1 000 000 microsec=1 000 000 000 nanosec = 1 000 000 000 000 picosecond
	millis := nanos / 1000000
	micros := nanos / 1000
    fmt.Println(secs)
	fmt.Println(millis)
	fmt.Println(micros)
	fmt.Println(nanos)
	//You can also convert integer seconds or nanoseconds since the epoch into the corresponding time.
	fmt.Println(time.Unix(secs, 0))
    fmt.Println(time.Unix(0, nanos))
}
// 0.5 nanoseconds – the half-life of beryllium-13.
// 0.96 nanoseconds – 100 Gigabit Ethernet Interpacket gap
// 1.0 nanosecond – cycle time of an electromagnetic wave with a frequency of 1 GHz (1×109 hertz).
// 1.0 nanosecond – electromagnetic wavelength of 1 light-nanosecond. Equivalent to 0.3m radio band.

// 1 picosecond – half-life of a bottom quark
// 10 picoseconds after the Big Bang – electromagnetism separates from the other fundamental forces