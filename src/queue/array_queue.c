/*----------------------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                            -*/
/*-DATE:        08042014                                                     -*/
/*-WHAT:        Baisc Data Structure                                         -*/
/*-REVISION:                                                                 -*/
/*- DATE -------------------- DESCRIPTION ------------------------------------*/
/*- 08042014    Queue of Array Implement.                                    -*/
/*----------------------------------------------------------------------------*/
struct array_queue *
create_array_queue_instance(void)
{
  struct array_queue *result;
  ENTER("create_array_queue_instance");

  malloc_initial((void**)&result, sizeof(*result));
  result->size = DEFAULT_QUEUE_SIZE;
  result->rest = DEFAULT_QUEUE_SIZE;

  malloc_initial((void**)&result->queue, sizeof(result->queue) * DEFAULT_QUEUE_SIZE);
  result->front = (void**)result->queue;
  result->rear = (void**)result->queue;

  LEAVE;
  return result;
}

void
destroy_array_queue_instance(struct array_queue **queue)
{
  ENTER("destroy_josephus_game_serial_node");

  if(NULL == *queue || NULL == queue)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_DESTROY;
  }

  saft_free((void**)&(*queue)->queue);
  saft_free((void**)queue);

END_OF_DESTROY:
  LEAVE;
  return;
}

void
expand_array_queue(struct array_queue *queue, unsigned size)
{
  unsigned new_size;
  void **old, **new;
  ENTER("expand_array_queue");

  if(NULL == queue)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_EXPAND;
  }

  if(size)
    new_size = queue->size + size;
  else
    new_size = queue->size * 2 + DEFAULT_QUEUE_SIZE;

  old = new = NULL;
  realloc_initial((void**)&queue->queue, sizeof(queue->queue) * new_size);
  if(queue->front == queue->rear)
  {
    old = queue->front;
    new = queue->front + new_size - queue->size;
    while(old < (void**)queue->queue + queue->size)
      *new++ = *old++;
  }
  queue->rest = new_size - queue->size;
  queue->size = new_size;

END_OF_EXPAND:
  LEAVE;
  return;
}

void
enter_array_queue(struct array_queue *queue, void *member)
{
  ENTER("enter_array_queue");

  if(NULL == queue)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_ENTER;
  }

  if(is_full_array_queue(queue))
    expand_array_queue(queue, 0);

  //IF rear point to last element of array
  if(queue->rear == (void**)queue->queue + queue->size - 1)
  {
    *queue->rear = member;
    queue->rear = (void**)queue->queue;
  }
  else
    *queue->rear++ = member;

  queue->rest--;

END_OF_ENTER:
  LEAVE;
  return;
}

void *
leave_array_queue(struct array_queue *queue)
{
  void *result;
  ENTER("leave_array_queue");

  if(NULL == queue)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_LEAVE;
  }

  result = NULL;
  if(is_empty_array_queue(queue))
    goto END_OF_LEAVE;

  if(queue->front == (void**)queue->queue + queue->size - 1)
  {
    result = *queue->front;
    queue->front = (void**)queue->queue;
  }
  else
    result = *queue->front++;

  queue->rest++;

END_OF_LEAVE:
  LEAVE;
  return result;
}

void
clear_array_queue(struct array_queue *queue)
{
  ENTER("clear_array_queue");

  if(NULL == queue)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_CLEAR;
  }

  memset(queue->queue, 0, sizeof(queue->queue) * queue->size);
  queue->rest = queue->size;
  queue->front = (void**)queue->queue;
  queue->rear = (void**)queue->queue;

END_OF_CLEAR:
  LEAVE;
  return;
}

void
traverse_array_queue(struct array_queue *queue, void (*op)(void *))
{
  void **st, **bound;
  ENTER("traverse_array_queue");

  if(NULL == queue)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_TRAVERSE;
  }

  bound = (void**)queue->queue + queue->size - 1;
  st = queue->front;
  while(st != queue->rear)
  {
    (*op)(*st);
    if(st == bound)
      st = (void**)queue->queue;
    else
      st++;
  }

END_OF_TRAVERSE:
  LEAVE;
  return;
}

int
is_empty_array_queue(struct array_queue *queue)
{
  int is_empty;
  ENTER("is_empty_array_queue");

  if(NULL == queue)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_EMPTY;
  }

  is_empty = queue->rest == queue->size ? 1 : 0;

END_OF_EMPTY:
  LEAVE;
  return is_empty;
}


int
is_full_array_queue(struct array_queue *queue)
{
  int is_full;
  ENTER("is_full_array_queue");

  if(NULL == queue)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_FULL;
  }

  is_full = queue->rest == 0 ? 1 : 0;

END_OF_FULL:
  LEAVE;
  return is_full;
}
