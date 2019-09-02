package sum

import "testing"

func TestSum(t *testing.T) {

	t.Run("collection of 5 numbers", func(t *testing.T) {
		//数组有个有趣的属性，它的大小也属于类型的一部分,[4]int和[5]int是不同的
		numbers := []int{1, 2, 3, 4, 5}

		got := Sum(numbers)
		want := 15

		if want != got {
			t.Errorf("want '%d' got '%d', %v", want, got, numbers)
		}
	})

	t.Run("collection of any size", func(t *testing.T) {
		numbers := []int{1,2,3}

		got := Sum(numbers)
		want := 6

		if want != got {
			t.Errorf("want '%d' got '%d', %v", want, got, numbers)
		}

	})
}