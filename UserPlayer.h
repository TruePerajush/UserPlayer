#pragma once
#include<iostream>
#include"player.h"
#include<vector>
using namespace std;

//This pair needed for returning value for calculate_near_points func
typedef pair<float, Point> WeightAndPoint;
class UserPlayer: public Player
{
	// This field contains values for all weights
	// TODO: Optimize weight table
	vector<vector<float>> weight_table = { 
		{0, 0, 0},
		{0, 0.1, 0.25},
		{0, 2, 5},
		{0, 7, 50},
		{0, 100, 1000},
		{1000, 1000, 1000} 
	};
	string _name;
	Mark mark = Mark::None;
public:
	UserPlayer(const string& name): _name(name){}
	string get_name() const override { return _name; }
	void assign_mark(Mark player_mark) override { mark = player_mark; }
	Point play(const GameView& game) override;
	void notify(const GameView& game, const Event& event) override;
	/*
	* This method calculate weight of the 8 near points and returns pair<float, Point>, 
	* which contains nearest efficent point and its weight
	*/
	WeightAndPoint calculate_near_points(const GameView& game, const Point& currently_checking_point, const Boundary& field_size);
	/*
	* This method calculate weight of the point based on 4 lines from our point of view 
	* and from point of view of oponent and returns weight of the point
	*/
	float calculate_weight(const GameView& game, Point& currently_checking_point, const Boundary& field_size);
	void calculate_weight_horizontal(const GameView& game, const Boundary& field_size, Point& currently_checking_point, float& calculating_weight);
	void calculate_weight_vertical(const GameView& game, const Boundary& field_size, Point& currently_checking_point, float& calculating_weight);
	void calculate_weight_diagonal_45(const GameView& game, const Boundary& field_size, Point& currently_checking_point, float& calculating_weight);
	void calculate_weight_diagonal_135(const GameView& game, const Boundary& field_size, Point& currently_checking_point, float& calculating_weight);
	/*
	* This method allows to change field weight_table
	*/
	void change_weight_table(const vector<vector<float>>& new_weight_table);
};
