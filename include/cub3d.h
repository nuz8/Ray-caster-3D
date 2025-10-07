/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:42:58 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/10/07 08:06:11 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/includes/libft.h"
# include "../lib/includes/ft_printf.h"
# include "../lib/includes/get_next_line.h"
# include "../lib/includes/garbage_collector.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <math.h>

/******************************************************************************/
/********     COLORS     ******************************************************/
/******************************************************************************/

// Colors
# define WHITE			0xFFFFFFFF
# define RED			0xFF0000FF
# define GREEN			0x00FF00FF
# define BLUE			0x0000FFFF
# define YELLOW			0xFFFF00FF
# define CYAN			0x00FFFFFF
# define MAGENTA		0xFF00FFFF
# define RESET			0x00000000

// Gray Scale
# define GRAY			0x808080FF
# define LIGHT_GRAY		0xC0C0C0FF

// Common Game Colors
# define ORANGE			0xFF8000FF
# define PURPLE			0x8000FFFF
# define BROWN			0x8B4513FF
# define PINK			0xFF69# define TILE_SIZE 60

// Different lava red shades
# define LAVA_RED_BRIGHT	0xFF4500FF  // Orange-red lava (RGB: 255, 69, 0)
# define LAVA_RED_DEEP		0xDC143CFF  // Crimson lava (RGB: 220, 20, 60)
# define LAVA_RED_CLASSIC	0xCF1020FF  // Classic lava red (RGB: 207, 16, 32)
# define LAVA_RED_DARK		0xB22222FF  // Fire brick red (RGB: 178, 34, 34)
# define LAVA_RED_MOLTEN	0xFF2400FF  // Scarlet lava (RGB: 255, 36, 0)

// Environment Colors
# define SKY_BLUE		0x87CEEBFF
# define FOREST_GREEN	0x228B22FF
# define SAND_YELLOW	0xF4A460FF

// Common Floor/Ceiling Colors
# define FLOOR_BROWN	0x8B4513FF
# define CEILING_BLUE	0x87CEEBFF
# define FLOOR_GRAY		0x696969FF
# define CEILING_WHITE	0xF5F5F5FF

// Minimap Colors
# define WALL_COLOR		0x000000FF  // Black walls
# define FLOOR_COLOR	0xFFFFFFFF  // White floor
# define PLAYER_COLOR	0xFF0000FF  // Red player dot
# define EMPTY_COLOR	0xC0C0C0FF  // Light gray for empty space

// Debug Colors
# define DEBUG_RED		0xFF000080  // Semi-transparent red
# define TEST_IMG_RED	0xFF000020  // Semi-transparent red
# define DEBUG_GREEN	0x00FF0080  // Semi-transparent green
# define DEBUG_GREEN2	0x00FF0040  // Semi-transparent green
// # define DEBUG_GREEN2	0x00FF00FF  // Semi-transparent green
# define DEBUG_BLUE		0x0000FF80  // Semi-transparent blue

// === Used Colors (Minimap) [Experimental set]
// # define DARK_GRAY		0x404040FF
// # define STONE_GRAY		0x708090FF
// # define BLACK			0x000000FF
// --- Used Colors (Transparent) (Minimap)
# define DARK_GRAY		0x40404080
# define STONE_GRAY		0x70809080
# define BLACK			0x00000080

/******************************************************************************/
/******     CONSTANTS     *****************************************************/
/******************************************************************************/

# define PI 3.141592654
# define READ_BUFFER 100

// Window Dimensions
// # define WIDTH 800
// # define HEIGHT 600
# define WIDTH 1800
# define HEIGHT 1100

// Player and Raycasting Constants
// # define PLAYER_DIA 8
# define START_PX 500
# define START_PY 500
# define FOV 60				// Field of View in degrees, f for float
// # define NUM_RAYS 1600
# define NUM_RAYS 1800
# define RAY_LEN_DEFAULT 10		// This number multiple of tile_size

