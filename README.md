# Data Structure and Algoritm 2019

These are homeworks and excercises in class.

## Link
- [hw1](#hw1)
- [hw2](#hw2)
- [hw3](#hw3)
- [hw4](#hw4)
- [hw5](#hw5)

## Each homework instruction
### hw1
#### Problem definition
Given a sequence of integers, your program should identify the K-th smallest number in a running window of M integers.

#### Input format
- Line#1: Three integers N, M, K, seperated by space.
  - N is the total length of the input sequence (1<=N<=200000).
  - M is the size of the running window (1<=M<=100000, M<=N)
  - K is the interger such that your program can find the the K-th smallest integer in a running window (1<=K<=M)
- Line#2: A sequence of N integers a1, a2,... , an, (1<=ai<=2147483647)

#### Output format
- When the running window is moving from left to right, output the K-th smallest integer in one line. The first running window should contain the first M elements of the sequence. Eventually there should be N-M+1 output, with each output in a line.
-----
### hw2
#### Problem definition
- The length of the longest common prefix of two strings A[0..m) and B[0..n), denoted by lcp(A,B), is the largest integer k≤min{m,n} such that A[0..k)=B[0..k). In this homework, we need to build a data structure that can compute LCP efficiently.

- First of all, we need to construct a large set of strings, as follows.

- We define that the 0'th string is a empty string.
- For the i'th string, it is one of previous strings (The p'th string where 0≤p<i) with a lower case English letter appended to it.
- For example:
  - The first string is “a”, which is the 0'th string with ‘a’ appended to it.
  - The second string is “ab” , which is the first string with ‘b’ appended to it.
  - The third string is “abc”, which is the second string with ‘c’ appended to it.
  - The forth string is “abd”, which is the second string with ‘d’ appended to it.
  - Then you have to answer q questions. For every question, you are given two positive integers i, j , please output the lcp( i'th string, j'th string ) in a line.
#### Input format

- The first line contain a single integer n , which denotes the number of strings.
For the next n line, the i'th line decribes the i'th string. In i'th line , there’re a integer l and a character c, which means that the i'th string is the l'th string with c appended to it.
- The next line contain a single integer q, which denotes the number of questions.
In each of next q line, there’re two integer i, j , which means that you are asked to output the lcp( i'th string, j'th string ).

#### Output format

- For each question, output the anser of it in a line.
---
### hw3
#### Problem definition
- Alice and Bob are playing a simple poker game with the following rules:

- Each player gets n cards from the deck, and all the cards are open to both players.

- Alice moves first, and then they take turns to play cards.
- At each move, the current player can only play a card that has the same suit or number as the previous one.

- A player can pass if and only if there is no suitable card in his/her hand.

- When a player passes, the next player can play any card in his/her hand.

- The game stops when one of the players has no more card in his/her hand.

- When the game ends, the loser still has some cards at hand, and the total points of these cards indicate how much the loser needs to pay the winner. (A card's points are defined by its number, as explain below.)

- During the game, the winner wants to maximize the points of the loser's remaining cards, while the loser want to minimize it. Your mission is to design a stragegy for both players to play optimally, and find out who is the winner and the remaining points of the loser.

- A card can be denoted by its suit and number:

  - A suit can be represented by C (club), D (diamond), H (heart), and S (spade).
  - A number can be represented by A, 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K.
  - Therefore a card can be represented by a two-character string, such as "DT" (diamond 10) or "SA" (spade A), etc.

  - Note that a card's points are denoted by its number, such that A==>1, 2==>2, 3==>3, ..., 9==>9, T==>10, J==>11, Q==>12, K==>13.

#### Input format

- Line 1 is a single integer n (n≤17), which is the number of cards for each player initially.
- Line 2 lists Alice's cards with n distinct space-separated two-characters string
- Line 3 lists Bob's cards similarly.
#### Output format
- Line 1 is the winner, "Alice" or "Bob", without quotes.
- Line 2 is the total remaining points of the loser.

---
### hw4

#### Problem definition
- You are given a string 𝑠 and an integer 𝑚, your task is to solve two problems:

- Find a longest string 𝑡, so that 𝑡 is a substring of 𝑠, and appears at least 𝑚 times in 𝑠. The definition of substring is a sequence of consecutive characters in a string.
  - For example, 𝑠=𝑏𝑎𝑎𝑎𝑎𝑏𝑎𝑏𝑎𝑏𝑎𝑏𝑏𝑎𝑏𝑎𝑏𝑏𝑎𝑏, 𝑚=3, then the answer would be 𝑏𝑎𝑏𝑎𝑏, since there is no other substring of 𝑠 is longer than 𝑏𝑎𝑏𝑎𝑏 and appears at least 3 times in string 𝑠.

- Find a longest string 𝑟, such that 𝑟 is a prefix of 𝑠 and a suffix of 𝑠. In other words, 𝑟 is the beginning of the string 𝑠 and the end of the string 𝑠. To make it more challenging, string 𝑟 also need to be able to be located somewhere inside the string 𝑠, that is, it is neither beginning, nor its end.
  - For example, 𝑠=𝑎𝑏𝑐𝑑𝑎𝑏𝑐𝑎𝑏𝑐, the answer is 𝑎𝑏𝑐, because it appears at positions 0 (prefix), 4 (neither prefix nor suffix), 7 (suffix), which meets the requirements.

#### Input Format

- The input contains several test cases. Each test case consists of a line with an integer 𝑚 (𝑚≥1), the minimum number of repetitions, followd by a line containing a string 𝑠. All characters in 𝑠 are lowercase characters from ‘a’ to ‘z’. The last test case is denoted by 𝑚=0 and must not be processed.

#### Output Format

- For each test case, you need to print two lines of answers:

- For problem 1, if there is no solution, output “none” without the quotes; otherwise, print two integers in a line, separated by a space. The first integer denotes the maximum length of a substring appearing at least 𝑚 times; the second integer is the right most possible starting position of such a substring.

- For problem 2, print the string that meets the requirements. If a suitable string does not exist, then print “Just a legend” without the quotes.
---

### hw5
#### Problem definition
- You have a graph paper of size N by M, each grid is either O or X.

- The action you can take is tearing it, and in each step, you can only choose one of two following operations to perform.

  - Select a piece of graph paper with more than one column and choose one of the columns filled with only O. Delete that column.

  - Select a piece of graph paper with more than one row and choose one of the rows filled with only O. Delete that row.

- You can perform the operations above on the graph paper as many times as you want.

- Note that after performing an operation, that piece of paper may become two pieces.

#### Input Format

- There are two integers 𝑁, 𝑀, which represent the size of the - graph paper in the first line.
The next 𝑁 lines contain 𝑀 characters each, which represents the graph paper.

#### Output Format

- Print the number of ways to tear the graph paper modulo 109+7.