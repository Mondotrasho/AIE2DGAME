#ifndef BINARYTREE_H
#define BINARYTREE_H

namespace aie {
	class Renderer2D;
}

class TreeNode;

class BinaryTree {
public:
	BinaryTree();
	~BinaryTree();
	bool isEmpty() const;
	void insert(int a_nValue);
	void remove(int a_nValue);
	TreeNode* find(int a_nValue);
	void draw(aie::Renderer2D* renderer, TreeNode* selected = nullptr);
private:
	//Find the node with the specified value.
	bool findNode(int a_nSearchValue, TreeNode** ppOutNode,
		TreeNode** ppOutParent);
	void draw(aie::Renderer2D* renderer, TreeNode*, int x, int y,
		int horizontalSpacing, TreeNode* selected = nullptr);
	//The root node of the tree
	TreeNode* m_pRoot { nullptr };
	//current node
	TreeNode* m_node{ nullptr };
};
#endif // BINARYTREE_H
