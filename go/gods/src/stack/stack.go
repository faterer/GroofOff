package stack

import (
	"container/list"
)

type Stack struct {
	l *list.List
}

func New() *Stack {
	return &Stack{l: list.New()}
}

func (s *Stack) Push(v interface{}) {
	s.l.PushBack(v)
}

func (s *Stack) Top() interface{} {
	return s.l.Back().Value
}

func (s *Stack) Pop() interface{} {
	return s.l.Remove(s.l.Back())
}

func (s *Stack) Len() int {
	return s.l.Len()
}

func (s *Stack) IsEmpty() bool {
	return s.l.Len() == 0
}