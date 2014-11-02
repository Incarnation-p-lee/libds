/*
 * Init single linked list data structure.
 * _RETURN_ single linked list node: (0, NULL).
 *   If no memory available, return NULL.
 */
struct single_linked_list *
slinked_list_initial(void)
{
    struct single_linked_list *head;

    head = (struct single_linked_list *)malloc(sizeof(*head));
    if (!head) {
        pr_log_err("Fail to get memory from system.\n");
    } else {
        head->index = 0;
        head->next = head;
    }

    return head;
}

/*
 * Generate one new single linked list data structure from int array.
 * _RETURN_ the head node of single linked list node.
 * _ARGV_ the int array, if invaild array, _RETURN_ NULL.
 */
struct single_linked_list *
slinked_list_generate(int *val, int size)
{
    struct single_linked_list *head;
    struct single_linked_list *node;
    register int *iterator;

    head = NULL;
    if (val && size > 0) {
        iterator = val;
        node = slinked_list_initial();
        node->index = *iterator++;
        head = node;

        while (iterator < val + size) {
            slinked_list_append_node(node, *iterator++);
            node = node->next;
        }
    }

    return head;
}

/*
 * Append one single linked list node to the node your specified.
 * _RETURN_ the appended node.
 * _ARGV_ node, if NULL, _RETURN_ NULL.
 *        value, the value for the append node. 
 */
struct single_linked_list *
append_slinked_list_node(struct single_linked_list *node, int value)
{
    struct single_linked_list *next;

    next = NULL;
    if (node) {
        next = (struct single_linked_list *)malloc(sizeof(*next));
        if (!next) {
            pr_log_err("Fail to get memory from system.\n");
        } else {
            next->index = value;
            next->next = NULL;
            next->next = node->next;
            node->next = next;
        }
    }

    return next;
}

/*
 * Delete one single linked list node from the given head. 
 * _ARGV_ head, head node.
 *        node, deletion node.
 *        If NULL, nothing will be done.
 */
void
delete_slinked_list_node(struct single_linked_list **head,
    struct single_linked_list *node)
{
  struct single_linked_list *cur;

  if (head && *head && node) {
    cur = *head;
    if (cur == node) {
      *head = node->next;
    } else {
      while (node != cur->next) {
        cur = cur->next;
      }
      cur->next = node->next;
    }
    free(node);
  }

  return;
}

struct single_linked_list *
slinked_list_remove_node

/*
 * _RETURN_ the next node of single linked list. 
 * _ARGV_ current node.
 *        If NULL, _RETURN_ NULL.
 */
struct single_linked_list *
next_slinked_list(struct single_linked_list *cur)
{
  struct single_linked_list *next;

  next = NULL;
  if (cur) {
    next = cur->next;
  }

  return next;
}

/*
 * _ARGV_ head node.
 *        If NULL, nothing will be done.
 */
void
destroy_slinked_list(struct single_linked_list **head)
{
  struct single_linked_list *cur;
  struct single_linked_list **iter;

  if (head && *head) {
    iter = head;
    while (NULL != (cur = *iter)) {
      iter = &cur->next;
      free(cur);
    }

    *head = NULL;
  }

  return;
}

/*
 * _RETURN_ the length of single linked list
 * _ARGV_ head node.
 *        If NULL, return -1
 */
int
lengthof_slinked_list(struct single_linked_list *head)
{
  int length;

  length = -1;
  if (head) {
    lengh = 0;
    while (NULL != head) {
      length++;
      head = head->next;
    }
  }

  return length;
}


struct single_linked_list *
accessby_index_slinked_list(struct single_linked_list *head, int index)
{
  struct single_linked_list *node;
  ENTER("accessby_index_slinked_list");

  node = head;
  if(NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_ACCESS;
  }
  if(0 > index || index > lengthof_slinked_list(head))
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
serialize_slinked_list(struct single_linked_list *head)
{
  struct single_linked_list *node;
  int index;
  ENTER("serialize_slinked_list");

  if(NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_SERIAL;
  }

  index = 0;
  node = head;
  while(node)
  {
    node->index = index++;
    node = node->next;
  }

END_OF_SERIAL:
  LEAVE;
  return;
}

void
print_slinked_list(FILE *fd, char *msg, struct single_linked_list *head)
{
  int align;
  register struct single_linked_list *iterator;
  char *default_msg = "Default single linked list";
  ENTER("print_slinked_list");

  if(NULL == msg)
    msg = default_msg;

  align = 0;
  iterator = head;
  fprintf(fd, "[%s]:\n", msg);
  while(NULL != iterator)
  {
    fprintf(fd, "%d-> ", iterator->index);
    if(!(++align % PRINT_WIDTH))
      fprintf(fd, "\n");
    iterator = iterator->next;
  }
  fprintf(fd, "NULL\n");

  LEAVE;
  return;
}


void
exchange_slinked_list(struct single_linked_list **head,
  struct single_linked_list *node)
{
  struct single_linked_list *cur;
  struct single_linked_list *pre;
  ENTER("exchange_slinked_list");

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

  pre = *head;
  while((cur = *head))
  {
    if(cur->next == node)
      break;
    pre = cur;
    head = &cur->next;
  }

  if(cur)
  {
    pre->next = node;
    cur->next = node->next;
    node->next = cur;
  }
  else
    warning_prompt(ADD_TRACE(warning_digest[3]));

END_OF_EXCHANGE:
  LEAVE;
  return;
}
