#ifndef HANDLER_H
# define HANDLER_H
# include "superparse.h"

int handle_none(t_superoption *option);
int handle_string(t_superoption *option);
int handle_int(t_superoption *option);
int handle_int64(t_superoption *option);

#endif