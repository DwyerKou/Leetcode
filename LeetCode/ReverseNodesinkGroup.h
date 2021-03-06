/*
Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5
*/
#pragma once
#include "LeetCode.h"
class ReverseNodesinkGroup
{
public:
	/*
	感觉这个题就是看会不会做，时间复杂度就是nk了，没法搞到lgn
	这个方法不好 我放弃了
	想到一个递归的方法
	肯定可以大大简化代码量
	直接别看这里看下面的另一个函数！！！！！！！！！！！！！失败
	*/
	ListNode* reverseKGroup_DwyerBad(ListNode* head, int k) {
		if (!head || k < 2) return head;
		ListNode* pre = head, *temp, *realHead = head;
		head = head->next;
		bool theFirstHead = true;
		ListNode* prepre = pre, *preprepre;
		while (head) {
			int i = k - 1;
			ListNode* headBackupThisCycle = pre;
			while (i&&head) {
				temp = head->next;
				head->next = pre;
				pre = head;
				head = temp;
				i--;
			}
			if (i == 0) {//刚好符合情况，让第一个节点指向下一个节点就行了，下一个为空也可以
				if (theFirstHead) {
					realHead = pre;
					theFirstHead = false;
				}
				if (head) {// 如果head还没指到空
					//让上一次最后一个指向下一次第一个
					preprepre = prepre;
					prepre->next = head;
					prepre = head;
					//将pre和head后移为下一次的反转做准备
					pre = head;
					head = head->next;
					headBackupThisCycle->next = pre;
				}
				else {
					headBackupThisCycle->next = nullptr;
					preprepre->next = pre;
				}
			}
			else {//说明k越界了应该再把最后一次的给反过来
				ListNode* a = pre;
				head = pre->next;
				while (i++ != k - 1) {
					temp = head->next;
					head->next = pre;
					pre = head;
					head = temp;
				}
				a->next = nullptr;
				break;
			}
		}
		return realHead;
	}

	/*
	递归用起来
	草！！！！！用递归瞬间搞定啊！！！！！！！！
	而且是最快的24ms
	*/
	ListNode* reverseKGroup(ListNode* head, int k) {
		if (!head || k < 2) return head;
		ListNode* headBackup = head, *temp;
		//判断k比链表长的情况
		for (int i = k - 1;i > 0;--i) {
			head = head->next;
			if (!head)
				return headBackup;
		}
		head = headBackup;
		ListNode *pre = head, *prepre = head;
		head = head->next;
		int i = k - 1;
		while (i) {
			--i;
			temp = head->next;
			head->next = pre;
			pre = head;
			head = temp;
		}
		prepre->next = reverseKGroup(head,k);
		return pre;
	}
};

