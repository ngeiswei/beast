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
#ifndef __BST_SNET_ROUTER_H__
#define __BST_SNET_ROUTER_H__

#include	"bstdefs.h"


#ifdef __cplusplus
extern "C" {
#pragma }
#endif /* __cplusplus */


/* --- Gtk+ type macros --- */
#define	BST_TYPE_SNET_ROUTER		(bst_snet_router_get_type ())
#define	BST_SNET_ROUTER(object)		(GTK_CHECK_CAST ((object), BST_TYPE_SNET_ROUTER, BstSNetRouter))
#define	BST_SNET_ROUTER_CLASS(klass)	(GTK_CHECK_CLASS_CAST ((klass), BST_TYPE_SNET_ROUTER, BstSNetRouterClass))
#define	BST_IS_SNET_ROUTER(object)	(GTK_CHECK_TYPE ((object), BST_TYPE_SNET_ROUTER))
#define	BST_IS_SNET_ROUTER_CLASS(klass)	(GTK_CHECK_CLASS_TYPE ((klass), BST_TYPE_SNET_ROUTER))
#define BST_SNET_ROUTER_GET_CLASS(obj)	((BstSNetRouterClass*) (((GtkObject*) (obj))->klass))


/* --- structures & typedefs --- */
typedef	struct	_BstSNetRouter		BstSNetRouter;
typedef	struct	_BstSNetRouterClass	BstSNetRouterClass;
struct _BstSNetRouter
{
  GtkHBox	 parent_object;

  BseSNet	*snet;

  GnomeCanvas	   *canvas;
  GnomeCanvasGroup *root;
};
struct _BstSNetRouterClass
{
  GtkHBoxClass  parent_class;

  GtkTooltips  *tooltips;
};


/* --- prototypes --- */
GtkType		bst_snet_router_get_type	(void);
GtkWidget*	bst_snet_router_new		(BseSNet	*snet);
void		bst_snet_router_update		(BstSNetRouter	*snet_router);
void		bst_snet_router_rebuild		(BstSNetRouter	*snet_router);
     



#ifdef __cplusplus
#pragma {
}
#endif /* __cplusplus */

#endif /* __BST_SNET_ROUTER_H__ */
