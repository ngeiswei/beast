/* BSE - Bedevilled Sound Engine
 * Copyright (C) 1997, 1998, 1999 Olaf Hoehmann and Tim Janik
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
#include        "bsepcmdevice-alsa.h"

#include        "../PKG_config.h"

#ifndef	BSE_PCM_DEVICE_CONF_ALSA
BSE_DUMMY_TYPE (BsePcmDeviceAlsa);
#else	/* BSE_PCM_DEVICE_CONF_ALSA */

#include        <sys/asoundlib.h>
#include        <errno.h>


/* --- BsePcmDeviceAlsa structs --- */
struct _BsePcmDeviceAlsa
{
  BsePcmDevice parent_object;

  guint                   card;
  guint                   device;
  snd_pcm_t              *handle;
  gchar                  *card_id;
  gchar                  *card_name;
};
struct _BsePcmDeviceAlsaClass
{
  BsePcmDeviceClass parent_class;
};


/* --- prototypes --- */
static void         bse_pcm_device_alsa_class_init       (BsePcmDeviceAlsaClass   *class);
static void         bse_pcm_device_alsa_init             (BsePcmDeviceAlsa        *pcm_device_alsa);
static void         bse_pcm_device_alsa_shutdown         (BseObject              *object);
static gchar*       bse_pcm_device_alsa_device_name      (BsePcmDevice           *pdev,
							  gboolean                descriptive);
static BseErrorType bse_pcm_device_alsa_update_caps      (BsePcmDevice           *pdev);
static BseErrorType bse_pcm_device_alsa_open             (BsePcmDevice           *pdev,
                                                          gboolean                readable,
                                                          gboolean                writable,
                                                          guint                   n_channels,
                                                          BsePcmFreqMask          rate,
                                                          guint                   fragment_size);
static BseErrorType bse_pcm_device_alsa_setup            (BsePcmDeviceAlsa       *alsa,
                                                          gboolean                readable,
                                                          gboolean                writable,
                                                          guint                   n_channels,
                                                          BsePcmFreqMask          rate,
                                                          guint                   n_fragments,
                                                          guint                   fragment_size);
static void         bse_pcm_device_alsa_update_state     (BsePcmDevice           *pdev);
static void	    bse_pcm_device_alsa_retrigger        (BsePcmDevice           *pdev);
static void         bse_pcm_device_alsa_close            (BsePcmDevice           *pdev);
static guint        bse_pcm_device_alsa_read		 (BsePcmDevice		 *pdev,
							  guint                   n_bytes,
							  guint8                 *bytes);
static guint	    bse_pcm_device_alsa_write		 (BsePcmDevice		 *pdev,
							  guint                   n_bytes,
							  guint8                  *bytes);
static guint        pcm_rates_from_alsa_rates            (guint                   alsa_rates);

const char* snd_card_type_name (unsigned int card_type); // FIXME


/* --- variables --- */
static gpointer parent_class = NULL;


/* --- functions --- */
BSE_BUILTIN_TYPE (BsePcmDeviceAlsa)
{
  BseType pcm_device_alsa_type;
  
  static const BseTypeInfo pcm_device_alsa_info = {
    sizeof (BsePcmDeviceAlsaClass),
    
    (BseBaseInitFunc) NULL,
    (BseBaseDestroyFunc) NULL,
    (BseClassInitFunc) bse_pcm_device_alsa_class_init,
    (BseClassDestroyFunc) NULL,
    NULL /* class_data */,
    
    sizeof (BsePcmDeviceAlsa),
    0 /* n_preallocs */,
    (BseObjectInitFunc) bse_pcm_device_alsa_init,
  };
  
  pcm_device_alsa_type = bse_type_register_static (BSE_TYPE_PCM_DEVICE,
                                                   "BsePcmDeviceAlsa",
                                                   "PCM device implementation for ALSA driver",
                                                   &pcm_device_alsa_info);
  // bse_categories_register_icon ("/Source/Projects/SNet", snet_type, &snet_pixdata);
  
  return pcm_device_alsa_type;
}

