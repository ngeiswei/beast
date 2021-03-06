// Licensed GNU LGPL v2.1 or later: http://www.gnu.org/licenses/lgpl.html
#ifndef __DAV_GUITAR_H__
#define __DAV_GUITAR_H__

#include <bse/bseplugin.hh>
#include <bse/bsesource.hh>

/* --- object type macros --- */
#define DAV_TYPE_GUITAR              (type_id_guitar)
#define DAV_GUITAR(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), DAV_TYPE_GUITAR, DavGuitar))
#define DAV_GUITAR_CLASS(class)      (G_TYPE_CHECK_CLASS_CAST ((class), DAV_TYPE_GUITAR, DavGuitar))
#define DAV_IS_GUITAR(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), DAV_TYPE_GUITAR))
#define DAV_IS_GUITAR_CLASS(class)   (G_TYPE_CHECK_CLASS_TYPE ((class), DAV_TYPE_GUITAR))
#define DAV_GUITAR_GET_CLASS(object) (G_TYPE_INSTANCE_GET_CLASS ((object), DAV_TYPE_GUITAR, DavGuitarClass))

struct WaveGuide {
  gfloat  freq;
  gfloat  lowpass_data, lowpass_coeff;
  gint    wavelen;
  gint    pos;
  gfloat *data;
};
struct DavGuitar : BseSource {
  gfloat hipass_data, hipass_coeff;
  gint      body_taps[6];
  WaveGuide strings[6];
  WaveGuide body;
  gfloat    trigger_vel;
  gfloat    metallic_factor;
  gfloat    snap_factor;
};
struct DavGuitarClass : BseSourceClass
{};

enum
{
  DAV_GUITAR_OCHANNEL_NONE,
  DAV_GUITAR_OCHANNEL_MONO
};

#endif /* __DAV_GUITAR_H__ */
