#include "struct.h"
#include "get_next_line.h"
#include <mlx.h>
#include <stdio.h>
#include "libft/libft.h"
//Const fill_rect
#define RECTX 10
#define RECTY 10
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "struct.h"

void draw_line2(void *mlx, void *win, float xi, float yi, float xf, float yf, int color)
{
  int dx,dy,i,xinc,yinc,cumul,x,y ;
  x = xi ;
  y = yi ;
  dx = xf - xi ;
  dy = yf - yi ;
  xinc = ( dx > 0 ) ? 1 : -1 ;
  yinc = ( dy > 0 ) ? 1 : -1 ;
  dx = abs(dx) ;
  dy = abs(dy) ;
  mlx_pixel_put(mlx, win, x, y, color);
  if ( dx > dy ) {
    cumul = dx / 2 ;
    for ( i = 1 ; i <= dx ; i++ ) {
      x += xinc ;
      cumul += dy ;
      if ( cumul >= dx ) {
	cumul -= dx ;
	y += yinc ; }
      mlx_pixel_put(mlx, win, x, y, color); } }
  else {
    cumul = dy / 2 ;
    for ( i = 1 ; i <= dy ; i++ ) {
      y += yinc ;
      cumul += dx ;
      if ( cumul >= dy ) {
	cumul -= dy ;
	x += xinc ; }
      mlx_pixel_put(mlx, win, x, y, color); } }
}

static char *ft_join(char const *s1, char const *s2, int len1, int len2)
{
  char *join;
  int i;
  int j;

  i = 0;
  j = 0;
  join = malloc(sizeof(char) * (len1 + len2) + 1);
  while (s1[i] != '\0')
    {
      join[i] = s1[i];
      i++;
    }
  while (s2[j] != '\0')
    {
      join[i] = s2[j];
      i++;
      j++;
    }
  join[i] = '\0';
  return (join);
}

char *ft_strjoins(char const *s1, char const *s2)
{
  int len1;
  int len2;
  char *join;

  if (!s1 || !s2)
    return (NULL);
  len1 = ft_strlen(s1);
  len2 = ft_strlen(s2);
  join = ft_join(s1, s2, len1, len2);
  return (join);
}

void fill_iso_rect(void *mlx, void *win, int x, int y, int t,int color)
{
  draw_line2(mlx, win, x, y, x + t, y - t, color);
  draw_line2(mlx, win, x + t, y - t, x + (t * 2), y, color);
  draw_line2(mlx, win, x+(t * 2), y, x + t, y + t, color);
  draw_line2(mlx, win, x + t, y + t, x, y, color);
}

int close_mlx(int keycode, t_struct *param)
{
  static int x;
  static int y;

  if(!y)
    y = 400;
  if(!x)
    x = 0;
  if(keycode == 53)
    exit(1);
  if(keycode == 2)
    {
      x+= 40;
      fill_iso_rect(param->mlx, param->win, x, y, 20,0x00FFFF);
    }
  if(keycode == 1)
    {
      y += 40;
      fill_iso_rect(param->mlx, param->win, x, y,20,0x00FFFF);
    }
  if(keycode == 13)
    {
      y -= 40;
      fill_iso_rect(param->mlx, param->win, x, y,20,0x00FFFF);
    }
  if(keycode == 0)
    {
      x -= 40;
      fill_iso_rect(param->mlx, param->win, x, y,20,0x00FFFF);
      //  mlx_cursor_move(param->mlx, param->win, x, y);
    }
  if(keycode == 12)
    {
      mlx_destroy_window(param->mlx, param->win);
      //      param->win = mlx_new_window(param->mlx, 900, 900, "42");      

    }
  return (0);
}

char **create_tab(char *argv, char **tab)
{
  char *line;
  char *yt;
  int fd;
  int ret;

  fd = 0;
  ret = 0;
  
  fd = open(argv, O_RDONLY);
  line = (char *)malloc(sizeof(char) * 2);
  while((ret = get_next_line(fd,&yt)))
    {
      line = ft_strjoins(line,yt);
      line = ft_strjoins(line, " \n ");
    }
  tab = ft_strsplit(line, ' ');
  return (tab);
}