static void
bse_pcm_device_alsa_class_init (BsePcmDeviceAlsaClass *class)
{
  BseObjectClass *object_class;
  BsePcmDeviceClass *pcm_device_class;
  
  parent_class = bse_type_class_peek (BSE_TYPE_PCM_DEVICE);
  object_class = BSE_OBJECT_CLASS (class);
  pcm_device_class = BSE_PCM_DEVICE_CLASS (class);
  
  object_class->shutdown = bse_pcm_device_alsa_shutdown;
  
  pcm_device_class->device_name = bse_pcm_device_alsa_device_name;
  pcm_device_class->update_caps = bse_pcm_device_alsa_update_caps;
  pcm_device_class->open = bse_pcm_device_alsa_open;
  pcm_device_class->update_state = bse_pcm_device_alsa_update_state;
  pcm_device_class->read = bse_pcm_device_alsa_read;
  pcm_device_class->write = bse_pcm_device_alsa_write;
  pcm_device_class->retrigger = bse_pcm_device_alsa_retrigger;
  pcm_device_class->close = bse_pcm_device_alsa_close;
}

static void
bse_pcm_device_alsa_init (BsePcmDeviceAlsa *alsa)
{
  alsa->card = 0;
  alsa->device = 0;
  alsa->handle = NULL;
  alsa->card_id = NULL;
  alsa->card_name = NULL;
}

static void
bse_pcm_device_alsa_shutdown (BseObject *object)
{
  BsePcmDeviceAlsa *alsa = BSE_PCM_DEVICE_ALSA (object);
  
  g_free (alsa->card_id);
  alsa->card_id = NULL;
  g_free (alsa->card_name);
  alsa->card_name = NULL;
  
  /* chain parent class' shutdown handler */
  BSE_OBJECT_CLASS (parent_class)->shutdown (object);
}

static gchar*
bse_pcm_device_alsa_device_name (BsePcmDevice *pdev,
				 gboolean      descriptive)
{
  BsePcmDeviceAlsa *alsa = BSE_PCM_DEVICE_ALSA (pdev);

  return descriptive ? alsa->card_id : alsa->card_name;
}

static BseErrorType
bse_pcm_device_alsa_open (BsePcmDevice  *pdev,
                          gboolean       readable,
                          gboolean       writable,
                          guint          n_channels,
                          BsePcmFreqMask rate,
                          guint          fragment_size)
{
  BsePcmDeviceAlsa *alsa = BSE_PCM_DEVICE_ALSA (pdev);
  BseErrorType error;
  gint omode = 0;
  gint perrno, fd;
  
  if (readable && writable)
    omode = SND_PCM_OPEN_DUPLEX;
  else if (readable)
    omode = SND_PCM_OPEN_CAPTURE;
  else if (writable)
    omode = SND_PCM_OPEN_PLAYBACK;

  perrno = snd_pcm_open (&alsa->handle, alsa->card, alsa->device, omode);
  if (perrno >= 0)
    {
      fd = snd_pcm_file_descriptor (alsa->handle);
      if (fd < 0)
        {
          snd_pcm_close (alsa->handle);
          perrno = fd;
        }
    }
  if (perrno < 0)
    {
      alsa->handle = NULL;
      perrno = -perrno;
      if (perrno == EBUSY)
        return BSE_ERROR_DEVICE_BUSY;
      else if (perrno == EISDIR || perrno == EACCES || perrno == EROFS)
        return BSE_ERROR_DEVICE_PERMS;
      else
        return BSE_ERROR_DEVICE_IO;
    }
  pdev->pfd.fd = fd;
  
  error = bse_pcm_device_alsa_setup (alsa, readable, writable, n_channels, rate, 128, fragment_size);
  if (error)
    {
      snd_pcm_close (alsa->handle);
      alsa->handle = NULL;
    }
  else
    {
      if (readable)
        BSE_OBJECT_SET_FLAGS (alsa, BSE_PCM_FLAG_READABLE);
      if (writable)
        BSE_OBJECT_SET_FLAGS (alsa, BSE_PCM_FLAG_WRITABLE);
    }
  
  return error;
}

static void
bse_pcm_device_alsa_close (BsePcmDevice *pdev)
{
  BsePcmDeviceAlsa *alsa = BSE_PCM_DEVICE_ALSA (pdev);
  
  snd_pcm_drain_playback (alsa->handle);
  snd_pcm_close (alsa->handle);
  alsa->handle = NULL;
}

