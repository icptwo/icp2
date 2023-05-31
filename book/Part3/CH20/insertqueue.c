// CH20:insertqueue.c
Node * List_insert(Node * head, int val)
{
  if (head == NULL)
    { return Node_construct(val); }
  Node * p = head -> next;
  // find the last node
  whie ((p -> next) != NULL)
    { p = p -> next; }
  p -> next = Node_construct(val);
  return head;   
}
