//#include "level.h"
//#include <iostream>
//
//
//
//
//
//
//
//
//Agent* Level::get_agent(int id)
//{
//	auto agent_iterator = id_to_agent.find(id);
//	if(agent_iterator != id_to_agent.end())
//	{
//		return agent_iterator->second;
//	}
//
//	return nullptr;
//}
//
//
//void Level::remove_dead_and_add_pending_agents()
//{
//	auto agent_iterator = all_agents.begin();
//	while(agent_iterator != all_agents.end())
//	{
//		if((*agent_iterator)->dead)
//		{
//			id_to_agent.erase((*agent_iterator)->id);
//			agent_iterator = all_agents.erase(agent_iterator);
//		} else 
//		{
//			agent_iterator++;
//		}
//	}
//
//	// This must happen _after_ we remove agents from the vector 'all_agents'.
//	// @AddMoreHere
//	grass.remove_if([](Grass& a){ return a.dead; });
//
//
//	// Add all pending agents
//	for (Agent* agent : pending_agents)
//	{
//		last_id += 1;
//		agent->id = last_id;
//
//		all_agents.push_back(agent);
//		id_to_agent.insert({ agent->id, agent });
//	}
//
//	pending_agents.clear(); // Important that we clear this, otherwise we'll add the same agents every frame.
//}
//
//void Level::LoadTextures()
//{
//	
//}
//
//Agent* Level::spawn_agent(Grass agent)
//{
//	Agent* result = nullptr;
//
//	grass.push_back(agent);
//	result = &grass.back();
//	
//	pending_agents.push_back(result); // Enqueue it so that it can be added to the level at the beginning of the next frame
//
//	return result;
//}
//
//void Level::reset()
//{
//	// TODO: Implement this yourself, clear all lists and vectors, after that spawn agents
//
//    // this is here just as an example.
//	LoadTextures();
//
//	std::vector<int> tiletracker;
//	for (int i = 0; i < grid->tile.size(); ++i)
//	{
//		tiletracker.push_back(i);
//	}
//	for (int i = 0; i < 15; ++i)
//	{
//		int v1 = rand() % tiletracker.size() + i;
//		if (grid->tile.at(tiletracker.at(v1)).GetTextureID() == 1)
//		{
//			auto example = spawn_agent(Grass(grid->tile.at(v1).GetPosition().x, grid->tile.at(v1).GetPosition().y));
//			grid->tile.at(v1).isTaken = true;
//		}
//	}
//
//}
//
//void Level::update()
//{
//	remove_dead_and_add_pending_agents();
//	if (agent.isSpreading == true)
//	{
//		for (auto& agent : grass)
//		{
//			for (int i = 0; i < grid->tile.size(); i++)
//			{
//				if (agent.test.x + 50 == grid->tile.at(i).GetPosition().x && agent.test.y == grid->tile.at(i).GetPosition().y && grid->tile.at(i).isTaken == false && grid->tile.at(i).GetTextureID() == 1)
//				{
//					spawn_agent(Grass(agent.test.x + 50, agent.test.y));
//					grid->tile.at(i).isTaken = true;
//					agent.isSpreading = false;
//				}
//				else if (agent.test.x - 50 == grid->tile.at(i).GetPosition().x && agent.test.y == grid->tile.at(i).GetPosition().y && grid->tile.at(i).isTaken == false && grid->tile.at(i).GetTextureID() == 1)
//				{
//					spawn_agent(Grass(agent.test.x - 50, agent.test.y));
//					grid->tile.at(i).isTaken = true;
//					agent.isSpreading = false;
//				}
//				else if (agent.test.x == grid->tile.at(i).GetPosition().x && agent.test.y + 50 == grid->tile.at(i).GetPosition().y && grid->tile.at(i).isTaken == false && grid->tile.at(i).GetTextureID() == 1)
//				{
//					spawn_agent(Grass(agent.test.x, agent.test.y + 50));
//					grid->tile.at(i).isTaken = true;
//					agent.isSpreading = false;
//				}
//				else if (agent.test.x == grid->tile.at(i).GetPosition().x && agent.test.y - 50 == grid->tile.at(i).GetPosition().y && grid->tile.at(i).isTaken == false && grid->tile.at(i).GetTextureID() == 1)
//				{
//					spawn_agent(Grass(agent.test.x, agent.test.y - 50));
//					grid->tile.at(i).isTaken = true;
//					agent.isSpreading = false;
//				}
//			}
//		}
//	}
//
//	for(auto& agent : all_agents)
//	{
//		// TODO: This piece of code needs to be changed to make sure that sense, decide, act, happen at different frequencies.
//			agent->setTextures(grassTexture);
//			agent->sense(this);
//			agent->decide();
//			agent->act();
//	}
//}
//
//void Level::draw()
//{
//	for(auto& agent : all_agents)
//	{
//		agent->draw();
//	}
//
//}
//
