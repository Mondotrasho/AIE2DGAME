#pragma once

#include "TreeNode_john.h"

class BinaryTree_john {
public:
	BinaryTree_john();
	~BinaryTree_john();

	bool isEmpty() const;
	void insert(int a_nValue);
	void remove(int a_nValue);
	TreeNode_john* find(int a_nValue) const;
	void draw(aie::Renderer2D* renderer, TreeNode_john* selected = nullptr);
private:

	void remove(TreeNode_john* node);

	//Find the node with the specified value.
	bool findNode(int a_nSearchValue, TreeNode_john** ppOutNode,
		TreeNode_john** ppOutParent);
	void draw(aie::Renderer2D* renderer, TreeNode_john*, int x, int y, int horizontalSpacing, TreeNode_john* selected = nullptr) const;
	//The root node of the tree
	TreeNode_john* m_pRoot { nullptr };
};
