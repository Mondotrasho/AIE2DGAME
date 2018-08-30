#pragma once

#include "Renderer2D.h"

class TreeNode_john
{
public:
	TreeNode_john(TreeNode_john* parent, int value);
	~TreeNode_john();

	bool hasLeft() { return (m_left != nullptr); }
	bool hasRight() { return (m_right != nullptr); }

	int getData() { return m_value; }
	TreeNode_john* getLeft() { return m_left; }
	TreeNode_john* getRight() { return m_right; }

	void setData(int value) { m_value = value; }
	void setLeft(TreeNode_john* node) { m_left = node; }
	void setRight(TreeNode_john* node) { m_right = node; }

	TreeNode_john* getParent() { return m_parent; }
	void setParent(TreeNode_john* p) { m_parent = p; }

	void draw(aie::Renderer2D*, int x, int y, bool selected = false) const;

private:
	// this could also be a pointer to another object if you like
	int m_value{ 0 };
	TreeNode_john* m_parent;

	// node's children
	TreeNode_john* m_left { nullptr };
	TreeNode_john* m_right{ nullptr };
};
