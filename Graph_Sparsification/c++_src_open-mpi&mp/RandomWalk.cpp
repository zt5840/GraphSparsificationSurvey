/*
 * RandomWalk.cpp
 *
 *  Created on: Dec 25, 2016
 *      Author: dkwan
 */

#include "RandomWalk.h"

RandomWalk::RandomWalk() {
	// TODO Auto-generated constructor stub
	sampled_size = 0;
}

EdgeGraph RandomWalk::get_sampled_graph(const AdjLinkGraph& graph,
		int sampled_size, random_walk_type t, double p) {
	vector<int> nodes;
	vector<Edge> ret;
//	switch (t) {
//	case RANDOM_WALK_WITH_JUMP:
//		nodes = rwj_sampled_points(graph, sampled_size, p);
//		break;
//
//	case RANDOM_WALK_WITH_RESTART:
//		break;
//
//	default:
	ret = rw_sampled_points(graph, sampled_size);
//	}

	return ret;
}

EdgeGraph RandomWalk::rw_sampled_points(const AdjLinkGraph& graph,
		int sampled_size) {
	int n = graph.get_num_of_nodes();
	srand(time(NULL));
	int s = rand() % n;
	// start from s

	int iterations = 0;
	int cnt_nodes = 0;
	EdgeGraph ret;
	unordered_set<int> nodes;
	set<pair<int, int>> my_set;

	// if walk too long, and still get too few points, just return the sampled points.
	while (cnt_nodes < sampled_size && iterations < 5 * sampled_size) {
		if (!nodes.count(s)) {
			cnt_nodes++;
			nodes.insert(s);
		}
		int m = graph.get_num_edge_of_node(s);
		int next = rand() % m;
		int t = graph.adjlink[s][next].v;
		int min_n = min(s, t);
		int max_n = max(s, t);
		if (!my_set.count(make_pair(min_n, max_n))) {
			my_set.insert(make_pair(min_n, max_n));
			ret.push_back(Edge(s, t, 1.0));
		}
		s = t;
		iterations++;
	}

	if(!nodes.count(s)) ret.pop_back();
	this->sampled_size = cnt_nodes;
	this->subset = nodes;
	return ret;
}


vector<int> RandomWalk::rwj_sampled_points(const AdjLinkGraph& graph,
		int sampled_size, double jump_prob) {
	int n = graph.get_num_of_nodes();
	;
	srand(time(NULL));
	int s = rand() % n;
	int iterations = 0;
	vector<int> ret;
	bool visited[n];
	memset(visited, false, sizeof(visited));

	// if walk too long, and still get too few points, just return the sampled points.
	while ((int) ret.size() < sampled_size && iterations < 5 * sampled_size) {
		if (!visited[s]) {
			ret.push_back(s);
			visited[s] = true;
		}

		double f = (double) rand() / RAND_MAX;

		if (f > jump_prob) {
			int m = graph.get_num_edge_of_node(s);
			int next = rand() % m;
			s = graph.adjlink[s][next].v;
		} else {
			// jump to a random point.
			int next = rand() % n;
			s = next;
		}
		iterations++;
	}

	return ret;
}

RandomWalk::~RandomWalk() {
	// TODO Auto-generated destructor stub
}

