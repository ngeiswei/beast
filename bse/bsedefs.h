/* BSE - Bedevilled Sound Engine
 * Copyright (C) 1997-2002 Tim Janik
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
 *
 * bsedefs.h: type definitions and forward definitions libbse
 */
#ifndef __BSE_DEFS_H__
#define __BSE_DEFS_H__

#undef          G_DISABLE_ASSERT
#undef          G_DISABLE_CHECKS
#include        <sfi/sfi.h>
#include        <sfi/sfistore.h>	// FIXME
#include	<sfi/sficomwire.h>	// FIXME
#include	<math.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* --- some globally used defines --- */
#define FIXME(msg)  g_message ("%s:%d:FIXME(%s): " # msg, __FILE__, __LINE__, \
                               G_GNUC_PRETTY_FUNCTION)
#define FIXME_SKIP(code)  g_message ("%s:%d:FIXME(%s): code portion skipped", \
                                     __FILE__, __LINE__, G_GNUC_PRETTY_FUNCTION)
#ifdef G_ENABLE_DEBUG
#  define BSE_IF_DEBUG(type)    if (!(bse_main_debug_flags & BSE_DEBUG_ ## type)) { } else
#else  /* !G_ENABLE_DEBUG */
#  define BSE_IF_DEBUG(type)    while (0) /* don't exec */
#endif /* !G_ENABLE_DEBUG */


/* --- BSE basic typedefs --- */
typedef gint64                          BseIndex;
typedef gulong                          BseTime;


/* --- BSE objects, classes & interfaces --- */
typedef struct  _BseBinData             BseBinData;
typedef struct  _BseBinDataClass        BseBinDataClass;
typedef struct  _BseCapture             BseCapture;
typedef struct  _BseCaptureClass        BseCaptureClass;
typedef struct  _BseContainer           BseContainer;
typedef struct  _BseContainerClass      BseContainerClass;
typedef struct  _BseContextMerger       BseContextMerger;
typedef struct  _BseContextMergerClass  BseContextMergerClass;
typedef struct  _BseEffect              BseEffect;
typedef struct  _BseEffectClass         BseEffectClass;
typedef struct  _BseItem                BseItem;
typedef struct  _BseItemClass           BseItemClass;
typedef struct  _BseJanitor             BseJanitor;
typedef struct  _BseJanitorClass        BseJanitorClass;
typedef struct	_BseMidiDecoder		BseMidiDecoder;
typedef struct  _BseMidiNotifier        BseMidiNotifier;
typedef struct  _BseMidiNotifierClass   BseMidiNotifierClass;
typedef struct  _BseMidiReceiver        BseMidiReceiver;
typedef struct  _BseMidiSynth           BseMidiSynth;
typedef struct  _BseMidiSynthClass      BseMidiSynthClass;
typedef struct  _BseObject              BseObject;
typedef struct  _BseObjectClass         BseObjectClass;
typedef struct  _BsePart		BsePart;
typedef struct  _BsePartClass		BsePartClass;
typedef struct  _BseProcedureClass      BseProcedureClass;
typedef struct  _BseProject             BseProject;
typedef struct  _BseProjectClass        BseProjectClass;
typedef struct  _BseScriptControl       BseScriptControl;
typedef struct  _BseScriptControlClass  BseScriptControlClass;
typedef struct  _BseServer              BseServer;
typedef struct  _BseServerClass         BseServerClass;
typedef struct  _BseSNet                BseSNet;
typedef struct  _BseSNetClass           BseSNetClass;
typedef struct  _BseSong                BseSong;
typedef struct  _BseSongClass           BseSongClass;
typedef struct  _BseSongSequencer       BseSongSequencer;
typedef struct  _BseSource              BseSource;
typedef struct  _BseSourceClass         BseSourceClass;
typedef struct  _BseStorage             BseStorage;
typedef struct  _BseStorageClass        BseStorageClass;
typedef struct  _BseSubSynth            BseSubSynth;
typedef struct  _BseSubSynthClass       BseSubSynthClass;
typedef struct  _BseSuper               BseSuper;
typedef struct  _BseSuperClass          BseSuperClass;
typedef struct  _BseTrack               BseTrack;
typedef struct  _BseTrackClass          BseTrackClass;
typedef struct  _BseVoice		BseVoice;
typedef struct  _BseWave                BseWave;
typedef struct  _BseWaveRepo            BseWaveRepo;
typedef struct  _BseWaveRepoClass       BseWaveRepoClass;