static void
bse_pcm_device_alsa_update_state (BsePcmDevice *pdev)
{
  BsePcmDeviceAlsa *alsa = BSE_PCM_DEVICE_ALSA (pdev);
  snd_pcm_channel_setup_t channel_setup;
  
  memset (&channel_setup, 0, sizeof (channel_setup));
  channel_setup.channel = SND_PCM_CHANNEL_PLAYBACK;
  if (snd_pcm_channel_setup (alsa->handle, &channel_setup) >= 0)
    {
      snd_pcm_channel_status_t channel_status = { 0, };
      
      channel_status.channel = channel_setup.channel;
      if (snd_pcm_channel_status (alsa->handle, &channel_status) >= 0)
        {
          pdev->n_playback_bytes = channel_status.free;
	  pdev->playback_buffer_size = channel_setup.buf.block.frags * channel_setup.buf.block.frag_size;
          BSE_IF_DEBUG (PCM)
            g_message ("OSPACE(%s:%d#%d): left=%5d/%d frags: total=%d max=%d min=%d size=%d cur=%d bytes=%d free=%d o=%d u=%d\n",
                       alsa->card_id,
                       alsa->card,
                       alsa->device,
                       pdev->n_playback_bytes,
                       pdev->playback_buffer_size,
                       channel_setup.buf.block.frags,
                       channel_setup.buf.block.frags_max,
                       channel_setup.buf.block.frags_min,
                       channel_setup.buf.block.frag_size,
                       channel_status.frag,
                       channel_status.count,
                       channel_status.free,
                       channel_status.overrun,
                       channel_status.underrun);
        }
    }
  
  memset (&channel_setup, 0, sizeof (channel_setup));
  channel_setup.channel = SND_PCM_CHANNEL_CAPTURE;
  if (snd_pcm_channel_setup (alsa->handle, &channel_setup) >= 0)
    {
      snd_pcm_channel_status_t channel_status = { 0, };
      
      channel_status.channel = channel_setup.channel;
      if (snd_pcm_channel_status (alsa->handle, &channel_status) >= 0)
        {
          pdev->n_capture_bytes = channel_status.count;
	  pdev->capture_buffer_size = channel_setup.buf.block.frags * channel_setup.buf.block.frag_size;
          BSE_IF_DEBUG (PCM)
            g_message ("ISPACE(%s:%d#%d): left=%5d/%d frags: total=%d max=%d min=%d size=%d cur=%d bytes=%d free=%d o=%d u=%d\n",
                       alsa->card_id,
                       alsa->card,
                       alsa->device,
                       pdev->n_capture_bytes,
                       pdev->capture_buffer_size,
                       channel_setup.buf.block.frags,
                       channel_setup.buf.block.frags_max,
                       channel_setup.buf.block.frags_min,
                       channel_setup.buf.block.frag_size,
                       channel_status.frag,
                       channel_status.count,
                       channel_status.free,
                       channel_status.overrun,
                       channel_status.underrun);
        }
    }
}

static void
bse_pcm_device_alsa_retrigger (BsePcmDevice *pdev)
{
  BsePcmDeviceAlsa *alsa = BSE_PCM_DEVICE_ALSA (pdev);

  if (0)
    {
      if (BSE_PCM_DEVICE_READABLE (alsa))
	snd_pcm_channel_prepare (alsa->handle, SND_PCM_CHANNEL_CAPTURE);
      if (BSE_PCM_DEVICE_WRITABLE (alsa))
	snd_pcm_channel_prepare (alsa->handle, SND_PCM_CHANNEL_PLAYBACK);
    }

  if (BSE_PCM_DEVICE_READABLE (alsa))
    snd_pcm_channel_go (alsa->handle, SND_PCM_CHANNEL_CAPTURE);
  if (BSE_PCM_DEVICE_WRITABLE (alsa))
    snd_pcm_channel_go (alsa->handle, SND_PCM_CHANNEL_PLAYBACK);
}

static guint
bse_pcm_device_alsa_read (BsePcmDevice *pdev,
			  guint         n_bytes,
			  guint8       *bytes)
{
  BsePcmDeviceAlsa *alsa = BSE_PCM_DEVICE_ALSA (pdev);
  gint n;

  do
    n = snd_pcm_read (alsa->handle, bytes, n_bytes);
  while (n < 0 && -n == EINTR); /* don't mind signals */

  return MAX (n, 0);
}