// Mini-Map Constants
# define TILE_SIZE 15
# define MMP_W 600
# define MMP_H 210
# define MINIMAP_TILE_MIN 1
# define MINIMAP_TILE_MAX 48
# define MAP_OFFSET_X 25
# define MAP_OFFSET_Y 25
// # define PL_DIR_LEN 8
# define MAP_SCALE 1.0f			// Scale for the minimap

// Experimental set
# define PLAYER_DIA 8
# define PL_DIR_LEN 8
// # define PLAYER_DIA 25
// # define TILE_SIZE 50
// # define PL_DIR_LEN 20

/******************************************************************************/
/********     STRUCTS     *****************************************************/
/******************************************************************************/

enum e_key_type
{
	NO_CHECK,
	SO_CHECK,
	WE_CHECK,
	EA_CHECK,
	F_CHECK,
	C_CHECK,
	KEY_COUNT
};

enum	e_current_state
{
	INITIAL_STATE,
	WAITING_FOR_MAP,
	PARSING_MAP
};

typedef mlx_image_t		t_img;
typedef mlx_texture_t	t_txr;
typedef mlx_key_data_t	t_key;

typedef struct s_game t_game;
typedef struct s_data t_data;
typedef struct s_map t_map;
typedef struct s_player t_player;
typedef struct s_rays t_rays;
typedef struct s_colour t_colour;
typedef struct s_ivec t_ivec;
typedef struct s_dvec t_dvec;

typedef struct s_ivec
{
	int	x;
	int	y;
}	t_ivec;

typedef struct s_dvec
{
	double	x;
	double	y;
}	t_dvec;

typedef struct s_colour
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}	t_color;

typedef struct s_game
{
	t_data		*data;			// for dynamic scaling and dimensioning

	mlx_t		*mlx;			// for window and mlx context
	t_img		*background;	// background image with ceiling and floor colors
	int32_t		background_inst_id;	// instance ID for background image
	t_img		*img_3d;			// for ray-casted 3D image to be put on the window
	int32_t		img_3d_inst_id;	// instance ID for 3D image
	// t_img		*gun3D;			// gun image to be used in 3D view
	// int32_t		gun_inst_id;	// gun instance ID for 3D image
	t_txr 		*NO_texture;
	t_txr 		*SO_texture;
	t_txr 		*WE_texture;
	t_txr 		*EA_texture;
	t_color		floor_color;
	t_color		ceiling_color;

	t_map		*map;			// pointer to map struct, also holds map image
	t_player	*player;		// pointer to player struct for player position
} t_game;

typedef struct s_data
{
	// Window Dimensions
	int		wind_w;
	int		wind_h;

	// Player elements
	int	 	pl_dia;
	int		pl_arr_x;
	int		pl_arr_y;
	int	 	pl_posx;
	int	 	pl_posy;
	int		pl_center_x;
	int		pl_center_y;
	double		pl_posx_d;
	double		pl_posy_d;
	double		pl_center_x_d;
	double		pl_center_y_d;
	double		inv_tile_size;

	// Ray casting elements
	double	fov;			// Field of View in degrees, f for float
	int		num_rays;		// No. of rays to cast within the FOV
	char	ini_dir;		// initial player direction character (N, S, E, W), initialized to N
	double	prev_dir;		// player direction in radians
	double	cur_dir;		// player direction in radians
	double	cosine;			// cos(cur_dir)
	double	sine;			// sin(cur_dir)

	// Mini-map elements
	int	 	mmp_w;
	int	 	mmp_h;
	int	 	mmp_offx;
	int	 	mmp_offy;
	double		mmp_scale;
	double		mmp_inv_scale;
	int	 	mm_tile_size;
	int	 	mmp_disp_w;
	int	 	mmp_disp_h;
	int	 	tile_size;		// size of each tile/block in the overview map
	int		tiles_x;
	int		tiles_y;
	bool	fov_toggle;
	int	 	pl_dia_mm;
	int	 	pl_dir_len_mm;

	// FPS related
	int		fps;
	double	time;
	double	acc_time;

	// Debugging elements
	int		debug_offset_x;	// offset for debugging view
	int		debug_offset_y;	// offset for debugging view
} t_data;

