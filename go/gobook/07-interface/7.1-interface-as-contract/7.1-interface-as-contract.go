package fmt

import (
	"bytes"
	"io"
	"os"
)

/*
package io

//Writer is the inteface that wraps the basic Write method.
type Writer interface {
	Write(p []byte) (n int, err error)
}
*/
//The first parameter of Fprintf is not a file either. It's an io.Writer, which is an interface type with following declaration
func Fprintf(w io.Writer, format string, args ...interface{}) (int, error)

func Printf(format string, args ...interface{}) (int, error) {
	return Fprintf(os.Stdout, format, args...)
}

func Sprintf(format string, args ...interface{}) string {
	var buf bytes.Buffer
	Fprintf(&buf, format, args...)
	return buf.String()
}