char ***create_coord_tab(char **tab, char ***coord, int i)
{
  int index;

  index = 0;
  coord = (char ***)malloc(sizeof(char **) * i + 1);
  while(index < i)
    {
      coord[index] = (char **)malloc(sizeof(char *) * 5);
      index++;
    }
  index = 0;
  while(index < i)
    {
      coord[index][0] = (char *)malloc(sizeof(char) * 5);
      coord[index][1] = (char *)malloc(sizeof(char) * 5);
      coord[index][2] = tab[index];
      index++;
    }
  return (coord);
}

char ***set_coord(char ***coord, int i)
{
  int index;
  int x;
  int y;
  int xdep;
  int ydep;
  int xtemp;
  int ytemp;
  int j;
  int v;

  v = 0;
  j = 0;
  index = 0;
  x = 300;
  y = 60;
  xdep = x;
  ydep = y;
  while(index < i)
    {
      if(j == 0)
	{
	  coord[index][0] = ft_itoa(x);
	  coord[index][1] = ft_itoa(y);
	}
      else
	{
	  coord[index][0] = ft_itoa(xtemp);
	  coord[index][1] = ft_itoa(ytemp);
	  j = 0;
	}
      if(coord[index][2][0] == '\n')
	{
	  x = xdep;
	  y = ydep;
	  x -= 20;
	  y += 20;
	  xdep = x;
	  ydep = y;
	}
      else
	{
	  x += 20;
	  y += 20;
	  if(coord[index][2][0] != '0')
	    {
	      v = ft_atoi(coord[index][2]);
	      xtemp = x + v;
	      ytemp = y - ((v * 2) + 1);
	      j++;
	    }
	}
      index++;
    }
  return (coord);
}

void draw_with_tab(char ***coord, int i, int maxline, t_struct *param)
{
  int x1;
  int x2;
  int y1;
  int y2;
  int index;

  index = 0;
  x1 = 0;
  x2 = 0;
  y1 = 0;
  y2 = 0;
  while(index + 1 < i)
    {
      if(index + 1 < i)
	{
	  x1 = ft_atoi(coord[index][0]);
	  y1 = ft_atoi(coord[index][1]);
	  x2 = ft_atoi(coord[index + 1][0]);
	  y2 = ft_atoi(coord[index + 1][1]);
	  if(coord[index][2][0] != '\n')
	    {
	      draw_line2(param->mlx, param->win, x1, y1, x2, y2, 0x00FFFF);
	    }
	}
      if(index + maxline + 1 < i)
	{
	  x1 = ft_atoi(coord[index][0]);
	  y1 = ft_atoi(coord[index][1]);
	  x2 = ft_atoi(coord[index + maxline + 1][0]);
	  y2 = ft_atoi(coord[index + maxline + 1][1]);
	  draw_line2(param->mlx, param->win, x1, y1, x2, y2, 0x00FFFF);
	}
      index++;
    }
}


