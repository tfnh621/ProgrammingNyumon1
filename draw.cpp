#include "draw.h"
#include <cstring>

void draw::graph(int x, int y, int graph_handle, int transparent_flag)
{
	int width, height;
	GetGraphSize(graph_handle, &width, &height);
	DrawGraph(x - width / 2, y - height / 2, graph_handle, transparent_flag);
}

void draw::sphere_3d(VECTOR center, float r, int polygon, COLOR_F color, int fill)
{
	MATERIALPARAM material;
	material.Diffuse = color;
	material.Ambient = color;
	material.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	material.Emissive = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	SetMaterialParam(material);
	DrawSphere3D(center, r, polygon, GetColor(200, 200, 200), NULL, fill);
}

void draw::chara(int x, int y, const char* str, unsigned int color, int font, int size, unsigned int edge_color)
{
	int length = static_cast<int>(strlen(str));
	float cx = static_cast<float>(x) - (length / 2.0f) * (size / 2.0f);
	float cy = static_cast<float>(y) - size / 2.0f;
	DrawStringFToHandle(cx, cy, str, color, font, edge_color);
}
