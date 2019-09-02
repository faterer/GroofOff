package iteration


func Repeat(character string) string {
	var repeat string

	for i := 0; i < 5; i++ {
		repeat += character
	}

	return repeat
}