package main

import (
	"fmt"
	"net/http"
	"strings"
	"log"
)

func sayHelloName(w http.ResponseWriter, r *http.Request) {
	log.Println("sayHelloName")
	//r.ParseForm()
	log.Println(r.Form)
	log.Println("path:", r.URL.Path)
	log.Println("scheme:", r.URL.Scheme)
	log.Println(r.Form["url_long"])
	for k, v := range r.Form {
		log.Println("key:", k)
		log.Println("val:", strings.Join(v,""))
	}
	fmt.Fprint(w, "hello faterer")
}

func main() {
	http.HandleFunc("/", sayHelloName)
	
	log.Println("Listening on http://localhost:9090/")
	err := http.ListenAndServe(":9090", nil)
	if err != nil {
		log.Fatal("ListenAndServe:", err)
	}
}