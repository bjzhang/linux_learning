package main

import "fmt"
import "os"
import "strings"

func lengthOfLongestSubstring(s string) int {
	if len(s) == 1 {
		return 1
	}
	lastMax := 0
	lastMaxString := ""
	for i := 0; i < len(s); i++ {
		curMax := 1
		curMaxString := ""
		for j := i + 1; j < len(s); j++ {
			if strings.Contains(s[i:j], s[j:j+1]) {
				curMax = j - i
				curMaxString = s[i:j]
				break
			} else if j == len(s)-1 {
				curMax = j - i + 1
				curMaxString = s[i : j+1]
			}
		}
		if curMax > lastMax {
			lastMax = curMax
			lastMaxString = curMaxString
		}
	}
	fmt.Printf("max string %s, %d\n", lastMaxString, lastMax)
	return len(lastMaxString)
}

func main() {
	lengthOfLongestSubstring(os.Args[1])

}
