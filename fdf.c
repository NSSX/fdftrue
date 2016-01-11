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


int close_mlx(int keycode, void *param)
{
  if(keycode == 53)
    exit(1);
  return (0);
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
  //creation de la fenetre  
  if(argc != 2)
    {
      printf("Bug arg");
      return (0);
    }
  fd = open(argv[1], O_RDONLY);
  line = (char *)malloc(sizeof(char) * 2);
  while((ret = get_next_line(fd,&yt)))
    {
      line = ft_strjoins(line,yt);
      line = ft_strjoins(line, " \n ");
    }
  tab = ft_strsplit(line, ' ');
  while(tab[i])
    i++;
  coord = (char ***)malloc(sizeof(char **) * i + 1);
  while(index < i)
    {
      coord[index] = (char **)malloc(sizeof(char *) * 4);
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
    }
  index = 0;  
  win = mlx_new_window(mlx, 900, 900, "42");
  while(line[index] != '\n')
    {
      if(line[index] != ' ')
	maxline++;
      index++;
    }
  
  index = 0;
  //Tracer une ligne avec 2 point
  while(index < i)
    {
      if(coord[index + 1])
	{
	  x1 = ft_atoi(coord[index][0]);
	  y1 = ft_atoi(coord[index][1]);
	  x2 = ft_atoi(coord[index + 1][0]);
	  y2 = ft_atoi(coord[index + 1][1]);
	  if(coord[index][2][0] != '\n')
	    {
	      draw_line2(mlx, win, x1, y1, x2, y2, 0x00FFFF);
	    }
	}
      if(coord[index + maxline + 1])
	{
	  x1 = ft_atoi(coord[index][0]);
	  y1 = ft_atoi(coord[index][1]);
	  x2 = ft_atoi(coord[index + maxline + 1][0]);
	  y2 = ft_atoi(coord[index + maxline + 1][1]);
	  draw_line2(mlx, win, x1, y1, x2, y2, 0x00FFFF);
	}
      index++;
    }
  
  //  draw_line2(mlx, win, 320, 313, 300,900, 0x00FFFF);
  //Fonction pour utiliser le clavier
  mlx_key_hook(win, close_mlx, 0);
  //Boucle pour tenir la fenetre
  mlx_loop(mlx);
  return(0);

}
