#include "BinaryTree.h"
#include "TreeNode.h"
#include "Renderer2D.h"
#include <windows.h>


BinaryTree::BinaryTree(): non_point_root(0)
{
	m_pRoot = nullptr;
	m_node = nullptr;
	ppOutNode = nullptr;
	ppOutParent = nullptr;
}

bool BinaryTree::isEmpty() const
{
	return m_pRoot == nullptr;
}

void BinaryTree::insert(int a_nValue)
{
//		If the tree is empty, the value is inserted at the root
	TreeNode* toAdd = new TreeNode(a_nValue);
	if(isEmpty())
	{
		non_point_root = *toAdd;
		m_pRoot = &non_point_root;
		return;
	}
	
//		Set the current node to the root
	auto parent = m_node;
	m_node = m_pRoot;
//		While the current node is not null
	while (m_node != nullptr) {
		//		If the value to be inserted is less than the value in the current node
		if(toAdd->getData() < m_node->getData())
		{
			parent = m_node;
			m_node = m_node->getLeft();
			continue;
			//		Set the current node to the left child and continue
		}
		//		If the value to be inserted is greater than the current node
		if (toAdd->getData() > m_node->getData())
		{
			parent = m_node;
			m_node = m_node->getRight();
			continue;
			//		Set the current node to the right child and continue
		}
		//		If the value to be inserted is the same as the value in the current node
		if (toAdd->getData() == m_node->getData())
		{
			//		The value is already in the tree, so exit
			return;
		}
		
		
		
	}
//Get the parent of the current node (before it was set to null)
//todo dunno if I need this
//If value to be inserted is less than parent
	if(toAdd->getData() < parent->getData())
	{
		//insert value as left child node
		parent->setLeft(toAdd);
		return;
	}
	parent->setRight(toAdd);
	//otherwise insert value as right child node
}

TreeNode* BinaryTree::remove(TreeNode* root, int a_nValue)
{
	if (root == nullptr) return root;
	else if (a_nValue < root->getData())
		root->m_left = remove(root->m_left, a_nValue);
	else if (a_nValue> root->getData())
		root->m_right = remove(root->m_right, a_nValue);
	else
	{
		//No child
		if (root->m_right == nullptr && root->m_left == nullptr)
		{
			delete root;
			root = nullptr;
		}
		//One child 
		else if (root->m_left == nullptr)
		{
			TreeNode* temp = root;
			root = root->m_right;
			delete temp;
		}
		else if (root->m_right == nullptr)
		{
			TreeNode* temp = root;
			root = root->m_left;
			delete temp;
		}
		//two child
		else
		{
			TreeNode* set = nullptr;

			if (root->m_left == nullptr)  set = nullptr;

			while (root->m_left->m_right != nullptr)
			{
				root->m_left = root->m_left->m_right;// root->m_left->m_right;
			}

			set = root->m_left;
			//set->m_left = root->m_left->m_left;
			//set->m_right = root->m_left->m_right;
			root->m_value = set->m_value;
			root->m_left = remove(root->m_left, set->getData());
		}
	}
	return root;

	////	find the value in the tree, obtaining a pointer to the node and its parent
	//TreeNode** current = nullptr;
	//TreeNode** parent = nullptr;
	//findNode(a_nValue, current, parent);
	////	If the current node has a right branch,	then
	//auto temp = *current;
	//if(temp->m_right != nullptr)
	//{	//	find the minimum value in the right branch by iterating down the left branch of the
	//	//	current node’s right child until there are no more left branch nodes
	//	while (m_pRoot-> != nullptr){

	//	}
	//}
	
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

TreeNode* BinaryTree::find(int a_nValue)
{
	ppOutNode = nullptr;
	findNode(a_nValue, ppOutNode, ppOutParent);
	if (ppOutNode != nullptr)
	{
		return *ppOutNode;
	}

	//todo check this caught
	return nullptr;

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
	//m_pRoot = m_node;
	m_node = m_pRoot;
	//	While the current node is not null
	while (m_node != nullptr)
	{
		//	if the search value equals the current node value,
		if(m_node->getData() == a_nSearchValue)
		{
			//		return the current node and its parent
			ppOutNode = &m_node;
			auto parent = m_node->getParent();
			ppOutParent = &parent;
			return true;
		}

		//		otherwise

		//		If the search value is less than the current node
		if (m_node->getData() > a_nSearchValue)
		{
			//		set the current node to the left child
			m_node = m_node->getLeft();
			continue;
		
		}
		//		otherwise set the current node to the right child
		m_node = m_node->getRight();
		//		end While
	}
	//		If the loop exits, then a match was not found, so return false
	return false;
}

void BinaryTree::draw(aie::Renderer2D* renderer, TreeNode* pNode, int x, int y,int horizontalSpacing, TreeNode* selected)
{
	horizontalSpacing /= 2;

	if (pNode) {

		if (pNode->getLeft() != nullptr) 
		{	
			renderer->setRenderColour(1, 0, 0);
			renderer->drawLine(x, y, x - horizontalSpacing, y - 80);
			draw(renderer, pNode->getLeft(), x - horizontalSpacing,
				y - 80, horizontalSpacing, selected);
			
		}
		if (pNode->getRight() != nullptr) 
		{
			renderer->setRenderColour(1, 0, 0);
			renderer->drawLine(x, y, x + horizontalSpacing, y - 80);
			draw(renderer, pNode->getRight(), x + horizontalSpacing,
				y - 80, horizontalSpacing, selected);
		}

		pNode->draw(renderer, x, y, (selected == pNode));
	}
}
