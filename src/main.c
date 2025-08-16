#include "ft_push_swap.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
	char *one_line[] = {"./a.out", "1 2 3 4 5 6 7 8 9 10", NULL};
	char *mult_line[] = {"./a.out", "-300", "-300", "-500", NULL};
	printf("one_line: %i\n", are_valid_args(one_line));
	printf("mult line: %i\n", are_valid_args(mult_line));

	// check stack filler
	t_stack *stack;
	stack = NULL;
	int ac = 0;
	while (one_line[ac] != NULL)
		ac++;
	printf("number of nums (ac) for one line: %i\n", ac);

	printf("Calling fill_stack_a for one line\n");
	fill_stack_a(&stack, ac, one_line);
	printf("Returned from fill_stack_a for one line\n");

	t_stack *cursor = stack;
	int count = 0; // debug for infinite loop
	while (cursor != NULL)
	{
		printf("stack num: %i\n", cursor->number);
		cursor = cursor->next;
		count++;
		if (count > 100) break ;
	}

	printf("Freeing stack one_line\n");
	t_stack *temp = stack;
	while (temp)
	{
		temp = (stack)->next;
		free(stack);
		stack = temp;
	}
	printf("Stack one line freed\n");

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
	error_free_exit(&stack, &stack2);
	return (0);
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
