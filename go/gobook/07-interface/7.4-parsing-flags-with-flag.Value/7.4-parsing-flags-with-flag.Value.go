package flag

//Value is an interface to the value stored in 	a flag.	
type Value interface {
	String() string
	Set(string) error
}