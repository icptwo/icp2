// CH20:insertsort.c
Node * List_insert(Node * head, int val)
{
  Node * ptr = Node_construct(val); 
  if (head == NULL)
    { return ptr; }
  if ((head -> value) > val) // new node becomes the head
    {
      ptr -> next = head; 
      return ptr;
    }
  // new node is not the head
  Node * q = head;
  Node * r = q -> next; // q is always before r
  while ((r != NULL) && ((r -> value) < val))
    {
      r = r -> next;
      q = q -> next;
    }
  // new node is between q and r; it is OK r is NULL
  q -> next = ptr;
  ptr -> next = r;
  return head;
}
