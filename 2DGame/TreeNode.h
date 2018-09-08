#ifndef TREENODE_H
#define TREENODE_H

namespace aie {
	class Renderer2D;
}

class TreeNode
{
public:
	TreeNode( int value);//TreeNode* parent
	~TreeNode() = default;
	bool hasLeft() const { return (L != nullptr); }
	bool hasRight() const { return (R != nullptr); }
	int getData() { return m_value; }
	TreeNode* getLeft() { if (L != nullptr) return L; }
	TreeNode* getRight() { if (L != nullptr) return R; }
	void setData(int value) { m_value = value; }
	void setLeft(TreeNode* node) { L = node; }
	void setRight(TreeNode* node) { R = node; }
	void draw(aie::Renderer2D*, int x, int y, bool selected = false);

	void setParent(TreeNode* node) { m_parent = node; }
	TreeNode* getParent() const { return m_parent; }
	// node's children
	TreeNode* L;
	TreeNode* R;
	TreeNode* m_parent;
	// this could also be a pointer to another object if you like
	int m_value{ 0 };
private:
	
	//
	
	
};
#endif // TREENODE_H
