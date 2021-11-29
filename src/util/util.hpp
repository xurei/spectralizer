/*************************************************************************
 * This file is part of spectralizer
 * github.con/univrsal/spectralizer
 * Copyright 2020 univrsal <universailp@web.de>.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************/

#pragma once

#include <obs-module.h>
#include <vector>

/* Logging */
#define log_src(log_level, format, ...) \
    blog(log_level, "[spectralizer: '%s'] " format, obs_source_get_name(context->source), ##__VA_ARGS__)
#define write_log(log_level, format, ...) blog(log_level, "[spectralizer] " format, ##__VA_ARGS__)

#define debug(format, ...) write_log(LOG_DEBUG, format, ##__VA_ARGS__)
#define info(format, ...) write_log(LOG_INFO, format, ##__VA_ARGS__)
#define warn(format, ...) write_log(LOG_WARNING, format, ##__VA_ARGS__)

/* clang-format off */

#define UTIL_EULER 2.7182818284590452353
#define UTIL_SWAP(a, b) do { typeof(a) tmp = a; a = b; b = tmp; } while (0)
#define UTIL_MAX(a, b)                  (((a) > (b)) ? (a) : (b))
#define UTIL_MIN(a, b)                  (((a) < (b)) ? (a) : (b))
#define UTIL_CLAMP(lower, x, upper)     (UTIL_MIN(upper, UTIL_MAX(x, lower)))
#define T_(v)                           obs_module_text(v)

#define T_SOURCE                        T_("Spectralizer.Source")
#define T_SOURCE_MODE                   T_("Spectralizer.Mode")
#define T_MODE_BARS                     T_("Spectralizer.Mode.Bars")
#define T_MODE_CIRCLE_BARS              T_("Spectralizer.Mode.Circle.Bars")
#define T_MODE_WIRE                     T_("Spectralizer.Mode.Wire")
#define T_STEREO                        T_("Spectralizer.Stereo")
#define T_STEREO_SPACE                  T_("Spectralizer.Stereo.Space")
#define T_DETAIL                        T_("Spectralizer.Detail")
#define T_REFRESH_RATE                  T_("Spectralizer.RefreshRate")
#define T_AUDIO_SOURCE                  T_("Spectralizer.AudioSource")
#define T_AUDIO_SOURCE_NONE             T_("Spectralizer.AudioSource.None")
#define T_SOURCE_MPD                    T_("Spectralizer.Source.Fifo")
#define T_FIFO_PATH                     T_("Spectralizer.Source.Fifo.Path")
#define T_BAR_WIDTH                     T_("Spectralizer.Bar.Width")
#define T_BAR_HEIGHT                    T_("Spectralizer.Bar.Height")
#define T_SAMPLE_RATE                   T_("Spectralizer.SampleRate")
#define T_BAR_SPACING                   T_("Spectralizer.Bar.Space")
#define T_WIRE_SPACING                  T_("Spectralizer.Wire.Space")
#define T_WIRE_HEIGHT                   T_("Spectralizer.Wire.Height")
#define T_COLOR                         T_("Spectralizer.Color")
#define T_GRAVITY                       T_("Spectralizer.Gravity")
#define T_FALLOFF                       T_("Spectralizer.Falloff")
#define T_FILTER_MODE                   T_("Spectralizer.Filter.Mode")
#define T_FILTER_NONE                   T_AUDIO_SOURCE_NONE
#define T_FILTER_MONSTERCAT             T_("Spectralizer.Filter.Monstercat")
#define T_FILTER_SGS                    T_("Spectralizer.Filter.SGS")
#define T_SGS_PASSES                    T_("Spectralizer.Filter.SGS.Passes")
#define T_SGS_POINTS                    T_("Spectralizer.Filter.SGS.Points")
#define T_FILTER_STRENGTH               T_("Spectralizer.Filter.Strength")
#define T_AUTO_CLEAR                    T_("Spectralizer.AutoClear")
#define T_AUTO_SCALE                    T_("Spectralizer.Use.AutoScale")
#define T_SCALE_BOOST                   T_("Spectralizer.Scale.Boost")
#define T_SCALE_SIZE                    T_("Spectralizer.Scale.Size")
#define T_WIRE_MODE_THIN                T_("Spectralizer.Wire.Mode.Thin")
#define T_WIRE_MODE_THICK               T_("Spectralizer.Wire.Mode.Thick")
#define T_WIRE_MODE_FILL                T_("Spectralizer.Wire.Mode.Fill")
#define T_WIRE_MODE_FILL_INVERTED       T_("Spectralizer.Wire.Mode.Fill.Invert")
#define T_WIRE_MODE                     T_("Spectralizer.Wire.Mode")
#define T_WIRE_THICKNESS                T_("Spectralizer.Wire.Thickness")
#define T_LOG_FREQ_SCALE                T_("Spectralizer.LogFreqScale.Enable")
#define T_LOG_FREQ_SCALE_QUAL           T_("Spectralizer.LogFreqScale.Quality")
#define T_LOG_FREQ_SCALE_QUAL_FAST      T_("Spectralizer.LogFreqScale.Quality.Fast")
#define T_LOG_FREQ_SCALE_QUAL_PRECISE   T_("Spectralizer.LogFreqScale.Quality.Precise")
#define T_LOG_FREQ_SCALE_START          T_("Spectralizer.LogFreqScale.Start")
#define T_LOG_FREQ_SCALE_USE_HPF        T_("Spectralizer.LogFreqScale.UseHPF")
#define T_LOG_FREQ_SCALE_HPF_CURVE      T_("Spectralizer.LogFreqScale.HPFCurve")
#define T_OFFSET                        T_("Spectralizer.Offset")
#define T_PADDING                       T_("Spectralizer.Padding")
#define T_EXPONENT                      T_("Spectralizer.Boost")
#define T_EXPONENT_ENABLED              T_("Spectralizer.Boost.Enabled")
#define T_CORNER_ROUNDING               T_("Spectralizer.Corner.Rounding")
#define T_CORNER_RADIUS                 T_("Spectralizer.Corner.Radius")
#define T_CORNER_POINTS                 T_("Spectralizer.Corner.Points")
#define T_UDP_IP                        T_("Spectralizer.UDP.IP")
#define T_UDP_PORT                      T_("Spectralizer.UDP.Port")

#define S_EXPONENT_ENABLED              "boost_enabled"
#define S_EXPONENT                      "boost"
#define S_SOURCE_MODE                   "source_mode"
#define S_STEREO                        "stereo"
#define S_STEREO_SPACE                  "stereo_space"
#define S_DETAIL                        "detail"
#define S_REFRESH_RATE                  "refresh_rate"
#define S_AUDIO_SOURCE                  "audio_source"
#define S_FIFO_PATH                     "fifo_path"
#define S_BAR_WIDTH                     "width"
#define S_BAR_HEIGHT                    "height"
#define S_SAMPLE_RATE                   "sample_rate"
#define S_BAR_SPACE                     "bar_space"
#define S_COLOR                         "color"
#define S_FILTER_MODE                   "filter_mode"
#define S_SGS_PASSES                    "sgs_passes"
#define S_SGS_POINTS                    "sgs_points"
#define S_GRAVITY                       "gravity"
#define S_FALLOFF                       "falloff"
#define S_FILTER_STRENGTH               "filter_strength"
#define S_AUTO_CLEAR                    "auto_clear"
#define S_AUTO_SCALE                    "use_auto_scale"
#define S_SCALE_BOOST                   "scale_boost"
#define S_SCALE_SIZE                    "scale_size"
#define S_WIRE_MODE                     "wire_mode"
#define S_WIRE_THICKNESS                "wire_thickness"
#define S_LOG_FREQ_SCALE                "log_freq_scale"
#define S_LOG_FREQ_SCALE_QUALITY        "log_freq_scale_quality"
#define S_LOG_FREQ_SCALE_START          "log_freq_scale_start"
#define S_LOG_FREQ_SCALE_USE_HPF        "log_freq_scale_use_hpf"
#define S_LOG_FREQ_SCALE_HPF_CURVE      "log_freq_scale_hpf_curve"
#define S_OFFSET                        "offset"
#define S_PADDING                       "padding"
#define S_CORNER_ROUNDING               "round_corners"
#define S_CORNER_RADIUS                 "corner_radius"
#define S_CORNER_POINTS                 "corner_points"
#define S_UDP_IP                        T_("udp_ip")
#define S_UDP_PORT                      T_("udp_port")

enum visual_mode
{
    VM_BARS, VM_CIRCULAR_BARS, VM_WIRE
};

enum wire_mode
{
    WM_THIN, WM_THICK, WM_FILL, WM_FILL_INVERTED
};

enum smooting_mode
{
    SM_NONE = 0,
    SM_MONSTERCAT,
    SM_SGS
};

enum falloff
{
    FO_NONE = 0,
    FO_FILL,
    FO_TOP
};

enum channel_mode
{
    CM_LEFT = 0,
    CM_RIGHT,
    CM_BOTH
};

enum freq_scale
{
    FS_LIN = 0,
    FS_LOG
};

enum log_freq_qual
{
    LFQ_FAST = 0,
    LFQ_PRECISE,
};

struct stereo_sample_frame
{
    int16_t l, r;
};

using pcm_stereo_sample = struct stereo_sample_frame;

namespace defaults {
    extern const bool           stereo;
    extern const visual_mode    visual;
    extern const smooting_mode  smoothing;
    extern const uint32_t       color;

    extern const bool           log_freq_scale;
    extern const log_freq_qual  log_freq_quality;
    extern const double         log_freq_start;
    extern const bool           log_freq_use_hpf;
    extern const double         log_freq_hpf_curve;
    /* constants for log_freq-related options */
    extern const double         log_freq_hpf_curve_max;
    extern const uint32_t       log_freq_quality_fast_detail_mul;
    extern const uint32_t       log_freq_quality_precise_detail_mul;

    extern const uint16_t       detail,
                                cx,
                                cy,
                                fps;

    extern const uint32_t       sample_rate,
                                sample_size;

    extern const double         lfreq_cut,
                                hfreq_cut,
                                falloff_weight,
                                gravity;
    extern const uint32_t       sgs_points,
                                sgs_passes;

    extern const double         mcat_smooth;

    extern const uint16_t       bar_space,
                                bar_width,
                                bar_height,
                                bar_min_height,
                                corner_points;

    extern const uint16_t       wire_thickness;
    extern const enum wire_mode wire_mode;

    extern const char           *fifo_path;
    extern const char           *audio_source;

    extern const bool           use_auto_scale;
    extern const double         scale_boost;
    extern const double         scale_size;

    extern const char *udp_ip;
    extern const uint16_t udp_port;
};

namespace constants {
    extern const int            auto_scale_span;
    extern const double         auto_scaling_reset_window;
    extern const double         auto_scaling_erase_percent;
    /* Amount of deviation needed between short term and long
     * term moving max height averages to trigger an autoscaling reset */
    extern const double         deviation_amount_to_reset;
}

/* clang-format on */
