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

char ***set_coord2(char ***coord, int i, int x, int y, int zoom);
char ***set_coord3(char ***coord, int i, int x, int y, int zoom, int rotate);

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

void legend(t_struct *param)
{
  mlx_string_put(param->mlx, param->win, 0, 0, 0x00FFFF, "Commande Disponible :");
  mlx_string_put(param->mlx, param->win, 0, 25, 0x00FFFF, "Zoom + : Q  | Zoom - : E");
  mlx_string_put(param->mlx, param->win, 0, 60, 0x00FFFF, "Deplacement :");
  mlx_string_put(param->mlx, param->win, 0, 80, 0x00FFFF, "Gauche : A");
  mlx_string_put(param->mlx, param->win, 0, 100, 0x00FFFF, "Droite : D");
  mlx_string_put(param->mlx, param->win, 0, 120, 0x00FFFF, "Haut : W");
  mlx_string_put(param->mlx, param->win, 0, 140, 0x00FFFF, "Bas : S");
  mlx_string_put(param->mlx, param->win, 0, 160, 0x00FFFF, "Return : R");
}

int close_mlx(int keycode, t_struct *param)
{
  static int x;
  static int y;
  static int xd;
  static int yd;
  static int rotate;
  static int r;
  
  if(!r)
    r = 0;
  if(!rotate)
    rotate = 0;
  if(!xd)
    xd = 300;
  if(!yd)
    yd = 60;
  if(!y)
    y = 400;
  if(!x)
    x = 0;
  if(keycode == 53)
    exit(1);
  if(keycode == 2)
    {
      xd += 40;
      mlx_destroy_window(param->mlx, param->win);
      param->win = mlx_new_window(param->mlx, 900, 900, "42");
      legend(param);
      if(param->zoom == 0)
	mlx_string_put(param->mlx, param->win, 200, 10, 0x00FFFF, "A partir de la le zoom va retourner la piece");
      set_coord(param->coord, param->i, xd, yd, param->zoom);
      draw_with_tab(param->coord, param->i, param->maxline, param);
      mlx_key_hook(param->win, close_mlx, param);
      //  x+= 40;
      //fill_iso_rect(param->mlx, param->win, x, y, 20,0x00FFFF);
    }
  if(keycode == 1)
    {
      yd += 40;
      mlx_destroy_window(param->mlx, param->win);
      param->win = mlx_new_window(param->mlx, 900, 900, "42");
      legend(param);
      if(param->zoom == 0)
	mlx_string_put(param->mlx, param->win, 200, 10, 0x00FFFF, "A partir de la le zoom va retourner la piece");
      set_coord(param->coord, param->i, xd, yd, param->zoom);
      draw_with_tab(param->coord, param->i, param->maxline, param);
      mlx_key_hook(param->win, close_mlx, param);
      //y += 40;
      //fill_iso_rect(param->mlx, param->win, x, y,20,0x00FFFF);
    }
  if(keycode == 13)
    {
      yd -= 40;
      mlx_destroy_window(param->mlx, param->win);
      param->win = mlx_new_window(param->mlx, 900, 900, "42");
      legend(param);
      if(param->zoom == 0)
	mlx_string_put(param->mlx, param->win, 200, 10, 0x00FFFF, "A partir de la le zoom va retourner la piece");
      set_coord(param->coord, param->i, xd, yd, param->zoom);
      draw_with_tab(param->coord, param->i, param->maxline, param);
      mlx_key_hook(param->win, close_mlx, param);
      //y -= 40;
      //fill_iso_rect(param->mlx, param->win, x, y,20,0x00FFFF);
    }
  if(keycode == 0)
    {
      xd -= 40;
      mlx_destroy_window(param->mlx, param->win);
      param->win = mlx_new_window(param->mlx, 900, 900, "42");
      legend(param);
      if(param->zoom == 0)
	mlx_string_put(param->mlx, param->win, 200, 10, 0x00FFFF, "A partir de la le zoom va retourner la piece");
      set_coord(param->coord, param->i, xd, yd, param->zoom);
      draw_with_tab(param->coord, param->i, param->maxline, param);
      mlx_key_hook(param->win, close_mlx, param);
      
      // x -= 40;
      //fill_iso_rect(param->mlx, param->win, x, y,20,0x00FFFF);
      //  mlx_cursor_move(param->mlx, param->win, x, y);
    }
  if(keycode == 12)
    {
      param->zoom += 5;
      mlx_destroy_window(param->mlx, param->win);
      param->win = mlx_new_window(param->mlx, 900, 900, "42");
      legend(param);
      if(param->zoom == 0)
	mlx_string_put(param->mlx, param->win, 200, 10, 0x00FFFF, "A partir de la le zoom va retourner la piece");
      set_coord(param->coord, param->i, xd, yd, param->zoom);
      draw_with_tab(param->coord, param->i, param->maxline, param);
      mlx_key_hook(param->win, close_mlx, param);
    }
  if(keycode == 14)
    {
      param->zoom -= 5;
      mlx_destroy_window(param->mlx, param->win);
      param->win = mlx_new_window(param->mlx, 900, 900, "42");
      legend(param);
      if(param->zoom == 0)
	mlx_string_put(param->mlx, param->win, 200, 10, 0x00FFFF, "A partir de la le zoom va retourner la piece");
      set_coord(param->coord, param->i, xd, yd, param->zoom);
      draw_with_tab(param->coord, param->i, param->maxline, param);
      mlx_key_hook(param->win, close_mlx, param);
    }
  if(keycode == 123)
    {
      //gauche
      rotate -= 5;
      mlx_destroy_window(param->mlx, param->win);
      param->win = mlx_new_window(param->mlx, 900, 900, "42");
      legend(param);
      if(param->zoom == 0)
	mlx_string_put(param->mlx, param->win, 200, 10, 0x00FFFF, "A partir de la le zoom va retourner la piece");
      set_coord3(param->coord, param->i, xd, yd, param->zoom,rotate);
      draw_with_tab(param->coord, param->i, param->maxline, param);
      mlx_key_hook(param->win, close_mlx, param);
    }
  if(keycode == 124)
    {
      //      droite
      rotate += 5;
      mlx_destroy_window(param->mlx, param->win);
      param->win = mlx_new_window(param->mlx, 900, 900, "42");
      legend(param);
      if(param->zoom == 0)
	mlx_string_put(param->mlx, param->win, 200, 10, 0x00FFFF, "A partir de la le zoom va retourner la piece");
      set_coord3(param->coord, param->i, xd, yd, param->zoom,rotate);
      draw_with_tab(param->coord, param->i, param->maxline, param);
      mlx_key_hook(param->win, close_mlx, param);
    }
  if(keycode == 15)
    {
  
      mlx_destroy_window(param->mlx, param->win);
      param->win = mlx_new_window(param->mlx, 900, 900, "42");
      legend(param);
      if(param->zoom == 0)
	mlx_string_put(param->mlx, param->win, 200, 10, 0x00FFFF, "A partir de la le zoom va retourner la piece");
      if(r == 0)
	{
	  r++;
	  set_coord2(param->coord, param->i, xd, yd, param->zoom);
	}
      else if(r == 1)
	{
	  r = 0;
	  set_coord(param->coord, param->i, xd, yd, param->zoom);
	}
      draw_with_tab(param->coord, param->i, param->maxline, param);
      mlx_key_hook(param->win, close_mlx, param);
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

char ***set_coord3(char ***coord, int i, int x, int y, int zoom, int rotate)
{
  int index;
  int xdep;
  int ydep;
  int xtemp;
  int ytemp;
  int j;
  int v;

  v = 0;
  j = 0;
  index = 0;
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
	  //	  x -= zoom - rotate;//a achanger
	  y += zoom;
	  xdep = x;
	  ydep = y;
	}
      else
	{
	  x += zoom;
	  //y += zoom - rotate;// a changer
	  if(coord[index][2][0] != '0')
	    {
	      v = ft_atoi(coord[index][2]);
	      xtemp = x + v;
	      ytemp =  y - ((v * 2)  + 1);
	      j++;
	    }
	}
      index++;
    }
  return (coord);
}

