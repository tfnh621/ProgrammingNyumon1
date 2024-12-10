#include "scoreboard.h"
#include <Windows.h>
#include <lmcons.h>

int scoreboard::gun_triggered = 0;
int scoreboard::target_hit = 0;
int scoreboard::score = 0;

void scoreboard::collect_statistics()
{
	// TODO

	char username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserName(username, &username_len);

	char computername[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD len = MAX_COMPUTERNAME_LENGTH + 1;
	GetComputerName(computername, &len);
}

void scoreboard::reset()
{
	gun_triggered = 0;
	target_hit = 0;
	score = 0;
}

void scoreboard::reset_fails()
{
	gun_triggered = target_hit;
}

int scoreboard::get_gun_triggered()
{
	return gun_triggered;
}

void scoreboard::add_gun_triggered(int count)
{
	gun_triggered += count;
}

int scoreboard::get_target_hit()
{
	return target_hit;
}

void scoreboard::add_target_hit(int count)
{
	target_hit += count;
}

double scoreboard::get_accuracy()
{
	return (double)target_hit / (gun_triggered != 0 ? gun_triggered : 1);
}

int scoreboard::get_score()
{
	return (int)(score * get_accuracy());
}

int scoreboard::get_raw_score()
{
	return score;
}

void scoreboard::add_score(int value)
{
	score += value;
}
