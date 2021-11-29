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
#ifdef WIN32
#define NOMINMAX 1
#include <Winsock2.h>
#include <Ws2tcpip.h>
#else
#include <arpa/inet.h> // htons, inet_addr
#include <netinet/in.h> // sockaddr_in
#include <sys/types.h> // uint16_t
#include <sys/socket.h> // socket, sendto
#include <unistd.h> // close
#endif
#include "../util.hpp"
#include "audio_visualizer.hpp"
#include <fftw3.h>
#include <vector>

#define DEAD_BAR_OFFSET 5 /* The last five bars seem to always be silent, so we cut them off */

/* Save some writing */
using doublev = std::vector<double>;
using uint32v = std::vector<uint32_t>;

namespace audio {

class spectrum_visualizer : public audio_visualizer {
    uint32_t m_last_bar_count;
    double m_last_log_freq_start;
    bool m_sleeping = false;
    float m_sleep_count = 0.f;
    /* fft calculation vars */
    size_t m_fftw_results;
    double *m_fftw_input_left;
    double *m_fftw_input_right;
    /* log scale related containers */
    doublev m_bar_freq;
    doublev m_fftw_magnitudes;

    fftw_complex *m_fftw_output_left;
    fftw_complex *m_fftw_output_right;

    fftw_plan m_fftw_plan_left;
    fftw_plan m_fftw_plan_right;

    /* Frequency cutoff variables */
    uint32v m_low_cutoff_frequencies;
    uint32v m_high_cutoff_frequencies;
    doublev m_frequency_constants_per_bin;

    uint64_t m_silent_runs; /* determines sleep state */

    int sock;
    int udp_threshold = 0;

    bool prepare_fft_input(pcm_stereo_sample *buffer, uint32_t sample_size, double *fftw_input,
                           channel_mode channel_mode);

    void create_spectrum_bars(fftw_complex *fftw_output, size_t fftw_results, int32_t win_height,
                              uint32_t number_of_bars, doublev *bars);

    void generate_bars(uint32_t number_of_bars, size_t fftw_results, const uint32v &low_cutoff_frequencies,
                       const uint32v &high_cutoff_frequencies, const fftw_complex *fftw_output, doublev *bars) const;
    void generate_log_bars(uint32_t number_of_bars, size_t fftw_results, const fftw_complex *fftw_output,
                           doublev &magnitudes, doublev &bars) const;

    void recalculate_cutoff_frequencies(uint32_t number_of_bars, uint32v *low_cutoff_frequencies,
                                        uint32v *high_cutoff_frequencies, doublev *freqconst_per_bin);
    void recalculate_target_log_frequencies(uint32_t number_of_bars);
    void smooth_bars(doublev *bars);
    void apply_falloff(const doublev &bars, doublev *falloff_bars) const;
    void calculate_moving_average_and_std_dev(double new_value, size_t max_number_of_elements, doublev *old_values,
                                              double *moving_average, double *std_dev) const;
    void maybe_reset_scaling_window(double current_max_height, size_t max_number_of_elements, doublev *values,
                                    double *moving_average, double *std_dev);
    void scale_bars(int32_t height, doublev *bars);
    void sgs_smoothing(doublev *bars);
    void monstercat_smoothing(doublev *bars);

protected:
    /* New values are smoothly copied over if smoothing is used
     * otherwise they're directly copied */
    doublev m_bars_left, m_bars_right, m_bars_left_new, m_bars_right_new;
    //    doublev m_bars_falloff_left, m_bars_falloff_right;
    doublev m_previous_max_heights;
    doublev m_monstercat_smoothing_weights;

    gs_vertbuffer_t *make_rounded_rectangle(float height);
    float m_corner_radius = 0;
    std::vector<struct vec2> m_circle_points;

public:
    explicit spectrum_visualizer(source::config *cfg);

    ~spectrum_visualizer() override;

    virtual void update() override;

    void tick(float seconds) override;
};

}