char ***set_coord2(char ***coord, int i, int x, int y, int zoom)
{
  int index;
  int xdep;
  int ydep;
  int xtemp;
  int ytemp;
  int j;
  int v;

  v = 0;
  j = 0;
  index = 0;
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
	   x -= zoom;
	  y += zoom;
	  xdep = x;
	  ydep = y;
	}
      else
	{
	  x += zoom;
		  y += zoom;
	  if(coord[index][2][0] != '0')
	    {
	      v = ft_atoi(coord[index][2]);
	      if(v > 0)
		v = -v;
	      xtemp = x + v;
	      ytemp =  y - ((v * 2)  + 1);;
	      j++;
	    }
	}
      index++;
    }
  return (coord);
}

char ***set_coord(char ***coord, int i, int x, int y, int zoom)
{
  int index;
  int xdep;
  int ydep;
  int xtemp;
  int ytemp;
  int j;
  int v;

  v = 0;
  j = 0;
  index = 0;
  xdep = x;
  ydep = y;
  while(index < i)
    {
      if(coord[index][2][0] == '\n')
	{
	  x = xdep;
	  y = ydep;
	  x -= zoom;
	  y += zoom;
	  xdep = x;
	  ydep = y;
	}
      else
	{
	  x += zoom;
	  y += zoom;
	  if(coord[index][2][0] != '0')
	    {
	      v = ft_atoi(coord[index][2]);
	      xtemp = x + v;
	      ytemp = y - ((v * 2)  + 1);
	      j++;
	    }
	}
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
  int color;
  int val1;
  int futurindex;

  futurindex = 0;
  color = 0x00FFFF;
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
	  val1 = ft_atoi(coord[index][2]);
	  /* if(val1 != 0)
	    {
	      color = 0xFFFFFF;
	    }
	  else
	  color = 0x00FFFF;*/
	  /// if(coord[index][2][0] == '\n')
	  // // {
	    //   mlx_string_put(param->mlx, param->win, x1 - 10, y1 - 10, 0xFFFFFF, "salut");
	  // }
	  //	  mlx_string_put(param->mlx, param->win, x1 - 10, y1 - 10, 0xFFFFFF, coord[index][2]);
	  //mlx_string_put(param->mlx, param->win, x1 - 10, y1 - 10, 0xFFFFFF, coord[index][2]);
  //      mlx_string_put(param->mlx, param->win, x2 - 10, y2 - 10, 0xFFFFFF, coord[index][2]);
	  if(coord[index + 1][2][0] != '\n')
	    {
	      draw_line2(param->mlx, param->win, x1, y1, x2, y2, color);
	    }
	  else
	    futurindex++;
	}
      if(index + maxline + 1 < i)
	{
	  x1 = ft_atoi(coord[index][0]);
	  y1 = ft_atoi(coord[index][1]);
	  x2 = ft_atoi(coord[index + maxline + 1][0]);
	  y2 = ft_atoi(coord[index + maxline + 1][1]);
	  if(coord[index + maxline + 1][2][0] != '\n')
	    {
	      draw_line2(param->mlx, param->win, x1, y1, x2, y2, color);	
	    }
	}
      if(futurindex > 0)
	{
	  index += 2;
	  futurindex = 0;
	}
      else
	index++;
    }
}


