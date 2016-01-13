#ifndef STRUCT_H
# define STRUCT_H



typedef struct          s_struct
{
  void *mlx;
  void *win;
  char ***coord;
  int i;
  int maxline;
  int zoom;
  
  struct s_struct   *next;
  struct s_struct   *before;
}                                       t_struct;

typedef struct
{
  int                im_width;
  int                im_height;
  unsigned int       im_bpp;
  unsigned int       im_bpl;
  unsigned char      *im_buffer;
  //  XImage             *im_ximg;
} MLXImage;

typedef struct s_img
{
  void *img;
  char *data;
  int bbp;
  int size_line;
  int endian;
} t_img;

void draw_with_tab(char ***coord, int i, int maxline, t_struct *param);
char ***set_coord(char ***coord, int i, int x, int y, int zoom);
char ***create_coord_tab(char **tab, char ***coord, int i);
char **create_tab(char *argv, char **tab);
void fill_iso_rect(void *mlx, void *win, int x, int y, int t,int color);
char *ft_strjoins(char const *s1, char const *s2);
static char *ft_join(char const *s1, char const *s2, int len1, int len2);
void draw_line2(void *mlx, void *win, float xi, float yi, float xf, float yf, int color);

#endif
