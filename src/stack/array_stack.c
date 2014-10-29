/*----------------------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                            -*/
/*-DATE:        07102014                                                     -*/
/*-WHAT:        Basic data structure                                         -*/
/*-REVISION:                                                                 -*/
/*- DATE -------------------- DESCRIPTION ------------------------------------*/
/*- 07102014    Basic Stack in Array Implement.                              -*/
/*----------------------------------------------------------------------------*/
struct array_stack *
create_array_stack_space(void)
{
  struct array_stack *base_ptr;
  ENTER("init_array_stack_space");

  malloc_initial((void**)&base_ptr, sizeof(*base_ptr));
  base_ptr->size = STACK_SIZE_DEFAULT;
  base_ptr->rest = STACK_SIZE_DEFAULT;

  malloc_initial((void**)&base_ptr->loc.bp, sizeof(base_ptr->loc.bp) *
    base_ptr->size);
  base_ptr->loc.sp = (void**)base_ptr->loc.bp;

  LEAVE;
  return base_ptr;
}

void
destroy_array_stack_space(struct array_stack **stack)
{
  ENTER("destroy_array_stack_space");

  saft_free((void**)&(*stack)->loc.bp);
  saft_free((void**)stack);

  LEAVE;
  return;
}

void
expand_array_stack_space(struct array_stack *stack, unsigned extra)
{
  unsigned new_size;
  ENTER("expand_array_stack_space");

  if(0 == extra)
    new_size = stack->size * 2 + STACK_SIZE_MIN;
  else
    new_size = stack->size + extra;

  realloc_noinitial((void**)&stack->loc.bp, sizeof(stack->loc.bp) * new_size);
  stack->rest += new_size - stack->size;
  stack->size = new_size;

  LEAVE;
  return;
}

int
is_array_stack_full(struct array_stack *stack)
{
  int issfull;
  ENTER("is_array_stack_full");

  issfull = 0;
  if(!rest_space_of_array_stack(stack))
    issfull = 1;

  LEAVE;
  return issfull;
}

unsigned
rest_space_of_array_stack(struct array_stack *stack)
{
  unsigned rest;
  ENTER("rest_space_of_array_stack");

  rest = stack->rest;

  LEAVE;
  return rest;
}

void
push_array_stack(struct array_stack *stack, void *member)
{
  ENTER("push_array_stack");

  if(NULL == member)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_PUSH;
  }

  if(is_array_stack_full(stack))
    expand_array_stack_space(stack, STACK_SIZE_MIN);

  *stack->loc.sp++ = member;
  stack->rest--;

END_OF_PUSH:
  LEAVE;
  return;
}

void *
pop_array_stack(struct array_stack *stack)
{
  void *data;
  ENTER("pop_array_stack");

  data = NULL;
  if(!is_empty_array_stack(stack))
  {
    data = *(--stack->loc.sp);
    stack->rest++;
  }

  LEAVE;
  return data;
}

int
is_empty_array_stack(struct array_stack *stack)
{
  int isempty;
  ENTER("is_empty_array_stack");

  isempty = stack->rest == stack->size ? 1 : 0;

  LEAVE;
  return isempty;
}

void
cleanup_array_stack(struct array_stack *stack)
{
  ENTER("cleanup_array_stack");

  memset(stack->loc.bp, 0, sizeof(stack->loc.bp) * stack->size);
  stack->loc.sp = (void**)stack->loc.bp;
  stack->rest = stack->size;

  LEAVE;
  return;
}

void
traverse_array_stack(struct array_stack *stack, void (*operation)(void *))
{
  register void **iter;
  ENTER("traverse_array_stack");

  if(NULL == operation)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_TRAVERSE;
  }

  iter = (void**)stack->loc.bp;
  while(iter != stack->loc.sp)
    operation(*iter++);

END_OF_TRAVERSE:
  LEAVE;
  return;
}