static guint
bse_pcm_device_alsa_write (BsePcmDevice *pdev,
			   guint         n_bytes,
			   guint8       *bytes)
{
  BsePcmDeviceAlsa *alsa = BSE_PCM_DEVICE_ALSA (pdev);
  gint n;

  do
    n = snd_pcm_write (alsa->handle, bytes, n_bytes);
  while (n < 0 && -n == EINTR); /* don't mind signals */

  return MAX (n, 0);
}

static BseErrorType
bse_pcm_device_alsa_setup (BsePcmDeviceAlsa *alsa,
                           gboolean          readable,
                           gboolean          writable,
                           guint             n_channels,
                           BsePcmFreqMask    rate,
                           guint             n_fragments,
                           guint             fragment_size)
{
  BsePcmDevice *pdev = BSE_PCM_DEVICE (alsa);
  snd_pcm_info_t pcm_info = { 0, };
  guint rep;

  if (snd_pcm_nonblock_mode (alsa->handle, TRUE) < 0)
    return BSE_ERROR_DEVICE_ASYNC;

  if (snd_pcm_info (alsa->handle, &pcm_info) < 0)
    return BSE_ERROR_DEVICE_GET_CAPS;
  g_free (alsa->card_name);
  alsa->card_name = g_strdup (snd_card_type_name (pcm_info.type));
  g_free (alsa->card_id);
  alsa->card_id = g_strdup (pcm_info.id);

  for (rep = 0; rep < 2; rep++)
    {
      snd_pcm_channel_info_t channel_info = { 0, };
      snd_pcm_channel_params_t channel_params = { 0, };
      snd_pcm_channel_setup_t channel_setup = { 0, };

      if (rep == 0 && readable)
        channel_info.channel = SND_PCM_CHANNEL_CAPTURE;
      else if (rep == 1 && writable)
        channel_info.channel = SND_PCM_CHANNEL_PLAYBACK;
      else
        continue;

      if (snd_pcm_channel_info (alsa->handle, &channel_info) < 0)
        return BSE_ERROR_DEVICE_GET_CAPS;
      if (!(channel_info.formats & SND_PCM_FMT_S16))
        return BSE_ERROR_DEVICE_CAPS_MISMATCH;

      if (snd_pcm_flush_channel (alsa->handle, channel_info.channel) < 0)
        return BSE_ERROR_DEVICE_IO;

      channel_params.mode = SND_PCM_MODE_BLOCK;
      channel_params.channel = channel_info.channel;
      channel_params.format.interleave = 1;
      channel_params.format.format = SND_PCM_SFMT_S16;
      channel_params.format.rate = bse_pcm_freq_to_freq (rate);
      channel_params.format.voices = n_channels;
      channel_params.start_mode = SND_PCM_START_DATA;
      channel_params.stop_mode = SND_PCM_STOP_ROLLOVER;
      channel_params.buf.block.frag_size = fragment_size;
      channel_params.buf.block.frags_min = 0;
      channel_params.buf.block.frags_max = 65536;
      if (snd_pcm_channel_params (alsa->handle, &channel_params) < 0)
        return BSE_ERROR_DEVICE_SET_CAPS;

      if (snd_pcm_channel_prepare (alsa->handle, channel_info.channel) < 0)
        return BSE_ERROR_DEVICE_IO;

      channel_setup.channel = channel_info.channel;
      if (snd_pcm_channel_setup (alsa->handle, &channel_setup) < 0)
        return BSE_ERROR_DEVICE_GET_CAPS;

      pdev->n_channels = channel_setup.format.voices;
      pdev->sample_freq = channel_setup.format.rate;
    }
  
  return BSE_ERROR_NONE;
}

