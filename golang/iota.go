
package main

import (
    "fmt"
)

const (
    deleteItem = iota
    setItem  // = iota // the second iota could be skipped.
)

func main() {
	fmt.Println("deleteItem: ", deleteItem)
	fmt.Println("setItem: ", setItem)
	return
}
