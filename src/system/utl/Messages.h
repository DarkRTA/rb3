#ifndef UTL_MESSAGES_H
#define UTL_MESSAGES_H
#include "obj/Msg.h"
#include "utl/Symbols.h"
#include "utl/Messages2.h" // IWYU pragma: export
#include "utl/Messages3.h" // IWYU pragma: export
#include "utl/Messages4.h" // IWYU pragma: export

#define LITERAL_MSG(name) Message name##_msg(#name)

extern Message allows_hiding_msg;
extern Message allows_input_to_shell_msg;
extern Message art_loaded_msg;
extern Message auto_script_done_msg;
extern Message block_wipe_in_msg;
extern Message button_pulse_joined_msg;
extern Message button_pulse_unjoined_msg;
extern Message cam_cut_msg;
extern Message cancel_find_override_msg;
extern Message change_file_msg;
extern Message change_proxies_msg;
extern Message char_edit_flow_msg;
extern Message cheat_init_msg;
extern Message check_disconnect_msg;
extern Message checkout_failed_msg;
extern Message choose_char_flow_msg;
extern Message choose_colors_msg;
extern Message choose_finish_msg;
extern Message clear_all_msg;
extern Message clear_difficulty_restriction_msg;
extern Message clear_initially_selected_tour_msg;
extern Message clear_lighting_msg;
extern Message clear_pics_msg;
extern Message client_update_goal_info_msg;
extern Message coda_blown_msg;
extern Message coda_end_script_msg;
extern Message coda_success_msg;
extern Message controllers_changed_msg;
extern Message credits_done_msg;
extern Message deactivate_msg;
extern Message deploy_msg;
extern Message disable_msg;
extern Message disable_facehair_msg;
extern Message disconnected_msg;
extern Message dlc_motd_msg;
extern Message done_msg;
extern Message drum_fill_complete_msg;
extern Message enable_msg;
extern Message enable_facehair_msg;
extern Message enable_player_msg;
extern Message enable_retry_msg;
extern Message end_chord_legend_msg;
extern Message end_chord_legend_no_rollback_msg;
extern Message end_chordbook_msg;
extern Message end_game_end_msg;
extern Message end_play_msg;
extern Message end_solo_msg;
extern Message endgame_vocals_high_msg;
extern Message endgame_vocals_low_msg;
extern Message endgame_vocals_medium_msg;
extern Message endgame_vocals_none_msg;
extern Message enter_msg;
extern Message enum_finished_msg;
extern Message enum_start_msg;
extern Message exit_msg;
extern Message exit_complete_msg;
extern Message feedback_off_msg;
extern Message feedback_on_msg;
extern Message fill_progress_and_reset_msg;
extern Message filter_clips_msg;
extern Message finish_load_msg;
extern Message finished_coda_msg;
extern Message game_outro_msg;
extern Message get_backscreen_msg;
extern Message get_band_logo_msg;
extern Message get_customize_slot_msg;
extern Message get_diffselect_screen_msg;
extern Message get_focus_is_harmony_msg;
extern Message get_focus_is_prodrums_msg;
extern Message get_focus_track_type_msg;
extern Message get_initially_selected_tour_msg;
extern Message get_musiclibrary_backscreen_msg;
extern Message get_musiclibrary_nextscreen_msg;
extern Message get_remote_status_msg;
extern Message get_selected_details_entry_index_msg;
extern Message get_selected_filter_index_msg;
extern Message get_selected_index_msg;
extern Message get_selected_tourdesc_index_msg;

#endif