/* --- BSE aux structures --- */
typedef struct  _BseGlobals             BseGlobals;
typedef struct  _BsePixdata             BsePixdata;
typedef struct  _BsePlugin              BsePlugin;
typedef struct  _BsePluginClass         BsePluginClass;


/* --- anticipated enums --- */
typedef enum
{
  BSE_DEBUG_TABLES              = (1 << 0),
  BSE_DEBUG_CLASSES             = (1 << 1),
  BSE_DEBUG_OBJECTS             = (1 << 2),
  BSE_DEBUG_NOTIFY              = (1 << 3),
  BSE_DEBUG_PLUGINS             = (1 << 4),
  BSE_DEBUG_CHUNKS              = (1 << 5),
  BSE_DEBUG_LOOP                = (1 << 6),
  BSE_DEBUG_PCM                 = (1 << 7),
  BSE_DEBUG_MIDI                = (1 << 8),
  BSE_DEBUG_LEAKS               = (1 << 9)
} BseDebugFlags;
typedef enum                    /*< skip >*/
{
  BSE_TOKEN_UNMATCHED           = G_TOKEN_LAST + 1
} BseTokenType;
typedef enum                    /*< skip >*/
{
  BSE_PIXDATA_RGB               = 3,
  BSE_PIXDATA_RGBA              = 4,
  BSE_PIXDATA_RGB_MASK          = 0x07,
  BSE_PIXDATA_1BYTE_RLE         = (1 << 3),
  BSE_PIXDATA_ENCODING_MASK     = 0x08
} BsePixdataType;


/* --- FIXME --- */
#define	BSE_STEREO_SHIFT	 (1)
#define	BSE_SAMPLE_SHIFT	 (16)
#define BSE_MAX_SAMPLE_VALUE_f   ((gfloat) BSE_MAX_SAMPLE_VALUE)
#define BSE_MIN_SAMPLE_VALUE_f   ((gfloat) BSE_MIN_SAMPLE_VALUE)
#define BSE_MAX_SAMPLE_VALUE_d   ((gdouble) BSE_MAX_SAMPLE_VALUE)
#define BSE_MIN_SAMPLE_VALUE_d   ((gdouble) BSE_MIN_SAMPLE_VALUE)
#define BSE_MAX_SAMPLE_VALUE     (32767)
#define BSE_MIN_SAMPLE_VALUE     (-32768) /* don't use this, assume
                                          * -BSE_MAX_SAMPLE_VALUE instead
                                          */

/* --- anticipated structures --- */
struct _BsePixdata
{
  BsePixdataType type : 8;
  guint          width : 12;
  guint          height : 12;
  const guint8  *encoded_pix_data;
};


/* --- anticipated variables --- */
extern BseDebugFlags bse_main_debug_flags;


/* --- BSE function types --- */
typedef void          (*BseFunc)             (void);
typedef void          (*BseIOWatch)	     (gpointer		 data,
					      GPollFD		*pfd);
typedef BseTokenType  (*BseTryStatement)     (gpointer           func_data,
                                              BseStorage        *storage,
                                              gpointer           user_data);
typedef BseObject*    (*BseUPathResolver)    (gpointer           func_data,
                                              GType              required_type,
                                              const gchar       *path,
					      gchar	       **error);
typedef gboolean      (*BseProcedureShare)   (gpointer           func_data,
                                              const gchar       *proc_name,
                                              gfloat             progress);
typedef gboolean      (*BseCategoryForeach)  (const gchar       *category_path,
                                              GType              type,
                                              gpointer           user_data);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BSE_DEFS_H__ */
