/* GTK - The GIMP Toolkit
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * GtkBindingSet: Keybinding manager for GtkObjects.
 * Copyright (C) 1998 Tim Janik
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
#ifndef __GTK_BINDINGS_H__
#define __GTK_BINDINGS_H__


#include <gdk/gdk.h>
#include <gtk/gtkobject.h>
#include <gtk/gtkenums.h>


#ifdef __cplusplus
extern "C" {
#pragma }
#endif /* __cplusplus */


/* Pattern matching
 */
typedef struct	_GtkPatternSpec	GtkPatternSpec;

struct _GtkPatternSpec
{
  GtkMatchType	 match_type;
  guint		 pattern_length;
  gchar		*pattern;
  gchar		*pattern_reversed;
  gpointer	 user_data;
  guint		 seq_id;
};

void	 gtk_pattern_spec_init	    (GtkPatternSpec	 *pspec,
				     const gchar	 *pattern);
void	 gtk_pattern_spec_free_segs (GtkPatternSpec	 *pspec);
gboolean gtk_pattern_match	    (GtkPatternSpec	 *pspec,
				     guint		  string_length,
				     const gchar	 *string,
				     const gchar	 *string_reversed);
gboolean gtk_pattern_match_string   (GtkPatternSpec	 *pspec,
				     const gchar	 *string);
gboolean gtk_pattern_match_simple   (const gchar	 *pattern,
				     const gchar	 *string);


/* Binding sets
 */

#define	GTK_BINDING_ARG_INT	(GTK_TYPE_INT)
#define	GTK_BINDING_ARG_LONG	(GTK_TYPE_LONG)
#define	GTK_BINDING_ARG_FLOAT	(GTK_TYPE_FLOAT)
#define	GTK_BINDING_ARG_DOUBLE	(GTK_TYPE_DOUBLE)
#define	GTK_BINDING_ARG_STRING	(GTK_TYPE_STRING)

typedef struct _GtkBindingSet		GtkBindingSet;
typedef struct _GtkBindingEntry		GtkBindingEntry;
typedef struct _GtkBindingSignal	GtkBindingSignal;
typedef struct _GtkBindingArg		GtkBindingArg;

struct _GtkBindingSet
{
  gchar			*set_name;
  gint			 priority;
  GSList		*widget_path_pspecs;
  GSList		*widget_class_pspecs;
  GSList		*class_branch_pspecs;
  GtkBindingEntry	*entries;
  GtkBindingEntry	*current;
};

struct _GtkBindingEntry
{
  /* key portion
   */
  guint			 keyval;
  guint			 modifiers;
  
  GtkBindingSet		*binding_set;
  guint			destroyed : 1;
  guint			in_emission : 1;
  GtkBindingEntry	*set_next;
  GtkBindingEntry	*hash_next;
  GtkBindingSignal	*signals;
};

struct _GtkBindingSignal
{
  GtkBindingSignal	*next;
  gchar			*signal_name;
  guint			 n_args;
  GtkBindingArg		*args;
};

struct _GtkBindingArg
{
  GtkType	arg_type;
  union {
    glong	 long_data;
    gdouble	 double_data;
    gchar	*string_data;
  } d;
};

/* Binding sets
 */
GtkBindingSet*	gtk_binding_set_new	(const gchar	*set_name);
GtkBindingSet*	gtk_binding_set_by_class(gpointer	 object_class);
GtkBindingSet*	gtk_binding_set_find	(const gchar	*set_name);
gboolean gtk_bindings_activate		(GtkObject	*object,
					 guint		 keyval,
					 guint		 modifiers);
gboolean gtk_binding_set_activate	(GtkBindingSet	*binding_set,
					 guint		 keyval,
					 guint		 modifiers,
					 GtkObject	*object);
#define	 gtk_binding_entry_add		gtk_binding_entry_clear
void	 gtk_binding_entry_clear	(GtkBindingSet	*binding_set,
					 guint		 keyval,
					 guint		 modifiers);
void	 gtk_binding_entry_remove	(GtkBindingSet	*binding_set,
					 guint		 keyval,
					 guint		 modifiers);
void	 gtk_binding_entry_add_signal	(GtkBindingSet	*binding_set,
					 guint		 keyval,
					 guint		 modifiers,
					 const gchar	*signal_name,
					 guint		 n_args,
					 ...);
void	 gtk_binding_entry_add_signall	(GtkBindingSet	*binding_set,
					 guint		 keyval,
					 guint		 modifiers,
					 const gchar	*signal_name,
					 GSList		*binding_args);
void	 gtk_binding_set_add_path	(GtkBindingSet	*binding_set,
					 GtkPathType	 path_type,
					 const gchar	*path_pattern,
					 GtkPathPriorityType priority);





#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __GTK_BINDINGS_H__ */