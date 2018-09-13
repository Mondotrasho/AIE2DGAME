#include "BinaryTree.h"
#include "TreeNode.h"
#include "Renderer2D.h"
#include <windows.h>


BinaryTree::BinaryTree() : non_point_root(0)
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
	auto toAdd = new TreeNode(a_nValue);
	if (isEmpty())
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
		if (toAdd->getData() < m_node->getData())
		{
			parent = m_node;
			m_node = m_node->L;
			
			continue;
			//		Set the current node to the left child and continue
		}
		//		If the value to be inserted is greater than the current node
		if (toAdd->getData() > m_node->getData())
		{
			parent = m_node;
			m_node = m_node->R;
			
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
	if (toAdd->getData() < parent->getData())
	{
		//insert value as left child node
		auto temp = parent;
		parent->L = toAdd;
		parent->L->m_parent = temp;
		return;
	}
	auto temp1 = parent;
	parent->R = toAdd;
	parent->R->m_parent = temp1;
	//otherwise insert value as right child node
}

TreeNode* BinaryTree::remove(TreeNode* root, int a_nValue)
{
	
	if (root == nullptr) return root;
	else if (a_nValue < root->getData())
		root->L = remove(root->L, a_nValue);
	else if (a_nValue> root->getData())
		root->R = remove(root->R, a_nValue);
	else
	{
		//No child
		if (root->R == nullptr && root->L == nullptr)
		{
			root = nullptr;
			delete root;
			return nullptr;
			}
		//One child 
		//Child is right as there is no left
		else if (root->L == nullptr)
		{
			//store the place we are
			TreeNode* temp = root;
			//move the right leaf to where we are
			root = root->R;
			//delete where we were
			delete temp;
		}
		//child is left as there is no right
		else if (root->R == nullptr)
		{
			//store where we were
			TreeNode* temp = root;
			//move the left leaf to where we are
			root = root->L;
			//delete the old one
			delete temp;
		}
		//two child
		else
		{
			TreeNode* smallestLeft = nullptr;
			TreeNode* NodetoRemove;
			TreeNode* ParentofSmall = nullptr;

			//this is the one we are removing so its where we are at atm
			NodetoRemove = root;
			
			//make where we are one right so we are only seeing larger
			root = NodetoRemove->R;
			ParentofSmall = root->getParent();
			//while there is a left node move left
			while(root->L != nullptr)
			{
				//store where we are thats the parent of the smallest
				ParentofSmall = root;
				//move where we are to the left once
				root = root->L;
				//store the smallest where we were
				
			}
			smallestLeft = root;
			auto valofsmall = smallestLeft->m_value;
			//need to set NtR val later so save		
			remove(m_pRoot, valofsmall);
			
			//remove(root, root->m_value);
			NodetoRemove->m_value = valofsmall;
			//SUPER IMPORTANT OTHER WISE CHANGE IS LOST
			root = NodetoRemove;
			
		}
	}
	return root;


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



bool BinaryTree::findNode(int a_nSearchValue, TreeNode** ppOutNode, TreeNode** ppOutParent)
{
	//The find() function could be implemented as a recursive function or using a while loop.If you find
	//	the former easier, you may wish to modify your class accordingly.
	//	Set the current node to the root
	//where we were aka the parent of where we are
	TreeNode* parent = nullptr;
	//where we are starting at the root
	m_node = m_pRoot;
	//	While the current node is not null
	while (m_node != nullptr)
	{
		//	if the search value equals the current node value,
		if (m_node->getData() == a_nSearchValue)
		{
			//		return the current node and its parent
			ppOutNode = &m_node;
			ppOutParent = &parent;
			return true;
		}

		//		otherwise

		//		If the search value is less than the current node
		if (m_node->getData() > a_nSearchValue)
		{
			//update parent
			parent = m_node;
			//		set the current node to the left child
			m_node = m_node->L;
			continue;

		}
		//update parent
		parent = m_node;
		//		otherwise set the current node to the right child
		m_node = m_node->R;
		//		end While
	}
	//		If the loop exits, then a match was not found, so return false
	return false;
}

void BinaryTree::draw(aie::Renderer2D* renderer, TreeNode* selected)
{
	draw(renderer, m_pRoot, 640, 680, 640, selected);
}
void BinaryTree::draw(aie::Renderer2D* renderer, TreeNode* pNode, int x, int y,int horizontalSpacing, TreeNode* selected)
{
	horizontalSpacing /= 2;
	if (pNode) {
		if (pNode->hasLeft()) {
			renderer->setRenderColour(1, 0, 0);
			renderer->drawLine(x, y, x - horizontalSpacing, y - 80);
			draw(renderer, pNode->L, x - horizontalSpacing,
				y - 80, horizontalSpacing, selected);
		}
		if (pNode->hasRight()) {
			renderer->setRenderColour(1, 0, 0);
			renderer->drawLine(x, y, x + horizontalSpacing, y - 80);
			draw(renderer, pNode->R, x + horizontalSpacing,
				y - 80, horizontalSpacing, selected);
		}
		pNode->draw(renderer, x, y, (selected == pNode));
	}
}
