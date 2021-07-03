#include "node.hpp"


namespace huffman
{
    void delete_tree(const TreeNode* root)
    {
        if (!root)
            return;

        delete_tree(root->left);
        delete_tree(root->right);
        delete root;
    }
}
