#pragma once
class scoreboard
{
public:
	static void collect_statistics();
	static void reset();
	static void reset_fails();
	static int get_gun_triggered();
	static void add_gun_triggered(int count = 1);
	static int get_target_hit();
	static void add_target_hit(int count = 1);
	static double get_accuracy();
	static int get_score();
	static int get_raw_score();
	static void add_score(int value);
private:
	static int gun_triggered;
	static int target_hit;
	static int score;
};
