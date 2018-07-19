namespace aie {
	class Renderer2D;
};

class GameState { friend class GameStateManager;
public:
	GameState();
	virtual ~GameState();
	bool isActive() const { return m_active; }
protected:
	virtual void onUpdate(float deltaTime) = 0;
	virtual void onDraw(aie::Renderer2D* renderer) = 0;
	void enter() { m_active = true; onEnter(); }
	void exit() { m_active = false; onExit(); }
	// can be overwritten in derived classes that need to behave
	// in certain ways when activated/deactivated or pushed/popped
	virtual void onEnter() {}
	virtual void onExit() {}
	virtual void onPushed() {}
	virtual void onPopped() {}
private:
	bool m_active = false;
};