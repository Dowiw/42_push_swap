void	small_sort(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*cursor;

	cursor = *stack_a;
	if (cursor->number < cursor->next->number)
		do_sa(stack_a);
}
