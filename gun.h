#pragma once
class gun
{
public:
	static int reticle_handle;
	static void handle_left();
	static void release_left();
	static void handle_right();
	static void release_right();
	static void draw_reticle();
	static bool is_locked();
	static void lock();
	static void unlock();
private:
	static bool locked;
};

