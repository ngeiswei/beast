/* BSE - Bedevilled Sound Engine
 * Copyright (C) 1998-1999, 2000-2002 Tim Janik
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
 */
#ifndef __BSE_PROCEDURE_H__
#define __BSE_PROCEDURE_H__

#include	<bse/bseparam.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/* --- BSE type macros --- */
#define	BSE_PROCEDURE_TYPE(proc)	(G_TYPE_FROM_CLASS (proc))
#define	BSE_IS_PROCEDURE_CLASS(proc)	(G_TYPE_CHECK_CLASS_TYPE ((proc), BSE_TYPE_PROCEDURE))


/* --- limits --- */
#define	BSE_PROCEDURE_MAX_IN_PARAMS	(16)
#define	BSE_PROCEDURE_MAX_OUT_PARAMS	(16)


/* --- BseProcedureClass --- */
typedef BseErrorType  (*BseProcedureExec)    (BseProcedureClass *procedure,
					      const GValue	*in_values,
					      GValue		*out_values);
struct _BseProcedureClass
{
  GTypeClass      bse_class;
  gchar          *name;
  gchar          *blurb;
  guint           private_id;

  /* setup upon init */
  gchar          *help;
  gchar          *authors;
  gchar          *copyright;
  
  /* implementation */
  guint           n_in_pspecs;
  GParamSpec	**in_pspecs;
  guint           n_out_pspecs;
  GParamSpec	**out_pspecs;

  BseProcedureExec execute;
};


/* --- notifiers --- */
typedef gboolean (*BseProcedureNotify) (gpointer     func_data,
					const gchar *proc_name,
					BseErrorType exit_status);
typedef BseErrorType (*BseProcedureMarshal) (gpointer		marshal_data,
					     BseProcedureClass *proc,
					     const GValue      *ivalues,
					     GValue	       *ovalues);


/* --- prototypes --- */
/* execute procedure, passing n_in_pspecs param values for in
 * values and n_out_pspecs param value locations for out values
 */
BseErrorType bse_procedure_exec	  	  (const gchar		*proc_name,
					   ...);
BseErrorType bse_procedure_exec_void  	  (const gchar		*proc_name,
					   ...);
BseErrorType bse_procedure_store          (const gchar		*proc_name,
					   BseStorage		*storage,
					   ...);
GType	     bse_procedure_lookup	  (const gchar		*proc_name);
BseErrorType bse_procedure_marshal_valist (GType		 proc_type,
					   const GValue		*first_value,
					   BseProcedureMarshal	 marshal,
					   gpointer		 marshal_data,
					   gboolean		 skip_ovalues,
					   va_list		 var_args);
BseErrorType bse_procedure_marshal        (GType		 proc_type,
					   const GValue		*ivalues,
					   GValue		*ovalues,
					   BseProcedureMarshal	 marshal,
					   gpointer		 marshal_data);
BseErrorType bse_procedure_execvl	  (BseProcedureClass	*proc,
					   GSList		*in_value_list,
					   GSList		*out_value_list,
					   BseProcedureMarshal	 marshal,
					   gpointer		 marshal_data);


/* --- internal --- */
const gchar* bse_procedure_type_register (const gchar		*name,
					  const gchar		*blurb,
					  BsePlugin		*plugin,
					  GType  		*ret_type);
#if 0
gchar*	bse_procedure_eval		(const gchar		*expr,
					 BseErrorType		*error_p,
					 GValue			*value);
gchar*	bse_procedure_marshal_retval	(BseErrorType		 error,
					 GValue			*value,
					 const gchar		*warnings);
gchar*	bse_procedure_unmarshal_retval	(const gchar		*string,
					 BseErrorType		*error_p,
					 GValue			*value);
#endif


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BSE_PROCEDURE_H__ */