int main(int argc, char **argv)
{ 
  void *mlx;
  void *win;
  int fd;
  char *line;
  int ret;
  char *yt;
  char **tab;
  int i;
  int index;
  char ***coord;
  int v;
  int j;
  int x;
  int y;
  int xdep;
  int ydep;
  int xtemp;
  int ytemp;
  int x1;
  int y1;
  int x2;
  int y2;
  int maxline;
  int color;
  int val;
  int val2;
  t_struct *mystruct;
  void *try_img; 
  MLXImage *img;
  t_img *myimg;  

  //void    *mlx_new_image(void *mlx_ptr,int width,int height);
 /*
**  return void *0 if failed
*/
  //  char    *mlx_get_data_addr(void *img_ptr, int *bits_per_pixel,
  //			     int *size_line, int *endian);
  /*
  **  endian : 0 = sever X is little endian, 1 = big endian
  **  endian : useless on macos, client and graphical framework have the same endian
  */
  //  int     mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr,
  //				  int x, int y);
  //unsigned int    mlx_get_color_value(void *mlx_ptr, int color);
  
  color = 0x00FFFF;
  val2 = 0;
  val = 0;
  maxline = 0;
  x = 300;
  y = 60;
  xdep = x;
  ydep = y;
  j = 0;
  v = 0;
  i = 0;
  index = 0;
  mlx = mlx_init();

//GERER ERREUR PARAM  
  if(argc != 2)
    {
      printf("Bug arg");
      return (0);
    }
  /*
  fd = open(argv[1], O_RDONLY);
  line = (char *)malloc(sizeof(char) * 2);
  while((ret = get_next_line(fd,&yt)))
    {
      line = ft_strjoins(line,yt);
      line = ft_strjoins(line, " \n ");
    }
    tab = ft_strsplit(line, ' ');*/
  
  //creation du tab////
  tab = create_tab(argv[1], tab);
  while(tab[i])
    i++;
  coord = create_coord_tab(tab, coord, i);
    /* coord = (char ***)malloc(sizeof(char **) * i + 1);
  while(index < i)
    {
      coord[index] = (char **)malloc(sizeof(char *) * 5);
      index++;
    }
  index = 0;
  while(index < i)
    {
      coord[index][0] = (char *)malloc(sizeof(char) * 5); 
      coord[index][1] = (char *)malloc(sizeof(char) * 5);
      coord[index][2] = tab[index];
      index++;
      }*//*
  index = 0;
  while(index < i)
    {
      if(j == 0)
	{
	  coord[index][0] = ft_itoa(x);
	  coord[index][1] = ft_itoa(y);
	}
      else
	{
	  coord[index][0] = ft_itoa(xtemp);
	  coord[index][1] = ft_itoa(ytemp);
	  j = 0;
	}
      if(coord[index][2][0] == '\n')
	{
	  x = xdep;
	  y = ydep;
	  x -= 20;
	  y += 20;
	  xdep = x;
	  ydep = y;
	}
      else
	{
	  x += 20;
	  y += 20;
	  if(coord[index][2][0] != '0')
	    {
	      v = ft_atoi(coord[index][2]);
	      xtemp = x + v;
	      ytemp = y - ((v * 2) + 1);
	      j++;
	    }
	}
      index++;
      }*/
  coord = set_coord(coord, i);
  index = 0;  
  win = mlx_new_window(mlx, 900, 900, "42");
//img/////////////////////img//////////
  /*try_img =  mlx_new_image(mlx, 200, 200);  
 myimg =  mlx_new_image(mlx, 200, 200);
 mlx_string_put(mlx, win, 0, 0, 0x00FFFF, "bonjour HIII");
myimg->bbp =  mlx_get_color_value(mlx, 0x00FFFF);
 myimg->size_line = 4;
 mlx_put_image_to_window(mlx, win, myimg, 0, 0);*/
 //////////////////
 mystruct = malloc(sizeof(mystruct) * 2);
  mystruct->mlx = mlx;
  mystruct->win = win;
  while(tab[index][0] != '\n')
    {
      if(tab[index][0] != ' ')
	maxline++;
      index++;
    }
  index = 0;
  draw_with_tab(coord, i, maxline, mystruct);
  //Tracer une ligne avec 2 point
    /* while(index + 1 < i)
    {
      if(index + 1 < i)
	{
	  x1 = ft_atoi(coord[index][0]);
	  y1 = ft_atoi(coord[index][1]);
	  x2 = ft_atoi(coord[index + 1][0]);
	  y2 = ft_atoi(coord[index + 1][1]);
	  val = ft_atoi(coord[index][2]);	  
	  val2 = ft_atoi(coord[index + 1][2]);
	  //pour ne pas relier des mauvais point
	  if(coord[index][2][0] != '\n')
	    {
	      draw_line2(mlx, win, x1, y1, x2, y2, color);
	    }
	}
      if(index + maxline + 1 < i)
	{
	  x1 = ft_atoi(coord[index][0]);
	  y1 = ft_atoi(coord[index][1]);
	  x2 = ft_atoi(coord[index + maxline + 1][0]);
	  y2 = ft_atoi(coord[index + maxline + 1][1]);
	  val = ft_atoi(coord[index][2]);
	  val2 = ft_atoi(coord[index + maxline + 1][2]);

	  draw_line2(mlx, win, x1, y1, x2, y2, color);
	 }
      index++;
      }*/
  //Fonction pour utiliser le clavier
  mlx_key_hook(win, close_mlx, mystruct);
  //Boucle pour tenir la fenetre
  mlx_loop(mlx);
  return(0);

}