static BseErrorType
bse_pcm_device_alsa_update_caps (BsePcmDevice *pdev)
{
  BsePcmDeviceAlsa *alsa = BSE_PCM_DEVICE_ALSA (pdev);
  snd_pcm_info_t pcm_info = { 0, };
  snd_pcm_t *handle = NULL;
  gint perrno, fd;
  guint rep;

  perrno = snd_pcm_open (&handle, alsa->card, alsa->device, SND_PCM_OPEN_DUPLEX);
  if (perrno < 0)
    perrno = snd_pcm_open (&handle, alsa->card, alsa->device, SND_PCM_OPEN_CAPTURE);
  if (perrno < 0)
    perrno = snd_pcm_open (&handle, alsa->card, alsa->device, SND_PCM_OPEN_PLAYBACK);
  if (perrno >= 0)
    {
      fd = snd_pcm_file_descriptor (handle);
      if (fd < 0)
        {
          snd_pcm_close (handle);
          perrno = fd;
        }
    }
  if (perrno < 0)
    {
      perrno = -perrno;
      if (perrno == EBUSY)
        return BSE_ERROR_DEVICE_BUSY;
      else if (perrno == EISDIR || perrno == EACCES || perrno == EROFS)
        return BSE_ERROR_DEVICE_PERMS;
      else
        return BSE_ERROR_DEVICE_IO;
    }

  if (snd_pcm_info (handle, &pcm_info) < 0)
    return BSE_ERROR_DEVICE_GET_CAPS;
  g_free (alsa->card_name);
  alsa->card_name = g_strdup (snd_card_type_name (pcm_info.type));
  g_free (alsa->card_id);
  alsa->card_id = g_strdup (pcm_info.id);

  pdev->caps.readable = (pcm_info.flags & SND_PCM_INFO_CAPTURE) != 0;
  pdev->caps.writable = (pcm_info.flags & SND_PCM_INFO_PLAYBACK) != 0;
  pdev->caps.duplex = (pcm_info.flags & SND_PCM_INFO_DUPLEX) != 0;
  if (!pdev->caps.readable && !pdev->caps.writable)
    {
      snd_pcm_close (handle);
      return BSE_ERROR_DEVICE_CAPS_MISMATCH;
    }

  for (rep = 0; rep < 2; rep++)
    {
      snd_pcm_channel_info_t channel_info = { 0, };

      if (rep == 0 && pdev->caps.readable)
        channel_info.channel = SND_PCM_CHANNEL_CAPTURE;
      else if (rep == 1 && pdev->caps.writable)
        channel_info.channel = SND_PCM_CHANNEL_PLAYBACK;
      else
        continue;

      if (snd_pcm_channel_info (handle, &channel_info) < 0)
        {
          snd_pcm_close (handle);
          return BSE_ERROR_DEVICE_GET_CAPS;
        }
      if (!(channel_info.flags & SND_PCM_CHNINFO_BLOCK) ||
          !(channel_info.formats & SND_PCM_FMT_S16) ||
          channel_info.min_voices < 1)
        {
          snd_pcm_close (handle);
          return BSE_ERROR_DEVICE_CAPS_MISMATCH;
        }
      
      pdev->caps.max_n_channels = channel_info.max_voices;
      if (channel_info.channel == SND_PCM_CHANNEL_CAPTURE)
        pdev->caps.capture_freq_mask = pcm_rates_from_alsa_rates (channel_info.rates);
      else
        pdev->caps.playback_freq_mask = pcm_rates_from_alsa_rates (channel_info.rates);
      pdev->caps.max_fragment_size = channel_info.max_fragment_size;
    }

  snd_pcm_close (handle);

  BSE_IF_DEBUG (PCM)
    g_message ("CAPS(\"%s\" %s:%d#%d): w=%d r=%d d=%d max_ch=%d pfreq=0x%x cfreq=0x%x fragsize=%d\n",
               alsa->card_name,
               alsa->card_id,
               alsa->card,
               alsa->device,
               pdev->caps.writable,
               pdev->caps.readable,
               pdev->caps.duplex,
               pdev->caps.max_n_channels,
               pdev->caps.playback_freq_mask,
               pdev->caps.capture_freq_mask,
               pdev->caps.max_fragment_size);
  
  return BSE_ERROR_NONE;
}

static guint
pcm_rates_from_alsa_rates (guint alsa_rates)
{
  guint rates = 0;
  
  if (alsa_rates & SND_PCM_RATE_8000)   rates |= BSE_PCM_FREQ_8000;
  if (alsa_rates & SND_PCM_RATE_11025)  rates |= BSE_PCM_FREQ_11025;
  if (alsa_rates & SND_PCM_RATE_16000)  rates |= BSE_PCM_FREQ_16000;
  if (alsa_rates & SND_PCM_RATE_22050)  rates |= BSE_PCM_FREQ_22050;
  if (alsa_rates & SND_PCM_RATE_32000)  rates |= BSE_PCM_FREQ_32000;
  if (alsa_rates & SND_PCM_RATE_44100)  rates |= BSE_PCM_FREQ_44100;
  if (alsa_rates & SND_PCM_RATE_48000)  rates |= BSE_PCM_FREQ_48000;
  if (alsa_rates & SND_PCM_RATE_88200)  rates |= BSE_PCM_FREQ_88200;
  if (alsa_rates & SND_PCM_RATE_96000)  rates |= BSE_PCM_FREQ_96000;
  if (alsa_rates & SND_PCM_RATE_176400) rates |= BSE_PCM_FREQ_176400;
  if (alsa_rates & SND_PCM_RATE_192000) rates |= BSE_PCM_FREQ_192000;
  
  return rates;
}

