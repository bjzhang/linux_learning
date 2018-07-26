package main

//https://leetcode.com/problems/add-two-numbers/description/

import "fmt"

func printList(l *ListNode) {
	fmt.Printf("Current list: ")
	for {
		if l != nil {
			fmt.Printf("%d ", l.Val)
		}
		if l.Next != nil {
			l = l.Next
		} else {
			break
		}
	}
	fmt.Printf("\n")
}

/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {
	var result *ListNode = new(ListNode)
	var latestResult = result
	var carry int = 0
	/*
	   defer func() {
	       if r := recover(); r != nil {
	           fmt.Println("Recovered in f", r)
	           latestResult.Val = carry
	       }
	   }()
	*/
	for {
		latestResult.Val = (l1.Val + l2.Val + carry) % 10
		carry = (l1.Val + l2.Val + carry) / 10
		fmt.Println(carry, latestResult.Val)
		printList(result)
		if l1.Next != nil && l2.Next != nil {
			l1 = l1.Next
			l2 = l2.Next
		} else {
			break
		}
		latestResult.Next = new(ListNode)
		latestResult = latestResult.Next
	}
	if l1.Next != nil {
		latestResult.Next = new(ListNode)
		latestResult = latestResult.Next
		l1 = l1.Next
		for {
			latestResult.Val = (l1.Val + carry) % 10
			carry = (l1.Val + carry) / 10
			fmt.Println(latestResult.Val, carry)
			printList(result)
			if l1.Next != nil {
				l1 = l1.Next
			} else {
				break
			}
			latestResult.Next = new(ListNode)
			latestResult = latestResult.Next
		}
	}
	if l2.Next != nil {
		latestResult.Next = new(ListNode)
		latestResult = latestResult.Next
		l2 = l2.Next
		for {
			latestResult.Val = (l2.Val + carry) % 10
			carry = (l2.Val + carry) / 10
			fmt.Println(latestResult.Val, carry)
			printList(result)
			if l2.Next != nil {
				l2 = l2.Next
			} else {
				break
			}
			latestResult.Next = new(ListNode)
			latestResult = latestResult.Next
		}
	}
	if carry != 0 {
		latestResult.Next = new(ListNode)
		latestResult = latestResult.Next
		latestResult.Val = carry
	}
	return result
}
