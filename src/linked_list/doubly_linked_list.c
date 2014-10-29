/*
 * _RETURN_ one node linked list.
 *   If no memory, _RETURN_ NULL.
 */
struct doubly_linked_list *
dlinked_list_initial(void)
{
  struct doubly_linked_list *head;

  head = (struct doubly_linked_list *)malloc(sizeof(*head));
  if (head) {
    head->index = 0;
    head->next = head;
    head->previous = head;
  } else {
  }

  return head;
}

/*
 * _RETURN_ one linked list from given int array.
 *          If invalid _ARGV_, _RETURN_ NULL.
 */
struct doubly_linked_list *
dlinked_list_generate(int *val, int size)
{
  struct doubly_linked_list *head;
  struct doubly_linked_list *node;
  register int *iterator;

  head = NULL;
  if (val && size > 0) {
    iterator = val;
    node = (struct doubly_linked_list *)malloc(sizeof(*node));

    if (node) {
      node->index = *iterator++;
      node->next = node;
      node->previous = node;
      head = node;

      while(iterator < val + size) {
        append_dlinked_list_node(node, *iterator++);
        node = node->next;
      }
    }
  }

  return head;
}

/*
 * Append one node of given value after the given node.
 *   If NULL _ARGV_, nothing will be done.
 *   If uninitialized or destroyed, export warning, nothing else will be done.
 */
void
append_dlinked_list_node(struct doubly_linked_list *node, int value)
{
  struct doubly_linked_list *next;


  if (node) {
    next = (struct doubly_linked_list *)malloc(sizeof(*next));
  next->index = value;
  next->previous = NULL;
  next->next = NULL;
  }

  if(NULL != node->next)
  {
    next->next = node->next;
    node->next->previous = next;
  }
  node->next = next;
  next->previous = node;

END_OF_APPEND:
  LEAVE;
  return;
}

void
insert_after_dlinked_list(struct doubly_linked_list *cur,
                          struct doubly_linked_list *node)
{
  ENTER("insert_after_dlinked_list");

  if(cur && node)
  {
    cur->next->previous = node;
    node->next = cur->next;
    cur->next = node;
    node->previous = cur;
  }

  LEAVE;
  return;
}

void
destroy_dlinked_list(struct doubly_linked_list **head)
{
  struct doubly_linked_list *cur;
  struct doubly_linked_list **iter;
  ENTER("destroy_dlinked_list");

  if(NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_CLEAR;
  }

  iter = head;
  while(NULL != (cur = *iter))
  {
    iter = &cur->next;
    remove_node_dlinked_list(cur);
    saft_free((void**)&cur);
  }

  *head = NULL;

END_OF_CLEAR:
  LEAVE;
  return;
}


int
lengthof_dlinked_list(struct doubly_linked_list *head)
{
  int length;
  struct doubly_linked_list *node;
  ENTER("lengthof_dlinked_list");

  if(NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    length = -1;
    goto END_OF_LENGTHOF;
  }

  length = 0;
  node = head;
  while(node->next != head)
  {
    length++;
    node = node->next;
  }

END_OF_LENGTHOF:
  LEAVE;
  return length;
}


struct doubly_linked_list *
accessby_index_dlinked_list(struct doubly_linked_list *head, int index)
{
  struct doubly_linked_list *node;
  ENTER("accessby_index_slinked_list");

  node = head;
  if(NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_ACCESS;
  }
  if(0 > index)
  {
    warning_prompt(ADD_TRACE(warning_digest[1]));
    goto END_OF_ACCESS;
  }

  while(index > 0)
  {
    node = node->next;
    index--;
  }

END_OF_ACCESS:
  LEAVE;
  return node;
}


void
print_dlinked_list(FILE *fd, char *msg, struct doubly_linked_list *head)
{
  int align;
  register struct doubly_linked_list *iterator;
  char *default_msg = "Default doubly linked list";
  ENTER("print_dlinked_list");

  if(NULL == msg)
    msg = default_msg;

  if(head)
  {
    align = 0;
    iterator = head;
    fprintf(fd, "[%s]:\n", msg);
    iterator = iterator->next;
    while(head != iterator)
    {
      fprintf(fd, "%d-> ", iterator->index);
      if(!(++align % PRINT_WIDTH))
        fprintf(fd, "\n");
      iterator = iterator->next;
    }
  }
  fprintf(fd, "NULL\n");

  LEAVE;
  return;
}


void
print_reverse_dlinked_list(FILE *fd, char *msg, struct doubly_linked_list *tail)
{
  int align;
  register struct doubly_linked_list *iterator;
  char *default_msg = "Default doubly linked list";
  ENTER("print_dlinked_list");

  if(NULL == msg)
    msg = default_msg;

  align = 0;
  iterator = tail;
  fprintf(fd, "[%s]:\n", msg);
  iterator = iterator->next;
  while(tail != iterator)
  {
    fprintf(fd, "%d-> ", iterator->index);
    if(!(++align % PRINT_WIDTH))
      fprintf(fd, "\n");
    iterator = iterator->previous;
  }
  fprintf(fd, "NULL\n");

  LEAVE;
  return;
}


void
exchange_dlinked_list(struct doubly_linked_list **head,
  struct doubly_linked_list *node)
{
  struct doubly_linked_list *cur;
  struct doubly_linked_list *start;
  ENTER("exchange_dlinked_list");

  if(NULL == head || NULL == *head || NULL == node)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_EXCHANGE;
  }
  if(*head == node)
  {
    warning_prompt(ADD_TRACE(warning_digest[2]));
    goto END_OF_EXCHANGE;
  }

  start = *head;
  while((cur = *head)->next != start)
  {
    if(cur->next == node)
      break;
    head = &cur->next;
  }

  if(cur)
  {
    /* If cur == *head                                                        */
    if(cur->previous)
    {
      cur->previous->next = node;
      /* If the last element is node                                          */
      if(node->next)
        node->next->previous = cur;
    }
    node->previous = cur->previous;
    cur->previous = node;
    cur->next = node->next;
    node->next = cur;
  }
  else
    warning_prompt(ADD_TRACE(warning_digest[3]));

END_OF_EXCHANGE:
  LEAVE;
  return;
}


void
serialize_dlinked_list(struct doubly_linked_list *head)
{
  struct doubly_linked_list *node;
  int index;
  ENTER("serialize_dlinked_list");

  if(NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_SERIAL;
  }

  index = 0;
  node = head->next;
  while(head != node)
  {
    node->index = index++;
    node = node->next;
  }

END_OF_SERIAL:
  LEAVE;
  return;
}

/*
* As doubly linked list, remove operation will return next node by default.
*/
struct doubly_linked_list *
remove_node_dlinked_list(struct doubly_linked_list *node)
{
  struct doubly_linked_list *next;
  ENTER("remove_node_dlinked_list");

  next = NULL;
  if(node && node->next == node)
    node->next = node->previous = NULL;
  else if(node)
  {
    next = node->next;
    node->previous->next = node->next;
    node->next->previous = node->previous;
  }

  LEAVE;
  return next;
}