#include <linux/asoundid.h>
const char* snd_card_type_name (unsigned int card_type)
{
  switch (card_type)
    {
      /* Gravis UltraSound */
    case SND_CARD_TYPE_GUS_CLASSIC:             return "GUS Classic";
    case SND_CARD_TYPE_GUS_EXTREME:             return "GUS Extreme";
    case SND_CARD_TYPE_GUS_ACE:                 return "GUS ACE";
    case SND_CARD_TYPE_GUS_MAX:                 return "GUS MAX";
    case SND_CARD_TYPE_AMD_INTERWAVE:           return "AMD Interwave";
      /* Sound Blaster */
    case SND_CARD_TYPE_SB_10:                   return "Sound Blaster 10";
    case SND_CARD_TYPE_SB_20:                   return "Sound Blaster 20";
    case SND_CARD_TYPE_SB_PRO:                  return "Sound Blaster Pro";
    case SND_CARD_TYPE_SB_16:                   return "Sound Blaster 16";
    case SND_CARD_TYPE_SB_AWE:                  return "Sound Blaster AWE";
      /* Various */
    case SND_CARD_TYPE_ESS_ES1688:              return "ESS AudioDrive ESx688";
    case SND_CARD_TYPE_OPL3_SA:                 return "Yamaha OPL3 SA";
    case SND_CARD_TYPE_MOZART:                  return "OAK Mozart";
    case SND_CARD_TYPE_S3_SONICVIBES:           return "S3 SonicVibes";
    case SND_CARD_TYPE_ENS1370:                 return "Ensoniq ES1370";
    case SND_CARD_TYPE_ENS1371:                 return "Ensoniq ES1371";
    case SND_CARD_TYPE_CS4232:                  return "CS4232/CS4232A";
    case SND_CARD_TYPE_CS4236:                  return "CS4235/CS4236B/CS4237B/CS4238B/CS4239";
    case SND_CARD_TYPE_AMD_INTERWAVE_STB:       return "AMD InterWave + TEA6330T";
    case SND_CARD_TYPE_ESS_ES1938:              return "ESS Solo-1 ES1938";
    case SND_CARD_TYPE_ESS_ES18XX:              return "ESS AudioDrive ES18XX";
    case SND_CARD_TYPE_CS4231:                  return "CS4231";
    case SND_CARD_TYPE_SERIAL:                  return "Serial MIDI driver";
    case SND_CARD_TYPE_AD1848:                  return "Generic AD1848 driver";
    case SND_CARD_TYPE_TRID4DWAVEDX:            return "Trident 4DWave DX";
    case SND_CARD_TYPE_TRID4DWAVENX:            return "Trident 4DWave NX";
    case SND_CARD_TYPE_SGALAXY:                 return "Aztech Sound Galaxy";
    case SND_CARD_TYPE_CS461X:                  return "Sound Fusion CS4610/12/15";
      /* Turtle Beach WaveFront series */
    case SND_CARD_TYPE_WAVEFRONT:               return "TB WaveFront generic";
    case SND_CARD_TYPE_TROPEZ:                  return "TB Tropez";
    case SND_CARD_TYPE_TROPEZPLUS:              return "TB Tropez+";
    case SND_CARD_TYPE_MAUI:                    return "TB Maui";
    case SND_CARD_TYPE_CMI8330:                 return "C-Media CMI8330";
    case SND_CARD_TYPE_DUMMY:                   return "Dummy Soundcard";
      /* --- */
    case SND_CARD_TYPE_ALS100:                  return "Avance Logic ALS100";
      /* --- */
    case SND_CARD_TYPE_SHARE:                   return "Soundcard share module";
    default:
      if (card_type < SND_CARD_TYPE_LAST)
	return "Unknown";
      return "Invalid";
    }
}

#endif	/* BSE_PCM_DEVICE_CONF_ALSA */
