#include "SceneObject.h"
#include <cassert>


SceneObject::SceneObject()
{
}

SceneObject::~SceneObject()
{
	// detach from parent
	if (m_parent != nullptr)
		m_parent->removeChild(this);
	// remove all children
	for (auto child : m_children)
		child->m_parent = nullptr;
}

void SceneObject::addChild(SceneObject* child) {
	// make sure it doesn't have a parent already
	assert(child->m_parent == nullptr);
	// assign "this as parent
	child->m_parent = this;
	// add new child to collection
	m_children.push_back(child);
}

void SceneObject::removeChild(SceneObject* child) {
	// find the child in the collection
	auto iter = std::find(m_children.begin(),
		m_children.end(), child);
	// if found, remove it
	if (iter != m_children.end()) {
		m_children.erase(iter);
		// also unassign parent
		child->m_parent = nullptr;
	}
}

const Matrix3& SceneObject::getLocalTransform() const {
	return m_localTransform;
}
const Matrix3& SceneObject::getGlobalTransform() const {
	return m_globalTransform;
}
void SceneObject::updateTransform() {
	if (m_parent != nullptr)
		m_globalTransform = m_parent->m_globalTransform *
		m_localTransform;
	else
		m_globalTransform = m_localTransform;
	for (auto child : m_children)
		child->updateTransform();
}
void SceneObject::setPosition(float x, float y) {
	m_localTransform[2] = { x, y, 1 };
	updateTransform();
}
void SceneObject::setRotate(float radians) {
	m_localTransform.setRotateZ(radians);
	updateTransform();
}
void SceneObject::setScale(float width, float height) {
	m_localTransform.set_scaled(width, height);
	updateTransform();
}
void SceneObject::translate(float x, float y) {
	m_localTransform.translate(x, y);
	updateTransform();
}
void SceneObject::rotate(float radians) {
	m_localTransform.rotate_z(radians);
	updateTransform();
}
void SceneObject::scale(float width, float height) {
	m_localTransform.scale(width, height);
	updateTransform();
}

void SceneObject::onUpdate(float deltaTime) { }
void SceneObject::onDraw(aie::Renderer2D* renderer) { }

void SceneObject::update(float deltaTime) {
	// run onUpdate behaviour
	onUpdate(deltaTime);
	// update children
	for (auto child : m_children)
		child->update(deltaTime);
}
void SceneObject::draw(aie::Renderer2D* renderer) {
	// run onDraw behaviour
	onDraw(renderer);
	// draw children
	for (auto child : m_children)
		child->draw(renderer);
}