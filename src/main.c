#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "main.h"

int mouse_pressed = 0;
int key_pressed = 0;
int key;
int running = 0;
long ticks = 0;

void parse_events(SDL_Event *event)
{
    while (SDL_PollEvent(event))
    {
        if (event->type == SDL_QUIT)
            running = 0;
        else if (event->type == SDL_MOUSEBUTTONDOWN)
            mouse_pressed = 1;
        else if (event->type == SDL_MOUSEBUTTONUP)
            mouse_pressed = 0;
        else if (event->type == SDL_KEYDOWN)
        {
            key_pressed = 1;
            key = event->key.keysym.sym;
        }
        else if (event->type == SDL_KEYUP)
        {
            key_pressed = 0;
            key = event->key.keysym.sym;
        }
    }
}

void render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    rotateY(507, head, 0.01);

    drawmesh(507, head, renderer, WIDTH / 2, HEIGHT / 2);

    SDL_RenderPresent(renderer);
}

void drawmesh(const int numVertices, double mesh[numVertices][4], SDL_Renderer *renderer, int x, int y)
{
    SDL_Rect *rects = malloc(sizeof(SDL_Rect) * 507);
    for (int i = 0; i < numVertices; i++)
    {
        rects[i].x = mesh[i][0] + x;
        rects[i].y = mesh[i][1] + y;
        rects[i].w = rects[i].h = 2;
    }
    SDL_RenderDrawRects(renderer, rects, 507);
    free(rects);
}

void matmul(double m1[4], double m2[4][4])
{
    double temp[4];
    for (int y = 0; y < 4; y++)
    {
        double result = 0;
        for (int x = 0; x < 4; x++)
        {
            result += m1[x] * m2[y][x];
        }
        temp[y] = result;
    }
    for (int i = 0; i < 4; i++)
    {
        m1[i] = temp[i];
    }
}

void translate(const int numVertices, double mesh[numVertices][4], double x, double y, double z)
{
    double translation[4][4] = {
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1},
    };
    for (int i = 0; i < numVertices; i++)
        matmul(mesh[i], translation);
}

void scale(const int numVertices, double mesh[numVertices][4], double x, double y, double z)
{
    double scale[4][4] = {
        {x, 0, 0, 0},
        {0, y, 0, 0},
        {0, 0, z, 0},
        {0, 0, 0, 1},
    };
    for (int i = 0; i < numVertices; i++)
        matmul(mesh[i], scale);
}

void rotateX(const int numVertices, double mesh[numVertices][4], double angle)
{
    double rotation[4][4] = {
        {1, 0, 0, 0},
        {0, cos(angle), sin(angle), 0},
        {0, -sin(angle), cos(angle), 0},
        {0, 0, 0, 1},
    };
    for (int i = 0; i < numVertices; i++)
        matmul(mesh[i], rotation);
}

void rotateY(const int numVertices, double mesh[numVertices][4], double angle)
{
    double rotation[4][4] = {
        {cos(angle), 0, -sin(angle), 0},
        {0, 1, 0, 0},
        {sin(angle), 0, cos(angle), 0},
        {0, 0, 0, 1},
    };
    for (int i = 0; i < numVertices; i++)
        matmul(mesh[i], rotation);
}

