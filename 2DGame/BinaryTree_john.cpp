#include "BinaryTree_john.h"
#include <cassert>


BinaryTree_john::BinaryTree_john()
{
}


BinaryTree_john::~BinaryTree_john()
{
	if (!isEmpty())
	{
		delete m_pRoot;
	}
}

bool BinaryTree_john::isEmpty() const
{
	return m_pRoot == nullptr;
}


void BinaryTree_john::insert(int value)
{
	if (find(value) != nullptr) return;

	if (isEmpty())
	{
		m_pRoot = new TreeNode_john(nullptr, value);
	}
	else
	{
		TreeNode_john* node = m_pRoot;
		while(true)
		{
			if (value < node->getData())
			{
				if (node->getLeft() == nullptr)
				{
					node->setLeft(new TreeNode_john(node, value));
					return;
				}
				else
				{
					node = node->getLeft();
				}
			}
			else
			{
				if (node->getRight() == nullptr)
				{
					node->setRight(new TreeNode_john(node, value));
					return;
				}
				else
				{
					node = node->getRight();
				}
			}
		}
	}
}

void BinaryTree_john::remove(TreeNode_john* nodeToRemove)
{
	if (nodeToRemove == nullptr) return;

	if (nodeToRemove->getLeft() == nullptr && nodeToRemove->getRight() == nullptr)
	{
		if (nodeToRemove->getParent() == nullptr)
		{
			m_pRoot = nullptr;
		}
		else
		{
			if (nodeToRemove->getParent()->getLeft() == nodeToRemove)
			{
				nodeToRemove->getParent()->setLeft(nullptr);
			}
			else
			{
				nodeToRemove->getParent()->setRight(nullptr);
			}
		}
		delete nodeToRemove;
		return;
	}

	if (nodeToRemove->getLeft() && nodeToRemove->getRight())
	{
		TreeNode_john* smallestOnTheRight = nodeToRemove->getRight();
		while (smallestOnTheRight->getLeft() != nullptr)
		{
			smallestOnTheRight = smallestOnTheRight->getLeft();
		}
		const int tempValue = smallestOnTheRight->getData();
		nodeToRemove->setData(tempValue);
		remove(smallestOnTheRight);
	}
	else if (nodeToRemove->getLeft())
	{
		nodeToRemove->getLeft()->setParent(nodeToRemove->getParent());
		if (nodeToRemove->getParent()->getLeft() == nodeToRemove)
		{
			nodeToRemove->getParent()->setLeft(nodeToRemove->getLeft());
		}
		else
		{
			nodeToRemove->getParent()->setRight(nodeToRemove->getLeft());
		}

		delete nodeToRemove;
		return;
	}
	else if (nodeToRemove->getRight())
	{
		nodeToRemove->getRight()->setParent(nodeToRemove->getParent());
		if (nodeToRemove->getParent()->getLeft() == nodeToRemove)
		{			
			nodeToRemove->getParent()->setLeft(nodeToRemove->getRight());
		}
		else
		{			
			nodeToRemove->getParent()->setRight(nodeToRemove->getRight());
		}

		delete nodeToRemove;
		return;
	}
}

void BinaryTree_john::remove(int value)
{
	TreeNode_john* nodeToRemove = find(value);
	remove(nodeToRemove);
}

TreeNode_john* BinaryTree_john::find(int value) const
{
	if (isEmpty())
	{
		return nullptr;
	}
	else
	{
		TreeNode_john* node = m_pRoot;
		while (true)
		{
			if (node->getData() == value)
			{
				return node;
			}
			else if (value < node->getData())
			{
				if (node->getLeft())
				{
					node = node->getLeft();
				}
				else
				{
					return nullptr;
				}
			}
			else
			{
				if (node->getRight())
				{
					node = node->getRight();
				}
				else
				{
					return nullptr;
				}
			}
		}
	}
}

bool BinaryTree_john::findNode(int a_nSearchValue, TreeNode_john** ppOutNode, TreeNode_john** ppOutParent)
{
	(void)( (!!(false)) || (_wassert(_CRT_WIDE("false"), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0) );
	return false;
}

void BinaryTree_john::draw(aie::Renderer2D* renderer, TreeNode_john* selected)
{
	draw(renderer, m_pRoot, 640, 680, 640, selected);
}

void BinaryTree_john::draw(aie::Renderer2D* renderer, TreeNode_john* pNode, int x, int y,
	int horizontalSpacing, TreeNode_john* selected) const
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
