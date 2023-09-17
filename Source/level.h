//#pragma once
//
//
//class Level;
//
//
//	
//class Level 
//{
//	int last_id = 0;
//	int up = 0;
//
//	//NOTE(Filippo): Using a list here is not the best idea, ideally you should store agents in some other data structure that keeps them close to each other while being pointer-stable.
//	std::list<Grass> grass;
//
//	std::unordered_map<int, Agent*> id_to_agent;
//	std::vector<Agent*> all_agents;
//
//	std::vector<Agent*> pending_agents; // Agents that will be added at the beginning of the next frame
//
//	Image grassImage;
//
//	Image grassImage2;
//	Image grassImage3;
//
//
//	Grid* grid = Grid::getInstance();
//
//public:
//	Texture2D grassTexture;
//	Texture2D grassTexture2;
//	Texture2D grassTexture3;
//	Agent* get_agent(int id);
//
//	Agent* spawn_agent(Grass agent);
//	// @AddMoreHere
//
//	void reset();
//	void update();
//	void draw();
//
//private:
//	void LoadTextures();
//	void remove_dead_and_add_pending_agents();
//	// Remember, if you add more lists (see @AddMoreHere), edit this function so that dead agents are removed correctly without leaking memory
//};
