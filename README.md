# 42_push_swap

A sorting algorithm project for the 42 curriculum. The hardest of its kind in Rank 2.

This project is a different kind of DSA problem. It does minutely focuses on time and space complexity but rather "move complexity".

**Task:** Given a sequence of random numbers in stack A, sort them using only an extra stack B and a limited set of stack operations.

**Bonus task:**
Implement a `checker` program.
This program reads a sequence of stack operations from standard input and applies them to the initial stack (provided as arguments).
At the end, it should output `OK` if the stack is sorted and `KO` otherwise.
`Error` for errors :-)

## Operations

| Command | Description                                                                                   |
|---------|----------------------------------------------------------------------------------------------|
| `sa`    | Swap the first 2 elements at the top of stack A.                                             |
| `sb`    | Swap the first 2 elements at the top of stack B.                                             |
| `ss`    | `sa` and `sb` at the same time.                                                              |
| `pa`    | Push the first element at the top of B to the top of A. (Do nothing if B is empty.)          |
| `pb`    | Push the first element at the top of A to the top of B. (Do nothing if A is empty.)          |
| `ra`    | Rotate A: shift up all elements of stack A by 1. First element becomes the last.             |
| `rb`    | Rotate B: shift up all elements of stack B by 1. First element becomes the last.             |
| `rr`    | `ra` and `rb` at the same time.                                                              |
| `rra`   | Reverse rotate A: shift down all elements of stack A by 1. Last element becomes the first.   |
| `rrb`   | Reverse rotate B: shift down all elements of stack B by 1. Last element becomes the first.   |
| `rrr`   | `rra` and `rrb` at the same time.                                                            |

## Usage

Tested with:
- GCC 10.5
- C17 standard
(May work on older versions.)

To compile `push_swap`:
```sh
make
```
*contains rules for all, bonus, clean, fclean, re*

To test:
```sh
ARG="$(shuf -i 0-100 -n 100 | paste -sd' ')"; ./push_swap $ARG | wc -l
ARG="$(shuf -i 0-100 -n 100 | paste -sd' ')"; ./push_swap $ARG | ./checker_linux $ARG
```
If you want the checker, you may use the compilable one from the `bonus` rule.

## Submodules

This project uses Git submodules for testing and visualizing, if interested.

**After cloning the repository, run:**
```sh
git submodule update --init --recursive
```
*follow instructions in respective repos*

## Results

![Demo Animation](resources/demo.gif)

The logic was largely based on jeongble and ayogun's approach to the problem.

When pushing to B, we want to retain the structure that looks like a "pac-man", where the smallest numbers are on the middle and biggest numbers on the side. Similar to jeongble's method.

Pushing back to A uses ayogun's turk of determining all the moves for every number in stack B where it takes the lowest moves while ensuring ascending order.

And then rotate the smallest number back to the top.

[Video on 500 to 1](resources/500to1.mp4)

## Huge thanks and references

The logic was formed based on ideas from:
- **jeongble (Jeongbin Lee)** for inspirational videos and logic
  - [Velog post](https://velog.io/@arat5724/42-pushswap-%EC%B5%9C%EC%A0%81%ED%99%94) (Super interesting post on reverse permutations)
  - [video on shuffled numbers](resources/jble3914.mp4) (these 2 videos helped a lot coding the logic myself)
  - [video on 500 to 1](resources/jble500-1.mp4)
- **ayogun (A. Yigit Ogun)** for his [blog on push_swap](https://medium.com/@ayogun/push-swap-c1f5d2d41e97) which inspired my `push_back_to_a` logic

Submodule/tester owners:
  - [gemartin's Push-Swap-Tester](https://github.com/gemartin99/Push-Swap-Tester.git)
  - [o-reo's push_swap_visualizer](https://github.com/o-reo/push_swap_visualizer.git)


Ideas on optimizations from:
- [Selbouka's easy algorithm](https://medium.com/@Selbouka/push-swap-easy-algorithm-56fd19bf2ee8)
- **Ulysse Gerkens** for the four stacks idea and references
  - [Medium post](https://medium.com/@ulysse.gks/push-swap-in-less-than-4200-operations-c292f034f6c0)
- **Fred** for a short video on his approach to push_swap on chunking
  - [Push_swap video](https://youtu.be/2aMrmWOgLvU?si=5XPfF8-8R1HwPuKO)

## Visualizer Note

The visualizer might not build with recent CMake versions due to warning flags.
Use:
```sh
cmake -Wno-dev
```
If you get an error in `pushswap.cpp` about `unique_ptr`, change line 17 to:
```cpp
std::unique_ptr<FILE, int(*)(FILE*)> pipe(popen(command.c_str(), "r"), static_cast<int(*)(FILE*)>(pclose));
```

---

Thanks to everyone who contributed ideas and resources on push_swap.

> Made in C
