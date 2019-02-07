#include "App2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "imgui.h"
#include "PathFindingDjikstra.h"
#include "AStar.h"


App2D::App2D() {

}

App2D::~App2D() {

}



bool App2D::startup() {

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

	m_playerFollowBehaviour.setSpeed(100);
	m_playerFollowBehaviour.setTarget(&Mouse);

	m_followBehaviour.setSpeed(75);
	m_followBehaviour.setTarget(&m_player);

	m_player.set_position(Vector2(getWindowWidth() * 0.5f, getWindowHeight() * 0.5f));
	m_enemy.set_position(Vector2(getWindowWidth() * 0.5f, getWindowHeight() * 0.5f - 100.0f));
	m_player.add_behaviour(&m_playerFollowBehaviour);
	m_enemy.add_behaviour(&m_followBehaviour);
	m_player.SetSize(10);
	m_enemy.SetSize(10);

	Mouse.set_position(Vector2(ImGui::GetMousePos().x, ImGui::GetMousePos().y));

	//search start


	//setup nodes with no connections
	Node node0 = { "0", Vector2{ 150, 400 } };
	Node node1 = { "1", Vector2{ 250, 400 } };
	Node node2 = { "2", Vector2{ 250, 300 } };
	Node node3 = { "3", Vector2{ 250, 150 } };
	Node node4 = { "4", Vector2{ 200, 100 } };
	Node node5 = { "5", Vector2{ 150, 150 } };
	//pushback Nodes
	nodes.push_back(node0);
	nodes.push_back(node1);
	nodes.push_back(node2);
	nodes.push_back(node3);
	nodes.push_back(node4);
	nodes.push_back(node5);
	//setup edges to attach
	std::vector<Edge> node0Edges;
	Edge node0Edge1 = { &nodes[5], 5.0f };
	node0Edges.push_back(node0Edge1);
	Edge node0Edge2 = { &nodes[1], 2.0f };
	node0Edges.push_back(node0Edge2);
	nodes[0].Connections = node0Edges;

	std::vector<Edge> node1Edges;
	Edge node1Edge1 = { &nodes[2], 3.0f };
	node1Edges.push_back(node1Edge1);
	nodes[1].Connections = node1Edges;

	std::vector<Edge> node2Edges;
	Edge node2Edge1 = { &nodes[0], 3.0f };
	node2Edges.push_back(node2Edge1);
	Edge node2Edge2 = { &nodes[3], 1.0f };
	node2Edges.push_back(node2Edge2);
	nodes[2].Connections = node2Edges;

	std::vector<Edge> node3Edges;
	Edge node3Edge1 = { &nodes[4], 4.0f };
	node3Edges.push_back(node3Edge1);
	Edge node3Edge2 = { &nodes[5], 4.0f };
	node3Edges.push_back(node3Edge2);
	nodes[3].Connections = node3Edges;

	//node 4 is empty

	std::vector<Edge> node5Edges;
	Edge node5Edge1 = { &nodes[4], 6.0f };
	node5Edges.push_back(node5Edge1);
	nodes[5].Connections = node5Edges;
	//attach edges
	node0.Connections = node0Edges;
	node1.Connections = node1Edges;
	node2.Connections = node2Edges;
	node3.Connections = node3Edges;
	//nodes[4].Connections = node4Edges;
	node5.Connections = node5Edges;

	//endpos;
	//search end
	return true;
}

void App2D::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void App2D::update(float deltaTime) {

	m_timer += deltaTime;
	m_player.update(deltaTime);
	m_enemy.update(deltaTime);
	Mouse.set_position(Vector2(ImGui::GetMousePos().x, ImGui::GetMousePos().y));
	// input example
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_SPACE))
		mode = !mode;

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void App2D::draw() {

	// wipe the screen to the background colour
	clearScreen();
	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);
	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	// draw player as a green circle
	m_2dRenderer->setRenderColour(1, 1, 0);
	m_player.draw(m_2dRenderer);
	// draw enemy as a red circle
	m_2dRenderer->setRenderColour(1, 0, 0);
	m_enemy.draw(m_2dRenderer);
	//search draw
	for (auto node : nodes)
	{
		node.Draw(m_2dRenderer);
	}

	if (mode) {
		auto DjikstraPath = Djiki.dijkstrasSearch(&nodes[0], &nodes[4]);
		Djiki.Draw(DjikstraPath, m_2dRenderer);
	}
	if (!mode) {
		auto StarPath = star.AStarSearch(&nodes[0], &nodes[4]);
		star.Draw(StarPath, m_2dRenderer);
	}
	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}
