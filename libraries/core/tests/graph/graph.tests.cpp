#include "morpheus/core/graph/graph.hpp"

#include <catch2/catch_all.hpp>

namespace morpheus::graph
{

/*constexpr auto allocateNodeId()
{
	static constexpr NodeId nextId = 0;
	return nextId;
}*/

constexpr NodeId gameId = 1;
constexpr NodeId physicsId = 2;
constexpr NodeId sceneGraphId = 3;
constexpr NodeId aiEngineId = 4;
constexpr NodeId visualisationId = 5;
constexpr NodeId worldModelId = 6;

TEST_CASE("Verify construction of a graph", "[morpheus.graph.graph]")
{
	Node constexpr game(gameId);
	Node constexpr physics(physicsId);
	Node constexpr sceneGraph(sceneGraphId);
	Node constexpr aiEngine(aiEngineId);
	Node constexpr visualisation(visualisationId);
	Node constexpr worldModel(worldModelId);

	std::array constexpr nodes = { game, physics, sceneGraph, aiEngine, visualisation, worldModel };
	STATIC_REQUIRE(UniqueNodeRange<decltype(nodes)>);

	Graph constexpr gameGraph(nodes);
}


TEST_CASE("Verify creation of a constexpr graph", "[morpheus.graph.constexpr]")
{
}

} // morpheus::namespace morpheus::graph
