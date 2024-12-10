#pragma once
class font
{
public:
	static void init();
	static int title;
	static int settings;
	static int timer;
	static int result;
};

class fontsize
{
public:
	static const int title = 128;
	static const int settings = 24;
	static const int timer = 50;
	static const int result = 256;
};
