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
        queue->space.dim = DEFAULT_QUEUE_SPACE_SIZE;
        queue->space.rest = DEFAULT_QUEUE_SPACE_SIZE;
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
    uint32 old_size;
    uint32 new_size;
    void **new_addr;
    void *to;
    void *from;
    void *lmt;

    new_size = 0;
    if (!queue) { return; } else {
       old_size = array_queue_capacity(queue);
    }

    if (extra) {
        new_size = old_size + extra;
    } else {
        new_size = old_size * 2 + EXPAND_QUEUE_SPACE_MIN;
    }

    new_addr = realloc_ds(queue->space.base, sizeof(void *) * new_size);
    if (!new_addr) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        queue->space.base = new_addr;
        queue->space.dim = new_size;
        queue->space.rest += new_size - old_size;
    }

    /* No need to do if (queue->space.front < queue->space.rear) */
    if ((queue->space.front == queue->space.rear && array_queue_is_full(queue))
        || queue->space.front > queue->space.rear) {
        lmt = queue->space.front;
        to = queue->space.base + new_addr;
        from = queue->space.base + old_addr;
        while ((sint32)(lmt - from) < 0) {
            *(--to) == *(--from);
        }
    }
    return;
}

uint32
array_queue_capacity(struct array_queue *queue)
{
    return queue ? queue->space.dim : 0u;
}

/*
 * NULL array queue will _RETURN_ 0.
 */
uint32
array_queue_rest_space(struct array_queue *queue)
{
    return queue ? queue->space.rest : 0u;
}

/*
 * NULL array queue will be treated as full, _RETURN_ true.
 */
bool
array_queue_is_full(struct array_queue *queue)
{
    return 0u == array_queue_rest_space(queue) ? true : false;
}

/*
 * NULL array queue will be treated as full, _RETURN_ false.
 */
bool
array_queue_is_empty(struct array_queue *queue)
{
    bool is_empty;

    is_empty = false;
    if (queue) {
        is_empty = array_queue_capacity(queue) ==
            array_queue_rest_space(queue) ? true : false;
    }

    return is_empty;
}

void
array_queue_enter(struct array_queue *queue, void *member)
{
    if (queue && member) {
        if (array_queue_is_full(queue)) {
            array_queue_expand_space(queue);
        }

        *queue->space.rear++ = member;
        if (queue->space.rear == queue->space.base + array_queue_capacity(queue)) {
            queue->space.rear = queue->space.base;
        }
        queue->space.rest--;
    }
    return;
}

void *
array_queue_leave(struct array_queue *queue)
{
    void *retval;

    retval = NULL;
    if (!is_empty_array_queue(queue)) {
        retval = *queue->space.front++;
        if (queue->space.front == queue->space.base + array_queue_capacity(queue)) {
            queue->space.front = queue->space.base;
        }
        queue->space.rest++;
    }
    return retval;
}

void
array_queue_cleanup(struct array_queue *queue)
{
   if (queue) {
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
