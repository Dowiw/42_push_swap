#include <unistd.h>

void	do_sa(t_stack **stack_a)
{
	t_stack *temp;
	t_stack	*cursor;

	temp = *stack_a;
	cursor = *stack_a;
	cursor = cursor->next;
	cursor = temp;
	write(1, "sa\n", 3);
}
