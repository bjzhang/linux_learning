package main

import "fmt"
import "os"

func lengthOfLongestSubstring(s string) int {
	if len(s) == 1 {
		return 1
	}
	for i := 0; i < len(s); i++ {
		fmt.Printf("outter loop: %d: %c\n", i, s[i])
		lastChar := s[i]
		curMax := 1
		for j := i + 1; j < len(s); j++ {
			fmt.Printf("inner loop: %d: %c(last char: %c)\n", j, s[j], lastChar)
			fmt.Printf("current string: %s\n", s[i:j+1])
			if s[j] == lastChar {
				curMax = j - i
				fmt.Printf("CURRENT max length string: %d, %s\n", curMax, s[i:j])
				break
			} else if j == len(s)-1 {
				curMax = j - i + 1
				fmt.Printf("CURRENT max length string: %d, %s\n", curMax, s[i:j+1])
			}
			lastChar = s[j]
		}
	}
	return 1
}

func main() {
	lengthOfLongestSubstring(os.Args[1])
}
