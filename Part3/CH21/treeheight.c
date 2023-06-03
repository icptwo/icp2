// CH21:treeheight
int Tree_height(TreeNode * tn)
{
  if (tn == NULL)
    { return 0; }
  int lh = Tree_height(tn -> left);
  int rh = Tree_height(tn -> right);
  if (lh > rh)
    { return (lh + 1); }
  return (rh + 1);
}
