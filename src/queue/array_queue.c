struct array_queue *
array_queue_create(void)
{
    struct array_queue *queue;

    queue = malloc_ds(sizeof(*queue));
    if (!queue) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        queue->sid = 0u;
    }

    queue->space.queue = malloc_ds(sizeof(void *) * DEFAULT_QUEUE_SPACE_SIZE);
    if (!queue->space.queue) {
        free_ds(queue);
        pr_log_err("Fail to get memory from system.\n");
    } else {
        queue->space.front = queue->space.base;
        queue->space.rear = queue->space.base;
    }

    return queue;
}

void
array_queue_destroy(struct array_queue **queue)
{
    if(queue && *queue) {
    {
        free_ds((*queue)->space.base);
        free_ds(*queue);
        *queue = NULL;
    }

    return;
}

void
array_queue_expand_space(struct array_queue *queue, uint32 extra)
{
    uint32 new_size;
    void **new_addr;

    new_size = 0;
    if (queue && extra) {
        new_size = array_queue_capacity(queue) + size;
    } else if (queue && !extra) {
        new_size = array_queue_capacity(queue) * 2 + EXPAND_QUEUE_SPACE_MIN;
    }

    if (new_size) {
        new_addr = realloc_ds(queue->space.base, sizeof(void *) * new_size);
        if (!new_addr) {
            pr_log_err("Fail to get memory from system.\n");
        } else {
            queue->space.base = new_addr;
        }
    }

    if(queue->front == queue->rear)
    {
      old = queue->front;
      new = queue->front + new_size - queue->size;
      while(old < (void**)queue->queue + queue->size)
        *new++ = *old++;
    }
    queue->rest = new_size - queue->size;
    queue->size = new_size;

    return;
}

uint32
array_queue_capacity(struct array_queue *queue)
{
    return queue ? queue->space.dim : 0u;
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
