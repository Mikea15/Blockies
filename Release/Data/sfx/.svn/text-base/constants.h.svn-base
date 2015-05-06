

#ifndef H_CONSTANTS
#define H_CONSTANTS

// blocksizes
#define BLOCKSIZE	30
#define NBLOCKW		15
#define NBLOCKH		20
#define NBLOCKS		8
#define	BLOCKGRID	5

// window defines
#define WINHEIGHT	600
#define WINWIDTH	800
#define BPP			32

// image colors
enum { NONE, YELLOW, BLUE, CYAN, PINK, RED, ORANGE, GREEN };

// block types

enum { SQ, I, L, LI, N, NI, T};


// grid size
#define BGSIZE		4
typedef struct Block {
	int x;
	int y;
	int	grid[BGSIZE][BGSIZE];
} Block;

typedef struct PlayerInfo {
	std::string	name;
	int			score;
	int			level;
	int			lines;
	int			time;
} PlayerInfo;


#endif

