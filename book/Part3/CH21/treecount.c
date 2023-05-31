// CH21:treecount
void Tree_count(TreeNode * tn, int * count)
{
  if (tn == NULL)
    { return; }
  (* count) ++;
  Tree_count(tn -> left, count);
  Tree_count(tn -> right, count);
}
