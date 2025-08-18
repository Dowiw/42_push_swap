#include "ft_push_swap.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void testing_b(t_stack **stack_a, t_stack **stack_b);
void testing_a(t_stack **stack_a, t_stack **stack_b);

int main() {
	char *one_line[] = {"./a.out", "12 5 19 3 8 1 14 7 2 9 15 6 0 18 4 11 13 10 16 17", NULL};
	char *mult_line[] = {"./a.out", "-300", "-300", "-500", NULL};
	printf("[Arg] one_line: %i\n", are_valid_args(one_line));
	printf("[Args] mult line: %i\n", are_valid_args(mult_line));

	// check stack filler
	t_stack *stack_a;
	stack_a = NULL;
	int ac = 0;
	while (one_line[ac] != NULL)
		ac++;
	printf("[Count] number of nums (ac) for one line: %i\n", ac);

	printf("[Fill] Calling fill_stack_a for one line\n");
	fill_stack_a(&stack_a, ac, one_line);
	printf("[OK] Returned from fill_stack_a for one line\n");

	t_stack *cursor = stack_a;
	t_stack *stack_b = NULL;
	printf("[Print] Printing stack content\n");
	printf("Stack A: ");
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");
	cursor = stack_b;
	printf("Stack B: ");
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");
	testing_b(&stack_a, &stack_b);
	testing_a(&stack_a, &stack_b);

	printf("\n[Free] Freeing stack one_line\n");
	t_stack *temp = stack_a;
	while (temp)
	{
		temp = (stack_a)->next;
		free(stack_a);
		stack_a = temp;
	}
	printf("[OK] Stack one line freed\n");

	t_stack *stack2 = NULL;
	int argc = 0;
	while (mult_line[argc] != NULL)
		argc++;
	printf("number of nums in multiple line: %i\n", argc);

	printf("Calling fill_stack_a for mult line\n");
	fill_stack_a(&stack2, argc, mult_line);
	printf("Returned from fill_stack_a for mult line\n");

	cursor = stack2;
	int counter = 0;
	while (cursor != NULL)
	{
		printf("stack mult num: %i\n", cursor->number);
		cursor = cursor->next;
		counter++;
		if (counter > 100) break ;
	}
	// free everything
	// int i = 0;
	// while (test[i] != NULL)
	// {
	// 	free(split[i]);
	// 	i++;
	// }
	// free(split);
	error_free_exit(&stack_a, &stack2);
	return (0);
}

void testing_b(t_stack **stack_a, t_stack **stack_b)
{
	t_stack *cursor;
	printf("[Test MOVES in b] Testing moves\n");
	printf("\nMove: ");	do_pb(stack_a, stack_b);
	printf("[Print] Printing stack content\n");
	printf("Stack A: ");
	cursor = *stack_a;
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");
	cursor = *stack_b;
	printf("Stack B: ");
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");

	printf("\nMove: ");	do_pb(stack_a, stack_b);
	printf("[Print] Printing stack content\n");
	printf("Stack A: ");
	cursor = *stack_a;
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");
	cursor = *stack_b;
	printf("Stack B: ");
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");

	printf("\nMove: ");	do_sb(stack_b);
	printf("[Print] Printing stack content\n");
	printf("Stack A: ");
	cursor = *stack_a;
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");
	cursor = *stack_b;
	printf("Stack B: ");
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");

	printf("\nMove: ");	do_pb(stack_a, stack_b);
	printf("[Print] Printing stack content\n");
	printf("Stack A: ");
	cursor = *stack_a;
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");
	cursor = *stack_b;
	printf("Stack B: ");
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");

	printf("\nMove: ");	do_rb(stack_b);
	printf("[Print] Printing stack content\n");
	printf("Stack A: ");
	cursor = *stack_a;
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");
	cursor = *stack_b;
	printf("Stack B: ");
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");

	printf("\nMove: ");
	do_rrb(stack_b);
	printf("[Print] Printing stack content\n");
	printf("Stack A: ");
	cursor = *stack_a;
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");
	cursor = *stack_b;
	printf("Stack B: ");
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");
}

void testing_a(t_stack **stack_a, t_stack **stack_b)
{
	t_stack *cursor;
	printf("[Test MOVES in a] Testing moves\n");
	printf("\nMove: ");	do_pa(stack_b, stack_a);
	printf("[Print] Printing stack content\n");
	printf("Stack A: ");
	cursor = *stack_a;
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");
	cursor = *stack_b;
	printf("Stack B: ");
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");

	printf("\nMove: ");	do_pa(stack_b, stack_a);
	printf("[Print] Printing stack content\n");
	printf("Stack A: ");
	cursor = *stack_a;
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");
	cursor = *stack_b;
	printf("Stack B: ");
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");

	printf("\nMove: ");	do_pa(stack_b, stack_a);
	printf("[Print] Printing stack content\n");
	printf("Stack A: ");
	cursor = *stack_a;
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");
	cursor = *stack_b;
	printf("Stack B: ");
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");

	printf("\nMove: ");	do_sa(stack_a);
	printf("[Print] Printing stack content\n");
	printf("Stack A: ");
	cursor = *stack_a;
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");
	cursor = *stack_b;
	printf("Stack B: ");
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");

	printf("\nMove: ");	do_ra(stack_a);
	printf("[Print] Printing stack content\n");
	printf("Stack A: ");
	cursor = *stack_a;
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");
	cursor = *stack_b;
	printf("Stack B: ");
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");

	printf("\nMove: ");
	do_rra(stack_a);
	printf("[Print] Printing stack content\n");
	printf("Stack A: ");
	cursor = *stack_a;
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");
	cursor = *stack_b;
	printf("Stack B: ");
	while (cursor != NULL)
	{
		printf("%i, ", cursor->number);
		cursor = cursor->next;
	}
	printf("\n");
}

// int main(int ac, char **av)
// {
// 	t_stack	*stack_a;
// 	t_stack	*stack_b;

// 	if (ac < 2)
// 		return (0);
// 	else if (!are_valid_args(av))
// 		error_free_exit(NULL, NULL);
// 	fill_stack_a(&stack_a, ac, av);
// 	stack_b = NULL;
// 	do_push_swap(&stack_a, &stack_b);

// 	t_stack *cursor = stack_a;
// 	while (cursor != NULL)
// 	{
// 		printf("num: %i\n", cursor->number);
// 		cursor = cursor->next;
// 	}
// }