void rotateZ(const int numVertices, double mesh[numVertices][4], double a)
{
    double rotation[4][4] = {
        {cos(a), sin(a), 0, 0},
        {-sin(a), cos(a), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    };
    for (int i = 0; i < numVertices; i++)
        matmul(mesh[i], rotation);
}

void makePoint(double arr[4], double x, double y, double z, double w)
{
    arr[0] = x;
    arr[1] = y;
    arr[2] = z;
    arr[3] = w;
}

void init()
{
    makePoint(head[0], 1.1330, -0.6526, 1.1641, 1);
    makePoint(head[1], 0.2580, -0.6526, 1.1641, 1);
    makePoint(head[2], 1.1955, -0.5744, 1.0938, 1);
    makePoint(head[3], 0.1955, -0.5744, 1.0938, 1);
    makePoint(head[4], 1.2424, -0.4651, 1.0547, 1);
    makePoint(head[5], 0.1486, -0.4651, 1.0547, 1);
    makePoint(head[6], 1.0471, -0.5041, 0.9766, 1);
    makePoint(head[7], 0.3439, -0.5041, 0.9766, 1);
    makePoint(head[8], 1.0471, -0.6057, 1.0313, 1);
    makePoint(head[9], 0.3439, -0.6057, 1.0313, 1);
    makePoint(head[10], 1.0471, -0.6682, 1.1328, 1);
    makePoint(head[11], 0.3439, -0.6682, 1.1328, 1);
    makePoint(head[12], 0.9689, -0.6838, 1.1641, 1);
    makePoint(head[13], 0.4221, -0.6838, 1.1641, 1);
    makePoint(head[14], 0.8986, -0.6291, 1.0938, 1);
    makePoint(head[15], 0.4924, -0.6291, 1.0938, 1);
    makePoint(head[16], 0.8518, -0.5354, 1.0547, 1);
    makePoint(head[17], 0.5393, -0.5354, 1.0547, 1);
    makePoint(head[18], 0.7736, -0.5432, 1.2422, 1);
    makePoint(head[19], 0.6174, -0.5432, 1.2422, 1);
    makePoint(head[20], 0.8361, -0.6291, 1.2422, 1);
    makePoint(head[21], 0.5549, -0.6291, 1.2422, 1);
    makePoint(head[22], 0.9377, -0.6838, 1.2422, 1);
    makePoint(head[23], 0.4533, -0.6838, 1.2422, 1);
    makePoint(head[24], 0.9689, -0.6838, 1.3281, 1);
    makePoint(head[25], 0.4221, -0.6838, 1.3281, 1);
    makePoint(head[26], 0.8986, -0.6291, 1.3906, 1);
    makePoint(head[27], 0.4924, -0.6291, 1.3906, 1);
    makePoint(head[28], 0.8518, -0.5354, 1.4375, 1);
    makePoint(head[29], 0.5393, -0.5354, 1.4375, 1);
    makePoint(head[30], 1.0471, -0.5041, 1.5156, 1);
    makePoint(head[31], 0.3439, -0.5041, 1.5156, 1);
    makePoint(head[32], 1.0471, -0.6057, 1.4531, 1);
    makePoint(head[33], 0.3439, -0.6057, 1.4531, 1);
    makePoint(head[34], 1.0471, -0.6682, 1.3594, 1);
    makePoint(head[35], 0.3439, -0.6682, 1.3594, 1);
    makePoint(head[36], 1.1330, -0.6526, 1.3281, 1);
    makePoint(head[37], 0.2580, -0.6526, 1.3281, 1);
    makePoint(head[38], 1.1955, -0.5744, 1.3906, 1);
    makePoint(head[39], 0.1955, -0.5744, 1.3906, 1);
    makePoint(head[40], 1.2424, -0.4651, 1.4375, 1);
    makePoint(head[41], 0.1486, -0.4651, 1.4375, 1);
    makePoint(head[42], 1.3205, -0.4494, 1.2422, 1);
    makePoint(head[43], 0.0705, -0.4494, 1.2422, 1);
    makePoint(head[44], 1.2580, -0.5588, 1.2422, 1);
    makePoint(head[45], 0.1330, -0.5588, 1.2422, 1);
    makePoint(head[46], 1.1643, -0.6448, 1.2422, 1);
    makePoint(head[47], 0.2268, -0.6448, 1.2422, 1);
    makePoint(head[48], 1.1721, -0.6604, 1.2422, 1);
    makePoint(head[49], 0.2189, -0.6604, 1.2422, 1);
    makePoint(head[50], 1.1408, -0.6682, 1.3359, 1);
    makePoint(head[51], 0.2502, -0.6682, 1.3359, 1);
    makePoint(head[52], 1.0471, -0.6916, 1.3750, 1);
    makePoint(head[53], 0.3439, -0.6916, 1.3750, 1);
    makePoint(head[54], 0.9611, -0.7073, 1.3359, 1);
    makePoint(head[55], 0.4299, -0.7073, 1.3359, 1);
    makePoint(head[56], 0.9221, -0.7073, 1.2422, 1);
    makePoint(head[57], 0.4689, -0.7073, 1.2422, 1);
    makePoint(head[58], 0.9611, -0.7073, 1.1563, 1);
    makePoint(head[59], 0.4299, -0.7073, 1.1563, 1);
    makePoint(head[60], 1.0471, -0.7151, 1.2422, 1);
    makePoint(head[61], 0.3439, -0.7151, 1.2422, 1);
    makePoint(head[62], 1.0471, -0.6916, 1.1172, 1);
    makePoint(head[63], 0.3439, -0.6916, 1.1172, 1);
    makePoint(head[64], 1.1408, -0.6682, 1.1563, 1);
    makePoint(head[65], 0.2502, -0.6682, 1.1563, 1);
    makePoint(head[66], 0.6955, -0.6291, 1.4297, 1);
    makePoint(head[67], 0.6955, -0.7073, 1.3516, 1);
    makePoint(head[68], 0.6955, -0.6213, 0.3203, 1);
    makePoint(head[69], 0.6955, -0.6682, 0.6797, 1);
    makePoint(head[70], 0.6955, -0.6838, 0.8125, 1);
    makePoint(head[71], 0.6955, -0.6057, 0.2266, 1);
    makePoint(head[72], 0.6955, -0.4885, 1.4063, 1);
    makePoint(head[73], 0.6955, -0.4573, 1.5703, 1);
    makePoint(head[74], 0.6955, 0.6599, 1.8984, 1);
    makePoint(head[75], 0.6955, 0.9646, 1.5625, 1);
    makePoint(head[76], 0.6955, 0.9412, 1.0703, 1);
    makePoint(head[77], 0.6955, 0.4646, 0.6172, 1);
    makePoint(head[78], 0.8986, -0.4494, 0.8125, 1);
    makePoint(head[79], 0.4924, -0.4494, 0.8125, 1);
    makePoint(head[80], 1.0080, -0.4573, 0.5625, 1);
    makePoint(head[81], 0.3830, -0.4573, 0.5625, 1);
    makePoint(head[82], 1.0471, -0.4573, 0.3047, 1);
    makePoint(head[83], 0.3439, -0.4573, 0.3047, 1);
    makePoint(head[84], 1.0627, -0.4182, 0.1094, 1);
    makePoint(head[85], 0.3283, -0.4182, 0.1094, 1);
    makePoint(head[86], 1.0236, -0.4104, 0.0547, 1);
    makePoint(head[87], 0.3674, -0.4104, 0.0547, 1);
    makePoint(head[88], 0.8752, -0.4416, 0.0313, 1);
    makePoint(head[89], 0.5158, -0.4416, 0.0313, 1);
    makePoint(head[90], 0.6955, -0.4651, 0.0156, 1);
    makePoint(head[91], 1.1330, -0.4182, 0.8594, 1);
    makePoint(head[92], 0.2580, -0.4182, 0.8594, 1);
    makePoint(head[93], 1.3283, -0.4260, 0.9609, 1);
    makePoint(head[94], 0.0627, -0.4260, 0.9609, 1);
    makePoint(head[95], 1.5236, -0.3323, 1.1484, 1);
    makePoint(head[96], -0.1326, -0.3323, 1.1484, 1);
    makePoint(head[97], 1.5549, -0.4807, 1.4297, 1);
    makePoint(head[98], -0.1639, -0.4807, 1.4297, 1);
    makePoint(head[99], 1.4064, -0.5119, 1.4844, 1);
    makePoint(head[100], -0.0154, -0.5119, 1.4844, 1);
    makePoint(head[101], 1.1877, -0.5744, 1.6016, 1);
    makePoint(head[102], 0.2033, -0.5744, 1.6016, 1);
    makePoint(head[103], 1.0158, -0.6213, 1.7578, 1);
    makePoint(head[104], 0.3752, -0.6213, 1.7578, 1);
    makePoint(head[105], 0.8518, -0.6448, 1.7188, 1);
    makePoint(head[106], 0.5393, -0.6448, 1.7188, 1);
    makePoint(head[107], 0.7580, -0.6369, 1.4922, 1);
    makePoint(head[108], 0.6330, -0.6369, 1.4922, 1);
    makePoint(head[109], 0.8596, -0.6604, 1.4141, 1);
    makePoint(head[110], 0.5314, -0.6604, 1.4141, 1);
    makePoint(head[111], 0.8205, -0.6526, 1.3047, 1);
    makePoint(head[112], 0.5705, -0.6526, 1.3047, 1);
    makePoint(head[113], 0.8986, -0.6291, 1.0938, 1);
    makePoint(head[114], 0.4924, -0.6291, 1.0938, 1);
    makePoint(head[115], 1.0705, -0.5901, 1.0156, 1);
    makePoint(head[116], 0.3205, -0.5901, 1.0156, 1);
    makePoint(head[117], 1.1877, -0.5588, 1.0625, 1);
    makePoint(head[118], 0.2033, -0.5588, 1.0625, 1);
    makePoint(head[119], 1.3205, -0.5354, 1.1875, 1);
    makePoint(head[120], 0.0705, -0.5354, 1.1875, 1);
    makePoint(head[121], 1.3361, -0.5354, 1.2969, 1);
    makePoint(head[122], 0.0549, -0.5354, 1.2969, 1);
    makePoint(head[123], 1.2971, -0.5510, 1.3750, 1);
    makePoint(head[124], 0.0939, -0.5510, 1.3750, 1);
    makePoint(head[125], 1.1252, -0.6057, 1.4375, 1);
    makePoint(head[126], 0.2658, -0.6057, 1.4375, 1);
    makePoint(head[127], 0.9455, -0.6448, 1.4688, 1);
    makePoint(head[128], 0.4455, -0.6448, 1.4688, 1);
    makePoint(head[129], 0.6955, -0.6213, 0.2344, 1);
    makePoint(head[130], 0.8049, -0.6213, 0.2813, 1);
    makePoint(head[131], 0.5861, -0.6213, 0.2813, 1);
    makePoint(head[132], 0.8127, -0.5979, 0.1641, 1);
    makePoint(head[133], 0.5783, -0.5979, 0.1641, 1);
    makePoint(head[134], 0.7580, -0.5823, 0.1172, 1);
    makePoint(head[135], 0.6330, -0.5823, 0.1172, 1);
    makePoint(head[136], 0.6955, -0.5744, 0.1094, 1);
    makePoint(head[137], 0.6955, -0.6369, 0.8047, 1);
    makePoint(head[138], 0.6955, -0.6291, 0.8594, 1);
    makePoint(head[139], 0.7971, -0.6291, 0.8516, 1);
    makePoint(head[140], 0.5939, -0.6291, 0.8516, 1);
    makePoint(head[141], 0.8205, -0.6369, 0.7734, 1);
    makePoint(head[142], 0.5705, -0.6369, 0.7734, 1);
    makePoint(head[143], 0.7814, -0.6291, 0.7109, 1);
    makePoint(head[144], 0.6096, -0.6291, 0.7109, 1);
    makePoint(head[145], 1.0939, -0.5588, 0.9531, 1);
    makePoint(head[146], 0.2971, -0.5588, 0.9531, 1);
    makePoint(head[147], 1.3127, -0.5119, 1.0547, 1);
    makePoint(head[148], 0.0783, -0.5119, 1.0547, 1);
    makePoint(head[149], 1.4221, -0.4885, 1.2031, 1);
    makePoint(head[150], -0.0311, -0.4885, 1.2031, 1);
    makePoint(head[151], 1.4377, -0.5432, 1.3750, 1);
    makePoint(head[152], -0.0467, -0.5432, 1.3750, 1);
    makePoint(head[153], 1.3830, -0.6135, 1.4141, 1);
    makePoint(head[154], 0.0080, -0.6135, 1.4141, 1);
    makePoint(head[155], 1.1330, -0.6838, 1.5469, 1);
    makePoint(head[156], 0.2580, -0.6838, 1.5469, 1);
    makePoint(head[157], 1.0080, -0.7229, 1.6406, 1);
    makePoint(head[158], 0.3830, -0.7229, 1.6406, 1);
    makePoint(head[159], 0.8986, -0.7385, 1.6172, 1);
    makePoint(head[160], 0.4924, -0.7385, 1.6172, 1);
    makePoint(head[161], 0.7971, -0.7307, 1.4297, 1);
    makePoint(head[162], 0.5939, -0.7307, 1.4297, 1);
    makePoint(head[163], 0.8205, -0.6994, 0.8984, 1);
    makePoint(head[164], 0.5705, -0.6994, 0.8984, 1);
    makePoint(head[165], 0.9064, -0.5979, 0.5547, 1);
    makePoint(head[166], 0.4846, -0.5979, 0.5547, 1);
    makePoint(head[167], 0.9455, -0.5744, 0.2969, 1);
    makePoint(head[168], 0.4455, -0.5744, 0.2969, 1);
    makePoint(head[169], 0.9611, -0.5510, 0.1797, 1);
    makePoint(head[170], 0.4299, -0.5510, 0.1797, 1);
    makePoint(head[171], 0.9299, -0.5198, 0.0859, 1);
    makePoint(head[172], 0.4611, -0.5198, 0.0859, 1);
    makePoint(head[173], 0.8596, -0.5198, 0.0703, 1);
    makePoint(head[174], 0.5314, -0.5198, 0.0703, 1);
    makePoint(head[175], 0.6955, -0.5276, 0.0547, 1);
    makePoint(head[176], 0.6955, -0.6135, 1.0469, 1);
    makePoint(head[177], 0.6955, -0.6526, 1.2109, 1);
    makePoint(head[178], 1.0236, -0.6291, 1.4766, 1);
    makePoint(head[179], 0.3674, -0.6291, 1.4766, 1);
    makePoint(head[180], 0.8596, -0.6369, 1.1406, 1);
    makePoint(head[181], 0.5314, -0.6369, 1.1406, 1);
    makePoint(head[182], 0.8283, -0.6448, 1.2109, 1);
    makePoint(head[183], 0.5627, -0.6448, 1.2109, 1);
    makePoint(head[184], 0.8127, -0.6213, 0.3125, 1);
    makePoint(head[185], 0.5783, -0.6213, 0.3125, 1);
    makePoint(head[186], 0.7736, -0.6369, 0.5547, 1);
    makePoint(head[187], 0.6174, -0.6369, 0.5547, 1);
    makePoint(head[188], 0.6955, -0.6369, 0.5547, 1);
    makePoint(head[189], 0.6955, -0.6291, 0.6719, 1);
    makePoint(head[190], 0.7893, -0.6682, 0.7266, 1);
    makePoint(head[191], 0.6018, -0.6682, 0.7266, 1);
    makePoint(head[192], 0.8283, -0.6838, 0.7734, 1);
    makePoint(head[193], 0.5627, -0.6838, 0.7734, 1);
    makePoint(head[194], 0.8049, -0.6682, 0.8672, 1);
    makePoint(head[195], 0.5861, -0.6682, 0.8672, 1);
    makePoint(head[196], 0.7346, -0.6682, 0.8750, 1);
    makePoint(head[197], 0.6564, -0.6682, 0.8750, 1);
    makePoint(head[198], 0.6955, -0.7151, 0.7969, 1);
    makePoint(head[199], 0.7424, -0.6994, 0.8516, 1);
    makePoint(head[200], 0.6486, -0.6994, 0.8516, 1);
    makePoint(head[201], 0.7893, -0.6994, 0.8438, 1);
    makePoint(head[202], 0.6018, -0.6994, 0.8438, 1);
    makePoint(head[203], 0.8049, -0.7151, 0.7734, 1);
    makePoint(head[204], 0.5861, -0.7151, 0.7734, 1);
    makePoint(head[205], 0.7736, -0.6916, 0.7500, 1);
    makePoint(head[206], 0.6174, -0.6916, 0.7500, 1);
    makePoint(head[207], 0.6955, -0.6916, 0.7109, 1);
    makePoint(head[208], 0.9533, -0.4416, 0.6875, 1);
    makePoint(head[209], 0.4377, -0.4416, 0.6875, 1);
    makePoint(head[210], 0.8596, -0.5979, 0.7578, 1);
    makePoint(head[211], 0.5314, -0.5979, 0.7578, 1);
    makePoint(head[212], 0.8752, -0.5979, 0.6875, 1);
    makePoint(head[213], 0.5158, -0.5979, 0.6875, 1);
    makePoint(head[214], 0.9299, -0.4416, 0.7500, 1);
    makePoint(head[215], 0.4611, -0.4416, 0.7500, 1);
    makePoint(head[216], 0.6955, -0.5744, 0.1250, 1);
    makePoint(head[217], 0.7424, -0.5744, 0.1328, 1);
    makePoint(head[218], 0.6486, -0.5744, 0.1328, 1);
    makePoint(head[219], 0.7893, -0.5979, 0.1797, 1);
    makePoint(head[220], 0.6018, -0.5979, 0.1797, 1);
    makePoint(head[221], 0.7893, -0.6135, 0.2578, 1);
    makePoint(head[222], 0.6018, -0.6135, 0.2578, 1);
    makePoint(head[223], 0.6955, -0.5432, 0.2188, 1);
    makePoint(head[224], 0.7893, -0.5510, 0.2500, 1);
    makePoint(head[225], 0.6018, -0.5510, 0.2500, 1);
    makePoint(head[226], 0.7893, -0.5276, 0.1875, 1);
    makePoint(head[227], 0.6018, -0.5276, 0.1875, 1);
    makePoint(head[228], 0.7424, -0.5198, 0.1484, 1);
    makePoint(head[229], 0.6486, -0.5198, 0.1484, 1);
    makePoint(head[230], 0.6955, -0.5198, 0.1406, 1);
    makePoint(head[231], 0.8674, -0.6682, 1.2188, 1);
    makePoint(head[232], 0.5236, -0.6682, 1.2188, 1);
    makePoint(head[233], 0.8830, -0.6604, 1.1563, 1);
    makePoint(head[234], 0.5080, -0.6604, 1.1563, 1);
    makePoint(head[235], 1.0314, -0.6448, 1.4297, 1);
    makePoint(head[236], 0.3596, -0.6448, 1.4297, 1);
    makePoint(head[237], 0.9689, -0.6604, 1.4219, 1);
    makePoint(head[238], 0.4221, -0.6604, 1.4219, 1);
    makePoint(head[239], 1.1174, -0.6604, 1.3984, 1);
    makePoint(head[240], 0.2736, -0.6604, 1.3984, 1);
    makePoint(head[241], 1.2580, -0.5823, 1.3516, 1);
    makePoint(head[242], 0.1330, -0.5823, 1.3516, 1);
    makePoint(head[243], 1.2814, -0.5744, 1.2891, 1);
    makePoint(head[244], 0.1096, -0.5744, 1.2891, 1);
    makePoint(head[245], 1.2736, -0.5666, 1.1953, 1);
    makePoint(head[246], 0.1174, -0.5666, 1.1953, 1);
    makePoint(head[247], 1.1721, -0.6057, 1.1016, 1);
    makePoint(head[248], 0.2189, -0.6057, 1.1016, 1);
    makePoint(head[249], 1.0705, -0.6291, 1.0625, 1);
    makePoint(head[250], 0.3205, -0.6291, 1.0625, 1);
    makePoint(head[251], 0.9221, -0.6682, 1.1094, 1);
    makePoint(head[252], 0.4689, -0.6682, 1.1094, 1);
    makePoint(head[253], 0.8752, -0.6682, 1.2969, 1);
    makePoint(head[254], 0.5158, -0.6682, 1.2969, 1);
    makePoint(head[255], 0.9064, -0.6682, 1.3750, 1);
    makePoint(head[256], 0.4846, -0.6682, 1.3750, 1);
    makePoint(head[257], 0.9299, -0.6448, 1.3594, 1);
    makePoint(head[258], 0.4611, -0.6448, 1.3594, 1);
    makePoint(head[259], 0.8908, -0.6448, 1.2969, 1);
    makePoint(head[260], 0.5002, -0.6448, 1.2969, 1);
    makePoint(head[261], 0.9377, -0.6448, 1.1250, 1);
    makePoint(head[262], 0.4533, -0.6448, 1.1250, 1);
    makePoint(head[263], 1.0705, -0.6135, 1.0859, 1);
    makePoint(head[264], 0.3205, -0.6135, 1.0859, 1);
    makePoint(head[265], 1.1564, -0.5901, 1.1172, 1);
    makePoint(head[266], 0.2346, -0.5901, 1.1172, 1);
    makePoint(head[267], 1.2424, -0.5588, 1.2109, 1);
    makePoint(head[268], 0.1486, -0.5588, 1.2109, 1);
    makePoint(head[269], 1.2502, -0.5588, 1.2813, 1);
    makePoint(head[270], 0.1408, -0.5588, 1.2813, 1);
    makePoint(head[271], 1.2268, -0.5666, 1.3359, 1);
    makePoint(head[272], 0.1643, -0.5666, 1.3359, 1);
    makePoint(head[273], 1.1096, -0.6369, 1.3906, 1);
    makePoint(head[274], 0.2814, -0.6369, 1.3906, 1);
    makePoint(head[275], 0.9768, -0.6526, 1.3984, 1);
    makePoint(head[276], 0.4143, -0.6526, 1.3984, 1);
    makePoint(head[277], 1.0314, -0.6369, 1.4063, 1);
    makePoint(head[278], 0.3596, -0.6369, 1.4063, 1);
    makePoint(head[279], 0.8986, -0.6369, 1.1719, 1);
    makePoint(head[280], 0.4924, -0.6369, 1.1719, 1);
    makePoint(head[281], 0.8908, -0.6369, 1.2266, 1);
    makePoint(head[282], 0.5002, -0.6369, 1.2266, 1);
    makePoint(head[283], 0.8049, -0.4963, 1.4609, 1);
    makePoint(head[284], 0.5861, -0.4963, 1.4609, 1);
    makePoint(head[285], 0.8908, -0.5041, 1.6641, 1);
    makePoint(head[286], 0.5002, -0.5041, 1.6641, 1);
    makePoint(head[287], 1.0314, -0.4807, 1.6875, 1);
    makePoint(head[288], 0.3596, -0.4807, 1.6875, 1);
    makePoint(head[289], 1.1799, -0.4416, 1.5547, 1);
    makePoint(head[290], 0.2111, -0.4416, 1.5547, 1);
    makePoint(head[291], 1.3752, -0.3791, 1.4531, 1);
    makePoint(head[292], 0.0158, -0.3791, 1.4531, 1);
    makePoint(head[293], 1.4924, -0.3479, 1.4063, 1);
    makePoint(head[294], -0.1014, -0.3479, 1.4063, 1);
    makePoint(head[295], 1.4689, -0.2619, 1.1641, 1);
    makePoint(head[296], -0.0779, -0.2619, 1.1641, 1);
    makePoint(head[297], 1.2971, -0.3010, 1.0000, 1);
    makePoint(head[298], 0.0939, -0.3010, 1.0000, 1);
    makePoint(head[299], 1.1330, -0.3557, 0.9063, 1);
    makePoint(head[300], 0.2580, -0.3557, 0.9063, 1);
    makePoint(head[301], 0.6955, -0.1760, 1.8984, 1);
    makePoint(head[302], 0.6955, 0.1912, 1.9844, 1);
    makePoint(head[303], 0.6955, 0.7849, 0.8047, 1);
    makePoint(head[304], 0.6955, -0.0744, 0.5391, 1);
    makePoint(head[305], 0.6955, -0.3479, 0.0234, 1);
    makePoint(head[306], 0.6955, -0.2307, 0.1953, 1);
    makePoint(head[307], 0.6955, -0.2073, 0.4297, 1);
    makePoint(head[308], 0.6955, -0.1682, 0.5156, 1);
    makePoint(head[309], 1.5471, 0.0584, 1.2344, 1);
    makePoint(head[310], -0.1561, 0.0584, 1.2344, 1);
    makePoint(head[311], 1.5549, 0.1599, 1.3203, 1);
    makePoint(head[312], -0.1639, 0.1599, 1.3203, 1);
    makePoint(head[313], 1.4689, 0.5506, 1.2656, 1);
    makePoint(head[314], -0.0779, 0.5506, 1.2656, 1);
    makePoint(head[315], 1.1564, 0.8162, 1.4375, 1);
    makePoint(head[316], 0.2346, 0.8162, 1.4375, 1);
    makePoint(head[317], 1.4299, 0.0427, 0.9531, 1);
    makePoint(head[318], -0.0389, 0.0427, 0.9531, 1);
    makePoint(head[319], 1.2893, 0.2771, 0.8750, 1);
    makePoint(head[320], 0.1018, 0.2771, 0.8750, 1);
    makePoint(head[321], 1.3361, 0.5427, 0.9922, 1);
    makePoint(head[322], 0.0549, 0.5427, 0.9922, 1);
    makePoint(head[323], 1.0314, 0.7771, 1.0547, 1);
    makePoint(head[324], 0.3596, 0.7771, 1.0547, 1);
    makePoint(head[325], 0.9299, -0.2932, 0.6484, 1);
    makePoint(head[326], 0.4611, -0.2932, 0.6484, 1);
    makePoint(head[327], 0.8752, -0.1448, 0.5859, 1);
    makePoint(head[328], 0.5158, -0.1448, 0.5859, 1);
    makePoint(head[329], 0.9846, -0.2698, 0.2891, 1);
    makePoint(head[330], 0.4064, -0.2698, 0.2891, 1);
    makePoint(head[331], 0.9455, -0.2776, 0.5000, 1);
    makePoint(head[332], 0.4455, -0.2776, 0.5000, 1);
    makePoint(head[333], 1.0236, -0.2854, 0.0859, 1);
    makePoint(head[334], 0.3674, -0.2854, 0.0859, 1);
    makePoint(head[335], 0.8361, -0.2541, 0.2422, 1);
    makePoint(head[336], 0.5549, -0.2541, 0.2422, 1);
    makePoint(head[337], 0.8205, -0.2463, 0.4609, 1);
    makePoint(head[338], 0.5705, -0.2463, 0.4609, 1);
    makePoint(head[339], 0.8596, -0.3244, 0.0547, 1);
    makePoint(head[340], 0.5314, -0.3244, 0.0547, 1);
    makePoint(head[341], 0.9143, -0.3166, 0.7188, 1);
    makePoint(head[342], 0.4768, -0.3166, 0.7188, 1);
    makePoint(head[343], 0.9064, -0.3557, 0.7734, 1);
    makePoint(head[344], 0.4846, -0.3557, 0.7734, 1);
    makePoint(head[345], 0.8986, -0.3869, 0.8281, 1);
    makePoint(head[346], 0.4924, -0.3869, 0.8281, 1);
    makePoint(head[347], 0.9064, -0.0510, 0.6094, 1);
    makePoint(head[348], 0.4846, -0.0510, 0.6094, 1);
    makePoint(head[349], 0.9924, 0.3787, 0.6875, 1);
    makePoint(head[350], 0.3986, 0.3787, 0.6875, 1);
    makePoint(head[351], 1.0393, 0.6521, 0.8516, 1);
    makePoint(head[352], 0.3518, 0.6521, 0.8516, 1);
    makePoint(head[353], 1.1486, 0.4959, 1.8672, 1);
    makePoint(head[354], 0.2424, 0.4959, 1.8672, 1);
    makePoint(head[355], 1.1486, 0.1834, 1.9297, 1);
    makePoint(head[356], 0.2424, 0.1834, 1.9297, 1);
    makePoint(head[357], 1.1486, -0.1213, 1.8516, 1);
    makePoint(head[358], 0.2424, -0.1213, 1.8516, 1);
    makePoint(head[359], 1.1564, -0.3166, 1.5234, 1);
    makePoint(head[360], 0.2346, -0.3166, 1.5234, 1);
    makePoint(head[361], 1.4221, -0.2229, 1.4063, 1);
    makePoint(head[362], -0.0311, -0.2229, 1.4063, 1);
    makePoint(head[363], 1.3283, -0.1682, 1.4531, 1);
    makePoint(head[364], 0.0627, -0.1682, 1.4531, 1);
    makePoint(head[365], 1.3361, 0.0584, 1.7031, 1);
    makePoint(head[366], 0.0549, 0.0584, 1.7031, 1);
    makePoint(head[367], 1.4924, -0.0119, 1.5625, 1);
    makePoint(head[368], -0.1014, -0.0119, 1.5625, 1);
    makePoint(head[369], 1.4924, 0.2302, 1.6172, 1);
    makePoint(head[370], -0.1014, 0.2302, 1.6172, 1);
    makePoint(head[371], 1.3361, 0.3084, 1.7500, 1);
    makePoint(head[372], 0.0549, 0.3084, 1.7500, 1);
    makePoint(head[373], 1.3361, 0.5584, 1.6797, 1);
    makePoint(head[374], 0.0549, 0.5584, 1.6797, 1);
    makePoint(head[375], 1.4924, 0.4724, 1.5391, 1);
    makePoint(head[376], -0.1014, 0.4724, 1.5391, 1);
    makePoint(head[377], 1.3127, 0.6990, 1.3281, 1);
    makePoint(head[378], 0.0783, 0.6990, 1.3281, 1);
    makePoint(head[379], 1.1799, 0.6599, 1.0234, 1);
    makePoint(head[380], 0.2111, 0.6599, 1.0234, 1);
    makePoint(head[381], 1.5158, 0.3162, 1.3281, 1);
    makePoint(head[382], -0.1248, 0.3162, 1.3281, 1);
    makePoint(head[383], 1.1018, -0.0354, 0.8281, 1);
    makePoint(head[384], 0.2893, -0.0354, 0.8281, 1);
    makePoint(head[385], 1.1252, 0.3240, 0.8047, 1);
    makePoint(head[386], 0.2658, 0.3240, 0.8047, 1);
    makePoint(head[387], 1.5861, 0.3474, 1.4063, 1);
    makePoint(head[388], -0.1951, 0.3474, 1.4063, 1);
    makePoint(head[389], 1.4689, 0.2381, 0.8594, 1);
    makePoint(head[390], -0.0779, 0.2381, 0.8594, 1);
    makePoint(head[391], 1.7346, 0.4412, 0.8984, 1);
    makePoint(head[392], -0.3436, 0.4412, 0.8984, 1);
    makePoint(head[393], 1.9768, 0.5427, 1.0547, 1);
    makePoint(head[394], -0.5857, 0.5427, 1.0547, 1);
    makePoint(head[395], 2.0471, 0.5349, 1.3203, 1);
    makePoint(head[396], -0.6561, 0.5349, 1.3203, 1);
    makePoint(head[397], 1.9299, 0.5349, 1.5078, 1);
    makePoint(head[398], -0.5389, 0.5349, 1.5078, 1);
    makePoint(head[399], 1.7189, 0.4256, 1.4766, 1);
    makePoint(head[400], -0.3279, 0.4256, 1.4766, 1);
    makePoint(head[401], 1.7111, 0.4021, 1.4141, 1);
    makePoint(head[402], -0.3201, 0.4021, 1.4141, 1);
    makePoint(head[403], 1.8830, 0.5037, 1.4375, 1);
    makePoint(head[404], -0.4920, 0.5037, 1.4375, 1);
    makePoint(head[405], 1.9611, 0.5193, 1.2891, 1);
    makePoint(head[406], -0.5701, 0.5193, 1.2891, 1);
    makePoint(head[407], 1.9064, 0.5193, 1.0781, 1);
    makePoint(head[408], -0.5154, 0.5193, 1.0781, 1);
    makePoint(head[409], 1.7268, 0.4177, 0.9609, 1);
    makePoint(head[410], -0.3357, 0.4177, 0.9609, 1);
    makePoint(head[411], 1.5236, 0.2459, 0.9297, 1);
    makePoint(head[412], -0.1326, 0.2459, 0.9297, 1);
    makePoint(head[413], 1.6174, 0.3318, 1.3594, 1);
    makePoint(head[414], -0.2264, 0.3318, 1.3594, 1);
    makePoint(head[415], 1.6408, 0.4021, 1.3047, 1);
    makePoint(head[416], -0.2498, 0.4021, 1.3047, 1);
    makePoint(head[417], 1.5783, 0.3240, 0.9766, 1);
    makePoint(head[418], -0.1873, 0.3240, 0.9766, 1);
    makePoint(head[419], 1.7346, 0.4802, 1.0000, 1);
    makePoint(head[420], -0.3436, 0.4802, 1.0000, 1);
    makePoint(head[421], 1.8830, 0.5584, 1.0938, 1);
    makePoint(head[422], -0.4920, 0.5584, 1.0938, 1);
    makePoint(head[423], 1.9299, 0.5584, 1.2500, 1);
    makePoint(head[424], -0.5389, 0.5584, 1.2500, 1);
    makePoint(head[425], 1.8674, 0.5506, 1.3594, 1);
    makePoint(head[426], -0.4764, 0.5506, 1.3594, 1);
    makePoint(head[427], 1.7189, 0.4724, 1.3438, 1);
    makePoint(head[428], -0.3279, 0.4724, 1.3438, 1);
    makePoint(head[429], 1.5393, 0.3240, 1.2891, 1);
    makePoint(head[430], -0.1482, 0.3240, 1.2891, 1);
    makePoint(head[431], 1.5314, 0.3865, 1.1719, 1);
    makePoint(head[432], -0.1404, 0.3865, 1.1719, 1);
    makePoint(head[433], 1.4533, 0.3865, 1.0938, 1);
    makePoint(head[434], -0.0623, 0.3865, 1.0938, 1);
    makePoint(head[435], 1.5158, 0.3865, 1.0859, 1);
    makePoint(head[436], -0.1248, 0.3865, 1.0859, 1);
    makePoint(head[437], 1.5393, 0.3865, 1.0156, 1);
    makePoint(head[438], -0.1482, 0.3865, 1.0156, 1);
    makePoint(head[439], 1.5080, 0.3865, 0.9844, 1);
    makePoint(head[440], -0.1170, 0.3865, 0.9844, 1);
    makePoint(head[441], 1.4221, 0.1834, 1.0000, 1);
    makePoint(head[442], -0.0311, 0.1834, 1.0000, 1);
    makePoint(head[443], 1.4143, 0.2849, 0.9766, 1);
    makePoint(head[444], -0.0232, 0.2849, 0.9766, 1);
    makePoint(head[445], 1.4143, 0.3006, 1.0391, 1);
    makePoint(head[446], -0.0232, 0.3006, 1.0391, 1);
    makePoint(head[447], 1.4924, 0.3240, 1.2031, 1);
    makePoint(head[448], -0.1014, 0.3240, 1.2031, 1);
    makePoint(head[449], 1.5861, 0.3787, 1.2422, 1);
    makePoint(head[450], -0.1951, 0.3787, 1.2422, 1);
    makePoint(head[451], 1.5861, 0.4334, 1.2344, 1);
    makePoint(head[452], -0.1951, 0.4334, 1.2344, 1);
    makePoint(head[453], 1.5080, 0.4334, 0.9844, 1);
    makePoint(head[454], -0.1170, 0.4334, 0.9844, 1);
    makePoint(head[455], 1.5471, 0.4334, 1.0156, 1);
    makePoint(head[456], -0.1561, 0.4334, 1.0156, 1);
    makePoint(head[457], 1.5236, 0.4334, 1.0781, 1);
    makePoint(head[458], -0.1326, 0.4334, 1.0781, 1);
    makePoint(head[459], 1.4611, 0.4334, 1.0938, 1);
    makePoint(head[460], -0.0701, 0.4334, 1.0938, 1);
    makePoint(head[461], 1.5393, 0.4334, 1.1719, 1);
    makePoint(head[462], -0.1482, 0.4334, 1.1719, 1);
    makePoint(head[463], 1.7346, 0.5271, 1.3281, 1);
    makePoint(head[464], -0.3436, 0.5271, 1.3281, 1);
    makePoint(head[465], 1.8830, 0.5974, 1.3438, 1);
    makePoint(head[466], -0.4920, 0.5974, 1.3438, 1);
    makePoint(head[467], 1.9533, 0.6052, 1.2422, 1);
    makePoint(head[468], -0.5623, 0.6052, 1.2422, 1);
    makePoint(head[469], 1.9064, 0.5974, 1.0859, 1);
    makePoint(head[470], -0.5154, 0.5974, 1.0859, 1);
    makePoint(head[471], 1.7424, 0.5349, 1.0000, 1);
    makePoint(head[472], -0.3514, 0.5349, 1.0000, 1);
    makePoint(head[473], 1.5783, 0.3787, 0.9844, 1);
    makePoint(head[474], -0.1873, 0.3787, 0.9844, 1);
    makePoint(head[475], 1.6486, 0.4568, 1.2891, 1);
    makePoint(head[476], -0.2576, 0.4568, 1.2891, 1);
    makePoint(head[477], 1.5861, 0.4412, 1.1094, 1);
    makePoint(head[478], -0.1951, 0.4412, 1.1094, 1);
    makePoint(head[479], 1.6330, 0.4490, 1.0625, 1);
    makePoint(head[480], -0.2420, 0.4490, 1.0625, 1);
    makePoint(head[481], 1.6955, 0.4802, 1.1250, 1);
    makePoint(head[482], -0.3045, 0.4802, 1.1250, 1);
    makePoint(head[483], 1.6564, 0.4646, 1.1719, 1);
    makePoint(head[484], -0.2654, 0.4646, 1.1719, 1);
    makePoint(head[485], 1.7111, 0.4881, 1.2344, 1);
    makePoint(head[486], -0.3201, 0.4881, 1.2344, 1);
    makePoint(head[487], 1.7502, 0.4959, 1.1875, 1);
    makePoint(head[488], -0.3592, 0.4959, 1.1875, 1);
    makePoint(head[489], 1.8049, 0.5037, 1.2109, 1);
    makePoint(head[490], -0.4139, 0.5037, 1.2109, 1);
    makePoint(head[491], 1.7814, 0.5037, 1.2734, 1);
    makePoint(head[492], -0.3904, 0.5037, 1.2734, 1);
    makePoint(head[493], 1.7189, 0.5974, 1.4375, 1);
    makePoint(head[494], -0.3279, 0.5974, 1.4375, 1);
    makePoint(head[495], 1.9455, 0.6599, 1.4688, 1);
    makePoint(head[496], -0.5545, 0.6599, 1.4688, 1);
    makePoint(head[497], 2.0627, 0.6131, 1.2969, 1);
    makePoint(head[498], -0.6717, 0.6131, 1.2969, 1);
    makePoint(head[499], 2.0080, 0.6443, 1.0547, 1);
    makePoint(head[500], -0.6170, 0.6443, 1.0547, 1);
    makePoint(head[501], 1.7346, 0.6052, 0.9141, 1);
    makePoint(head[502], -0.3436, 0.6052, 0.9141, 1);
    makePoint(head[503], 1.4846, 0.4412, 0.8750, 1);
    makePoint(head[504], -0.0936, 0.4412, 0.8750, 1);
    makePoint(head[505], 1.5549, 0.4959, 1.3828, 1);
    makePoint(head[506], -0.1639, 0.4959, 1.3828, 1);
    scale(507, head, 100, 100, 100);
    rotateX(507, head, 4.8);
    translate(507, head, -60, 70, 0);
}

int main(int argv, char *args[])
{
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_OPENGL, &window, &renderer);
    init();
    running = 1;
    SDL_Event event;
    while (running)
    {
        parse_events(&event);
        if (ticks + 1000 / FPS > SDL_GetTicks())
            continue;
        ticks = SDL_GetTicks();
        render(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}