package main

import "fmt"

const englishPrefix = "Hello, "
const freashHelloPrefix = "Bonjour, "
const spanishHelloPrefix = "Hola, "
const french = "French"
const spanish = "Spanish"

func Hello(name string, language string) string {
	if name == "" {
		name = "World"
	}

	return helloPrefix(language) + name
}

//prefix string 命名返回值
//私有函数以小写字母开头
func helloPrefix(language string) (prefix string) {
	switch language {
	case french:
		prefix = freashHelloPrefix
	case spanish:
		prefix = spanishHelloPrefix
	default:
		prefix = englishPrefix
	}
	return
}


func main()  {
	fmt.Println("Hello")
}
