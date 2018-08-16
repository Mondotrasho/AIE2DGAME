#include "BinaryTree.h"
#include "TreeNode.h"
#include "Renderer2D.h"


BinaryTree::BinaryTree()
{
	m_pRoot = nullptr;

}

bool BinaryTree::isEmpty() const
{
	return m_pRoot == nullptr;
}

void BinaryTree::insert(int a_nValue)
{
//		If the tree is empty, the value is inserted at the root
	//TreeNode toAdd = TreeNode(a_nValue);
	if(isEmpty())
	{
		
	
		*m_pRoot = toAdd; 
		
		return;
	}
	
//		Set the current node to the root
	m_node = m_pRoot;
//		While the current node is not null
	while (m_pRoot->getData() != 0) {
		//		If the value to be inserted is less than the value in the current node
		if(toAdd.getData() < m_node->getData())
		{
			auto old = m_node;
			m_node = m_node->getLeft();
			m_node->setParent(old);
			continue;
			//		Set the current node to the left child and continue
		}
		//		If the value to be inserted is greater than the current node
		if (toAdd.getData() > m_node->getData())
		{
			auto old = m_node;
			m_node = m_node->getRight();
			m_node->setParent(old);
			continue;
			//		Set the current node to the right child and continue
		}
		//		If the value to be inserted is the same as the value in the current node
		if (toAdd.getData() == m_node->getData())
		{
			//		The value is already in the tree, so exit
			return;
		}
		
		
		
	}
//Get the parent of the current node (before it was set to null)

	
//If value to be inserted is less than parent
	if(m_node->getData() < m_node->getParent()->getData())
	{
		
		//insert value as left child node
		m_node->setRight(m_node);
		return;
	}
	m_node->setRight(m_node);
	//otherwise insert value as right child node
}

void BinaryTree::remove(int a_nValue)
{
	//remove(int value)
	//	find the value in the tree, obtaining a pointer to the node and its parent
	//	If the current node has a right branch,	then
	if(m_pRoot->getRight())
	{	//	find the minimum value in the right branch by iterating down the left branch of the
		//	current node’s right child until there are no more left branch nodes
		while (m_pRoot->getLeft() != nullptr){

		}
	}
	
	//	copy the value from this minimum node to the current node
	//	find the minimum node’s parent node(the parent of the node you are deleting)
	//	if you are deleting the parent’s left node
	//		set this left child of the parent to the right child of the minimum
	//		node
	//		if you are deleting the parent’s right node
	//			set the right child of the parent to the minimum node’s right child
	//			If the current node has no right branch
	//			if we are deleting the parent’s left child, set the left child of the parent to the left
	//				child of the current node
	//				If we are deleting the parent’s right child, set the right child of the parent to the left
	//				child of the current node
	//				If we are deleting the root, the root becomes the left child of the current node

}

void BinaryTree::draw(aie::Renderer2D* renderer, TreeNode* selected)
{
	draw(renderer, m_pRoot, 640, 680, 640, selected);
}

bool BinaryTree::findNode(int a_nSearchValue, TreeNode** ppOutNode, TreeNode** ppOutParent)
{
	//The find() function could be implemented as a recursive function or using a while loop.If you find
	//	the former easier, you may wish to modify your class accordingly.
	//	Set the current node to the root
	m_pRoot->setData(a_nSearchValue);
	//	While the current node is not null
	while (m_pRoot->getData() != 0)
	{
		//	if the search value equals the current node value,
		auto parent = m_pRoot->getData();
		if(m_pRoot->getData() == a_nSearchValue)
		{
			//		return the current node and its parent
			ppOutNode = m_pRoot*;
			ppOutParent = m_pRoot*;
				return 1;
		}

		//		otherwise
		//		If the search value is less than the current node
		//		set the current node to the left child
		//		otherwise set the current node to the right child
		//		end While
	}

	//		If the loop exits, then a match was not found, so return false
}

void BinaryTree::draw(aie::Renderer2D* renderer, TreeNode* pNode, int x, int y,
	int horizontalSpacing, TreeNode* selected)
{
	horizontalSpacing /= 2;
	if (pNode) {
		if (pNode->hasLeft()) {
			renderer->setRenderColour(1, 0, 0);
			renderer->drawLine(x, y, x - horizontalSpacing, y - 80);
			draw(renderer, pNode->getLeft(), x - horizontalSpacing,
				y - 80, horizontalSpacing, selected);
		}
		if (pNode->hasRight()) {
			renderer->setRenderColour(1, 0, 0);
			renderer->drawLine(x, y, x + horizontalSpacing, y - 80);
			draw(renderer, pNode->getRight(), x + horizontalSpacing,
				y - 80, horizontalSpacing, selected);
		}
		pNode->draw(renderer, x, y, (selected == pNode));
	}
}
