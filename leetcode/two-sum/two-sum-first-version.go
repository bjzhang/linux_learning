package main

// https://leetcode.com/articles/two-sum/

import "fmt"

func twoSum(nums []int, target int) []int {
	var result = make([]int, 2)
	for i := 0; i < len(nums); i++ {
		for j := 0; j < len(nums); j++ {
			if i == j {
				continue
			}
			if target == nums[i]+nums[j] {
				result[0] = i
				result[1] = j
				return result
			}
		}
	}
	return result
}

func main() {
	tests := []int{1, 2, 4, 8, 16}
	results := twoSum(tests, 9)
	fmt.Println(results)
}
