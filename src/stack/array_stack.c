/*
 * _RETURN_ one instance of array_stack.
 *   If no memory available, it never _RETURN_, export an error and exit.
 */
struct array_stack *
array_stack_create_space(void)
{
    struct array_stack *ptr;

    ptr = (struct array_stack *)malloc_ds(sizeof(*ptr));
    if (!ptr) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        ptr->size = DEFAULT_STACK_SPACE_SIZE;
        ptr->rest = DEFAULT_STACK_SPACE_SIZE;
    }

    ptr->loc.bp = malloc_ds(sizeof(ptr->loc.bp) * DEFAULT_STACK_SPACE_SIZE);
    if (!ptr->loc.bp) {
        free_ds(ptr);
        pr_log_err("Fail to get memory from system.\n");
    } else {
        ptr->loc.sp = (void **)ptr->loc.bp;
    }

    return ptr;
}

/*
 * Destroy the instance of array stack.
 *   If NULL _ARGV_, nothing will be done.
 */
void
destroy_array_stack_space(struct array_stack **stack)
{
    if (stack && *stack) {
        free_ds((*stack)->loc.bp);
        free_ds(*stack);
        *stack = NULL;
    }

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