int dothis()
{
  ft_putstr("lol");
  return (0);
}

int main(int argc, char **argv)
{ 
  void *mlx;
  void *win;
  char *line;
  int i;
  int maxline;
  t_struct *mystruct;
  char ***coord;
  char **tab;
  int index;

  index = 0;
  maxline = 0;
  i = 0;
  
//GERER ERREUR PARAM  
  if(argc != 2)
    {
      printf("Bug arg");
      return (0);
    }

////////////Init mlx//
  mlx = mlx_init();
  ///////////////
  
  /////////Create win//////// 
  win = mlx_new_window(mlx, 900, 900, "42");
  ////////////\\\\\\\\\\\\\\\\\\\\\
  
  //Create struct////
 mystruct = malloc(sizeof(mystruct) * 6);
  mystruct->mlx = mlx;
  mystruct->win = win;
  mystruct->zoom = 20;
  legend(mystruct);
  /////////////////
  
  //creation du tab////
  tab = create_tab(argv[1], tab);
  /////////////////

  /////////Take my max range tab///////
  while(tab[i])
    i++;
  /////////////////
  
  ////////set coord and mallloc||||||||||||
  coord = create_coord_tab(tab, coord, i);
  coord = set_coord(coord, i, 300, 60, mystruct->zoom);
  ////////////////////////////////
  
  /////MY maxline//////
  while(tab[index][0] != '\n')
    {
      if(tab[index][0] != ' ')
	maxline++;
      index++;
    }
  //////////////////////

  mystruct->i = i;
  mystruct->maxline = maxline;
  mystruct->coord = coord;
  
  ////Draw with my tab
  draw_with_tab(coord, i, maxline, mystruct);
  ////////////////////////////
  
  ///////Function appeler quand on fait un truc a la fenetre, faut le remettre dans le new fen//////////////////////
  // mlx_expose_hook (mystruct->win, dothis, 0);  
  ////////////////////////
  
  //Fonction pour utiliser le clavier
  mlx_key_hook(mystruct->win, close_mlx, mystruct);
  ///////////////////////////
  
  //Boucle pour tenir la fenetre
  mlx_loop(mlx);
  ///////////////////
  return(0);

}
