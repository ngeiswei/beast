/* BEAST - Bedevilled Audio System
 * Copyright (C) 1998, 1999 Olaf Hoehmann and Tim Janik
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
 */
#ifndef __BST_MENUS_H__
#define __BST_MENUS_H__


#include        "bstdefs.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


typedef struct _BstMenuEntry BstMenuEntry;
struct _BstMenuEntry
{
  GtkItemFactoryEntry entry;
  BseIcon            *icon;
};


/* --- prototypes --- */
GSList*	bst_menu_entries_compose	(guint			 n_menu_entries,
					 GtkItemFactoryEntry	*menu_entries,
					 guint			 n_cats,
					 BseCategory		*cats,
					 GtkItemFactoryCallback  cat_activate);
void    bst_menu_entries_create         (GtkItemFactory         *ifactory,
					 GSList                 *bst_menu_entries,
					 gpointer                callback_data);




#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif  /* __BST_MENUS_H__ */
