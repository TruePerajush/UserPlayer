#include"UserPlayer.h"
Point UserPlayer::play(const GameView& game) {
	Boundary field_size = game.get_settings().field_size; //This variable will be used in all 3 main methods (play, calculate_near_points, calculate_weight)
	Point result((field_size.min.x + field_size.max.x) / 2, (field_size.min.y + field_size.max.y) / 2); //This variable contain result, which is returning result of the method
																										//By defolt it contains middle point of field or nearest point
	if (game.get_state().field.get()->get_value(result) != Mark::None) //This "if" needed to check if userPlayer doesn't play first
	{
		result.x += 1;
	}
	WeightAndPoint calculated; //This variable will be used to contain result of method calculate_near_points
	float max_weight = 0; //This variable will contain max weight of point among all near non-None points
	//This two "for"s needed to search for non-None points on the field
	for (int x = field_size.min.x; x <= field_size.max.x; x++)
	{
		for (int y = field_size.min.y; y <= field_size.max.y; y++)
		{
			Point searching_point(x, y); //This additional point needed to search through field and to calculate nearest points
			if (game.get_state().field.get()->get_value(searching_point) != Mark::None)
			{
				calculated = calculate_near_points(game, searching_point, field_size);
				if (calculated.first > max_weight)
				{
					max_weight = calculated.first;
					result = calculated.second;
				}
				//This "if" needed for situation when user and oponent both have 4 points in a row but they eaqually efficient for algorithm,
				//so if the user plays first, so this method will return exactly winnig point for him
				//The same "if" will be in calculate_near_points
				else if (calculated.first >= weight_table[5][2] && game.get_state().field.get()->get_value(searching_point) == mark)
				{
					return result;
				}
			}
		}
	}
	return result;
}
WeightAndPoint UserPlayer::calculate_near_points(const GameView& game, const Point& searching_point, const Boundary& field_size) {
	Point currently_checking_point(searching_point); //This copy of a searching_point needed to look through all 8 nearest points
													//and to not change searching point, beacause it needed for the same "if" as in play method 
													//for equal situation
	float calculated_weight = 0; //Will contain result of method calculate_weight
	WeightAndPoint result(0, currently_checking_point); //contains result with weight of the most efficiently point and point
	if (currently_checking_point.x + 1 <= field_size.max.x) //Calculates point to the right 
	{
		currently_checking_point.x += 1;
		if (game.get_state().field.get()->get_value(currently_checking_point) == Mark::None)
		{
			if (result.first == 0){result.second = currently_checking_point;};
			calculated_weight = calculate_weight(game, currently_checking_point, field_size);
			if (calculated_weight > result.first)
			{
				result.first = calculated_weight;
				result.second = currently_checking_point;
			}
			//"if" for equal situation
			else if (calculated_weight >= weight_table[5][2] && game.get_state().field.get()->get_value(searching_point) == mark)
			{
				result.first = calculated_weight;
				result.second = currently_checking_point;
				return result;
			}
		}
		currently_checking_point.x -= 1;
	}
	if (currently_checking_point.y - 1 >= field_size.min.y) //Calculates lower point
	{
		currently_checking_point.y -= 1;
		if (game.get_state().field.get()->get_value(currently_checking_point) == Mark::None)
		{
			if (result.first == 0){result.second = currently_checking_point;};
			calculated_weight = calculate_weight(game, currently_checking_point, field_size);
			if (calculated_weight > result.first)
			{
				result.first = calculated_weight;
				result.second = currently_checking_point;
			}
			else if (calculated_weight >= weight_table[5][2] && game.get_state().field.get()->get_value(searching_point) == mark)
			{
				result.first = calculated_weight;
				result.second = currently_checking_point;
				return result;
			}
		}
		currently_checking_point.y += 1;
	}
	if (currently_checking_point.x - 1 >= field_size.min.x) //Calculates point tp the left
	{
		currently_checking_point.x -= 1;
		if (game.get_state().field.get()->get_value(currently_checking_point) == Mark::None)
		{
			if (result.first == 0){result.second = currently_checking_point;};
			calculated_weight = calculate_weight(game, currently_checking_point, field_size);
			if (calculated_weight > result.first)
			{
				result.first = calculated_weight;
				result.second = currently_checking_point;
			}
			else if (calculated_weight >= weight_table[5][2] && game.get_state().field.get()->get_value(searching_point) == mark)
			{
				result.first = calculated_weight;
				result.second = currently_checking_point;
				return result;
			}
		}
		currently_checking_point.x += 1;
	}
	if (currently_checking_point.y + 1 <= field_size.max.y) //Calculates higher point
	{
		currently_checking_point.y += 1;
		if (game.get_state().field.get()->get_value(currently_checking_point) == Mark::None)
		{
			if (result.first == 0){result.second = currently_checking_point;};
			calculated_weight = calculate_weight(game, currently_checking_point, field_size);
			if (calculated_weight > result.first)
			{
				result.first = calculated_weight;
				result.second = currently_checking_point;
			}
			else if (calculated_weight >= weight_table[5][2] && game.get_state().field.get()->get_value(searching_point) == mark)
			{
				result.first = calculated_weight;
				result.second = currently_checking_point;
				return result;
			}
		}
		currently_checking_point.y -= 1;
	}
	if (currently_checking_point.x + 1 <= field_size.max.x && currently_checking_point.y + 1 <= field_size.max.y) //Calculates point higher and to the right
	{
		currently_checking_point.y += 1;
		currently_checking_point.x += 1;
		if (game.get_state().field.get()->get_value(currently_checking_point) == Mark::None)
		{
			if (result.first == 0){result.second = currently_checking_point;};
			calculated_weight = calculate_weight(game, currently_checking_point, field_size);
			if (calculated_weight > result.first)
			{
				result.first = calculated_weight;
				result.second = currently_checking_point;
			}
			else if (calculated_weight >= weight_table[5][2] && game.get_state().field.get()->get_value(searching_point) == mark) 
			{
				result.first = calculated_weight;
				result.second = currently_checking_point;
				return result;
			}
		}
		currently_checking_point.y -= 1;
		currently_checking_point.x -= 1;
	}
	if (currently_checking_point.x + 1 <= field_size.max.x && currently_checking_point.y - 1 >= field_size.min.y)//Calculates point lower and to the right
	{
		currently_checking_point.y -= 1;
		currently_checking_point.x += 1;
		if (game.get_state().field.get()->get_value(currently_checking_point) == Mark::None)
		{
			if (result.first == 0){result.second = currently_checking_point;};
			calculated_weight = calculate_weight(game, currently_checking_point, field_size);
			if (calculated_weight > result.first)
			{
				result.first = calculated_weight;
				result.second = currently_checking_point;
			}
			else if (calculated_weight >= weight_table[5][2] && game.get_state().field.get()->get_value(searching_point) == mark)
			{
				result.first = calculated_weight;
				result.second = currently_checking_point;
				return result;
			}
		}
		currently_checking_point.y += 1;
		currently_checking_point.x -= 1;
	}
	if (currently_checking_point.x - 1 >= field_size.min.x && currently_checking_point.y + 1 <= field_size.max.y) //Calculates point higher and to the left
	{
		currently_checking_point.y += 1;
		currently_checking_point.x -= 1;
		if (game.get_state().field.get()->get_value(currently_checking_point) == Mark::None)
		{
			if (result.first == 0){result.second = currently_checking_point;};
			calculated_weight = calculate_weight(game, currently_checking_point, field_size);
			if (calculated_weight > result.first)
			{
				result.first = calculated_weight;
				result.second = currently_checking_point;
			}
			else if (calculated_weight >= weight_table[5][2] && game.get_state().field.get()->get_value(searching_point) == mark)
			{
				result.first = calculated_weight;
				result.second = currently_checking_point;
				return result;
			}
		}
		currently_checking_point.y -= 1;
		currently_checking_point.x += 1;
	}
	if (currently_checking_point.x - 1 >= field_size.min.x && currently_checking_point.y - 1 >= field_size.min.y) //Calculates point lower and to the left
	{
		currently_checking_point.y -= 1;
		currently_checking_point.x -= 1;
		if (game.get_state().field.get()->get_value(currently_checking_point) == Mark::None)
		{
			if (result.first == 0){result.second = currently_checking_point;};
			calculated_weight = calculate_weight(game, currently_checking_point, field_size);
			if (calculated_weight > result.first)
			{
				result.first = calculated_weight;
				result.second = currently_checking_point;
			}
			else if (calculated_weight >= weight_table[5][2] && game.get_state().field.get()->get_value(searching_point) == mark)
			{
				result.first = calculated_weight;
				result.second = currently_checking_point;
				return result;
			}
		}
		currently_checking_point.y += 1;
		currently_checking_point.x += 1;
	}
	return result;
}
float UserPlayer::calculate_weight(const GameView& game, Point& currently_checking_point, const Boundary& field_size) {
	float calculating_weight = 0; //Will contain the sum of weight of all 4 lines
	// For horizontal
	calculate_weight_horizontal(game, field_size, currently_checking_point, calculating_weight);
	// For vertical
	calculate_weight_vertical(game, field_size, currently_checking_point, calculating_weight);
	// For 45 degrees diagonal
	calculate_weight_diagonal_45(game, field_size, currently_checking_point, calculating_weight);
	// For 135 degrees diagonal
	calculate_weight_diagonal_135(game, field_size, currently_checking_point, calculating_weight);
	return calculating_weight;
}
void UserPlayer::calculate_weight_horizontal(const GameView& game, const Boundary& field_size, Point& currently_checking_point, float& calculating_weight)
{
		// Calculating weight from the point of our view
		Point for_calculating(currently_checking_point);
		int amount_of_this_marks = 1; //Always starts with 1, because on this empty point we imaginary put "mark"
		int amount_of_free_ways_1 = 0;//It can be 1 or 0, because we going trough one "for" only forward of backward, relatively speaking
		bool is_out = false;
		for (int x = currently_checking_point.x + 1; x < currently_checking_point.x + 5; x++) //calculating weight to the right of currently_checking_point
		{
			if (is_out){break;}
			for_calculating.x += 1;
			if (x <= field_size.max.x)
			{
				switch (game.get_state().field.get()->get_value(for_calculating))
				{
				case Mark::Cross:
					if (mark == Mark::Cross)
					{
						amount_of_this_marks += 1;
						amount_of_free_ways_1 = x == field_size.max.x ? 0 : 1;
					}
					else
					{
						amount_of_free_ways_1 = 0;
						is_out = true;
					}
					break;
				case Mark::Zero:
					if (mark == Mark::Zero)
					{
						amount_of_this_marks += 1;
						amount_of_free_ways_1 = x == field_size.max.x ? 0 : 1;
					}
					else
					{
						amount_of_free_ways_1 = 0;
						is_out = true;
					}
					break;
				default:
					amount_of_free_ways_1 = 1;
					is_out = true;
				}
			}
			else {
				amount_of_free_ways_1 = 0;
				is_out = true;
			}
		}
		for_calculating = currently_checking_point;
		int amount_of_free_ways_2 = 0;
		is_out = false;
		for (int x = currently_checking_point.x - 1; x > currently_checking_point.x - 5; x--) //calculating weight to the left of currently_checking_point
		{
			if (is_out) { break; }
			for_calculating.x -= 1;
			if (x >= field_size.min.x)
			{
				switch (game.get_state().field.get()->get_value(for_calculating))
				{
				case Mark::Cross:
					if (mark == Mark::Cross)
					{
						amount_of_this_marks += 1;
						amount_of_free_ways_2 = x == field_size.min.x ? 0 : 1;
					}
					else
					{
						amount_of_free_ways_2 = 0;
						is_out = true;
					}
					break;
				case Mark::Zero:
					if (mark == Mark::Zero)
					{
						amount_of_this_marks += 1;
						amount_of_free_ways_2 = x == field_size.min.x ? 0 : 1;
					}
					else
					{
						amount_of_free_ways_2 = 0;
						is_out = true;
					}
					break;
				default:
					amount_of_free_ways_2 = 1;
					is_out = true;
				}
			}
			else {
				amount_of_free_ways_2 = 0;
				is_out = true;
			}
		}
		amount_of_this_marks = amount_of_this_marks > 5 ? 5 : amount_of_this_marks;
		calculating_weight += weight_table[amount_of_this_marks][amount_of_free_ways_1 + amount_of_free_ways_2];
		// Calculating now weight from the point of view of oponent
		for_calculating = currently_checking_point;
		int amount_of_other_marks = 1;
		int amount_of_other_free_ways_1 = 0;
		is_out = false;
		for (int x = currently_checking_point.x + 1; x < currently_checking_point.x + 5; x++)
		{
			if (is_out) { break; }
			for_calculating.x += 1;
			if (x <= field_size.max.x)
			{
				switch (game.get_state().field.get()->get_value(for_calculating))
				{
				case Mark::Cross:
					if (mark != Mark::Cross)
					{
						amount_of_other_marks += 1;
						amount_of_other_free_ways_1 = x == field_size.max.x ? 0 : 1;
					}
					else
					{
						amount_of_other_free_ways_1 = 0;
						is_out = true;
					}
					break;
				case Mark::Zero:
					if (mark != Mark::Zero)
					{
						amount_of_other_marks += 1;
						amount_of_other_free_ways_1 = x == field_size.max.x ? 0 : 1;
					}
					else
					{
						amount_of_other_free_ways_1 = 0;
						is_out = true;
					}
					break;
				default:
					amount_of_other_free_ways_1 = 1;
					is_out = true;
				}
			}
			else {
				amount_of_other_free_ways_1 = 0;
				is_out = true;
			}
		}
		for_calculating = currently_checking_point;
		int amount_of_other_free_ways_2 = 0;
		is_out = false;
		for (int x = currently_checking_point.x - 1; x > currently_checking_point.x - 5; x--)
		{
			if (is_out) { break; }
			for_calculating.x -= 1;
			if (x >= field_size.min.x)
			{
				switch (game.get_state().field.get()->get_value(for_calculating))
				{
				case Mark::Cross:
					if (mark != Mark::Cross)
					{
						amount_of_other_marks += 1;
						amount_of_other_free_ways_2 = x == field_size.min.x ? 0 : 1;
					}
					else
					{
						amount_of_other_free_ways_2 = 0;
						is_out = true;
					}
					break;
				case Mark::Zero:
					if (mark != Mark::Zero)
					{
						amount_of_other_marks += 1;
						amount_of_other_free_ways_2 = x == field_size.min.x ? 0 : 1;
					}
					else
					{
						amount_of_other_free_ways_2 = 0;
						is_out = true;
					}
					break;
				default:
					amount_of_other_free_ways_2 = 1;
					is_out = true;
				}
			}
			else {
				amount_of_other_free_ways_2 = 0;
				is_out = true;
			}
		}
		amount_of_other_marks = amount_of_other_marks > 5 ? 5 : amount_of_other_marks;
		calculating_weight += weight_table[amount_of_other_marks][amount_of_other_free_ways_1 + amount_of_other_free_ways_2];
}
void UserPlayer::calculate_weight_vertical(const GameView& game, const Boundary& field_size, Point& currently_checking_point, float& calculating_weight)
{
	Point for_calculating(currently_checking_point);
	int amount_of_this_marks = 1;
	int amount_of_free_ways_1 = 0;
	bool is_out = false;
	for (int y = currently_checking_point.y + 1; y < currently_checking_point.y + 5; y++)
	{
		if (is_out) { break; }
		for_calculating.y += 1;
		if (y <= field_size.max.y)
		{
			switch (game.get_state().field.get()->get_value(for_calculating))
			{
			case Mark::Cross:
				if (mark == Mark::Cross)
				{
					amount_of_this_marks += 1;
					amount_of_free_ways_1 = y == field_size.max.y ? 0 : 1;
				}
				else
				{
					amount_of_free_ways_1 = 0;
					is_out = true;
				}
				break;
			case Mark::Zero:
				if (mark == Mark::Zero)
				{
					amount_of_this_marks += 1;
					amount_of_free_ways_1 = y == field_size.max.y ? 0 : 1;
				}
				else
				{
					amount_of_free_ways_1 = 0;
					is_out = true;
				}
				break;
			default:
				amount_of_free_ways_1 = 1;
				is_out = true;
			}
		}
		else {
			amount_of_free_ways_1 = 0;
			is_out = true;
		}
	}
	for_calculating = currently_checking_point;
	int amount_of_free_ways_2 = 0;
	is_out = false;
	for (int y = currently_checking_point.y - 1; y > currently_checking_point.y - 5; y--)
	{
		if (is_out) { break; }
		for_calculating.y -= 1;
		if (y >= field_size.min.y)
		{
			switch (game.get_state().field.get()->get_value(for_calculating))
			{
			case Mark::Cross:
				if (mark == Mark::Cross)
				{
					amount_of_this_marks += 1;
					amount_of_free_ways_2 = y == field_size.min.y ? 0 : 1;
				}
				else
				{
					amount_of_free_ways_2 = 0;
					is_out = true;
				}
				break;
			case Mark::Zero:
				if (mark == Mark::Zero)
				{
					amount_of_this_marks += 1;
					amount_of_free_ways_2 = y == field_size.min.y ? 0 : 1;
				}
				else
				{
					amount_of_free_ways_2 = 0;
					is_out = true;
				}
				break;
			default:
				amount_of_free_ways_2 = 1;
				is_out = true;
			}
		}
		else {
			amount_of_free_ways_2 = 0;
			is_out = true;
		}
	}
	amount_of_this_marks = amount_of_this_marks > 5 ? 5 : amount_of_this_marks;
	calculating_weight += weight_table[amount_of_this_marks][amount_of_free_ways_1 + amount_of_free_ways_2];
	// Calculating now weight from the point of view of oponent
	for_calculating = currently_checking_point;
	int amount_of_other_marks = 1;
	int amount_of_other_free_ways_1 = 0;
	is_out = false;
	for (int y = currently_checking_point.y + 1; y < currently_checking_point.y + 5; y++)
	{
		if (is_out) { break; }
		for_calculating.y += 1;
		if (y <= field_size.max.y)
		{
			switch (game.get_state().field.get()->get_value(for_calculating))
			{
			case Mark::Cross:
				if (mark != Mark::Cross)
				{
					amount_of_other_marks += 1;
					amount_of_other_free_ways_1 = y == field_size.max.y ? 0 : 1;
				}
				else
				{
					amount_of_other_free_ways_1 = 0;
					is_out = true;
				}
				break;
			case Mark::Zero:
				if (mark != Mark::Zero)
				{
					amount_of_other_marks += 1;
					amount_of_other_free_ways_1 = y == field_size.max.y ? 0 : 1;
				}
				else
				{
					amount_of_other_free_ways_1 = 0;
					is_out = true;
				}
				break;
			default:
				amount_of_other_free_ways_1 = 1;
				is_out = true;
			}
		}
		else {
			amount_of_other_free_ways_1 = 0;
			is_out = true;
		}
	}
	for_calculating = currently_checking_point;
	int amount_of_other_free_ways_2 = 0;
	is_out = false;
	for (int y = currently_checking_point.y - 1; y > currently_checking_point.y - 5; y--)
	{
		if (is_out) { break; }
		for_calculating.y -= 1;
		if (y >= field_size.min.y)
		{
			switch (game.get_state().field.get()->get_value(for_calculating))
			{
			case Mark::Cross:
				if (mark != Mark::Cross)
				{
					amount_of_other_marks += 1;
					amount_of_other_free_ways_2 = y == field_size.min.y ? 0 : 1;
				}
				else
				{
					amount_of_other_free_ways_2 = 0;
					is_out = true;
				}
				break;
			case Mark::Zero:
				if (mark != Mark::Zero)
				{
					amount_of_other_marks += 1;
					amount_of_other_free_ways_2 = y == field_size.min.y ? 0 : 1;
				}
				else
				{
					amount_of_other_free_ways_2 = 0;
					is_out = true;
				}
				break;
			default:
				amount_of_other_free_ways_2 = 1;
				is_out = true;
			}
		}
		else {
			amount_of_other_free_ways_2 = 0;
			is_out = true;
		}
	}
	amount_of_other_marks = amount_of_other_marks > 5 ? 5 : amount_of_other_marks;
	calculating_weight += weight_table[amount_of_other_marks][amount_of_other_free_ways_1 + amount_of_other_free_ways_2];
}
void UserPlayer::calculate_weight_diagonal_45(const GameView& game, const Boundary& field_size, Point& currently_checking_point, float& calculating_weight)
{
	Point for_calculating(currently_checking_point);
	int amount_of_this_marks = 1;
	int amount_of_free_ways_1 = 0;
	bool is_out = false;
	for (int x = currently_checking_point.x + 1, y = currently_checking_point.y + 1; x < currently_checking_point.x + 5; x++, y++)
	{
		if (is_out) { break; }
		for_calculating.x += 1;
		for_calculating.y += 1;
		if (x <= field_size.max.x && y <= field_size.max.y)
		{
			switch (game.get_state().field.get()->get_value(for_calculating))
			{
			case Mark::Cross:
				if (mark == Mark::Cross)
				{
					amount_of_this_marks += 1;
					amount_of_free_ways_1 = (y == field_size.max.y && x == field_size.max.x) ? 0 : 1;
				}
				else
				{
					amount_of_free_ways_1 = 0;
					is_out = true;
				}
				break;
			case Mark::Zero:
				if (mark == Mark::Zero)
				{
					amount_of_this_marks += 1;
					amount_of_free_ways_1 = (y == field_size.max.y && x == field_size.max.x) ? 0 : 1;
				}
				else
				{
					amount_of_free_ways_1 = 0;
					is_out = true;
				}
				break;
			default:
				amount_of_free_ways_1 = 1;
				is_out = true;
			}
		}
		else {
			amount_of_free_ways_1 = 0;
			is_out = true;
		}
	}
	for_calculating = currently_checking_point;
	int amount_of_free_ways_2 = 0;
	is_out = false;
	for (int x = currently_checking_point.x - 1, y = currently_checking_point.y - 1; x > currently_checking_point.x - 5; x--, y--)
	{
		if (is_out) { break; }
		for_calculating.x -= 1;
		for_calculating.y -= 1;
		if (x >= field_size.min.x && y >= field_size.min.y)
		{
			switch (game.get_state().field.get()->get_value(for_calculating))
			{
			case Mark::Cross:
				if (mark == Mark::Cross)
				{
					amount_of_this_marks += 1;
					amount_of_free_ways_2 = (y == field_size.min.y && x == field_size.min.x) ? 0 : 1;
				}
				else
				{
					amount_of_free_ways_2 = 0;
					is_out = true;
				}
				break;
			case Mark::Zero:
				if (mark == Mark::Zero)
				{
					amount_of_this_marks += 1;
					amount_of_free_ways_2 = (y == field_size.min.y && x == field_size.min.x) ? 0 : 1;
				}
				else
				{
					amount_of_free_ways_2 = 0;
					is_out = true;
				}
				break;
			default:
				amount_of_free_ways_2 = 1;
				is_out = true;
			}
		}
		else {
			amount_of_free_ways_2 = 0;
			is_out = true;
		}
	}
	amount_of_this_marks = amount_of_this_marks > 5 ? 5 : amount_of_this_marks;
	calculating_weight += weight_table[amount_of_this_marks][amount_of_free_ways_1 + amount_of_free_ways_2];
	// Calculating now weight from the point of view of oponent
	for_calculating = currently_checking_point;
	int amount_of_other_marks = 1;
	int amount_of_other_free_ways_1 = 0;
	is_out = false;
	for (int x = currently_checking_point.x + 1, y = currently_checking_point.y + 1; x < currently_checking_point.x + 5; x++, y++)
	{
		if (is_out) { break; }
		for_calculating.y += 1;
		for_calculating.x += 1;
		if (x <= field_size.max.x && y <= field_size.max.y)
		{
			switch (game.get_state().field.get()->get_value(for_calculating))
			{
			case Mark::Cross:
				if (mark != Mark::Cross)
				{
					amount_of_other_marks += 1;
					amount_of_other_free_ways_1 = (y == field_size.max.y && x == field_size.max.x) ? 0 : 1;
				}
				else
				{
					amount_of_other_free_ways_1 = 0;
					is_out = true;
				}
				break;
			case Mark::Zero:
				if (mark != Mark::Zero)
				{
					amount_of_other_marks += 1;
					amount_of_other_free_ways_1 = (y == field_size.max.y && x == field_size.max.x) ? 0 : 1;
				}
				else
				{
					amount_of_other_free_ways_1 = 0;
					is_out = true;
				}
				break;
			default:
				amount_of_other_free_ways_1 = 1;
				is_out = true;
			}
		}
		else {
			amount_of_other_free_ways_1 = 0;
			is_out = true;
		}
	}
	for_calculating = currently_checking_point;
	int amount_of_other_free_ways_2 = 0;
	is_out = false;
	for (int x = currently_checking_point.x - 1, y = currently_checking_point.y - 1; x > currently_checking_point.x - 5; x--, y--)
	{
		if (is_out) { break; }
		for_calculating.y -= 1;
		for_calculating.x -= 1;
		if (x >= field_size.min.x && y >= field_size.min.y)
		{
			switch (game.get_state().field.get()->get_value(for_calculating))
			{
			case Mark::Cross:
				if (mark != Mark::Cross)
				{
					amount_of_other_marks += 1;
					amount_of_other_free_ways_2 = (y == field_size.min.y && x == field_size.min.x) ? 0 : 1;
				}
				else
				{
					amount_of_other_free_ways_2 = 0;
					is_out = true;
				}
				break;
			case Mark::Zero:
				if (mark != Mark::Zero)
				{
					amount_of_other_marks += 1;
					amount_of_other_free_ways_2 = (y == field_size.min.y && x == field_size.min.x) ? 0 : 1;
				}
				else
				{
					amount_of_other_free_ways_2 = 0;
					is_out = true;
				}
				break;
			default:
				amount_of_other_free_ways_2 = 1;
				is_out = true;
			}
		}
		else {
			amount_of_other_free_ways_2 = 0;
			is_out = true;
		}
	}
	amount_of_other_marks = amount_of_other_marks > 5 ? 5 : amount_of_other_marks;
	calculating_weight += weight_table[amount_of_other_marks][amount_of_other_free_ways_1 + amount_of_other_free_ways_2];
}
void UserPlayer::calculate_weight_diagonal_135(const GameView& game, const Boundary& field_size, Point& currently_checking_point, float& calculating_weight)
{
	Point for_calculating(currently_checking_point);
	int amount_of_this_marks = 1;
	int amount_of_free_ways_1 = 0;
	bool is_out = false;
	for (int x = currently_checking_point.x - 1, y = currently_checking_point.y + 1; x > currently_checking_point.x - 5; x--, y++)
	{
		if (is_out) { break; }
		for_calculating.x -= 1;
		for_calculating.y += 1;
		if (x >= field_size.min.x && y <= field_size.max.y)
		{
			switch (game.get_state().field.get()->get_value(for_calculating))
			{
			case Mark::Cross:
				if (mark == Mark::Cross)
				{
					amount_of_this_marks += 1;
					amount_of_free_ways_1 = (y == field_size.max.y && x == field_size.min.x) ? 0 : 1;
				}
				else
				{
					amount_of_free_ways_1 = 0;
					is_out = true;
				}
				break;
			case Mark::Zero:
				if (mark == Mark::Zero)
				{
					amount_of_this_marks += 1;
					amount_of_free_ways_1 = (y == field_size.max.y && x == field_size.min.x) ? 0 : 1;
				}
				else
				{
					amount_of_free_ways_1 = 0;
					is_out = true;
				}
				break;
			default:
				amount_of_free_ways_1 = 1;
				is_out = true;
			}
		}
		else {
			amount_of_free_ways_1 = 0;
			is_out = true;
		}
	}
	for_calculating = currently_checking_point;
	int amount_of_free_ways_2 = 0;
	is_out = false;
	for (int x = currently_checking_point.x + 1, y = currently_checking_point.y - 1; x < currently_checking_point.x + 5; x++, y--)
	{
		if (is_out) { break; }
		for_calculating.x += 1;
		for_calculating.y -= 1;
		if (x <= field_size.max.x && y >= field_size.min.y)
		{
			switch (game.get_state().field.get()->get_value(for_calculating))
			{
			case Mark::Cross:
				if (mark == Mark::Cross)
				{
					amount_of_this_marks += 1;
					amount_of_free_ways_2 = (y == field_size.min.y && x == field_size.max.x) ? 0 : 1;
				}
				else
				{
					amount_of_free_ways_2 = 0;
					is_out = true;
				}
				break;
			case Mark::Zero:
				if (mark == Mark::Zero)
				{
					amount_of_this_marks += 1;
					amount_of_free_ways_2 = (y == field_size.min.y && x == field_size.max.x) ? 0 : 1;
				}
				else
				{
					amount_of_free_ways_2 = 0;
					is_out = true;
				}
				break;
			default:
				amount_of_free_ways_2 = 1;
				is_out = true;
			}
		}
		else {
			amount_of_free_ways_2 = 0;
			is_out = true;
		}
	}
	amount_of_this_marks = amount_of_this_marks > 5 ? 5 : amount_of_this_marks;
	calculating_weight += weight_table[amount_of_this_marks][amount_of_free_ways_1 + amount_of_free_ways_2];
	// Calculating now weight from the point of view of oponent
	for_calculating = currently_checking_point;
	int amount_of_other_marks = 1;
	int amount_of_other_free_ways_1 = 0;
	is_out = false;
	for (int x = currently_checking_point.x - 1, y = currently_checking_point.y + 1; x > currently_checking_point.x - 5; x--, y++)
	{
		if (is_out) { break; }
		for_calculating.y += 1;
		for_calculating.x -= 1;
		if (x >= field_size.min.x && y <= field_size.max.y)
		{
			switch (game.get_state().field.get()->get_value(for_calculating))
			{
			case Mark::Cross:
				if (mark != Mark::Cross)
				{
					amount_of_other_marks += 1;
					amount_of_other_free_ways_1 = (y == field_size.max.y && x == field_size.min.x) ? 0 : 1;
				}
				else
				{
					amount_of_other_free_ways_1 = 0;
					is_out = true;
				}
				break;
			case Mark::Zero:
				if (mark != Mark::Zero)
				{
					amount_of_other_marks += 1;
					amount_of_other_free_ways_1 = (y == field_size.max.y && x == field_size.min.x) ? 0 : 1;
				}
				else
				{
					amount_of_other_free_ways_1 = 0;
					is_out = true;
				}
				break;
			default:
				amount_of_other_free_ways_1 = 1;
				is_out = true;
			}
		}
		else {
			amount_of_other_free_ways_1 = 0;
			is_out = true;
		}
	}
	for_calculating = currently_checking_point;
	int amount_of_other_free_ways_2 = 0;
	is_out = false;
	for (int x = currently_checking_point.x + 1, y = currently_checking_point.y - 1; x < currently_checking_point.x + 5; x++, y--)
	{
		if (is_out) { break; }
		for_calculating.y -= 1;
		for_calculating.x += 1;
		if (x <= field_size.max.x && y >= field_size.min.y)
		{
			switch (game.get_state().field.get()->get_value(for_calculating))
			{
			case Mark::Cross:
				if (mark != Mark::Cross)
				{
					amount_of_other_marks += 1;
					amount_of_other_free_ways_2 = (y == field_size.min.y && x == field_size.max.x) ? 0 : 1;
				}
				else
				{
					amount_of_other_free_ways_2 = 0;
					is_out = true;
				}
				break;
			case Mark::Zero:
				if (mark != Mark::Zero)
				{
					amount_of_other_marks += 1;
					amount_of_other_free_ways_2 = (y == field_size.min.y && x == field_size.max.x) ? 0 : 1;
				}
				else
				{
					amount_of_other_free_ways_2 = 0;
					is_out = true;
				}
				break;
			default:
				amount_of_other_free_ways_2 = 1;
				is_out = true;
			}
		}
		else {
			amount_of_other_free_ways_2 = 0;
			is_out = true;
		}
	}
	amount_of_other_marks = amount_of_other_marks > 5 ? 5 : amount_of_other_marks;
	calculating_weight += weight_table[amount_of_other_marks][amount_of_other_free_ways_1 + amount_of_other_free_ways_2];
}
void UserPlayer::notify(const GameView& game, const Event& event) {
	//does noting
}
void UserPlayer::change_weight_table(const vector<vector<float>>& new_weight_table) {
	weight_table = new_weight_table;
}