typedef struct s_map
{
	t_data		*data;

	t_img		*image;			// pointer to the image of the 2D map
	int			image_inst_id;	// instance ID for 2D map image
	int			fd;				// file descriptor for map file
	char		**map_array;	// 2D array of map data (strings)
	char		**img_array;	// 2D array of image data (strings)

	t_player	*player;		// pointer to player struct for convenience
	t_game		*game;

	// test elements
	t_img		*test;
	int			test_inst_id;
} t_map;

typedef struct s_player
{
	t_data		*data;

	t_img		*blob_2d;		// pointer to 2D player blob image
	int32_t		blob_inst_id;	// instance ID for 2D player blob
	t_img		*view;
	int			view_inst_id;
	t_rays		**rays;			// array of rays for raycasting

	t_map		*map;
	t_game		*game;
} t_player;

typedef struct s_rays
{
	int			index;			// index of the current ray being processed
	double		delta;			// angle of deviation +/- from the player's current direction
	double		*prev_dir;
	double		*cur_dir;
	double		angle;			// absolute angle of the ray in radians
	double		cosine;			// cosine of the angle
	double		sine;			// sine of the angle
	t_dvec		coeff;			// element for ray-casting (must be updated in run-time)
	int			*center_x;		// x coordinate of the starting point of the ray
	int			*center_y;		// y coordinate of the starting point of the ray
	double		*center_x_d;
	double		*center_y_d;
	double		hit_x;			// x coordinate of the hit point
	double		hit_y;			// y coordinate of the hit point
	double		length;			// length of the distance traveled by the ray
	double		wall_distance;	// ray length if the cur-direction aligns with ray angle, i.e. with the factor of cos(delta)
	double		inv_wall_distance;
	char		hit_wall;		// N, S, E or W
	t_txr		*tex;
	double		tex_u;
} t_rays;

typedef struct s_circle_ctx
{
	t_data	*data;
	char	**img;
	double	radius;
	int		width;
	int		height;
}	t_circle_ctx;

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_offsets_info
{
	const t_vec2	*arr;
	size_t			count;
}	t_offsets_info;

typedef struct s_rect
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
}			t_rect;

typedef struct s_dir_ctx
{
	double			center_x;
	double			center_y;
	double			scale;
	int				width;
	int				height;
	double			cosine;
	double			sine;
}					t_dir_ctx;

typedef struct s_ray_ctx
{
	double			start_x;
	double			start_y;
	double			cosine;
	double			sine;
	double			scale;
	int				width;
	int				height;
	int				steps;
	int				prev_ix;
	int				prev_iy;
	bool			first;
}					t_ray_ctx;

typedef struct s_ray_trace
{
	t_dvec			hop;
	t_dvec			hype[3];
	t_ivec			check;
	t_ivec			hit;
	t_dvec			start;
	double			inv_tile;
}					t_ray_trace;

typedef struct s_wall_frame
{
	t_rays			**rays;
	int				total;
	int				index;
	int				scale;
	t_rays			*ray;
	int				height;
	float			tex_u;
}					t_wall_frame;

typedef struct s_column_ctx
{
	t_img			*target;
	t_txr			*texture;
	uint8_t			*dst;
	uint32_t		width;
	int				screen_x;
	int				wall_height;
	float			wall_u;
	int				draw_start;
	int				draw_end;
	double			tex_step;
	double			tex_pos;
	int				tex_x;
}					t_column_ctx;

typedef struct s_blob_ctx
{
	double			scale;
	int				width;
	int				height;
	int				draw_x;
	int				draw_y;
}					t_blob_ctx;


/******************************************************************************/
/*******     FUNCTIONS     ****************************************************/
/******************************************************************************/

// src

int			main(int argc, char **argv);
void		game_loop(void *param);
bool		move_player(t_game *game);
bool		turn_player(t_game *game);
double		rotation_step(t_game *game);
void		clear_player_view(t_game *game);
void		print_fps(t_data *data);
void		init_events(void *param);

// src/initialization

