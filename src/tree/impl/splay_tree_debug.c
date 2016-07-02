static inline bool
splay_tree_ordered_p(struct splay_tree *tree)
{
    struct splay_tree *left;
    struct splay_tree *right;

    if (!tree) {
        return true;
    } else {
        left = tree->left;
        right = tree->right;

        if (left && tree->nice < left->nice) {
            return false;
        } else if (right && tree->nice > right->nice) {
            return false;
        } else {
            if (!splay_tree_ordered_p(left)) {
                return false;
            } else {
                return splay_tree_ordered_p(right);
            }
        }
    }
}