t_game		*get_game(void);
t_data		*get_data(void);
t_map		*get_map(void);
t_player	*get_player(void);
t_rays		**get_rays(void);

void		init_game_elements(t_game *game, char *arg);
void		update_game_data_after_parsing(t_data *data);

void		assign_textures(t_game *game, t_txr **txr, char *line, char *prfx);
void		identify_rgb(t_game *game, char *line, t_color *color);
void		parse_line(t_game *game, char *line);
int			validate_map_line(t_game *game, char *line);
void		init_background(t_game *game);

void		init_rays(t_rays **rays);

void		create_image_array(t_map *map, t_data *data);


// src/parsing

void		check_map(t_game *game);
void		assign_direction(t_map *map, char player_dir);
char		*expand_tabs(char *line);
bool		empty_line(char *line);
void		parse_game_data(t_game *game, char *map_name);
int			check_key_data_completion(t_game *game);
void		pad_shorter_lines(t_game *game);
char		**copy_map(char **original);
bool		flood_fill(char **map, int x, int y);
void		allocate_map_array(t_game *game, char *line);
int			parse_key_data(t_game *game, char *line);

// src/drawing

void		start_drawing(t_game *game);

void		place_block(t_img *img, int i, int j, int block_color);
void		place_lined_block(t_img *img, int x, int y, int block_color);

void		place_player_2d(t_game *game);

void		draw_player_direction(t_player *pl, t_data *data);
void		erase_prev_direction(t_player *pl, t_data *data);
void		draw_cur_direction(t_player *pl, t_data *data);

void		erase_previous_fov(t_player *pl, t_rays **rays);
void		erase_ray(t_player * pl, t_rays *ray);

void		draw_current_fov(t_player *pl, t_rays **rays);
void		draw_ray(t_player * pl, t_rays *ray);

void		udpate_rays(t_rays **rays, t_map *map, t_data *data);
bool		is_border_pixel(int x, int y, int width, int height);
double		tile_step(void);
void		init_tile_edges(double step, int tile, int *start, int *end);
bool		validate_edge(int *start, int *end, int max);
bool		init_direction_ctx(t_player *pl, t_data *data, double angle,
				t_dir_ctx *ctx);
void		draw_direction_line(t_player *pl, t_dir_ctx *ctx, uint32_t colour);
int			world_to_minimap(double value, double scale);
void		minimap_plot_ray(t_player *pl, t_rays *ray, uint32_t colour);
bool		init_ray_ctx(t_player *pl, t_rays *ray, t_ray_ctx *ctx);
void		plot_ray_pixels(t_player *pl, t_ray_ctx *ctx, uint32_t colour);

// src/rendering

void		render_graphics(t_game *game);
void		draw_3d_walls(t_game *game);
void		erase_3d_walls(t_game *game);
void		render_column(t_game *game, t_column_ctx *ctx);
void		render_minimap_view(t_game *game, t_map *map);
void		render_player_blob(t_game *game, t_player *pl);
void		render_2d_view(t_game *game, t_player *pl);
uint32_t	column_sample_color(t_column_ctx *ctx, int tex_y);
void		column_write_texel(t_column_ctx *ctx, int y, uint32_t color);

// src/coordinates

bool		wall_collision_circle(t_map *map, double center_x, double center_y);

// src/ray_casting

void		cast_rays(t_map *map, t_rays **rays, t_data *data);
void 		initialize_ray_caster(t_rays *ray, t_data *data, t_dvec *d_ptr[], t_ivec *check);
void		update_distance(t_dvec *hype, t_ivec *check);
void		extract_hit(t_rays *ray, t_ray_trace *ctx);
void		assign_wall_texture(t_game *game, t_rays *ray, t_dvec hop,
				t_ivec check);

// src/utils

bool 		is_valid(char c);
bool 		is_valid_block(char c);
bool 		is_player(char c);
int			ft_maxi(int x, int y);
void		exit_early(t_game *game, char *msg, int ret);
void		free_exit_early(t_game *game, char *msg, int ret, char *str);


#endif
