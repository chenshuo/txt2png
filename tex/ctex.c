/*4:*/
/*9:*/

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define odd(X) ((X) & 1)
#define chr(X) ((unsigned char)(X))
#define ord(X) ((int)(X))

#if __SIZEOF_FLOAT__ == 4
typedef float float32_t;
#else
#error float type must have size 4
#endif

#define banner "This is TeX, Version 3.141592653 (HINT)"

#define mem_bot 0

#define mem_top 30000

#define font_base 0

#define hash_size 2100

#define hash_prime 1777
#define hyph_size 307

#define done6 36
#define incr(X) X = X + 1
#define decr(X) X = X - 1
#define negate(X) X = -X
#define loop while (true)
#define do_nothing
#define empty 0

#define text_char unsigned char
#define first_text_char 0
#define last_text_char 255

#define null_code 00
#define carriage_return 015
#define invalid_code 0177

#define reset_OK(X) erstat(X) == 0
#define rewrite_OK(X) erstat(X) == 0

#define t_open_in term_in.f = stdin
#define t_open_out term_out.f = stdout

#define update_terminal fflush(term_out.f)
#define clear_terminal fflush(term_in.f)
#define wake_up_terminal do_nothing

#define loc cur_input.loc_field

#define si(X) X
#define so(X) X

#define length(X) (str_start[X + 1] - str_start[X])

#define cur_length (pool_ptr - str_start[str_ptr])

#define append_char(X)          \
  {                             \
    str_pool[pool_ptr] = si(X); \
    incr(pool_ptr);             \
  }
#define flush_char decr(pool_ptr)
#define str_room(X)                                     \
  {                                                     \
    if (pool_ptr + X > pool_size)                       \
      overflow("pool size", pool_size - init_pool_ptr); \
  }

#define flush_string               \
  {                                \
    decr(str_ptr);                 \
    pool_ptr = str_start[str_ptr]; \
  }

#define app_lc_hex(X) \
  l = X;              \
  if (l < 10) append_char(l + '0') else append_char(l - 10 + 'a')

#define bad_pool(X)        \
  {                        \
    wake_up_terminal;      \
    write_ln(term_out, X); \
    a_close(&pool_file);   \
    return false;          \
  }
#define no_print 16
#define term_only 17
#define log_only 18
#define term_and_log 19
#define pseudo 20
#define new_string 21
#define max_selector 21

#define print_ASCII print

#define prompt_input(X) \
  {                     \
    wake_up_terminal;   \
    print_str(X);       \
    term_input();       \
  }

#define batch_mode 0
#define nonstop_mode 1
#define scroll_mode 2
#define error_stop_mode 3
#define print_err(X)                                      \
  {                                                       \
    if (interaction == error_stop_mode) wake_up_terminal; \
    print_nl("! ");                                       \
    print_str(X);                                         \
  }

#define spotless 0
#define warning_issued 1
#define error_message_issued 2
#define fatal_error_stop 3

#define hlp1(X)     \
  help_line[0] = X; \
  }
#define hlp2(X)     \
  help_line[1] = X; \
  hlp1
#define hlp3(X)     \
  help_line[2] = X; \
  hlp2
#define hlp4(X)     \
  help_line[3] = X; \
  hlp3
#define hlp5(X)     \
  help_line[4] = X; \
  hlp4
#define hlp6(X)     \
  help_line[5] = X; \
  hlp5
#define help0 help_ptr = 0
#define help1     \
  {               \
    help_ptr = 1; \
    hlp1
#define help2     \
  {               \
    help_ptr = 2; \
    hlp2
#define help3     \
  {               \
    help_ptr = 3; \
    hlp3
#define help4     \
  {               \
    help_ptr = 4; \
    hlp4
#define help5     \
  {               \
    help_ptr = 5; \
    hlp5
#define help6     \
  {               \
    help_ptr = 6; \
    hlp6

#define succumb                                                    \
  {                                                                \
    if (interaction == error_stop_mode) interaction = scroll_mode; \
    if (log_opened) error();                                       \
    if (interaction > batch_mode) debug_help();                    \
    history = fatal_error_stop;                                    \
    jump_out();                                                    \
  }

#define check_interrupt                           \
  {                                               \
    if (interrupt != 0) pause_for_instructions(); \
  }

#define unity 0200000
#define two 0400000

#define nx_plus_y(X, Y, Z) mult_and_add(X, Y, Z, 07777777777)
#define mult_integers(X, Y) mult_and_add(X, Y, 0, 017777777777)

#define inf_bad 10000

#define set_glue_ratio_zero(X) X = 0.0
#define set_glue_ratio_one(X) X = 1.0
#define float(X) ((double)(X))
#define unfloat(X) ((glue_ratio)(X))
#define float_constant(X) ((double)(X))

#define min_quarterword 0
#define max_quarterword 255
#define min_halfword 0
#define max_halfword 65535

#define qi(X) X + min_quarterword

#define qo(X) X - min_quarterword

#define hi(X) X + min_halfword

#define ho(X) X - min_halfword

#define sc i

#define pointer halfword
#define null min_halfword

#define link(X) mem[X].hh.rh
#define info(X) mem[X].hh.lh

#define free_avail(X) \
  {                   \
    link(X) = avail;  \
    avail = X;        \
    decr_dyn_used;    \
  }

#define fast_get_avail(X) \
  {                       \
    X = avail;            \
    if (X == null)        \
      X = get_avail();    \
    else {                \
      avail = link(X);    \
      link(X) = null;     \
      incr_dyn_used;      \
    }                     \
  }

#define empty_flag max_halfword
#define is_empty(X) (link(X) == empty_flag)
#define node_size info
#define llink(X) info(X + 1)
#define rlink(X) link(X + 1)

#define type(X) mem[X].hh.b0
#define subtype(X) mem[X].hh.b1

#define is_char_node(X) (X >= hi_mem_min)

#define font type
#define character subtype

#define hlist_node 0
#define box_node_size 7
#define width_offset 1
#define depth_offset 2
#define height_offset 3
#define width(X) mem[X + width_offset].sc
#define depth(X) mem[X + depth_offset].sc
#define height(X) mem[X + height_offset].sc
#define shift_amount(X) mem[X + 4].sc
#define list_offset 5
#define list_ptr(X) link(X + list_offset)
#define glue_order(X) subtype(X + list_offset)
#define glue_sign(X) type(X + list_offset)
#define normal 0
#define stretching 1
#define shrinking 2
#define glue_offset 6
#define glue_set(X) mem[X + glue_offset].gr

#define vlist_node 1

#define rule_node 2
#define rule_node_size 4
#define null_flag -010000000000
#define is_running(X) (X == null_flag)

#define ins_node 3
#define ins_node_size 5
#define float_cost(X) mem[X + 1].i
#define ins_ptr(X) info(X + 4)
#define split_top_ptr(X) link(X + 4)

#define mark_node 4
#define small_node_size 2
#define mark_ptr(X) mem[X + 1].i

#define adjust_node 5
#define adjust_ptr mark_ptr

#define ligature_node 6
#define lig_char(X) X + 1
#define lig_ptr(X) link(lig_char(X))

#define disc_node 7
#define replace_count subtype
#define pre_break llink
#define post_break rlink

#define whatsit_node 8

#define math_node 9
#define before 0
#define after 1

#define precedes_break(X) (type(X) < math_node)
#define non_discardable(X) (type(X) < math_node)

#define glue_node 10
#define cond_math_glue 98
#define mu_glue 99
#define a_leaders 100
#define c_leaders 101
#define x_leaders 102
#define glue_ptr llink
#define leader_ptr rlink

#define glue_spec_size 4
#define glue_ref_count(X) link(X)
#define stretch(X) mem[X + 2].sc
#define shrink(X) mem[X + 3].sc
#define stretch_order type
#define shrink_order subtype
#define fil 1
#define fill 2
#define filll 3

#define kern_node 11
#define explicit 1
#define acc_kern 2

#define penalty_node 12
#define inf_penalty inf_bad
#define eject_penalty (-inf_penalty)
#define penalty(X) mem[X + 1].i

#define unset_node 13
#define glue_stretch(X) mem[X + glue_offset].sc
#define glue_shrink shift_amount
#define span_count subtype

#define zero_glue mem_bot
#define fil_glue zero_glue + glue_spec_size
#define fill_glue fil_glue + glue_spec_size
#define ss_glue fill_glue + glue_spec_size
#define fil_neg_glue ss_glue + glue_spec_size
#define lo_mem_stat_max fil_neg_glue + glue_spec_size - 1

#define page_ins_head mem_top
#define contrib_head mem_top - 1
#define page_head mem_top - 2
#define temp_head mem_top - 3
#define hold_head mem_top - 4
#define adjust_head mem_top - 5
#define active mem_top - 7
#define align_head mem_top - 8
#define end_span mem_top - 9
#define omit_template mem_top - 10
#define null_list mem_top - 11
#define lig_trick mem_top - 12
#define garbage mem_top - 12
#define backup_head mem_top - 13
#define hi_mem_stat_min mem_top - 13

#define hi_mem_stat_usage 14

#define node_list_display(X) \
  {                          \
    append_char('.');        \
    show_node_list(X);       \
    flush_char;              \
  }

#define token_ref_count(X) info(X)

#define fast_delete_glue_ref(X)     \
  {                                 \
    if (glue_ref_count(X) == null)  \
      free_node(X, glue_spec_size); \
    else                            \
      decr(glue_ref_count(X));      \
  }

#define add_token_ref(X) incr(token_ref_count(X))
#define add_glue_ref(X) incr(glue_ref_count(X))

#define escape 0

#define relax 0
#define left_brace 1
#define right_brace 2
#define math_shift 3
#define tab_mark 4
#define car_ret 5
#define out_param 5
#define mac_param 6
#define sup_mark 7
#define sub_mark 8
#define ignore 9
#define endv 9
#define spacer 10
#define letter 11
#define other_char 12
#define active_char 13
#define par_end 13
#define match 13
#define comment 14
#define end_match 14
#define stop 14
#define invalid_char 15
#define delim_num 15
#define max_char_code 15

#define char_num 16
#define math_char_num 17
#define mark 18
#define xray 19
#define make_box 20
#define hmove 21
#define vmove 22
#define un_hbox 23
#define un_vbox 24
#define remove_item 25

#define hskip 26
#define vskip 27
#define mskip 28
#define kern 29
#define mkern 30
#define leader_ship 31
#define halign 32
#define valign 33
#define no_align 34
#define vrule 35
#define hrule 36
#define insert 37
#define vadjust 38
#define ignore_spaces 39
#define after_assignment 40
#define after_group 41
#define break_penalty 42
#define start_par 43
#define ital_corr 44
#define accent 45
#define math_accent 46
#define discretionary 47
#define eq_no 48
#define left_right 49
#define math_comp 50
#define limit_switch 51
#define above 52
#define math_style 53
#define math_choice 54
#define non_script 55
#define vcenter 56
#define case_shift 57
#define message 58
#define extension 59
#define in_stream 60
#define begin_group 61
#define end_group 62
#define omit 63
#define ex_space 64
#define no_boundary 65
#define radical 66
#define end_cs_name 67
#define min_internal 68
#define char_given 68
#define math_given 69
#define last_item 70

#define max_non_prefixed_command 70

#define toks_register 71
#define assign_toks 72
#define assign_int 73
#define assign_dimen 74
#define assign_glue 75
#define assign_mu_glue 76
#define assign_font_dimen 77
#define assign_font_int 78

#define set_aux 79
#define set_prev_graf 80
#define set_page_dimen 81
#define set_page_int 82

#define set_box_dimen 83
#define set_shape 84
#define def_code 85
#define def_family 86
#define set_font 87
#define def_font 88
#define register 89
#define max_internal 89
#define advance 90
#define multiply 91
#define divide 92
#define prefix 93
#define let 94
#define shorthand_def 95
#define read_to_cs 96
#define def 97
#define set_box 98
#define hyph_data 99
#define set_interaction 100
#define max_command 100

#define undefined_cs (max_command + 1)
#define expand_after (max_command + 2)
#define no_expand (max_command + 3)
#define input (max_command + 4)
#define if_test (max_command + 5)
#define fi_or_else (max_command + 6)
#define cs_name (max_command + 7)
#define convert (max_command + 8)
#define the (max_command + 9)
#define top_bot_mark (max_command + 10)
#define call (max_command + 11)
#define long_call (max_command + 12)
#define outer_call (max_command + 13)
#define long_outer_call (max_command + 14)
#define end_template (max_command + 15)
#define dont_expand (max_command + 16)
#define glue_ref (max_command + 17)
#define shape_ref (max_command + 18)
#define box_ref (max_command + 19)
#define data (max_command + 20)

#define vmode 1
#define hmode (vmode + max_command + 1)
#define mmode (hmode + max_command + 1)

#define ignore_depth -65536000

#define mode cur_list.mode_field
#define head cur_list.head_field
#define tail cur_list.tail_field
#define prev_graf cur_list.pg_field
#define aux cur_list.aux_field
#define prev_depth aux.sc
#define space_factor aux.hh.lh
#define clang aux.hh.rh
#define incompleat_noad aux.i
#define mode_line cur_list.ml_field

#define tail_append(X) \
  {                    \
    link(tail) = X;    \
    tail = link(tail); \
  }

#define eq_level_field(X) X.hh.b1
#define eq_type_field(X) X.hh.b0
#define equiv_field(X) X.hh.rh
#define eq_level(X) eq_level_field(eqtb[X])
#define eq_type(X) eq_type_field(eqtb[X])
#define equiv(X) equiv_field(eqtb[X])
#define level_zero min_quarterword
#define level_one (level_zero + 1)

#define active_base 1
#define single_base (active_base + 256)
#define null_cs (single_base + 256)
#define hash_base (null_cs + 1)
#define frozen_control_sequence (hash_base + hash_size)
#define frozen_protection frozen_control_sequence
#define frozen_cr (frozen_control_sequence + 1)
#define frozen_end_group (frozen_control_sequence + 2)
#define frozen_right (frozen_control_sequence + 3)
#define frozen_fi (frozen_control_sequence + 4)
#define frozen_end_template (frozen_control_sequence + 5)
#define frozen_endv (frozen_control_sequence + 6)
#define frozen_relax (frozen_control_sequence + 7)
#define end_write (frozen_control_sequence + 8)
#define frozen_dont_expand (frozen_control_sequence + 9)

#define frozen_null_font (frozen_control_sequence + 10)

#define font_id_base (frozen_null_font - font_base)

#define undefined_control_sequence (frozen_null_font + 257)
#define glue_base (undefined_control_sequence + 1)

#define line_skip_code 0
#define baseline_skip_code 1
#define par_skip_code 2
#define above_display_skip_code 3
#define below_display_skip_code 4
#define above_display_short_skip_code 5

#define below_display_short_skip_code 6

#define left_skip_code 7
#define right_skip_code 8
#define top_skip_code 9
#define split_top_skip_code 10
#define tab_skip_code 11
#define space_skip_code 12
#define xspace_skip_code 13
#define par_fill_skip_code 14
#define thin_mu_skip_code 15
#define med_mu_skip_code 16
#define thick_mu_skip_code 17
#define glue_pars 18
#define skip_base (glue_base + glue_pars)
#define mu_skip_base (skip_base + 256)
#define local_base (mu_skip_base + 256)

#define skip(X) equiv(skip_base + X)
#define mu_skip(X) equiv(mu_skip_base + X)
#define glue_par(X) equiv(glue_base + X)
#define line_skip glue_par(line_skip_code)
#define baseline_skip glue_par(baseline_skip_code)
#define par_skip glue_par(par_skip_code)
#define above_display_skip glue_par(above_display_skip_code)
#define below_display_skip glue_par(below_display_skip_code)
#define above_display_short_skip glue_par(above_display_short_skip_code)
#define below_display_short_skip glue_par(below_display_short_skip_code)
#define left_skip glue_par(left_skip_code)
#define right_skip glue_par(right_skip_code)
#define top_skip glue_par(top_skip_code)
#define split_top_skip glue_par(split_top_skip_code)
#define tab_skip glue_par(tab_skip_code)
#define space_skip glue_par(space_skip_code)
#define xspace_skip glue_par(xspace_skip_code)
#define par_fill_skip glue_par(par_fill_skip_code)
#define thin_mu_skip glue_par(thin_mu_skip_code)
#define med_mu_skip glue_par(med_mu_skip_code)
#define thick_mu_skip glue_par(thick_mu_skip_code)

#define par_shape_loc local_base
#define output_routine_loc (local_base + 1)
#define every_par_loc (local_base + 2)
#define every_math_loc (local_base + 3)
#define every_display_loc (local_base + 4)
#define every_hbox_loc (local_base + 5)
#define every_vbox_loc (local_base + 6)
#define every_job_loc (local_base + 7)
#define every_cr_loc (local_base + 8)
#define err_help_loc (local_base + 9)
#define toks_base (local_base + 10)
#define box_base (toks_base + 256)
#define cur_font_loc (box_base + 256)
#define math_font_base (cur_font_loc + 1)
#define cat_code_base (math_font_base + 48)

#define lc_code_base (cat_code_base + 256)
#define uc_code_base (lc_code_base + 256)
#define sf_code_base (uc_code_base + 256)
#define math_code_base (sf_code_base + 256)
#define int_base (math_code_base + 256)

#define par_shape_ptr equiv(par_shape_loc)
#define output_routine equiv(output_routine_loc)
#define every_par equiv(every_par_loc)
#define every_math equiv(every_math_loc)
#define every_display equiv(every_display_loc)
#define every_hbox equiv(every_hbox_loc)
#define every_vbox equiv(every_vbox_loc)
#define every_job equiv(every_job_loc)
#define every_cr equiv(every_cr_loc)
#define err_help equiv(err_help_loc)
#define toks(X) equiv(toks_base + X)
#define box(X) equiv(box_base + X)
#define cur_font equiv(cur_font_loc)
#define fam_fnt(X) equiv(math_font_base + X)
#define cat_code(X) equiv(cat_code_base + X)
#define lc_code(X) equiv(lc_code_base + X)
#define uc_code(X) equiv(uc_code_base + X)
#define sf_code(X) equiv(sf_code_base + X)
#define math_code(X) equiv(math_code_base + X)

#define null_font font_base
#define var_code 070000

#define pretolerance_code 0
#define tolerance_code 1
#define line_penalty_code 2
#define hyphen_penalty_code 3
#define ex_hyphen_penalty_code 4
#define club_penalty_code 5
#define widow_penalty_code 6
#define display_widow_penalty_code 7
#define broken_penalty_code 8
#define bin_op_penalty_code 9
#define rel_penalty_code 10
#define pre_display_penalty_code 11

#define post_display_penalty_code 12

#define inter_line_penalty_code 13
#define double_hyphen_demerits_code 14
#define final_hyphen_demerits_code 15
#define adj_demerits_code 16
#define mag_code 17
#define delimiter_factor_code 18
#define looseness_code 19
#define time_code 20
#define day_code 21
#define month_code 22
#define year_code 23
#define show_box_breadth_code 24
#define show_box_depth_code 25
#define hbadness_code 26
#define vbadness_code 27
#define pausing_code 28
#define tracing_online_code 29
#define tracing_macros_code 30
#define tracing_stats_code 31
#define tracing_paragraphs_code 32
#define tracing_pages_code 33
#define tracing_output_code 34
#define tracing_lost_chars_code 35
#define tracing_commands_code 36
#define tracing_restores_code 37
#define uc_hyph_code 38
#define output_penalty_code 39
#define max_dead_cycles_code 40
#define hang_after_code 41
#define floating_penalty_code 42
#define global_defs_code 43
#define cur_fam_code 44
#define escape_char_code 45
#define default_hyphen_char_code 46
#define default_skew_char_code 47
#define end_line_char_code 48
#define new_line_char_code 49
#define language_code 50
#define left_hyphen_min_code 51
#define right_hyphen_min_code 52
#define holding_inserts_code 53
#define error_context_lines_code 54
#define int_pars 55
#define count_base (int_base + int_pars)
#define del_code_base (count_base + 256)
#define dimen_base (del_code_base + 256)

#define del_code(X) eqtb[del_code_base + X].i
#define count(X) eqtb[count_base + X].i
#define int_par(X) eqtb[int_base + X].i
#define pretolerance int_par(pretolerance_code)
#define tolerance int_par(tolerance_code)
#define line_penalty int_par(line_penalty_code)
#define hyphen_penalty int_par(hyphen_penalty_code)
#define ex_hyphen_penalty int_par(ex_hyphen_penalty_code)
#define club_penalty int_par(club_penalty_code)
#define widow_penalty int_par(widow_penalty_code)
#define display_widow_penalty int_par(display_widow_penalty_code)
#define broken_penalty int_par(broken_penalty_code)
#define bin_op_penalty int_par(bin_op_penalty_code)
#define rel_penalty int_par(rel_penalty_code)
#define pre_display_penalty int_par(pre_display_penalty_code)
#define post_display_penalty int_par(post_display_penalty_code)
#define inter_line_penalty int_par(inter_line_penalty_code)
#define double_hyphen_demerits int_par(double_hyphen_demerits_code)
#define final_hyphen_demerits int_par(final_hyphen_demerits_code)
#define adj_demerits int_par(adj_demerits_code)
#define mag int_par(mag_code)
#define delimiter_factor int_par(delimiter_factor_code)
#define looseness int_par(looseness_code)
#define time int_par(time_code)
#define day int_par(day_code)
#define month int_par(month_code)
#define year int_par(year_code)
#define show_box_breadth int_par(show_box_breadth_code)
#define show_box_depth int_par(show_box_depth_code)
#define hbadness int_par(hbadness_code)
#define vbadness int_par(vbadness_code)
#define pausing int_par(pausing_code)
#define tracing_online int_par(tracing_online_code)
#define tracing_macros int_par(tracing_macros_code)
#define tracing_stats int_par(tracing_stats_code)
#define tracing_paragraphs int_par(tracing_paragraphs_code)
#define tracing_pages int_par(tracing_pages_code)
#define tracing_output int_par(tracing_output_code)
#define tracing_lost_chars int_par(tracing_lost_chars_code)
#define tracing_commands int_par(tracing_commands_code)
#define tracing_restores int_par(tracing_restores_code)
#define uc_hyph int_par(uc_hyph_code)
#define output_penalty int_par(output_penalty_code)
#define max_dead_cycles int_par(max_dead_cycles_code)
#define hang_after int_par(hang_after_code)
#define floating_penalty int_par(floating_penalty_code)
#define global_defs int_par(global_defs_code)
#define cur_fam int_par(cur_fam_code)
#define escape_char int_par(escape_char_code)
#define default_hyphen_char int_par(default_hyphen_char_code)
#define default_skew_char int_par(default_skew_char_code)
#define end_line_char int_par(end_line_char_code)
#define new_line_char int_par(new_line_char_code)
#define language int_par(language_code)
#define left_hyphen_min int_par(left_hyphen_min_code)
#define right_hyphen_min int_par(right_hyphen_min_code)
#define holding_inserts int_par(holding_inserts_code)
#define error_context_lines int_par(error_context_lines_code)

#define par_indent_code 0
#define math_surround_code 1
#define line_skip_limit_code 2
#define hsize_code 3
#define vsize_code 4
#define max_depth_code 5
#define split_max_depth_code 6
#define box_max_depth_code 7
#define hfuzz_code 8
#define vfuzz_code 9
#define delimiter_shortfall_code 10
#define null_delimiter_space_code 11
#define script_space_code 12
#define pre_display_size_code 13
#define display_width_code 14
#define display_indent_code 15
#define overfull_rule_code 16
#define hang_indent_code 17
#define h_offset_code 18
#define v_offset_code 19
#define emergency_stretch_code 20
#define dimen_pars 21
#define scaled_base (dimen_base + dimen_pars)

#define eqtb_size (scaled_base + 255)

#define dimen(X) eqtb[scaled_base + X].sc
#define dimen_par(X) eqtb[dimen_base + X].sc
#define par_indent dimen_par(par_indent_code)
#define math_surround dimen_par(math_surround_code)
#define line_skip_limit dimen_par(line_skip_limit_code)
#define hsize dimen_par(hsize_code)
#define vsize dimen_par(vsize_code)
#define max_depth dimen_par(max_depth_code)
#define split_max_depth dimen_par(split_max_depth_code)
#define box_max_depth dimen_par(box_max_depth_code)
#define hfuzz dimen_par(hfuzz_code)
#define vfuzz dimen_par(vfuzz_code)
#define delimiter_shortfall dimen_par(delimiter_shortfall_code)
#define null_delimiter_space dimen_par(null_delimiter_space_code)
#define script_space dimen_par(script_space_code)
#define pre_display_size dimen_par(pre_display_size_code)
#define display_width dimen_par(display_width_code)
#define display_indent dimen_par(display_indent_code)
#define overfull_rule dimen_par(overfull_rule_code)
#define hang_indent dimen_par(hang_indent_code)
#define h_offset dimen_par(h_offset_code)
#define v_offset dimen_par(v_offset_code)
#define emergency_stretch dimen_par(emergency_stretch_code)

#define next(X) hash[X].lh
#define text(X) hash[X].rh
#define hash_is_full (hash_used == hash_base)
#define font_id_text(X) text(font_id_base + X)

#define save_type(X) save_stack[X].hh.b0
#define save_level(X) save_stack[X].hh.b1

#define save_index(X) save_stack[X].hh.rh

#define restore_old_value 0
#define restore_zero 1
#define insert_token 2
#define level_boundary 3

#define bottom_level 0
#define simple_group 1
#define hbox_group 2
#define adjusted_hbox_group 3
#define vbox_group 4
#define vtop_group 5
#define align_group 6
#define no_align_group 7
#define output_group 8
#define math_group 9
#define disc_group 10
#define insert_group 11
#define vcenter_group 12
#define math_choice_group 13
#define semi_simple_group 14
#define math_shift_group 15
#define math_left_group 16
#define max_group_code 16

#define check_full_save_stack                                             \
  if (save_ptr > max_save_stack) {                                        \
    max_save_stack = save_ptr;                                            \
    if (max_save_stack > save_size - 6) overflow("save size", save_size); \
  }

#define saved(X) save_stack[save_ptr + X].i

#define cs_token_flag 07777

#define left_brace_token 00400
#define left_brace_limit 01000
#define right_brace_token 01000
#define right_brace_limit 01400
#define math_shift_token 01400
#define tab_token 02000
#define out_param_token 02400
#define space_token 05040
#define letter_token 05400
#define other_token 06000
#define match_token 06400
#define end_match_token 07000

#define chr_cmd(X)         \
  {                        \
    print_str(X);          \
    print_ASCII(chr_code); \
  }

#define state cur_input.state_field
#define index cur_input.index_field
#define start cur_input.start_field
#define limit cur_input.limit_field
#define name cur_input.name_field

#define mid_line 1
#define skip_blanks (2 + max_char_code)
#define new_line (3 + max_char_code + max_char_code)

#define terminal_input (name == 0)
#define cur_file input_file[index]

#define skipping 1
#define defining 2
#define matching 3
#define aligning 4
#define absorbing 5

#define token_list 0
#define token_type index
#define param_start limit
#define parameter 0
#define u_template 1
#define v_template 2
#define backed_up 3
#define inserted 4
#define macro 5
#define output_text 6
#define every_par_text 7
#define every_math_text 8
#define every_display_text 9
#define every_hbox_text 10
#define every_vbox_text 11
#define every_job_text 12
#define every_cr_text 13
#define mark_text 14
#define write_text 15

#define begin_pseudoprint  \
  {                        \
    l = tally;             \
    tally = 0;             \
    selector = pseudo;     \
    trick_count = 1000000; \
  }
#define set_trick_count                                     \
  {                                                         \
    first_count = tally;                                    \
    trick_count = tally + 1 + error_line - half_error_line; \
    if (trick_count < error_line) trick_count = error_line; \
  }

#define push_input                                                           \
  {                                                                          \
    if (input_ptr > max_in_stack) {                                          \
      max_in_stack = input_ptr;                                              \
      if (input_ptr == stack_size) overflow("input stack size", stack_size); \
    }                                                                        \
    input_stack[input_ptr] = cur_input;                                      \
    incr(input_ptr);                                                         \
  }

#define pop_input                       \
  {                                     \
    decr(input_ptr);                    \
    cur_input = input_stack[input_ptr]; \
  }

#define back_list(X) begin_token_list(X, backed_up)
#define ins_list(X) begin_token_list(X, inserted)

#define any_state_plus(X) \
  case mid_line + X:      \
  case skip_blanks + X:   \
  case new_line + X

#define add_delims_to(X)                                                \
  X + math_shift : X + tab_mark : X + mac_param : X + sub_mark : X +    \
                                                                 letter \
      : X +                                                             \
        other_char

#define is_hex(X) (((X >= '0') && (X <= '9')) || ((X >= 'a') && (X <= 'f')))
#define hex_to_cur_chr                 \
  if (c <= '9')                        \
    cur_chr = c - '0';                 \
  else                                 \
    cur_chr = c - 'a' + 10;            \
  if (cc <= '9')                       \
    cur_chr = 16 * cur_chr + cc - '0'; \
  else                                 \
    cur_chr = 16 * cur_chr + cc - 'a' + 10

#define no_expand_flag 257

#define end_line_char_inactive (end_line_char < 0) || (end_line_char > 255)

#define store_new_token(X) \
  {                        \
    q = get_avail();       \
    link(p) = q;           \
    info(q) = X;           \
    p = q;                 \
  }
#define fast_store_new_token(X) \
  {                             \
    fast_get_avail(q);          \
    link(p) = q;                \
    info(q) = X;                \
    p = q;                      \
  }

#define top_mark_code 0
#define first_mark_code 1
#define bot_mark_code 2
#define split_first_mark_code 3
#define split_bot_mark_code 4
#define top_mark cur_mark[top_mark_code]
#define first_mark cur_mark[first_mark_code]
#define bot_mark cur_mark[bot_mark_code]
#define split_first_mark cur_mark[split_first_mark_code]
#define split_bot_mark cur_mark[split_bot_mark_code]

#define int_val 0
#define dimen_val 1
#define glue_val 2
#define mu_val 3
#define ident_val 4
#define tok_val 5

#define scanned_result_end(X) \
  cur_val_level = X;          \
  }
#define scanned_result(X) \
  {                       \
    cur_val = X;          \
    scanned_result_end

#define input_line_no_code (glue_val + 1)
#define badness_code (glue_val + 2)

#define max_dimen 07777777777

#define octal_token (other_token + '\'')
#define hex_token (other_token + '"')
#define alpha_token (other_token + '`')
#define point_token (other_token + '.')
#define continental_point_token (other_token + ',')

#define infinity 017777777777
#define zero_token (other_token + '0')
#define A_token (letter_token + 'A')
#define other_A_token (other_token + 'A')

#define scan_normal_dimen scan_dimen(false, false, false)

#define set_conversion_end(X) \
  denom = X;                  \
  }
#define set_conversion(X) \
  {                       \
    num = X;              \
    set_conversion_end

#define default_rule 26214

#define number_code 0
#define roman_numeral_code 1
#define string_code 2
#define meaning_code 3
#define font_name_code 4
#define job_name_code 5

#define closed 2
#define just_open 1

#define if_char_code 0
#define if_cat_code 1
#define if_int_code 2
#define if_dim_code 3
#define if_odd_code 4
#define if_vmode_code 5
#define if_hmode_code 6
#define if_mmode_code 7
#define if_inner_code 8
#define if_void_code 9
#define if_hbox_code 10
#define if_vbox_code 11
#define ifx_code 12
#define if_eof_code 13
#define if_true_code 14
#define if_false_code 15
#define if_case_code 16

#define if_node_size 2
#define if_line_field(X) mem[X + 1].i
#define if_code 1
#define fi_code 2
#define else_code 3
#define or_code 4

#define get_x_token_or_active_char                       \
  {                                                      \
    get_x_token();                                       \
    if (cur_cmd == relax)                                \
      if (cur_chr == no_expand_flag) {                   \
        cur_cmd = active_char;                           \
        cur_chr = cur_tok - cs_token_flag - active_base; \
      }                                                  \
  }

#define append_to_name(X)                               \
  {                                                     \
    c = X;                                              \
    incr(k);                                            \
    if (k <= file_name_size) name_of_file[k] = xchr[c]; \
  }

#define format_default_length 20
#define format_area_length 11
#define format_ext_length 4
#define format_extension_str ".fmt"

#define pack_cur_name pack_file_name(cur_name, cur_area, cur_ext)

#define no_tag 0
#define lig_tag 1
#define list_tag 2
#define ext_tag 3

#define stop_flag qi(128)
#define kern_flag qi(128)
#define skip_byte(X) X.b0
#define next_char(X) X.b1
#define op_byte(X) X.b2
#define rem_byte(X) X.b3

#define ext_top(X) X.b0
#define ext_mid(X) X.b1
#define ext_bot(X) X.b2
#define ext_rep(X) X.b3

#define slant_code 1
#define space_code 2
#define space_stretch_code 3
#define space_shrink_code 4
#define x_height_code 5
#define quad_code 6
#define extra_space_code 7

#define non_char qi(256)
#define non_address 0

#define char_info_end(X) X].qqqq
#define char_info(X) font_info[char_base[X]+char_info_end
#define char_width_end(X) X.b0].sc
#define char_width(X) font_info[width_base[X]+char_width_end
#define char_exists(X) (X.b0 > min_quarterword)
#define char_italic_end(X) (qo(X.b2) ) /4].sc
#define char_italic(X) font_info[italic_base[X]+char_italic_end
#define height_depth(X) qo(X.b1)
#define char_height_end(X) (X) /16].sc
#define char_height(X) font_info[height_base[X]+char_height_end
#define char_depth_end(X) (X) %16].sc
#define char_depth(X) font_info[depth_base[X]+char_depth_end
#define char_tag(X) ((qo(X.b2)) % 4)

#define char_kern_end(X) 256*op_byte(X) +rem_byte(X) ].sc
#define char_kern(X) font_info[kern_base[X]+char_kern_end
#define kern_base_offset 256 * (128 + min_quarterword)
#define lig_kern_start(X) lig_kern_base[X] + rem_byte
#define lig_kern_restart_end(X) \
  256 * op_byte(X) + rem_byte(X) + 32768 - kern_base_offset
#define lig_kern_restart(X) lig_kern_base[X] + lig_kern_restart_end

#define param_end(X) param_base[X]].sc
#define param(X) font_info[X+param_end
#define slant param(slant_code)
#define space param(space_code)
#define space_stretch param(space_stretch_code)
#define space_shrink param(space_shrink_code)
#define x_height param(x_height_code)
#define quad param(quad_code)
#define extra_space param(extra_space_code)

#define abort goto bad_tfm

#define start_font_error_message            \
  print_err("Font ");                       \
  sprint_cs(u);                             \
  print_char('=');                          \
  print_file_name(nom, aire, empty_string); \
  if (s >= 0) {                             \
    print_str(" at ");                      \
    print_scaled(s);                        \
    print_str("pt");                        \
  } else if (s != -1000) {                  \
    print_str(" scaled ");                  \
    print_int(-s);                          \
  }

#define fget get(tfm_file)
#define fbyte tfm_file.d
#define read_sixteen(X)   \
  {                       \
    X = fbyte;            \
    if (X > 127) abort;   \
    fget;                 \
    X = X * 0400 + fbyte; \
  }
#define store_four_quarters(X) \
  {                            \
    fget;                      \
    a = fbyte;                 \
    qw.b0 = qi(a);             \
    fget;                      \
    b = fbyte;                 \
    qw.b1 = qi(b);             \
    fget;                      \
    c = fbyte;                 \
    qw.b2 = qi(c);             \
    fget;                      \
    d = fbyte;                 \
    qw.b3 = qi(d);             \
    X = qw;                    \
  }

#define check_byte_range(X)          \
  {                                  \
    if ((X < bc) || (X > ec)) abort; \
  }
#define current_character_being_worked_on k + bc - fmem_ptr

#define store_scaled(X)                                            \
  {                                                                \
    fget;                                                          \
    a = fbyte;                                                     \
    fget;                                                          \
    b = fbyte;                                                     \
    fget;                                                          \
    c = fbyte;                                                     \
    fget;                                                          \
    d = fbyte;                                                     \
    sw = (((((d * z) / 0400) + (c * z)) / 0400) + (b * z)) / beta; \
    if (a == 0)                                                    \
      X = sw;                                                      \
    else if (a == 255)                                             \
      X = sw - alpha;                                              \
    else                                                           \
      abort;                                                       \
  }

#define check_existence(X)       \
  {                              \
    check_byte_range(X);         \
    qw = char_info(f)(X);        \
    if (!char_exists(qw)) abort; \
  }

#define adjust(X) X[f] = qo(X[f])

#define set_char_0 0
#define set1 128
#define set_rule 132
#define put_rule 137
#define nop 138
#define bop 139
#define eop 140
#define push 141
#define pop 142
#define right1 143
#define w0 147
#define w1 148
#define x0 152
#define x1 153
#define down1 157
#define y0 161
#define y1 162
#define z0 166
#define z1 167
#define fnt_num_0 171
#define fnt1 235
#define xxx1 239
#define xxx4 242
#define fnt_def1 243
#define pre 247
#define post 248
#define post_post 249

#define id_byte 2

#define dvi_out(X)                        \
  {                                       \
    dvi_buf[dvi_ptr] = X;                 \
    incr(dvi_ptr);                        \
    if (dvi_ptr == dvi_limit) dvi_swap(); \
  }

#define movement_node_size 3
#define location(X) mem[X + 2].i

#define y_here 1
#define z_here 2
#define yz_OK 3
#define y_OK 4
#define z_OK 5
#define d_fixed 6

#define none_seen 0
#define y_seen 6
#define z_seen 12

#define synch_h                      \
  if (cur_h != dvi_h) {              \
    movement(cur_h - dvi_h, right1); \
    dvi_h = cur_h;                   \
  }
#define synch_v                     \
  if (cur_v != dvi_v) {             \
    movement(cur_v - dvi_v, down1); \
    dvi_v = cur_v;                  \
  }

#define billion float_constant(1000000000)
#define vet_glue(X)              \
  glue_temp = X;                 \
  if (glue_temp > billion)       \
    glue_temp = billion;         \
  else if (glue_temp < -billion) \
  glue_temp = -billion

#define exactly 0
#define additional 1
#define natural 0, additional

#define noad_size 4
#define nucleus(X) X + 1
#define supscr(X) X + 2
#define subscr(X) X + 3
#define math_type link
#define fam font
#define math_char 1
#define sub_box 2
#define sub_mlist 3
#define math_text_char 4

#define ord_noad (unset_node + 3)
#define op_noad (ord_noad + 1)
#define bin_noad (ord_noad + 2)
#define rel_noad (ord_noad + 3)
#define open_noad (ord_noad + 4)
#define close_noad (ord_noad + 5)
#define punct_noad (ord_noad + 6)
#define inner_noad (ord_noad + 7)
#define limits 1
#define no_limits 2

#define left_delimiter(X) X + 4
#define right_delimiter(X) X + 5
#define radical_noad (inner_noad + 1)
#define radical_noad_size 5
#define fraction_noad (radical_noad + 1)
#define fraction_noad_size 6
#define small_fam(X) mem[X].qqqq.b0
#define small_char(X) mem[X].qqqq.b1
#define large_fam(X) mem[X].qqqq.b2
#define large_char(X) mem[X].qqqq.b3
#define thickness width
#define default_code 010000000000
#define numerator supscr
#define denominator subscr

#define under_noad (fraction_noad + 1)
#define over_noad (under_noad + 1)
#define accent_noad (over_noad + 1)
#define accent_noad_size 5
#define accent_chr(X) X + 4
#define vcenter_noad (accent_noad + 1)
#define left_noad (vcenter_noad + 1)
#define right_noad (left_noad + 1)
#define delimiter nucleus
#define scripts_allowed(X) (type(X) >= ord_noad) && (type(X) < left_noad)

#define style_node (unset_node + 1)
#define style_node_size 3
#define display_style 0
#define text_style 2
#define script_style 4
#define script_script_style 6
#define cramped 1

#define choice_node (unset_node + 2)
#define display_mlist(X) info(X + 1)
#define text_mlist(X) link(X + 1)
#define script_mlist(X) info(X + 2)
#define script_script_mlist(X) link(X + 2)

#define text_size 0
#define script_size 16
#define script_script_size 32

#define mathsy_end(X) fam_fnt(2+X) ]].sc
#define mathsy(X) font_info[X+param_base[mathsy_end
#define math_x_height mathsy(5)
#define math_quad mathsy(6)
#define num1 mathsy(8)
#define num2 mathsy(9)
#define num3 mathsy(10)
#define denom1 mathsy(11)
#define denom2 mathsy(12)
#define sup1 mathsy(13)
#define sup2 mathsy(14)
#define sup3 mathsy(15)
#define sub1 mathsy(16)
#define sub2 mathsy(17)
#define sup_drop mathsy(18)
#define sub_drop mathsy(19)
#define delim1 mathsy(20)

#define delim2 mathsy(21)
#define axis_height mathsy(22)
#define total_mathsy_params 22

#define mathex(X) font_info[X + param_base[fam_fnt(3 + cur_size)]].sc
#define default_rule_thickness mathex(8)
#define big_op_spacing1 mathex(9)
#define big_op_spacing2 mathex(10)
#define big_op_spacing3 mathex(11)
#define big_op_spacing4 mathex(12)
#define big_op_spacing5 mathex(13)
#define total_mathex_params 13

#define cramped_style(X) 2 * (X / 2) + cramped
#define sub_style(X) 2 * (X / 4) + script_style + cramped
#define sup_style(X) 2 * (X / 4) + script_style + (X % 2)
#define num_style(X) X + 2 - 2 * (X / 6)
#define denom_style(X) 2 * (X / 2) + cramped + 2 - 2 * (X / 6)

#define mu_mult(X) nx_plus_y(n, X, xn_over_d(X, f, 0200000))

#define new_hlist(X) mem[nucleus(X)].i

#define choose_mlist(X) \
  {                     \
    p = X(q);           \
    X(q) = null;        \
  }

#define math_spacing_str "math_spacing"

#define u_part(X) mem[X + height_offset].i
#define v_part(X) mem[X + depth_offset].i
#define extra_info(X) info(X + list_offset)

#define preamble link(align_head)
#define align_stack_node_size 5

#define span_code 256
#define cr_code 257
#define cr_cr_code (cr_code + 1)
#define end_template_token cs_token_flag + frozen_end_template

#define span_node_size 2

#define tight_fit 3

#define loose_fit 1

#define very_loose_fit 0

#define decent_fit 2

#define active_node_size 3
#define fitness subtype
#define break_node rlink
#define line_number llink
#define total_demerits(X) mem[X + 2].i
#define unhyphenated 0
#define hyphenated 1
#define last_active active

#define passive_node_size 2
#define cur_break rlink
#define prev_break llink
#define serial info

#define delta_node_size 7
#define delta_node 2

#define do_all_six(X) \
  X(1);               \
  X(2);               \
  X(3);               \
  X(4);               \
  X(5);               \
  X(6)

#define check_shrinkage(X)                               \
  if ((shrink_order(X) != normal) && (shrink(X) != 0)) { \
    X = finite_shrink(X);                                \
  }

#define copy_to_cur_active(X) cur_active_width[X] = active_width[X]
#define update_width(X) \
  cur_active_width[X] = cur_active_width[X] + mem[r + X].sc

#define awful_bad 07777777777

#define set_break_width_to_background(X) break_width[X] = background[X]

#define convert_to_break_width(X) \
  mem[prev_r + X].sc = mem[prev_r + X].sc - cur_active_width[X] + break_width[X]
#define store_break_width(X) active_width[X] = break_width[X]
#define new_delta_to_break_width(X) \
  mem[q + X].sc = break_width[X] - cur_active_width[X]

#define new_delta_from_break_width(X) \
  mem[q + X].sc = cur_active_width[X] - break_width[X]

#define combine_two_deltas(X) \
  mem[prev_r + X].sc = mem[prev_r + X].sc + mem[r + X].sc
#define downdate_width(X) \
  cur_active_width[X] = cur_active_width[X] - mem[prev_r + X].sc

#define update_active(X) active_width[X] = active_width[X] + mem[r + X].sc

#define store_background(X) active_width[X] = background[X]

#define act_width active_width[1]
#define kern_break                                                    \
  {                                                                   \
    if (!is_char_node(link(cur_p)) && auto_breaking)                  \
      if (type(link(cur_p)) == glue_node) try_break(0, unhyphenated); \
    act_width = act_width + width(cur_p);                             \
  }

#define next_break prev_break

#define append_charnode_to_t(X) \
  {                             \
    link(t) = get_avail();      \
    t = link(t);                \
    font(t) = hf;               \
    character(t) = X;           \
  }
#define set_cur_r            \
  {                          \
    if (j < n)               \
      cur_r = qi(hu[j + 1]); \
    else                     \
      cur_r = bchar;         \
    if (odd(hyf[j]))         \
      cur_rh = hchar;        \
    else                     \
      cur_rh = non_char;     \
  }

#define wrap_lig(X)                           \
  if (ligature_present) {                     \
    p = new_ligature(hf, cur_l, link(cur_q)); \
    if (lft_hit) {                            \
      subtype(p) = 2;                         \
      lft_hit = false;                        \
    }                                         \
    if (X)                                    \
      if (lig_stack == null) {                \
        incr(subtype(p));                     \
        rt_hit = false;                       \
      }                                       \
    link(cur_q) = p;                          \
    t = p;                                    \
    ligature_present = false;                 \
  }
#define pop_lig_stack                                                   \
  {                                                                     \
    if (lig_ptr(lig_stack) > null) {                                    \
      link(t) = lig_ptr(lig_stack);                                     \
      t = link(t);                                                      \
      incr(j);                                                          \
    }                                                                   \
    p = lig_stack;                                                      \
    lig_stack = link(p);                                                \
    free_node(p, small_node_size);                                      \
    if (lig_stack == null) set_cur_r else cur_r = character(lig_stack); \
  }

#define advance_major_tail         \
  {                                \
    major_tail = link(major_tail); \
    incr(r_count);                 \
  }

#define trie_link(X) trie[X].rh
#define trie_char(X) trie[X].b1
#define trie_op(X) trie[X].b0

#define set_cur_lang       \
  if (language <= 0)       \
    cur_lang = 0;          \
  else if (language > 255) \
    cur_lang = 0;          \
  else                     \
    cur_lang = language

#define trie_root trie_l[0]

#define trie_ref trie_hash
#define trie_back(X) trie[X].lh

#define active_height active_width
#define cur_height active_height[1]
#define set_height_zero(X) active_height[X] = 0

#define deplorable 100000

#define inserts_only 1

#define box_there 2

#define page_ins_node_size 4
#define inserting 0
#define split_up 1
#define broken_ptr(X) link(X + 1)

#define broken_ins(X) info(X + 1)
#define last_ins_ptr(X) link(X + 2)
#define best_ins_ptr(X) info(X + 2)

#define page_goal page_so_far[0]
#define page_total page_so_far[1]
#define page_shrink page_so_far[6]
#define page_depth page_so_far[7]

#define print_plus_end(X) \
  print_str(X);           \
  }
#define print_plus(X)             \
  if (page_so_far[X] != 0) {      \
    print_str(" plus ");          \
    print_scaled(page_so_far[X]); \
  print_plus_end

#define set_page_so_far_zero(X) page_so_far[X] = 0

#define contrib_tail nest[0].tail_field

#define adjust_space_factor                \
  main_s = sf_code(cur_chr);               \
  if (main_s == 1000)                      \
    space_factor = 1000;                   \
  else if (main_s < 1000) {                \
    if (main_s > 0) space_factor = main_s; \
  } else if (space_factor < 1000)          \
    space_factor = 1000;                   \
  else                                     \
    space_factor = main_s

#define pack_lig(X)                                    \
  {                                                    \
    main_p = new_ligature(main_f, cur_l, link(cur_q)); \
    if (lft_hit) {                                     \
      subtype(main_p) = 2;                             \
      lft_hit = false;                                 \
    }                                                  \
    if (X)                                             \
      if (lig_stack == null) {                         \
        incr(subtype(main_p));                         \
        rt_hit = false;                                \
      }                                                \
    link(cur_q) = main_p;                              \
    tail = main_p;                                     \
    ligature_present = false;                          \
  }

#define wrapup(X)                                                      \
  if (cur_l < non_char) {                                              \
    if (link(cur_q) > null)                                            \
      if (character(tail) == qi(hyphen_char[main_f])) ins_disc = true; \
    if (ligature_present) pack_lig(X);                                 \
    if (ins_disc) {                                                    \
      ins_disc = false;                                                \
      if (mode > 0) tail_append(new_disc());                           \
    }                                                                  \
  }

#define any_mode(X) \
  case vmode + X:   \
  case hmode + X:   \
  case mmode + X

#define non_math(X) \
  case vmode + X:   \
  case hmode + X

#define fil_code 0
#define fill_code 1
#define ss_code 2
#define fil_neg_code 3
#define skip_code 4
#define mskip_code 5

#define box_flag 010000000000
#define ship_out_flag box_flag + 512
#define leader_flag box_flag + 513
#define box_code 0
#define copy_code 1
#define last_box_code 2
#define vsplit_code 3
#define vtop_code 4

#define fam_in_range ((cur_fam >= 0) && (cur_fam < 16))

#define above_code 0
#define over_code 1
#define atop_code 2
#define delimited_code 3

#define global (a >= 4)
#define define(X, Y, Z)  \
  if (global)            \
    geq_define(X, Y, Z); \
  else                   \
    eq_define(X, Y, Z)
#define word_define(X, Y)  \
  if (global)              \
    geq_word_define(X, Y); \
  else                     \
    eq_word_define(X, Y)

#define char_def_code 0
#define math_char_def_code 1
#define count_def_code 2
#define dimen_def_code 3
#define skip_def_code 4
#define mu_skip_def_code 5
#define toks_def_code 6

#define show_code 0
#define show_box_code 1
#define show_the_code 2
#define show_lists_code 3

#define too_small(X)                          \
  {                                           \
    wake_up_terminal;                         \
    wterm_ln("---! Must increase the %s", X); \
                                              \
    goto bad_fmt;                             \
  }

#define dump_wd(X)  \
  {                 \
    fmt_file.d = X; \
    put(fmt_file);  \
  }
#define dump_int(X)   \
  {                   \
    fmt_file.d.i = X; \
    put(fmt_file);    \
  }
#define dump_hh(X)     \
  {                    \
    fmt_file.d.hh = X; \
    put(fmt_file);     \
  }
#define dump_qqqq(X)     \
  {                      \
    fmt_file.d.qqqq = X; \
    put(fmt_file);       \
  }

#define undump_wd(X) \
  {                  \
    get(fmt_file);   \
    X = fmt_file.d;  \
  }
#define undump_int(X) \
  {                   \
    get(fmt_file);    \
    X = fmt_file.d.i; \
  }
#define undump_hh(X)   \
  {                    \
    get(fmt_file);     \
    X = fmt_file.d.hh; \
  }
#define undump_qqqq(X)   \
  {                      \
    get(fmt_file);       \
    X = fmt_file.d.qqqq; \
  }
#define undump_end_end(X) \
  X = x;                  \
  }
#define undump_end(X) (x> X) ) goto bad_fmt; \
  else undump_end_end
#define undump(X) \
  {               \
    undump_int(x);if((x<X) ||undump_end
#define undump_size_end_end(X) too_small(X) else undump_end_end
#define undump_size_end(X) \
  if (x > X) undump_size_end_end
#define undump_size(X)       \
  {                          \
    undump_int(x);           \
    if (x < X) goto bad_fmt; \
    undump_size_end

#define dump_four_ASCII           \
  w.b0 = qi(so(str_pool[k]));     \
  w.b1 = qi(so(str_pool[k + 1])); \
  w.b2 = qi(so(str_pool[k + 2])); \
  w.b3 = qi(so(str_pool[k + 3])); \
  dump_qqqq(w)

#define undump_four_ASCII         \
  undump_qqqq(w);                 \
  str_pool[k] = si(qo(w.b0));     \
  str_pool[k + 1] = si(qo(w.b1)); \
  str_pool[k + 2] = si(qo(w.b2)); \
  str_pool[k + 3] = si(qo(w.b3))

#define write_node_size 2
#define open_node_size 3
#define open_node 0
#define write_node 1
#define close_node 2
#define special_node 3
#define language_node 4
#define what_lang(X) link(X + 1)
#define what_lhm(X) type(X + 1)
#define what_rhm(X) subtype(X + 1)
#define write_tokens(X) link(X + 1)
#define write_stream(X) info(X + 1)
#define open_name(X) link(X + 1)
#define open_area(X) info(X + 2)
#define open_ext(X) link(X + 2)

#define immediate_code 4
#define set_language_code 5

#define adv_past(X)                  \
  if (subtype(X) == language_node) { \
    cur_lang = what_lang(X);         \
    l_hyf = what_lhm(X);             \
    r_hyf = what_rhm(X);             \
  }

#define end_write_token cs_token_flag + end_write

#define str_0_255                                                    \
  "^^@^^A^^B^^C^^D^^E^^F^^G^^H^^I^^J^^K^^L^^M^^N^^O"                 \
  "^^P^^Q^^R^^S^^T^^U^^V^^W^^X^^Y^^Z^^[^^\\^^]^^^^^_"                \
  " !\"#$%&'()*+,-./"                                                \
  "0123456789:;<=>?"                                                 \
  "@ABCDEFGHIJKLMNO"                                                 \
  "PQRSTUVWXYZ[\\]^_"                                                \
  "`abcdefghijklmno"                                                 \
  "pqrstuvwxyz{|}~^^?"                                               \
  "^^80^^81^^82^^83^^84^^85^^86^^87^^88^^89^^8a^^8b^^8c^^8d^^8e^^8f" \
  "^^90^^91^^92^^93^^94^^95^^96^^97^^98^^99^^9a^^9b^^9c^^9d^^9e^^9f" \
  "^^a0^^a1^^a2^^a3^^a4^^a5^^a6^^a7^^a8^^a9^^aa^^ab^^ac^^ad^^ae^^af" \
  "^^b0^^b1^^b2^^b3^^b4^^b5^^b6^^b7^^b8^^b9^^ba^^bb^^bc^^bd^^be^^bf" \
  "^^c0^^c1^^c2^^c3^^c4^^c5^^c6^^c7^^c8^^c9^^ca^^cb^^cc^^cd^^ce^^cf" \
  "^^d0^^d1^^d2^^d3^^d4^^d5^^d6^^d7^^d8^^d9^^da^^db^^dc^^dd^^de^^df" \
  "^^e0^^e1^^e2^^e3^^e4^^e5^^e6^^e7^^e8^^e9^^ea^^eb^^ec^^ed^^ee^^ef" \
  "^^f0^^f1^^f2^^f3^^f4^^f5^^f6^^f7^^f8^^f9^^fa^^fb^^fc^^fd^^fe^^ff"
#define str_start_0_255                                                       \
  0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48, 51, 54, 57, \
      60, 63, 66, 69, 72, 75, 78, 81, 84, 87, 90, 93, 96, 97, 98, 99, 100,    \
      101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,   \
      115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128,   \
      129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142,   \
      143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156,   \
      157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170,   \
      171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184,   \
      185, 186, 187, 188, 189, 190, 191, 194, 198, 202, 206, 210, 214, 218,   \
      222, 226, 230, 234, 238, 242, 246, 250, 254, 258, 262, 266, 270, 274,   \
      278, 282, 286, 290, 294, 298, 302, 306, 310, 314, 318, 322, 326, 330,   \
      334, 338, 342, 346, 350, 354, 358, 362, 366, 370, 374, 378, 382, 386,   \
      390, 394, 398, 402, 406, 410, 414, 418, 422, 426, 430, 434, 438, 442,   \
      446, 450, 454, 458, 462, 466, 470, 474, 478, 482, 486, 490, 494, 498,   \
      502, 506, 510, 514, 518, 522, 526, 530, 534, 538, 542, 546, 550, 554,   \
      558, 562, 566, 570, 574, 578, 582, 586, 590, 594, 598, 602, 606, 610,   \
      614, 618, 622, 626, 630, 634, 638, 642, 646, 650, 654, 658, 662, 666,   \
      670, 674, 678, 682, 686, 690, 694, 698, 702,
#define str_256 "???"
#define str_257 "m2d5c2l5x2v5i"
#define str_258 "batchmode"
#define str_259 "nonstopmode"
#define str_260 "scrollmode"
#define str_261 "CLOBBERED."
#define str_262 "fil"
#define str_263 "unset"
#define str_264 "rule("
#define str_265 "insert"
#define str_266 "glue"
#define str_267 "nonscript"
#define str_268 "mskip"
#define str_269 "mu"
#define str_270 ""
#define empty_string 270
#define str_271 "kern"
#define str_272 "mkern"
#define str_273 "math"
#define str_274 "penalty "
#define str_275 "discretionary"
#define str_276 "mark"
#define str_277 "vadjust"
#define str_278 "flushing"
#define str_279 "copying"
#define str_280 "lineskip"
#define str_281 "baselineskip"
#define str_282 "parskip"
#define str_283 "abovedisplayskip"
#define str_284 "belowdisplayskip"
#define str_285 "abovedisplayshortskip"
#define str_286 "belowdisplayshortskip"
#define str_287 "leftskip"
#define str_288 "rightskip"
#define str_289 "topskip"
#define str_290 "splittopskip"
#define str_291 "tabskip"
#define str_292 "spaceskip"
#define str_293 "xspaceskip"
#define str_294 "parfillskip"
#define str_295 "thinmuskip"
#define str_296 "medmuskip"
#define str_297 "thickmuskip"
#define str_298 "skip"
#define str_299 "muskip"
#define str_300 "pt"
#define str_301 "output"
#define str_302 "everypar"
#define str_303 "everymath"
#define str_304 "everydisplay"
#define str_305 "everyhbox"
#define str_306 "everyvbox"
#define str_307 "everyjob"
#define str_308 "everycr"
#define str_309 "errhelp"
#define str_310 "toks"
#define str_311 "parshape"
#define str_312 "box"
#define str_313 "textfont"
#define str_314 "scriptfont"
#define str_315 "scriptscriptfont"
#define str_316 "catcode"
#define str_317 "lccode"
#define str_318 "uccode"
#define str_319 "sfcode"
#define str_320 "mathcode"
#define str_321 "pretolerance"
#define str_322 "tolerance"
#define str_323 "linepenalty"
#define str_324 "hyphenpenalty"
#define str_325 "exhyphenpenalty"
#define str_326 "clubpenalty"
#define str_327 "widowpenalty"
#define str_328 "displaywidowpenalty"
#define str_329 "brokenpenalty"
#define str_330 "binoppenalty"
#define str_331 "relpenalty"
#define str_332 "predisplaypenalty"
#define str_333 "postdisplaypenalty"
#define str_334 "interlinepenalty"
#define str_335 "doublehyphendemerits"
#define str_336 "finalhyphendemerits"
#define str_337 "adjdemerits"
#define str_338 "mag"
#define str_339 "delimiterfactor"
#define str_340 "looseness"
#define str_341 "time"
#define str_342 "day"
#define str_343 "month"
#define str_344 "year"
#define str_345 "showboxbreadth"
#define str_346 "showboxdepth"
#define str_347 "hbadness"
#define str_348 "vbadness"
#define str_349 "pausing"
#define str_350 "tracingonline"
#define str_351 "tracingmacros"
#define str_352 "tracingstats"
#define str_353 "tracingparagraphs"
#define str_354 "tracingpages"
#define str_355 "tracingoutput"
#define str_356 "tracinglostchars"
#define str_357 "tracingcommands"
#define str_358 "tracingrestores"
#define str_359 "uchyph"
#define str_360 "outputpenalty"
#define str_361 "maxdeadcycles"
#define str_362 "hangafter"
#define str_363 "floatingpenalty"
#define str_364 "globaldefs"
#define str_365 "fam"
#define str_366 "escapechar"
#define str_367 "defaulthyphenchar"
#define str_368 "defaultskewchar"
#define str_369 "endlinechar"
#define str_370 "newlinechar"
#define str_371 "language"
#define str_372 "lefthyphenmin"
#define str_373 "righthyphenmin"
#define str_374 "holdinginserts"
#define str_375 "errorcontextlines"
#define str_376 "count"
#define str_377 "delcode"
#define str_378 "parindent"
#define str_379 "mathsurround"
#define str_380 "lineskiplimit"
#define str_381 "hsize"
#define str_382 "vsize"
#define str_383 "maxdepth"
#define str_384 "splitmaxdepth"
#define str_385 "boxmaxdepth"
#define str_386 "hfuzz"
#define str_387 "vfuzz"
#define str_388 "delimitershortfall"
#define str_389 "nulldelimiterspace"
#define str_390 "scriptspace"
#define str_391 "predisplaysize"
#define str_392 "displaywidth"
#define str_393 "displayindent"
#define str_394 "overfullrule"
#define str_395 "hangindent"
#define str_396 "hoffset"
#define str_397 "voffset"
#define str_398 "emergencystretch"
#define str_399 "dimen"
#define str_400 "notexpanded:"
#define str_401 "csname"
#define str_402 "endcsname"
#define str_403 "IMPOSSIBLE."
#define str_404 "NONEXISTENT."
#define str_405 "accent"
#define str_406 "advance"
#define str_407 "afterassignment"
#define str_408 "aftergroup"
#define str_409 "begingroup"
#define str_410 "char"
#define str_411 "delimiter"
#define str_412 "divide"
#define str_413 "endgroup"
#define str_414 "expandafter"
#define str_415 "font"
#define str_416 "fontdimen"
#define str_417 "halign"
#define str_418 "hrule"
#define str_419 "ignorespaces"
#define str_420 "mathaccent"
#define str_421 "mathchar"
#define str_422 "mathchoice"
#define str_423 "multiply"
#define str_424 "noalign"
#define str_425 "noboundary"
#define str_426 "noexpand"
#define str_427 "omit"
#define str_428 "penalty"
#define str_429 "prevgraf"
#define str_430 "radical"
#define str_431 "read"
#define str_432 "relax"
#define str_433 "setbox"
#define str_434 "the"
#define str_435 "valign"
#define str_436 "vcenter"
#define str_437 "vrule"
#define str_438 "curlevel"
#define str_439 "retaining"
#define str_440 "restoring"
#define str_441 "ETC."
#define str_442 "BAD."
#define str_443 "write"
#define str_444 "par"
#define str_445 "input"
#define str_446 "endinput"
#define str_447 "topmark"
#define str_448 "firstmark"
#define str_449 "botmark"
#define str_450 "splitfirstmark"
#define str_451 "splitbotmark"
#define str_452 "spacefactor"
#define str_453 "prevdepth"
#define str_454 "deadcycles"
#define str_455 "insertpenalties"
#define str_456 "wd"
#define str_457 "ht"
#define str_458 "dp"
#define str_459 "lastpenalty"
#define str_460 "lastkern"
#define str_461 "lastskip"
#define str_462 "inputlineno"
#define str_463 "badness"
#define str_464 "true"
#define str_465 "em"
#define str_466 "ex"
#define str_467 "in"
#define str_468 "pc"
#define str_469 "cm"
#define str_470 "mm"
#define str_471 "bp"
#define str_472 "dd"
#define str_473 "cc"
#define str_474 "sp"
#define str_475 "plus"
#define str_476 "minus"
#define str_477 "width"
#define str_478 "height"
#define str_479 "depth"
#define str_480 "number"
#define str_481 "romannumeral"
#define str_482 "string"
#define str_483 "meaning"
#define str_484 "fontname"
#define str_485 "jobname"
#define str_486 "if"
#define str_487 "ifcat"
#define str_488 "ifnum"
#define str_489 "ifdim"
#define str_490 "ifodd"
#define str_491 "ifvmode"
#define str_492 "ifhmode"
#define str_493 "ifmmode"
#define str_494 "ifinner"
#define str_495 "ifvoid"
#define str_496 "ifhbox"
#define str_497 "ifvbox"
#define str_498 "ifx"
#define str_499 "ifeof"
#define str_500 "iftrue"
#define str_501 "iffalse"
#define str_502 "ifcase"
#define str_503 "fi"
#define str_504 "or"
#define str_505 "else"
#define str_506 "TeXinputs/"
#define TEX_area 506
#define str_507 "TeXfonts/"
#define TEX_font_area 507
#define str_508 ".fmt"
#define format_extension 508
#define str_509 ".log"
#define str_510 ".dvi"
#define str_511 "input file name"
#define str_512 ".tex"
#define str_513 "texput"
#define str_514 "nullfont"
#define str_515 ".tfm"
#define str_516 "vlistout"
#define str_517 "to"
#define str_518 "spread"
#define str_519 "vpack"
#define str_520 "displaystyle"
#define str_521 "textstyle"
#define str_522 "scriptstyle"
#define str_523 "scriptscriptstyle"
#define str_524 "mathord"
#define str_525 "mathop"
#define str_526 "mathbin"
#define str_527 "mathrel"
#define str_528 "mathopen"
#define str_529 "mathclose"
#define str_530 "mathpunct"
#define str_531 "mathinner"
#define str_532 "overline"
#define str_533 "underline"
#define str_534 "left"
#define str_535 "right"
#define str_536 "limits"
#define str_537 "nolimits"
#define str_538 "fraction, thickness "
#define str_539 "mlist1"
#define str_540 "mlist2"
#define str_541 "mlist3"
#define str_542 \
  "0234000122*4000133**3**344*0400400*000000234000111*1111112341011"
#define math_spacing 542
#define str_543 "mlist4"
#define str_544 "span"
#define str_545 "cr"
#define str_546 "crcr"
#define str_547 "endtemplate"
#define str_548 "endv"
#define str_549 "256 spans"
#define str_550 "align1"
#define str_551 "align0"
#define str_552 "disc1"
#define str_553 "disc2"
#define str_554 "paragraph"
#define str_555 "disc3"
#define str_556 "disc4"
#define str_557 "line breaking"
#define str_558 "hyphenation"
#define str_559 "patterns"
#define str_560 "pruning"
#define str_561 "vertbreak"
#define str_562 "vsplit"
#define str_563 "vbox"
#define str_564 "pagegoal"
#define str_565 "pagetotal"
#define str_566 "pagestretch"
#define str_567 "pagefilstretch"
#define str_568 "pagefillstretch"
#define str_569 "pagefilllstretch"
#define str_570 "pageshrink"
#define str_571 "pagedepth"
#define str_572 "page"
#define str_573 "end"
#define str_574 "dump"
#define str_575 "hskip"
#define str_576 "hfil"
#define str_577 "hfill"
#define str_578 "hss"
#define str_579 "hfilneg"
#define str_580 "vskip"
#define str_581 "vfil"
#define str_582 "vfill"
#define str_583 "vss"
#define str_584 "vfilneg"
#define str_585 "right."
#define str_586 "rightbrace"
#define str_587 "moveleft"
#define str_588 "moveright"
#define str_589 "raise"
#define str_590 "lower"
#define str_591 "copy"
#define str_592 "lastbox"
#define str_593 "vtop"
#define str_594 "hbox"
#define str_595 "shipout"
#define str_596 "leaders"
#define str_597 "cleaders"
#define str_598 "xleaders"
#define str_599 "indent"
#define str_600 "noindent"
#define str_601 "unpenalty"
#define str_602 "unkern"
#define str_603 "unskip"
#define str_604 "unhbox"
#define str_605 "unhcopy"
#define str_606 "unvbox"
#define str_607 "unvcopy"
#define str_608 "eqno"
#define str_609 "leqno"
#define str_610 "displaylimits"
#define str_611 "above"
#define str_612 "over"
#define str_613 "atop"
#define str_614 "abovewithdelims"
#define str_615 "overwithdelims"
#define str_616 "atopwithdelims"
#define str_617 "display"
#define str_618 "long"
#define str_619 "outer"
#define str_620 "global"
#define str_621 "def"
#define str_622 "gdef"
#define str_623 "edef"
#define str_624 "xdef"
#define str_625 "prefix"
#define str_626 "inaccessible"
#define str_627 "let"
#define str_628 "futurelet"
#define str_629 "chardef"
#define str_630 "mathchardef"
#define str_631 "countdef"
#define str_632 "dimendef"
#define str_633 "skipdef"
#define str_634 "muskipdef"
#define str_635 "toksdef"
#define str_636 "by"
#define str_637 "hyphenchar"
#define str_638 "skewchar"
#define str_639 "FONT"
#define str_640 "at"
#define str_641 "scaled"
#define str_642 "errorstopmode"
#define str_643 "openin"
#define str_644 "closein"
#define str_645 "message"
#define str_646 "errmessage"
#define str_647 "lowercase"
#define str_648 "uppercase"
#define str_649 "show"
#define str_650 "showbox"
#define str_651 "showthe"
#define str_652 "showlists"
#define str_653 "long macro"
#define str_654 "outer macro"
#define str_655 "outer endtemplate"
#define str_656 " (INITEX)"
#define str_657 "end occurred "
#define str_658 "openout"
#define str_659 "closeout"
#define str_660 "special"
#define str_661 "immediate"
#define str_662 "setlanguage"
#define str_663 "ext1"
#define str_664 "ext2"
#define str_665 "ext3"
#define str_666 "endwrite"
#define str_667 "ext4"


/*:9*/ /*56:*/

#define put(file) fwrite(&((file).d), sizeof((file).d), 1, (file).f)
#define get(file) fread(&((file).d), sizeof((file).d), 1, (file).f)

#define reset(file, name, mode) \
  ((file).f = fopen((char *)(name) + 1, mode), (file).f != NULL ? get(file) : 0)
#define rewrite(file, name, mode) ((file).f = fopen((char *)(name) + 1, mode))
#define close(file) fclose((file).f)
#define eof(file) feof((file).f)
#define eoln(file) ((file).d == '\n' || eof(file))
#define erstat(file) ((file).f == NULL ? -1 : ferror((file).f))

#define read(file, x) ((x) = (file).d, get(file))
#define read_ln(file) \
  do get(file);       \
  while (!eoln(file))

#define write(file, format, ...) fprintf(file.f, format, ##__VA_ARGS__)
#define write_ln(file, ...) write(file, __VA_ARGS__ "\n")

#define wterm(format, ...) write(term_out, format, ##__VA_ARGS__)
#define wterm_ln(format, ...) wterm(format "\n", ##__VA_ARGS__)
#define wterm_cr write(term_out, "\n")
#define wlog(format, ...) write(log_file, format, ##__VA_ARGS__)
#define wlog_ln(format, ...) wlog(format "\n", ##__VA_ARGS__)
#define wlog_cr write(log_file, "\n")

/*:56*/

/*6:*/

/*:6*/

/*11:*/

enum { mem_max = 30000 };

enum { mem_min = 0 };

enum { buf_size = 500 };

enum { error_line = 72 };
enum { half_error_line = 42 };

enum { max_print_line = 79 };
enum { stack_size = 200 };
enum { max_in_open = 6 };

enum { font_max = 75 };

enum { font_mem_size = 20000 };
enum { param_size = 60 };
enum { nest_size = 40 };
enum { max_strings = 3000 };
enum { string_vacancies = 8000 };

enum { pool_size = 32000 };

enum { save_size = 600 };

enum { trie_size = 8000 };

enum { trie_op_size = 500 };
enum { dvi_buf_size = 800 };
enum { file_name_size = 40 };
const char *pool_name = "TeXformats:TEX.POOL                     ";

/*:11*/

/*18:*/

typedef uint8_t ASCII_code;

/*:18*/ /*25:*/

typedef uint8_t eight_bits;
typedef struct {
  FILE *f;
  text_char d;
} alpha_file;
typedef struct {
  FILE *f;
  eight_bits d;
} byte_file;

/*:25*/ /*38:*/

typedef uint16_t pool_pointer;
typedef uint16_t str_number;
typedef uint8_t packed_ASCII_code;

/*:38*/ /*101:*/

typedef int scaled;
typedef uint32_t nonnegative_integer;
typedef uint8_t small_number;

/*:101*/ /*109:*/

typedef float32_t glue_ratio;

/*:109*/ /*113:*/

typedef uint8_t quarterword;
typedef uint16_t halfword;
typedef uint8_t two_choices;
typedef uint8_t four_choices;
typedef struct {
  halfword rh;
  union {
    halfword lh;
    struct {
      quarterword b0;
      quarterword b1;
    };
  };
} two_halves;
typedef struct {
  quarterword b0;
  quarterword b1;
  quarterword b2;
  quarterword b3;
} four_quarters;
typedef struct {
  union {
    int i;
    glue_ratio gr;
    two_halves hh;
    four_quarters qqqq;
  };
} memory_word;
typedef struct {
  FILE *f;
  memory_word d;
} word_file;

/*:113*/ /*150:*/

typedef uint8_t glue_ord;

/*:150*/ /*212:*/

typedef struct {
  int16_t mode_field;
  pointer head_field, tail_field;
  int pg_field, ml_field;
  memory_word aux_field;
} list_state_record;

/*:212*/ /*269:*/

typedef uint8_t group_code;

/*:269*/ /*300:*/

typedef struct {
  quarterword state_field, index_field;
  halfword start_field, loc_field, limit_field, name_field;
} in_state_record;

/*:300*/ /*548:*/

typedef uint8_t internal_font_number;
typedef uint16_t font_index;

/*:548*/ /*594:*/

typedef uint16_t dvi_index;

/*:594*/ /*920:*/

typedef uint16_t trie_pointer;

/*:920*/ /*925:*/

typedef uint16_t hyph_pointer;

/*:925*/

/*13:*/

int bad;

/*:13*/ /*20:*/

ASCII_code xord[256];

uint8_t xchr[256];

/*:20*/ /*26:*/

uint8_t name_of_file0[file_name_size + 1] = {0}, *const name_of_file =
                                                     name_of_file0 - 1;

uint8_t name_length;

/*:26*/ /*30:*/

ASCII_code buffer[buf_size + 1];
uint16_t first;
uint16_t last;
uint16_t max_buf_stack;

/*:30*/ /*32:*/

alpha_file term_in;
alpha_file term_out;

/*:32*/ /*39:*/

/*1795:*/

typedef enum {
  str_start_256 = sizeof(str_0_255) - 1,
  str_start_257 = str_start_256 + sizeof(str_256) - 1,
  str_start_258 = str_start_257 + sizeof(str_257) - 1,
  str_start_259 = str_start_258 + sizeof(str_258) - 1,
  str_start_260 = str_start_259 + sizeof(str_259) - 1,
  str_start_261 = str_start_260 + sizeof(str_260) - 1,
  str_start_262 = str_start_261 + sizeof(str_261) - 1,
  str_start_263 = str_start_262 + sizeof(str_262) - 1,
  str_start_264 = str_start_263 + sizeof(str_263) - 1,
  str_start_265 = str_start_264 + sizeof(str_264) - 1,
  str_start_266 = str_start_265 + sizeof(str_265) - 1,
  str_start_267 = str_start_266 + sizeof(str_266) - 1,
  str_start_268 = str_start_267 + sizeof(str_267) - 1,
  str_start_269 = str_start_268 + sizeof(str_268) - 1,
  str_start_270 = str_start_269 + sizeof(str_269) - 1,
  str_start_271 = str_start_270 + sizeof(str_270) - 1,
  str_start_272 = str_start_271 + sizeof(str_271) - 1,
  str_start_273 = str_start_272 + sizeof(str_272) - 1,
  str_start_274 = str_start_273 + sizeof(str_273) - 1,
  str_start_275 = str_start_274 + sizeof(str_274) - 1,
  str_start_276 = str_start_275 + sizeof(str_275) - 1,
  str_start_277 = str_start_276 + sizeof(str_276) - 1,
  str_start_278 = str_start_277 + sizeof(str_277) - 1,
  str_start_279 = str_start_278 + sizeof(str_278) - 1,
  str_start_280 = str_start_279 + sizeof(str_279) - 1,
  str_start_281 = str_start_280 + sizeof(str_280) - 1,
  str_start_282 = str_start_281 + sizeof(str_281) - 1,
  str_start_283 = str_start_282 + sizeof(str_282) - 1,
  str_start_284 = str_start_283 + sizeof(str_283) - 1,
  str_start_285 = str_start_284 + sizeof(str_284) - 1,
  str_start_286 = str_start_285 + sizeof(str_285) - 1,
  str_start_287 = str_start_286 + sizeof(str_286) - 1,
  str_start_288 = str_start_287 + sizeof(str_287) - 1,
  str_start_289 = str_start_288 + sizeof(str_288) - 1,
  str_start_290 = str_start_289 + sizeof(str_289) - 1,
  str_start_291 = str_start_290 + sizeof(str_290) - 1,
  str_start_292 = str_start_291 + sizeof(str_291) - 1,
  str_start_293 = str_start_292 + sizeof(str_292) - 1,
  str_start_294 = str_start_293 + sizeof(str_293) - 1,
  str_start_295 = str_start_294 + sizeof(str_294) - 1,
  str_start_296 = str_start_295 + sizeof(str_295) - 1,
  str_start_297 = str_start_296 + sizeof(str_296) - 1,
  str_start_298 = str_start_297 + sizeof(str_297) - 1,
  str_start_299 = str_start_298 + sizeof(str_298) - 1,
  str_start_300 = str_start_299 + sizeof(str_299) - 1,
  str_start_301 = str_start_300 + sizeof(str_300) - 1,
  str_start_302 = str_start_301 + sizeof(str_301) - 1,
  str_start_303 = str_start_302 + sizeof(str_302) - 1,
  str_start_304 = str_start_303 + sizeof(str_303) - 1,
  str_start_305 = str_start_304 + sizeof(str_304) - 1,
  str_start_306 = str_start_305 + sizeof(str_305) - 1,
  str_start_307 = str_start_306 + sizeof(str_306) - 1,
  str_start_308 = str_start_307 + sizeof(str_307) - 1,
  str_start_309 = str_start_308 + sizeof(str_308) - 1,
  str_start_310 = str_start_309 + sizeof(str_309) - 1,
  str_start_311 = str_start_310 + sizeof(str_310) - 1,
  str_start_312 = str_start_311 + sizeof(str_311) - 1,
  str_start_313 = str_start_312 + sizeof(str_312) - 1,
  str_start_314 = str_start_313 + sizeof(str_313) - 1,
  str_start_315 = str_start_314 + sizeof(str_314) - 1,
  str_start_316 = str_start_315 + sizeof(str_315) - 1,
  str_start_317 = str_start_316 + sizeof(str_316) - 1,
  str_start_318 = str_start_317 + sizeof(str_317) - 1,
  str_start_319 = str_start_318 + sizeof(str_318) - 1,
  str_start_320 = str_start_319 + sizeof(str_319) - 1,
  str_start_321 = str_start_320 + sizeof(str_320) - 1,
  str_start_322 = str_start_321 + sizeof(str_321) - 1,
  str_start_323 = str_start_322 + sizeof(str_322) - 1,
  str_start_324 = str_start_323 + sizeof(str_323) - 1,
  str_start_325 = str_start_324 + sizeof(str_324) - 1,
  str_start_326 = str_start_325 + sizeof(str_325) - 1,
  str_start_327 = str_start_326 + sizeof(str_326) - 1,
  str_start_328 = str_start_327 + sizeof(str_327) - 1,
  str_start_329 = str_start_328 + sizeof(str_328) - 1,
  str_start_330 = str_start_329 + sizeof(str_329) - 1,
  str_start_331 = str_start_330 + sizeof(str_330) - 1,
  str_start_332 = str_start_331 + sizeof(str_331) - 1,
  str_start_333 = str_start_332 + sizeof(str_332) - 1,
  str_start_334 = str_start_333 + sizeof(str_333) - 1,
  str_start_335 = str_start_334 + sizeof(str_334) - 1,
  str_start_336 = str_start_335 + sizeof(str_335) - 1,
  str_start_337 = str_start_336 + sizeof(str_336) - 1,
  str_start_338 = str_start_337 + sizeof(str_337) - 1,
  str_start_339 = str_start_338 + sizeof(str_338) - 1,
  str_start_340 = str_start_339 + sizeof(str_339) - 1,
  str_start_341 = str_start_340 + sizeof(str_340) - 1,
  str_start_342 = str_start_341 + sizeof(str_341) - 1,
  str_start_343 = str_start_342 + sizeof(str_342) - 1,
  str_start_344 = str_start_343 + sizeof(str_343) - 1,
  str_start_345 = str_start_344 + sizeof(str_344) - 1,
  str_start_346 = str_start_345 + sizeof(str_345) - 1,
  str_start_347 = str_start_346 + sizeof(str_346) - 1,
  str_start_348 = str_start_347 + sizeof(str_347) - 1,
  str_start_349 = str_start_348 + sizeof(str_348) - 1,
  str_start_350 = str_start_349 + sizeof(str_349) - 1,
  str_start_351 = str_start_350 + sizeof(str_350) - 1,
  str_start_352 = str_start_351 + sizeof(str_351) - 1,
  str_start_353 = str_start_352 + sizeof(str_352) - 1,
  str_start_354 = str_start_353 + sizeof(str_353) - 1,
  str_start_355 = str_start_354 + sizeof(str_354) - 1,
  str_start_356 = str_start_355 + sizeof(str_355) - 1,
  str_start_357 = str_start_356 + sizeof(str_356) - 1,
  str_start_358 = str_start_357 + sizeof(str_357) - 1,
  str_start_359 = str_start_358 + sizeof(str_358) - 1,
  str_start_360 = str_start_359 + sizeof(str_359) - 1,
  str_start_361 = str_start_360 + sizeof(str_360) - 1,
  str_start_362 = str_start_361 + sizeof(str_361) - 1,
  str_start_363 = str_start_362 + sizeof(str_362) - 1,
  str_start_364 = str_start_363 + sizeof(str_363) - 1,
  str_start_365 = str_start_364 + sizeof(str_364) - 1,
  str_start_366 = str_start_365 + sizeof(str_365) - 1,
  str_start_367 = str_start_366 + sizeof(str_366) - 1,
  str_start_368 = str_start_367 + sizeof(str_367) - 1,
  str_start_369 = str_start_368 + sizeof(str_368) - 1,
  str_start_370 = str_start_369 + sizeof(str_369) - 1,
  str_start_371 = str_start_370 + sizeof(str_370) - 1,
  str_start_372 = str_start_371 + sizeof(str_371) - 1,
  str_start_373 = str_start_372 + sizeof(str_372) - 1,
  str_start_374 = str_start_373 + sizeof(str_373) - 1,
  str_start_375 = str_start_374 + sizeof(str_374) - 1,
  str_start_376 = str_start_375 + sizeof(str_375) - 1,
  str_start_377 = str_start_376 + sizeof(str_376) - 1,
  str_start_378 = str_start_377 + sizeof(str_377) - 1,
  str_start_379 = str_start_378 + sizeof(str_378) - 1,
  str_start_380 = str_start_379 + sizeof(str_379) - 1,
  str_start_381 = str_start_380 + sizeof(str_380) - 1,
  str_start_382 = str_start_381 + sizeof(str_381) - 1,
  str_start_383 = str_start_382 + sizeof(str_382) - 1,
  str_start_384 = str_start_383 + sizeof(str_383) - 1,
  str_start_385 = str_start_384 + sizeof(str_384) - 1,
  str_start_386 = str_start_385 + sizeof(str_385) - 1,
  str_start_387 = str_start_386 + sizeof(str_386) - 1,
  str_start_388 = str_start_387 + sizeof(str_387) - 1,
  str_start_389 = str_start_388 + sizeof(str_388) - 1,
  str_start_390 = str_start_389 + sizeof(str_389) - 1,
  str_start_391 = str_start_390 + sizeof(str_390) - 1,
  str_start_392 = str_start_391 + sizeof(str_391) - 1,
  str_start_393 = str_start_392 + sizeof(str_392) - 1,
  str_start_394 = str_start_393 + sizeof(str_393) - 1,
  str_start_395 = str_start_394 + sizeof(str_394) - 1,
  str_start_396 = str_start_395 + sizeof(str_395) - 1,
  str_start_397 = str_start_396 + sizeof(str_396) - 1,
  str_start_398 = str_start_397 + sizeof(str_397) - 1,
  str_start_399 = str_start_398 + sizeof(str_398) - 1,
  str_start_400 = str_start_399 + sizeof(str_399) - 1,
  str_start_401 = str_start_400 + sizeof(str_400) - 1,
  str_start_402 = str_start_401 + sizeof(str_401) - 1,
  str_start_403 = str_start_402 + sizeof(str_402) - 1,
  str_start_404 = str_start_403 + sizeof(str_403) - 1,
  str_start_405 = str_start_404 + sizeof(str_404) - 1,
  str_start_406 = str_start_405 + sizeof(str_405) - 1,
  str_start_407 = str_start_406 + sizeof(str_406) - 1,
  str_start_408 = str_start_407 + sizeof(str_407) - 1,
  str_start_409 = str_start_408 + sizeof(str_408) - 1,
  str_start_410 = str_start_409 + sizeof(str_409) - 1,
  str_start_411 = str_start_410 + sizeof(str_410) - 1,
  str_start_412 = str_start_411 + sizeof(str_411) - 1,
  str_start_413 = str_start_412 + sizeof(str_412) - 1,
  str_start_414 = str_start_413 + sizeof(str_413) - 1,
  str_start_415 = str_start_414 + sizeof(str_414) - 1,
  str_start_416 = str_start_415 + sizeof(str_415) - 1,
  str_start_417 = str_start_416 + sizeof(str_416) - 1,
  str_start_418 = str_start_417 + sizeof(str_417) - 1,
  str_start_419 = str_start_418 + sizeof(str_418) - 1,
  str_start_420 = str_start_419 + sizeof(str_419) - 1,
  str_start_421 = str_start_420 + sizeof(str_420) - 1,
  str_start_422 = str_start_421 + sizeof(str_421) - 1,
  str_start_423 = str_start_422 + sizeof(str_422) - 1,
  str_start_424 = str_start_423 + sizeof(str_423) - 1,
  str_start_425 = str_start_424 + sizeof(str_424) - 1,
  str_start_426 = str_start_425 + sizeof(str_425) - 1,
  str_start_427 = str_start_426 + sizeof(str_426) - 1,
  str_start_428 = str_start_427 + sizeof(str_427) - 1,
  str_start_429 = str_start_428 + sizeof(str_428) - 1,
  str_start_430 = str_start_429 + sizeof(str_429) - 1,
  str_start_431 = str_start_430 + sizeof(str_430) - 1,
  str_start_432 = str_start_431 + sizeof(str_431) - 1,
  str_start_433 = str_start_432 + sizeof(str_432) - 1,
  str_start_434 = str_start_433 + sizeof(str_433) - 1,
  str_start_435 = str_start_434 + sizeof(str_434) - 1,
  str_start_436 = str_start_435 + sizeof(str_435) - 1,
  str_start_437 = str_start_436 + sizeof(str_436) - 1,
  str_start_438 = str_start_437 + sizeof(str_437) - 1,
  str_start_439 = str_start_438 + sizeof(str_438) - 1,
  str_start_440 = str_start_439 + sizeof(str_439) - 1,
  str_start_441 = str_start_440 + sizeof(str_440) - 1,
  str_start_442 = str_start_441 + sizeof(str_441) - 1,
  str_start_443 = str_start_442 + sizeof(str_442) - 1,
  str_start_444 = str_start_443 + sizeof(str_443) - 1,
  str_start_445 = str_start_444 + sizeof(str_444) - 1,
  str_start_446 = str_start_445 + sizeof(str_445) - 1,
  str_start_447 = str_start_446 + sizeof(str_446) - 1,
  str_start_448 = str_start_447 + sizeof(str_447) - 1,
  str_start_449 = str_start_448 + sizeof(str_448) - 1,
  str_start_450 = str_start_449 + sizeof(str_449) - 1,
  str_start_451 = str_start_450 + sizeof(str_450) - 1,
  str_start_452 = str_start_451 + sizeof(str_451) - 1,
  str_start_453 = str_start_452 + sizeof(str_452) - 1,
  str_start_454 = str_start_453 + sizeof(str_453) - 1,
  str_start_455 = str_start_454 + sizeof(str_454) - 1,
  str_start_456 = str_start_455 + sizeof(str_455) - 1,
  str_start_457 = str_start_456 + sizeof(str_456) - 1,
  str_start_458 = str_start_457 + sizeof(str_457) - 1,
  str_start_459 = str_start_458 + sizeof(str_458) - 1,
  str_start_460 = str_start_459 + sizeof(str_459) - 1,
  str_start_461 = str_start_460 + sizeof(str_460) - 1,
  str_start_462 = str_start_461 + sizeof(str_461) - 1,
  str_start_463 = str_start_462 + sizeof(str_462) - 1,
  str_start_464 = str_start_463 + sizeof(str_463) - 1,
  str_start_465 = str_start_464 + sizeof(str_464) - 1,
  str_start_466 = str_start_465 + sizeof(str_465) - 1,
  str_start_467 = str_start_466 + sizeof(str_466) - 1,
  str_start_468 = str_start_467 + sizeof(str_467) - 1,
  str_start_469 = str_start_468 + sizeof(str_468) - 1,
  str_start_470 = str_start_469 + sizeof(str_469) - 1,
  str_start_471 = str_start_470 + sizeof(str_470) - 1,
  str_start_472 = str_start_471 + sizeof(str_471) - 1,
  str_start_473 = str_start_472 + sizeof(str_472) - 1,
  str_start_474 = str_start_473 + sizeof(str_473) - 1,
  str_start_475 = str_start_474 + sizeof(str_474) - 1,
  str_start_476 = str_start_475 + sizeof(str_475) - 1,
  str_start_477 = str_start_476 + sizeof(str_476) - 1,
  str_start_478 = str_start_477 + sizeof(str_477) - 1,
  str_start_479 = str_start_478 + sizeof(str_478) - 1,
  str_start_480 = str_start_479 + sizeof(str_479) - 1,
  str_start_481 = str_start_480 + sizeof(str_480) - 1,
  str_start_482 = str_start_481 + sizeof(str_481) - 1,
  str_start_483 = str_start_482 + sizeof(str_482) - 1,
  str_start_484 = str_start_483 + sizeof(str_483) - 1,
  str_start_485 = str_start_484 + sizeof(str_484) - 1,
  str_start_486 = str_start_485 + sizeof(str_485) - 1,
  str_start_487 = str_start_486 + sizeof(str_486) - 1,
  str_start_488 = str_start_487 + sizeof(str_487) - 1,
  str_start_489 = str_start_488 + sizeof(str_488) - 1,
  str_start_490 = str_start_489 + sizeof(str_489) - 1,
  str_start_491 = str_start_490 + sizeof(str_490) - 1,
  str_start_492 = str_start_491 + sizeof(str_491) - 1,
  str_start_493 = str_start_492 + sizeof(str_492) - 1,
  str_start_494 = str_start_493 + sizeof(str_493) - 1,
  str_start_495 = str_start_494 + sizeof(str_494) - 1,
  str_start_496 = str_start_495 + sizeof(str_495) - 1,
  str_start_497 = str_start_496 + sizeof(str_496) - 1,
  str_start_498 = str_start_497 + sizeof(str_497) - 1,
  str_start_499 = str_start_498 + sizeof(str_498) - 1,
  str_start_500 = str_start_499 + sizeof(str_499) - 1,
  str_start_501 = str_start_500 + sizeof(str_500) - 1,
  str_start_502 = str_start_501 + sizeof(str_501) - 1,
  str_start_503 = str_start_502 + sizeof(str_502) - 1,
  str_start_504 = str_start_503 + sizeof(str_503) - 1,
  str_start_505 = str_start_504 + sizeof(str_504) - 1,
  str_start_506 = str_start_505 + sizeof(str_505) - 1,
  str_start_507 = str_start_506 + sizeof(str_506) - 1,
  str_start_508 = str_start_507 + sizeof(str_507) - 1,
  str_start_509 = str_start_508 + sizeof(str_508) - 1,
  str_start_510 = str_start_509 + sizeof(str_509) - 1,
  str_start_511 = str_start_510 + sizeof(str_510) - 1,
  str_start_512 = str_start_511 + sizeof(str_511) - 1,
  str_start_513 = str_start_512 + sizeof(str_512) - 1,
  str_start_514 = str_start_513 + sizeof(str_513) - 1,
  str_start_515 = str_start_514 + sizeof(str_514) - 1,
  str_start_516 = str_start_515 + sizeof(str_515) - 1,
  str_start_517 = str_start_516 + sizeof(str_516) - 1,
  str_start_518 = str_start_517 + sizeof(str_517) - 1,
  str_start_519 = str_start_518 + sizeof(str_518) - 1,
  str_start_520 = str_start_519 + sizeof(str_519) - 1,
  str_start_521 = str_start_520 + sizeof(str_520) - 1,
  str_start_522 = str_start_521 + sizeof(str_521) - 1,
  str_start_523 = str_start_522 + sizeof(str_522) - 1,
  str_start_524 = str_start_523 + sizeof(str_523) - 1,
  str_start_525 = str_start_524 + sizeof(str_524) - 1,
  str_start_526 = str_start_525 + sizeof(str_525) - 1,
  str_start_527 = str_start_526 + sizeof(str_526) - 1,
  str_start_528 = str_start_527 + sizeof(str_527) - 1,
  str_start_529 = str_start_528 + sizeof(str_528) - 1,
  str_start_530 = str_start_529 + sizeof(str_529) - 1,
  str_start_531 = str_start_530 + sizeof(str_530) - 1,
  str_start_532 = str_start_531 + sizeof(str_531) - 1,
  str_start_533 = str_start_532 + sizeof(str_532) - 1,
  str_start_534 = str_start_533 + sizeof(str_533) - 1,
  str_start_535 = str_start_534 + sizeof(str_534) - 1,
  str_start_536 = str_start_535 + sizeof(str_535) - 1,
  str_start_537 = str_start_536 + sizeof(str_536) - 1,
  str_start_538 = str_start_537 + sizeof(str_537) - 1,
  str_start_539 = str_start_538 + sizeof(str_538) - 1,
  str_start_540 = str_start_539 + sizeof(str_539) - 1,
  str_start_541 = str_start_540 + sizeof(str_540) - 1,
  str_start_542 = str_start_541 + sizeof(str_541) - 1,
  str_start_543 = str_start_542 + sizeof(str_542) - 1,
  str_start_544 = str_start_543 + sizeof(str_543) - 1,
  str_start_545 = str_start_544 + sizeof(str_544) - 1,
  str_start_546 = str_start_545 + sizeof(str_545) - 1,
  str_start_547 = str_start_546 + sizeof(str_546) - 1,
  str_start_548 = str_start_547 + sizeof(str_547) - 1,
  str_start_549 = str_start_548 + sizeof(str_548) - 1,
  str_start_550 = str_start_549 + sizeof(str_549) - 1,
  str_start_551 = str_start_550 + sizeof(str_550) - 1,
  str_start_552 = str_start_551 + sizeof(str_551) - 1,
  str_start_553 = str_start_552 + sizeof(str_552) - 1,
  str_start_554 = str_start_553 + sizeof(str_553) - 1,
  str_start_555 = str_start_554 + sizeof(str_554) - 1,
  str_start_556 = str_start_555 + sizeof(str_555) - 1,
  str_start_557 = str_start_556 + sizeof(str_556) - 1,
  str_start_558 = str_start_557 + sizeof(str_557) - 1,
  str_start_559 = str_start_558 + sizeof(str_558) - 1,
  str_start_560 = str_start_559 + sizeof(str_559) - 1,
  str_start_561 = str_start_560 + sizeof(str_560) - 1,
  str_start_562 = str_start_561 + sizeof(str_561) - 1,
  str_start_563 = str_start_562 + sizeof(str_562) - 1,
  str_start_564 = str_start_563 + sizeof(str_563) - 1,
  str_start_565 = str_start_564 + sizeof(str_564) - 1,
  str_start_566 = str_start_565 + sizeof(str_565) - 1,
  str_start_567 = str_start_566 + sizeof(str_566) - 1,
  str_start_568 = str_start_567 + sizeof(str_567) - 1,
  str_start_569 = str_start_568 + sizeof(str_568) - 1,
  str_start_570 = str_start_569 + sizeof(str_569) - 1,
  str_start_571 = str_start_570 + sizeof(str_570) - 1,
  str_start_572 = str_start_571 + sizeof(str_571) - 1,
  str_start_573 = str_start_572 + sizeof(str_572) - 1,
  str_start_574 = str_start_573 + sizeof(str_573) - 1,
  str_start_575 = str_start_574 + sizeof(str_574) - 1,
  str_start_576 = str_start_575 + sizeof(str_575) - 1,
  str_start_577 = str_start_576 + sizeof(str_576) - 1,
  str_start_578 = str_start_577 + sizeof(str_577) - 1,
  str_start_579 = str_start_578 + sizeof(str_578) - 1,
  str_start_580 = str_start_579 + sizeof(str_579) - 1,
  str_start_581 = str_start_580 + sizeof(str_580) - 1,
  str_start_582 = str_start_581 + sizeof(str_581) - 1,
  str_start_583 = str_start_582 + sizeof(str_582) - 1,
  str_start_584 = str_start_583 + sizeof(str_583) - 1,
  str_start_585 = str_start_584 + sizeof(str_584) - 1,
  str_start_586 = str_start_585 + sizeof(str_585) - 1,
  str_start_587 = str_start_586 + sizeof(str_586) - 1,
  str_start_588 = str_start_587 + sizeof(str_587) - 1,
  str_start_589 = str_start_588 + sizeof(str_588) - 1,
  str_start_590 = str_start_589 + sizeof(str_589) - 1,
  str_start_591 = str_start_590 + sizeof(str_590) - 1,
  str_start_592 = str_start_591 + sizeof(str_591) - 1,
  str_start_593 = str_start_592 + sizeof(str_592) - 1,
  str_start_594 = str_start_593 + sizeof(str_593) - 1,
  str_start_595 = str_start_594 + sizeof(str_594) - 1,
  str_start_596 = str_start_595 + sizeof(str_595) - 1,
  str_start_597 = str_start_596 + sizeof(str_596) - 1,
  str_start_598 = str_start_597 + sizeof(str_597) - 1,
  str_start_599 = str_start_598 + sizeof(str_598) - 1,
  str_start_600 = str_start_599 + sizeof(str_599) - 1,
  str_start_601 = str_start_600 + sizeof(str_600) - 1,
  str_start_602 = str_start_601 + sizeof(str_601) - 1,
  str_start_603 = str_start_602 + sizeof(str_602) - 1,
  str_start_604 = str_start_603 + sizeof(str_603) - 1,
  str_start_605 = str_start_604 + sizeof(str_604) - 1,
  str_start_606 = str_start_605 + sizeof(str_605) - 1,
  str_start_607 = str_start_606 + sizeof(str_606) - 1,
  str_start_608 = str_start_607 + sizeof(str_607) - 1,
  str_start_609 = str_start_608 + sizeof(str_608) - 1,
  str_start_610 = str_start_609 + sizeof(str_609) - 1,
  str_start_611 = str_start_610 + sizeof(str_610) - 1,
  str_start_612 = str_start_611 + sizeof(str_611) - 1,
  str_start_613 = str_start_612 + sizeof(str_612) - 1,
  str_start_614 = str_start_613 + sizeof(str_613) - 1,
  str_start_615 = str_start_614 + sizeof(str_614) - 1,
  str_start_616 = str_start_615 + sizeof(str_615) - 1,
  str_start_617 = str_start_616 + sizeof(str_616) - 1,
  str_start_618 = str_start_617 + sizeof(str_617) - 1,
  str_start_619 = str_start_618 + sizeof(str_618) - 1,
  str_start_620 = str_start_619 + sizeof(str_619) - 1,
  str_start_621 = str_start_620 + sizeof(str_620) - 1,
  str_start_622 = str_start_621 + sizeof(str_621) - 1,
  str_start_623 = str_start_622 + sizeof(str_622) - 1,
  str_start_624 = str_start_623 + sizeof(str_623) - 1,
  str_start_625 = str_start_624 + sizeof(str_624) - 1,
  str_start_626 = str_start_625 + sizeof(str_625) - 1,
  str_start_627 = str_start_626 + sizeof(str_626) - 1,
  str_start_628 = str_start_627 + sizeof(str_627) - 1,
  str_start_629 = str_start_628 + sizeof(str_628) - 1,
  str_start_630 = str_start_629 + sizeof(str_629) - 1,
  str_start_631 = str_start_630 + sizeof(str_630) - 1,
  str_start_632 = str_start_631 + sizeof(str_631) - 1,
  str_start_633 = str_start_632 + sizeof(str_632) - 1,
  str_start_634 = str_start_633 + sizeof(str_633) - 1,
  str_start_635 = str_start_634 + sizeof(str_634) - 1,
  str_start_636 = str_start_635 + sizeof(str_635) - 1,
  str_start_637 = str_start_636 + sizeof(str_636) - 1,
  str_start_638 = str_start_637 + sizeof(str_637) - 1,
  str_start_639 = str_start_638 + sizeof(str_638) - 1,
  str_start_640 = str_start_639 + sizeof(str_639) - 1,
  str_start_641 = str_start_640 + sizeof(str_640) - 1,
  str_start_642 = str_start_641 + sizeof(str_641) - 1,
  str_start_643 = str_start_642 + sizeof(str_642) - 1,
  str_start_644 = str_start_643 + sizeof(str_643) - 1,
  str_start_645 = str_start_644 + sizeof(str_644) - 1,
  str_start_646 = str_start_645 + sizeof(str_645) - 1,
  str_start_647 = str_start_646 + sizeof(str_646) - 1,
  str_start_648 = str_start_647 + sizeof(str_647) - 1,
  str_start_649 = str_start_648 + sizeof(str_648) - 1,
  str_start_650 = str_start_649 + sizeof(str_649) - 1,
  str_start_651 = str_start_650 + sizeof(str_650) - 1,
  str_start_652 = str_start_651 + sizeof(str_651) - 1,
  str_start_653 = str_start_652 + sizeof(str_652) - 1,
  str_start_654 = str_start_653 + sizeof(str_653) - 1,
  str_start_655 = str_start_654 + sizeof(str_654) - 1,
  str_start_656 = str_start_655 + sizeof(str_655) - 1,
  str_start_657 = str_start_656 + sizeof(str_656) - 1,
  str_start_658 = str_start_657 + sizeof(str_657) - 1,
  str_start_659 = str_start_658 + sizeof(str_658) - 1,
  str_start_660 = str_start_659 + sizeof(str_659) - 1,
  str_start_661 = str_start_660 + sizeof(str_660) - 1,
  str_start_662 = str_start_661 + sizeof(str_661) - 1,
  str_start_663 = str_start_662 + sizeof(str_662) - 1,
  str_start_664 = str_start_663 + sizeof(str_663) - 1,
  str_start_665 = str_start_664 + sizeof(str_664) - 1,
  str_start_666 = str_start_665 + sizeof(str_665) - 1,
  str_start_667 = str_start_666 + sizeof(str_666) - 1,
  str_start_668 = str_start_667 + sizeof(str_667) - 1,
  str_start_end
} str_starts;

/*:1795*/

packed_ASCII_code str_pool[pool_size + 1] = /*1793:*/

    str_0_255 str_256 str_257 str_258 str_259 str_260 str_261 str_262 str_263
        str_264 str_265 str_266 str_267 str_268 str_269 str_270 str_271 str_272
            str_273 str_274 str_275 str_276 str_277 str_278 str_279 str_280
                str_281 str_282 str_283 str_284 str_285 str_286 str_287 str_288
                    str_289 str_290 str_291 str_292 str_293 str_294 str_295
                        str_296 str_297 str_298 str_299 str_300 str_301 str_302
                            str_303 str_304 str_305 str_306 str_307 str_308
                                str_309 str_310 str_311 str_312 str_313 str_314
                                    str_315 str_316 str_317 str_318 str_319
                                        str_320 str_321 str_322 str_323 str_324
                                            str_325 str_326 str_327 str_328
                                                str_329 str_330 str_331 str_332
                                                    str_333 str_334 str_335
                                                        str_336 str_337 str_338
                                                            str_339 str_340
                                                                str_341 str_342
                                                                    str_343 str_344
                                                                        str_345 str_346
                                                                            str_347 str_348
                                                                                str_349 str_350
                                                                                    str_351 str_352
                                                                                        str_353 str_354
                                                                                            str_355
                                                                                                str_356 str_357 str_358 str_359 str_360 str_361 str_362 str_363 str_364 str_365 str_366 str_367 str_368 str_369 str_370 str_371 str_372 str_373 str_374 str_375 str_376 str_377 str_378 str_379 str_380 str_381 str_382 str_383 str_384 str_385 str_386 str_387
                                                                                                    str_388
                                                                                                        str_389
                                                                                                            str_390
                                                                                                                str_391
                                                                                                                    str_392
                                                                                                                        str_393
                                                                                                                            str_394
                                                                                                                                str_395
                                                                                                                                    str_396
                                                                                                                                        str_397
                                                                                                                                            str_398
                                                                                                                                                str_399
                                                                                                                                                    str_400
                                                                                                                                                        str_401
                                                                                                                                                            str_402
                                                                                                                                                                str_403
                                                                                                                                                                    str_404 str_405 str_406 str_407 str_408 str_409 str_410 str_411 str_412 str_413 str_414 str_415 str_416 str_417 str_418 str_419 str_420 str_421 str_422 str_423 str_424 str_425 str_426 str_427 str_428 str_429 str_430 str_431 str_432 str_433 str_434 str_435 str_436 str_437 str_438 str_439 str_440 str_441 str_442 str_443 str_444 str_445 str_446 str_447 str_448 str_449 str_450 str_451 str_452 str_453 str_454 str_455 str_456 str_457 str_458 str_459 str_460 str_461 str_462 str_463 str_464 str_465 str_466 str_467 str_468 str_469 str_470 str_471 str_472 str_473 str_474 str_475 str_476 str_477 str_478
                                                                                                                                                                        str_479 str_480
                                                                                                                                                                            str_481 str_482
                                                                                                                                                                                str_483
                                                                                                                                                                                    str_484 str_485 str_486 str_487 str_488 str_489 str_490 str_491 str_492 str_493 str_494 str_495 str_496 str_497 str_498 str_499 str_500 str_501 str_502
                                                                                                                                                                                        str_503 str_504
                                                                                                                                                                                            str_505 str_506
                                                                                                                                                                                                str_507 str_508
                                                                                                                                                                                                    str_509 str_510
                                                                                                                                                                                                        str_511 str_512
                                                                                                                                                                                                            str_513 str_514
                                                                                                                                                                                                                str_515 str_516
                                                                                                                                                                                                                    str_517 str_518
                                                                                                                                                                                                                        str_519 str_520
                                                                                                                                                                                                                            str_521 str_522
                                                                                                                                                                                                                                str_523
                                                                                                                                                                                                                                    str_524 str_525 str_526 str_527 str_528 str_529 str_530 str_531 str_532 str_533 str_534
                                                                                                                                                                                                                                        str_535 str_536
                                                                                                                                                                                                                                            str_537 str_538 str_539 str_540 str_541 str_542 str_543 str_544 str_545 str_546 str_547 str_548 str_549 str_550 str_551 str_552 str_553 str_554 str_555 str_556 str_557 str_558 str_559 str_560 str_561 str_562 str_563 str_564 str_565
                                                                                                                                                                                                                                                str_566 str_567 str_568 str_569 str_570 str_571 str_572 str_573 str_574 str_575 str_576 str_577 str_578 str_579 str_580 str_581 str_582
                                                                                                                                                                                                                                                    str_583 str_584
                                                                                                                                                                                                                                                        str_585 str_586
                                                                                                                                                                                                                                                            str_587 str_588
                                                                                                                                                                                                                                                                str_589
                                                                                                                                                                                                                                                                    str_590
                                                                                                                                                                                                                                                                        str_591 str_592 str_593 str_594 str_595 str_596 str_597 str_598 str_599 str_600 str_601 str_602 str_603 str_604 str_605 str_606 str_607 str_608 str_609 str_610 str_611 str_612 str_613 str_614 str_615 str_616 str_617 str_618 str_619 str_620 str_621 str_622 str_623 str_624 str_625 str_626 str_627 str_628
                                                                                                                                                                                                                                                                            str_629
                                                                                                                                                                                                                                                                                str_630 str_631 str_632 str_633 str_634 str_635 str_636 str_637 str_638 str_639 str_640 str_641 str_642 str_643 str_644 str_645 str_646 str_647 str_648 str_649 str_650 str_651 str_652 str_653 str_654
                                                                                                                                                                                                                                                                                    str_655 str_656
                                                                                                                                                                                                                                                                                        str_657 str_658
                                                                                                                                                                                                                                                                                            str_659 str_660
                                                                                                                                                                                                                                                                                                str_661 str_662
                                                                                                                                                                                                                                                                                                    str_663 str_664
                                                                                                                                                                                                                                                                                                        str_665 str_666
                                                                                                                                                                                                                                                                                                            str_667

/*:1793*/
    ;
pool_pointer str_start[max_strings + 1] = {/*1794:*/

                                           str_start_0_255 str_start_256,
                                           str_start_257,
                                           str_start_258,
                                           str_start_259,
                                           str_start_260,
                                           str_start_261,
                                           str_start_262,
                                           str_start_263,
                                           str_start_264,
                                           str_start_265,
                                           str_start_266,
                                           str_start_267,
                                           str_start_268,
                                           str_start_269,
                                           str_start_270,
                                           str_start_271,
                                           str_start_272,
                                           str_start_273,
                                           str_start_274,
                                           str_start_275,
                                           str_start_276,
                                           str_start_277,
                                           str_start_278,
                                           str_start_279,
                                           str_start_280,
                                           str_start_281,
                                           str_start_282,
                                           str_start_283,
                                           str_start_284,
                                           str_start_285,
                                           str_start_286,
                                           str_start_287,
                                           str_start_288,
                                           str_start_289,
                                           str_start_290,
                                           str_start_291,
                                           str_start_292,
                                           str_start_293,
                                           str_start_294,
                                           str_start_295,
                                           str_start_296,
                                           str_start_297,
                                           str_start_298,
                                           str_start_299,
                                           str_start_300,
                                           str_start_301,
                                           str_start_302,
                                           str_start_303,
                                           str_start_304,
                                           str_start_305,
                                           str_start_306,
                                           str_start_307,
                                           str_start_308,
                                           str_start_309,
                                           str_start_310,
                                           str_start_311,
                                           str_start_312,
                                           str_start_313,
                                           str_start_314,
                                           str_start_315,
                                           str_start_316,
                                           str_start_317,
                                           str_start_318,
                                           str_start_319,
                                           str_start_320,
                                           str_start_321,
                                           str_start_322,
                                           str_start_323,
                                           str_start_324,
                                           str_start_325,
                                           str_start_326,
                                           str_start_327,
                                           str_start_328,
                                           str_start_329,
                                           str_start_330,
                                           str_start_331,
                                           str_start_332,
                                           str_start_333,
                                           str_start_334,
                                           str_start_335,
                                           str_start_336,
                                           str_start_337,
                                           str_start_338,
                                           str_start_339,
                                           str_start_340,
                                           str_start_341,
                                           str_start_342,
                                           str_start_343,
                                           str_start_344,
                                           str_start_345,
                                           str_start_346,
                                           str_start_347,
                                           str_start_348,
                                           str_start_349,
                                           str_start_350,
                                           str_start_351,
                                           str_start_352,
                                           str_start_353,
                                           str_start_354,
                                           str_start_355,
                                           str_start_356,
                                           str_start_357,
                                           str_start_358,
                                           str_start_359,
                                           str_start_360,
                                           str_start_361,
                                           str_start_362,
                                           str_start_363,
                                           str_start_364,
                                           str_start_365,
                                           str_start_366,
                                           str_start_367,
                                           str_start_368,
                                           str_start_369,
                                           str_start_370,
                                           str_start_371,
                                           str_start_372,
                                           str_start_373,
                                           str_start_374,
                                           str_start_375,
                                           str_start_376,
                                           str_start_377,
                                           str_start_378,
                                           str_start_379,
                                           str_start_380,
                                           str_start_381,
                                           str_start_382,
                                           str_start_383,
                                           str_start_384,
                                           str_start_385,
                                           str_start_386,
                                           str_start_387,
                                           str_start_388,
                                           str_start_389,
                                           str_start_390,
                                           str_start_391,
                                           str_start_392,
                                           str_start_393,
                                           str_start_394,
                                           str_start_395,
                                           str_start_396,
                                           str_start_397,
                                           str_start_398,
                                           str_start_399,
                                           str_start_400,
                                           str_start_401,
                                           str_start_402,
                                           str_start_403,
                                           str_start_404,
                                           str_start_405,
                                           str_start_406,
                                           str_start_407,
                                           str_start_408,
                                           str_start_409,
                                           str_start_410,
                                           str_start_411,
                                           str_start_412,
                                           str_start_413,
                                           str_start_414,
                                           str_start_415,
                                           str_start_416,
                                           str_start_417,
                                           str_start_418,
                                           str_start_419,
                                           str_start_420,
                                           str_start_421,
                                           str_start_422,
                                           str_start_423,
                                           str_start_424,
                                           str_start_425,
                                           str_start_426,
                                           str_start_427,
                                           str_start_428,
                                           str_start_429,
                                           str_start_430,
                                           str_start_431,
                                           str_start_432,
                                           str_start_433,
                                           str_start_434,
                                           str_start_435,
                                           str_start_436,
                                           str_start_437,
                                           str_start_438,
                                           str_start_439,
                                           str_start_440,
                                           str_start_441,
                                           str_start_442,
                                           str_start_443,
                                           str_start_444,
                                           str_start_445,
                                           str_start_446,
                                           str_start_447,
                                           str_start_448,
                                           str_start_449,
                                           str_start_450,
                                           str_start_451,
                                           str_start_452,
                                           str_start_453,
                                           str_start_454,
                                           str_start_455,
                                           str_start_456,
                                           str_start_457,
                                           str_start_458,
                                           str_start_459,
                                           str_start_460,
                                           str_start_461,
                                           str_start_462,
                                           str_start_463,
                                           str_start_464,
                                           str_start_465,
                                           str_start_466,
                                           str_start_467,
                                           str_start_468,
                                           str_start_469,
                                           str_start_470,
                                           str_start_471,
                                           str_start_472,
                                           str_start_473,
                                           str_start_474,
                                           str_start_475,
                                           str_start_476,
                                           str_start_477,
                                           str_start_478,
                                           str_start_479,
                                           str_start_480,
                                           str_start_481,
                                           str_start_482,
                                           str_start_483,
                                           str_start_484,
                                           str_start_485,
                                           str_start_486,
                                           str_start_487,
                                           str_start_488,
                                           str_start_489,
                                           str_start_490,
                                           str_start_491,
                                           str_start_492,
                                           str_start_493,
                                           str_start_494,
                                           str_start_495,
                                           str_start_496,
                                           str_start_497,
                                           str_start_498,
                                           str_start_499,
                                           str_start_500,
                                           str_start_501,
                                           str_start_502,
                                           str_start_503,
                                           str_start_504,
                                           str_start_505,
                                           str_start_506,
                                           str_start_507,
                                           str_start_508,
                                           str_start_509,
                                           str_start_510,
                                           str_start_511,
                                           str_start_512,
                                           str_start_513,
                                           str_start_514,
                                           str_start_515,
                                           str_start_516,
                                           str_start_517,
                                           str_start_518,
                                           str_start_519,
                                           str_start_520,
                                           str_start_521,
                                           str_start_522,
                                           str_start_523,
                                           str_start_524,
                                           str_start_525,
                                           str_start_526,
                                           str_start_527,
                                           str_start_528,
                                           str_start_529,
                                           str_start_530,
                                           str_start_531,
                                           str_start_532,
                                           str_start_533,
                                           str_start_534,
                                           str_start_535,
                                           str_start_536,
                                           str_start_537,
                                           str_start_538,
                                           str_start_539,
                                           str_start_540,
                                           str_start_541,
                                           str_start_542,
                                           str_start_543,
                                           str_start_544,
                                           str_start_545,
                                           str_start_546,
                                           str_start_547,
                                           str_start_548,
                                           str_start_549,
                                           str_start_550,
                                           str_start_551,
                                           str_start_552,
                                           str_start_553,
                                           str_start_554,
                                           str_start_555,
                                           str_start_556,
                                           str_start_557,
                                           str_start_558,
                                           str_start_559,
                                           str_start_560,
                                           str_start_561,
                                           str_start_562,
                                           str_start_563,
                                           str_start_564,
                                           str_start_565,
                                           str_start_566,
                                           str_start_567,
                                           str_start_568,
                                           str_start_569,
                                           str_start_570,
                                           str_start_571,
                                           str_start_572,
                                           str_start_573,
                                           str_start_574,
                                           str_start_575,
                                           str_start_576,
                                           str_start_577,
                                           str_start_578,
                                           str_start_579,
                                           str_start_580,
                                           str_start_581,
                                           str_start_582,
                                           str_start_583,
                                           str_start_584,
                                           str_start_585,
                                           str_start_586,
                                           str_start_587,
                                           str_start_588,
                                           str_start_589,
                                           str_start_590,
                                           str_start_591,
                                           str_start_592,
                                           str_start_593,
                                           str_start_594,
                                           str_start_595,
                                           str_start_596,
                                           str_start_597,
                                           str_start_598,
                                           str_start_599,
                                           str_start_600,
                                           str_start_601,
                                           str_start_602,
                                           str_start_603,
                                           str_start_604,
                                           str_start_605,
                                           str_start_606,
                                           str_start_607,
                                           str_start_608,
                                           str_start_609,
                                           str_start_610,
                                           str_start_611,
                                           str_start_612,
                                           str_start_613,
                                           str_start_614,
                                           str_start_615,
                                           str_start_616,
                                           str_start_617,
                                           str_start_618,
                                           str_start_619,
                                           str_start_620,
                                           str_start_621,
                                           str_start_622,
                                           str_start_623,
                                           str_start_624,
                                           str_start_625,
                                           str_start_626,
                                           str_start_627,
                                           str_start_628,
                                           str_start_629,
                                           str_start_630,
                                           str_start_631,
                                           str_start_632,
                                           str_start_633,
                                           str_start_634,
                                           str_start_635,
                                           str_start_636,
                                           str_start_637,
                                           str_start_638,
                                           str_start_639,
                                           str_start_640,
                                           str_start_641,
                                           str_start_642,
                                           str_start_643,
                                           str_start_644,
                                           str_start_645,
                                           str_start_646,
                                           str_start_647,
                                           str_start_648,
                                           str_start_649,
                                           str_start_650,
                                           str_start_651,
                                           str_start_652,
                                           str_start_653,
                                           str_start_654,
                                           str_start_655,
                                           str_start_656,
                                           str_start_657,
                                           str_start_658,
                                           str_start_659,
                                           str_start_660,
                                           str_start_661,
                                           str_start_662,
                                           str_start_663,
                                           str_start_664,
                                           str_start_665,
                                           str_start_666,
                                           str_start_667,
                                           str_start_668

/*:1794*/
};
pool_pointer pool_ptr = /*1796:*/
    str_start_668

/*:1796*/
    ;
str_number str_ptr = /*1797:*/
    668

/*:1797*/
    ;
pool_pointer init_pool_ptr;
str_number init_str_ptr;

/*:39*/ /*50:*/

#ifdef INIT
alpha_file pool_file;
#endif

/*:50*/ /*54:*/

alpha_file log_file;
uint8_t selector;
uint8_t dig[23];
int tally;
uint8_t term_offset;

uint8_t file_offset;

ASCII_code trick_buf[error_line + 1];

int trick_count;
int first_count;

/*:54*/ /*73:*/

uint8_t interaction;

/*:73*/ /*76:*/

bool deletions_allowed;
bool set_box_allowed;
uint8_t history;
int8_t error_count;

/*:76*/ /*79:*/

char *help_line[6];
uint8_t help_ptr;
bool use_err_help;

/*:79*/ /*96:*/

int interrupt;
bool OK_to_interrupt;

/*:96*/ /*104:*/

bool arith_error;
scaled rem;

/*:104*/ /*115:*/

pointer temp_ptr;

/*:115*/ /*116:*/

memory_word mem0[mem_max - mem_min + 1], *const mem = mem0 - mem_min;
pointer lo_mem_max;
pointer hi_mem_min;

/*:116*/ /*117:*/

int var_used, dyn_used;
#ifdef DEBUG
#define incr_dyn_used incr(dyn_used)
#define decr_dyn_used decr(dyn_used)
#else
#define incr_dyn_used
#define decr_dyn_used
#endif

/*:117*/ /*118:*/

pointer avail;
pointer mem_end;

/*:118*/ /*124:*/

pointer rover;

/*:124*/ /*165:*/

#ifdef DEBUG
bool is_free0[mem_max - mem_min + 1], *const is_free = is_free0 - mem_min;
bool was_free0[mem_max - mem_min + 1], *const was_free = was_free0 - mem_min;

pointer was_mem_end, was_lo_max, was_hi_min;

bool panicking;
#endif

/*:165*/ /*173:*/

int font_in_short_display;

/*:173*/ /*181:*/

int depth_threshold;
int breadth_max;

/*:181*/ /*213:*/

list_state_record nest[nest_size + 1];
uint8_t nest_ptr;
uint8_t max_nest_stack;
list_state_record cur_list;
int16_t shown_mode;

/*:213*/ /*246:*/

uint8_t old_setting;
int sys_time, sys_day, sys_month, sys_year;

/*:246*/ /*253:*/

memory_word eqtb0[eqtb_size - active_base + 1], *const eqtb =
                                                    eqtb0 - active_base;
quarterword xeq_level0[eqtb_size - int_base + 1], *const xeq_level =
                                                      xeq_level0 - int_base;

/*:253*/ /*256:*/

two_halves hash0[undefined_control_sequence - hash_base], *const hash =
                                                              hash0 - hash_base;

pointer hash_used;
bool no_new_control_sequence;
int cs_count;

/*:256*/ /*271:*/

memory_word save_stack[save_size + 1];
uint16_t save_ptr;
uint16_t max_save_stack;
quarterword cur_level;
group_code cur_group;
uint16_t cur_boundary;

/*:271*/ /*286:*/

int mag_set;

/*:286*/ /*297:*/

eight_bits cur_cmd;
halfword cur_chr;
pointer cur_cs;
halfword cur_tok;

/*:297*/ /*301:*/

in_state_record input_stack[stack_size + 1];
uint8_t input_ptr;
uint8_t max_in_stack;
in_state_record cur_input;

/*:301*/ /*304:*/

uint8_t in_open;
uint8_t open_parens;
alpha_file input_file0[max_in_open], *const input_file = input_file0 - 1;
int line;
int line_stack0[max_in_open], *const line_stack = line_stack0 - 1;

/*:304*/ /*305:*/

uint8_t scanner_status;
pointer warning_index;
pointer def_ref;

/*:305*/ /*308:*/

pointer param_stack[param_size + 1];

uint8_t param_ptr;
int max_param_stack;

/*:308*/ /*309:*/

int align_state;

/*:309*/ /*310:*/

uint8_t base_ptr;

/*:310*/ /*333:*/

pointer par_loc;
halfword par_token;

/*:333*/ /*361:*/

bool force_eof;

/*:361*/ /*382:*/

pointer cur_mark0[split_bot_mark_code - top_mark_code + 1], *const cur_mark =
                                                                cur_mark0 -
                                                                top_mark_code;

/*:382*/ /*387:*/

uint8_t long_state;

/*:387*/ /*388:*/

pointer pstack[9];

/*:388*/ /*410:*/

int cur_val;
uint8_t cur_val_level;

/*:410*/ /*438:*/

small_number radix;

/*:438*/ /*447:*/

glue_ord cur_order;

/*:447*/ /*480:*/

alpha_file read_file[16];
uint8_t read_open[17];

/*:480*/ /*489:*/

pointer cond_ptr;
uint8_t if_limit;
small_number cur_if;
int if_line;

/*:489*/ /*493:*/

int skip_line;

/*:493*/ /*512:*/

str_number cur_name;
str_number cur_area;
str_number cur_ext;

/*:512*/ /*513:*/

pool_pointer area_delimiter;
pool_pointer ext_delimiter;

/*:513*/ /*520:*/

ASCII_code TEX_format_default[1 + format_default_length + 1] =
    " TeXformats/plain.fmt";

/*:520*/ /*526:*/

bool name_in_progress;
str_number job_name;
bool log_opened;

/*:526*/ /*532:*/

byte_file dvi_file;
str_number output_file_name;
str_number log_name;

/*:532*/ /*539:*/

byte_file tfm_file;

/*:539*/ /*549:*/

memory_word font_info[font_mem_size + 1];

font_index fmem_ptr;
internal_font_number font_ptr;
four_quarters font_check0[font_max - font_base + 1], *const font_check =
                                                         font_check0 -
                                                         font_base;
scaled font_size0[font_max - font_base + 1], *const font_size =
                                                 font_size0 - font_base;
scaled font_dsize0[font_max - font_base + 1], *const font_dsize =
                                                  font_dsize0 - font_base;
font_index font_params0[font_max - font_base + 1], *const font_params =
                                                       font_params0 - font_base;

str_number font_name0[font_max - font_base + 1], *const font_name =
                                                     font_name0 - font_base;
str_number font_area0[font_max - font_base + 1], *const font_area =
                                                     font_area0 - font_base;
eight_bits font_bc0[font_max - font_base + 1], *const font_bc =
                                                   font_bc0 - font_base;

eight_bits font_ec0[font_max - font_base + 1], *const font_ec =
                                                   font_ec0 - font_base;

pointer font_glue0[font_max - font_base + 1], *const font_glue =
                                                  font_glue0 - font_base;

bool font_used0[font_max - font_base + 1], *const font_used =
                                               font_used0 - font_base;

int hyphen_char0[font_max - font_base + 1], *const hyphen_char =
                                                hyphen_char0 - font_base;

int skew_char0[font_max - font_base + 1], *const skew_char =
                                              skew_char0 - font_base;

font_index bchar_label0[font_max - font_base + 1], *const bchar_label =
                                                       bchar_label0 - font_base;

uint16_t font_bchar0[font_max - font_base + 1], *const font_bchar =
                                                    font_bchar0 - font_base;

uint16_t font_false_bchar0[font_max - font_base + 1], *const font_false_bchar =
                                                          font_false_bchar0 -
                                                          font_base;

/*:549*/ /*550:*/

int char_base0[font_max - font_base + 1], *const char_base =
                                              char_base0 - font_base;

int width_base0[font_max - font_base + 1], *const width_base =
                                               width_base0 - font_base;

int height_base0[font_max - font_base + 1], *const height_base =
                                                height_base0 - font_base;

int depth_base0[font_max - font_base + 1], *const depth_base =
                                               depth_base0 - font_base;

int italic_base0[font_max - font_base + 1], *const italic_base =
                                                italic_base0 - font_base;

int lig_kern_base0[font_max - font_base + 1], *const lig_kern_base =
                                                  lig_kern_base0 - font_base;

int kern_base0[font_max - font_base + 1], *const kern_base =
                                              kern_base0 - font_base;

int exten_base0[font_max - font_base + 1], *const exten_base =
                                               exten_base0 - font_base;

int param_base0[font_max - font_base + 1], *const param_base =
                                               param_base0 - font_base;

/*:550*/ /*555:*/

four_quarters null_character;

/*:555*/ /*592:*/

int total_pages;
scaled max_v;
scaled max_h;
int max_push;
int last_bop;
int dead_cycles;
bool doing_leaders;

quarterword c, f;
scaled rule_ht, rule_dp, rule_wd;
pointer g;
int lq, lr;

/*:592*/ /*595:*/

eight_bits dvi_buf[dvi_buf_size + 1];
dvi_index half_buf;
dvi_index dvi_limit;
dvi_index dvi_ptr;
int dvi_offset;

int dvi_gone;

/*:595*/ /*605:*/

pointer down_ptr, right_ptr;

/*:605*/ /*616:*/

scaled dvi_h, dvi_v;
scaled cur_h, cur_v;
internal_font_number dvi_f;
int cur_s;

/*:616*/ /*646:*/

scaled total_stretch0[filll - normal + 1],
    *const total_stretch = total_stretch0 - normal,
           total_shrink0[filll - normal + 1],
           *const total_shrink = total_shrink0 - normal;

int last_badness;

/*:646*/ /*647:*/

pointer adjust_tail;

/*:647*/ /*661:*/

int pack_begin_line;

/*:661*/ /*684:*/

two_halves empty_field;
four_quarters null_delimiter;

/*:684*/ /*719:*/

pointer cur_mlist;
small_number cur_style;
small_number cur_size;
scaled cur_mu;
bool mlist_penalties;

/*:719*/ /*724:*/

internal_font_number cur_f;
quarterword cur_c;
four_quarters cur_i;

/*:724*/ /*764:*/

int magic_offset;

/*:764*/ /*770:*/

pointer cur_align;
pointer cur_span;
pointer cur_loop;
pointer align_ptr;
pointer cur_head, cur_tail;

/*:770*/ /*814:*/

pointer just_box;

/*:814*/ /*821:*/

pointer passive;
pointer printed_node;
halfword pass_number;

/*:821*/ /*823:*/

scaled active_width0[6], *const active_width = active_width0 - 1;

scaled cur_active_width0[6], *const cur_active_width = cur_active_width0 - 1;
scaled background0[6], *const background = background0 - 1;
scaled break_width0[6], *const break_width = break_width0 - 1;

/*:823*/ /*825:*/

bool no_shrink_error_yet;

/*:825*/ /*828:*/

pointer cur_p;
bool second_pass;
bool final_pass;
int threshold;

/*:828*/ /*833:*/

int minimal_demerits0[tight_fit - very_loose_fit + 1], *const minimal_demerits =
                                                           minimal_demerits0 -
                                                           very_loose_fit;

int minimum_demerits;

pointer best_place0[tight_fit - very_loose_fit + 1], *const best_place =
                                                         best_place0 -
                                                         very_loose_fit;

halfword best_pl_line0[tight_fit - very_loose_fit + 1], *const best_pl_line =
                                                            best_pl_line0 -
                                                            very_loose_fit;

/*:833*/ /*839:*/

scaled disc_width;

/*:839*/ /*847:*/

halfword easy_line;
halfword last_special_line;

scaled first_width;

scaled second_width;
scaled first_indent;
scaled second_indent;

/*:847*/ /*872:*/

pointer best_bet;
int fewest_demerits;
halfword best_line;
int actual_looseness;

int line_diff;

/*:872*/ /*892:*/

uint16_t hc[66];
uint8_t hn;

pointer ha, hb;
internal_font_number hf;
uint16_t hu[64];
int hyf_char;
ASCII_code cur_lang, init_cur_lang;
int l_hyf, r_hyf, init_l_hyf, init_r_hyf;
halfword hyf_bchar;

/*:892*/ /*900:*/

uint8_t hyf[65];
pointer init_list;
bool init_lig;
bool init_lft;

/*:900*/ /*905:*/

small_number hyphen_passed;

/*:905*/ /*907:*/

halfword cur_l, cur_r;
pointer cur_q;
pointer lig_stack;
bool ligature_present;
bool lft_hit, rt_hit;

/*:907*/ /*921:*/

two_halves trie[trie_size + 1];
small_number hyf_distance0[trie_op_size], *const hyf_distance =
                                              hyf_distance0 - 1;
small_number hyf_num0[trie_op_size], *const hyf_num = hyf_num0 - 1;
quarterword hyf_next0[trie_op_size], *const hyf_next = hyf_next0 - 1;
uint16_t op_start[256];

/*:921*/ /*926:*/

str_number hyph_word[hyph_size + 1];
pointer hyph_list[hyph_size + 1];
hyph_pointer hyph_count;

/*:926*/ /*943:*/

#ifdef INIT
uint16_t trie_op_hash0[trie_op_size + trie_op_size + 1], *const trie_op_hash =
                                                             trie_op_hash0 +
                                                             trie_op_size;

quarterword trie_used[256];

ASCII_code trie_op_lang0[trie_op_size], *const trie_op_lang = trie_op_lang0 - 1;

quarterword trie_op_val0[trie_op_size], *const trie_op_val = trie_op_val0 - 1;

uint16_t trie_op_ptr;
#endif

/*:943*/ /*947:*/

#ifdef INIT
packed_ASCII_code trie_c[trie_size + 1];

quarterword trie_o[trie_size + 1];

trie_pointer trie_l[trie_size + 1];

trie_pointer trie_r[trie_size + 1];

trie_pointer trie_ptr;
trie_pointer trie_hash[trie_size + 1];

#endif

/*:947*/ /*950:*/

#ifdef INIT
bool trie_taken0[trie_size], *const trie_taken = trie_taken0 - 1;

trie_pointer trie_min[256];

trie_pointer trie_max;
bool trie_not_ready;
#endif

/*:950*/ /*971:*/

scaled best_height_plus_depth;

/*:971*/ /*980:*/

pointer page_tail;
uint8_t page_contents;
scaled page_max_depth;
pointer best_page_break;
int least_page_cost;
scaled best_size;

/*:980*/ /*982:*/

scaled page_so_far[8];
pointer last_glue;
int last_penalty;
scaled last_kern;
int insert_penalties;

/*:982*/ /*989:*/

bool output_active;

/*:989*/ /*1032:*/

internal_font_number main_f;
four_quarters main_i;
four_quarters main_j;
font_index main_k;
pointer main_p;
int main_s;
halfword bchar;
halfword false_bchar;
bool cancel_boundary;
bool ins_disc;

/*:1032*/ /*1074:*/

pointer cur_box;

/*:1074*/ /*1266:*/

halfword after_token;

/*:1266*/ /*1281:*/

bool long_help_seen;

/*:1281*/ /*1299:*/

str_number format_ident;

/*:1299*/ /*1305:*/

word_file fmt_file;

/*:1305*/ /*1331:*/

int ready_already;

/*:1331*/ /*1342:*/

alpha_file write_file[16];
bool write_open[18];

/*:1342*/ /*1345:*/

pointer write_loc;

/*:1345*/

void initialize(void) { /*19:*/

  int i;

/*:19*/ /*163:*/

  int k;

/*:163*/ /*927:*/

  hyph_pointer z;

/*:927*/

/*8:*/

/*21:*/

  xchr[040] = ' ';
  xchr[041] = '!';
  xchr[042] = '"';
  xchr[043] = '#';
  xchr[044] = '$';
  xchr[045] = '%';
  xchr[046] = '&';
  xchr[047] = '\'';
  xchr[050] = '(';
  xchr[051] = ')';
  xchr[052] = '*';
  xchr[053] = '+';
  xchr[054] = ',';
  xchr[055] = '-';
  xchr[056] = '.';
  xchr[057] = '/';
  xchr[060] = '0';
  xchr[061] = '1';
  xchr[062] = '2';
  xchr[063] = '3';
  xchr[064] = '4';
  xchr[065] = '5';
  xchr[066] = '6';
  xchr[067] = '7';
  xchr[070] = '8';
  xchr[071] = '9';
  xchr[072] = ':';
  xchr[073] = ';';
  xchr[074] = '<';
  xchr[075] = '=';
  xchr[076] = '>';
  xchr[077] = '?';
  xchr[0100] = '@';
  xchr[0101] = 'A';
  xchr[0102] = 'B';
  xchr[0103] = 'C';
  xchr[0104] = 'D';
  xchr[0105] = 'E';
  xchr[0106] = 'F';
  xchr[0107] = 'G';
  xchr[0110] = 'H';
  xchr[0111] = 'I';
  xchr[0112] = 'J';
  xchr[0113] = 'K';
  xchr[0114] = 'L';
  xchr[0115] = 'M';
  xchr[0116] = 'N';
  xchr[0117] = 'O';
  xchr[0120] = 'P';
  xchr[0121] = 'Q';
  xchr[0122] = 'R';
  xchr[0123] = 'S';
  xchr[0124] = 'T';
  xchr[0125] = 'U';
  xchr[0126] = 'V';
  xchr[0127] = 'W';
  xchr[0130] = 'X';
  xchr[0131] = 'Y';
  xchr[0132] = 'Z';
  xchr[0133] = '[';
  xchr[0134] = '\\';
  xchr[0135] = ']';
  xchr[0136] = '^';
  xchr[0137] = '_';
  xchr[0140] = '`';
  xchr[0141] = 'a';
  xchr[0142] = 'b';
  xchr[0143] = 'c';
  xchr[0144] = 'd';
  xchr[0145] = 'e';
  xchr[0146] = 'f';
  xchr[0147] = 'g';
  xchr[0150] = 'h';
  xchr[0151] = 'i';
  xchr[0152] = 'j';
  xchr[0153] = 'k';
  xchr[0154] = 'l';
  xchr[0155] = 'm';
  xchr[0156] = 'n';
  xchr[0157] = 'o';
  xchr[0160] = 'p';
  xchr[0161] = 'q';
  xchr[0162] = 'r';
  xchr[0163] = 's';
  xchr[0164] = 't';
  xchr[0165] = 'u';
  xchr[0166] = 'v';
  xchr[0167] = 'w';
  xchr[0170] = 'x';
  xchr[0171] = 'y';
  xchr[0172] = 'z';
  xchr[0173] = '{';
  xchr[0174] = '|';
  xchr[0175] = '}';
  xchr[0176] = '~';

/*:21*/ /*23:*/

  for (i = 0; i <= 037; i++) xchr[i] = ' ';
  for (i = 0177; i <= 0377; i++) xchr[i] = ' ';

/*:23*/ /*24:*/

  for (i = first_text_char; i <= last_text_char; i++)
    xord[chr(i)] = invalid_code;
  for (i = 0200; i <= 0377; i++) xord[xchr[i]] = i;
  for (i = 0; i <= 0176; i++) xord[xchr[i]] = i;

/*:24*/ /*74:*/
  interaction = error_stop_mode;

/*:74*/ /*77:*/

  deletions_allowed = true;
  set_box_allowed = true;
  error_count = 0;

/*:77*/ /*80:*/

  help_ptr = 0;
  use_err_help = false;

/*:80*/ /*97:*/

  interrupt = 0;
  OK_to_interrupt = true;

/*:97*/ /*166:*/

#ifdef DEBUG
  was_mem_end = mem_min;
  was_lo_max = mem_min;
  was_hi_min = mem_max;
  panicking = false;
#endif

/*:166*/ /*215:*/

  nest_ptr = 0;
  max_nest_stack = 0;
  mode = vmode;
  head = contrib_head;
  tail = contrib_head;
  prev_depth = ignore_depth;
  mode_line = 0;
  prev_graf = 0;
  shown_mode = 0;
/*991:*/

  page_contents = empty;
  page_tail = page_head;
  link(page_head) = null;
  last_glue = max_halfword;
  last_penalty = 0;
  last_kern = 0;
  page_depth = 0;
  page_max_depth = 0

/*:991*/
      ;

/*:215*/ /*254:*/

  for (k = int_base; k <= eqtb_size; k++) xeq_level[k] = level_one;

/*:254*/ /*257:*/

  no_new_control_sequence = true;
  next(hash_base) = 0;
  text(hash_base) = 0;
  for (k = hash_base + 1; k <= undefined_control_sequence - 1; k++)
    hash[k] = hash[hash_base];

/*:257*/ /*272:*/

  save_ptr = 0;
  cur_level = level_one;
  cur_group = bottom_level;
  cur_boundary = 0;
  max_save_stack = 0;

/*:272*/ /*287:*/

  mag_set = 0;

/*:287*/ /*383:*/

  top_mark = null;
  first_mark = null;
  bot_mark = null;
  split_first_mark = null;
  split_bot_mark = null;

/*:383*/ /*439:*/

  cur_val = 0;
  cur_val_level = int_val;
  radix = 0;
  cur_order = normal;

/*:439*/ /*481:*/

  for (k = 0; k <= 16; k++) read_open[k] = closed;

/*:481*/ /*490:*/

  cond_ptr = null;
  if_limit = normal;
  cur_if = 0;
  if_line = 0;

/*:490*/ /*551:*/

  for (k = font_base; k <= font_max; k++) font_used[k] = false;

/*:551*/ /*556:*/

  null_character.b0 = min_quarterword;
  null_character.b1 = min_quarterword;
  null_character.b2 = min_quarterword;
  null_character.b3 = min_quarterword;

/*:556*/ /*593:*/

  total_pages = 0;
  max_v = 0;
  max_h = 0;
  max_push = 0;
  last_bop = -1;
  doing_leaders = false;
  dead_cycles = 0;
  cur_s = -1;

/*:593*/ /*596:*/

  half_buf = dvi_buf_size / 2;
  dvi_limit = dvi_buf_size;
  dvi_ptr = 0;
  dvi_offset = 0;
  dvi_gone = 0;

/*:596*/ /*606:*/

  down_ptr = null;
  right_ptr = null;

/*:606*/ /*648:*/
  adjust_tail = null;
  last_badness = 0;

/*:648*/ /*662:*/

  pack_begin_line = 0;

/*:662*/ /*685:*/

  empty_field.rh = empty;
  empty_field.lh = null;
  null_delimiter.b0 = 0;
  null_delimiter.b1 = min_quarterword;
  null_delimiter.b2 = 0;
  null_delimiter.b3 = min_quarterword;

/*:685*/ /*771:*/

  align_ptr = null;
  cur_align = null;
  cur_span = null;
  cur_loop = null;
  cur_head = null;
  cur_tail = null;

/*:771*/ /*928:*/

  for (z = 0; z <= hyph_size; z++) {
    hyph_word[z] = 0;
    hyph_list[z] = null;
  }
  hyph_count = 0;

/*:928*/ /*990:*/

  output_active = false;
  insert_penalties = 0;

/*:990*/ /*1033:*/

  ligature_present = false;
  cancel_boundary = false;
  lft_hit = false;
  rt_hit = false;
  ins_disc = false;

/*:1033*/ /*1267:*/

  after_token = 0;

/*:1267*/ /*1282:*/
  long_help_seen = false;

/*:1282*/ /*1300:*/

  format_ident = 0;

/*:1300*/ /*1343:*/

  for (k = 0; k <= 17; k++) write_open[k] = false;

/*:1343*/

#ifdef INIT
/*164:*/

  for (k = mem_bot + 1; k <= lo_mem_stat_max; k++) mem[k].sc = 0;

  k = mem_bot;
  while (k <= lo_mem_stat_max)

  {
    glue_ref_count(k) = null + 1;
    stretch_order(k) = normal;
    shrink_order(k) = normal;
    k = k + glue_spec_size;
  }
  stretch(fil_glue) = unity;
  stretch_order(fil_glue) = fil;
  stretch(fill_glue) = unity;
  stretch_order(fill_glue) = fill;
  stretch(ss_glue) = unity;
  stretch_order(ss_glue) = fil;
  shrink(ss_glue) = unity;
  shrink_order(ss_glue) = fil;
  stretch(fil_neg_glue) = -unity;
  stretch_order(fil_neg_glue) = fil;
  rover = lo_mem_stat_max + 1;
  link(rover) = empty_flag;
  node_size(rover) = 1000;
  llink(rover) = rover;
  rlink(rover) = rover;
  lo_mem_max = rover + 1000;
  link(lo_mem_max) = null;
  info(lo_mem_max) = null;
  for (k = hi_mem_stat_min; k <= mem_top; k++) mem[k] = mem[lo_mem_max];
/*790:*/

  info(omit_template) = end_template_token;

/*:790*/ /*797:*/

  link(end_span) = max_quarterword + 1;
  info(end_span) = null;

/*:797*/ /*820:*/

  type(last_active) = hyphenated;
  line_number(last_active) = max_halfword;
  subtype(last_active) = 0;

/*:820*/ /*981:*/

  subtype(page_ins_head) = qi(255);
  type(page_ins_head) = split_up;
  link(page_ins_head) = page_ins_head;

/*:981*/ /*988:*/

  type(page_head) = glue_node;
  subtype(page_head) = normal;

/*:988*/
  ;
  avail = null;
  mem_end = mem_top;
  hi_mem_min = hi_mem_stat_min;
  var_used = lo_mem_stat_max + 1 - mem_bot;
  dyn_used = hi_mem_stat_usage;

/*:164*/ /*222:*/

  eq_type(undefined_control_sequence) = undefined_cs;
  equiv(undefined_control_sequence) = null;
  eq_level(undefined_control_sequence) = level_zero;
  for (k = active_base; k <= undefined_control_sequence - 1; k++)
    eqtb[k] = eqtb[undefined_control_sequence];

/*:222*/ /*228:*/

  equiv(glue_base) = zero_glue;
  eq_level(glue_base) = level_one;
  eq_type(glue_base) = glue_ref;
  for (k = glue_base + 1; k <= local_base - 1; k++) eqtb[k] = eqtb[glue_base];
  glue_ref_count(zero_glue) =
      glue_ref_count(zero_glue) + local_base - glue_base;

/*:228*/ /*232:*/

  par_shape_ptr = null;
  eq_type(par_shape_loc) = shape_ref;
  eq_level(par_shape_loc) = level_one;
  for (k = output_routine_loc; k <= toks_base + 255; k++)
    eqtb[k] = eqtb[undefined_control_sequence];
  box(0) = null;
  eq_type(box_base) = box_ref;
  eq_level(box_base) = level_one;
  for (k = box_base + 1; k <= box_base + 255; k++) eqtb[k] = eqtb[box_base];
  cur_font = null_font;
  eq_type(cur_font_loc) = data;
  eq_level(cur_font_loc) = level_one;
  for (k = math_font_base; k <= math_font_base + 47; k++)
    eqtb[k] = eqtb[cur_font_loc];
  equiv(cat_code_base) = 0;
  eq_type(cat_code_base) = data;
  eq_level(cat_code_base) = level_one;
  for (k = cat_code_base + 1; k <= int_base - 1; k++)
    eqtb[k] = eqtb[cat_code_base];
  for (k = 0; k <= 255; k++) {
    cat_code(k) = other_char;
    math_code(k) = hi(k);
    sf_code(k) = 1000;
  }
  cat_code(carriage_return) = car_ret;
  cat_code(' ') = spacer;
  cat_code('\\') = escape;
  cat_code('%') = comment;
  cat_code(invalid_code) = invalid_char;
  cat_code(null_code) = ignore;
  for (k = '0'; k <= '9'; k++) math_code(k) = hi(k + var_code);
  for (k = 'A'; k <= 'Z'; k++) {
    cat_code(k) = letter;
    cat_code(k + 'a' - 'A') = letter;
    math_code(k) = hi(k + var_code + 0x100);
    math_code(k + 'a' - 'A') = hi(k + 'a' - 'A' + var_code + 0x100);
    lc_code(k) = k + 'a' - 'A';
    lc_code(k + 'a' - 'A') = k + 'a' - 'A';
    uc_code(k) = k;
    uc_code(k + 'a' - 'A') = k;
    sf_code(k) = 999;
  }

/*:232*/ /*240:*/

  for (k = int_base; k <= del_code_base - 1; k++) eqtb[k].i = 0;
  mag = 1000;
  tolerance = 10000;
  hang_after = 1;
  max_dead_cycles = 25;
  escape_char = '\\';
  end_line_char = carriage_return;
  for (k = 0; k <= 255; k++) del_code(k) = -1;
  del_code('.') = 0;

/*:240*/ /*250:*/

  for (k = dimen_base; k <= eqtb_size; k++) eqtb[k].sc = 0;

/*:250*/ /*258:*/

  hash_used = frozen_control_sequence;
  cs_count = 0;
  eq_type(frozen_dont_expand) = dont_expand;
  text(frozen_dont_expand) = /*1525:*/
      400
/*:1525*/
      ;

/*:258*/ /*552:*/

  font_ptr = null_font;
  fmem_ptr = 7;
  font_name[null_font] = /*1639:*/
      514
/*:1639*/
      ;
  font_area[null_font] = empty_string;
  hyphen_char[null_font] = '-';
  skew_char[null_font] = -1;
  bchar_label[null_font] = non_address;
  font_bchar[null_font] = non_char;
  font_false_bchar[null_font] = non_char;
  font_bc[null_font] = 1;
  font_ec[null_font] = 0;
  font_size[null_font] = 0;
  font_dsize[null_font] = 0;
  char_base[null_font] = 0;
  width_base[null_font] = 0;
  height_base[null_font] = 0;
  depth_base[null_font] = 0;
  italic_base[null_font] = 0;
  lig_kern_base[null_font] = 0;
  kern_base[null_font] = 0;
  exten_base[null_font] = 0;
  font_glue[null_font] = null;
  font_params[null_font] = 7;
  param_base[null_font] = -1;
  for (k = 0; k <= 6; k++) font_info[k].sc = 0;

/*:552*/ /*946:*/

  for (k = -trie_op_size; k <= trie_op_size; k++) trie_op_hash[k] = 0;
  for (k = 0; k <= 255; k++) trie_used[k] = min_quarterword;
  trie_op_ptr = 0;

/*:946*/ /*951:*/

  trie_not_ready = true;
  trie_root = 0;
  trie_c[0] = si(0);
  trie_ptr = 0;

/*:951*/ /*1216:*/

  text(frozen_protection) = /*1751:*/
      626
/*:1751*/
      ;

/*:1216*/ /*1301:*/

  format_ident = /*1781:*/
      656
/*:1781*/
      ;

/*:1301*/ /*1369:*/

  text(end_write) = /*1791:*/
      666
/*:1791*/
      ;
  eq_level(end_write) = level_one;
  eq_type(end_write) = outer_call;
  equiv(end_write) = null;

/*:1369*/

#endif

/*:8*/
  ;
}
/*57:*/

void print_ln(void) {
  switch (selector) {
    case term_and_log: {
      wterm_cr;
      wlog_cr;
      term_offset = 0;
      file_offset = 0;
    } break;
    case log_only: {
      wlog_cr;
      file_offset = 0;
    } break;
    case term_only: {
      wterm_cr;
      term_offset = 0;
    } break;
    case no_print:
    case pseudo:
    case new_string:
      do_nothing;
      break;
    default:
      write_ln(write_file[selector]);
  }
}

/*:57*/ /*58:*/

void print_char(ASCII_code s) {
  if (/*244:*/
      s == new_line_char

/*:244*/
  )
    if (selector < pseudo) {
      print_ln();
      return;
    }
  switch (selector) {
    case term_and_log: {
      wterm("%c", xchr[s]);
      wlog("%c", xchr[s]);
      incr(term_offset);
      incr(file_offset);
      if (term_offset == max_print_line) {
        wterm_cr;
        term_offset = 0;
      }
      if (file_offset == max_print_line) {
        wlog_cr;
        file_offset = 0;
      }
    } break;
    case log_only: {
      wlog("%c", xchr[s]);
      incr(file_offset);
      if (file_offset == max_print_line) print_ln();
    } break;
    case term_only: {
      wterm("%c", xchr[s]);
      incr(term_offset);
      if (term_offset == max_print_line) print_ln();
    } break;
    case no_print:
      do_nothing;
      break;
    case pseudo:
      if (tally < trick_count) trick_buf[tally % error_line] = s;
      break;
    case new_string: {
      if (pool_ptr < pool_size) append_char(s);
    } break;
    default:
      write(write_file[selector], "%c", xchr[s]);
  }
  incr(tally);
}

/*:58*/ /*59:*/

void print(int s) {
  pool_pointer j;
  int nl;
  if (s >= str_ptr)
    s = /*1381:*/
        256
/*:1381*/
        ;

  else if (s < 256)
    if (s < 0)
      s = /*1381:*/
          256
/*:1381*/
          ;
    else {
      if (selector > pseudo) {
        print_char(s);
        return;
      }
      if ((/*244:*/
           s == new_line_char

/*:244*/
           ))
        if (selector < pseudo) {
          print_ln();
          return;
        }
      nl = new_line_char;
      new_line_char = -1;

      j = str_start[s];
      while (j < str_start[s + 1]) {
        print_char(so(str_pool[j]));
        incr(j);
      }
      new_line_char = nl;
      return;
    }
  j = str_start[s];
  while (j < str_start[s + 1]) {
    print_char(so(str_pool[j]));
    incr(j);
  }
}

void print_str(char *s) {
  while (*s != 0) print_char(*s++);
}

/*:59*/ /*60:*/

void slow_print(int s) {
  pool_pointer j;
  if ((s >= str_ptr) || (s < 256))
    print(s);
  else {
    j = str_start[s];
    while (j < str_start[s + 1]) {
      print(so(str_pool[j]));
      incr(j);
    }
  }
}

/*:60*/ /*62:*/

void print_nl(char *s) {
  if (((term_offset > 0) && (odd(selector))) ||
      ((file_offset > 0) && (selector >= log_only)))
    print_ln();
  print_str(s);
}

/*:62*/ /*63:*/

void print_esc(str_number s) {
  int c;
/*243:*/
  c = escape_char

/*:243*/
      ;
  if (c >= 0)
    if (c < 256) print(c);
  slow_print(s);
}

/*:63*/ /*64:*/

void print_the_digs(eight_bits k)

{
  while (k > 0) {
    decr(k);
    if (dig[k] < 10)
      print_char('0' + dig[k]);
    else
      print_char('A' - 10 + dig[k]);
  }
}

/*:64*/ /*65:*/

void print_int(int n) {
  uint8_t k;
  int m;
  k = 0;
  if (n < 0) {
    print_char('-');
    if (n > -100000000)
      negate(n);
    else {
      m = -1 - n;
      n = m / 10;
      m = (m % 10) + 1;
      k = 1;
      if (m < 10)
        dig[0] = m;
      else {
        dig[0] = 0;
        incr(n);
      }
    }
  }
  do {
    dig[k] = n % 10;
    n = n / 10;
    incr(k);
  } while (!(n == 0));
  print_the_digs(k);
}

/*:65*/ /*262:*/

void print_cs(int p) {
  if (p < hash_base)
    if (p >= single_base)
      if (p == null_cs) {
        print_esc(/*1526:*/
                  401
/*:1526*/
        );
        print_esc(/*1527:*/
                  402
/*:1527*/
        );
        print_char(' ');
      } else {
        print_esc(p - single_base);
        if (cat_code(p - single_base) == letter) print_char(' ');
      }
    else if (p < active_base)
      print_esc(/*1528:*/
                403
/*:1528*/
      );

    else
      print(p - active_base);
  else if (p >= undefined_control_sequence)
    print_esc(/*1528:*/
              403
/*:1528*/
    );
  else if ((text(p) < 0) || (text(p) >= str_ptr))
    print_esc(/*1529:*/
              404
/*:1529*/
    );

  else {
    print_esc(text(p));
    print_char(' ');
  }
}

/*:262*/ /*263:*/

void sprint_cs(pointer p) {
  if (p < hash_base)
    if (p < single_base)
      print(p - active_base);
    else if (p < null_cs)
      print_esc(p - single_base);
    else {
      print_esc(/*1526:*/
                401
/*:1526*/
      );
      print_esc(/*1527:*/
                402
/*:1527*/
      );
    }
  else
    print_esc(text(p));
}

/*:263*/ /*518:*/

void print_file_name(int n, int a, int e) {
  slow_print(a);
  slow_print(n);
  slow_print(e);
}

/*:518*/ /*699:*/

void print_size(int s) {
  if (s == text_size)
    print_esc(/*1438:*/
              313
/*:1438*/
    );
  else if (s == script_size)
    print_esc(/*1439:*/
              314
/*:1439*/
    );
  else
    print_esc(/*1440:*/
              315
/*:1440*/
    );
}

/*:699*/ /*1355:*/

void print_write_whatsit(str_number s, pointer p) {
  print_esc(s);
  if (write_stream(p) < 16)
    print_int(write_stream(p));
  else if (write_stream(p) == 16)
    print_char('*');

  else
    print_char('-');
}

/*:1355*/

/*78:*/

void normalize_selector(void);
void get_token(void);
void term_input(void);
void show_context(void);
void begin_file_reading(void);
void open_log_file(void);
void close_files_and_terminate(void);
void clear_for_error_prompt(void);
void give_err_help(void);
#ifdef DEBUG
void debug_help(void);
#else
#define debug_help() do_nothing
#endif

/*:78*/ /*81:*/

void jump_out(void) {
  close_files_and_terminate();
  exit(0);
}

/*:81*/ /*82:*/

void error(void) {
  ASCII_code c;
  int s1, s2, s3, s4;

  if (history < error_message_issued) history = error_message_issued;
  print_char('.');
  show_context();
  if (interaction == error_stop_mode) /*83:*/

    loop {
    resume:
      if (interaction != error_stop_mode) return;
      clear_for_error_prompt();
      prompt_input("? ");

      if (last == first) return;
      c = buffer[first];
      if (c >= 'a') c = c + 'A' - 'a';
/*84:*/

      switch (c) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
          if (deletions_allowed)
/*88:*/

          {
            s1 = cur_tok;
            s2 = cur_cmd;
            s3 = cur_chr;
            s4 = align_state;
            align_state = 1000000;
            OK_to_interrupt = false;
            if ((last > first + 1) && (buffer[first + 1] >= '0') &&
                (buffer[first + 1] <= '9'))
              c = c * 10 + buffer[first + 1] - '0' * 11;
            else
              c = c - '0';
            while (c > 0) {
              get_token();
              decr(c);
            }
            cur_tok = s1;
            cur_cmd = s2;
            cur_chr = s3;
            align_state = s4;
            OK_to_interrupt = true;
            help2("I have just deleted some text, as you asked.")(
                "You can now delete more, or insert, or whatever.");
            show_context();
            goto resume;
          }

/*:88*/
          break;

#ifdef DEBUG
        case 'D': {
          debug_help();
          goto resume;
        }
#endif
        case 'E':
          if (base_ptr > 0)
            if (input_stack[base_ptr].name_field >= 256) {
              print_nl("You want to edit file ");

              slow_print(input_stack[base_ptr].name_field);
              print_str(" at line ");
              print_int(line);
              interaction = scroll_mode;
              jump_out();
            }
          break;
        case 'H': /*89:*/

        {
          if (use_err_help) {
            give_err_help();
            use_err_help = false;
          } else {
            if (help_ptr == 0)
              help2("Sorry, I don't know how to help in this situation.")(
                  "Maybe you should try asking a human?");
            do {
              decr(help_ptr);
              print_str(help_line[help_ptr]);
              print_ln();
            } while (!(help_ptr == 0));
          }
          help4("Sorry, I already gave what help I could...")(
              "Maybe you should try asking a human?")(
              "An error might have occurred before I noticed any problems.")(
              "``If all else fails, read the instructions.'");
          goto resume;
        }

/*:89*/

        case 'I': /*87:*/

        {
          begin_file_reading();

          if (last > first + 1) {
            loc = first + 1;
            buffer[first] = ' ';
          } else {
            prompt_input("insert>");
            loc = first;
          }
          first = last;
          cur_input.limit_field = last - 1;
          return;
        }

/*:87*/

        case 'Q':
        case 'R':
        case 'S': /*86:*/

        {
          error_count = 0;
          interaction = batch_mode + c - 'Q';
          print_str("OK, entering ");
          switch (c) {
            case 'Q': {
              print_esc(/*1383:*/
                        258
/*:1383*/
              );
              decr(selector);
            } break;
            case 'R':
              print_esc(/*1384:*/
                        259
/*:1384*/
              );
              break;
            case 'S':
              print_esc(/*1385:*/
                        260
/*:1385*/
              );
          }
          print_str("...");
          print_ln();
          update_terminal;
          return;
        }

/*:86*/

        case 'X': {
          interaction = scroll_mode;
          jump_out();
        } break;
        default:
          do_nothing;
      }
/*85:*/

      {
        print_str(
            "Type <return> to proceed, S to scroll future error messages,");

        print_nl("R to run without stopping, Q to run quietly,");
        print_nl("I to insert something, ");
        if (base_ptr > 0)
          if (input_stack[base_ptr].name_field >= 256)
            print_str("E to edit your file,");
        if (deletions_allowed)
          print_nl("1 or ... or 9 to ignore the next 1 to 9 tokens of input,");
        print_nl("H for help, X to quit.");
      }

/*:85*/

/*:84*/
      ;
    }

/*:83*/
    ;
  incr(error_count);
  if (error_count == 100) {
    print_nl("(That makes 100 errors; please try again.)");

    history = fatal_error_stop;
    jump_out();
  }
/*90:*/

  if (interaction > batch_mode) decr(selector);
  if (use_err_help) {
    print_ln();
    give_err_help();
  } else
    while (help_ptr > 0) {
      decr(help_ptr);
      print_nl(help_line[help_ptr]);
    }
  print_ln();
  if (interaction > batch_mode) incr(selector);
  print_ln()

/*:90*/
      ;
}

/*:82*/ /*93:*/

void fatal_error(char *s) {
  normalize_selector();
  print_err("Emergency stop");
  help1(s);
  succumb;
}

/*:93*/ /*94:*/

void overflow(char *s, int n) {
  normalize_selector();
  print_err("TeX capacity exceeded, sorry [");

  print_str(s);
  print_char('=');
  print_int(n);
  print_char(']');
  help2("If you really absolutely need more capacity,")(
      "you can ask a wizard to enlarge me.");
  succumb;
}

/*:94*/ /*95:*/

void confusion(str_number s)

{
  normalize_selector();
  if (history < error_message_issued) {
    print_err("This can't happen (");
    print(s);
    print_char(')');

    help1("I'm broken. Please show this to someone who can fix can fix");
  } else {
    print_err("I can't go on meeting you like this");

    help2("One of your faux pas seems to have wounded me deeply...")(
        "in fact, I'm barely conscious. Please fix it and try again.");
  }
  succumb;
}

/*:95*/

/*:4*/ /*27:*/
bool a_open_in(alpha_file *f)

{
  reset((*f), name_of_file, "r");
  return reset_OK((*f));
}

bool a_open_out(alpha_file *f)

{
  rewrite((*f), name_of_file, "w");
  return rewrite_OK((*f));
}

bool b_open_in(byte_file *f)

{
  reset((*f), name_of_file, "rb");
  return reset_OK((*f));
}

bool b_open_out(byte_file *f)

{
  rewrite((*f), name_of_file, "wb");
  return rewrite_OK((*f));
}

bool w_open_in(word_file *f)

{
  reset((*f), name_of_file, "rb");
  return reset_OK((*f));
}

bool w_open_out(word_file *f)

{
  rewrite((*f), name_of_file, "wb");
  return rewrite_OK((*f));
}

/*:27*/ /*28:*/
void a_close(alpha_file *f) { close((*f)); }

void b_close(byte_file *f) { close((*f)); }

void w_close(word_file *f) { close((*f)); }

/*:28*/ /*31:*/
bool input_ln(alpha_file *f, bool bypass_eoln)

{
  uint16_t last_nonblank;
  if (bypass_eoln)
    if (!eof((*f))) get((*f));

  last = first;
  if (eof((*f)))
    return false;
  else {
    last_nonblank = first;
    while (!eoln((*f))) {
      if (last >= max_buf_stack) {
        max_buf_stack = last + 1;
        if (max_buf_stack == buf_size) /*35:*/

          if (format_ident == 0) {
            write_ln(term_out, "Buffer size exceeded!");
            exit(0);

          } else {
            cur_input.loc_field = first;
            cur_input.limit_field = last - 1;
            overflow("buffer size", buf_size);
          }

/*:35*/
          ;
      }
      buffer[last] = xord[(*f).d];
      get((*f));
      incr(last);
      if (buffer[last - 1] != ' ') last_nonblank = last;
    }
    last = last_nonblank;
    return true;
  }
}

/*:31*/ /*37:*/
bool init_terminal(void) {
  t_open_in;
  loop {
    wake_up_terminal;
    write(term_out, "**");
    update_terminal;

    if (!input_ln(&term_in, true)) {
      write_ln(term_out);
      write(term_out, "! End of file on the terminal... why?");

      return false;
    }
    loc = first;
    while ((loc < last) && (buffer[loc] == ' ')) incr(loc);
    if (loc < last) {
      return true;
    }
    write_ln(term_out, "Please type the name of your input file.");
  }
}

/*:37*/ /*43:*/
str_number make_string(void) {
  if (str_ptr == max_strings)
    overflow("number of strings", max_strings - init_str_ptr);

  incr(str_ptr);
  str_start[str_ptr] = pool_ptr;
  return str_ptr - 1;
}

/*:43*/ /*45:*/
bool str_eq_buf(str_number s, int k)

{
  pool_pointer j;
  bool result;
  j = str_start[s];
  while (j < str_start[s + 1]) {
    if (so(str_pool[j]) != buffer[k]) {
      result = false;
      goto not_found;
    }
    incr(j);
    incr(k);
  }
  result = true;
not_found:
  return result;
}

/*:45*/ /*46:*/
bool str_eq_str(str_number s, str_number t)

{
  pool_pointer j, k;
  bool result;
  result = false;
  if (length(s) != length(t)) goto not_found;
  j = str_start[s];
  k = str_start[t];
  while (j < str_start[s + 1]) {
    if (str_pool[j] != str_pool[k]) goto not_found;
    incr(j);
    incr(k);
  }
  result = true;
not_found:
  return result;
}

/*:46*/ /*47:*/

#ifdef INIT
bool get_strings_started(void)

{
  int k, l;
  uint8_t m, n;
  str_number g;
  int a;
  bool c;
  pool_ptr = 0;
  str_ptr = 0;
  str_start[0] = 0;
/*48:*/

  for (k = 0; k <= 255; k++) {
    if (/*49:*/

        (k < ' ') || (k > '~')

/*:49*/
    ) {
      append_char('^');
      append_char('^');
      if (k < 0100)
        append_char(k + 0100) else if (k < 0200) append_char(k - 0100) else {
          app_lc_hex(k / 16);
          app_lc_hex(k % 16);
        }
    } else
      append_char(k);
    g = make_string();
  }

/*:48*/
  ;
/*51:*/

  {
    int k;
    for (k = 1; k <= file_name_size; k++) name_of_file[k] = pool_name[k - 1];
  }
  if (a_open_in(&pool_file)) {
    c = false;
    do { /*52:*/

      {
        if (eof(pool_file)) bad_pool("! TEX.POOL has no check sum.");

        read(pool_file, m);
        read(pool_file, n);
        if (m == '*') /*53:*/

        {
          a = 0;
          k = 1;
          loop {
            if ((xord[n] < '0') || (xord[n] > '9'))
              bad_pool("! TEX.POOL check sum doesn't have nine digits.");

            a = 10 * a + xord[n] - '0';
            if (k == 9) goto done;
            incr(k);
            read(pool_file, n);
          }
        done:
          if (a != 0) bad_pool("! TEX.POOL doesn't match; TANGLE me again.");

          c = true;
        }
/*:53*/

        else {
          if ((xord[m] < '0') || (xord[m] > '9') || (xord[n] < '0') ||
              (xord[n] > '9'))
            bad_pool("! TEX.POOL line doesn't begin with two digits.");

          l = xord[m] * 10 + xord[n] - '0' * 11;
          if (pool_ptr + l + string_vacancies > pool_size)
            bad_pool("! You have to increase POOLSIZE.");

          for (k = 1; k <= l; k++) {
            if (eoln(pool_file))
              m = ' ';
            else
              read(pool_file, m);
            append_char(xord[m]);
          }
          read_ln(pool_file);
          g = make_string();
        }
      }

/*:52*/
      ;
    } while (!(c));
    a_close(&pool_file);
    return true;
  } else
    bad_pool("! I can't read TEX.POOL.")

/*:51*/
        ;
}
#endif

/*:47*/ /*66:*/
void print_two(int n) {
  n = abs(n) % 100;
  print_char('0' + (n / 10));
  print_char('0' + (n % 10));
}

/*:66*/ /*67:*/
void print_hex(int n)

{
  uint8_t k;
  k = 0;
  print_char('"');
  do {
    dig[k] = n % 16;
    n = n / 16;
    incr(k);
  } while (!(n == 0));
  print_the_digs(k);
}

/*:67*/ /*69:*/
void print_roman_int(int n) {
  pool_pointer j, k;
  nonnegative_integer u, v;
  j = str_start[/*1382:*/
                257
/*:1382*/
  ];
  v = 1000;
  loop {
    while (n >= v) {
      print_char(so(str_pool[j]));
      n = n - v;
    }
    if (n <= 0) return;
    k = j + 2;
    u = v / (so(str_pool[k - 1]) - '0');
    if (str_pool[k - 1] == si('2')) {
      k = k + 2;
      u = u / (so(str_pool[k - 1]) - '0');
    }
    if (n + u >= v) {
      print_char(so(str_pool[k]));
      n = n + u;
    } else {
      j = j + 2;
      v = v / (so(str_pool[j - 1]) - '0');
    }
  }
}

/*:69*/ /*70:*/
void print_current_string(void) {
  pool_pointer j;
  j = str_start[str_ptr];
  while (j < pool_ptr) {
    print_char(so(str_pool[j]));
    incr(j);
  }
}

/*:70*/ /*71:*/
void term_input(void) {
  int k;
  update_terminal;
  if (!input_ln(&term_in, true)) fatal_error("End of file on the terminal!");

  term_offset = 0;
  decr(selector);
  if (last != first)
    for (k = first; k <= last - 1; k++) print(buffer[k]);
  print_ln();
  incr(selector);
}

/*:71*/ /*91:*/
void int_error(int n) {
  print_str(" (");
  print_int(n);
  print_char(')');
  error();
}

/*:91*/ /*92:*/
void normalize_selector(void) {
  if (log_opened)
    selector = term_and_log;
  else
    selector = term_only;
  if (job_name == 0) open_log_file();
  if (interaction == batch_mode) decr(selector);
}

/*:92*/ /*98:*/
void pause_for_instructions(void) {
  if (OK_to_interrupt) {
    interaction = error_stop_mode;
    if ((selector == log_only) || (selector == no_print)) incr(selector);
    print_err("Interruption");

    help3("You rang?")(
        "Try to insert an instruction for me (e.g., `I\\showlists'),")(
        "unless you just want to quit by typing `X'.");
    deletions_allowed = false;
    error();
    deletions_allowed = true;
    interrupt = 0;
  }
}

/*:98*/ /*100:*/
int half(int x) {
  if (odd(x))
    return (x + 1) / 2;
  else
    return x / 2;
}

/*:100*/ /*102:*/
scaled round_decimals(small_number k)

{
  int a;
  a = 0;
  while (k > 0) {
    decr(k);
    a = (a + dig[k] * two) / 10;
  }
  return (a + 1) / 2;
}

/*:102*/ /*103:*/
void print_scaled(scaled s)

{
  scaled delta;
  if (s < 0) {
    print_char('-');
    negate(s);
  }
  print_int(s / unity);
  print_char('.');
  s = 10 * (s % unity) + 5;
  delta = 10;
  do {
    if (delta > unity) s = s + 0100000 - 50000;
    print_char('0' + (s / unity));
    s = 10 * (s % unity);
    delta = delta * 10;
  } while (!(s <= delta));
}

/*:103*/ /*105:*/
scaled mult_and_add(int n, scaled x, scaled y, scaled max_answer) {
  if (n < 0) {
    negate(x);
    negate(n);
  }
  if (n == 0)
    return y;
  else if (((x <= (max_answer - y) / n) && (-x <= (max_answer + y) / n)))
    return n * x + y;
  else {
    arith_error = true;
    return 0;
  }
}

/*:105*/ /*106:*/
scaled x_over_n(scaled x, int n) {
  bool negative;
  scaled x_over_n;
  negative = false;
  if (n == 0) {
    arith_error = true;
    x_over_n = 0;
    rem = x;
  } else {
    if (n < 0) {
      negate(x);
      negate(n);
      negative = true;
    }
    if (x >= 0) {
      x_over_n = x / n;
      rem = x % n;
    } else {
      x_over_n = -((-x) / n);
      rem = -((-x) % n);
    }
  }
  if (negative) negate(rem);
  return x_over_n;
}

/*:106*/ /*107:*/
scaled xn_over_d(scaled x, int n, int d) {
  bool positive;
  nonnegative_integer t, u, v;
  scaled xn_over_d;
  if (x >= 0)
    positive = true;
  else {
    negate(x);
    positive = false;
  }
  t = (x % 0100000) * n;
  u = (x / 0100000) * n + (t / 0100000);
  v = (u % d) * 0100000 + (t % 0100000);
  if (u / d >= 0100000)
    arith_error = true;
  else
    u = 0100000 * (u / d) + (v / d);
  if (positive) {
    xn_over_d = u;
    rem = v % d;
  } else {
    xn_over_d = -u;
    rem = -(v % d);
  }
  return xn_over_d;
}

/*:107*/ /*108:*/
halfword badness(scaled t, scaled s) {
  int r;

  if (t == 0)
    return 0;
  else if (s <= 0)
    return inf_bad;
  else {
    if (t <= 7230584)
      r = (t * 297) / s;
    else if (s >= 1663497)
      r = t / (s / 297);
    else
      r = t;
    if (r > 1290)
      return inf_bad;
    else
      return (r * r * r + 0400000) / 01000000;
  }
}

/*:108*/ /*114:*/

#ifdef DEBUG
void print_word(memory_word w)

{
  print_int(w.i);
  print_char(' ');
  print_scaled(w.sc);
  print_char(' ');
  print_scaled(round(unity * float(w.gr)));
  print_ln();

  print_int(w.hh.lh);
  print_char('=');
  print_int(w.hh.b0);
  print_char(':');
  print_int(w.hh.b1);
  print_char(';');
  print_int(w.hh.rh);
  print_char(' ');
  print_int(w.qqqq.b0);
  print_char(':');
  print_int(w.qqqq.b1);
  print_char(':');
  print_int(w.qqqq.b2);
  print_char(':');
  print_int(w.qqqq.b3);
}
#endif

/*:114*/ /*119:*/
/*292:*/

void show_token_list(int p, int q, int l) {
  int m, c;
  ASCII_code match_chr;
  ASCII_code n;
  match_chr = '#';
  n = '0';
  tally = 0;
  while ((p != null) && (tally < l)) {
    if (p == q) /*320:*/
      set_trick_count

/*:320*/
          ;
/*293:*/

    if ((p < hi_mem_min) || (p > mem_end)) {
      print_esc(/*1386:*/
                261
/*:1386*/
      );
      return;
    }
    if (info(p) >= cs_token_flag)
      print_cs(info(p) - cs_token_flag);
    else {
      m = info(p) / 0400;
      c = info(p) % 0400;
      if (info(p) < 0)
        print_esc(/*1567:*/
                  442
/*:1567*/
        );

      else /*294:*/

        switch (m) {
          case left_brace:
          case right_brace:
          case math_shift:
          case tab_mark:
          case sup_mark:
          case sub_mark:
          case spacer:
          case letter:
          case other_char:
            print(c);
            break;
          case mac_param: {
            print(c);
            print(c);
          } break;
          case out_param: {
            print(match_chr);
            if (c <= 9)
              print_char(c + '0');
            else {
              print_char('!');
              return;
            }
          } break;
          case match: {
            match_chr = c;
            print(c);
            incr(n);
            print_char(n);
            if (n > '9') return;
          } break;
          case end_match:
            print_str("->");
            break;

          default:
            print_esc(/*1567:*/
                      442
/*:1567*/
            );
        }

/*:294*/
        ;
    }

/*:293*/
    ;
    p = link(p);
  }
  if (p != null)
    print_esc(/*1566:*/
              441
/*:1566*/
    );
}

/*:292*/

/*306:*/

void runaway(void) {
  pointer p;
  if (scanner_status > skipping) {
    print_nl("Runaway ");

    switch (scanner_status) {
      case defining: {
        print_str("definition");
        p = def_ref;
      } break;
      case matching: {
        print_str("argument");
        p = temp_head;
      } break;
      case aligning: {
        print_str("preamble");
        p = hold_head;
      } break;
      case absorbing: {
        print_str("text");
        p = def_ref;
      }
    }
    print_char('?');
    print_ln();
    show_token_list(link(p), null, error_line - 10);
  }
}

/*:306*/

/*:119*/ /*120:*/
pointer get_avail(void) {
  pointer p;
  p = avail;
  if (p != null)
    avail = link(avail);
  else if (mem_end < mem_max) {
    incr(mem_end);
    p = mem_end;
  } else {
    decr(hi_mem_min);
    p = hi_mem_min;
    if (hi_mem_min <= lo_mem_max) {
      runaway();
      overflow("main memory size", mem_max + 1 - mem_min);
    }
  }
  link(p) = null;
  incr_dyn_used;
  return p;
}

/*:120*/ /*123:*/
void flush_list(pointer p)

{
  pointer q, r;
  if (p != null) {
    r = p;
    do {
      q = r;
      r = link(r);
      decr_dyn_used;
    } while (!(r == null));
    link(q) = avail;
    avail = p;
  }
}

/*:123*/ /*125:*/
pointer get_node(int s) {
  pointer p;
  pointer q;
  int r;
  int t;
restart:
  p = rover;
  do { /*127:*/

    q = p + node_size(p);

    while (is_empty(q)) {
      t = rlink(q);
      if (q == rover) rover = t;
      llink(t) = llink(q);
      rlink(llink(q)) = t;
      q = q + node_size(q);
    }
    r = q - s;
    if (r > p + 1) /*128:*/

    {
      node_size(p) = r - p;

      rover = p;
      goto found;
    }

/*:128*/
    ;
    if (r == p)
      if (rlink(p) != p)
/*129:*/

      {
        rover = rlink(p);
        t = llink(p);
        llink(rover) = t;
        rlink(t) = rover;
        goto found;
      }

/*:129*/
      ;
    node_size(p) = q - p

/*:127*/
        ;

    p = rlink(p);
  } while (!(p == rover));
  if (s == 010000000000) {
    return max_halfword;
  }
  if (lo_mem_max + 2 < hi_mem_min)
    if (lo_mem_max + 2 <= mem_bot + max_halfword)
/*126:*/

    {
      if (hi_mem_min - lo_mem_max >= 1998)
        t = lo_mem_max + 1000;
      else
        t = lo_mem_max + 1 + (hi_mem_min - lo_mem_max) / 2;

      p = llink(rover);
      q = lo_mem_max;
      rlink(p) = q;
      llink(rover) = q;
      if (t > mem_bot + max_halfword) t = mem_bot + max_halfword;
      rlink(q) = rover;
      llink(q) = p;
      link(q) = empty_flag;
      node_size(q) = t - lo_mem_max;
      lo_mem_max = t;
      link(lo_mem_max) = null;
      info(lo_mem_max) = null;
      rover = q;
      goto restart;
    }

/*:126*/
    ;
  overflow("main memory size", mem_max + 1 - mem_min);

found:
  link(r) = null;
#ifdef STAT
  var_used = var_used + s;
#endif

  return r;
}

/*:125*/ /*130:*/
void free_node(pointer p, halfword s)

{
  pointer q;
  node_size(p) = s;
  link(p) = empty_flag;
  q = llink(rover);
  llink(p) = q;
  rlink(p) = rover;
  llink(rover) = p;
  rlink(q) = p;
#ifdef STAT
  var_used = var_used - s;
#endif
}

/*:130*/ /*131:*/

#ifdef INIT
void sort_avail(void)

{
  pointer p, q, r;
  pointer old_rover;
  p = get_node(010000000000);
  p = rlink(rover);
  rlink(rover) = max_halfword;
  old_rover = rover;
  while (p != old_rover) /*132:*/

    if (p < rover) {
      q = p;
      p = rlink(q);
      rlink(q) = rover;
      rover = q;
    } else {
      q = rover;
      while (rlink(q) < p) q = rlink(q);
      r = rlink(p);
      rlink(p) = rlink(q);
      rlink(q) = p;
      p = r;
    }

/*:132*/
    ;
  p = rover;
  while (rlink(p) != max_halfword) {
    llink(rlink(p)) = p;
    p = rlink(p);
  }
  rlink(p) = rover;
  llink(rover) = p;
}
#endif

/*:131*/ /*136:*/
pointer new_null_box(void) {
  pointer p;
  p = get_node(box_node_size);
  type(p) = hlist_node;
  subtype(p) = min_quarterword;
  width(p) = 0;
  depth(p) = 0;
  height(p) = 0;
  shift_amount(p) = 0;
  list_ptr(p) = null;
  glue_sign(p) = normal;
  glue_order(p) = normal;
  set_glue_ratio_zero(glue_set(p));
  return p;
}

/*:136*/ /*139:*/
pointer new_rule(void) {
  pointer p;
  p = get_node(rule_node_size);
  type(p) = rule_node;
  subtype(p) = 0;
  width(p) = null_flag;
  depth(p) = null_flag;
  height(p) = null_flag;
  return p;
}

/*:139*/ /*144:*/
pointer new_ligature(quarterword f, quarterword c, pointer q) {
  pointer p;
  p = get_node(small_node_size);
  type(p) = ligature_node;
  font(lig_char(p)) = f;
  character(lig_char(p)) = c;
  lig_ptr(p) = q;
  subtype(p) = 0;
  return p;
}

pointer new_lig_item(quarterword c) {
  pointer p;
  p = get_node(small_node_size);
  character(p) = c;
  lig_ptr(p) = null;
  return p;
}

/*:144*/ /*145:*/
pointer new_disc(void) {
  pointer p;
  p = get_node(small_node_size);
  type(p) = disc_node;
  replace_count(p) = 0;
  pre_break(p) = null;
  post_break(p) = null;
  return p;
}

/*:145*/ /*147:*/
pointer new_math(scaled w, small_number s) {
  pointer p;
  p = get_node(small_node_size);
  type(p) = math_node;
  subtype(p) = s;
  width(p) = w;
  return p;
}

/*:147*/ /*151:*/
pointer new_spec(pointer p) {
  pointer q;
  q = get_node(glue_spec_size);
  mem[q] = mem[p];
  glue_ref_count(q) = null;
  width(q) = width(p);
  stretch(q) = stretch(p);
  shrink(q) = shrink(p);
  return q;
}

/*:151*/ /*152:*/
pointer new_param_glue(small_number n) {
  pointer p;
  pointer q;
  p = get_node(small_node_size);
  type(p) = glue_node;
  subtype(p) = n + 1;
  leader_ptr(p) = null;
  q = /*224:*/
      glue_par(n)

/*:224*/
      ;
  glue_ptr(p) = q;
  incr(glue_ref_count(q));
  return p;
}

/*:152*/ /*153:*/
pointer new_glue(pointer q) {
  pointer p;
  p = get_node(small_node_size);
  type(p) = glue_node;
  subtype(p) = normal;
  leader_ptr(p) = null;
  glue_ptr(p) = q;
  incr(glue_ref_count(q));
  return p;
}

/*:153*/ /*154:*/
pointer new_skip_param(small_number n) {
  pointer p;
  temp_ptr = new_spec(/*224:*/
                      glue_par(n)

/*:224*/
  );
  p = new_glue(temp_ptr);
  glue_ref_count(temp_ptr) = null;
  subtype(p) = n + 1;
  return p;
}

/*:154*/ /*156:*/
pointer new_kern(scaled w) {
  pointer p;
  p = get_node(small_node_size);
  type(p) = kern_node;
  subtype(p) = normal;
  width(p) = w;
  return p;
}

/*:156*/ /*158:*/
pointer new_penalty(int m) {
  pointer p;
  p = get_node(small_node_size);
  type(p) = penalty_node;
  subtype(p) = 0;
  penalty(p) = m;
  return p;
}

/*:158*/ /*167:*/

#ifdef DEBUG
void check_mem(bool print_locs) {
  pointer p, q;
  bool clobbered;
  for (p = mem_min; p <= lo_mem_max; p++) is_free[p] = false;

  for (p = hi_mem_min; p <= mem_end; p++) is_free[p] = false;
/*168:*/

  p = avail;
  q = null;
  clobbered = false;
  while (p != null) {
    if ((p > mem_end) || (p < hi_mem_min))
      clobbered = true;
    else if (is_free[p])
      clobbered = true;
    if (clobbered) {
      print_nl("AVAIL list clobbered at ");

      print_int(q);
      goto done1;
    }
    is_free[p] = true;
    q = p;
    p = link(q);
  }
done1:

/*:168*/
    ;
/*169:*/

  p = rover;
  q = null;
  clobbered = false;
  do {
    if ((p >= lo_mem_max) || (p < mem_min))
      clobbered = true;
    else if ((rlink(p) >= lo_mem_max) || (rlink(p) < mem_min))
      clobbered = true;
    else if (!(is_empty(p)) || (node_size(p) < 2) ||
             (p + node_size(p) > lo_mem_max) || (llink(rlink(p)) != p))
      clobbered = true;
    if (clobbered) {
      print_nl("Double-AVAIL list clobbered at ");
      print_int(q);
      goto done2;
    }
    for (q = p; q <= p + node_size(p) - 1; q++) {
      if (is_free[q]) {
        print_nl("Doubly free location at ");

        print_int(q);
        goto done2;
      }
      is_free[q] = true;
    }
    q = p;
    p = rlink(p);
  } while (!(p == rover));
done2:

/*:169*/
    ;
/*170:*/

  p = mem_min;
  while (p <= lo_mem_max) {
    if (is_empty(p)) {
      print_nl("Bad flag at ");
      print_int(p);
    }
    while ((p <= lo_mem_max) && !is_free[p]) incr(p);
    while ((p <= lo_mem_max) && is_free[p]) incr(p);
  }

/*:170*/
  ;
  if (print_locs) /*171:*/

  {
    print_nl("New busy locs:");
    for (p = mem_min; p <= lo_mem_max; p++)
      if (!is_free[p] && ((p > was_lo_max) || was_free[p])) {
        print_char(' ');
        print_int(p);
      }
    for (p = hi_mem_min; p <= mem_end; p++)
      if (!is_free[p] &&
          ((p < was_hi_min) || (p > was_mem_end) || was_free[p])) {
        print_char(' ');
        print_int(p);
      }
  }

/*:171*/
  ;
  for (p = mem_min; p <= lo_mem_max; p++) was_free[p] = is_free[p];
  for (p = hi_mem_min; p <= mem_end; p++) was_free[p] = is_free[p];

  was_mem_end = mem_end;
  was_lo_max = lo_mem_max;
  was_hi_min = hi_mem_min;
}
#endif

/*:167*/ /*172:*/

#ifdef DEBUG
void search_mem(pointer p) {
  int q;
  for (q = mem_min; q <= lo_mem_max; q++) {
    if (link(q) == p) {
      print_nl("LINK(");
      print_int(q);
      print_char(')');
    }
    if (info(q) == p) {
      print_nl("INFO(");
      print_int(q);
      print_char(')');
    }
  }
  for (q = hi_mem_min; q <= mem_end; q++) {
    if (link(q) == p) {
      print_nl("LINK(");
      print_int(q);
      print_char(')');
    }
    if (info(q) == p) {
      print_nl("INFO(");
      print_int(q);
      print_char(')');
    }
  }
/*255:*/

  for (q = active_base; q <= box_base + 255; q++) {
    if (equiv(q) == p) {
      print_nl("EQUIV(");
      print_int(q);
      print_char(')');
    }
  }

/*:255*/
  ;
/*285:*/

  if (save_ptr > 0)
    for (q = 0; q <= save_ptr - 1; q++) {
      if (equiv_field(save_stack[q]) == p) {
        print_nl("SAVE(");
        print_int(q);
        print_char(')');
      }
    }

/*:285*/
    ;
/*933:*/

  for (q = 0; q <= hyph_size; q++) {
    if (hyph_list[q] == p) {
      print_nl("HYPH(");
      print_int(q);
      print_char(')');
    }
  }

/*:933*/
  ;
}
#endif

/*:172*/ /*174:*/
void short_display(int p) {
  int n;
  while (p > mem_min) {
    if (is_char_node(p)) {
      if (p <= mem_end) {
        if (font(p) != font_in_short_display) {
          if ((font(p) < font_base) || (font(p) > font_max))
            print_char('*');

          else /*267:*/

            print_esc(font_id_text(font(p)))

/*:267*/
                ;
          print_char(' ');
          font_in_short_display = font(p);
        }
        print_ASCII(qo(character(p)));
      }
    } else /*175:*/

      switch (type(p)) {
        case hlist_node:
        case vlist_node:
        case ins_node:
        case whatsit_node:
        case mark_node:
        case adjust_node:
        case unset_node:
          print_str("[]");
          break;
        case rule_node:
          print_char('|');
          break;
        case glue_node:
          if (glue_ptr(p) != zero_glue) print_char(' ');
          break;
        case math_node:
          print_char('$');
          break;
        case ligature_node:
          short_display(lig_ptr(p));
          break;
        case disc_node: {
          short_display(pre_break(p));
          short_display(post_break(p));
          n = replace_count(p);
          while (n > 0) {
            if (link(p) != null) p = link(p);
            decr(n);
          }
        } break;
        default:
          do_nothing;
      }

/*:175*/
      ;
    p = link(p);
  }
}

/*:174*/ /*176:*/
void print_font_and_char(int p) {
  if (p > mem_end)
    print_esc(/*1386:*/
              261
/*:1386*/
    );
  else {
    if ((font(p) < font_base) || (font(p) > font_max))
      print_char('*');

    else /*267:*/

      print_esc(font_id_text(font(p)))

/*:267*/
          ;
    print_char(' ');
    print_ASCII(qo(character(p)));
  }
}

void print_mark(int p) {
  print_char('{');
  if ((p < hi_mem_min) || (p > mem_end))
    print_esc(/*1386:*/
              261
/*:1386*/
    );
  else
    show_token_list(link(p), null, max_print_line - 10);
  print_char('}');
}

void print_rule_dimen(scaled d) {
  if (is_running(d))
    print_char('*');
  else
    print_scaled(d);
}

/*:176*/ /*177:*/
void print_glue(scaled d, int order, str_number s)

{
  print_scaled(d);
  if ((order < normal) || (order > filll))
    print_str("foul");
  else if (order > normal) {
    print_str("fil");
    while (order > fil) {
      print_char('l');
      decr(order);
    }
  } else if (s != 0)
    print(s);
}

/*:177*/ /*178:*/
void print_spec(int p, str_number s)

{
  if ((p < mem_min) || (p >= lo_mem_max))
    print_char('*');

  else {
    print_scaled(width(p));
    if (s != 0) print(s);
    if (stretch(p) != 0) {
      print_str(" plus ");
      print_glue(stretch(p), stretch_order(p), s);
    }
    if (shrink(p) != 0) {
      print_str(" minus ");
      print_glue(shrink(p), shrink_order(p), s);
    }
  }
}

/*:178*/ /*179:*/
/*691:*/

void print_fam_and_char(pointer p) {
  print_esc(/*1490:*/
            365
/*:1490*/
  );
  print_int(fam(p));
  print_char(' ');
  print_ASCII(qo(character(p)));
}

void print_delimiter(pointer p) {
  int a;
  a = small_fam(p) * 256 + qo(small_char(p));
  a = a * 0x1000 + large_fam(p) * 256 + qo(large_char(p));
  if (a < 0)
    print_int(a);
  else
    print_hex(a);
}

/*:691*/ /*692:*/

void show_info(void);
void print_subsidiary_data(pointer p, ASCII_code c)

{
  if (cur_length >= depth_threshold) {
    if (math_type(p) != empty) print_str(" []");
  } else {
    append_char(c);
    temp_ptr = p;
    switch (math_type(p)) {
      case math_char: {
        print_ln();
        print_current_string();
        print_fam_and_char(p);
      } break;
      case sub_box:
        show_info();
        break;
      case sub_mlist:
        if (info(p) == null) {
          print_ln();
          print_current_string();
          print_str("{}");
        } else
          show_info();
        break;
      default:
        do_nothing;
    }
    flush_char;
  }
}

/*:692*/ /*694:*/

void print_style(int c) {
  switch (c / 2) {
    case 0:
      print_esc(/*1645:*/
                520
/*:1645*/
      );
      break;
    case 1:
      print_esc(/*1646:*/
                521
/*:1646*/
      );
      break;
    case 2:
      print_esc(/*1647:*/
                522
/*:1647*/
      );
      break;
    case 3:
      print_esc(/*1648:*/
                523
/*:1648*/
      );
      break;
    default:
      print_str("Unknown style!");
  }
}

/*:694*/

/*225:*/

void print_skip_param(int n) {
  switch (n) {
    case line_skip_code:
      print_esc(/*1405:*/
                280
/*:1405*/
      );
      break;
    case baseline_skip_code:
      print_esc(/*1406:*/
                281
/*:1406*/
      );
      break;
    case par_skip_code:
      print_esc(/*1407:*/
                282
/*:1407*/
      );
      break;
    case above_display_skip_code:
      print_esc(/*1408:*/
                283
/*:1408*/
      );
      break;
    case below_display_skip_code:
      print_esc(/*1409:*/
                284
/*:1409*/
      );
      break;
    case above_display_short_skip_code:
      print_esc(/*1410:*/
                285
/*:1410*/
      );
      break;
    case below_display_short_skip_code:
      print_esc(/*1411:*/
                286
/*:1411*/
      );
      break;
    case left_skip_code:
      print_esc(/*1412:*/
                287
/*:1412*/
      );
      break;
    case right_skip_code:
      print_esc(/*1413:*/
                288
/*:1413*/
      );
      break;
    case top_skip_code:
      print_esc(/*1414:*/
                289
/*:1414*/
      );
      break;
    case split_top_skip_code:
      print_esc(/*1415:*/
                290
/*:1415*/
      );
      break;
    case tab_skip_code:
      print_esc(/*1416:*/
                291
/*:1416*/
      );
      break;
    case space_skip_code:
      print_esc(/*1417:*/
                292
/*:1417*/
      );
      break;
    case xspace_skip_code:
      print_esc(/*1418:*/
                293
/*:1418*/
      );
      break;
    case par_fill_skip_code:
      print_esc(/*1419:*/
                294
/*:1419*/
      );
      break;
    case thin_mu_skip_code:
      print_esc(/*1420:*/
                295
/*:1420*/
      );
      break;
    case med_mu_skip_code:
      print_esc(/*1421:*/
                296
/*:1421*/
      );
      break;
    case thick_mu_skip_code:
      print_esc(/*1422:*/
                297
/*:1422*/
      );
      break;
    default:
      print_str("[unknown glue parameter!]");
  }
}

/*:225*/

/*:179*/ /*182:*/
void show_node_list(int p) {
  int n;
  double g;
  if (cur_length > depth_threshold) {
    if (p > null) print_str(" []");

    return;
  }
  n = 0;
  while (p > mem_min) {
    print_ln();
    print_current_string();
    if (p > mem_end) {
      print_str("Bad link, display aborted.");
      return;
    }
    incr(n);
    if (n > breadth_max) {
      print_str("etc.");
      return;
    }
/*183:*/

    if (is_char_node(p))
      print_font_and_char(p);
    else
      switch (type(p)) {
        case hlist_node:
        case vlist_node:
        case unset_node: /*184:*/

        {
          if (type(p) == hlist_node)
            print_esc('h');
          else if (type(p) == vlist_node)
            print_esc('v');
          else
            print_esc(/*1388:*/
                      263
/*:1388*/
            );
          print_str("box(");
          print_scaled(height(p));
          print_char('+');
          print_scaled(depth(p));
          print_str(")x");
          print_scaled(width(p));
          if (type(p) == unset_node)
/*185:*/

          {
            if (span_count(p) != min_quarterword) {
              print_str(" (");
              print_int(qo(span_count(p)) + 1);
              print_str(" columns)");
            }
            if (glue_stretch(p) != 0) {
              print_str(", stretch ");
              print_glue(glue_stretch(p), glue_order(p), 0);
            }
            if (glue_shrink(p) != 0) {
              print_str(", shrink ");
              print_glue(glue_shrink(p), glue_sign(p), 0);
            }
          }

/*:185*/

          else { /*186:*/

            g = float(glue_set(p));
            if ((g != float_constant(0)) && (glue_sign(p) != normal)) {
              print_str(", glue set ");
              if (glue_sign(p) == shrinking) print_str("- ");
              if (abs(mem[p + glue_offset].i) < 04000000)
                print_str("?.?");
              else if (abs(g) > float_constant(20000)) {
                if (g > float_constant(0))
                  print_char('>');
                else
                  print_str("< -");
                print_glue(20000 * unity, glue_order(p), 0);
              } else
                print_glue(round(unity * g), glue_order(p), 0);
            }

/*:186*/
            ;
            if (shift_amount(p) != 0) {
              print_str(", shifted ");
              print_scaled(shift_amount(p));
            }
          }
          node_list_display(list_ptr(p));
        }

/*:184*/
        break;
        case rule_node: /*187:*/

        {
          print_esc(/*1389:*/
                    264
/*:1389*/
          );
          print_rule_dimen(height(p));
          print_char('+');
          print_rule_dimen(depth(p));
          print_str(")x");
          print_rule_dimen(width(p));
        }

/*:187*/
        break;
        case ins_node: /*188:*/

        {
          print_esc(/*1390:*/
                    265
/*:1390*/
          );
          print_int(qo(subtype(p)));
          print_str(", natural size ");
          print_scaled(height(p));
          print_str("; split(");
          print_spec(split_top_ptr(p), 0);
          print_char(',');
          print_scaled(depth(p));
          print_str("); float cost ");
          print_int(float_cost(p));
          node_list_display(ins_ptr(p));
        }

/*:188*/
        break;
        case whatsit_node: /*1356:*/

          switch (subtype(p)) {
            case open_node: {
              print_write_whatsit(/*1783:*/
                                  658
/*:1783*/
                                  ,
                                  p);
              print_char('=');
              print_file_name(open_name(p), open_area(p), open_ext(p));
            } break;
            case write_node: {
              print_write_whatsit(/*1568:*/
                                  443
/*:1568*/
                                  ,
                                  p);
              print_mark(write_tokens(p));
            } break;
            case close_node:
              print_write_whatsit(/*1784:*/
                                  659
/*:1784*/
                                  ,
                                  p);
              break;
            case special_node: {
              print_esc(/*1785:*/
                        660
/*:1785*/
              );
              print_mark(write_tokens(p));
            } break;
            case language_node: {
              print_esc(/*1787:*/
                        662
/*:1787*/
              );
              print_int(what_lang(p));
              print_str(" (hyphenmin ");
              print_int(what_lhm(p));
              print_char(',');
              print_int(what_rhm(p));
              print_char(')');
            } break;
            default:
              print_str("whatsit?");
          }

/*:1356*/
          break;
        case glue_node: /*189:*/

          if (subtype(p) >= a_leaders) /*190:*/

          {
            print_esc(empty_string);
            if (subtype(p) == c_leaders)
              print_char('c');
            else if (subtype(p) == x_leaders)
              print_char('x');
            print_str("leaders ");
            print_spec(glue_ptr(p), 0);
            node_list_display(leader_ptr(p));
          }
/*:190*/

          else {
            print_esc(/*1391:*/
                      266
/*:1391*/
            );
            if (subtype(p) != normal) {
              print_char('(');
              if (subtype(p) < cond_math_glue)
                print_skip_param(subtype(p) - 1);
              else if (subtype(p) == cond_math_glue)
                print_esc(/*1392:*/
                          267
/*:1392*/
                );
              else
                print_esc(/*1393:*/
                          268
/*:1393*/
                );
              print_char(')');
            }
            if (subtype(p) != cond_math_glue) {
              print_char(' ');
              if (subtype(p) < cond_math_glue)
                print_spec(glue_ptr(p), 0);
              else
                print_spec(glue_ptr(p), /*1394:*/
                           269
/*:1394*/
                );
            }
          }

/*:189*/
          break;
        case kern_node: /*191:*/

          if (subtype(p) != mu_glue) {
            print_esc(/*1396:*/
                      271
/*:1396*/
            );
            if (subtype(p) != normal) print_char(' ');
            print_scaled(width(p));
            if (subtype(p) == acc_kern) print_str(" (for accent)");

          } else {
            print_esc(/*1397:*/
                      272
/*:1397*/
            );
            print_scaled(width(p));
            print_str("mu");
          }

/*:191*/
          break;
        case math_node: /*192:*/

        {
          print_esc(/*1398:*/
                    273
/*:1398*/
          );
          if (subtype(p) == before)
            print_str("on");
          else
            print_str("off");
          if (width(p) != 0) {
            print_str(", surrounded ");
            print_scaled(width(p));
          }
        }

/*:192*/
        break;
        case ligature_node: /*193:*/

        {
          print_font_and_char(lig_char(p));
          print_str(" (ligature ");
          if (subtype(p) > 1) print_char('|');
          font_in_short_display = font(lig_char(p));
          short_display(lig_ptr(p));
          if (odd(subtype(p))) print_char('|');
          print_char(')');
        }

/*:193*/
        break;
        case penalty_node: /*194:*/

        {
          print_esc(/*1399:*/
                    274
/*:1399*/
          );
          print_int(penalty(p));
        }

/*:194*/
        break;
        case disc_node: /*195:*/

        {
          print_esc(/*1400:*/
                    275
/*:1400*/
          );
          if (replace_count(p) > 0) {
            print_str(" replacing ");
            print_int(replace_count(p));
          }
          node_list_display(pre_break(p));
          append_char('|');
          show_node_list(post_break(p));
          flush_char;
        }

/*:195*/
        break;
        case mark_node: /*196:*/

        {
          print_esc(/*1401:*/
                    276
/*:1401*/
          );
          print_mark(mark_ptr(p));
        }

/*:196*/
        break;
        case adjust_node: /*197:*/

        {
          print_esc(/*1402:*/
                    277
/*:1402*/
          );
          node_list_display(adjust_ptr(p));
        }

/*:197*/
        break;
/*690:*/

        case style_node:
          print_style(subtype(p));
          break;
        case choice_node: /*695:*/

        {
          print_esc(/*1547:*/
                    422
/*:1547*/
          );
          append_char('D');
          show_node_list(display_mlist(p));
          flush_char;
          append_char('T');
          show_node_list(text_mlist(p));
          flush_char;
          append_char('S');
          show_node_list(script_mlist(p));
          flush_char;
          append_char('s');
          show_node_list(script_script_mlist(p));
          flush_char;
        }

/*:695*/
        break;
        case ord_noad:
        case op_noad:
        case bin_noad:
        case rel_noad:
        case open_noad:
        case close_noad:
        case punct_noad:
        case inner_noad:
        case radical_noad:
        case over_noad:
        case under_noad:
        case vcenter_noad:
        case accent_noad:
        case left_noad:
        case right_noad: /*696:*/

        {
          switch (type(p)) {
            case ord_noad:
              print_esc(/*1649:*/
                        524
/*:1649*/
              );
              break;
            case op_noad:
              print_esc(/*1650:*/
                        525
/*:1650*/
              );
              break;
            case bin_noad:
              print_esc(/*1651:*/
                        526
/*:1651*/
              );
              break;
            case rel_noad:
              print_esc(/*1652:*/
                        527
/*:1652*/
              );
              break;
            case open_noad:
              print_esc(/*1653:*/
                        528
/*:1653*/
              );
              break;
            case close_noad:
              print_esc(/*1654:*/
                        529
/*:1654*/
              );
              break;
            case punct_noad:
              print_esc(/*1655:*/
                        530
/*:1655*/
              );
              break;
            case inner_noad:
              print_esc(/*1656:*/
                        531
/*:1656*/
              );
              break;
            case over_noad:
              print_esc(/*1657:*/
                        532
/*:1657*/
              );
              break;
            case under_noad:
              print_esc(/*1658:*/
                        533
/*:1658*/
              );
              break;
            case vcenter_noad:
              print_esc(/*1561:*/
                        436
/*:1561*/
              );
              break;
            case radical_noad: {
              print_esc(/*1555:*/
                        430
/*:1555*/
              );
              print_delimiter(left_delimiter(p));
            } break;
            case accent_noad: {
              print_esc(/*1530:*/
                        405
/*:1530*/
              );
              print_fam_and_char(accent_chr(p));
            } break;
            case left_noad: {
              print_esc(/*1659:*/
                        534
/*:1659*/
              );
              print_delimiter(delimiter(p));
            } break;
            case right_noad: {
              print_esc(/*1660:*/
                        535
/*:1660*/
              );
              print_delimiter(delimiter(p));
            }
          }
          if (subtype(p) != normal)
            if (subtype(p) == limits)
              print_esc(/*1661:*/
                        536
/*:1661*/
              );
            else
              print_esc(/*1662:*/
                        537
/*:1662*/
              );
          if (type(p) < left_noad) print_subsidiary_data(nucleus(p), '.');
          print_subsidiary_data(supscr(p), '^');
          print_subsidiary_data(subscr(p), '_');
        }

/*:696*/
        break;
        case fraction_noad: /*697:*/

        {
          print_esc(/*1663:*/
                    538
/*:1663*/
          );
          if (thickness(p) == default_code)
            print_str("= default");
          else
            print_scaled(thickness(p));
          if ((small_fam(left_delimiter(p)) != 0) ||
              (small_char(left_delimiter(p)) != min_quarterword) ||
              (large_fam(left_delimiter(p)) != 0) ||
              (large_char(left_delimiter(p)) != min_quarterword)) {
            print_str(", left-delimiter ");
            print_delimiter(left_delimiter(p));
          }
          if ((small_fam(right_delimiter(p)) != 0) ||
              (small_char(right_delimiter(p)) != min_quarterword) ||
              (large_fam(right_delimiter(p)) != 0) ||
              (large_char(right_delimiter(p)) != min_quarterword)) {
            print_str(", right-delimiter ");
            print_delimiter(right_delimiter(p));
          }
          print_subsidiary_data(numerator(p), '\\');
          print_subsidiary_data(denominator(p), '/');
        }

/*:697*/
        break;

/*:690*/

        default:
          print_str("Unknown node type!");
      }

/*:183*/
      ;
    p = link(p);
  }
}

/*:182*/ /*198:*/
void show_box(pointer p) { /*236:*/

  depth_threshold = show_box_depth;
  breadth_max = show_box_breadth

/*:236*/
      ;
  if (breadth_max <= 0) breadth_max = 5;
  if (pool_ptr + depth_threshold >= pool_size)
    depth_threshold = pool_size - pool_ptr - 1;

  show_node_list(p);
  print_ln();
}

/*:198*/ /*200:*/
void delete_token_ref(pointer p)

{
  if (token_ref_count(p) == null)
    flush_list(p);
  else
    decr(token_ref_count(p));
}

/*:200*/ /*201:*/
void delete_glue_ref(pointer p) fast_delete_glue_ref(p)
/*:201*/ /*202:*/
    void flush_node_list(pointer p) {
  pointer q;
  while (p != null)

  {
    q = link(p);
    if (is_char_node(p)) free_avail(p) else {
        switch (type(p)) {
          case hlist_node:
          case vlist_node:
          case unset_node: {
            flush_node_list(list_ptr(p));
            free_node(p, box_node_size);
            goto done;
          }
          case rule_node: {
            free_node(p, rule_node_size);
            goto done;
          }
          case ins_node: {
            flush_node_list(ins_ptr(p));
            delete_glue_ref(split_top_ptr(p));
            free_node(p, ins_node_size);
            goto done;
          }
          case whatsit_node: /*1358:*/

          {
            switch (subtype(p)) {
              case open_node:
                free_node(p, open_node_size);
                break;
              case write_node:
              case special_node: {
                delete_token_ref(write_tokens(p));
                free_node(p, write_node_size);
                goto done;
              }
              case close_node:
              case language_node:
                free_node(p, small_node_size);
                break;
              default:
                confusion(/*1790:*/
                          665
/*:1790*/
                );
            }
            goto done;
          }

/*:1358*/

          case glue_node: {
            fast_delete_glue_ref(glue_ptr(p));
            if (leader_ptr(p) != null) flush_node_list(leader_ptr(p));
          } break;
          case kern_node:
          case math_node:
          case penalty_node:
            do_nothing;
            break;
          case ligature_node:
            flush_node_list(lig_ptr(p));
            break;
          case mark_node:
            delete_token_ref(mark_ptr(p));
            break;
          case disc_node: {
            flush_node_list(pre_break(p));
            flush_node_list(post_break(p));
          } break;
          case adjust_node:
            flush_node_list(adjust_ptr(p));
            break;
/*698:*/

          case style_node: {
            free_node(p, style_node_size);
            goto done;
          }
          case choice_node: {
            flush_node_list(display_mlist(p));
            flush_node_list(text_mlist(p));
            flush_node_list(script_mlist(p));
            flush_node_list(script_script_mlist(p));
            free_node(p, style_node_size);
            goto done;
          }
          case ord_noad:
          case op_noad:
          case bin_noad:
          case rel_noad:
          case open_noad:
          case close_noad:
          case punct_noad:
          case inner_noad:
          case radical_noad:
          case over_noad:
          case under_noad:
          case vcenter_noad:
          case accent_noad: {
            if (math_type(nucleus(p)) >= sub_box)
              flush_node_list(info(nucleus(p)));
            if (math_type(supscr(p)) >= sub_box)
              flush_node_list(info(supscr(p)));
            if (math_type(subscr(p)) >= sub_box)
              flush_node_list(info(subscr(p)));
            if (type(p) == radical_noad)
              free_node(p, radical_noad_size);
            else if (type(p) == accent_noad)
              free_node(p, accent_noad_size);
            else
              free_node(p, noad_size);
            goto done;
          }
          case left_noad:
          case right_noad: {
            free_node(p, noad_size);
            goto done;
          }
          case fraction_noad: {
            flush_node_list(info(numerator(p)));
            flush_node_list(info(denominator(p)));
            free_node(p, fraction_noad_size);
            goto done;
          }

/*:698*/

          default:
            confusion(/*1403:*/
                      278
/*:1403*/
            );
        }
        free_node(p, small_node_size);
      done:;
      }
    p = q;
  }
}

/*:202*/ /*204:*/
pointer copy_node_list(pointer p)

{
  pointer h;
  pointer q;
  pointer r;
  uint8_t words;
  h = get_avail();
  q = h;
  while (p != null) { /*205:*/

    words = 1;
    if (is_char_node(p))
      r = get_avail();
    else /*206:*/

      switch (type(p)) {
        case hlist_node:
        case vlist_node:
        case unset_node: {
          r = get_node(box_node_size);
          mem[r + 6] = mem[p + 6];
          mem[r + 5] = mem[p + 5];
          list_ptr(r) = copy_node_list(list_ptr(p));
          words = 5;
        } break;
        case rule_node: {
          r = get_node(rule_node_size);
          words = rule_node_size;
        } break;
        case ins_node: {
          r = get_node(ins_node_size);
          mem[r + 4] = mem[p + 4];
          add_glue_ref(split_top_ptr(p));
          ins_ptr(r) = copy_node_list(ins_ptr(p));
          words = ins_node_size - 1;
        } break;
        case whatsit_node: /*1357:*/

          switch (subtype(p)) {
            case open_node: {
              r = get_node(open_node_size);
              words = open_node_size;
            } break;
            case write_node:
            case special_node: {
              r = get_node(write_node_size);
              add_token_ref(write_tokens(p));
              words = write_node_size;
            } break;
            case close_node:
            case language_node: {
              r = get_node(small_node_size);
              words = small_node_size;
            } break;
            default:
              confusion(/*1789:*/
                        664
/*:1789*/
              );
          }

/*:1357*/
          break;
        case glue_node: {
          r = get_node(small_node_size);
          add_glue_ref(glue_ptr(p));
          glue_ptr(r) = glue_ptr(p);
          leader_ptr(r) = copy_node_list(leader_ptr(p));
        } break;
        case kern_node:
        case math_node:
        case penalty_node: {
          r = get_node(small_node_size);
          words = small_node_size;
        } break;
        case ligature_node: {
          r = get_node(small_node_size);
          mem[lig_char(r)] = mem[lig_char(p)];
          lig_ptr(r) = copy_node_list(lig_ptr(p));
        } break;
        case disc_node: {
          r = get_node(small_node_size);
          pre_break(r) = copy_node_list(pre_break(p));
          post_break(r) = copy_node_list(post_break(p));
        } break;
        case mark_node: {
          r = get_node(small_node_size);
          add_token_ref(mark_ptr(p));
          words = small_node_size;
        } break;
        case adjust_node: {
          r = get_node(small_node_size);
          adjust_ptr(r) = copy_node_list(adjust_ptr(p));
        } break;
        default:
          confusion(/*1404:*/
                    279
/*:1404*/
          );
      }

/*:206*/
      ;
    while (words > 0) {
      decr(words);
      mem[r + words] = mem[p + words];
    }

/*:205*/
    ;
    link(q) = r;
    q = r;
    p = link(p);
  }
  link(q) = null;
  q = link(h);
  free_avail(h);
  return q;
}

/*:204*/ /*211:*/
void print_mode(int m) {
  if (m > 0) switch (m / (max_command + 1)) {
      case 0:
        print_str("vertical");
        break;
      case 1:
        print_str("horizontal");
        break;
      case 2:
        print_str("display math");
    }
  else if (m == 0)
    print_str("no");
  else
    switch ((-m) / (max_command + 1)) {
      case 0:
        print_str("internal vertical");
        break;
      case 1:
        print_str("restricted horizontal");
        break;
      case 2:
        print_str("math");
    }
  print_str(" mode");
}

/*:211*/ /*216:*/
void push_nest(void) {
  if (nest_ptr > max_nest_stack) {
    max_nest_stack = nest_ptr;
    if (nest_ptr == nest_size) overflow("semantic nest size", nest_size);
  }
  nest[nest_ptr] = cur_list;
  incr(nest_ptr);
  head = get_avail();
  tail = head;
  prev_graf = 0;
  mode_line = line;
}

/*:216*/ /*217:*/
void pop_nest(void) {
  free_avail(head);
  decr(nest_ptr);
  cur_list = nest[nest_ptr];
}

/*:217*/ /*218:*/
void print_totals(void);
void show_activities(void) {
  int p;
  int16_t m;
  memory_word a;
  pointer q, r;
  int t;
  nest[nest_ptr] = cur_list;
  print_nl("");
  print_ln();
  for (p = nest_ptr; p >= 0; p--) {
    m = nest[p].mode_field;
    a = nest[p].aux_field;
    print_nl("### ");
    print_mode(m);
    print_str(" entered at line ");
    print_int(abs(nest[p].ml_field));
    if (m == hmode)
      if (nest[p].pg_field != 040600000) {
        print_str(" (language");
        print_int(nest[p].pg_field % 0200000);
        print_str(":hyphenmin");
        print_int(nest[p].pg_field / 020000000);
        print_char(',');
        print_int((nest[p].pg_field / 0200000) % 0100);
        print_char(')');
      }
    if (nest[p].ml_field < 0) print_str(" (\\output routine)");
    if (p == 0) { /*986:*/

      if (page_head != page_tail) {
        print_nl("### current page:");
        if (output_active) print_str(" (held over for next output)");

        show_box(link(page_head));
        if (page_contents > empty) {
          print_nl("total height ");
          print_totals();

          print_nl(" goal height ");
          print_scaled(page_goal);

          r = link(page_ins_head);
          while (r != page_ins_head) {
            print_ln();
            print_esc(/*1390:*/
                      265
/*:1390*/
            );
            t = qo(subtype(r));
            print_int(t);
            print_str(" adds ");
            if (count(t) == 1000)
              t = height(r);
            else
              t = x_over_n(height(r), 1000) * count(t);
            print_scaled(t);
            if (type(r) == split_up) {
              q = page_head;
              t = 0;
              do {
                q = link(q);
                if ((type(q) == ins_node) && (subtype(q) == subtype(r)))
                  incr(t);
              } while (!(q == broken_ins(r)));
              print_str(", #");
              print_int(t);
              print_str(" might split");
            }
            r = link(r);
          }
        }
      }

/*:986*/
      ;
      if (link(contrib_head) != null) print_nl("### recent contributions:");
    }
    show_box(link(nest[p].head_field));
/*219:*/

    switch (abs(m) / (max_command + 1)) {
      case 0: {
        print_nl("prevdepth ");
        if (a.sc <= ignore_depth)
          print_str("ignored");
        else
          print_scaled(a.sc);
        if (nest[p].pg_field != 0) {
          print_str(", prevgraf ");
          print_int(nest[p].pg_field);
          print_str(" line");
          if (nest[p].pg_field != 1) print_char('s');
        }
      } break;
      case 1: {
        print_nl("spacefactor ");
        print_int(a.hh.lh);
        if (m > 0)
          if (a.hh.rh > 0) {
            print_str(", current language ");
            print_int(a.hh.rh);
          }
      } break;
      case 2:
        if (a.i != null) {
          print_str("this will begin denominator of:");
          show_box(a.i);
        }
    }

/*:219*/
    ;
  }
}

/*:218*/ /*237:*/
void print_param(int n) {
  switch (n) {
    case pretolerance_code:
      print_esc(/*1446:*/
                321
/*:1446*/
      );
      break;
    case tolerance_code:
      print_esc(/*1447:*/
                322
/*:1447*/
      );
      break;
    case line_penalty_code:
      print_esc(/*1448:*/
                323
/*:1448*/
      );
      break;
    case hyphen_penalty_code:
      print_esc(/*1449:*/
                324
/*:1449*/
      );
      break;
    case ex_hyphen_penalty_code:
      print_esc(/*1450:*/
                325
/*:1450*/
      );
      break;
    case club_penalty_code:
      print_esc(/*1451:*/
                326
/*:1451*/
      );
      break;
    case widow_penalty_code:
      print_esc(/*1452:*/
                327
/*:1452*/
      );
      break;
    case display_widow_penalty_code:
      print_esc(/*1453:*/
                328
/*:1453*/
      );
      break;
    case broken_penalty_code:
      print_esc(/*1454:*/
                329
/*:1454*/
      );
      break;
    case bin_op_penalty_code:
      print_esc(/*1455:*/
                330
/*:1455*/
      );
      break;
    case rel_penalty_code:
      print_esc(/*1456:*/
                331
/*:1456*/
      );
      break;
    case pre_display_penalty_code:
      print_esc(/*1457:*/
                332
/*:1457*/
      );
      break;
    case post_display_penalty_code:
      print_esc(/*1458:*/
                333
/*:1458*/
      );
      break;
    case inter_line_penalty_code:
      print_esc(/*1459:*/
                334
/*:1459*/
      );
      break;
    case double_hyphen_demerits_code:
      print_esc(/*1460:*/
                335
/*:1460*/
      );
      break;
    case final_hyphen_demerits_code:
      print_esc(/*1461:*/
                336
/*:1461*/
      );
      break;
    case adj_demerits_code:
      print_esc(/*1462:*/
                337
/*:1462*/
      );
      break;
    case mag_code:
      print_esc(/*1463:*/
                338
/*:1463*/
      );
      break;
    case delimiter_factor_code:
      print_esc(/*1464:*/
                339
/*:1464*/
      );
      break;
    case looseness_code:
      print_esc(/*1465:*/
                340
/*:1465*/
      );
      break;
    case time_code:
      print_esc(/*1466:*/
                341
/*:1466*/
      );
      break;
    case day_code:
      print_esc(/*1467:*/
                342
/*:1467*/
      );
      break;
    case month_code:
      print_esc(/*1468:*/
                343
/*:1468*/
      );
      break;
    case year_code:
      print_esc(/*1469:*/
                344
/*:1469*/
      );
      break;
    case show_box_breadth_code:
      print_esc(/*1470:*/
                345
/*:1470*/
      );
      break;
    case show_box_depth_code:
      print_esc(/*1471:*/
                346
/*:1471*/
      );
      break;
    case hbadness_code:
      print_esc(/*1472:*/
                347
/*:1472*/
      );
      break;
    case vbadness_code:
      print_esc(/*1473:*/
                348
/*:1473*/
      );
      break;
    case pausing_code:
      print_esc(/*1474:*/
                349
/*:1474*/
      );
      break;
    case tracing_online_code:
      print_esc(/*1475:*/
                350
/*:1475*/
      );
      break;
    case tracing_macros_code:
      print_esc(/*1476:*/
                351
/*:1476*/
      );
      break;
    case tracing_stats_code:
      print_esc(/*1477:*/
                352
/*:1477*/
      );
      break;
    case tracing_paragraphs_code:
      print_esc(/*1478:*/
                353
/*:1478*/
      );
      break;
    case tracing_pages_code:
      print_esc(/*1479:*/
                354
/*:1479*/
      );
      break;
    case tracing_output_code:
      print_esc(/*1480:*/
                355
/*:1480*/
      );
      break;
    case tracing_lost_chars_code:
      print_esc(/*1481:*/
                356
/*:1481*/
      );
      break;
    case tracing_commands_code:
      print_esc(/*1482:*/
                357
/*:1482*/
      );
      break;
    case tracing_restores_code:
      print_esc(/*1483:*/
                358
/*:1483*/
      );
      break;
    case uc_hyph_code:
      print_esc(/*1484:*/
                359
/*:1484*/
      );
      break;
    case output_penalty_code:
      print_esc(/*1485:*/
                360
/*:1485*/
      );
      break;
    case max_dead_cycles_code:
      print_esc(/*1486:*/
                361
/*:1486*/
      );
      break;
    case hang_after_code:
      print_esc(/*1487:*/
                362
/*:1487*/
      );
      break;
    case floating_penalty_code:
      print_esc(/*1488:*/
                363
/*:1488*/
      );
      break;
    case global_defs_code:
      print_esc(/*1489:*/
                364
/*:1489*/
      );
      break;
    case cur_fam_code:
      print_esc(/*1490:*/
                365
/*:1490*/
      );
      break;
    case escape_char_code:
      print_esc(/*1491:*/
                366
/*:1491*/
      );
      break;
    case default_hyphen_char_code:
      print_esc(/*1492:*/
                367
/*:1492*/
      );
      break;
    case default_skew_char_code:
      print_esc(/*1493:*/
                368
/*:1493*/
      );
      break;
    case end_line_char_code:
      print_esc(/*1494:*/
                369
/*:1494*/
      );
      break;
    case new_line_char_code:
      print_esc(/*1495:*/
                370
/*:1495*/
      );
      break;
    case language_code:
      print_esc(/*1496:*/
                371
/*:1496*/
      );
      break;
    case left_hyphen_min_code:
      print_esc(/*1497:*/
                372
/*:1497*/
      );
      break;
    case right_hyphen_min_code:
      print_esc(/*1498:*/
                373
/*:1498*/
      );
      break;
    case holding_inserts_code:
      print_esc(/*1499:*/
                374
/*:1499*/
      );
      break;
    case error_context_lines_code:
      print_esc(/*1500:*/
                375
/*:1500*/
      );
      break;
    default:
      print_str("[unknown integer parameter!]");
  }
}

/*:237*/ /*241:*/
void fix_date_and_time(void) {
  sys_time = 12 * 60;
  sys_day = 4;
  sys_month = 7;
  sys_year = 1776;
  time = sys_time;
  day = sys_day;
  month = sys_month;
  year = sys_year;
}

/*:241*/ /*245:*/
void begin_diagnostic(void) {
  old_setting = selector;
  if ((tracing_online <= 0) && (selector == term_and_log)) {
    decr(selector);
    if (history == spotless) history = warning_issued;
  }
}

void end_diagnostic(bool blank_line)

{
  print_nl("");
  if (blank_line) print_ln();
  selector = old_setting;
}

/*:245*/ /*247:*/
void print_length_param(int n) {
  switch (n) {
    case par_indent_code:
      print_esc(/*1503:*/
                378
/*:1503*/
      );
      break;
    case math_surround_code:
      print_esc(/*1504:*/
                379
/*:1504*/
      );
      break;
    case line_skip_limit_code:
      print_esc(/*1505:*/
                380
/*:1505*/
      );
      break;
    case hsize_code:
      print_esc(/*1506:*/
                381
/*:1506*/
      );
      break;
    case vsize_code:
      print_esc(/*1507:*/
                382
/*:1507*/
      );
      break;
    case max_depth_code:
      print_esc(/*1508:*/
                383
/*:1508*/
      );
      break;
    case split_max_depth_code:
      print_esc(/*1509:*/
                384
/*:1509*/
      );
      break;
    case box_max_depth_code:
      print_esc(/*1510:*/
                385
/*:1510*/
      );
      break;
    case hfuzz_code:
      print_esc(/*1511:*/
                386
/*:1511*/
      );
      break;
    case vfuzz_code:
      print_esc(/*1512:*/
                387
/*:1512*/
      );
      break;
    case delimiter_shortfall_code:
      print_esc(/*1513:*/
                388
/*:1513*/
      );
      break;
    case null_delimiter_space_code:
      print_esc(/*1514:*/
                389
/*:1514*/
      );
      break;
    case script_space_code:
      print_esc(/*1515:*/
                390
/*:1515*/
      );
      break;
    case pre_display_size_code:
      print_esc(/*1516:*/
                391
/*:1516*/
      );
      break;
    case display_width_code:
      print_esc(/*1517:*/
                392
/*:1517*/
      );
      break;
    case display_indent_code:
      print_esc(/*1518:*/
                393
/*:1518*/
      );
      break;
    case overfull_rule_code:
      print_esc(/*1519:*/
                394
/*:1519*/
      );
      break;
    case hang_indent_code:
      print_esc(/*1520:*/
                395
/*:1520*/
      );
      break;
    case h_offset_code:
      print_esc(/*1521:*/
                396
/*:1521*/
      );
      break;
    case v_offset_code:
      print_esc(/*1522:*/
                397
/*:1522*/
      );
      break;
    case emergency_stretch_code:
      print_esc(/*1523:*/
                398
/*:1523*/
      );
      break;
    default:
      print_str("[unknown dimen parameter!]");
  }
}

/*:247*/ /*252:*/
/*298:*/

void print_cmd_chr(quarterword cmd, halfword chr_code) {
  switch (cmd) {
    case left_brace:
      chr_cmd("begin-group character ") break;
    case right_brace:
      chr_cmd("end-group character ") break;
    case math_shift:
      chr_cmd("math shift character ") break;
    case mac_param:
      chr_cmd("macro parameter character ") break;
    case sup_mark:
      chr_cmd("superscript character ") break;
    case sub_mark:
      chr_cmd("subscript character ") break;
    case endv:
      print_str("end of alignment template");
      break;
    case spacer:
      chr_cmd("blank space ") break;
    case letter:
      chr_cmd("the letter ") break;
    case other_char:
      chr_cmd("the character ") break;
/*227:*/

    case assign_glue:
    case assign_mu_glue:
      if (chr_code < skip_base)
        print_skip_param(chr_code - glue_base);
      else if (chr_code < mu_skip_base) {
        print_esc(/*1423:*/
                  298
/*:1423*/
        );
        print_int(chr_code - skip_base);
      } else {
        print_esc(/*1424:*/
                  299
/*:1424*/
        );
        print_int(chr_code - mu_skip_base);
      }
      break;

/*:227*/ /*231:*/

    case assign_toks:
      if (chr_code >= toks_base) {
        print_esc(/*1435:*/
                  310
/*:1435*/
        );
        print_int(chr_code - toks_base);
      } else
        switch (chr_code) {
          case output_routine_loc:
            print_esc(/*1426:*/
                      301
/*:1426*/
            );
            break;
          case every_par_loc:
            print_esc(/*1427:*/
                      302
/*:1427*/
            );
            break;
          case every_math_loc:
            print_esc(/*1428:*/
                      303
/*:1428*/
            );
            break;
          case every_display_loc:
            print_esc(/*1429:*/
                      304
/*:1429*/
            );
            break;
          case every_hbox_loc:
            print_esc(/*1430:*/
                      305
/*:1430*/
            );
            break;
          case every_vbox_loc:
            print_esc(/*1431:*/
                      306
/*:1431*/
            );
            break;
          case every_job_loc:
            print_esc(/*1432:*/
                      307
/*:1432*/
            );
            break;
          case every_cr_loc:
            print_esc(/*1433:*/
                      308
/*:1433*/
            );
            break;
          default:
            print_esc(/*1434:*/
                      309
/*:1434*/
            );
        }
      break;

/*:231*/ /*239:*/

    case assign_int:
      if (chr_code < count_base)
        print_param(chr_code - int_base);
      else {
        print_esc(/*1501:*/
                  376
/*:1501*/
        );
        print_int(chr_code - count_base);
      }
      break;

/*:239*/ /*249:*/

    case assign_dimen:
      if (chr_code < scaled_base)
        print_length_param(chr_code - dimen_base);
      else {
        print_esc(/*1524:*/
                  399
/*:1524*/
        );
        print_int(chr_code - scaled_base);
      }
      break;

/*:249*/ /*266:*/

    case accent:
      print_esc(/*1530:*/
                405
/*:1530*/
      );
      break;
    case advance:
      print_esc(/*1531:*/
                406
/*:1531*/
      );
      break;
    case after_assignment:
      print_esc(/*1532:*/
                407
/*:1532*/
      );
      break;
    case after_group:
      print_esc(/*1533:*/
                408
/*:1533*/
      );
      break;
    case assign_font_dimen:
      print_esc(/*1541:*/
                416
/*:1541*/
      );
      break;
    case begin_group:
      print_esc(/*1534:*/
                409
/*:1534*/
      );
      break;
    case break_penalty:
      print_esc(/*1553:*/
                428
/*:1553*/
      );
      break;
    case char_num:
      print_esc(/*1535:*/
                410
/*:1535*/
      );
      break;
    case cs_name:
      print_esc(/*1526:*/
                401
/*:1526*/
      );
      break;
    case def_font:
      print_esc(/*1540:*/
                415
/*:1540*/
      );
      break;
    case delim_num:
      print_esc(/*1536:*/
                411
/*:1536*/
      );
      break;
    case divide:
      print_esc(/*1537:*/
                412
/*:1537*/
      );
      break;
    case end_cs_name:
      print_esc(/*1527:*/
                402
/*:1527*/
      );
      break;
    case end_group:
      print_esc(/*1538:*/
                413
/*:1538*/
      );
      break;
    case ex_space:
      print_esc(' ');
      break;
    case expand_after:
      print_esc(/*1539:*/
                414
/*:1539*/
      );
      break;
    case halign:
      print_esc(/*1542:*/
                417
/*:1542*/
      );
      break;
    case hrule:
      print_esc(/*1543:*/
                418
/*:1543*/
      );
      break;
    case ignore_spaces:
      print_esc(/*1544:*/
                419
/*:1544*/
      );
      break;
    case insert:
      print_esc(/*1390:*/
                265
/*:1390*/
      );
      break;
    case ital_corr:
      print_esc('/');
      break;
    case mark:
      print_esc(/*1401:*/
                276
/*:1401*/
      );
      break;
    case math_accent:
      print_esc(/*1545:*/
                420
/*:1545*/
      );
      break;
    case math_char_num:
      print_esc(/*1546:*/
                421
/*:1546*/
      );
      break;
    case math_choice:
      print_esc(/*1547:*/
                422
/*:1547*/
      );
      break;
    case multiply:
      print_esc(/*1548:*/
                423
/*:1548*/
      );
      break;
    case no_align:
      print_esc(/*1549:*/
                424
/*:1549*/
      );
      break;
    case no_boundary:
      print_esc(/*1550:*/
                425
/*:1550*/
      );
      break;
    case no_expand:
      print_esc(/*1551:*/
                426
/*:1551*/
      );
      break;
    case non_script:
      print_esc(/*1392:*/
                267
/*:1392*/
      );
      break;
    case omit:
      print_esc(/*1552:*/
                427
/*:1552*/
      );
      break;
    case radical:
      print_esc(/*1555:*/
                430
/*:1555*/
      );
      break;
    case read_to_cs:
      print_esc(/*1556:*/
                431
/*:1556*/
      );
      break;
    case relax:
      print_esc(/*1557:*/
                432
/*:1557*/
      );
      break;
    case set_box:
      print_esc(/*1558:*/
                433
/*:1558*/
      );
      break;
    case set_prev_graf:
      print_esc(/*1554:*/
                429
/*:1554*/
      );
      break;
    case set_shape:
      print_esc(/*1436:*/
                311
/*:1436*/
      );
      break;
    case the:
      print_esc(/*1559:*/
                434
/*:1559*/
      );
      break;
    case toks_register:
      print_esc(/*1435:*/
                310
/*:1435*/
      );
      break;
    case vadjust:
      print_esc(/*1402:*/
                277
/*:1402*/
      );
      break;
    case valign:
      print_esc(/*1560:*/
                435
/*:1560*/
      );
      break;
    case vcenter:
      print_esc(/*1561:*/
                436
/*:1561*/
      );
      break;
    case vrule:
      print_esc(/*1562:*/
                437
/*:1562*/
      );
      break;

/*:266*/ /*335:*/

    case par_end:
      print_esc(/*1569:*/
                444
/*:1569*/
      );
      break;

/*:335*/ /*377:*/

    case input:
      if (chr_code == 0)
        print_esc(/*1570:*/
                  445
/*:1570*/
        );
      else
        print_esc(/*1571:*/
                  446
/*:1571*/
        );
      break;

/*:377*/ /*385:*/

    case top_bot_mark:
      switch (chr_code) {
        case first_mark_code:
          print_esc(/*1573:*/
                    448
/*:1573*/
          );
          break;
        case bot_mark_code:
          print_esc(/*1574:*/
                    449
/*:1574*/
          );
          break;
        case split_first_mark_code:
          print_esc(/*1575:*/
                    450
/*:1575*/
          );
          break;
        case split_bot_mark_code:
          print_esc(/*1576:*/
                    451
/*:1576*/
          );
          break;
        default:
          print_esc(/*1572:*/
                    447
/*:1572*/
          );
      }
      break;

/*:385*/ /*412:*/

    case register:
      if (chr_code == int_val)
        print_esc(/*1501:*/
                  376
/*:1501*/
        );
      else if (chr_code == dimen_val)
        print_esc(/*1524:*/
                  399
/*:1524*/
        );
      else if (chr_code == glue_val)
        print_esc(/*1423:*/
                  298
/*:1423*/
        );
      else
        print_esc(/*1424:*/
                  299
/*:1424*/
        );
      break;

/*:412*/ /*417:*/

    case set_aux:
      if (chr_code == vmode)
        print_esc(/*1578:*/
                  453
/*:1578*/
        );
      else
        print_esc(/*1577:*/
                  452
/*:1577*/
        );
      break;
    case set_page_int:
      if (chr_code == 0)
        print_esc(/*1579:*/
                  454
/*:1579*/
        );
      else
        print_esc(/*1580:*/
                  455
/*:1580*/
        );
      break;
    case set_box_dimen:
      if (chr_code == width_offset)
        print_esc(/*1581:*/
                  456
/*:1581*/
        );
      else if (chr_code == height_offset)
        print_esc(/*1582:*/
                  457
/*:1582*/
        );
      else
        print_esc(/*1583:*/
                  458
/*:1583*/
        );
      break;
    case last_item:
      switch (chr_code) {
        case int_val:
          print_esc(/*1584:*/
                    459
/*:1584*/
          );
          break;
        case dimen_val:
          print_esc(/*1585:*/
                    460
/*:1585*/
          );
          break;
        case glue_val:
          print_esc(/*1586:*/
                    461
/*:1586*/
          );
          break;
        case input_line_no_code:
          print_esc(/*1587:*/
                    462
/*:1587*/
          );
          break;
        default:
          print_esc(/*1588:*/
                    463
/*:1588*/
          );
      }
      break;

/*:417*/ /*469:*/

    case convert:
      switch (chr_code) {
        case number_code:
          print_esc(/*1605:*/
                    480
/*:1605*/
          );
          break;
        case roman_numeral_code:
          print_esc(/*1606:*/
                    481
/*:1606*/
          );
          break;
        case string_code:
          print_esc(/*1607:*/
                    482
/*:1607*/
          );
          break;
        case meaning_code:
          print_esc(/*1608:*/
                    483
/*:1608*/
          );
          break;
        case font_name_code:
          print_esc(/*1609:*/
                    484
/*:1609*/
          );
          break;
        default:
          print_esc(/*1610:*/
                    485
/*:1610*/
          );
      }
      break;

/*:469*/ /*488:*/

    case if_test:
      switch (chr_code) {
        case if_cat_code:
          print_esc(/*1612:*/
                    487
/*:1612*/
          );
          break;
        case if_int_code:
          print_esc(/*1613:*/
                    488
/*:1613*/
          );
          break;
        case if_dim_code:
          print_esc(/*1614:*/
                    489
/*:1614*/
          );
          break;
        case if_odd_code:
          print_esc(/*1615:*/
                    490
/*:1615*/
          );
          break;
        case if_vmode_code:
          print_esc(/*1616:*/
                    491
/*:1616*/
          );
          break;
        case if_hmode_code:
          print_esc(/*1617:*/
                    492
/*:1617*/
          );
          break;
        case if_mmode_code:
          print_esc(/*1618:*/
                    493
/*:1618*/
          );
          break;
        case if_inner_code:
          print_esc(/*1619:*/
                    494
/*:1619*/
          );
          break;
        case if_void_code:
          print_esc(/*1620:*/
                    495
/*:1620*/
          );
          break;
        case if_hbox_code:
          print_esc(/*1621:*/
                    496
/*:1621*/
          );
          break;
        case if_vbox_code:
          print_esc(/*1622:*/
                    497
/*:1622*/
          );
          break;
        case ifx_code:
          print_esc(/*1623:*/
                    498
/*:1623*/
          );
          break;
        case if_eof_code:
          print_esc(/*1624:*/
                    499
/*:1624*/
          );
          break;
        case if_true_code:
          print_esc(/*1625:*/
                    500
/*:1625*/
          );
          break;
        case if_false_code:
          print_esc(/*1626:*/
                    501
/*:1626*/
          );
          break;
        case if_case_code:
          print_esc(/*1627:*/
                    502
/*:1627*/
          );
          break;
        default:
          print_esc(/*1611:*/
                    486
/*:1611*/
          );
      }
      break;

/*:488*/ /*492:*/

    case fi_or_else:
      if (chr_code == fi_code)
        print_esc(/*1628:*/
                  503
/*:1628*/
        );
      else if (chr_code == or_code)
        print_esc(/*1629:*/
                  504
/*:1629*/
        );
      else
        print_esc(/*1630:*/
                  505
/*:1630*/
        );
      break;

/*:492*/ /*781:*/

    case tab_mark:
      if (chr_code == span_code)
        print_esc(/*1669:*/
                  544
/*:1669*/
        );
      else
        chr_cmd("alignment tab character ") break;
    case car_ret:
      if (chr_code == cr_code)
        print_esc(/*1670:*/
                  545
/*:1670*/
        );
      else
        print_esc(/*1671:*/
                  546
/*:1671*/
        );
      break;

/*:781*/ /*984:*/

    case set_page_dimen:
      switch (chr_code) {
        case 0:
          print_esc(/*1689:*/
                    564
/*:1689*/
          );
          break;
        case 1:
          print_esc(/*1690:*/
                    565
/*:1690*/
          );
          break;
        case 2:
          print_esc(/*1691:*/
                    566
/*:1691*/
          );
          break;
        case 3:
          print_esc(/*1692:*/
                    567
/*:1692*/
          );
          break;
        case 4:
          print_esc(/*1693:*/
                    568
/*:1693*/
          );
          break;
        case 5:
          print_esc(/*1694:*/
                    569
/*:1694*/
          );
          break;
        case 6:
          print_esc(/*1695:*/
                    570
/*:1695*/
          );
          break;
        default:
          print_esc(/*1696:*/
                    571
/*:1696*/
          );
      }
      break;

/*:984*/ /*1053:*/

    case stop:
      if (chr_code == 1)
        print_esc(/*1699:*/
                  574
/*:1699*/
        );
      else
        print_esc(/*1698:*/
                  573
/*:1698*/
        );
      break;

/*:1053*/ /*1059:*/

    case hskip:
      switch (chr_code) {
        case skip_code:
          print_esc(/*1700:*/
                    575
/*:1700*/
          );
          break;
        case fil_code:
          print_esc(/*1701:*/
                    576
/*:1701*/
          );
          break;
        case fill_code:
          print_esc(/*1702:*/
                    577
/*:1702*/
          );
          break;
        case ss_code:
          print_esc(/*1703:*/
                    578
/*:1703*/
          );
          break;
        default:
          print_esc(/*1704:*/
                    579
/*:1704*/
          );
      }
      break;
    case vskip:
      switch (chr_code) {
        case skip_code:
          print_esc(/*1705:*/
                    580
/*:1705*/
          );
          break;
        case fil_code:
          print_esc(/*1706:*/
                    581
/*:1706*/
          );
          break;
        case fill_code:
          print_esc(/*1707:*/
                    582
/*:1707*/
          );
          break;
        case ss_code:
          print_esc(/*1708:*/
                    583
/*:1708*/
          );
          break;
        default:
          print_esc(/*1709:*/
                    584
/*:1709*/
          );
      }
      break;
    case mskip:
      print_esc(/*1393:*/
                268
/*:1393*/
      );
      break;
    case kern:
      print_esc(/*1396:*/
                271
/*:1396*/
      );
      break;
    case mkern:
      print_esc(/*1397:*/
                272
/*:1397*/
      );
      break;

/*:1059*/ /*1072:*/

    case hmove:
      if (chr_code == 1)
        print_esc(/*1712:*/
                  587
/*:1712*/
        );
      else
        print_esc(/*1713:*/
                  588
/*:1713*/
        );
      break;
    case vmove:
      if (chr_code == 1)
        print_esc(/*1714:*/
                  589
/*:1714*/
        );
      else
        print_esc(/*1715:*/
                  590
/*:1715*/
        );
      break;
    case make_box:
      switch (chr_code) {
        case box_code:
          print_esc(/*1437:*/
                    312
/*:1437*/
          );
          break;
        case copy_code:
          print_esc(/*1716:*/
                    591
/*:1716*/
          );
          break;
        case last_box_code:
          print_esc(/*1717:*/
                    592
/*:1717*/
          );
          break;
        case vsplit_code:
          print_esc(/*1687:*/
                    562
/*:1687*/
          );
          break;
        case vtop_code:
          print_esc(/*1718:*/
                    593
/*:1718*/
          );
          break;
        case vtop_code + vmode:
          print_esc(/*1688:*/
                    563
/*:1688*/
          );
          break;
        default:
          print_esc(/*1719:*/
                    594
/*:1719*/
          );
      }
      break;
    case leader_ship:
      if (chr_code == a_leaders)
        print_esc(/*1721:*/
                  596
/*:1721*/
        );
      else if (chr_code == c_leaders)
        print_esc(/*1722:*/
                  597
/*:1722*/
        );
      else if (chr_code == x_leaders)
        print_esc(/*1723:*/
                  598
/*:1723*/
        );
      else
        print_esc(/*1720:*/
                  595
/*:1720*/
        );
      break;

/*:1072*/ /*1089:*/

    case start_par:
      if (chr_code == 0)
        print_esc(/*1725:*/
                  600
/*:1725*/
        );
      else
        print_esc(/*1724:*/
                  599
/*:1724*/
        );
      break;

/*:1089*/ /*1108:*/

    case remove_item:
      if (chr_code == glue_node)
        print_esc(/*1728:*/
                  603
/*:1728*/
        );
      else if (chr_code == kern_node)
        print_esc(/*1727:*/
                  602
/*:1727*/
        );
      else
        print_esc(/*1726:*/
                  601
/*:1726*/
        );
      break;
    case un_hbox:
      if (chr_code == copy_code)
        print_esc(/*1730:*/
                  605
/*:1730*/
        );
      else
        print_esc(/*1729:*/
                  604
/*:1729*/
        );
      break;
    case un_vbox:
      if (chr_code == copy_code)
        print_esc(/*1732:*/
                  607
/*:1732*/
        );
      else
        print_esc(/*1731:*/
                  606
/*:1731*/
        );
      break;

/*:1108*/ /*1115:*/

    case discretionary:
      if (chr_code == 1)
        print_esc('-');
      else
        print_esc(/*1400:*/
                  275
/*:1400*/
        );
      break;

/*:1115*/ /*1143:*/

    case eq_no:
      if (chr_code == 1)
        print_esc(/*1734:*/
                  609
/*:1734*/
        );
      else
        print_esc(/*1733:*/
                  608
/*:1733*/
        );
      break;

/*:1143*/ /*1157:*/

    case math_comp:
      switch (chr_code) {
        case ord_noad:
          print_esc(/*1649:*/
                    524
/*:1649*/
          );
          break;
        case op_noad:
          print_esc(/*1650:*/
                    525
/*:1650*/
          );
          break;
        case bin_noad:
          print_esc(/*1651:*/
                    526
/*:1651*/
          );
          break;
        case rel_noad:
          print_esc(/*1652:*/
                    527
/*:1652*/
          );
          break;
        case open_noad:
          print_esc(/*1653:*/
                    528
/*:1653*/
          );
          break;
        case close_noad:
          print_esc(/*1654:*/
                    529
/*:1654*/
          );
          break;
        case punct_noad:
          print_esc(/*1655:*/
                    530
/*:1655*/
          );
          break;
        case inner_noad:
          print_esc(/*1656:*/
                    531
/*:1656*/
          );
          break;
        case under_noad:
          print_esc(/*1658:*/
                    533
/*:1658*/
          );
          break;
        default:
          print_esc(/*1657:*/
                    532
/*:1657*/
          );
      }
      break;
    case limit_switch:
      if (chr_code == limits)
        print_esc(/*1661:*/
                  536
/*:1661*/
        );
      else if (chr_code == no_limits)
        print_esc(/*1662:*/
                  537
/*:1662*/
        );
      else
        print_esc(/*1735:*/
                  610
/*:1735*/
        );
      break;

/*:1157*/ /*1170:*/

    case math_style:
      print_style(chr_code);
      break;

/*:1170*/ /*1179:*/

    case above:
      switch (chr_code) {
        case over_code:
          print_esc(/*1737:*/
                    612
/*:1737*/
          );
          break;
        case atop_code:
          print_esc(/*1738:*/
                    613
/*:1738*/
          );
          break;
        case delimited_code + above_code:
          print_esc(/*1739:*/
                    614
/*:1739*/
          );
          break;
        case delimited_code + over_code:
          print_esc(/*1740:*/
                    615
/*:1740*/
          );
          break;
        case delimited_code + atop_code:
          print_esc(/*1741:*/
                    616
/*:1741*/
          );
          break;
        default:
          print_esc(/*1736:*/
                    611
/*:1736*/
          );
      }
      break;

/*:1179*/ /*1189:*/

    case left_right:
      if (chr_code == left_noad)
        print_esc(/*1659:*/
                  534
/*:1659*/
        );
      else
        print_esc(/*1660:*/
                  535
/*:1660*/
        );
      break;

/*:1189*/ /*1209:*/

    case prefix:
      if (chr_code == 1)
        print_esc(/*1743:*/
                  618
/*:1743*/
        );
      else if (chr_code == 2)
        print_esc(/*1744:*/
                  619
/*:1744*/
        );
      else
        print_esc(/*1745:*/
                  620
/*:1745*/
        );
      break;
    case def:
      if (chr_code == 0)
        print_esc(/*1746:*/
                  621
/*:1746*/
        );
      else if (chr_code == 1)
        print_esc(/*1747:*/
                  622
/*:1747*/
        );
      else if (chr_code == 2)
        print_esc(/*1748:*/
                  623
/*:1748*/
        );
      else
        print_esc(/*1749:*/
                  624
/*:1749*/
        );
      break;

/*:1209*/ /*1220:*/

    case let:
      if (chr_code != normal)
        print_esc(/*1753:*/
                  628
/*:1753*/
        );
      else
        print_esc(/*1752:*/
                  627
/*:1752*/
        );
      break;

/*:1220*/ /*1223:*/

    case shorthand_def:
      switch (chr_code) {
        case char_def_code:
          print_esc(/*1754:*/
                    629
/*:1754*/
          );
          break;
        case math_char_def_code:
          print_esc(/*1755:*/
                    630
/*:1755*/
          );
          break;
        case count_def_code:
          print_esc(/*1756:*/
                    631
/*:1756*/
          );
          break;
        case dimen_def_code:
          print_esc(/*1757:*/
                    632
/*:1757*/
          );
          break;
        case skip_def_code:
          print_esc(/*1758:*/
                    633
/*:1758*/
          );
          break;
        case mu_skip_def_code:
          print_esc(/*1759:*/
                    634
/*:1759*/
          );
          break;
        default:
          print_esc(/*1760:*/
                    635
/*:1760*/
          );
      }
      break;
    case char_given: {
      print_esc(/*1535:*/
                410
/*:1535*/
      );
      print_hex(chr_code);
    } break;
    case math_given: {
      print_esc(/*1546:*/
                421
/*:1546*/
      );
      print_hex(chr_code);
    } break;

/*:1223*/ /*1231:*/

    case def_code:
      if (chr_code == cat_code_base)
        print_esc(/*1441:*/
                  316
/*:1441*/
        );
      else if (chr_code == math_code_base)
        print_esc(/*1445:*/
                  320
/*:1445*/
        );
      else if (chr_code == lc_code_base)
        print_esc(/*1442:*/
                  317
/*:1442*/
        );
      else if (chr_code == uc_code_base)
        print_esc(/*1443:*/
                  318
/*:1443*/
        );
      else if (chr_code == sf_code_base)
        print_esc(/*1444:*/
                  319
/*:1444*/
        );
      else
        print_esc(/*1502:*/
                  377
/*:1502*/
        );
      break;
    case def_family:
      print_size(chr_code - math_font_base);
      break;

/*:1231*/ /*1251:*/

    case hyph_data:
      if (chr_code == 1)
        print_esc(/*1684:*/
                  559
/*:1684*/
        );
      else
        print_esc(/*1683:*/
                  558
/*:1683*/
        );
      break;

/*:1251*/ /*1255:*/

    case assign_font_int:
      if (chr_code == 0)
        print_esc(/*1762:*/
                  637
/*:1762*/
        );
      else
        print_esc(/*1763:*/
                  638
/*:1763*/
        );
      break;

/*:1255*/ /*1261:*/

    case set_font: {
      print_str("select font ");
      slow_print(font_name[chr_code]);
      if (font_size[chr_code] != font_dsize[chr_code]) {
        print_str(" at ");
        print_scaled(font_size[chr_code]);
        print_str("pt");
      }
    } break;

/*:1261*/ /*1263:*/

    case set_interaction:
      switch (chr_code) {
        case batch_mode:
          print_esc(/*1383:*/
                    258
/*:1383*/
          );
          break;
        case nonstop_mode:
          print_esc(/*1384:*/
                    259
/*:1384*/
          );
          break;
        case scroll_mode:
          print_esc(/*1385:*/
                    260
/*:1385*/
          );
          break;
        default:
          print_esc(/*1767:*/
                    642
/*:1767*/
          );
      }
      break;

/*:1263*/ /*1273:*/

    case in_stream:
      if (chr_code == 0)
        print_esc(/*1769:*/
                  644
/*:1769*/
        );
      else
        print_esc(/*1768:*/
                  643
/*:1768*/
        );
      break;

/*:1273*/ /*1278:*/

    case message:
      if (chr_code == 0)
        print_esc(/*1770:*/
                  645
/*:1770*/
        );
      else
        print_esc(/*1771:*/
                  646
/*:1771*/
        );
      break;

/*:1278*/ /*1287:*/

    case case_shift:
      if (chr_code == lc_code_base)
        print_esc(/*1772:*/
                  647
/*:1772*/
        );
      else
        print_esc(/*1773:*/
                  648
/*:1773*/
        );
      break;

/*:1287*/ /*1292:*/

    case xray:
      switch (chr_code) {
        case show_box_code:
          print_esc(/*1775:*/
                    650
/*:1775*/
          );
          break;
        case show_the_code:
          print_esc(/*1776:*/
                    651
/*:1776*/
          );
          break;
        case show_lists_code:
          print_esc(/*1777:*/
                    652
/*:1777*/
          );
          break;
        default:
          print_esc(/*1774:*/
                    649
/*:1774*/
          );
      }
      break;

/*:1292*/ /*1295:*/

    case undefined_cs:
      print_str("undefined");
      break;
    case call:
      print_str("macro");
      break;
    case long_call:
      print_esc(/*1778:*/
                653
/*:1778*/
      );
      break;
    case outer_call:
      print_esc(/*1779:*/
                654
/*:1779*/
      );
      break;
    case long_outer_call: {
      print_esc(/*1743:*/
                618
/*:1743*/
      );
      print_esc(/*1779:*/
                654
/*:1779*/
      );
    } break;
    case end_template:
      print_esc(/*1780:*/
                655
/*:1780*/
      );
      break;

/*:1295*/ /*1346:*/

    case extension:
      switch (chr_code) {
        case open_node:
          print_esc(/*1783:*/
                    658
/*:1783*/
          );
          break;
        case write_node:
          print_esc(/*1568:*/
                    443
/*:1568*/
          );
          break;
        case close_node:
          print_esc(/*1784:*/
                    659
/*:1784*/
          );
          break;
        case special_node:
          print_esc(/*1785:*/
                    660
/*:1785*/
          );
          break;
        case immediate_code:
          print_esc(/*1786:*/
                    661
/*:1786*/
          );
          break;
        case set_language_code:
          print_esc(/*1787:*/
                    662
/*:1787*/
          );
          break;
        default:
          print_str("[unknown extension!]");
      }
      break;

/*:1346*/

    default:
      print_str("[unknown command code!]");
  }
}

/*:298*/

#ifdef STAT
void show_eqtb(pointer n) {
  if (n < active_base)
    print_char('?');
  else if (n < glue_base) /*223:*/

  {
    sprint_cs(n);
    print_char('=');
    print_cmd_chr(eq_type(n), equiv(n));
    if (eq_type(n) >= call) {
      print_char(':');
      show_token_list(link(equiv(n)), null, 32);
    }
  }

/*:223*/

  else if (n < local_base) /*229:*/

    if (n < skip_base) {
      print_skip_param(n - glue_base);
      print_char('=');
      if (n < glue_base + thin_mu_skip_code)
        print_spec(equiv(n), /*1425:*/
                   300
/*:1425*/
        );
      else
        print_spec(equiv(n), /*1394:*/
                   269
/*:1394*/
        );
    } else if (n < mu_skip_base) {
      print_esc(/*1423:*/
                298
/*:1423*/
      );
      print_int(n - skip_base);
      print_char('=');
      print_spec(equiv(n), /*1425:*/
                 300
/*:1425*/
      );
    } else {
      print_esc(/*1424:*/
                299
/*:1424*/
      );
      print_int(n - mu_skip_base);
      print_char('=');
      print_spec(equiv(n), /*1394:*/
                 269
/*:1394*/
      );
    }

/*:229*/

  else if (n < int_base) /*233:*/

    if (n == par_shape_loc) {
      print_esc(/*1436:*/
                311
/*:1436*/
      );
      print_char('=');
      if (par_shape_ptr == null)
        print_char('0');
      else
        print_int(info(par_shape_ptr));
    } else if (n < toks_base) {
      print_cmd_chr(assign_toks, n);
      print_char('=');
      if (equiv(n) != null) show_token_list(link(equiv(n)), null, 32);
    } else if (n < box_base) {
      print_esc(/*1435:*/
                310
/*:1435*/
      );
      print_int(n - toks_base);
      print_char('=');
      if (equiv(n) != null) show_token_list(link(equiv(n)), null, 32);
    } else if (n < cur_font_loc) {
      print_esc(/*1437:*/
                312
/*:1437*/
      );
      print_int(n - box_base);
      print_char('=');
      if (equiv(n) == null)
        print_str("void");
      else {
        depth_threshold = 0;
        breadth_max = 1;
        show_node_list(equiv(n));
      }
    } else if (n < cat_code_base) /*234:*/

    {
      if (n == cur_font_loc)
        print_str("current font");
      else if (n < math_font_base + 16) {
        print_esc(/*1438:*/
                  313
/*:1438*/
        );
        print_int(n - math_font_base);
      } else if (n < math_font_base + 32) {
        print_esc(/*1439:*/
                  314
/*:1439*/
        );
        print_int(n - math_font_base - 16);
      } else {
        print_esc(/*1440:*/
                  315
/*:1440*/
        );
        print_int(n - math_font_base - 32);
      }
      print_char('=');
      print_esc(hash[font_id_base + equiv(n)].rh);

    }
/*:234*/

    else /*235:*/

        if (n < math_code_base) {
      if (n < lc_code_base) {
        print_esc(/*1441:*/
                  316
/*:1441*/
        );
        print_int(n - cat_code_base);
      } else if (n < uc_code_base) {
        print_esc(/*1442:*/
                  317
/*:1442*/
        );
        print_int(n - lc_code_base);
      } else if (n < sf_code_base) {
        print_esc(/*1443:*/
                  318
/*:1443*/
        );
        print_int(n - uc_code_base);
      } else {
        print_esc(/*1444:*/
                  319
/*:1444*/
        );
        print_int(n - sf_code_base);
      }
      print_char('=');
      print_int(equiv(n));
    } else {
      print_esc(/*1445:*/
                320
/*:1445*/
      );
      print_int(n - math_code_base);
      print_char('=');
      print_int(ho(equiv(n)));
    }

/*:235*/

/*:233*/

  else if (n < dimen_base) /*242:*/

  {
    if (n < count_base)
      print_param(n - int_base);
    else if (n < del_code_base) {
      print_esc(/*1501:*/
                376
/*:1501*/
      );
      print_int(n - count_base);
    } else {
      print_esc(/*1502:*/
                377
/*:1502*/
      );
      print_int(n - del_code_base);
    }
    print_char('=');
    print_int(eqtb[n].i);
  }
/*:242*/

  else if (n <= eqtb_size) /*251:*/

  {
    if (n < scaled_base)
      print_length_param(n - dimen_base);
    else {
      print_esc(/*1524:*/
                399
/*:1524*/
      );
      print_int(n - scaled_base);
    }
    print_char('=');
    print_scaled(eqtb[n].sc);
    print_str("pt");
  }

/*:251*/

  else
    print_char('?');
}
#endif

/*:252*/ /*259:*/
pointer id_lookup(int j, int l) {
  int h;
  int d;
  pointer p;
  pointer k;
/*261:*/

  h = buffer[j];
  for (k = j + 1; k <= j + l - 1; k++) {
    h = h + h + buffer[k];
    while (h >= hash_prime) h = h - hash_prime;
  }

/*:261*/
  ;
  p = h + hash_base;
  loop {
    if (text(p) > 0)
      if (length(text(p)) == l)
        if (str_eq_buf(text(p), j)) goto found;
    if (next(p) == 0) {
      if (no_new_control_sequence)
        p = undefined_control_sequence;
      else /*260:*/

      {
        if (text(p) > 0) {
          do {
            if (hash_is_full) overflow("hash size", hash_size);

            decr(hash_used);
          } while (!(text(hash_used) == 0));
          next(p) = hash_used;
          p = hash_used;
        }
        str_room(l);
        d = cur_length;
        while (pool_ptr > str_start[str_ptr]) {
          decr(pool_ptr);
          str_pool[pool_ptr + l] = str_pool[pool_ptr];
        }
        for (k = j; k <= j + l - 1; k++) append_char(buffer[k]);
        text(p) = make_string();
        pool_ptr = pool_ptr + d;
#ifdef STAT
        incr(cs_count);
#endif
      }

/*:260*/
      ;
      goto found;
    }
    p = next(p);
  }
found:
  return p;
}

/*:259*/ /*264:*/

#ifdef INIT
void primitive(str_number s, quarterword c, halfword o) {
  pool_pointer k;
  int j;
  small_number l;
  if (s < 256)
    cur_val = s + single_base;
  else {
    k = str_start[s];
    l = str_start[s + 1] - k;

    for (j = 0; j <= l - 1; j++) buffer[j] = so(str_pool[k + j]);
    cur_val = id_lookup(0, l);
    flush_string;
    text(cur_val) = s;
  }
  eq_level(cur_val) = level_one;
  eq_type(cur_val) = c;
  equiv(cur_val) = o;
}
#endif

/*:264*/ /*274:*/
void new_save_level(group_code c) {
  check_full_save_stack;
  save_type(save_ptr) = level_boundary;
  save_level(save_ptr) = cur_group;
  save_index(save_ptr) = cur_boundary;
  if (cur_level == max_quarterword)
    overflow("grouping levels",

             max_quarterword - min_quarterword);

  cur_boundary = save_ptr;
  incr(cur_level);
  incr(save_ptr);
  cur_group = c;
}

/*:274*/ /*275:*/
void eq_destroy(memory_word w) {
  pointer q;
  switch (eq_type_field(w)) {
    case call:
    case long_call:
    case outer_call:
    case long_outer_call:
      delete_token_ref(equiv_field(w));
      break;
    case glue_ref:
      delete_glue_ref(equiv_field(w));
      break;
    case shape_ref: {
      q = equiv_field(w);
      if (q != null) free_node(q, info(q) + info(q) + 1);
    } break;
    case box_ref:
      flush_node_list(equiv_field(w));
      break;
    default:
      do_nothing;
  }
}

/*:275*/ /*276:*/
void eq_save(pointer p, quarterword l) {
  check_full_save_stack;
  if (l == level_zero)
    save_type(save_ptr) = restore_zero;
  else {
    save_stack[save_ptr] = eqtb[p];
    incr(save_ptr);
    save_type(save_ptr) = restore_old_value;
  }
  save_level(save_ptr) = l;
  save_index(save_ptr) = p;
  incr(save_ptr);
}

/*:276*/ /*277:*/
void eq_define(pointer p, quarterword t, halfword e)

{
  if (eq_level(p) == cur_level)
    eq_destroy(eqtb[p]);
  else if (cur_level > level_one)
    eq_save(p, eq_level(p));
  eq_level(p) = cur_level;
  eq_type(p) = t;
  equiv(p) = e;
}

/*:277*/ /*278:*/
void eq_word_define(pointer p, int w) {
  if (xeq_level[p] != cur_level) {
    eq_save(p, xeq_level[p]);
    xeq_level[p] = cur_level;
  }
  eqtb[p].i = w;
}

/*:278*/ /*279:*/
void geq_define(pointer p, quarterword t, halfword e)

{
  eq_destroy(eqtb[p]);
  eq_level(p) = level_one;
  eq_type(p) = t;
  equiv(p) = e;
}

void geq_word_define(pointer p, int w) {
  eqtb[p].i = w;
  xeq_level[p] = level_one;
}

/*:279*/ /*280:*/
void save_for_after(halfword t) {
  if (cur_level > level_one) {
    check_full_save_stack;
    save_type(save_ptr) = insert_token;
    save_level(save_ptr) = level_zero;
    save_index(save_ptr) = t;
    incr(save_ptr);
  }
}

/*:280*/ /*281:*/
/*284:*/

#ifdef STAT
void restore_trace(pointer p, str_number s)

{
  begin_diagnostic();
  print_char('{');
  print(s);
  print_char(' ');
  show_eqtb(p);
  print_char('}');
  end_diagnostic(false);
}
#endif

/*:284*/

void back_input(void);
void unsave(void) {
  pointer p;
  quarterword l;
  halfword t;
  if (cur_level > level_one) {
    decr(cur_level);
/*282:*/

    loop {
      decr(save_ptr);
      if (save_type(save_ptr) == level_boundary) goto done;
      p = save_index(save_ptr);
      if (save_type(save_ptr) == insert_token)
/*326:*/

      {
        t = cur_tok;
        cur_tok = p;
        back_input();
        cur_tok = t;
      }
/*:326*/

      else {
        if (save_type(save_ptr) == restore_old_value) {
          l = save_level(save_ptr);
          decr(save_ptr);
        } else
          save_stack[save_ptr] = eqtb[undefined_control_sequence];
/*283:*/

        if (p < int_base)
          if (eq_level(p) == level_one) {
            eq_destroy(save_stack[save_ptr]);

#ifdef STAT
            if (tracing_restores > 0)
              restore_trace(p, /*1564:*/
                            439
/*:1564*/
              );
#endif

          } else {
            eq_destroy(eqtb[p]);
            eqtb[p] = save_stack[save_ptr];

#ifdef STAT
            if (tracing_restores > 0)
              restore_trace(p, /*1565:*/
                            440
/*:1565*/
              );
#endif
          }
        else if (xeq_level[p] != level_one) {
          eqtb[p] = save_stack[save_ptr];
          xeq_level[p] = l;

#ifdef STAT
          if (tracing_restores > 0)
            restore_trace(p, /*1565:*/
                          440
/*:1565*/
            );
#endif

        } else {
#ifdef STAT
          if (tracing_restores > 0)
            restore_trace(p, /*1564:*/
                          439
/*:1564*/
            );
#endif
        }

/*:283*/
        ;
      }
    }
  done:
    cur_group = save_level(save_ptr);
    cur_boundary = save_index(save_ptr)

/*:282*/
        ;
  } else
    confusion(/*1563:*/
              438
/*:1563*/
    );
}

/*:281*/ /*288:*/
void prepare_mag(void) {
  if ((mag_set > 0) && (mag != mag_set)) {
    print_err("Incompatible magnification (");
    print_int(mag);

    print_str(");");
    print_nl(" the previous value will be retained");
    help2("I can handle only one magnification ratio per job. So I've")(
        "reverted to the magnification you used earlier on this run.");
    int_error(mag_set);
    geq_word_define(int_base + mag_code, mag_set);
  }
  if ((mag <= 0) || (mag > 32768)) {
    print_err("Illegal magnification has been changed to 1000");

    help1("The magnification ratio must be between 1 and 32768.");
    int_error(mag);
    geq_word_define(int_base + mag_code, 1000);
  }
  mag_set = mag;
}

/*:288*/ /*295:*/
void token_show(pointer p) {
  if (p != null) show_token_list(link(p), null, 10000000);
}

/*:295*/ /*296:*/
void print_meaning(void) {
  print_cmd_chr(cur_cmd, cur_chr);
  if (cur_cmd >= call) {
    print_char(':');
    print_ln();
    token_show(cur_chr);
  } else if (cur_cmd == top_bot_mark) {
    print_char(':');
    print_ln();
    token_show(cur_mark[cur_chr]);
  }
}

/*:296*/ /*299:*/
void show_cur_cmd_chr(void) {
  begin_diagnostic();
  print_nl("{");
  if (mode != shown_mode) {
    print_mode(mode);
    print_str(": ");
    shown_mode = mode;
  }
  print_cmd_chr(cur_cmd, cur_chr);
  print_char('}');
  end_diagnostic(false);
}

/*:299*/ /*311:*/
void show_context(void) {
  uint8_t old_setting;
  int nn;
  bool bottom_line;
/*315:*/

  int i;
  uint16_t j;
  uint8_t l;
  int m;
  uint8_t n;
  int p;
  int q;

/*:315*/

  base_ptr = input_ptr;
  input_stack[base_ptr] = cur_input;

  nn = -1;
  bottom_line = false;
  loop {
    cur_input = input_stack[base_ptr];
    if ((state != token_list))
      if ((name > 17) || (base_ptr == 0)) bottom_line = true;
    if ((base_ptr == input_ptr) || bottom_line || (nn < error_context_lines))
/*312:*/

    {
      if ((base_ptr == input_ptr) || (state != token_list) ||
          (token_type != backed_up) || (loc != null))

      {
        tally = 0;
        old_setting = selector;
        if (state != token_list) { /*313:*/

          if (name <= 17)
            if (terminal_input)
              if (base_ptr == 0)
                print_nl("<*>");
              else
                print_nl("<insert> ");
            else {
              print_nl("<read ");
              if (name == 17)
                print_char('*');
              else
                print_int(name - 1);

              print_char('>');
            }
          else {
            print_nl("l.");
            print_int(line);
          }
          print_char(' ')

/*:313*/
              ;
/*318:*/

          begin_pseudoprint;
          if (buffer[limit] == end_line_char)
            j = limit;
          else
            j = limit + 1;
          if (j > 0)
            for (i = start; i <= j - 1; i++) {
              if (i == loc) set_trick_count;
              print(buffer[i]);
            }

/*:318*/
            ;
        } else { /*314:*/

          switch (token_type) {
            case parameter:
              print_nl("<argument> ");
              break;
            case u_template:
            case v_template:
              print_nl("<template> ");
              break;
            case backed_up:
              if (loc == null)
                print_nl("<recently read> ");
              else
                print_nl("<to be read again> ");
              break;
            case inserted:
              print_nl("<inserted text> ");
              break;
            case macro: {
              print_ln();
              print_cs(name);
            } break;
            case output_text:
              print_nl("<output> ");
              break;
            case every_par_text:
              print_nl("<everypar> ");
              break;
            case every_math_text:
              print_nl("<everymath> ");
              break;
            case every_display_text:
              print_nl("<everydisplay> ");
              break;
            case every_hbox_text:
              print_nl("<everyhbox> ");
              break;
            case every_vbox_text:
              print_nl("<everyvbox> ");
              break;
            case every_job_text:
              print_nl("<everyjob> ");
              break;
            case every_cr_text:
              print_nl("<everycr> ");
              break;
            case mark_text:
              print_nl("<mark> ");
              break;
            case write_text:
              print_nl("<write> ");
              break;
            default:
              print_nl("?");
          }

/*:314*/
          ;
/*319:*/

          begin_pseudoprint;
          if (token_type < macro)
            show_token_list(start, loc, 100000);
          else
            show_token_list(link(start), loc, 100000)

/*:319*/
                ;
        }
        selector = old_setting;
/*317:*/

        if (trick_count == 1000000) set_trick_count;

        if (tally < trick_count)
          m = tally - first_count;
        else
          m = trick_count - first_count;
        if (l + first_count <= half_error_line) {
          p = 0;
          n = l + first_count;
        } else {
          print_str("...");
          p = l + first_count - half_error_line + 3;
          n = half_error_line;
        }
        for (q = p; q <= first_count - 1; q++)
          print_char(trick_buf[q % error_line]);
        print_ln();
        for (q = 1; q <= n; q++) print_char(' ');
        if (m + n <= error_line)
          p = first_count + m;
        else
          p = first_count + (error_line - n - 3);
        for (q = first_count; q <= p - 1; q++)
          print_char(trick_buf[q % error_line]);
        if (m + n > error_line)
          print_str("...")

/*:317*/
              ;
        incr(nn);
      }
    }
/*:312*/

    else if (nn == error_context_lines) {
      print_nl("...");
      incr(nn);
    }
    if (bottom_line) goto done;
    decr(base_ptr);
  }
done:
  cur_input = input_stack[input_ptr];
}

/*:311*/ /*323:*/
void begin_token_list(pointer p, quarterword t) {
  push_input;
  state = token_list;
  start = p;
  token_type = t;
  if (t >= macro) {
    add_token_ref(p);
    if (t == macro)
      param_start = param_ptr;
    else {
      loc = link(p);
      if (tracing_macros > 1) {
        begin_diagnostic();
        print_nl("");
        switch (t) {
          case mark_text:
            print_esc(/*1401:*/
                      276
/*:1401*/
            );
            break;
          case write_text:
            print_esc(/*1568:*/
                      443
/*:1568*/
            );
            break;
          default:
            print_cmd_chr(assign_toks, t - output_text + output_routine_loc);
        }
        print_str("->");
        token_show(p);
        end_diagnostic(false);
      }
    }
  } else
    loc = p;
}

/*:323*/ /*324:*/
void end_token_list(void) {
  if (token_type >= backed_up) {
    if (token_type <= inserted)
      flush_list(start);
    else {
      delete_token_ref(start);
      if (token_type == macro)
        while (param_ptr > param_start) {
          decr(param_ptr);
          flush_list(param_stack[param_ptr]);
        }
    }
  } else if (token_type == u_template)
    if (align_state > 500000)
      align_state = 0;
    else
      fatal_error("(interwoven alignment preambles are not allowed)");

  pop_input;
  check_interrupt;
}

/*:324*/ /*325:*/
void back_input(void) {
  pointer p;
  while ((state == token_list) && (loc == null) && (token_type != v_template))
    end_token_list();
  p = get_avail();
  info(p) = cur_tok;
  if (cur_tok < right_brace_limit)
    if (cur_tok < left_brace_limit)
      decr(align_state);
    else
      incr(align_state);
  push_input;
  state = token_list;
  start = p;
  token_type = backed_up;
  loc = p;
}

/*:325*/ /*327:*/
void back_error(void) {
  OK_to_interrupt = false;
  back_input();
  OK_to_interrupt = true;
  error();
}

void ins_error(void) {
  OK_to_interrupt = false;
  back_input();
  token_type = inserted;
  OK_to_interrupt = true;
  error();
}

/*:327*/ /*328:*/
void begin_file_reading(void) {
  if (in_open == max_in_open) overflow("text input levels", max_in_open);

  if (first == buf_size) overflow("buffer size", buf_size);

  incr(in_open);
  push_input;
  index = in_open;
  line_stack[index] = line;
  start = first;
  state = mid_line;
  name = 0;
}

/*:328*/ /*329:*/
void end_file_reading(void) {
  first = start;
  line = line_stack[index];
  if (name > 17) a_close(&cur_file);
  pop_input;
  decr(in_open);
}

/*:329*/ /*330:*/
void clear_for_error_prompt(void) {
  while ((state != token_list) && terminal_input && (input_ptr > 0) &&
         (loc > limit))
    end_file_reading();
  print_ln();
  clear_terminal;
}

/*:330*/ /*336:*/
void check_outer_validity(void) {
  pointer p;
  pointer q;
  if (scanner_status != normal) {
    deletions_allowed = false;
/*337:*/

    if (cur_cs != 0) {
      if ((state == token_list) || (name < 1) || (name > 17)) {
        p = get_avail();
        info(p) = cs_token_flag + cur_cs;
        back_list(p);
      }
      cur_cmd = spacer;
      cur_chr = ' ';
    }

/*:337*/
    ;
    if (scanner_status > skipping)
/*338:*/

    {
      runaway();
      if (cur_cs == 0)
        print_err("File ended")

            else {
          cur_cs = 0;
          print_err("Forbidden control sequence found");
        }
      print_str(" while scanning ");
/*339:*/

      p = get_avail();
      switch (scanner_status) {
        case defining: {
          print_str("definition");
          info(p) = right_brace_token + '}';
        } break;
        case matching: {
          print_str("use");
          info(p) = par_token;
          long_state = outer_call;
        } break;
        case aligning: {
          print_str("preamble");
          info(p) = right_brace_token + '}';
          q = p;
          p = get_avail();
          link(p) = q;
          info(p) = cs_token_flag + frozen_cr;
          align_state = -1000000;
        } break;
        case absorbing: {
          print_str("text");
          info(p) = right_brace_token + '}';
        }
      }
      ins_list(p)

/*:339*/
          ;
      print_str(" of ");
      sprint_cs(warning_index);
      help4("I suspect you have forgotten a `}', causing me")(
          "to read past where you wanted me to stop.")(
          "I'll try to recover; but if the error is serious,")(
          "you'd better type `E' or `X' now and fix your file.");
      error();
    }
/*:338*/

    else {
      print_err("Incomplete ");
      print_cmd_chr(if_test, cur_if);

      print_str("; all text was ignored after line ");
      print_int(skip_line);
      help3("A forbidden control sequence occurred in skipped text.")(
          "This kind of error happens when you say `\\if...' and forget")(
          "the matching `\\fi'. I've inserted a `\\fi'; this might work.");
      if (cur_cs != 0)
        cur_cs = 0;
      else
        help_line[2] = "The file ended while I was skipping conditional text.";
      cur_tok = cs_token_flag + frozen_fi;
      ins_error();
    }
    deletions_allowed = true;
  }
}

/*:336*/ /*340:*/
void firm_up_the_line(void);

/*:340*/ /*341:*/
void get_next(void) {
  uint16_t k;
  halfword t;
  uint8_t cat;
  ASCII_code c, cc;
  uint8_t d;
restart:
  cur_cs = 0;
  if (state != token_list)
/*343:*/

  {
  get_cur_chr:
    if (loc <= limit) {
      cur_chr = buffer[loc];
      incr(loc);
    reswitch:
      cur_cmd = cat_code(cur_chr);
/*344:*/

      switch (state + cur_cmd) {
/*345:*/

      any_state_plus(ignore) : case skip_blanks + spacer:
      case new_line + spacer

/*:345*/
          :
        goto get_cur_chr;
        any_state_plus(escape)
            : /*354:*/

        {
          if (loc > limit)
            cur_cs = null_cs;
          else {
          start_cs:
            k = loc;
            cur_chr = buffer[k];
            cat = cat_code(cur_chr);
            incr(k);
            if (cat == letter)
              state = skip_blanks;
            else if (cat == spacer)
              state = skip_blanks;
            else
              state = mid_line;
            if ((cat == letter) && (k <= limit))
/*356:*/

            {
              do {
                cur_chr = buffer[k];
                cat = cat_code(cur_chr);
                incr(k);
              } while (!((cat != letter) || (k > limit)));
/*355:*/

              {
                if (buffer[k] == cur_chr)
                  if (cat == sup_mark)
                    if (k < limit) {
                      c = buffer[k + 1];
                      if (c < 0200) {
                        d = 2;
                        if (is_hex(c))
                          if (k + 2 <= limit) {
                            cc = buffer[k + 2];
                            if (is_hex(cc)) incr(d);
                          }
                        if (d > 2) {
                          hex_to_cur_chr;
                          buffer[k - 1] = cur_chr;
                        } else if (c < 0100)
                          buffer[k - 1] = c + 0100;
                        else
                          buffer[k - 1] = c - 0100;
                        limit = limit - d;
                        first = first - d;
                        while (k <= limit) {
                          buffer[k] = buffer[k + d];
                          incr(k);
                        }
                        goto start_cs;
                      }
                    }
              }

/*:355*/
              ;
              if (cat != letter) decr(k);

              if (k > loc + 1) {
                cur_cs = id_lookup(loc, k - loc);
                loc = k;
                goto found;
              }
            }
/*:356*/

            else /*355:*/

            {
              if (buffer[k] == cur_chr)
                if (cat == sup_mark)
                  if (k < limit) {
                    c = buffer[k + 1];
                    if (c < 0200) {
                      d = 2;
                      if (is_hex(c))
                        if (k + 2 <= limit) {
                          cc = buffer[k + 2];
                          if (is_hex(cc)) incr(d);
                        }
                      if (d > 2) {
                        hex_to_cur_chr;
                        buffer[k - 1] = cur_chr;
                      } else if (c < 0100)
                        buffer[k - 1] = c + 0100;
                      else
                        buffer[k - 1] = c - 0100;
                      limit = limit - d;
                      first = first - d;
                      while (k <= limit) {
                        buffer[k] = buffer[k + d];
                        incr(k);
                      }
                      goto start_cs;
                    }
                  }
            }

/*:355*/
            ;
            cur_cs = single_base + buffer[loc];
            incr(loc);
          }
        found:
          cur_cmd = eq_type(cur_cs);
          cur_chr = equiv(cur_cs);
          if (cur_cmd >= outer_call) check_outer_validity();
        }

/*:354*/
        break;
        any_state_plus(active_char)
            : /*353:*/

        {
          cur_cs = cur_chr + active_base;
          cur_cmd = eq_type(cur_cs);
          cur_chr = equiv(cur_cs);
          state = mid_line;
          if (cur_cmd >= outer_call) check_outer_validity();
        }

/*:353*/
        break;
        any_state_plus(sup_mark)
            : /*352:*/

        {
          if (cur_chr == buffer[loc])
            if (loc < limit) {
              c = buffer[loc + 1];
              if (c < 0200) {
                loc = loc + 2;
                if (is_hex(c))
                  if (loc <= limit) {
                    cc = buffer[loc];
                    if (is_hex(cc)) {
                      incr(loc);
                      hex_to_cur_chr;
                      goto reswitch;
                    }
                  }
                if (c < 0100)
                  cur_chr = c + 0100;
                else
                  cur_chr = c - 0100;
                goto reswitch;
              }
            }
          state = mid_line;
        }

/*:352*/
        break;
        any_state_plus(invalid_char)
            : /*346:*/

        {
          print_err("Text line contains an invalid character");

          help2("A funny symbol that I can't read has just been input.")(
              "Continue, and I'll forget that it ever happened.");
          deletions_allowed = false;
          error();
          deletions_allowed = true;
          goto restart;
        }

/*:346*/

/*347:*/

        case mid_line + spacer: /*349:*/

        {
          state = skip_blanks;
          cur_chr = ' ';
        }

/*:349*/
        break;
        case mid_line + car_ret: /*348:*/

        {
          loc = limit + 1;
          cur_cmd = spacer;
          cur_chr = ' ';
        }

/*:348*/
        break;
        case skip_blanks + car_ret:
          any_state_plus(comment)
              :
/*350:*/

          {
            loc = limit + 1;
            goto get_cur_chr;
          }

/*:350*/

        case new_line + car_ret: /*351:*/

        {
          loc = limit + 1;
          cur_cs = par_loc;
          cur_cmd = eq_type(cur_cs);
          cur_chr = equiv(cur_cs);
          if (cur_cmd >= outer_call) check_outer_validity();
        }

/*:351*/
        break;
        case mid_line + left_brace:
          incr(align_state);
          break;
        case skip_blanks + left_brace:
        case new_line + left_brace: {
          state = mid_line;
          incr(align_state);
        } break;
        case mid_line + right_brace:
          decr(align_state);
          break;
        case skip_blanks + right_brace:
        case new_line + right_brace: {
          state = mid_line;
          decr(align_state);
        } break;
          add_delims_to(case skip_blanks)
              : add_delims_to(case new_line) : state = mid_line;
          break;

/*:347*/

        default:
          do_nothing;
      }

/*:344*/
      ;
    } else {
      state = new_line;
/*360:*/

      if (name > 17) /*362:*/

      {
        incr(line);
        first = start;
        if (!force_eof) {
          if (input_ln(&cur_file, true))
            firm_up_the_line();
          else
            force_eof = true;
        }
        if (force_eof) {
          print_char(')');
          decr(open_parens);
          update_terminal;
          force_eof = false;
          end_file_reading();
          check_outer_validity();
          goto restart;
        }
        if (end_line_char_inactive)
          decr(limit);
        else
          buffer[limit] = end_line_char;
        first = limit + 1;
        loc = start;
      }
/*:362*/

      else {
        if (!terminal_input) {
          cur_cmd = 0;
          cur_chr = 0;
          return;
        }
        if (input_ptr > 0) {
          end_file_reading();
          goto restart;
        }
        if (selector < log_only) open_log_file();
        if (interaction > nonstop_mode) {
          if (end_line_char_inactive) incr(limit);
          if (limit == start)
            print_nl("(Please type a command or say `\\end')");

          print_ln();
          first = start;
          prompt_input("*");

          limit = last;
          if (end_line_char_inactive)
            decr(limit);
          else
            buffer[limit] = end_line_char;
          first = limit + 1;
          loc = start;
        } else
          fatal_error("*** (job aborted, no legal \\end found)");
      }

/*:360*/
      ;
      check_interrupt;
      goto get_cur_chr;
    }
  }
/*:343*/

  else /*357:*/

      if (loc != null)

  {
    t = info(loc);
    loc = link(loc);
    if (t >= cs_token_flag) {
      cur_cs = t - cs_token_flag;
      cur_cmd = eq_type(cur_cs);
      cur_chr = equiv(cur_cs);
      if (cur_cmd >= outer_call)
        if (cur_cmd == dont_expand)
/*358:*/

        {
          cur_cs = info(loc) - cs_token_flag;
          loc = null;
          cur_cmd = eq_type(cur_cs);
          cur_chr = equiv(cur_cs);
          if (cur_cmd > max_command) {
            cur_cmd = relax;
            cur_chr = no_expand_flag;
          }
        }

/*:358*/

        else
          check_outer_validity();
    } else {
      cur_cmd = t / 0400;
      cur_chr = t % 0400;
      switch (cur_cmd) {
        case left_brace:
          incr(align_state);
          break;
        case right_brace:
          decr(align_state);
          break;
        case out_param: /*359:*/

        {
          begin_token_list(param_stack[param_start + cur_chr - 1], parameter);
          goto restart;
        }

/*:359*/

        default:
          do_nothing;
      }
    }
  } else {
    end_token_list();
    goto restart;
  }

/*:357*/
  ;
/*342:*/

  if (cur_cmd <= car_ret)
    if (cur_cmd >= tab_mark)
      if (align_state == 0)
/*789:*/

      {
        if ((scanner_status == aligning) || (cur_align == null))
          fatal_error("(interwoven alignment preambles are not allowed)");

        cur_cmd = extra_info(cur_align);
        extra_info(cur_align) = cur_chr;
        if (cur_cmd == omit)
          begin_token_list(omit_template, v_template);
        else
          begin_token_list(v_part(cur_align), v_template);
        align_state = 1000000;
        goto restart;
      }

/*:789*/

/*:342*/
      ;
}

/*:341*/ /*363:*/
void firm_up_the_line(void) {
  int k;
  limit = last;
  if (pausing > 0)
    if (interaction > nonstop_mode) {
      wake_up_terminal;
      print_ln();
      if (start < limit)
        for (k = start; k <= limit - 1; k++) print(buffer[k]);
      first = limit;
      prompt_input("=>");

      if (last > first) {
        for (k = first; k <= last - 1; k++)
          buffer[k + start - first] = buffer[k];
        limit = start + last - first;
      }
    }
}

/*:363*/ /*365:*/
void get_token(void) {
  no_new_control_sequence = false;
  get_next();
  no_new_control_sequence = true;

  if (cur_cs == 0)
    cur_tok = (cur_cmd * 0400) + cur_chr;
  else
    cur_tok = cs_token_flag + cur_cs;
}

/*:365*/ /*366:*/
/*389:*/

void macro_call(void) {
  pointer r;
  pointer p;
  pointer q;
  pointer s;
  pointer t;
  pointer u, v;
  pointer rbrace_ptr;
  small_number n;
  halfword unbalance;
  int m;
  pointer ref_count;
  small_number save_scanner_status;
  pointer save_warning_index;
  ASCII_code match_chr;
  save_scanner_status = scanner_status;
  save_warning_index = warning_index;
  warning_index = cur_cs;
  ref_count = cur_chr;
  r = link(ref_count);
  n = 0;
  if (tracing_macros > 0) /*401:*/

  {
    begin_diagnostic();
    print_ln();
    print_cs(warning_index);
    token_show(ref_count);
    end_diagnostic(false);
  }

/*:401*/
  ;
  if (info(r) != end_match_token)
/*391:*/

  {
    scanner_status = matching;
    unbalance = 0;
    long_state = eq_type(cur_cs);
    if (long_state >= outer_call) long_state = long_state - 2;
    do {
      link(temp_head) = null;
      if ((info(r) > match_token + 255) || (info(r) < match_token))
        s = null;
      else {
        match_chr = info(r) - match_token;
        s = link(r);
        r = s;
        p = temp_head;
        m = 0;
      }
/*392:*/

    resume:
      get_token();
      if (cur_tok == info(r))
/*394:*/

      {
        r = link(r);
        if ((info(r) >= match_token) && (info(r) <= end_match_token)) {
          if (cur_tok < left_brace_limit) decr(align_state);
          goto found;
        } else
          goto resume;
      }

/*:394*/
      ;
/*397:*/

      if (s != r)
        if (s == null) /*398:*/

        {
          print_err("Use of ");
          sprint_cs(warning_index);

          print_str(" doesn't match its definition");
          help4("If you say, e.g., `\\def\\a1{...}', then you must always")(
              "put `1' after `\\a', since control sequence names are")(
              "made up of letters only. The macro here has not been")(
              "followed by the required stuff, so I'm ignoring it.");
          error();
          goto end;
        }
/*:398*/

        else {
          t = s;
          do {
            store_new_token(info(t));
            incr(m);
            u = link(t);
            v = s;
            loop {
              if (u == r)
                if (cur_tok != info(v))
                  goto done;
                else {
                  r = link(v);
                  goto resume;
                }
              if (info(u) != info(v)) goto done;
              u = link(u);
              v = link(v);
            }
          done:
            t = link(t);
          } while (!(t == r));
          r = s;
        }

/*:397*/
        ;
      if (cur_tok == par_token)
        if (long_state != long_call)
/*396:*/

        {
          if (long_state == call) {
            runaway();
            print_err("Paragraph ended before ");

            sprint_cs(warning_index);
            print_str(" was complete");
            help3("I suspect you've forgotten a `}', causing me to apply this")(
                "control sequence to too much text. How can we recover?")(
                "My plan is to forget the whole thing and hope for the best.");
            back_error();
          }
          pstack[n] = link(temp_head);
          align_state = align_state - unbalance;
          for (m = 0; m <= n; m++) flush_list(pstack[m]);
          goto end;
        }

/*:396*/
        ;
      if (cur_tok < right_brace_limit)
        if (cur_tok < left_brace_limit)
/*399:*/

        {
          unbalance = 1;

          loop {
            fast_store_new_token(cur_tok);
            get_token();
            if (cur_tok == par_token)
              if (long_state != long_call)
/*396:*/

              {
                if (long_state == call) {
                  runaway();
                  print_err("Paragraph ended before ");

                  sprint_cs(warning_index);
                  print_str(" was complete");
                  help3(
                      "I suspect you've forgotten a `}', causing me to apply "
                      "this")(
                      "control sequence to too much text. How can we recover?")(
                      "My plan is to forget the whole thing and hope for the "
                      "best.");
                  back_error();
                }
                pstack[n] = link(temp_head);
                align_state = align_state - unbalance;
                for (m = 0; m <= n; m++) flush_list(pstack[m]);
                goto end;
              }

/*:396*/
              ;
            if (cur_tok < right_brace_limit)
              if (cur_tok < left_brace_limit)
                incr(unbalance);
              else {
                decr(unbalance);
                if (unbalance == 0) goto done1;
              }
          }
        done1:
          rbrace_ptr = p;
          store_new_token(cur_tok);
        }
/*:399*/

        else /*395:*/

        {
          back_input();
          print_err("Argument of ");
          sprint_cs(warning_index);

          print_str(" has an extra }");
          help6("I've run across a `}' that doesn't seem to match anything.")(
              "For example, `\\def\\a#1{...}' and `\\a}' would produce")(
              "this error. If you simply proceed now, the `\\par' that")(
              "I've just inserted will cause me to report a runaway")(
              "argument that might be the root of the problem. But if")(
              "your `}' was spurious, just type `2' and it will go away.");
          incr(align_state);
          long_state = call;
          cur_tok = par_token;
          ins_error();
          goto resume;
        }

/*:395*/

      else /*393:*/

      {
        if (cur_tok == space_token)
          if (info(r) <= end_match_token)
            if (info(r) >= match_token) goto resume;
        store_new_token(cur_tok);
      }

/*:393*/
      ;
      incr(m);
      if (info(r) > end_match_token) goto resume;
      if (info(r) < match_token) goto resume;
    found:
      if (s != null) /*400:*/

      {
        if ((m == 1) && (info(p) < right_brace_limit)) {
          link(rbrace_ptr) = null;
          free_avail(p);
          p = link(temp_head);
          pstack[n] = link(p);
          free_avail(p);
        } else
          pstack[n] = link(temp_head);
        incr(n);
        if (tracing_macros > 0) {
          begin_diagnostic();
          print_nl("");
          print(match_chr);
          print_int(n);
          print_str("<-");
          show_token_list(pstack[n - 1], null, 1000);
          end_diagnostic(false);
        }
      }

/*:400*/

/*:392*/
      ;

    } while (!(info(r) == end_match_token));
  }

/*:391*/
  ;
/*390:*/

  while ((state == token_list) && (loc == null) && (token_type != v_template))
    end_token_list();
  begin_token_list(ref_count, macro);
  name = warning_index;
  loc = link(r);
  if (n > 0) {
    if (param_ptr + n > max_param_stack) {
      max_param_stack = param_ptr + n;
      if (max_param_stack > param_size)
        overflow("parameter stack size", param_size);
    }
    for (m = 0; m <= n - 1; m++) param_stack[param_ptr + m] = pstack[m];
    param_ptr = param_ptr + n;
  }

/*:390*/
  ;
end:
  scanner_status = save_scanner_status;
  warning_index = save_warning_index;
}

/*:389*/

/*379:*/

void insert_relax(void) {
  cur_tok = cs_token_flag + cur_cs;
  back_input();
  cur_tok = cs_token_flag + frozen_relax;
  back_input();
  token_type = inserted;
}

/*:379*/

void pass_text(void);
void start_input(void);
void conditional(void);
void get_x_token(void);
void conv_toks(void);
void ins_the_toks(void);
void expand(void) {
  halfword t;
  pointer p, q, r;
  uint16_t j;
  int cv_backup;
  small_number cvl_backup, radix_backup, co_backup;

  pointer backup_backup;
  small_number save_scanner_status;
  cv_backup = cur_val;
  cvl_backup = cur_val_level;
  radix_backup = radix;
  co_backup = cur_order;
  backup_backup = link(backup_head);
  if (cur_cmd < call) /*367:*/

  {
    if (tracing_commands > 1) show_cur_cmd_chr();
    switch (cur_cmd) {
      case top_bot_mark: /*386:*/

      {
        if (cur_mark[cur_chr] != null)
          begin_token_list(cur_mark[cur_chr], mark_text);
      }

/*:386*/
      break;
      case expand_after: /*368:*/

      {
        get_token();
        t = cur_tok;
        get_token();
        if (cur_cmd > max_command)
          expand();
        else
          back_input();
        cur_tok = t;
        back_input();
      }

/*:368*/
      break;
      case no_expand: /*369:*/

      {
        save_scanner_status = scanner_status;
        scanner_status = normal;
        get_token();
        scanner_status = save_scanner_status;
        t = cur_tok;
        back_input();
        if (t >= cs_token_flag) {
          p = get_avail();
          info(p) = cs_token_flag + frozen_dont_expand;
          link(p) = loc;
          start = p;
          loc = p;
        }
      }

/*:369*/
      break;
      case cs_name: /*372:*/

      {
        r = get_avail();
        p = r;
        do {
          get_x_token();
          if (cur_cs == 0) store_new_token(cur_tok);
        } while (!(cur_cs != 0));
        if (cur_cmd != end_cs_name) /*373:*/

        {
          print_err("Missing ");
          print_esc(/*1527:*/
                    402
/*:1527*/
          );
          print_str(" inserted");

          help2("The control sequence marked <to be read again> should")(
              "not appear between \\csname and \\endcsname.");
          back_error();
        }

/*:373*/
        ;
/*374:*/

        j = first;
        p = link(r);
        while (p != null) {
          if (j >= max_buf_stack) {
            max_buf_stack = j + 1;
            if (max_buf_stack == buf_size) overflow("buffer size", buf_size);
          }
          buffer[j] = info(p) % 0400;
          incr(j);
          p = link(p);
        }
        if (j > first + 1) {
          no_new_control_sequence = false;
          cur_cs = id_lookup(first, j - first);
          no_new_control_sequence = true;
        } else if (j == first)
          cur_cs = null_cs;
        else
          cur_cs = single_base + buffer[first]

/*:374*/
              ;
        flush_list(r);
        if (eq_type(cur_cs) == undefined_cs) {
          eq_define(cur_cs, relax, 256);
        }
        cur_tok = cur_cs + cs_token_flag;
        back_input();
      }

/*:372*/
      break;
      case convert:
        conv_toks();
        break;
      case the:
        ins_the_toks();
        break;
      case if_test:
        conditional();
        break;
      case fi_or_else: /*510:*/

        if (cur_chr > if_limit)
          if (if_limit == if_code)
            insert_relax();
          else {
            print_err("Extra ");
            print_cmd_chr(fi_or_else, cur_chr);

            help1("I'm ignoring this; it doesn't match any \\if.");
            error();
          }
        else {
          while (cur_chr != fi_code) pass_text();
/*496:*/

          {
            p = cond_ptr;
            if_line = if_line_field(p);
            cur_if = subtype(p);
            if_limit = type(p);
            cond_ptr = link(p);
            free_node(p, if_node_size);
          }

/*:496*/
          ;
        }

/*:510*/
        break;
      case input: /*378:*/

        if (cur_chr > 0)
          force_eof = true;
        else if (name_in_progress)
          insert_relax();
        else
          start_input()

/*:378*/
              ;
        break;
      default: /*370:*/

      {
        print_err("Undefined control sequence");

        help5("The control sequence at the end of the top line")(
            "of your error message was never \\def'ed. If you have")(
            "misspelled it (e.g., `\\hobx'), type `I' and the correct")(
            "spelling (e.g., `I\\hbox'). Otherwise just continue,")(
            "and I'll forget about whatever was undefined.");
        error();
      }

/*:370*/
    }
  }

/*:367*/

  else if (cur_cmd < end_template)
    macro_call();
  else /*375:*/

  {
    cur_tok = cs_token_flag + frozen_endv;
    back_input();
  }

/*:375*/
  ;
  cur_val = cv_backup;
  cur_val_level = cvl_backup;
  radix = radix_backup;
  cur_order = co_backup;
  link(backup_head) = backup_backup;
}

/*:366*/ /*380:*/
void get_x_token(void)

{
restart:
  get_next();

  if (cur_cmd <= max_command) goto done;
  if (cur_cmd >= call)
    if (cur_cmd < end_template)
      macro_call();
    else {
      cur_cs = frozen_endv;
      cur_cmd = endv;
      goto done;
    }
  else
    expand();
  goto restart;
done:
  if (cur_cs == 0)
    cur_tok = (cur_cmd * 0400) + cur_chr;
  else
    cur_tok = cs_token_flag + cur_cs;
}

/*:380*/ /*381:*/
void x_token(void) {
  while (cur_cmd > max_command) {
    expand();
    get_next();
  }
  if (cur_cs == 0)
    cur_tok = (cur_cmd * 0400) + cur_chr;
  else
    cur_tok = cs_token_flag + cur_cs;
}

/*:381*/ /*403:*/
void scan_left_brace(void) { /*404:*/

  do {
    get_x_token();
  } while (!((cur_cmd != spacer) && (cur_cmd != relax)))

/*:404*/
      ;
  if (cur_cmd != left_brace) {
    print_err("Missing { inserted");

    help4("A left brace was mandatory here, so I've put one in.")(
        "You might want to delete and/or insert some corrections")(
        "so that I will find a matching right brace soon.")(
        "(If you're confused by all this, try typing `I}' now.)");
    back_error();
    cur_tok = left_brace_token + '{';
    cur_cmd = left_brace;
    cur_chr = '{';
    incr(align_state);
  }
}

/*:403*/ /*405:*/
void scan_optional_equals(void) { /*406:*/

  do {
    get_x_token();
  } while (!(cur_cmd != spacer))

/*:406*/
      ;
  if (cur_tok != other_token + '=') back_input();
}

/*:405*/ /*407:*/
bool scan_keyword(str_number s) {
  pointer p;
  pointer q;
  pool_pointer k;
  p = backup_head;
  link(p) = null;
  k = str_start[s];
  while (k < str_start[s + 1]) {
    get_x_token();

    if ((cur_cs == 0) && ((cur_chr == so(str_pool[k])) ||
                          (cur_chr == so(str_pool[k]) - 'a' + 'A'))) {
      store_new_token(cur_tok);
      incr(k);
    } else if ((cur_cmd != spacer) || (p != backup_head)) {
      back_input();
      if (p != backup_head) back_list(link(backup_head));
      return false;
    }
  }
  flush_list(link(backup_head));
  return true;
}

/*:407*/ /*408:*/
void mu_error(void) {
  print_err("Incompatible glue units");

  help1("I'm going to assume that 1mu=1pt when they're mixed.");
  error();
}

/*:408*/ /*409:*/
void scan_int(void);
/*433:*/

void scan_eight_bit_int(void) {
  scan_int();
  if ((cur_val < 0) || (cur_val > 255)) {
    print_err("Bad register code");

    help2("A register number must be between 0 and 255.")(
        "I changed this one to zero.");
    int_error(cur_val);
    cur_val = 0;
  }
}

/*:433*/ /*434:*/

void scan_char_num(void) {
  scan_int();
  if ((cur_val < 0) || (cur_val > 255)) {
    print_err("Bad character code");

    help2("A character number must be between 0 and 255.")(
        "I changed this one to zero.");
    int_error(cur_val);
    cur_val = 0;
  }
}

/*:434*/ /*435:*/

void scan_four_bit_int(void) {
  scan_int();
  if ((cur_val < 0) || (cur_val > 15)) {
    print_err("Bad number");

    help2("Since I expected to read a number between 0 and 15,")(
        "I changed this one to zero.");
    int_error(cur_val);
    cur_val = 0;
  }
}

/*:435*/ /*436:*/

void scan_fifteen_bit_int(void) {
  scan_int();
  if ((cur_val < 0) || (cur_val > 077777)) {
    print_err("Bad mathchar");

    help2("A mathchar number must be between 0 and 32767.")(
        "I changed this one to zero.");
    int_error(cur_val);
    cur_val = 0;
  }
}

/*:436*/ /*437:*/

void scan_twenty_seven_bit_int(void) {
  scan_int();
  if ((cur_val < 0) || (cur_val > 0777777777)) {
    print_err("Bad delimiter code");

    help2("A numeric delimiter code must be between 0 and 2^{27}-1.")(
        "I changed this one to zero.");
    int_error(cur_val);
    cur_val = 0;
  }
}

/*:437*/

/*577:*/

void scan_font_ident(void) {
  internal_font_number f;
  halfword m;
/*406:*/

  do {
    get_x_token();
  } while (!(cur_cmd != spacer))

/*:406*/
      ;
  if (cur_cmd == def_font)
    f = cur_font;
  else if (cur_cmd == set_font)
    f = cur_chr;
  else if (cur_cmd == def_family) {
    m = cur_chr;
    scan_four_bit_int();
    f = equiv(m + cur_val);
  } else {
    print_err("Missing font identifier");

    help2("I was looking for a control sequence whose")(
        "current meaning has been defined by \\font.");
    back_error();
    f = null_font;
  }
  cur_val = f;
}

/*:577*/ /*578:*/

void find_font_dimen(bool writing)

{
  internal_font_number f;
  int n;
  scan_int();
  n = cur_val;
  scan_font_ident();
  f = cur_val;
  if (n <= 0)
    cur_val = fmem_ptr;
  else {
    if (writing && (n <= space_shrink_code) && (n >= space_code) &&
        (font_glue[f] != null)) {
      delete_glue_ref(font_glue[f]);
      font_glue[f] = null;
    }
    if (n > font_params[f])
      if (f < font_ptr)
        cur_val = fmem_ptr;
      else /*580:*/

      {
        do {
          if (fmem_ptr == font_mem_size) overflow("font memory", font_mem_size);

          font_info[fmem_ptr].sc = 0;
          incr(fmem_ptr);
          incr(font_params[f]);
        } while (!(n == font_params[f]));
        cur_val = fmem_ptr - 1;
      }

/*:580*/

    else
      cur_val = n + param_base[f];
  }
/*579:*/

  if (cur_val == fmem_ptr) {
    print_err("Font ");
    print_esc(font_id_text(f));
    print_str(" has only ");
    print_int(font_params[f]);
    print_str(" fontdimen parameters");

    help2("To increase the number of font parameters, you must")(
        "use \\fontdimen immediately after the \\font is loaded.");
    error();
  }

/*:579*/
  ;
}

/*:578*/

/*:409*/ /*413:*/
void scan_something_internal(small_number level, bool negative)

{
  halfword m;
  uint8_t p;
  m = cur_chr;
  switch (cur_cmd) {
    case def_code: /*414:*/

    {
      scan_char_num();
      if (m == math_code_base)
        scanned_result(ho(math_code(cur_val)))(int_val) else if (m <
                                                                 math_code_base)
            scanned_result(equiv(m + cur_val))(int_val) else scanned_result(
                eqtb[m + cur_val].i)(int_val);
    }

/*:414*/
    break;
    case toks_register:
    case assign_toks:
    case def_family:
    case set_font:
    case def_font: /*415:*/

      if (level != tok_val) {
        print_err("Missing number, treated as zero");

        help3("A number should have been here; I inserted `0'.")(
            "(If you can't figure out why I needed to see a number,")(
            "look up `weird error' in the index to The TeXbook.)");

        back_error();
        scanned_result(0)(dimen_val);
      } else if (cur_cmd <= assign_toks) {
        if (cur_cmd < assign_toks) {
          scan_eight_bit_int();
          m = toks_base + cur_val;
        }
        scanned_result(equiv(m))(tok_val);
      } else {
        back_input();
        scan_font_ident();
        scanned_result(font_id_base + cur_val)(ident_val);
      }

/*:415*/
      break;
    case assign_int:
      scanned_result(eqtb[m].i)(int_val) break;
    case assign_dimen:
      scanned_result(eqtb[m].sc)(dimen_val) break;
    case assign_glue:
      scanned_result(equiv(m))(glue_val) break;
    case assign_mu_glue:
      scanned_result(equiv(m))(mu_val) break;
    case set_aux: /*418:*/

      if (abs(mode) != m) {
        print_err("Improper ");
        print_cmd_chr(set_aux, m);

        help4("You can refer to \\spacefactor only in horizontal mode;")(
            "you can refer to \\prevdepth only in vertical mode; and")(
            "neither of these is meaningful inside \\write. So")(
            "I'm forgetting what you said and using zero instead.");
        error();
        if (level != tok_val)
          scanned_result(0)(dimen_val) else scanned_result(0)(int_val);
      } else if (m == vmode)
        scanned_result(prev_depth)(dimen_val) else scanned_result(space_factor)(
            int_val)

/*:418*/
            break;
    case set_prev_graf: /*422:*/

      if (mode == 0) scanned_result(0)(int_val) else {
          nest[nest_ptr] = cur_list;
          p = nest_ptr;
          while (abs(nest[p].mode_field) != vmode) decr(p);
          scanned_result(nest[p].pg_field)(int_val);
        }

/*:422*/
      break;
    case set_page_int: /*419:*/

    {
      if (m == 0)
        cur_val = dead_cycles;
      else
        cur_val = insert_penalties;
      cur_val_level = int_val;
    }

/*:419*/
    break;
    case set_page_dimen: /*421:*/

    {
      if ((page_contents == empty) && (!output_active))
        if (m == 0)
          cur_val = max_dimen;
        else
          cur_val = 0;
      else
        cur_val = page_so_far[m];
      cur_val_level = dimen_val;
    }

/*:421*/
    break;
    case set_shape: /*423:*/

    {
      if (par_shape_ptr == null)
        cur_val = 0;
      else
        cur_val = info(par_shape_ptr);
      cur_val_level = int_val;
    }

/*:423*/
    break;
    case set_box_dimen: /*420:*/

    {
      scan_eight_bit_int();
      if (box(cur_val) == null)
        cur_val = 0;
      else
        cur_val = mem[box(cur_val) + m].sc;
      cur_val_level = dimen_val;
    }

/*:420*/
    break;
    case char_given:
    case math_given:
      scanned_result(cur_chr)(int_val) break;
    case assign_font_dimen: /*425:*/

    {
      find_font_dimen(false);
      font_info[fmem_ptr].sc = 0;
      scanned_result(font_info[cur_val].sc)(dimen_val);
    }

/*:425*/
    break;
    case assign_font_int: /*426:*/

    {
      scan_font_ident();
      if (m == 0)
        scanned_result(hyphen_char[cur_val])(int_val) else scanned_result(
            skew_char[cur_val])(int_val);
    }

/*:426*/
    break;
    case register: /*427:*/

    {
      scan_eight_bit_int();
      switch (m) {
        case int_val:
          cur_val = count(cur_val);
          break;
        case dimen_val:
          cur_val = dimen(cur_val);
          break;
        case glue_val:
          cur_val = skip(cur_val);
          break;
        case mu_val:
          cur_val = mu_skip(cur_val);
      }
      cur_val_level = m;
    }

/*:427*/
    break;
    case last_item: /*424:*/

      if (cur_chr > glue_val) {
        if (cur_chr == input_line_no_code)
          cur_val = line;
        else
          cur_val = last_badness;
        cur_val_level = int_val;
      } else {
        if (cur_chr == glue_val)
          cur_val = zero_glue;
        else
          cur_val = 0;
        cur_val_level = cur_chr;
        if (!is_char_node(tail) && (mode != 0)) switch (cur_chr) {
            case int_val:
              if (type(tail) == penalty_node) cur_val = penalty(tail);
              break;
            case dimen_val:
              if (type(tail) == kern_node) cur_val = width(tail);
              break;
            case glue_val:
              if (type(tail) == glue_node) {
                cur_val = glue_ptr(tail);
                if (subtype(tail) == mu_glue) cur_val_level = mu_val;
              }
          }
        else if ((mode == vmode) && (tail == head))
          switch (cur_chr) {
            case int_val:
              cur_val = last_penalty;
              break;
            case dimen_val:
              cur_val = last_kern;
              break;
            case glue_val:
              if (last_glue != max_halfword) cur_val = last_glue;
          }
      }

/*:424*/
      break;
    default: /*428:*/

    {
      print_err("You can't use `");
      print_cmd_chr(cur_cmd, cur_chr);

      print_str("' after ");
      print_esc(/*1559:*/
                434
/*:1559*/
      );
      help1("I'm forgetting what you said and using zero instead.");
      error();
      if (level != tok_val)
        scanned_result(0)(dimen_val) else scanned_result(0)(int_val);
    }

/*:428*/
  }
  while (cur_val_level > level) /*429:*/

  {
    if (cur_val_level == glue_val)
      cur_val = width(cur_val);
    else if (cur_val_level == mu_val)
      mu_error();
    decr(cur_val_level);
  }

/*:429*/
  ;
/*430:*/

  if (negative)
    if (cur_val_level >= glue_val) {
      cur_val = new_spec(cur_val);
/*431:*/

      {
        negate(width(cur_val));
        negate(stretch(cur_val));
        negate(shrink(cur_val));
      }

/*:431*/
      ;
    } else
      negate(cur_val);
  else if ((cur_val_level >= glue_val) && (cur_val_level <= mu_val))
    add_glue_ref(cur_val)

/*:430*/
        ;
}

/*:413*/ /*440:*/
void scan_int(void) {
  bool negative;
  int m;
  small_number d;
  bool vacuous;
  bool OK_so_far;
  radix = 0;
  OK_so_far = true;
/*441:*/

  negative = false;
  do { /*406:*/

    do {
      get_x_token();
    } while (!(cur_cmd != spacer))

/*:406*/
        ;
    if (cur_tok == other_token + '-') {
      negative = !negative;
      cur_tok = other_token + '+';
    }
  } while (!(cur_tok != other_token + '+'))

/*:441*/
      ;
  if (cur_tok == alpha_token) /*442:*/

  {
    get_token();
    if (cur_tok < cs_token_flag) {
      cur_val = cur_chr;
      if (cur_cmd <= right_brace)
        if (cur_cmd == right_brace)
          incr(align_state);
        else
          decr(align_state);
    } else if (cur_tok < cs_token_flag + single_base)
      cur_val = cur_tok - cs_token_flag - active_base;
    else
      cur_val = cur_tok - cs_token_flag - single_base;
    if (cur_val > 255) {
      print_err("Improper alphabetic constant");

      help2("A one-character control sequence belongs after a ` mark.")(
          "So I'm essentially inserting \\0 here.");
      cur_val = '0';
      back_error();
    } else /*443:*/

    {
      get_x_token();
      if (cur_cmd != spacer) back_input();
    }

/*:443*/
    ;
  }

/*:442*/

  else if ((cur_cmd >= min_internal) && (cur_cmd <= max_internal))
    scan_something_internal(int_val, false);
  else /*444:*/

  {
    radix = 10;
    m = 214748364;
    if (cur_tok == octal_token) {
      radix = 8;
      m = 02000000000;
      get_x_token();
    } else if (cur_tok == hex_token) {
      radix = 16;
      m = 01000000000;
      get_x_token();
    }
    vacuous = true;
    cur_val = 0;
/*445:*/

    loop {
      if ((cur_tok < zero_token + radix) && (cur_tok >= zero_token) &&
          (cur_tok <= zero_token + 9))
        d = cur_tok - zero_token;
      else if (radix == 16)
        if ((cur_tok <= A_token + 5) && (cur_tok >= A_token))
          d = cur_tok - A_token + 10;
        else if ((cur_tok <= other_A_token + 5) && (cur_tok >= other_A_token))
          d = cur_tok - other_A_token + 10;
        else
          goto done;
      else
        goto done;
      vacuous = false;
      if ((cur_val >= m) && ((cur_val > m) || (d > 7) || (radix != 10))) {
        if (OK_so_far) {
          print_err("Number too big");

          help2("I can only go up to 2147483647='17777777777=\"7FFFFFFF,")(
              "so I'm using that number instead of yours.");
          error();
          cur_val = infinity;
          OK_so_far = false;
        }
      } else
        cur_val = cur_val * radix + d;
      get_x_token();
    }
  done:

/*:445*/
      ;
    if (vacuous) /*446:*/

    {
      print_err("Missing number, treated as zero");

      help3("A number should have been here; I inserted `0'.")(
          "(If you can't figure out why I needed to see a number,")(
          "look up `weird error' in the index to The TeXbook.)");

      back_error();
    }

/*:446*/

    else if (cur_cmd != spacer)
      back_input();
  }

/*:444*/
  ;
  if (negative) negate(cur_val);
}

/*:440*/ /*448:*/
void scan_dimen(bool mu, bool inf, bool shortcut)

{
  bool negative;
  int f;
/*450:*/

  uint32_t num, denom;
  int k, kk;
  pointer p, q;
  scaled v;
  int save_cur_val;

/*:450*/

  f = 0;
  arith_error = false;
  cur_order = normal;
  negative = false;
  if (!shortcut) { /*441:*/

    negative = false;
    do { /*406:*/

      do {
        get_x_token();
      } while (!(cur_cmd != spacer))

/*:406*/
          ;
      if (cur_tok == other_token + '-') {
        negative = !negative;
        cur_tok = other_token + '+';
      }
    } while (!(cur_tok != other_token + '+'))

/*:441*/
        ;
    if ((cur_cmd >= min_internal) && (cur_cmd <= max_internal)) /*449:*/

      if (mu) {
        scan_something_internal(mu_val, false);
/*451:*/

        if (cur_val_level >= glue_val) {
          v = width(cur_val);
          delete_glue_ref(cur_val);
          cur_val = v;
        }

/*:451*/
        ;
        if (cur_val_level == mu_val) goto attach_sign;
        if (cur_val_level != int_val) mu_error();
      } else {
        scan_something_internal(dimen_val, false);
        if (cur_val_level == dimen_val) goto attach_sign;
      }

/*:449*/

    else {
      back_input();
      if (cur_tok == continental_point_token) cur_tok = point_token;
      if (cur_tok != point_token)
        scan_int();
      else {
        radix = 10;
        cur_val = 0;
      }
      if (cur_tok == continental_point_token) cur_tok = point_token;
      if ((radix == 10) && (cur_tok == point_token)) /*452:*/

      {
        k = 0;
        p = null;
        get_token();
        loop {
          get_x_token();
          if ((cur_tok > zero_token + 9) || (cur_tok < zero_token)) goto done1;
          if (k < 17) {
            q = get_avail();
            link(q) = p;
            info(q) = cur_tok - zero_token;
            p = q;
            incr(k);
          }
        }
      done1:
        for (kk = k; kk >= 1; kk--) {
          dig[kk - 1] = info(p);
          q = p;
          p = link(p);
          free_avail(q);
        }
        f = round_decimals(k);
        if (cur_cmd != spacer) back_input();
      }

/*:452*/
      ;
    }
  }
  if (cur_val < 0) {
    negative = !negative;
    negate(cur_val);
  }
/*453:*/

  if (inf) /*454:*/

    if (scan_keyword(/*1387:*/
                     262
/*:1387*/
                     ))

    {
      cur_order = fil;
      while (scan_keyword('l')) {
        if (cur_order == filll) {
          print_err("Illegal unit of measure (");

          print_str("replaced by filll)");
          help1("I dddon't go any higher than filll.");
          error();
        } else
          incr(cur_order);
      }
      goto attach_fraction;
    }

/*:454*/
    ;
/*455:*/

  save_cur_val = cur_val;
/*406:*/

  do {
    get_x_token();
  } while (!(cur_cmd != spacer))

/*:406*/
      ;
  if ((cur_cmd < min_internal) || (cur_cmd > max_internal))
    back_input();
  else {
    if (mu) {
      scan_something_internal(mu_val, false); /*451:*/

      if (cur_val_level >= glue_val) {
        v = width(cur_val);
        delete_glue_ref(cur_val);
        cur_val = v;
      }

/*:451*/
      ;
      if (cur_val_level != mu_val) mu_error();
    } else
      scan_something_internal(dimen_val, false);
    v = cur_val;
    goto found;
  }
  if (mu) goto not_found;
  if (scan_keyword(/*1590:*/
                   465
/*:1590*/
                   ))
    v = (/*558:*/
         quad(cur_font)

/*:558*/
    );

  else if (scan_keyword(/*1591:*/
                        466
/*:1591*/
                        ))
    v = (/*559:*/
         x_height(cur_font)

/*:559*/
    );

  else
    goto not_found;
/*443:*/

  {
    get_x_token();
    if (cur_cmd != spacer) back_input();
  }

/*:443*/
  ;
found:
  cur_val = nx_plus_y(save_cur_val, v, xn_over_d(v, f, 0200000));
  goto attach_sign;
not_found:

/*:455*/
    ;
  if (mu) /*456:*/

    if (scan_keyword(/*1394:*/
                     269
/*:1394*/
                     ))
      goto attach_fraction;

    else {
      print_err("Illegal unit of measure (");
      print_str("mu inserted)");

      help4("The unit of measurement in math glue must be mu.")(
          "To recover gracefully from this error, it's best to")(
          "delete the erroneous units; e.g., type `2' to delete")(
          "two letters. (See Chapter 27 of The TeXbook.)");

      error();
      goto attach_fraction;
    }

/*:456*/
    ;
  if (scan_keyword(/*1589:*/
                   464
/*:1589*/
                   )) /*457:*/

  {
    prepare_mag();
    if (mag != 1000) {
      cur_val = xn_over_d(cur_val, 1000, mag);
      f = (1000 * f + 0200000 * rem) / mag;
      cur_val = cur_val + (f / 0200000);
      f = f % 0200000;
    }
  }

/*:457*/
  ;

  if (scan_keyword(/*1425:*/
                   300
/*:1425*/
                   ))
    goto attach_fraction;

/*458:*/

  if (scan_keyword(/*1592:*/
                   467
/*:1592*/
                   ))
    set_conversion(7227)(100)

        else if (scan_keyword(/*1593:*/
                              468
/*:1593*/
                              )) set_conversion(12)(1)

            else if (scan_keyword(/*1594:*/
                                  469
/*:1594*/
                                  )) set_conversion(7227)(254)

                else if (scan_keyword(/*1595:*/
                                      470
/*:1595*/
                                      )) set_conversion(7227)(2540)

                    else if (scan_keyword(/*1596:*/
                                          471
/*:1596*/
                                          )) set_conversion(7227)(7200)

                        else if (scan_keyword(/*1597:*/
                                              472
/*:1597*/
                                              )) set_conversion(1238)(1157)

                            else if (scan_keyword(/*1598:*/
                                                  473
/*:1598*/
                                                  )) set_conversion(14856)(1157)

                                else if (scan_keyword(/*1599:*/
                                                      474
/*:1599*/
                                                      )) goto done;

  else /*459:*/

  {
    print_err("Illegal unit of measure (");
    print_str("pt inserted)");

    help6("Dimensions can be in units of em, ex, in, pt, pc,")(
        "cm, mm, dd, cc, bp, or sp; but yours is a new one!")(
        "I'll assume that you meant to say pt, for printer's points.")(
        "To recover gracefully from this error, it's best to")(
        "delete the erroneous units; e.g., type `2' to delete")(
        "two letters. (See Chapter 27 of The TeXbook.)");

    error();
    goto done2;
  }

/*:459*/
  ;
  cur_val = xn_over_d(cur_val, num, denom);
  f = (num * f + 0200000 * rem) / denom;
  cur_val = cur_val + (f / 0200000);
  f = f % 0200000;
done2:

/*:458*/
    ;
attach_fraction:
  if (cur_val >= 040000)
    arith_error = true;
  else
    cur_val = cur_val * unity + f;
done:

/*:453*/
    ;
/*443:*/

  {
    get_x_token();
    if (cur_cmd != spacer) back_input();
  }

/*:443*/
  ;
attach_sign:
  if (arith_error || (abs(cur_val) >= 010000000000))
/*460:*/

  {
    print_err("Dimension too large");

    help2("I can't work with sizes bigger than about 19 feet.")(
        "Continue and I'll use the largest value I can.");
    error();
    cur_val = max_dimen;
    arith_error = false;
  }

/*:460*/
  ;
  if (negative) negate(cur_val);
}

/*:448*/ /*461:*/
void scan_glue(small_number level)

{
  bool negative;
  pointer q;
  bool mu;
  mu = (level == mu_val); /*441:*/

  negative = false;
  do { /*406:*/

    do {
      get_x_token();
    } while (!(cur_cmd != spacer))

/*:406*/
        ;
    if (cur_tok == other_token + '-') {
      negative = !negative;
      cur_tok = other_token + '+';
    }
  } while (!(cur_tok != other_token + '+'))

/*:441*/
      ;
  if ((cur_cmd >= min_internal) && (cur_cmd <= max_internal)) {
    scan_something_internal(level, negative);
    if (cur_val_level >= glue_val) {
      if (cur_val_level != level) mu_error();
      return;
    }
    if (cur_val_level == int_val)
      scan_dimen(mu, false, true);
    else if (level == mu_val)
      mu_error();
  } else {
    back_input();
    scan_dimen(mu, false, false);
    if (negative) negate(cur_val);
  }
/*462:*/

  q = new_spec(zero_glue);
  width(q) = cur_val;
  if (scan_keyword(/*1600:*/
                   475
/*:1600*/
                   ))

  {
    scan_dimen(mu, true, false);
    stretch(q) = cur_val;
    stretch_order(q) = cur_order;
  }
  if (scan_keyword(/*1601:*/
                   476
/*:1601*/
                   ))

  {
    scan_dimen(mu, true, false);
    shrink(q) = cur_val;
    shrink_order(q) = cur_order;
  }
  cur_val = q

/*:462*/
      ;
}

/*:461*/ /*463:*/
pointer scan_rule_spec(void) {
  pointer q;
  q = new_rule();
  if (cur_cmd == vrule)
    width(q) = default_rule;
  else {
    height(q) = default_rule;
    depth(q) = 0;
  }
reswitch:
  if (scan_keyword(/*1602:*/
                   477
/*:1602*/
                   ))

  {
    scan_normal_dimen;
    width(q) = cur_val;
    goto reswitch;
  }
  if (scan_keyword(/*1603:*/
                   478
/*:1603*/
                   ))

  {
    scan_normal_dimen;
    height(q) = cur_val;
    goto reswitch;
  }
  if (scan_keyword(/*1604:*/
                   479
/*:1604*/
                   ))

  {
    scan_normal_dimen;
    depth(q) = cur_val;
    goto reswitch;
  }
  return q;
}

/*:463*/ /*464:*/
pointer str_toks(pool_pointer b)

{
  pointer p;
  pointer q;
  halfword t;
  pool_pointer k;
  str_room(1);
  p = temp_head;
  link(p) = null;
  k = b;
  while (k < pool_ptr) {
    t = so(str_pool[k]);
    if (t == ' ')
      t = space_token;
    else
      t = other_token + t;
    fast_store_new_token(t);
    incr(k);
  }
  pool_ptr = b;
  return p;
}

/*:464*/ /*465:*/
pointer the_toks(void) {
  uint8_t old_setting;
  pointer p, q, r;
  pool_pointer b;
  get_x_token();
  scan_something_internal(tok_val, false);
  if (cur_val_level >= ident_val) /*466:*/

  {
    p = temp_head;
    link(p) = null;
    if (cur_val_level == ident_val)
      store_new_token(cs_token_flag + cur_val) else if (cur_val != null) {
        r = link(cur_val);
        while (r != null) {
          fast_store_new_token(info(r));
          r = link(r);
        }
      }
    return p;
  }
/*:466*/

  else {
    old_setting = selector;
    selector = new_string;
    b = pool_ptr;
    switch (cur_val_level) {
      case int_val:
        print_int(cur_val);
        break;
      case dimen_val: {
        print_scaled(cur_val);
        print_str("pt");
      } break;
      case glue_val: {
        print_spec(cur_val, /*1425:*/
                   300
/*:1425*/
        );
        delete_glue_ref(cur_val);
      } break;
      case mu_val: {
        print_spec(cur_val, /*1394:*/
                   269
/*:1394*/
        );
        delete_glue_ref(cur_val);
      }
    }
    selector = old_setting;
    return str_toks(b);
  }
}

/*:465*/ /*467:*/
void ins_the_toks(void) {
  link(garbage) = the_toks();
  ins_list(link(temp_head));
}

/*:467*/ /*470:*/
void conv_toks(void) {
  uint8_t old_setting;
  uint8_t c;
  small_number save_scanner_status;
  pool_pointer b;
  c = cur_chr; /*471:*/

  switch (c) {
    case number_code:
    case roman_numeral_code:
      scan_int();
      break;
    case string_code:
    case meaning_code: {
      save_scanner_status = scanner_status;
      scanner_status = normal;
      get_token();
      scanner_status = save_scanner_status;
    } break;
    case font_name_code:
      scan_font_ident();
      break;
    case job_name_code:
      if (job_name == 0) open_log_file();
  }

/*:471*/
  ;
  old_setting = selector;
  selector = new_string;
  b = pool_ptr;
/*472:*/

  switch (c) {
    case number_code:
      print_int(cur_val);
      break;
    case roman_numeral_code:
      print_roman_int(cur_val);
      break;
    case string_code:
      if (cur_cs != 0)
        sprint_cs(cur_cs);
      else
        print_char(cur_chr);
      break;
    case meaning_code:
      print_meaning();
      break;
    case font_name_code: {
      print(font_name[cur_val]);
      if (font_size[cur_val] != font_dsize[cur_val]) {
        print_str(" at ");
        print_scaled(font_size[cur_val]);
        print_str("pt");
      }
    } break;
    case job_name_code:
      print(job_name);
  }

/*:472*/
  ;
  selector = old_setting;
  link(garbage) = str_toks(b);
  ins_list(link(temp_head));
}

/*:470*/ /*473:*/
pointer scan_toks(bool macro_def, bool xpand) {
  halfword t;
  halfword s;
  pointer p;
  pointer q;
  halfword unbalance;
  halfword hash_brace;
  if (macro_def)
    scanner_status = defining;
  else
    scanner_status = absorbing;
  warning_index = cur_cs;
  def_ref = get_avail();
  token_ref_count(def_ref) = null;
  p = def_ref;
  hash_brace = 0;
  t = zero_token;
  if (macro_def) /*474:*/

  {
    loop {
    resume:
      get_token();
      if (cur_tok < right_brace_limit) goto done1;
      if (cur_cmd == mac_param)
/*476:*/

      {
        s = match_token + cur_chr;
        get_token();
        if (cur_tok < left_brace_limit) {
          hash_brace = cur_tok;
          store_new_token(cur_tok);
          store_new_token(end_match_token);
          goto done;
        }
        if (t == zero_token + 9) {
          print_err("You already have nine parameters");

          help2("I'm going to ignore the # sign you just used,")(
              "as well as the token that followed it.");
          error();
          goto resume;
        } else {
          incr(t);
          if (cur_tok != t) {
            print_err("Parameters must be numbered consecutively");

            help2("I've inserted the digit you should have used after the #.")(
                "Type `1' to delete what you did use.");
            back_error();
          }
          cur_tok = s;
        }
      }

/*:476*/
      ;
      store_new_token(cur_tok);
    }
  done1:
    store_new_token(end_match_token);
    if (cur_cmd == right_brace)
/*475:*/

    {
      print_err("Missing { inserted");
      incr(align_state);

      help2("Where was the left brace? You said something like `\\def\\a}',")(
          "which I'm going to interpret as `\\def\\a{}'.");
      error();
      goto found;
    }

/*:475*/
    ;
  done:;
  }

/*:474*/

  else
    scan_left_brace();
/*477:*/

  unbalance = 1;
  loop {
    if (xpand) /*478:*/

    {
      loop {
        get_next();
        if (cur_cmd <= max_command) goto done2;
        if (cur_cmd != the)
          expand();
        else {
          q = the_toks();
          if (link(temp_head) != null) {
            link(p) = link(temp_head);
            p = q;
          }
        }
      }
    done2:
      x_token();
    }

/*:478*/

    else
      get_token();
    if (cur_tok < right_brace_limit)
      if (cur_cmd < right_brace)
        incr(unbalance);
      else {
        decr(unbalance);
        if (unbalance == 0) goto found;
      }
    else if (cur_cmd == mac_param)
      if (macro_def) /*479:*/

      {
        s = cur_tok;
        if (xpand)
          get_x_token();
        else
          get_token();
        if (cur_cmd != mac_param)
          if ((cur_tok <= zero_token) || (cur_tok > t)) {
            print_err("Illegal parameter number in definition of ");

            sprint_cs(warning_index);
            help3("You meant to type ## instead of #, right?")(
                "Or maybe a } was forgotten somewhere earlier, and things")(
                "are all screwed up? I'm going to assume that you meant ##.");
            back_error();
            cur_tok = s;
          } else
            cur_tok = out_param_token - '0' + cur_chr;
      }

/*:479*/
      ;
    store_new_token(cur_tok);
  }

/*:477*/
  ;
found:
  scanner_status = normal;
  if (hash_brace != 0) store_new_token(hash_brace);
  return p;
}

/*:473*/ /*482:*/
void read_toks(int n, pointer r) {
  pointer p;
  pointer q;
  int s;
  small_number m;
  scanner_status = defining;
  warning_index = r;
  def_ref = get_avail();
  token_ref_count(def_ref) = null;
  p = def_ref;
  store_new_token(end_match_token);
  if ((n < 0) || (n > 15))
    m = 16;
  else
    m = n;
  s = align_state;
  align_state = 1000000;
  do { /*483:*/

    begin_file_reading();
    name = m + 1;
    if (read_open[m] == closed) /*484:*/

      if (interaction > nonstop_mode)
        if (n < 0) prompt_input("") else {
            wake_up_terminal;
            print_ln();
            sprint_cs(r);
            prompt_input("=");
            n = -1;
          }
        else
          fatal_error("*** (cannot \\read from terminal in nonstop modes)")

/*:484*/
              ;
      else if (read_open[m] == just_open) /*485:*/

        if (input_ln(&read_file[m], false))
          read_open[m] = normal;
        else {
          a_close(&read_file[m]);
          read_open[m] = closed;
        }

/*:485*/

      else /*486:*/

      {
        if (!input_ln(&read_file[m], true)) {
          a_close(&read_file[m]);
          read_open[m] = closed;
          if (align_state != 1000000) {
            runaway();
            print_err("File ended within ");
            print_esc(/*1556:*/
                      431
/*:1556*/
            );

            help1("This \\read has unbalanced braces.");
            align_state = 1000000;
            limit = 0;
            error();
          }
        }
      }

/*:486*/
      ;
    limit = last;
    if (end_line_char_inactive)
      decr(limit);
    else
      buffer[limit] = end_line_char;
    first = limit + 1;
    loc = start;
    state = new_line;
    loop {
      get_token();
      if (cur_tok == 0) goto done;

      if (align_state < 1000000) {
        do {
          get_token();
        } while (!(cur_tok == 0));
        align_state = 1000000;
        goto done;
      }
      store_new_token(cur_tok);
    }
  done:
    end_file_reading()

/*:483*/
        ;
  } while (!(align_state == 1000000));
  cur_val = def_ref;
  scanner_status = normal;
  align_state = s;
}

/*:482*/ /*494:*/
void pass_text(void) {
  int l;
  small_number save_scanner_status;
  save_scanner_status = scanner_status;
  scanner_status = skipping;
  l = 0;
  skip_line = line;
  loop {
    get_next();
    if (cur_cmd == fi_or_else) {
      if (l == 0) goto done;
      if (cur_chr == fi_code) decr(l);
    } else if (cur_cmd == if_test)
      incr(l);
  }
done:
  scanner_status = save_scanner_status;
}

/*:494*/ /*497:*/
void change_if_limit(small_number l, pointer p) {
  pointer q;
  if (p == cond_ptr)
    if_limit = l;
  else {
    q = cond_ptr;
    loop {
      if (q == null)
        confusion(/*1611:*/
                  486
/*:1611*/
        );

      if (link(q) == p) {
        type(q) = l;
        return;
      }
      q = link(q);
    }
  }
}

/*:497*/ /*498:*/
void conditional(void) {
  bool b;
  uint8_t r;
  int m, n;
  pointer p, q;
  small_number save_scanner_status;
  pointer save_cond_ptr;
  small_number this_if;
/*495:*/

  {
    p = get_node(if_node_size);
    link(p) = cond_ptr;
    type(p) = if_limit;
    subtype(p) = cur_if;
    if_line_field(p) = if_line;
    cond_ptr = p;
    cur_if = cur_chr;
    if_limit = if_code;
    if_line = line;
  }

/*:495*/
  ;
  save_cond_ptr = cond_ptr;
  this_if = cur_chr;
/*501:*/

  switch (this_if) {
    case if_char_code:
    case if_cat_code: /*506:*/

    {
      get_x_token_or_active_char;
      if ((cur_cmd > active_char) || (cur_chr > 255)) {
        m = relax;
        n = 256;
      } else {
        m = cur_cmd;
        n = cur_chr;
      }
      get_x_token_or_active_char;
      if ((cur_cmd > active_char) || (cur_chr > 255)) {
        cur_cmd = relax;
        cur_chr = 256;
      }
      if (this_if == if_char_code)
        b = (n == cur_chr);
      else
        b = (m == cur_cmd);
    }

/*:506*/
    break;
    case if_int_code:
    case if_dim_code: /*503:*/

    {
      if (this_if == if_int_code)
        scan_int();
      else
        scan_normal_dimen;
      n = cur_val; /*406:*/

      do {
        get_x_token();
      } while (!(cur_cmd != spacer))

/*:406*/
          ;
      if ((cur_tok >= other_token + '<') && (cur_tok <= other_token + '>'))
        r = cur_tok - other_token;
      else {
        print_err("Missing = inserted for ");

        print_cmd_chr(if_test, this_if);
        help1("I was expecting to see `<', `=', or `>'. Didn't.");
        back_error();
        r = '=';
      }
      if (this_if == if_int_code)
        scan_int();
      else
        scan_normal_dimen;
      switch (r) {
        case '<':
          b = (n < cur_val);
          break;
        case '=':
          b = (n == cur_val);
          break;
        case '>':
          b = (n > cur_val);
      }
    }

/*:503*/
    break;
    case if_odd_code: /*504:*/

    {
      scan_int();
      b = odd(cur_val);
    }

/*:504*/
    break;
    case if_vmode_code:
      b = (abs(mode) == vmode);
      break;
    case if_hmode_code:
      b = (abs(mode) == hmode);
      break;
    case if_mmode_code:
      b = (abs(mode) == mmode);
      break;
    case if_inner_code:
      b = (mode < 0);
      break;
    case if_void_code:
    case if_hbox_code:
    case if_vbox_code: /*505:*/

    {
      scan_eight_bit_int();
      p = box(cur_val);
      if (this_if == if_void_code)
        b = (p == null);
      else if (p == null)
        b = false;
      else if (this_if == if_hbox_code)
        b = (type(p) == hlist_node);
      else
        b = (type(p) == vlist_node);
    }

/*:505*/
    break;
    case ifx_code: /*507:*/

    {
      save_scanner_status = scanner_status;
      scanner_status = normal;
      get_next();
      n = cur_cs;
      p = cur_cmd;
      q = cur_chr;
      get_next();
      if (cur_cmd != p)
        b = false;
      else if (cur_cmd < call)
        b = (cur_chr == q);
      else /*508:*/

      {
        p = link(cur_chr);
        q = link(equiv(n));
        if (p == q)
          b = true;
        else {
          while ((p != null) && (q != null))
            if (info(p) != info(q))
              p = null;
            else {
              p = link(p);
              q = link(q);
            }
          b = ((p == null) && (q == null));
        }
      }

/*:508*/
      ;
      scanner_status = save_scanner_status;
    }

/*:507*/
    break;
    case if_eof_code: {
      scan_four_bit_int();
      b = (read_open[cur_val] == closed);
    } break;
    case if_true_code:
      b = true;
      break;
    case if_false_code:
      b = false;
      break;
    case if_case_code: /*509:*/

    {
      scan_int();
      n = cur_val;
      if (tracing_commands > 1) {
        begin_diagnostic();
        print_str("{case ");
        print_int(n);
        print_char('}');
        end_diagnostic(false);
      }
      while (n != 0) {
        pass_text();
        if (cond_ptr == save_cond_ptr)
          if (cur_chr == or_code)
            decr(n);
          else
            goto common_ending;
        else if (cur_chr == fi_code) /*496:*/

        {
          p = cond_ptr;
          if_line = if_line_field(p);
          cur_if = subtype(p);
          if_limit = type(p);
          cond_ptr = link(p);
          free_node(p, if_node_size);
        }

/*:496*/
        ;
      }
      change_if_limit(or_code, save_cond_ptr);
      return;
    }

/*:509*/
    ;
  }

/*:501*/
  ;
  if (tracing_commands > 1) /*502:*/

  {
    begin_diagnostic();
    if (b)
      print_str("{true}");
    else
      print_str("{false}");
    end_diagnostic(false);
  }

/*:502*/
  ;
  if (b) {
    change_if_limit(else_code, save_cond_ptr);
    return;
  }
/*500:*/

  loop {
    pass_text();
    if (cond_ptr == save_cond_ptr) {
      if (cur_chr != or_code) goto common_ending;
      print_err("Extra ");
      print_esc(/*1629:*/
                504
/*:1629*/
      );

      help1("I'm ignoring this; it doesn't match any \\if.");
      error();
    } else if (cur_chr == fi_code) /*496:*/

    {
      p = cond_ptr;
      if_line = if_line_field(p);
      cur_if = subtype(p);
      if_limit = type(p);
      cond_ptr = link(p);
      free_node(p, if_node_size);
    }

/*:496*/
    ;
  }

/*:500*/
  ;
common_ending:
  if (cur_chr == fi_code) /*496:*/

  {
    p = cond_ptr;
    if_line = if_line_field(p);
    cur_if = subtype(p);
    if_limit = type(p);
    cond_ptr = link(p);
    free_node(p, if_node_size);
  }

/*:496*/

  else
    if_limit = fi_code;
}

/*:498*/ /*515:*/
void begin_name(void) {
  area_delimiter = 0;
  ext_delimiter = 0;
}

/*:515*/ /*516:*/
bool more_name(ASCII_code c) {
  if (c == ' ')
    return false;
  else {
    str_room(1);
    append_char(c);
    if ((c == '>') || (c == ':')) {
      area_delimiter = cur_length;
      ext_delimiter = 0;
    } else if ((c == '.') && (ext_delimiter == 0))
      ext_delimiter = cur_length;
    return true;
  }
}

/*:516*/ /*517:*/
void end_name(void) {
  if (str_ptr + 3 > max_strings)
    overflow("number of strings", max_strings - init_str_ptr);

  if (area_delimiter == 0)
    cur_area = empty_string;
  else {
    cur_area = str_ptr;
    str_start[str_ptr + 1] = str_start[str_ptr] + area_delimiter;
    incr(str_ptr);
  }
  if (ext_delimiter == 0) {
    cur_ext = empty_string;
    cur_name = make_string();
  } else {
    cur_name = str_ptr;
    str_start[str_ptr + 1] =
        str_start[str_ptr] + ext_delimiter - area_delimiter - 1;
    incr(str_ptr);
    cur_ext = make_string();
  }
}

/*:517*/ /*519:*/
void pack_file_name(str_number n, str_number a, str_number e) {
  int k;
  ASCII_code c;
  int j;
  k = 0;
  for (j = str_start[a]; j <= str_start[a + 1] - 1; j++)
    append_to_name(so(str_pool[j]));
  for (j = str_start[n]; j <= str_start[n + 1] - 1; j++)
    append_to_name(so(str_pool[j]));
  for (j = str_start[e]; j <= str_start[e + 1] - 1; j++)
    append_to_name(so(str_pool[j]));
  if (k <= file_name_size)
    name_length = k;
  else
    name_length = file_name_size;
  name_of_file[name_length + 1] = 0;
}

/*:519*/ /*522:*/
void pack_buffered_name(small_number n, int a, int b) {
  int k;
  ASCII_code c;
  int j;
  if (n + b - a + 1 + format_ext_length > file_name_size)
    b = a + file_name_size - n - 1 - format_ext_length;
  k = 0;
  for (j = 1; j <= n; j++) append_to_name(xord[TEX_format_default[j]]);
  for (j = a; j <= b; j++) append_to_name(buffer[j]);
  for (j = format_default_length - format_ext_length + 1;
       j <= format_default_length; j++)
    append_to_name(xord[TEX_format_default[j]]);
  if (k <= file_name_size)
    name_length = k;
  else
    name_length = file_name_size;
  name_of_file[name_length + 1] = 0;
}

/*:522*/ /*524:*/
str_number make_name_string(void) {
  int k;
  if ((pool_ptr + name_length > pool_size) || (str_ptr == max_strings) ||
      (cur_length > 0))
    return '?';
  else {
    for (k = 1; k <= name_length; k++) append_char(xord[name_of_file[k]]);
    return make_string();
  }
}
str_number a_make_name_string(alpha_file *f) { return make_name_string(); }
str_number b_make_name_string(byte_file *f) { return make_name_string(); }
str_number w_make_name_string(word_file *f) { return make_name_string(); }

/*:524*/ /*525:*/
void scan_file_name(void) {
  name_in_progress = true;
  begin_name();
/*406:*/

  do {
    get_x_token();
  } while (!(cur_cmd != spacer))

/*:406*/
      ;
  loop {
    if ((cur_cmd > other_char) || (cur_chr > 255)) {
      back_input();
      goto done;
    }
    if (!more_name(cur_chr)) goto done;
    get_x_token();
  }
done:
  end_name();
  name_in_progress = false;
}

/*:525*/ /*528:*/
void pack_job_name(str_number s)

{
  cur_area = empty_string;
  cur_ext = s;
  cur_name = job_name;
  pack_cur_name;
}

/*:528*/ /*529:*/
void prompt_file_name(char *s, str_number e) {
  uint16_t k;
  if (interaction == scroll_mode) wake_up_terminal;
  if (strcmp(s, "input file name") == 0)
    print_err("I can't find file `")

        else print_err("I can't write on file `");

  print_file_name(cur_name, cur_area, cur_ext);
  print_str("'.");
  if (e == /*1637:*/
      512
/*:1637*/
  )
    show_context();
  print_nl("Please type another ");
  print_str(s);

  if (interaction < scroll_mode)
    fatal_error("*** (job aborted, file error in nonstop mode)");

  clear_terminal;
  prompt_input(": "); /*530:*/

  {
    begin_name();
    k = first;
    while ((buffer[k] == ' ') && (k < last)) incr(k);
    loop {
      if (k == last) goto done;
      if (!more_name(buffer[k])) goto done;
      incr(k);
    }
  done:
    end_name();
  }

/*:530*/
  ;
  if (cur_ext == empty_string) cur_ext = e;
  pack_cur_name;
}

/*:529*/ /*534:*/
void open_log_file(void) {
  uint8_t old_setting;
  int k;
  uint16_t l;
  ASCII_code months[] = " JANFEBMARAPRMAYJUNJULAUGSEPOCTNOVDEC";
  old_setting = selector;
  if (job_name == 0)
    job_name = /*1638:*/
        513
/*:1638*/
        ;

  pack_job_name(/*1634:*/
                509
/*:1634*/
  );
  while (!a_open_out(&log_file)) /*535:*/

  {
    selector = term_only;
    prompt_file_name("transcript file name", /*1634:*/
                     509
/*:1634*/
    );
  }

/*:535*/
  ;
  log_name = a_make_name_string(&log_file);
  selector = log_only;
  log_opened = true;
/*536:*/

  {
    wlog("%s", banner);
    slow_print(format_ident);
    print_str("  ");
    print_int(sys_day);
    print_char(' ');
    for (k = 3 * sys_month - 2; k <= 3 * sys_month; k++) wlog("%c", months[k]);
    print_char(' ');
    print_int(sys_year);
    print_char(' ');
    print_two(sys_time / 60);
    print_char(':');
    print_two(sys_time % 60);
  }

/*:536*/
  ;
  input_stack[input_ptr] = cur_input;
  print_nl("**");

  l = input_stack[0].limit_field;
  if (buffer[l] == end_line_char) decr(l);
  for (k = 1; k <= l; k++) print(buffer[k]);
  print_ln();
  selector = old_setting + 2;
}

/*:534*/ /*537:*/
void start_input(void) {
  scan_file_name();
  if (cur_ext == empty_string)
    cur_ext = /*1637:*/
        512
/*:1637*/
        ;
  pack_cur_name;
  loop {
    begin_file_reading();
    if (a_open_in(&cur_file)) goto done;
    if (cur_area == empty_string) {
      pack_file_name(cur_name, TEX_area, cur_ext);
      if (a_open_in(&cur_file)) goto done;
    }
    end_file_reading();
    prompt_file_name("input file name", /*1637:*/
                     512
/*:1637*/
    );
  }
done:
  name = a_make_name_string(&cur_file);
  if (job_name == 0) {
    job_name = cur_name;
    open_log_file();
  }

  if (term_offset + length(name) > max_print_line - 2)
    print_ln();
  else if ((term_offset > 0) || (file_offset > 0))
    print_char(' ');
  print_char('(');
  incr(open_parens);
  slow_print(name);
  update_terminal;
  state = new_line;
  if (name == str_ptr - 1) {
    flush_string;
    name = cur_name;
  }
/*538:*/

  {
    line = 1;
    if (input_ln(&cur_file, false)) do_nothing;
    firm_up_the_line();
    if (end_line_char_inactive)
      decr(limit);
    else
      buffer[limit] = end_line_char;
    first = limit + 1;
    loc = start;
  }

/*:538*/
  ;
}

/*:537*/ /*560:*/
internal_font_number read_font_info(pointer u, str_number nom, str_number aire,
                                    scaled s) {
  font_index k;
  bool file_opened;
  halfword lf, lh, bc, ec, nw, nh, nd, ni, nl, nk, ne, np;

  internal_font_number f;
  internal_font_number g;
  eight_bits a, b, c, d;
  four_quarters qw;
  scaled sw;
  int bch_label;
  uint16_t bchar;
  scaled z;
  int alpha;
  uint8_t beta;

  g = null_font;
/*562:*/

/*563:*/

  file_opened = false;
  if (aire == empty_string)
    pack_file_name(nom, TEX_font_area, /*1640:*/
                   515
/*:1640*/
    );
  else
    pack_file_name(nom, aire, /*1640:*/
                   515
/*:1640*/
    );
  if (!b_open_in(&tfm_file)) abort;
  file_opened = true

/*:563*/
      ;
/*565:*/

  {
    read_sixteen(lf);
    fget;
    read_sixteen(lh);
    fget;
    read_sixteen(bc);
    fget;
    read_sixteen(ec);
    if ((bc > ec + 1) || (ec > 255)) abort;
    if (bc > 255) {
      bc = 1;
      ec = 0;
    }
    fget;
    read_sixteen(nw);
    fget;
    read_sixteen(nh);
    fget;
    read_sixteen(nd);
    fget;
    read_sixteen(ni);
    fget;
    read_sixteen(nl);
    fget;
    read_sixteen(nk);
    fget;
    read_sixteen(ne);
    fget;
    read_sixteen(np);
    if (lf != 6 + lh + (ec - bc + 1) + nw + nh + nd + ni + nl + nk + ne + np)
      abort;
    if ((nw == 0) || (nh == 0) || (nd == 0) || (ni == 0)) abort;
  }

/*:565*/
  ;
/*566:*/

  lf = lf - 6 - lh;
  if (np < 7) lf = lf + 7 - np;
  if ((font_ptr == font_max) || (fmem_ptr + lf > font_mem_size))
/*567:*/

  {
    start_font_error_message;
    print_str(" not loaded: Not enough room left");

    help4("I'm afraid I won't be able to make use of this font,")(
        "because my memory for character-size data is too small.")(
        "If you're really stuck, ask a wizard to enlarge me.")(
        "Or maybe try `I\\font<same font id>=<name of loaded font>'.");
    error();
    goto done;
  }

/*:567*/
  ;
  f = font_ptr + 1;
  char_base[f] = fmem_ptr - bc;
  width_base[f] = char_base[f] + ec + 1;
  height_base[f] = width_base[f] + nw;
  depth_base[f] = height_base[f] + nh;
  italic_base[f] = depth_base[f] + nd;
  lig_kern_base[f] = italic_base[f] + ni;
  kern_base[f] = lig_kern_base[f] + nl - kern_base_offset;
  exten_base[f] = kern_base[f] + kern_base_offset + nk;
  param_base[f] = exten_base[f] + ne

/*:566*/
      ;
/*568:*/

  {
    if (lh < 2) abort;
    store_four_quarters(font_check[f]);
    fget;
    read_sixteen(z);
    fget;
    z = z * 0400 + fbyte;
    fget;
    z = (z * 020) + (fbyte / 020);
    if (z < unity) abort;
    while (lh > 2) {
      fget;
      fget;
      fget;
      fget;
      decr(lh);
    }
    font_dsize[f] = z;
    if (s != -1000)
      if (s >= 0)
        z = s;
      else
        z = xn_over_d(z, -s, 1000);
    font_size[f] = z;
  }

/*:568*/
  ;
/*569:*/

  for (k = fmem_ptr; k <= width_base[f] - 1; k++) {
    store_four_quarters(font_info[k].qqqq);
    if ((a >= nw) || (b / 020 >= nh) || (b % 020 >= nd) || (c / 4 >= ni)) abort;
    switch (c % 4) {
      case lig_tag:
        if (d >= nl) abort;
        break;
      case ext_tag:
        if (d >= ne) abort;
        break;
      case list_tag: /*570:*/

      {
        check_byte_range(d);
        while (d < current_character_being_worked_on) {
          qw = char_info(f)(d);

          if (char_tag(qw) != list_tag) goto not_found;
          d = qo(rem_byte(qw));
        }
        if (d == current_character_being_worked_on) abort;
      not_found:;
      }

/*:570*/
      break;
      default:
        do_nothing;
    }
  }

/*:569*/
  ;
/*571:*/

  { /*572:*/

    {
      alpha = 16;
      while (z >= 040000000) {
        z = z / 2;
        alpha = alpha + alpha;
      }
      beta = 256 / alpha;
      alpha = alpha * z;
    }

/*:572*/
    ;
    for (k = width_base[f]; k <= lig_kern_base[f] - 1; k++)
      store_scaled(font_info[k].sc);
    if (font_info[width_base[f]].sc != 0) abort;
    if (font_info[height_base[f]].sc != 0) abort;
    if (font_info[depth_base[f]].sc != 0) abort;
    if (font_info[italic_base[f]].sc != 0) abort;
  }

/*:571*/
  ;
/*573:*/

  bch_label = 077777;
  bchar = 256;
  if (nl > 0) {
    for (k = lig_kern_base[f]; k <= kern_base[f] + kern_base_offset - 1; k++) {
      store_four_quarters(font_info[k].qqqq);
      if (a > 128) {
        if (256 * c + d >= nl) abort;
        if (a == 255)
          if (k == lig_kern_base[f]) bchar = b;
      } else {
        if (b != bchar) check_existence(b);
        if (c < 128)
          check_existence(d) else if (256 * (c - 128) + d >= nk) abort;
        if (a < 128)
          if (k - lig_kern_base[f] + a + 1 >= nl) abort;
      }
    }
    if (a == 255) bch_label = 256 * c + d;
  }
  for (k = kern_base[f] + kern_base_offset; k <= exten_base[f] - 1; k++)
    store_scaled(font_info[k].sc);

/*:573*/
  ;
/*574:*/

  for (k = exten_base[f]; k <= param_base[f] - 1; k++) {
    store_four_quarters(font_info[k].qqqq);
    if (a != 0) check_existence(a);
    if (b != 0) check_existence(b);
    if (c != 0) check_existence(c);
    check_existence(d);
  }

/*:574*/
  ;
/*575:*/

  {
    for (k = 1; k <= np; k++)
      if (k == 1) {
        fget;
        sw = fbyte;
        if (sw > 127) sw = sw - 256;
        fget;
        sw = sw * 0400 + fbyte;
        fget;
        sw = sw * 0400 + fbyte;
        fget;
        font_info[param_base[f]].sc = (sw * 020) + (fbyte / 020);
      } else
        store_scaled(font_info[param_base[f] + k - 1].sc);
    if (eof(tfm_file)) abort;
    for (k = np + 1; k <= 7; k++) font_info[param_base[f] + k - 1].sc = 0;
  }

/*:575*/
  ;
/*576:*/

  if (np >= 7)
    font_params[f] = np;
  else
    font_params[f] = 7;
  hyphen_char[f] = default_hyphen_char;
  skew_char[f] = default_skew_char;
  if (bch_label < nl)
    bchar_label[f] = bch_label + lig_kern_base[f];
  else
    bchar_label[f] = non_address;
  font_bchar[f] = qi(bchar);
  font_false_bchar[f] = qi(bchar);
  if (bchar <= ec)
    if (bchar >= bc) {
      qw = char_info(f)(bchar);
      if (char_exists(qw)) font_false_bchar[f] = non_char;
    }
  font_name[f] = nom;
  font_area[f] = aire;
  font_bc[f] = bc;
  font_ec[f] = ec;
  font_glue[f] = null;
  adjust(char_base);
  adjust(width_base);
  adjust(lig_kern_base);
  adjust(kern_base);
  adjust(exten_base);
  decr(param_base[f]);
  fmem_ptr = fmem_ptr + lf;
  font_ptr = f;
  g = f;
  goto done

/*:576*/

/*:562*/
      ;
bad_tfm: /*561:*/

  start_font_error_message;

  if (file_opened)
    print_str(" not loadable: Bad metric (TFM) file");
  else
    print_str(" not loadable: Metric (TFM) file not found");
  help5("I wasn't able to read the size data for this font,")(
      "so I will ignore the font specification.")(
      "[Wizards can fix TFM files using TFtoPL/PLtoTF.]")(
      "You might try inserting a different font spec;")(
      "e.g., type `I\\font<same font id>=<substitute font name>'.");
  error()

/*:561*/
      ;
done:
  if (file_opened) b_close(&tfm_file);
  return g;
}

/*:560*/ /*581:*/
void char_warning(internal_font_number f, eight_bits c) {
  if (tracing_lost_chars > 0) {
    begin_diagnostic();
    print_nl("Missing character: There is no ");

    print_ASCII(c);
    print_str(" in font ");
    slow_print(font_name[f]);
    print_char('!');
    end_diagnostic(false);
  }
}

/*:581*/ /*582:*/
pointer new_character(internal_font_number f, eight_bits c) {
  pointer p;
  if (font_bc[f] <= c)
    if (font_ec[f] >= c)
      if (char_exists(char_info(f)(qi(c)))) {
        p = get_avail();
        font(p) = f;
        character(p) = qi(c);
        return p;
      }
  char_warning(f, c);
  return null;
}

/*:582*/ /*597:*/
void write_dvi(dvi_index a, dvi_index b) {
  int k;
  for (k = a; k <= b; k++) write(dvi_file, "%c", dvi_buf[k]);
}

/*:597*/ /*598:*/
void dvi_swap(void) {
  if (dvi_limit == dvi_buf_size) {
    write_dvi(0, half_buf - 1);
    dvi_limit = half_buf;
    dvi_offset = dvi_offset + dvi_buf_size;
    dvi_ptr = 0;
  } else {
    write_dvi(half_buf, dvi_buf_size - 1);
    dvi_limit = dvi_buf_size;
  }
  dvi_gone = dvi_gone + half_buf;
}

/*:598*/ /*600:*/
void dvi_four(int x) {
  if (x >= 0) dvi_out(x / 0100000000) else {
      x = x + 010000000000;
      x = x + 010000000000;
      dvi_out((x / 0100000000) + 128);
    }
  x = x % 0100000000;
  dvi_out(x / 0200000);
  x = x % 0200000;
  dvi_out(x / 0400);
  dvi_out(x % 0400);
}

/*:600*/ /*601:*/
void dvi_pop(int l) {
  if ((l == dvi_offset + dvi_ptr) && (dvi_ptr > 0))
    decr(dvi_ptr);
  else
    dvi_out(pop);
}

/*:601*/ /*602:*/
void dvi_font_def(internal_font_number f) {
  int k;
  dvi_out(fnt_def1);
  dvi_out(f - font_base - 1);
  dvi_out(qo(font_check[f].b0));
  dvi_out(qo(font_check[f].b1));
  dvi_out(qo(font_check[f].b2));
  dvi_out(qo(font_check[f].b3));
  dvi_four(font_size[f]);
  dvi_four(font_dsize[f]);
  dvi_out(length(font_area[f]));
  dvi_out(length(font_name[f]));
/*603:*/

  for (k = str_start[font_area[f]]; k <= str_start[font_area[f] + 1] - 1; k++)
    dvi_out(so(str_pool[k]));
  for (k = str_start[font_name[f]]; k <= str_start[font_name[f] + 1] - 1; k++)
    dvi_out(so(str_pool[k]))

/*:603*/
        ;
}

/*:602*/ /*607:*/
void movement(scaled w, eight_bits o) {
  small_number mstate;
  pointer p, q;
  int k;
  q = get_node(movement_node_size);
  width(q) = w;
  location(q) = dvi_offset + dvi_ptr;
  if (o == down1) {
    link(q) = down_ptr;
    down_ptr = q;
  } else {
    link(q) = right_ptr;
    right_ptr = q;
  }
/*611:*/

  p = link(q);
  mstate = none_seen;
  while (p != null) {
    if (width(p) == w) /*612:*/

      switch (mstate + info(p)) {
        case none_seen + yz_OK:
        case none_seen + y_OK:
        case z_seen + yz_OK:
        case z_seen + y_OK:
          if (location(p) < dvi_gone)
            goto not_found;
          else /*613:*/

          {
            k = location(p) - dvi_offset;
            if (k < 0) k = k + dvi_buf_size;
            dvi_buf[k] = dvi_buf[k] + y1 - down1;
            info(p) = y_here;
            goto found;
          }

/*:613*/
          break;
        case none_seen + z_OK:
        case y_seen + yz_OK:
        case y_seen + z_OK:
          if (location(p) < dvi_gone)
            goto not_found;
          else /*614:*/

          {
            k = location(p) - dvi_offset;
            if (k < 0) k = k + dvi_buf_size;
            dvi_buf[k] = dvi_buf[k] + z1 - down1;
            info(p) = z_here;
            goto found;
          }

/*:614*/
          break;
        case none_seen + y_here:
        case none_seen + z_here:
        case y_seen + z_here:
        case z_seen + y_here:
          goto found;
        default:
          do_nothing;
      }

/*:612*/

    else
      switch (mstate + info(p)) {
        case none_seen + y_here:
          mstate = y_seen;
          break;
        case none_seen + z_here:
          mstate = z_seen;
          break;
        case y_seen + z_here:
        case z_seen + y_here:
          goto not_found;
        default:
          do_nothing;
      }
    p = link(p);
  }
not_found:

/*:611*/
    ;
/*610:*/

  info(q) = yz_OK;
  if (abs(w) >= 040000000) {
    dvi_out(o + 3);
    dvi_four(w);
    return;
  }
  if (abs(w) >= 0100000) {
    dvi_out(o + 2);
    if (w < 0) w = w + 0100000000;
    dvi_out(w / 0200000);
    w = w % 0200000;
    goto label2;
  }
  if (abs(w) >= 0200) {
    dvi_out(o + 1);
    if (w < 0) w = w + 0200000;
    goto label2;
  }
  dvi_out(o);
  if (w < 0) w = w + 0400;
  goto label1;
label2:
  dvi_out(w / 0400);
label1:
  dvi_out(w % 0400);
  return

/*:610*/
      ;
found: /*609:*/

  info(q) = info(p);
  if (info(q) == y_here) {
    dvi_out(o + y0 - down1);
    while (link(q) != p) {
      q = link(q);
      switch (info(q)) {
        case yz_OK:
          info(q) = z_OK;
          break;
        case y_OK:
          info(q) = d_fixed;
          break;
        default:
          do_nothing;
      }
    }
  } else {
    dvi_out(o + z0 - down1);
    while (link(q) != p) {
      q = link(q);
      switch (info(q)) {
        case yz_OK:
          info(q) = y_OK;
          break;
        case z_OK:
          info(q) = d_fixed;
          break;
        default:
          do_nothing;
      }
    }
  }

/*:609*/
  ;
}

/*:607*/ /*615:*/
void prune_movements(int l)

{
  pointer p;
  while (down_ptr != null) {
    if (location(down_ptr) < l) goto done;
    p = down_ptr;
    down_ptr = link(p);
    free_node(p, movement_node_size);
  }
done:
  while (right_ptr != null) {
    if (location(right_ptr) < l) return;
    p = right_ptr;
    right_ptr = link(p);
    free_node(p, movement_node_size);
  }
}

/*:615*/ /*618:*/
void vlist_out(void);

/*:618*/ /*619:*/
/*1368:*/

void special_out(pointer p) {
  uint8_t old_setting;
  int k;
  synch_h;
  synch_v;
  old_setting = selector;
  selector = new_string;
  show_token_list(link(write_tokens(p)), null, pool_size - pool_ptr);
  selector = old_setting;
  str_room(1);
  if (cur_length < 256) {
    dvi_out(xxx1);
    dvi_out(cur_length);
  } else {
    dvi_out(xxx4);
    dvi_four(cur_length);
  }
  for (k = str_start[str_ptr]; k <= pool_ptr - 1; k++) dvi_out(so(str_pool[k]));
  pool_ptr = str_start[str_ptr];
}

/*:1368*/ /*1370:*/

void write_out(pointer p) {
  uint8_t old_setting;
  int old_mode;
  small_number j;
  pointer q, r;
/*1371:*/

  q = get_avail();
  info(q) = right_brace_token + '}';
  r = get_avail();
  link(q) = r;
  info(r) = end_write_token;
  ins_list(q);
  begin_token_list(write_tokens(p), write_text);
  q = get_avail();
  info(q) = left_brace_token + '{';
  ins_list(q);

  old_mode = mode;
  mode = 0;

  cur_cs = write_loc;
  q = scan_toks(false, true);
  get_token();
  if (cur_tok != end_write_token)
/*1372:*/

  {
    print_err("Unbalanced write command");

    help2("On this page there's a \\write with fewer real {'s than }'s.")(
        "I can't handle that very well; good luck.");
    error();
    do {
      get_token();
    } while (!(cur_tok == end_write_token));
  }

/*:1372*/
  ;
  mode = old_mode;
  end_token_list()

/*:1371*/
      ;
  old_setting = selector;
  j = write_stream(p);
  if (write_open[j])
    selector = j;
  else {
    if ((j == 17) && (selector == term_and_log)) selector = log_only;
    print_nl("");
  }
  token_show(def_ref);
  print_ln();
  flush_list(def_ref);
  selector = old_setting;
}

/*:1370*/ /*1373:*/

void out_what(pointer p) {
  small_number j;
  switch (subtype(p)) {
    case open_node:
    case write_node:
    case close_node: /*1374:*/

      if (!doing_leaders) {
        j = write_stream(p);
        if (subtype(p) == write_node)
          write_out(p);
        else {
          if (write_open[j]) a_close(&write_file[j]);
          if (subtype(p) == close_node)
            write_open[j] = false;
          else if (j < 16) {
            cur_name = open_name(p);
            cur_area = open_area(p);
            cur_ext = open_ext(p);
            if (cur_ext == empty_string)
              cur_ext = /*1637:*/
                  512
/*:1637*/
                  ;
            pack_cur_name;
            while (!a_open_out(&write_file[j]))
              prompt_file_name("output file name", /*1637:*/
                               512
/*:1637*/
              );
            write_open[j] = true;
          }
        }
      }

/*:1374*/
      break;
    case special_node:
      special_out(p);
      break;
    case language_node:
      do_nothing;
      break;
    default:
      confusion(/*1792:*/
                667

/*:1792*/
      );
  }
}

/*:1373*/

void hlist_out(void) {
  scaled base_line;
  scaled left_edge;
  scaled save_h, save_v;
  pointer this_box;
  glue_ord g_order;
  uint8_t g_sign;
  pointer p;
  int save_loc;
  pointer leader_box;
  scaled leader_wd;
  scaled lx;
  bool outer_doing_leaders;
  scaled edge;
  double glue_temp;
  double cur_glue;
  scaled cur_g;
  cur_g = 0;
  cur_glue = float_constant(0);
  this_box = temp_ptr;
  g_order = glue_order(this_box);
  g_sign = glue_sign(this_box);
  p = list_ptr(this_box);
  incr(cur_s);
  if (cur_s > 0) dvi_out(push);
  if (cur_s > max_push) max_push = cur_s;
  save_loc = dvi_offset + dvi_ptr;
  base_line = cur_v;
  left_edge = cur_h;
  while (p != null) /*620:*/

  reswitch:
    if (is_char_node(p)) {
      synch_h;
      synch_v;
      do {
        f = font(p);
        c = character(p);
        if (f != dvi_f) /*621:*/

        {
          if (!font_used[f]) {
            dvi_font_def(f);
            font_used[f] = true;
          }
          if (f <= 64 + font_base) dvi_out(f - font_base - 1 + fnt_num_0) else {
              dvi_out(fnt1);
              dvi_out(f - font_base - 1);
            }
          dvi_f = f;
        }

/*:621*/
        ;
        if (c >= qi(128)) dvi_out(set1);
        dvi_out(qo(c));
        cur_h = cur_h + char_width(f)(char_info(f)(c));
        p = link(p);
      } while (!(!is_char_node(p)));
      dvi_h = cur_h;
    } else /*622:*/

    {
      switch (type(p)) {
        case hlist_node:
        case vlist_node: /*623:*/

          if (list_ptr(p) == null)
            cur_h = cur_h + width(p);
          else {
            save_h = dvi_h;
            save_v = dvi_v;
            cur_v = base_line + shift_amount(p);
            temp_ptr = p;
            edge = cur_h;
            if (type(p) == vlist_node)
              vlist_out();
            else
              hlist_out();
            dvi_h = save_h;
            dvi_v = save_v;
            cur_h = edge + width(p);
            cur_v = base_line;
          }

/*:623*/
          break;
        case rule_node: {
          rule_ht = height(p);
          rule_dp = depth(p);
          rule_wd = width(p);
          goto fin_rule;
        }
        case whatsit_node: /*1367:*/

          out_what(p)

/*:1367*/
              ;
          break;
        case glue_node: /*625:*/

        {
          g = glue_ptr(p);
          rule_wd = width(g) - cur_g;
          if (g_sign != normal) {
            if (g_sign == stretching) {
              if (stretch_order(g) == g_order) {
                cur_glue = cur_glue + stretch(g);
                vet_glue(float(glue_set(this_box)) * cur_glue);

                cur_g = round(glue_temp);
              }
            } else if (shrink_order(g) == g_order) {
              cur_glue = cur_glue - shrink(g);
              vet_glue(float(glue_set(this_box)) * cur_glue);
              cur_g = round(glue_temp);
            }
          }
          rule_wd = rule_wd + cur_g;
          if (subtype(p) >= a_leaders)
/*626:*/

          {
            leader_box = leader_ptr(p);
            if (type(leader_box) == rule_node) {
              rule_ht = height(leader_box);
              rule_dp = depth(leader_box);
              goto fin_rule;
            }
            leader_wd = width(leader_box);
            if ((leader_wd > 0) && (rule_wd > 0)) {
              rule_wd = rule_wd + 10;
              edge = cur_h + rule_wd;
              lx = 0;
/*627:*/

              if (subtype(p) == a_leaders) {
                save_h = cur_h;
                cur_h =
                    left_edge + leader_wd * ((cur_h - left_edge) / leader_wd);
                if (cur_h < save_h) cur_h = cur_h + leader_wd;
              } else {
                lq = rule_wd / leader_wd;
                lr = rule_wd % leader_wd;
                if (subtype(p) == c_leaders)
                  cur_h = cur_h + (lr / 2);
                else {
                  lx = lr / (lq + 1);
                  cur_h = cur_h + ((lr - (lq - 1) * lx) / 2);
                }
              }

/*:627*/
              ;
              while (cur_h + leader_wd <= edge)
/*628:*/

              {
                cur_v = base_line + shift_amount(leader_box);
                synch_v;
                save_v = dvi_v;
                synch_h;
                save_h = dvi_h;
                temp_ptr = leader_box;
                outer_doing_leaders = doing_leaders;
                doing_leaders = true;
                if (type(leader_box) == vlist_node)
                  vlist_out();
                else
                  hlist_out();
                doing_leaders = outer_doing_leaders;
                dvi_v = save_v;
                dvi_h = save_h;
                cur_v = base_line;
                cur_h = save_h + leader_wd + lx;
              }

/*:628*/
              ;
              cur_h = edge - 10;
              goto next_p;
            }
          }

/*:626*/
          ;
          goto move_past;
        }

/*:625*/

        case kern_node:
        case math_node:
          cur_h = cur_h + width(p);
          break;
        case ligature_node: /*652:*/

        {
          mem[lig_trick] = mem[lig_char(p)];
          link(lig_trick) = link(p);
          p = lig_trick;
          goto reswitch;
        }

/*:652*/

        default:
          do_nothing;
      }
      goto next_p;
    fin_rule: /*624:*/

      if (is_running(rule_ht)) rule_ht = height(this_box);
      if (is_running(rule_dp)) rule_dp = depth(this_box);
      rule_ht = rule_ht + rule_dp;
      if ((rule_ht > 0) && (rule_wd > 0)) {
        synch_h;
        cur_v = base_line + rule_dp;
        synch_v;
        dvi_out(set_rule);
        dvi_four(rule_ht);
        dvi_four(rule_wd);
        cur_v = base_line;
        dvi_h = dvi_h + rule_wd;
      }

/*:624*/
      ;
    move_past:
      cur_h = cur_h + rule_wd;
    next_p:
      p = link(p);
    }

/*:622*/

/*:620*/
    ;
  prune_movements(save_loc);
  if (cur_s > 0) dvi_pop(save_loc);
  decr(cur_s);
}

/*:619*/ /*629:*/
void vlist_out(void) {
  scaled left_edge;
  scaled top_edge;
  scaled save_h, save_v;
  pointer this_box;
  glue_ord g_order;
  uint8_t g_sign;
  pointer p;
  int save_loc;
  pointer leader_box;
  scaled leader_ht;
  scaled lx;
  bool outer_doing_leaders;
  scaled edge;
  double glue_temp;
  double cur_glue;
  scaled cur_g;
  cur_g = 0;
  cur_glue = float_constant(0);
  this_box = temp_ptr;
  g_order = glue_order(this_box);
  g_sign = glue_sign(this_box);
  p = list_ptr(this_box);
  incr(cur_s);
  if (cur_s > 0) dvi_out(push);
  if (cur_s > max_push) max_push = cur_s;
  save_loc = dvi_offset + dvi_ptr;
  left_edge = cur_h;
  cur_v = cur_v - height(this_box);
  top_edge = cur_v;
  while (p != null) /*630:*/

  {
    if (is_char_node(p))
      confusion(/*1641:*/
                516
/*:1641*/
      );

    else /*631:*/

    {
      switch (type(p)) {
        case hlist_node:
        case vlist_node: /*632:*/

          if (list_ptr(p) == null)
            cur_v = cur_v + height(p) + depth(p);
          else {
            cur_v = cur_v + height(p);
            synch_v;
            save_h = dvi_h;
            save_v = dvi_v;
            cur_h = left_edge + shift_amount(p);
            temp_ptr = p;
            if (type(p) == vlist_node)
              vlist_out();
            else
              hlist_out();
            dvi_h = save_h;
            dvi_v = save_v;
            cur_v = save_v + depth(p);
            cur_h = left_edge;
          }

/*:632*/
          break;
        case rule_node: {
          rule_ht = height(p);
          rule_dp = depth(p);
          rule_wd = width(p);
          goto fin_rule;
        }
        case whatsit_node: /*1366:*/

          out_what(p)

/*:1366*/
              ;
          break;
        case glue_node: /*634:*/

        {
          g = glue_ptr(p);
          rule_ht = width(g) - cur_g;
          if (g_sign != normal) {
            if (g_sign == stretching) {
              if (stretch_order(g) == g_order) {
                cur_glue = cur_glue + stretch(g);
                vet_glue(float(glue_set(this_box)) * cur_glue);

                cur_g = round(glue_temp);
              }
            } else if (shrink_order(g) == g_order) {
              cur_glue = cur_glue - shrink(g);
              vet_glue(float(glue_set(this_box)) * cur_glue);
              cur_g = round(glue_temp);
            }
          }
          rule_ht = rule_ht + cur_g;
          if (subtype(p) >= a_leaders)
/*635:*/

          {
            leader_box = leader_ptr(p);
            if (type(leader_box) == rule_node) {
              rule_wd = width(leader_box);
              rule_dp = 0;
              goto fin_rule;
            }
            leader_ht = height(leader_box) + depth(leader_box);
            if ((leader_ht > 0) && (rule_ht > 0)) {
              rule_ht = rule_ht + 10;
              edge = cur_v + rule_ht;
              lx = 0;
/*636:*/

              if (subtype(p) == a_leaders) {
                save_v = cur_v;
                cur_v = top_edge + leader_ht * ((cur_v - top_edge) / leader_ht);
                if (cur_v < save_v) cur_v = cur_v + leader_ht;
              } else {
                lq = rule_ht / leader_ht;
                lr = rule_ht % leader_ht;
                if (subtype(p) == c_leaders)
                  cur_v = cur_v + (lr / 2);
                else {
                  lx = lr / (lq + 1);
                  cur_v = cur_v + ((lr - (lq - 1) * lx) / 2);
                }
              }

/*:636*/
              ;
              while (cur_v + leader_ht <= edge)
/*637:*/

              {
                cur_h = left_edge + shift_amount(leader_box);
                synch_h;
                save_h = dvi_h;
                cur_v = cur_v + height(leader_box);
                synch_v;
                save_v = dvi_v;
                temp_ptr = leader_box;
                outer_doing_leaders = doing_leaders;
                doing_leaders = true;
                if (type(leader_box) == vlist_node)
                  vlist_out();
                else
                  hlist_out();
                doing_leaders = outer_doing_leaders;
                dvi_v = save_v;
                dvi_h = save_h;
                cur_h = left_edge;
                cur_v = save_v - height(leader_box) + leader_ht + lx;
              }

/*:637*/
              ;
              cur_v = edge - 10;
              goto next_p;
            }
          }

/*:635*/
          ;
          goto move_past;
        }

/*:634*/

        case kern_node:
          cur_v = cur_v + width(p);
          break;
        default:
          do_nothing;
      }
      goto next_p;
    fin_rule: /*633:*/

      if (is_running(rule_wd)) rule_wd = width(this_box);
      rule_ht = rule_ht + rule_dp;
      cur_v = cur_v + rule_ht;
      if ((rule_ht > 0) && (rule_wd > 0)) {
        synch_h;
        synch_v;
        dvi_out(put_rule);
        dvi_four(rule_ht);
        dvi_four(rule_wd);
      }
      goto next_p

/*:633*/
          ;
    move_past:
      cur_v = cur_v + rule_ht;
    }

/*:631*/
    ;
  next_p:
    p = link(p);
  }

/*:630*/
  ;
  prune_movements(save_loc);
  if (cur_s > 0) dvi_pop(save_loc);
  decr(cur_s);
}

/*:629*/ /*638:*/
void ship_out(pointer p) {
  int page_loc;
  uint8_t j, k;
  int s;
  uint8_t old_setting;
  if (tracing_output > 0) {
    print_nl("");
    print_ln();
    print_str("Completed box being shipped out");
  }
  if (term_offset > max_print_line - 9)
    print_ln();
  else if ((term_offset > 0) || (file_offset > 0))
    print_char(' ');
  print_char('[');
  j = 9;
  while ((count(j) == 0) && (j > 0)) decr(j);
  for (k = 0; k <= j; k++) {
    print_int(count(k));
    if (k < j) print_char('.');
  }
  update_terminal;
  if (tracing_output > 0) {
    print_char(']');
    begin_diagnostic();
    show_box(p);
    end_diagnostic(true);
  }
/*640:*/

/*641:*/

  if ((height(p) > max_dimen) || (depth(p) > max_dimen) ||
      (height(p) + depth(p) + v_offset > max_dimen) ||
      (width(p) + h_offset > max_dimen)) {
    print_err("Huge page cannot be shipped out");

    help2("The page just created is more than 18 feet tall or")(
        "more than 18 feet wide, so I suspect something went wrong.");
    error();
    if (tracing_output <= 0) {
      begin_diagnostic();
      print_nl("The following box has been deleted:");

      show_box(p);
      end_diagnostic(true);
    }
    goto done;
  }
  if (height(p) + depth(p) + v_offset > max_v)
    max_v = height(p) + depth(p) + v_offset;
  if (width(p) + h_offset > max_h)
    max_h = width(p) + h_offset

/*:641*/
        ;
/*617:*/

  dvi_h = 0;
  dvi_v = 0;
  cur_h = h_offset;
  dvi_f = null_font;
/*531:*/

  if (output_file_name == 0) {
    if (job_name == 0) open_log_file();
    pack_job_name(/*1635:*/
                  510
/*:1635*/
    );
    while (!b_open_out(&dvi_file))
      prompt_file_name("file name for output", /*1635:*/
                       510
/*:1635*/
      );
    output_file_name = b_make_name_string(&dvi_file);
  }

/*:531*/
  ;
  if (total_pages == 0) {
    dvi_out(pre);
    dvi_out(id_byte);

    dvi_four(25400000);
    dvi_four(473628672);
    prepare_mag();
    dvi_four(mag);
    old_setting = selector;
    selector = new_string;
    print_str(" TeX output ");
    print_int(year);
    print_char('.');
    print_two(month);
    print_char('.');
    print_two(day);
    print_char(':');
    print_two(time / 60);
    print_two(time % 60);
    selector = old_setting;
    dvi_out(cur_length);
    for (s = str_start[str_ptr]; s <= pool_ptr - 1; s++)
      dvi_out(so(str_pool[s]));
    pool_ptr = str_start[str_ptr];
  }

/*:617*/
  ;
  page_loc = dvi_offset + dvi_ptr;
  dvi_out(bop);
  for (k = 0; k <= 9; k++) dvi_four(count(k));
  dvi_four(last_bop);
  last_bop = page_loc;
  cur_v = height(p) + v_offset;
  temp_ptr = p;
  if (type(p) == vlist_node)
    vlist_out();
  else
    hlist_out();
  dvi_out(eop);
  incr(total_pages);
  cur_s = -1;
done:

/*:640*/
    ;
  if (tracing_output <= 0) print_char(']');
  dead_cycles = 0;
  update_terminal;
/*639:*/

#ifdef STAT
  if (tracing_stats > 1) {
    print_nl("Memory usage before: ");

    print_int(var_used);
    print_char('&');
    print_int(dyn_used);
    print_char(';');
  }
#endif
  flush_node_list(p);
#ifdef STAT
  if (tracing_stats > 1) {
    print_str(" after: ");
    print_int(var_used);
    print_char('&');
    print_int(dyn_used);
    print_str("; still untouched: ");
    print_int(hi_mem_min - lo_mem_max - 1);
    print_ln();
  }
#endif

/*:639*/
  ;
}

/*:638*/ /*645:*/
void scan_spec(group_code c, bool three_codes)

{
  int s;
  uint8_t spec_code;
  if (three_codes) s = saved(0);
  if (scan_keyword(/*1642:*/
                   517
/*:1642*/
                   ))
    spec_code = exactly;

  else if (scan_keyword(/*1643:*/
                        518
/*:1643*/
                        ))
    spec_code = additional;

  else {
    spec_code = additional;
    cur_val = 0;
    goto found;
  }
  scan_normal_dimen;
found:
  if (three_codes) {
    saved(0) = s;
    incr(save_ptr);
  }
  saved(0) = spec_code;
  saved(1) = cur_val;
  save_ptr = save_ptr + 2;
  new_save_level(c);
  scan_left_brace();
}

/*:645*/ /*649:*/
pointer hpack(pointer p, scaled w, small_number m) {
  pointer r;
  pointer q;
  scaled h, d, x;
  scaled s;
  pointer g;
  glue_ord o;
  internal_font_number f;
  four_quarters i;
  eight_bits hd;
  last_badness = 0;
  r = get_node(box_node_size);
  type(r) = hlist_node;
  subtype(r) = min_quarterword;
  shift_amount(r) = 0;
  q = r + list_offset;
  link(q) = p;
  h = 0; /*650:*/

  d = 0;
  x = 0;
  total_stretch[normal] = 0;
  total_shrink[normal] = 0;
  total_stretch[fil] = 0;
  total_shrink[fil] = 0;
  total_stretch[fill] = 0;
  total_shrink[fill] = 0;
  total_stretch[filll] = 0;
  total_shrink[filll] = 0

/*:650*/
      ;
  while (p != null) /*651:*/

  {
  reswitch:
    while (is_char_node(p))
/*654:*/

    {
      f = font(p);
      i = char_info(f)(character(p));
      hd = height_depth(i);
      x = x + char_width(f)(i);
      s = char_height(f)(hd);
      if (s > h) h = s;
      s = char_depth(f)(hd);
      if (s > d) d = s;
      p = link(p);
    }

/*:654*/
    ;
    if (p != null) {
      switch (type(p)) {
        case hlist_node:
        case vlist_node:
        case rule_node:
        case unset_node:
/*653:*/

        {
          x = x + width(p);
          if (type(p) >= rule_node)
            s = 0;
          else
            s = shift_amount(p);
          if (height(p) - s > h) h = height(p) - s;
          if (depth(p) + s > d) d = depth(p) + s;
        }

/*:653*/
        break;
        case ins_node:
        case mark_node:
        case adjust_node:
          if (adjust_tail != null)
/*655:*/

          {
            while (link(q) != p) q = link(q);
            if (type(p) == adjust_node) {
              link(adjust_tail) = adjust_ptr(p);
              while (link(adjust_tail) != null) adjust_tail = link(adjust_tail);
              p = link(p);
              free_node(link(q), small_node_size);
            } else {
              link(adjust_tail) = p;
              adjust_tail = p;
              p = link(p);
            }
            link(q) = p;
            p = q;
          }

/*:655*/
          break;
        case whatsit_node: /*1360:*/
          do_nothing

/*:1360*/
              ;
          break;
        case glue_node: /*656:*/

        {
          g = glue_ptr(p);
          x = x + width(g);
          o = stretch_order(g);
          total_stretch[o] = total_stretch[o] + stretch(g);
          o = shrink_order(g);
          total_shrink[o] = total_shrink[o] + shrink(g);
          if (subtype(p) >= a_leaders) {
            g = leader_ptr(p);
            if (height(g) > h) h = height(g);
            if (depth(g) > d) d = depth(g);
          }
        }

/*:656*/
        break;
        case kern_node:
        case math_node:
          x = x + width(p);
          break;
        case ligature_node: /*652:*/

        {
          mem[lig_trick] = mem[lig_char(p)];
          link(lig_trick) = link(p);
          p = lig_trick;
          goto reswitch;
        }

/*:652*/

        default:
          do_nothing;
      }
      p = link(p);
    }
  }

/*:651*/
  ;
  if (adjust_tail != null) link(adjust_tail) = null;
  height(r) = h;
  depth(r) = d;
/*657:*/

  if (m == additional) w = x + w;
  width(r) = w;
  x = w - x;
  if (x == 0) {
    glue_sign(r) = normal;
    glue_order(r) = normal;
    set_glue_ratio_zero(glue_set(r));
    goto end;
  } else if (x > 0) /*658:*/

  { /*659:*/

    if (total_stretch[filll] != 0)
      o = filll;
    else if (total_stretch[fill] != 0)
      o = fill;
    else if (total_stretch[fil] != 0)
      o = fil;
    else
      o = normal

/*:659*/
          ;
    glue_order(r) = o;
    glue_sign(r) = stretching;
    if (total_stretch[o] != 0)
      glue_set(r) = unfloat(x / (double)total_stretch[o]);

    else {
      glue_sign(r) = normal;
      set_glue_ratio_zero(glue_set(r));
    }
    if (o == normal)
      if (list_ptr(r) != null)
/*660:*/

      {
        last_badness = badness(x, total_stretch[normal]);
        if (last_badness > hbadness) {
          print_ln();
          if (last_badness > 100)
            print_nl("Underfull");
          else
            print_nl("Loose");
          print_str(" \\hbox (badness ");
          print_int(last_badness);

          goto common_ending;
        }
      }

/*:660*/
      ;
    goto end;
  }

/*:658*/

  else /*664:*/

  { /*665:*/

    if (total_shrink[filll] != 0)
      o = filll;
    else if (total_shrink[fill] != 0)
      o = fill;
    else if (total_shrink[fil] != 0)
      o = fil;
    else
      o = normal

/*:665*/
          ;
    glue_order(r) = o;
    glue_sign(r) = shrinking;
    if (total_shrink[o] != 0)
      glue_set(r) = unfloat((-x) / (double)total_shrink[o]);

    else {
      glue_sign(r) = normal;
      set_glue_ratio_zero(glue_set(r));
    }
    if ((total_shrink[o] < -x) && (o == normal) && (list_ptr(r) != null)) {
      last_badness = 1000000;
      set_glue_ratio_one(glue_set(r));
/*666:*/

      if ((-x - total_shrink[normal] > hfuzz) || (hbadness < 100)) {
        if ((overfull_rule > 0) && (-x - total_shrink[normal] > hfuzz)) {
          while (link(q) != null) q = link(q);
          link(q) = new_rule();
          width(link(q)) = overfull_rule;
        }
        print_ln();
        print_nl("Overfull \\hbox (");

        print_scaled(-x - total_shrink[normal]);
        print_str("pt too wide");
        goto common_ending;
      }

/*:666*/
      ;
    } else if (o == normal)
      if (list_ptr(r) != null)
/*667:*/

      {
        last_badness = badness(-x, total_shrink[normal]);
        if (last_badness > hbadness) {
          print_ln();
          print_nl("Tight \\hbox (badness ");
          print_int(last_badness);

          goto common_ending;
        }
      }

/*:667*/
      ;
    goto end;
  }

/*:664*/

/*:657*/
  ;
common_ending: /*663:*/

  if (output_active)
    print_str(") has occurred while \\output is active");
  else {
    if (pack_begin_line != 0) {
      if (pack_begin_line > 0)
        print_str(") in paragraph at lines ");
      else
        print_str(") in alignment at lines ");
      print_int(abs(pack_begin_line));
      print_str("--");
    } else
      print_str(") detected at line ");
    print_int(line);
  }
  print_ln();
  font_in_short_display = null_font;
  short_display(list_ptr(r));
  print_ln();
  begin_diagnostic();
  show_box(r);
  end_diagnostic(true)

/*:663*/
      ;
end:
  return r;
}

/*:649*/ /*668:*/

#define vpack(...) vpackage(__VA_ARGS__, max_dimen)

pointer vpackage(pointer p, scaled h, small_number m, scaled l) {
  pointer r;
  scaled w, d, x;
  scaled s;
  pointer g;
  glue_ord o;
  last_badness = 0;
  r = get_node(box_node_size);
  type(r) = vlist_node;
  subtype(r) = min_quarterword;
  shift_amount(r) = 0;
  list_ptr(r) = p;
  w = 0; /*650:*/

  d = 0;
  x = 0;
  total_stretch[normal] = 0;
  total_shrink[normal] = 0;
  total_stretch[fil] = 0;
  total_shrink[fil] = 0;
  total_stretch[fill] = 0;
  total_shrink[fill] = 0;
  total_stretch[filll] = 0;
  total_shrink[filll] = 0

/*:650*/
      ;
  while (p != null) /*669:*/

  {
    if (is_char_node(p))
      confusion(/*1644:*/
                519
/*:1644*/
      );

    else
      switch (type(p)) {
        case hlist_node:
        case vlist_node:
        case rule_node:
        case unset_node:
/*670:*/

        {
          x = x + d + height(p);
          d = depth(p);
          if (type(p) >= rule_node)
            s = 0;
          else
            s = shift_amount(p);
          if (width(p) + s > w) w = width(p) + s;
        }

/*:670*/
        break;
        case whatsit_node: /*1359:*/
          do_nothing

/*:1359*/
              ;
          break;
        case glue_node: /*671:*/

        {
          x = x + d;
          d = 0;
          g = glue_ptr(p);
          x = x + width(g);
          o = stretch_order(g);
          total_stretch[o] = total_stretch[o] + stretch(g);
          o = shrink_order(g);
          total_shrink[o] = total_shrink[o] + shrink(g);
          if (subtype(p) >= a_leaders) {
            g = leader_ptr(p);
            if (width(g) > w) w = width(g);
          }
        }

/*:671*/
        break;
        case kern_node: {
          x = x + d + width(p);
          d = 0;
        } break;
        default:
          do_nothing;
      }
    p = link(p);
  }

/*:669*/
  ;
  width(r) = w;
  if (d > l) {
    x = x + d - l;
    depth(r) = l;
  } else
    depth(r) = d;
/*672:*/

  if (m == additional) h = x + h;
  height(r) = h;
  x = h - x;
  if (x == 0) {
    glue_sign(r) = normal;
    glue_order(r) = normal;
    set_glue_ratio_zero(glue_set(r));
    goto end;
  } else if (x > 0) /*673:*/

  { /*659:*/

    if (total_stretch[filll] != 0)
      o = filll;
    else if (total_stretch[fill] != 0)
      o = fill;
    else if (total_stretch[fil] != 0)
      o = fil;
    else
      o = normal

/*:659*/
          ;
    glue_order(r) = o;
    glue_sign(r) = stretching;
    if (total_stretch[o] != 0)
      glue_set(r) = unfloat(x / (double)total_stretch[o]);

    else {
      glue_sign(r) = normal;
      set_glue_ratio_zero(glue_set(r));
    }
    if (o == normal)
      if (list_ptr(r) != null)
/*674:*/

      {
        last_badness = badness(x, total_stretch[normal]);
        if (last_badness > vbadness) {
          print_ln();
          if (last_badness > 100)
            print_nl("Underfull");
          else
            print_nl("Loose");
          print_str(" \\vbox (badness ");
          print_int(last_badness);

          goto common_ending;
        }
      }

/*:674*/
      ;
    goto end;
  }

/*:673*/

  else /*676:*/

  { /*665:*/

    if (total_shrink[filll] != 0)
      o = filll;
    else if (total_shrink[fill] != 0)
      o = fill;
    else if (total_shrink[fil] != 0)
      o = fil;
    else
      o = normal

/*:665*/
          ;
    glue_order(r) = o;
    glue_sign(r) = shrinking;
    if (total_shrink[o] != 0)
      glue_set(r) = unfloat((-x) / (double)total_shrink[o]);

    else {
      glue_sign(r) = normal;
      set_glue_ratio_zero(glue_set(r));
    }
    if ((total_shrink[o] < -x) && (o == normal) && (list_ptr(r) != null)) {
      last_badness = 1000000;
      set_glue_ratio_one(glue_set(r));
/*677:*/

      if ((-x - total_shrink[normal] > vfuzz) || (vbadness < 100)) {
        print_ln();
        print_nl("Overfull \\vbox (");

        print_scaled(-x - total_shrink[normal]);
        print_str("pt too high");
        goto common_ending;
      }

/*:677*/
      ;
    } else if (o == normal)
      if (list_ptr(r) != null)
/*678:*/

      {
        last_badness = badness(-x, total_shrink[normal]);
        if (last_badness > vbadness) {
          print_ln();
          print_nl("Tight \\vbox (badness ");
          print_int(last_badness);

          goto common_ending;
        }
      }

/*:678*/
      ;
    goto end;
  }

/*:676*/

/*:672*/
  ;
common_ending: /*675:*/

  if (output_active)
    print_str(") has occurred while \\output is active");
  else {
    if (pack_begin_line != 0) {
      print_str(") in alignment at lines ");
      print_int(abs(pack_begin_line));
      print_str("--");
    } else
      print_str(") detected at line ");
    print_int(line);
    print_ln();
  }
  begin_diagnostic();
  show_box(r);
  end_diagnostic(true)

/*:675*/
      ;
end:
  return r;
}

/*:668*/ /*679:*/
void append_to_vlist(pointer b) {
  scaled d;
  pointer p;
  if (prev_depth > ignore_depth) {
    d = width(baseline_skip) - prev_depth - height(b);
    if (d < line_skip_limit)
      p = new_param_glue(line_skip_code);
    else {
      p = new_skip_param(baseline_skip_code);
      width(temp_ptr) = d;
    }
    link(tail) = p;
    tail = p;
  }
  link(tail) = b;
  tail = b;
  prev_depth = depth(b);
}

/*:679*/ /*686:*/
pointer new_noad(void) {
  pointer p;
  p = get_node(noad_size);
  type(p) = ord_noad;
  subtype(p) = normal;
  mem[nucleus(p)].hh = empty_field;
  mem[subscr(p)].hh = empty_field;
  mem[supscr(p)].hh = empty_field;
  return p;
}

/*:686*/ /*688:*/
pointer new_style(small_number s) {
  pointer p;
  p = get_node(style_node_size);
  type(p) = style_node;
  subtype(p) = s;
  width(p) = 0;
  depth(p) = 0;
  return p;
}

/*:688*/ /*689:*/
pointer new_choice(void) {
  pointer p;
  p = get_node(style_node_size);
  type(p) = choice_node;
  subtype(p) = 0;
  display_mlist(p) = null;
  text_mlist(p) = null;
  script_mlist(p) = null;
  script_script_mlist(p) = null;
  return p;
}

/*:689*/ /*693:*/
void show_info(void) { show_node_list(info(temp_ptr)); }

/*:693*/ /*704:*/
pointer fraction_rule(scaled t)

{
  pointer p;
  p = new_rule();
  height(p) = t;
  depth(p) = 0;
  return p;
}

/*:704*/ /*705:*/
pointer overbar(pointer b, scaled k, scaled t) {
  pointer p, q;
  p = new_kern(k);
  link(p) = b;
  q = fraction_rule(t);
  link(q) = p;
  p = new_kern(t);
  link(p) = q;
  return vpack(p, natural);
}

/*:705*/ /*706:*/
/*709:*/

pointer char_box(internal_font_number f, quarterword c) {
  four_quarters q;
  eight_bits hd;
  pointer b, p;
  q = char_info(f)(c);
  hd = height_depth(q);
  b = new_null_box();
  width(b) = char_width(f)(q) + char_italic(f)(q);
  height(b) = char_height(f)(hd);
  depth(b) = char_depth(f)(hd);
  p = get_avail();
  character(p) = c;
  font(p) = f;
  list_ptr(b) = p;
  return b;
}

/*:709*/ /*711:*/

void stack_into_box(pointer b, internal_font_number f, quarterword c) {
  pointer p;
  p = char_box(f, c);
  link(p) = list_ptr(b);
  list_ptr(b) = p;
  height(b) = height(p);
}

/*:711*/ /*712:*/

scaled height_plus_depth(internal_font_number f, quarterword c) {
  four_quarters q;
  eight_bits hd;
  q = char_info(f)(c);
  hd = height_depth(q);
  return char_height(f)(hd) + char_depth(f)(hd);
}

/*:712*/

pointer var_delimiter(pointer d, small_number s, scaled v) {
  pointer b;
  internal_font_number f, g;
  quarterword c, x, y;
  int m, n;
  scaled u;
  scaled w;
  four_quarters q;
  eight_bits hd;
  four_quarters r;
  small_number z;
  bool large_attempt;
  f = null_font;
  w = 0;
  large_attempt = false;
  z = small_fam(d);
  x = small_char(d);
  loop { /*707:*/

    if ((z != 0) || (x != min_quarterword)) {
      z = z + s + 16;
      do {
        z = z - 16;
        g = fam_fnt(z);
        if (g != null_font)
/*708:*/

        {
          y = x;
          if ((qo(y) >= font_bc[g]) && (qo(y) <= font_ec[g])) {
          resume:
            q = char_info(g)(y);
            if (char_exists(q)) {
              if (char_tag(q) == ext_tag) {
                f = g;
                c = y;
                goto found;
              }
              hd = height_depth(q);
              u = char_height(g)(hd) + char_depth(g)(hd);
              if (u > w) {
                f = g;
                c = y;
                w = u;
                if (u >= v) goto found;
              }
              if (char_tag(q) == list_tag) {
                y = rem_byte(q);
                goto resume;
              }
            }
          }
        }

/*:708*/
        ;
      } while (!(z < 16));
    }

/*:707*/
    ;
    if (large_attempt) goto found;
    large_attempt = true;
    z = large_fam(d);
    x = large_char(d);
  }
found:
  if (f != null_font) /*710:*/

    if (char_tag(q) == ext_tag)
/*713:*/

    {
      b = new_null_box();
      type(b) = vlist_node;
      r = font_info[exten_base[f] + rem_byte(q)].qqqq;
/*714:*/

      c = ext_rep(r);
      u = height_plus_depth(f, c);
      w = 0;
      q = char_info(f)(c);
      width(b) = char_width(f)(q) + char_italic(f)(q);
      c = ext_bot(r);
      if (c != min_quarterword) w = w + height_plus_depth(f, c);
      c = ext_mid(r);
      if (c != min_quarterword) w = w + height_plus_depth(f, c);
      c = ext_top(r);
      if (c != min_quarterword) w = w + height_plus_depth(f, c);
      n = 0;
      if (u > 0)
        while (w < v) {
          w = w + u;
          incr(n);
          if (ext_mid(r) != min_quarterword) w = w + u;
        }

/*:714*/
        ;
      c = ext_bot(r);
      if (c != min_quarterword) stack_into_box(b, f, c);
      c = ext_rep(r);
      for (m = 1; m <= n; m++) stack_into_box(b, f, c);
      c = ext_mid(r);
      if (c != min_quarterword) {
        stack_into_box(b, f, c);
        c = ext_rep(r);
        for (m = 1; m <= n; m++) stack_into_box(b, f, c);
      }
      c = ext_top(r);
      if (c != min_quarterword) stack_into_box(b, f, c);
      depth(b) = w - height(b);
    }

/*:713*/

    else
      b = char_box(f, c)

/*:710*/
          ;
  else {
    b = new_null_box();
    width(b) = null_delimiter_space;
  }
  shift_amount(b) = half(height(b) - depth(b)) - axis_height(s);
  return b;
}

/*:706*/ /*715:*/
pointer rebox(pointer b, scaled w) {
  pointer p;
  internal_font_number f;
  scaled v;
  if ((width(b) != w) && (list_ptr(b) != null)) {
    if (type(b) == vlist_node) b = hpack(b, natural);
    p = list_ptr(b);
    if ((is_char_node(p)) && (link(p) == null)) {
      f = font(p);
      v = char_width(f)(char_info(f)(character(p)));
      if (v != width(b)) link(p) = new_kern(width(b) - v);
    }
    free_node(b, box_node_size);
    b = new_glue(ss_glue);
    link(b) = p;
    while (link(p) != null) p = link(p);
    link(p) = new_glue(ss_glue);
    return hpack(b, w, exactly);
  } else {
    width(b) = w;
    return b;
  }
}

/*:715*/ /*716:*/
pointer math_glue(pointer g, scaled m) {
  pointer p;
  int n;
  scaled f;
  n = x_over_n(m, 0200000);
  f = rem;
  if (f < 0) {
    decr(n);
    f = f + 0200000;
  }
  p = get_node(glue_spec_size);
  width(p) = mu_mult(width(g));
  stretch_order(p) = stretch_order(g);
  if (stretch_order(p) == normal)
    stretch(p) = mu_mult(stretch(g));
  else
    stretch(p) = stretch(g);
  shrink_order(p) = shrink_order(g);
  if (shrink_order(p) == normal)
    shrink(p) = mu_mult(shrink(g));
  else
    shrink(p) = shrink(g);
  return p;
}

/*:716*/ /*717:*/
void math_kern(pointer p, scaled m) {
  int n;
  scaled f;
  if (subtype(p) == mu_glue) {
    n = x_over_n(m, 0200000);
    f = rem;
    if (f < 0) {
      decr(n);
      f = f + 0200000;
    }
    width(p) = mu_mult(width(p));
    subtype(p) = explicit;
  }
}

/*:717*/ /*718:*/
void flush_math(void) {
  flush_node_list(link(head));
  flush_node_list(incompleat_noad);
  link(head) = null;
  tail = head;
  incompleat_noad = null;
}

/*:718*/ /*720:*/
void mlist_to_hlist(void);
pointer clean_box(pointer p, small_number s) {
  pointer q;
  small_number save_style;
  pointer x;
  pointer r;
  switch (math_type(p)) {
    case math_char: {
      cur_mlist = new_noad();
      mem[nucleus(cur_mlist)] = mem[p];
    } break;
    case sub_box: {
      q = info(p);
      goto found;
    }
    case sub_mlist:
      cur_mlist = info(p);
      break;
    default: {
      q = new_null_box();
      goto found;
    }
  }
  save_style = cur_style;
  cur_style = s;
  mlist_penalties = false;
  mlist_to_hlist();
  q = link(temp_head);
  cur_style = save_style;
/*703:*/

  {
    if (cur_style < script_style)
      cur_size = text_size;
    else
      cur_size = 16 * ((cur_style - text_style) / 2);
    cur_mu = x_over_n(math_quad(cur_size), 18);
  }

/*:703*/
  ;
found:
  if (is_char_node(q) || (q == null))
    x = hpack(q, natural);
  else if ((link(q) == null) && (type(q) <= vlist_node) &&
           (shift_amount(q) == 0))
    x = q;
  else
    x = hpack(q, natural);
/*721:*/

  q = list_ptr(x);
  if (is_char_node(q)) {
    r = link(q);
    if (r != null)
      if (link(r) == null)
        if (!is_char_node(r))
          if (type(r) == kern_node) {
            free_node(r, small_node_size);
            link(q) = null;
          }
  }

/*:721*/
  ;
  return x;
}

/*:720*/ /*722:*/
void fetch(pointer a) {
  cur_c = character(a);
  cur_f = fam_fnt(fam(a) + cur_size);
  if (cur_f == null_font)
/*723:*/

  {
    print_err("");
    print_size(cur_size);
    print_char(' ');
    print_int(fam(a));
    print_str(" is undefined (character ");
    print_ASCII(qo(cur_c));
    print_char(')');
    help4("Somewhere in the math formula just ended, you used the")(
        "stated character from an undefined font family. For example,")(
        "plain TeX doesn't allow \\it or \\sl in subscripts. Proceed,")(
        "and I'll try to forget that I needed that character.");
    error();
    cur_i = null_character;
    math_type(a) = empty;
  }
/*:723*/

  else {
    if ((qo(cur_c) >= font_bc[cur_f]) && (qo(cur_c) <= font_ec[cur_f]))
      cur_i = char_info(cur_f)(cur_c);
    else
      cur_i = null_character;
    if (!(char_exists(cur_i))) {
      char_warning(cur_f, qo(cur_c));
      math_type(a) = empty;
      cur_i = null_character;
    }
  }
}

/*:722*/ /*726:*/
/*734:*/

void make_over(pointer q) {
  info(nucleus(q)) =
      overbar(clean_box(nucleus(q), cramped_style(cur_style)),
              3 * default_rule_thickness, default_rule_thickness);
  math_type(nucleus(q)) = sub_box;
}

/*:734*/ /*735:*/

void make_under(pointer q) {
  pointer p, x, y;
  scaled delta;
  x = clean_box(nucleus(q), cur_style);
  p = new_kern(3 * default_rule_thickness);
  link(x) = p;
  link(p) = fraction_rule(default_rule_thickness);
  y = vpack(x, natural);
  delta = height(y) + depth(y) + default_rule_thickness;
  height(y) = height(x);
  depth(y) = delta - height(y);
  info(nucleus(q)) = y;
  math_type(nucleus(q)) = sub_box;
}

/*:735*/ /*736:*/

void make_vcenter(pointer q) {
  pointer v;
  scaled delta;
  v = info(nucleus(q));
  if (type(v) != vlist_node)
    confusion(/*1561:*/
              436
/*:1561*/
    );

  delta = height(v) + depth(v);
  height(v) = axis_height(cur_size) + half(delta);
  depth(v) = delta - height(v);
}

/*:736*/ /*737:*/

void make_radical(pointer q) {
  pointer x, y;
  scaled delta, clr;
  x = clean_box(nucleus(q), cramped_style(cur_style));
  if (cur_style < text_style)
    clr = default_rule_thickness + (abs(math_x_height(cur_size)) / 4);
  else {
    clr = default_rule_thickness;
    clr = clr + (abs(clr) / 4);
  }
  y = var_delimiter(left_delimiter(q), cur_size,
                    height(x) + depth(x) + clr + default_rule_thickness);
  delta = depth(y) - (height(x) + depth(x) + clr);
  if (delta > 0) clr = clr + half(delta);
  shift_amount(y) = -(height(x) + clr);
  link(y) = overbar(x, clr, height(y));
  info(nucleus(q)) = hpack(y, natural);
  math_type(nucleus(q)) = sub_box;
}

/*:737*/ /*738:*/

void make_math_accent(pointer q) {
  pointer p, x, y;
  int a;
  quarterword c;
  internal_font_number f;
  four_quarters i;
  scaled s;
  scaled h;
  scaled delta;
  scaled w;
  fetch(accent_chr(q));
  if (char_exists(cur_i)) {
    i = cur_i;
    c = cur_c;
    f = cur_f;
/*741:*/

    s = 0;
    if (math_type(nucleus(q)) == math_char) {
      fetch(nucleus(q));
      if (char_tag(cur_i) == lig_tag) {
        a = lig_kern_start(cur_f)(cur_i);
        cur_i = font_info[a].qqqq;
        if (skip_byte(cur_i) > stop_flag) {
          a = lig_kern_restart(cur_f)(cur_i);
          cur_i = font_info[a].qqqq;
        }
        loop {
          if (qo(next_char(cur_i)) == skew_char[cur_f]) {
            if (op_byte(cur_i) >= kern_flag)
              if (skip_byte(cur_i) <= stop_flag) s = char_kern(cur_f)(cur_i);
            goto done1;
          }
          if (skip_byte(cur_i) >= stop_flag) goto done1;
          a = a + qo(skip_byte(cur_i)) + 1;
          cur_i = font_info[a].qqqq;
        }
      }
    }
  done1:

/*:741*/
      ;
    x = clean_box(nucleus(q), cramped_style(cur_style));
    w = width(x);
    h = height(x);
/*740:*/

    loop {
      if (char_tag(i) != list_tag) goto done;
      y = rem_byte(i);
      i = char_info(f)(y);
      if (!char_exists(i)) goto done;
      if (char_width(f)(i) > w) goto done;
      c = y;
    }
  done:

/*:740*/
      ;
    if (h < x_height(f))
      delta = h;
    else
      delta = x_height(f);
    if ((math_type(supscr(q)) != empty) || (math_type(subscr(q)) != empty))
      if (math_type(nucleus(q)) == math_char)
/*742:*/

      {
        flush_node_list(x);
        x = new_noad();
        mem[nucleus(x)] = mem[nucleus(q)];
        mem[supscr(x)] = mem[supscr(q)];
        mem[subscr(x)] = mem[subscr(q)];
        mem[supscr(q)].hh = empty_field;
        mem[subscr(q)].hh = empty_field;
        math_type(nucleus(q)) = sub_mlist;
        info(nucleus(q)) = x;
        x = clean_box(nucleus(q), cur_style);
        delta = delta + height(x) - h;
        h = height(x);
      }

/*:742*/
      ;
    y = char_box(f, c);
    shift_amount(y) = s + half(w - width(y));
    width(y) = 0;
    p = new_kern(-delta);
    link(p) = x;
    link(y) = p;
    y = vpack(y, natural);
    width(y) = width(x);
    if (height(y) < h) /*739:*/

    {
      p = new_kern(h - height(y));
      link(p) = list_ptr(y);
      list_ptr(y) = p;
      height(y) = h;
    }

/*:739*/
    ;
    info(nucleus(q)) = y;
    math_type(nucleus(q)) = sub_box;
  }
}

/*:738*/ /*743:*/

void make_fraction(pointer q) {
  pointer p, v, x, y, z;
  scaled delta, delta1, delta2, shift_up, shift_down, clr;

  if (thickness(q) == default_code) thickness(q) = default_rule_thickness;
/*744:*/

  x = clean_box(numerator(q), num_style(cur_style));
  z = clean_box(denominator(q), denom_style(cur_style));
  if (width(x) < width(z))
    x = rebox(x, width(z));
  else
    z = rebox(z, width(x));
  if (cur_style < text_style) {
    shift_up = num1(cur_size);
    shift_down = denom1(cur_size);
  } else {
    shift_down = denom2(cur_size);
    if (thickness(q) != 0)
      shift_up = num2(cur_size);
    else
      shift_up = num3(cur_size);
  }

/*:744*/
  ;
  if (thickness(q) == 0) /*745:*/

  {
    if (cur_style < text_style)
      clr = 7 * default_rule_thickness;
    else
      clr = 3 * default_rule_thickness;
    delta = half(clr - ((shift_up - depth(x)) - (height(z) - shift_down)));
    if (delta > 0) {
      shift_up = shift_up + delta;
      shift_down = shift_down + delta;
    }
  }
/*:745*/

  else /*746:*/

  {
    if (cur_style < text_style)
      clr = 3 * thickness(q);
    else
      clr = thickness(q);
    delta = half(thickness(q));
    delta1 = clr - ((shift_up - depth(x)) - (axis_height(cur_size) + delta));
    delta2 = clr - ((axis_height(cur_size) - delta) - (height(z) - shift_down));
    if (delta1 > 0) shift_up = shift_up + delta1;
    if (delta2 > 0) shift_down = shift_down + delta2;
  }

/*:746*/
  ;
/*747:*/

  v = new_null_box();
  type(v) = vlist_node;
  height(v) = shift_up + height(x);
  depth(v) = depth(z) + shift_down;
  width(v) = width(x);
  if (thickness(q) == 0) {
    p = new_kern((shift_up - depth(x)) - (height(z) - shift_down));
    link(p) = z;
  } else {
    y = fraction_rule(thickness(q));
    p = new_kern((axis_height(cur_size) - delta) - (height(z) - shift_down));
    link(y) = p;
    link(p) = z;
    p = new_kern((shift_up - depth(x)) - (axis_height(cur_size) + delta));
    link(p) = y;
  }
  link(x) = p;
  list_ptr(v) = x

/*:747*/
      ;
/*748:*/

  if (cur_style < text_style)
    delta = delim1(cur_size);
  else
    delta = delim2(cur_size);
  x = var_delimiter(left_delimiter(q), cur_size, delta);
  link(x) = v;
  z = var_delimiter(right_delimiter(q), cur_size, delta);
  link(v) = z;
  new_hlist(q) = hpack(x, natural)

/*:748*/
      ;
}

/*:743*/ /*749:*/

scaled make_op(pointer q) {
  scaled delta;
  pointer p, v, x, y, z;
  quarterword c;
  four_quarters i;
  scaled shift_up, shift_down;
  if ((subtype(q) == normal) && (cur_style < text_style)) subtype(q) = limits;
  if (math_type(nucleus(q)) == math_char) {
    fetch(nucleus(q));
    if ((cur_style < text_style) && (char_tag(cur_i) == list_tag)) {
      c = rem_byte(cur_i);
      i = char_info(cur_f)(c);
      if (char_exists(i)) {
        cur_c = c;
        cur_i = i;
        character(nucleus(q)) = c;
      }
    }
    delta = char_italic(cur_f)(cur_i);
    x = clean_box(nucleus(q), cur_style);
    if ((math_type(subscr(q)) != empty) && (subtype(q) != limits))
      width(x) = width(x) - delta;
    shift_amount(x) = half(height(x) - depth(x)) - axis_height(cur_size);

    math_type(nucleus(q)) = sub_box;
    info(nucleus(q)) = x;
  } else
    delta = 0;
  if (subtype(q) == limits)
/*750:*/

  {
    x = clean_box(supscr(q), sup_style(cur_style));
    y = clean_box(nucleus(q), cur_style);
    z = clean_box(subscr(q), sub_style(cur_style));
    v = new_null_box();
    type(v) = vlist_node;
    width(v) = width(y);
    if (width(x) > width(v)) width(v) = width(x);
    if (width(z) > width(v)) width(v) = width(z);
    x = rebox(x, width(v));
    y = rebox(y, width(v));
    z = rebox(z, width(v));
    shift_amount(x) = half(delta);
    shift_amount(z) = -shift_amount(x);
    height(v) = height(y);
    depth(v) = depth(y);
/*751:*/

    if (math_type(supscr(q)) == empty) {
      free_node(x, box_node_size);
      list_ptr(v) = y;
    } else {
      shift_up = big_op_spacing3 - depth(x);
      if (shift_up < big_op_spacing1) shift_up = big_op_spacing1;
      p = new_kern(shift_up);
      link(p) = y;
      link(x) = p;
      p = new_kern(big_op_spacing5);
      link(p) = x;
      list_ptr(v) = p;
      height(v) = height(v) + big_op_spacing5 + height(x) + depth(x) + shift_up;
    }
    if (math_type(subscr(q)) == empty)
      free_node(z, box_node_size);
    else {
      shift_down = big_op_spacing4 - height(z);
      if (shift_down < big_op_spacing2) shift_down = big_op_spacing2;
      p = new_kern(shift_down);
      link(y) = p;
      link(p) = z;
      p = new_kern(big_op_spacing5);
      link(z) = p;
      depth(v) = depth(v) + big_op_spacing5 + height(z) + depth(z) + shift_down;
    }

/*:751*/
    ;
    new_hlist(q) = v;
  }

/*:750*/
  ;
  return delta;
}

/*:749*/ /*752:*/

void make_ord(pointer q) {
  int a;
  pointer p, r;
restart:
  if (math_type(subscr(q)) == empty)
    if (math_type(supscr(q)) == empty)
      if (math_type(nucleus(q)) == math_char) {
        p = link(q);
        if (p != null)
          if ((type(p) >= ord_noad) && (type(p) <= punct_noad))
            if (math_type(nucleus(p)) == math_char)
              if (fam(nucleus(p)) == fam(nucleus(q))) {
                math_type(nucleus(q)) = math_text_char;
                fetch(nucleus(q));
                if (char_tag(cur_i) == lig_tag) {
                  a = lig_kern_start(cur_f)(cur_i);
                  cur_c = character(nucleus(p));
                  cur_i = font_info[a].qqqq;
                  if (skip_byte(cur_i) > stop_flag) {
                    a = lig_kern_restart(cur_f)(cur_i);
                    cur_i = font_info[a].qqqq;
                  }
                  loop { /*753:*/

                    if (next_char(cur_i) == cur_c)
                      if (skip_byte(cur_i) <= stop_flag)
                        if (op_byte(cur_i) >= kern_flag) {
                          p = new_kern(char_kern(cur_f)(cur_i));
                          link(p) = link(q);
                          link(q) = p;
                          return;
                        } else {
                          check_interrupt;
                          switch (op_byte(cur_i)) {
                            qi(case 1)
                                : qi(case 5)
                                : character(nucleus(q)) = rem_byte(cur_i);
                            break;
                            qi(case 2)
                                : qi(case 6)
                                : character(nucleus(p)) = rem_byte(cur_i);
                            break;
                            qi(case 3) : qi(case 7) : qi(case 11) : {
                              r = new_noad();
                              character(nucleus(r)) = rem_byte(cur_i);
                              fam(nucleus(r)) = fam(nucleus(q));
                              link(q) = r;
                              link(r) = p;
                              if (op_byte(cur_i) < qi(11))
                                math_type(nucleus(r)) = math_char;
                              else
                                math_type(nucleus(r)) = math_text_char;
                            }
                            break;
                            default: {
                              link(q) = link(p);
                              character(nucleus(q)) = rem_byte(cur_i);
                              mem[subscr(q)] = mem[subscr(p)];
                              mem[supscr(q)] = mem[supscr(p)];
                              free_node(p, noad_size);
                            }
                          }
                          if (op_byte(cur_i) > qi(3)) return;
                          math_type(nucleus(q)) = math_char;
                          goto restart;
                        }

/*:753*/
                        ;
                    if (skip_byte(cur_i) >= stop_flag) return;
                    a = a + qo(skip_byte(cur_i)) + 1;
                    cur_i = font_info[a].qqqq;
                  }
                }
              }
      }
}

/*:752*/ /*756:*/

void make_scripts(pointer q, scaled delta) {
  pointer p, x, y, z;
  scaled shift_up, shift_down, clr;
  small_number t;
  p = new_hlist(q);
  if (is_char_node(p)) {
    shift_up = 0;
    shift_down = 0;
  } else {
    z = hpack(p, natural);
    if (cur_style < script_style)
      t = script_size;
    else
      t = script_script_size;
    shift_up = height(z) - sup_drop(t);
    shift_down = depth(z) + sub_drop(t);
    free_node(z, box_node_size);
  }
  if (math_type(supscr(q)) == empty)
/*757:*/

  {
    x = clean_box(subscr(q), sub_style(cur_style));
    width(x) = width(x) + script_space;
    if (shift_down < sub1(cur_size)) shift_down = sub1(cur_size);
    clr = height(x) - (abs(math_x_height(cur_size) * 4) / 5);
    if (shift_down < clr) shift_down = clr;
    shift_amount(x) = shift_down;
  }

/*:757*/

  else { /*758:*/

    {
      x = clean_box(supscr(q), sup_style(cur_style));
      width(x) = width(x) + script_space;
      if (odd(cur_style))
        clr = sup3(cur_size);
      else if (cur_style < text_style)
        clr = sup1(cur_size);
      else
        clr = sup2(cur_size);
      if (shift_up < clr) shift_up = clr;
      clr = depth(x) + (abs(math_x_height(cur_size)) / 4);
      if (shift_up < clr) shift_up = clr;
    }

/*:758*/
    ;
    if (math_type(subscr(q)) == empty)
      shift_amount(x) = -shift_up;
    else /*759:*/

    {
      y = clean_box(subscr(q), sub_style(cur_style));
      width(y) = width(y) + script_space;
      if (shift_down < sub2(cur_size)) shift_down = sub2(cur_size);
      clr = 4 * default_rule_thickness -
            ((shift_up - depth(x)) - (height(y) - shift_down));
      if (clr > 0) {
        shift_down = shift_down + clr;
        clr = (abs(math_x_height(cur_size) * 4) / 5) - (shift_up - depth(x));
        if (clr > 0) {
          shift_up = shift_up + clr;
          shift_down = shift_down - clr;
        }
      }
      shift_amount(x) = delta;
      p = new_kern((shift_up - depth(x)) - (height(y) - shift_down));
      link(x) = p;
      link(p) = y;
      x = vpack(x, natural);
      shift_amount(x) = shift_down;
    }

/*:759*/
    ;
  }
  if (new_hlist(q) == null)
    new_hlist(q) = x;
  else {
    p = new_hlist(q);
    while (link(p) != null) p = link(p);
    link(p) = x;
  }
}

/*:756*/ /*762:*/

small_number make_left_right(pointer q, small_number style, scaled max_d,
                             scaled max_h) {
  scaled delta, delta1, delta2;
  if (style < script_style)
    cur_size = text_size;
  else
    cur_size = 16 * ((style - text_style) / 2);
  delta2 = max_d + axis_height(cur_size);
  delta1 = max_h + max_d - delta2;
  if (delta2 > delta1) delta1 = delta2;
  delta = (delta1 / 500) * delimiter_factor;
  delta2 = delta1 + delta1 - delimiter_shortfall;
  if (delta < delta2) delta = delta2;
  new_hlist(q) = var_delimiter(delimiter(q), cur_size, delta);
  return type(q) - (left_noad - open_noad);
}

/*:762*/

void mlist_to_hlist(void) {
  pointer mlist;
  bool penalties;
  small_number style;
  small_number save_style;
  pointer q;
  pointer r;
  small_number r_type;
  small_number t;
  pointer p, x, y, z;
  int pen;
  small_number s;
  scaled max_h, max_d;
  scaled delta;
  mlist = cur_mlist;
  penalties = mlist_penalties;
  style = cur_style;
  q = mlist;
  r = null;
  r_type = op_noad;
  max_h = 0;
  max_d = 0;
/*703:*/

  {
    if (cur_style < script_style)
      cur_size = text_size;
    else
      cur_size = 16 * ((cur_style - text_style) / 2);
    cur_mu = x_over_n(math_quad(cur_size), 18);
  }

/*:703*/
  ;
  while (q != null) /*727:*/

  { /*728:*/

  reswitch:
    delta = 0;
    switch (type(q)) {
      case bin_noad:
        switch (r_type) {
          case bin_noad:
          case op_noad:
          case rel_noad:
          case open_noad:
          case punct_noad:
          case left_noad: {
            type(q) = ord_noad;
            goto reswitch;
          }
          default:
            do_nothing;
        }
        break;
      case rel_noad:
      case close_noad:
      case punct_noad:
      case right_noad: {
/*729:*/

        if (r_type == bin_noad)
          type(r) = ord_noad

/*:729*/
              ;
        if (type(q) == right_noad) goto done_with_noad;
      } break;
/*733:*/

      case left_noad:
        goto done_with_noad;
      case fraction_noad: {
        make_fraction(q);
        goto check_dimensions;
      }
      case op_noad: {
        delta = make_op(q);
        if (subtype(q) == limits) goto check_dimensions;
      } break;
      case ord_noad:
        make_ord(q);
        break;
      case open_noad:
      case inner_noad:
        do_nothing;
        break;
      case radical_noad:
        make_radical(q);
        break;
      case over_noad:
        make_over(q);
        break;
      case under_noad:
        make_under(q);
        break;
      case accent_noad:
        make_math_accent(q);
        break;
      case vcenter_noad:
        make_vcenter(q);
        break;

/*:733*/

/*730:*/

      case style_node: {
        cur_style = subtype(q);
/*703:*/

        {
          if (cur_style < script_style)
            cur_size = text_size;
          else
            cur_size = 16 * ((cur_style - text_style) / 2);
          cur_mu = x_over_n(math_quad(cur_size), 18);
        }

/*:703*/
        ;
        goto done_with_node;
      }
      case choice_node: /*731:*/

      {
        switch (cur_style / 2) {
          case 0:
            choose_mlist(display_mlist) break;
          case 1:
            choose_mlist(text_mlist) break;
          case 2:
            choose_mlist(script_mlist) break;
          case 3:
            choose_mlist(script_script_mlist);
        }
        flush_node_list(display_mlist(q));
        flush_node_list(text_mlist(q));
        flush_node_list(script_mlist(q));
        flush_node_list(script_script_mlist(q));
        type(q) = style_node;
        subtype(q) = cur_style;
        width(q) = 0;
        depth(q) = 0;
        if (p != null) {
          z = link(q);
          link(q) = p;
          while (link(p) != null) p = link(p);
          link(p) = z;
        }
        goto done_with_node;
      }

/*:731*/

      case ins_node:
      case mark_node:
      case adjust_node:
      case whatsit_node:
      case penalty_node:
      case disc_node:
        goto done_with_node;
      case rule_node: {
        if (height(q) > max_h) max_h = height(q);
        if (depth(q) > max_d) max_d = depth(q);
        goto done_with_node;
      }
      case glue_node: { /*732:*/

        if (subtype(q) == mu_glue) {
          x = glue_ptr(q);
          y = math_glue(x, cur_mu);
          delete_glue_ref(x);
          glue_ptr(q) = y;
          subtype(q) = normal;
        } else if ((cur_size != text_size) && (subtype(q) == cond_math_glue)) {
          p = link(q);
          if (p != null)
            if ((type(p) == glue_node) || (type(p) == kern_node)) {
              link(q) = link(p);
              link(p) = null;
              flush_node_list(p);
            }
        }

/*:732*/
        ;
        goto done_with_node;
      }
      case kern_node: {
        math_kern(q, cur_mu);
        goto done_with_node;
      }

/*:730*/

      default:
        confusion(/*1664:*/
                  539
/*:1664*/
        );
    }
/*754:*/

    switch (math_type(nucleus(q))) {
      case math_char:
      case math_text_char:
/*755:*/

      {
        fetch(nucleus(q));
        if (char_exists(cur_i)) {
          delta = char_italic(cur_f)(cur_i);
          p = new_character(cur_f, qo(cur_c));
          if ((math_type(nucleus(q)) == math_text_char) && (space(cur_f) != 0))
            delta = 0;
          if ((math_type(subscr(q)) == empty) && (delta != 0)) {
            link(p) = new_kern(delta);
            delta = 0;
          }
        } else
          p = null;
      }

/*:755*/
      break;
      case empty:
        p = null;
        break;
      case sub_box:
        p = info(nucleus(q));
        break;
      case sub_mlist: {
        cur_mlist = info(nucleus(q));
        save_style = cur_style;
        mlist_penalties = false;
        mlist_to_hlist();

        cur_style = save_style; /*703:*/

        {
          if (cur_style < script_style)
            cur_size = text_size;
          else
            cur_size = 16 * ((cur_style - text_style) / 2);
          cur_mu = x_over_n(math_quad(cur_size), 18);
        }

/*:703*/
        ;
        p = hpack(link(temp_head), natural);
      } break;
      default:
        confusion(/*1665:*/
                  540
/*:1665*/
        );
    }
    new_hlist(q) = p;
    if ((math_type(subscr(q)) == empty) && (math_type(supscr(q)) == empty))
      goto check_dimensions;
    make_scripts(q, delta)

/*:754*/

/*:728*/
        ;
  check_dimensions:
    z = hpack(new_hlist(q), natural);
    if (height(z) > max_h) max_h = height(z);
    if (depth(z) > max_d) max_d = depth(z);
    free_node(z, box_node_size);
  done_with_noad:
    r = q;
    r_type = type(r);
  done_with_node:
    q = link(q);
  }

/*:727*/
  ;
/*729:*/

  if (r_type == bin_noad)
    type(r) = ord_noad

/*:729*/
        ;
/*760:*/

  p = temp_head;
  link(p) = null;
  q = mlist;
  r_type = 0;
  cur_style = style;
/*703:*/

  {
    if (cur_style < script_style)
      cur_size = text_size;
    else
      cur_size = 16 * ((cur_style - text_style) / 2);
    cur_mu = x_over_n(math_quad(cur_size), 18);
  }

/*:703*/
  ;
  while (q != null) { /*761:*/

    t = ord_noad;
    s = noad_size;
    pen = inf_penalty;
    switch (type(q)) {
      case op_noad:
      case open_noad:
      case close_noad:
      case punct_noad:
      case inner_noad:
        t = type(q);
        break;
      case bin_noad: {
        t = bin_noad;
        pen = bin_op_penalty;
      } break;
      case rel_noad: {
        t = rel_noad;
        pen = rel_penalty;
      } break;
      case ord_noad:
      case vcenter_noad:
      case over_noad:
      case under_noad:
        do_nothing;
        break;
      case radical_noad:
        s = radical_noad_size;
        break;
      case accent_noad:
        s = accent_noad_size;
        break;
      case fraction_noad:
        s = fraction_noad_size;
        break;
      case left_noad:
      case right_noad:
        t = make_left_right(q, style, max_d, max_h);
        break;
      case style_node: /*763:*/

      {
        cur_style = subtype(q);
        s = style_node_size;
/*703:*/

        {
          if (cur_style < script_style)
            cur_size = text_size;
          else
            cur_size = 16 * ((cur_style - text_style) / 2);
          cur_mu = x_over_n(math_quad(cur_size), 18);
        }

/*:703*/
        ;
        goto delete_q;
      }

/*:763*/

      case whatsit_node:
      case penalty_node:
      case rule_node:
      case disc_node:
      case adjust_node:
      case ins_node:
      case mark_node:
      case glue_node:
      case kern_node: {
        link(p) = q;
        p = q;
        q = link(q);
        link(p) = null;
        goto done;
      }
      default:
        confusion(/*1666:*/
                  541
/*:1666*/
        );
    }

/*:761*/
    ;
/*766:*/

    if (r_type > 0) {
      switch (so(str_pool[r_type * 8 + t + magic_offset])) {
        case '0':
          x = 0;
          break;
        case '1':
          if (cur_style < script_style)
            x = thin_mu_skip_code;
          else
            x = 0;
          break;
        case '2':
          x = thin_mu_skip_code;
          break;
        case '3':
          if (cur_style < script_style)
            x = med_mu_skip_code;
          else
            x = 0;
          break;
        case '4':
          if (cur_style < script_style)
            x = thick_mu_skip_code;
          else
            x = 0;
          break;
        default:
          confusion(/*1668:*/
                    543
/*:1668*/
          );
      }
      if (x != 0) {
        y = math_glue(glue_par(x), cur_mu);
        z = new_glue(y);
        glue_ref_count(y) = null;
        link(p) = z;
        p = z;
        subtype(z) = x + 1;
      }
    }

/*:766*/
    ;
/*767:*/

    if (new_hlist(q) != null) {
      link(p) = new_hlist(q);
      do {
        p = link(p);
      } while (!(link(p) == null));
    }
    if (penalties)
      if (link(q) != null)
        if (pen < inf_penalty) {
          r_type = type(link(q));
          if (r_type != penalty_node)
            if (r_type != rel_noad) {
              z = new_penalty(pen);
              link(p) = z;
              p = z;
            }
        }

/*:767*/
        ;
    r_type = t;
  delete_q:
    r = q;
    q = link(q);
    free_node(r, s);
  done:;
  }

/*:760*/
  ;
}

/*:726*/ /*772:*/
void push_alignment(void) {
  pointer p;
  p = get_node(align_stack_node_size);
  link(p) = align_ptr;
  info(p) = cur_align;
  llink(p) = preamble;
  rlink(p) = cur_span;
  mem[p + 2].i = cur_loop;
  mem[p + 3].i = align_state;
  info(p + 4) = cur_head;
  link(p + 4) = cur_tail;
  align_ptr = p;
  cur_head = get_avail();
}

void pop_alignment(void) {
  pointer p;
  free_avail(cur_head);
  p = align_ptr;
  cur_tail = link(p + 4);
  cur_head = info(p + 4);
  align_state = mem[p + 3].i;
  cur_loop = mem[p + 2].i;
  cur_span = rlink(p);
  preamble = llink(p);
  cur_align = info(p);
  align_ptr = link(p);
  free_node(p, align_stack_node_size);
}

/*:772*/ /*774:*/
/*782:*/

void get_preamble_token(void) {
restart:
  get_token();
  while ((cur_chr == span_code) && (cur_cmd == tab_mark)) {
    get_token();
    if (cur_cmd > max_command) {
      expand();
      get_token();
    }
  }
  if (cur_cmd == endv)
    fatal_error("(interwoven alignment preambles are not allowed)");

  if ((cur_cmd == assign_glue) && (cur_chr == glue_base + tab_skip_code)) {
    scan_optional_equals();
    scan_glue(glue_val);
    if (global_defs > 0)
      geq_define(glue_base + tab_skip_code, glue_ref, cur_val);
    else
      eq_define(glue_base + tab_skip_code, glue_ref, cur_val);
    goto restart;
  }
}

/*:782*/

void align_peek(void);
void normal_paragraph(void);
void init_align(void) {
  pointer save_cs_ptr;
  pointer p;
  save_cs_ptr = cur_cs;
  push_alignment();
  align_state = -1000000;
/*776:*/

  if ((mode == mmode) && ((tail != head) || (incompleat_noad != null))) {
    print_err("Improper ");
    print_esc(/*1542:*/
              417
/*:1542*/
    );
    print_str(" inside $$'s");

    help3("Displays can use special alignments (like \\eqalignno)")(
        "only if nothing but the alignment itself is between $$'s.")(
        "So I've deleted the formulas that preceded this alignment.");
    error();
    flush_math();
  }

/*:776*/
  ;
  push_nest();
/*775:*/

  if (mode == mmode) {
    mode = -vmode;
    prev_depth = nest[nest_ptr - 2].aux_field.sc;
  } else if (mode > 0)
    negate(mode)

/*:775*/
        ;
  scan_spec(align_group, false);
/*777:*/

  preamble = null;
  cur_align = align_head;
  cur_loop = null;
  scanner_status = aligning;
  warning_index = save_cs_ptr;
  align_state = -1000000;

  loop { /*778:*/

    link(cur_align) = new_param_glue(tab_skip_code);
    cur_align = link(cur_align)

/*:778*/
        ;
    if (cur_cmd == car_ret) goto done;
/*779:*/

/*783:*/

    p = hold_head;
    link(p) = null;
    loop {
      get_preamble_token();
      if (cur_cmd == mac_param) goto done1;
      if ((cur_cmd <= car_ret) && (cur_cmd >= tab_mark) &&
          (align_state == -1000000))
        if ((p == hold_head) && (cur_loop == null) && (cur_cmd == tab_mark))
          cur_loop = cur_align;
        else {
          print_err("Missing # inserted in alignment preamble");

          help3("There should be exactly one # between &'s, when an")(
              "\\halign or \\valign is being set up. In this case you had")(
              "none, so I've put one in; maybe that will work.");
          back_error();
          goto done1;
        }
      else if ((cur_cmd != spacer) || (p != hold_head)) {
        link(p) = get_avail();
        p = link(p);
        info(p) = cur_tok;
      }
    }
  done1:

/*:783*/
      ;
    link(cur_align) = new_null_box();
    cur_align = link(cur_align);
    info(cur_align) = end_span;
    width(cur_align) = null_flag;
    u_part(cur_align) = link(hold_head);
/*784:*/

    p = hold_head;
    link(p) = null;
    loop {
    resume:
      get_preamble_token();
      if ((cur_cmd <= car_ret) && (cur_cmd >= tab_mark) &&
          (align_state == -1000000))
        goto done2;
      if (cur_cmd == mac_param) {
        print_err("Only one # is allowed per tab");

        help3("There should be exactly one # between &'s, when an")(
            "\\halign or \\valign is being set up. In this case you had")(
            "more than one, so I'm ignoring all but the first.");
        error();
        goto resume;
      }
      link(p) = get_avail();
      p = link(p);
      info(p) = cur_tok;
    }
  done2:
    link(p) = get_avail();
    p = link(p);
    info(p) = end_template_token

/*:784*/
        ;
    v_part(cur_align) = link(hold_head)

/*:779*/
        ;
  }
done:
  scanner_status = normal

/*:777*/
      ;
  new_save_level(align_group);
  if (every_cr != null) begin_token_list(every_cr, every_cr_text);
  align_peek();
}

/*:774*/ /*786:*/
/*787:*/

void init_span(pointer p) {
  push_nest();
  if (mode == -hmode)
    space_factor = 1000;
  else {
    prev_depth = ignore_depth;
    normal_paragraph();
  }
  cur_span = p;
}

/*:787*/

void init_row(void) {
  push_nest();
  mode = (-hmode - vmode) - mode;
  if (mode == -hmode)
    space_factor = 0;
  else
    prev_depth = 0;
  tail_append(new_glue(glue_ptr(preamble)));
  subtype(tail) = tab_skip_code + 1;
  cur_align = link(preamble);
  cur_tail = cur_head;
  init_span(cur_align);
}

/*:786*/ /*788:*/
void init_col(void) {
  extra_info(cur_align) = cur_cmd;
  if (cur_cmd == omit)
    align_state = 0;
  else {
    back_input();
    begin_token_list(u_part(cur_align), u_template);
  }
}

/*:788*/ /*791:*/
bool fin_col(void) {
  pointer p;
  pointer q, r;
  pointer s;
  pointer u;
  scaled w;
  glue_ord o;
  halfword n;
  if (cur_align == null)
    confusion(/*1673:*/
              548
/*:1673*/
    );
  q = link(cur_align);
  if (q == null)
    confusion(/*1673:*/
              548
/*:1673*/
    );

  if (align_state < 500000)
    fatal_error("(interwoven alignment preambles are not allowed)");

  p = link(q);
/*792:*/

  if ((p == null) && (extra_info(cur_align) < cr_code))
    if (cur_loop != null) /*793:*/

    {
      link(q) = new_null_box();
      p = link(q);
      info(p) = end_span;
      width(p) = null_flag;
      cur_loop = link(cur_loop);
/*794:*/

      q = hold_head;
      r = u_part(cur_loop);
      while (r != null) {
        link(q) = get_avail();
        q = link(q);
        info(q) = info(r);
        r = link(r);
      }
      link(q) = null;
      u_part(p) = link(hold_head);
      q = hold_head;
      r = v_part(cur_loop);
      while (r != null) {
        link(q) = get_avail();
        q = link(q);
        info(q) = info(r);
        r = link(r);
      }
      link(q) = null;
      v_part(p) = link(hold_head)

/*:794*/
          ;
      cur_loop = link(cur_loop);
      link(p) = new_glue(glue_ptr(cur_loop));
      subtype(link(p)) = tab_skip_code + 1;
    }
/*:793*/

    else {
      print_err("Extra alignment tab has been changed to ");

      print_esc(/*1670:*/
                545
/*:1670*/
      );
      help3("You have given more \\span or & marks than there were")(
          "in the preamble to the \\halign or \\valign now in progress.")(
          "So I'll assume that you meant to type \\cr instead.");
      extra_info(cur_align) = cr_code;
      error();
    }

/*:792*/
    ;
  if (extra_info(cur_align) != span_code) {
    unsave();
    new_save_level(align_group);
/*796:*/

    {
      if (mode == -hmode) {
        adjust_tail = cur_tail;
        u = hpack(link(head), natural);
        w = width(u);
        cur_tail = adjust_tail;
        adjust_tail = null;
      } else {
        u = vpackage(link(head), natural, 0);
        w = height(u);
      }
      n = min_quarterword;
      if (cur_span != cur_align) /*798:*/

      {
        q = cur_span;
        do {
          incr(n);
          q = link(link(q));
        } while (!(q == cur_align));
        if (n > max_quarterword)
          confusion(/*1674:*/
                    549
/*:1674*/
          );

        q = cur_span;
        while (link(info(q)) < n) q = info(q);
        if (link(info(q)) > n) {
          s = get_node(span_node_size);
          info(s) = info(q);
          link(s) = n;
          info(q) = s;
          width(s) = w;
        } else if (width(info(q)) < w)
          width(info(q)) = w;
      }

/*:798*/

      else if (w > width(cur_align))
        width(cur_align) = w;
      type(u) = unset_node;
      span_count(u) = n;
/*659:*/

      if (total_stretch[filll] != 0)
        o = filll;
      else if (total_stretch[fill] != 0)
        o = fill;
      else if (total_stretch[fil] != 0)
        o = fil;
      else
        o = normal

/*:659*/
            ;
      glue_order(u) = o;
      glue_stretch(u) = total_stretch[o];
/*665:*/

      if (total_shrink[filll] != 0)
        o = filll;
      else if (total_shrink[fill] != 0)
        o = fill;
      else if (total_shrink[fil] != 0)
        o = fil;
      else
        o = normal

/*:665*/
            ;
      glue_sign(u) = o;
      glue_shrink(u) = total_shrink[o];
      pop_nest();
      link(tail) = u;
      tail = u;
    }

/*:796*/
    ;
/*795:*/

    tail_append(new_glue(glue_ptr(link(cur_align))));
    subtype(tail) = tab_skip_code + 1

/*:795*/
        ;
    if (extra_info(cur_align) >= cr_code) {
      return true;
    }
    init_span(p);
  }
  align_state = 1000000; /*406:*/

  do {
    get_x_token();
  } while (!(cur_cmd != spacer))

/*:406*/
      ;
  cur_align = p;
  init_col();
  return false;
}

/*:791*/ /*799:*/
void fin_row(void) {
  pointer p;
  if (mode == -hmode) {
    p = hpack(link(head), natural);
    pop_nest();
    append_to_vlist(p);
    if (cur_head != cur_tail) {
      link(tail) = link(cur_head);
      tail = cur_tail;
    }
  } else {
    p = vpack(link(head), natural);
    pop_nest();
    link(tail) = p;
    tail = p;
    space_factor = 1000;
  }
  type(p) = unset_node;
  glue_stretch(p) = 0;
  if (every_cr != null) begin_token_list(every_cr, every_cr_text);
  align_peek();
}

/*:799*/ /*800:*/
void do_assignments(void);
void resume_after_display(void);
void build_page(void);
void fin_align(void) {
  pointer p, q, r, s, u, v;
  scaled t, w;
  scaled o;
  halfword n;
  scaled rule_save;
  memory_word aux_save;
  if (cur_group != align_group)
    confusion(/*1675:*/
              550
/*:1675*/
    );

  unsave();
  if (cur_group != align_group)
    confusion(/*1676:*/
              551
/*:1676*/
    );
  unsave();
  if (nest[nest_ptr - 1].mode_field == mmode)
    o = display_indent;
  else
    o = 0;
/*801:*/

  q = link(preamble);
  do {
    flush_list(u_part(q));
    flush_list(v_part(q));
    p = link(link(q));
    if (width(q) == null_flag)
/*802:*/

    {
      width(q) = 0;
      r = link(q);
      s = glue_ptr(r);
      if (s != zero_glue) {
        add_glue_ref(zero_glue);
        delete_glue_ref(s);
        glue_ptr(r) = zero_glue;
      }
    }

/*:802*/
    ;
    if (info(q) != end_span)
/*803:*/

    {
      t = width(q) + width(glue_ptr(link(q)));
      r = info(q);
      s = end_span;
      info(s) = p;
      n = min_quarterword + 1;
      do {
        width(r) = width(r) - t;
        u = info(r);
        while (link(r) > n) {
          s = info(s);
          n = link(info(s)) + 1;
        }
        if (link(r) < n) {
          info(r) = info(s);
          info(s) = r;
          decr(link(r));
          s = r;
        } else {
          if (width(r) > width(info(s))) width(info(s)) = width(r);
          free_node(r, span_node_size);
        }
        r = u;
      } while (!(r == end_span));
    }

/*:803*/
    ;
    type(q) = unset_node;
    span_count(q) = min_quarterword;
    height(q) = 0;
    depth(q) = 0;
    glue_order(q) = normal;
    glue_sign(q) = normal;
    glue_stretch(q) = 0;
    glue_shrink(q) = 0;
    q = p;
  } while (!(q == null))

/*:801*/
      ;
/*804:*/

  save_ptr = save_ptr - 2;
  pack_begin_line = -mode_line;
  if (mode == -vmode) {
    rule_save = overfull_rule;
    overfull_rule = 0;
    p = hpack(preamble, saved(1), saved(0));
    overfull_rule = rule_save;
  } else {
    q = link(preamble);
    do {
      height(q) = width(q);
      width(q) = 0;
      q = link(link(q));
    } while (!(q == null));
    p = vpack(preamble, saved(1), saved(0));
    q = link(preamble);
    do {
      width(q) = height(q);
      height(q) = 0;
      q = link(link(q));
    } while (!(q == null));
  }
  pack_begin_line = 0

/*:804*/
      ;
/*805:*/

  q = link(head);
  s = head;
  while (q != null) {
    if (!is_char_node(q))
      if (type(q) == unset_node)
/*807:*/

      {
        if (mode == -vmode) {
          type(q) = hlist_node;
          width(q) = width(p);
        } else {
          type(q) = vlist_node;
          height(q) = height(p);
        }
        glue_order(q) = glue_order(p);
        glue_sign(q) = glue_sign(p);
        glue_set(q) = glue_set(p);
        shift_amount(q) = o;
        r = link(list_ptr(q));
        s = link(list_ptr(p));
        do { /*808:*/

          n = span_count(r);
          t = width(s);
          w = t;
          u = hold_head;
          while (n > min_quarterword) {
            decr(n);
/*809:*/

            s = link(s);
            v = glue_ptr(s);
            link(u) = new_glue(v);
            u = link(u);
            subtype(u) = tab_skip_code + 1;
            t = t + width(v);
            if (glue_sign(p) == stretching) {
              if (stretch_order(v) == glue_order(p))
                t = t + round(float(glue_set(p)) * stretch(v));

            } else if (glue_sign(p) == shrinking) {
              if (shrink_order(v) == glue_order(p))
                t = t - round(float(glue_set(p)) * shrink(v));
            }
            s = link(s);
            link(u) = new_null_box();
            u = link(u);
            t = t + width(s);
            if (mode == -vmode)
              width(u) = width(s);
            else {
              type(u) = vlist_node;
              height(u) = width(s);
            }

/*:809*/
            ;
          }
          if (mode == -vmode)
/*810:*/

          {
            height(r) = height(q);
            depth(r) = depth(q);
            if (t == width(r)) {
              glue_sign(r) = normal;
              glue_order(r) = normal;
              set_glue_ratio_zero(glue_set(r));
            } else if (t > width(r)) {
              glue_sign(r) = stretching;
              if (glue_stretch(r) == 0)
                set_glue_ratio_zero(glue_set(r));
              else
                glue_set(r) = unfloat((t - width(r)) / (double)glue_stretch(r));

            } else {
              glue_order(r) = glue_sign(r);
              glue_sign(r) = shrinking;
              if (glue_shrink(r) == 0)
                set_glue_ratio_zero(glue_set(r));
              else if ((glue_order(r) == normal) &&
                       (width(r) - t > glue_shrink(r)))
                set_glue_ratio_one(glue_set(r));
              else
                glue_set(r) = unfloat((width(r) - t) / (double)glue_shrink(r));
            }
            width(r) = w;
            type(r) = hlist_node;
          }
/*:810*/

          else /*811:*/

          {
            width(r) = width(q);
            if (t == height(r)) {
              glue_sign(r) = normal;
              glue_order(r) = normal;
              set_glue_ratio_zero(glue_set(r));
            } else if (t > height(r)) {
              glue_sign(r) = stretching;
              if (glue_stretch(r) == 0)
                set_glue_ratio_zero(glue_set(r));
              else
                glue_set(r) =
                    unfloat((t - height(r)) / (double)glue_stretch(r));

            } else {
              glue_order(r) = glue_sign(r);
              glue_sign(r) = shrinking;
              if (glue_shrink(r) == 0)
                set_glue_ratio_zero(glue_set(r));
              else if ((glue_order(r) == normal) &&
                       (height(r) - t > glue_shrink(r)))
                set_glue_ratio_one(glue_set(r));
              else
                glue_set(r) = unfloat((height(r) - t) / (double)glue_shrink(r));
            }
            height(r) = w;
            type(r) = vlist_node;
          }

/*:811*/
          ;
          shift_amount(r) = 0;
          if (u != hold_head) {
            link(u) = link(r);
            link(r) = link(hold_head);
            r = u;
          }

/*:808*/
          ;
          r = link(link(r));
          s = link(link(s));
        } while (!(r == null));
      }
/*:807*/

      else if (type(q) == rule_node)
/*806:*/

      {
        if (is_running(width(q))) width(q) = width(p);
        if (is_running(height(q))) height(q) = height(p);
        if (is_running(depth(q))) depth(q) = depth(p);
        if (o != 0) {
          r = link(q);
          link(q) = null;
          q = hpack(q, natural);
          shift_amount(q) = o;
          link(q) = r;
          link(s) = q;
        }
      }

/*:806*/
      ;
    s = q;
    q = link(q);
  }

/*:805*/
  ;
  flush_node_list(p);
  pop_alignment();
/*812:*/

  aux_save = aux;
  p = link(head);
  q = tail;
  pop_nest();
  if (mode == mmode) /*1206:*/

  {
    do_assignments();
    if (cur_cmd != math_shift) /*1207:*/

    {
      print_err("Missing $$ inserted");

      help2("Displays can use special alignments (like \\eqalignno)")(
          "only if nothing but the alignment itself is between $$'s.");
      back_error();
    }
/*:1207*/

    else /*1197:*/

    {
      get_x_token();
      if (cur_cmd != math_shift) {
        print_err("Display math should end with $$");

        help2("The `$' that I just saw supposedly matches a previous `$$'.")(
            "So I shall assume that you typed `$$' both times.");
        back_error();
      }
    }

/*:1197*/
    ;
    pop_nest();
    tail_append(new_penalty(pre_display_penalty));
    tail_append(new_param_glue(above_display_skip_code));
    link(tail) = p;
    if (p != null) tail = q;
    tail_append(new_penalty(post_display_penalty));
    tail_append(new_param_glue(below_display_skip_code));
    prev_depth = aux_save.sc;
    resume_after_display();
  }
/*:1206*/

  else {
    aux = aux_save;
    link(tail) = p;
    if (p != null) tail = q;
    if (mode == vmode) build_page();
  }

/*:812*/
  ;
}
/*785:*/

void align_peek(void) {
restart:
  align_state = 1000000; /*406:*/

  do {
    get_x_token();
  } while (!(cur_cmd != spacer))

/*:406*/
      ;
  if (cur_cmd == no_align) {
    scan_left_brace();
    new_save_level(no_align_group);
    if (mode == -vmode) normal_paragraph();
  } else if (cur_cmd == right_brace)
    fin_align();
  else if ((cur_cmd == car_ret) && (cur_chr == cr_cr_code))
    goto restart;
  else {
    init_row();
    init_col();
  }
}

/*:785*/

/*:800*/ /*815:*/
/*826:*/

pointer finite_shrink(pointer p) {
  pointer q;
  if (no_shrink_error_yet) {
    no_shrink_error_yet = false;

#ifdef STAT
    if (tracing_paragraphs > 0) end_diagnostic(true);
#endif

    print_err("Infinite glue shrinkage found in a paragraph");

    help5("The paragraph just ended includes some glue that has")(
        "infinite shrinkability, e.g., `\\hskip 0pt minus 1fil'.")(
        "Such glue doesn't belong there---it allows a paragraph")(
        "of any length to fit on one line. But it's safe to proceed,")(
        "since the offensive shrinkability has been made finite.");
    error();

#ifdef STAT
    if (tracing_paragraphs > 0) begin_diagnostic();
#endif
  }
  q = new_spec(p);
  shrink_order(q) = normal;
  delete_glue_ref(p);
  return q;
}

/*:826*/ /*829:*/

void try_break(int pi, small_number break_type) {
  pointer r;
  pointer prev_r;
  halfword old_l;
  bool no_break_yet;
/*830:*/

  pointer prev_prev_r;
  pointer s;
  pointer q;
  pointer v;
  int t;
  internal_font_number f;
  halfword l;
  bool node_r_stays_active;
  scaled line_width;
  uint8_t fit_class;
  halfword b;
  int d;
  bool artificial_demerits;
#ifdef STAT
  pointer save_link;
#endif
  scaled shortfall;

/*:830*/

/*831:*/

  if (abs(pi) >= inf_penalty)
    if (pi > 0)
      goto end;
    else
      pi = eject_penalty

/*:831*/
          ;
  no_break_yet = true;
  prev_r = active;
  old_l = 0;
  do_all_six(copy_to_cur_active);
  loop {
  resume:
    r = link(prev_r);
/*832:*/

    if (type(r) == delta_node) {
      do_all_six(update_width);
      prev_prev_r = prev_r;
      prev_r = r;
      goto resume;
    }

/*:832*/
    ;
/*835:*/

    {
      l = line_number(r);
      if (l > old_l) {
        if ((minimum_demerits < awful_bad) &&
            ((old_l != easy_line) || (r == last_active)))
/*836:*/

        {
          if (no_break_yet) /*837:*/

          {
            no_break_yet = false;
            do_all_six(set_break_width_to_background);
            s = cur_p;
            if (break_type > unhyphenated)
              if (cur_p != null)
/*840:*/

              {
                t = replace_count(cur_p);
                v = cur_p;
                s = post_break(cur_p);
                while (t > 0) {
                  decr(t);
                  v = link(v);
/*841:*/

                  if (is_char_node(v)) {
                    f = font(v);
                    break_width[1] = break_width[1] -
                                     char_width(f)(char_info(f)(character(v)));
                  } else
                    switch (type(v)) {
                      case ligature_node: {
                        f = font(lig_char(v));
                        break_width[1] =
                            break_width[1] -
                            char_width(f)(char_info(f)(character(lig_char(v))));
                      } break;
                      case hlist_node:
                      case vlist_node:
                      case rule_node:
                      case kern_node:
                        break_width[1] = break_width[1] - width(v);
                        break;
                      default:
                        confusion(/*1677:*/
                                  552
/*:1677*/
                        );
                    }

/*:841*/
                    ;
                }
                while (s != null) { /*842:*/

                  if (is_char_node(s)) {
                    f = font(s);
                    break_width[1] = break_width[1] +
                                     char_width(f)(char_info(f)(character(s)));
                  } else
                    switch (type(s)) {
                      case ligature_node: {
                        f = font(lig_char(s));
                        break_width[1] =
                            break_width[1] +
                            char_width(f)(char_info(f)(character(lig_char(s))));
                      } break;
                      case hlist_node:
                      case vlist_node:
                      case rule_node:
                      case kern_node:
                        break_width[1] = break_width[1] + width(s);
                        break;
                      default:
                        confusion(/*1678:*/
                                  553
/*:1678*/
                        );
                    }

/*:842*/
                    ;
                  s = link(s);
                }
                break_width[1] = break_width[1] + disc_width;
                if (post_break(cur_p) == null) s = link(v);
              }

/*:840*/
              ;
            while (s != null) {
              if (is_char_node(s)) goto done;
              switch (type(s)) {
                case glue_node: /*838:*/

                {
                  v = glue_ptr(s);
                  break_width[1] = break_width[1] - width(v);
                  break_width[2 + stretch_order(v)] =
                      break_width[2 + stretch_order(v)] - stretch(v);
                  break_width[6] = break_width[6] - shrink(v);
                }

/*:838*/
                break;
                case penalty_node:
                  do_nothing;
                  break;
                case math_node:
                  break_width[1] = break_width[1] - width(s);
                  break;
                case kern_node:
                  if (subtype(s) != explicit)
                    goto done;
                  else
                    break_width[1] = break_width[1] - width(s);
                  break;
                default:
                  goto done;
              }
              s = link(s);
            }
          done:;
          }

/*:837*/
          ;
/*843:*/

          if (type(prev_r) == delta_node) {
            do_all_six(convert_to_break_width);
          } else if (prev_r == active) {
            do_all_six(store_break_width);
          } else {
            q = get_node(delta_node_size);
            link(q) = r;
            type(q) = delta_node;
            subtype(q) = 0;
            do_all_six(new_delta_to_break_width);
            link(prev_r) = q;
            prev_prev_r = prev_r;
            prev_r = q;
          }

/*:843*/
          ;
          if (abs(adj_demerits) >= awful_bad - minimum_demerits)
            minimum_demerits = awful_bad - 1;
          else
            minimum_demerits = minimum_demerits + abs(adj_demerits);
          for (fit_class = very_loose_fit; fit_class <= tight_fit;
               fit_class++) {
            if (minimal_demerits[fit_class] <= minimum_demerits)
/*845:*/

            {
              q = get_node(passive_node_size);
              link(q) = passive;
              passive = q;
              cur_break(q) = cur_p;
#ifdef STAT
              incr(pass_number);
              serial(q) = pass_number;
#endif

              prev_break(q) = best_place[fit_class];
              q = get_node(active_node_size);
              break_node(q) = passive;
              line_number(q) = best_pl_line[fit_class] + 1;
              fitness(q) = fit_class;
              type(q) = break_type;
              total_demerits(q) = minimal_demerits[fit_class];
              link(q) = r;
              link(prev_r) = q;
              prev_r = q;
#ifdef STAT
              if (tracing_paragraphs > 0)
/*846:*/

              {
                print_nl("@@");
                print_int(serial(passive));

                print_str(": line ");
                print_int(line_number(q) - 1);
                print_char('.');
                print_int(fit_class);
                if (break_type == hyphenated) print_char('-');
                print_str(" t=");
                print_int(total_demerits(q));
                print_str(" -> @@");
                if (prev_break(passive) == null)
                  print_char('0');
                else
                  print_int(serial(prev_break(passive)));
              }

/*:846*/
              ;
#endif
            }

/*:845*/
            ;
            minimal_demerits[fit_class] = awful_bad;
          }
          minimum_demerits = awful_bad;
/*844:*/

          if (r != last_active) {
            q = get_node(delta_node_size);
            link(q) = r;
            type(q) = delta_node;
            subtype(q) = 0;
            do_all_six(new_delta_from_break_width);
            link(prev_r) = q;
            prev_prev_r = prev_r;
            prev_r = q;
          }

/*:844*/
          ;
        }

/*:836*/
        ;
        if (r == last_active) goto end;
/*850:*/

        if (l > easy_line) {
          line_width = second_width;
          old_l = max_halfword - 1;
        } else {
          old_l = l;
          if (l > last_special_line)
            line_width = second_width;
          else if (par_shape_ptr == null)
            line_width = first_width;
          else
            line_width = mem[par_shape_ptr + 2 * l].sc;
        }

/*:850*/
        ;
      }
    }

/*:835*/
    ;
/*851:*/

    {
      artificial_demerits = false;

      shortfall = line_width - cur_active_width[1];
      if (shortfall > 0) /*852:*/

        if ((cur_active_width[3] != 0) || (cur_active_width[4] != 0) ||
            (cur_active_width[5] != 0)) {
          b = 0;
          fit_class = decent_fit;
        } else {
          if (shortfall > 7230584)
            if (cur_active_width[2] < 1663497) {
              b = inf_bad;
              fit_class = very_loose_fit;
              goto done1;
            }
          b = badness(shortfall, cur_active_width[2]);
          if (b > 12)
            if (b > 99)
              fit_class = very_loose_fit;
            else
              fit_class = loose_fit;
          else
            fit_class = decent_fit;
        done1:;
        }

/*:852*/

      else /*853:*/

      {
        if (-shortfall > cur_active_width[6])
          b = inf_bad + 1;
        else
          b = badness(-shortfall, cur_active_width[6]);
        if (b > 12)
          fit_class = tight_fit;
        else
          fit_class = decent_fit;
      }

/*:853*/
      ;
      if ((b > inf_bad) || (pi == eject_penalty))
/*854:*/

      {
        if (final_pass && (minimum_demerits == awful_bad) &&
            (link(r) == last_active) && (prev_r == active))
          artificial_demerits = true;
        else if (b > threshold)
          goto deactivate;
        node_r_stays_active = false;
      }
/*:854*/

      else {
        prev_r = r;
        if (b > threshold) goto resume;
        node_r_stays_active = true;
      }
/*855:*/

      if (artificial_demerits)
        d = 0;
      else /*859:*/

      {
        d = line_penalty + b;
        if (abs(d) >= 10000)
          d = 100000000;
        else
          d = d * d;
        if (pi != 0)
          if (pi > 0)
            d = d + pi * pi;
          else if (pi > eject_penalty)
            d = d - pi * pi;
        if ((break_type == hyphenated) && (type(r) == hyphenated))
          if (cur_p != null)
            d = d + double_hyphen_demerits;
          else
            d = d + final_hyphen_demerits;
        if (abs(fit_class - fitness(r)) > 1) d = d + adj_demerits;
      }

/*:859*/
      ;
#ifdef STAT
      if (tracing_paragraphs > 0)
/*856:*/

      {
        if (printed_node != cur_p)
/*857:*/

        {
          print_nl("");
          if (cur_p == null)
            short_display(link(printed_node));
          else {
            save_link = link(cur_p);
            link(cur_p) = null;
            print_nl("");
            short_display(link(printed_node));
            link(cur_p) = save_link;
          }
          printed_node = cur_p;
        }

/*:857*/
        ;
        print_nl("@");

        if (cur_p == null)
          print_esc(/*1569:*/
                    444
/*:1569*/
          );
        else if (type(cur_p) != glue_node) {
          if (type(cur_p) == penalty_node)
            print_esc(/*1553:*/
                      428
/*:1553*/
            );
          else if (type(cur_p) == disc_node)
            print_esc(/*1400:*/
                      275
/*:1400*/
            );
          else if (type(cur_p) == kern_node)
            print_esc(/*1396:*/
                      271
/*:1396*/
            );
          else
            print_esc(/*1398:*/
                      273
/*:1398*/
            );
        }
        print_str(" via @@");
        if (break_node(r) == null)
          print_char('0');
        else
          print_int(serial(break_node(r)));
        print_str(" b=");
        if (b > inf_bad)
          print_char('*');
        else
          print_int(b);

        print_str(" p=");
        print_int(pi);
        print_str(" d=");
        if (artificial_demerits)
          print_char('*');
        else
          print_int(d);
      }

/*:856*/
      ;
#endif

      d = d + total_demerits(r);

      if (d <= minimal_demerits[fit_class]) {
        minimal_demerits[fit_class] = d;
        best_place[fit_class] = break_node(r);
        best_pl_line[fit_class] = l;
        if (d < minimum_demerits) minimum_demerits = d;
      }

/*:855*/
      ;
      if (node_r_stays_active) goto resume;
    deactivate: /*860:*/

      link(prev_r) = link(r);
      free_node(r, active_node_size);
      if (prev_r == active) /*861:*/

      {
        r = link(active);
        if (type(r) == delta_node) {
          do_all_six(update_active);
          do_all_six(copy_to_cur_active);
          link(active) = link(r);
          free_node(r, delta_node_size);
        }
      }
/*:861*/

      else if (type(prev_r) == delta_node) {
        r = link(prev_r);
        if (r == last_active) {
          do_all_six(downdate_width);
          link(prev_prev_r) = last_active;
          free_node(prev_r, delta_node_size);
          prev_r = prev_prev_r;
        } else if (type(r) == delta_node) {
          do_all_six(update_width);
          do_all_six(combine_two_deltas);
          link(prev_r) = link(r);
          free_node(r, delta_node_size);
        }
      }

/*:860*/
      ;
    }

/*:851*/
    ;
  }
end:;
#ifdef STAT
/*858:*/

  if (cur_p == printed_node)
    if (cur_p != null)
      if (type(cur_p) == disc_node) {
        t = replace_count(cur_p);
        while (t > 0) {
          decr(t);
          printed_node = link(printed_node);
        }
      }

/*:858*/
      ;
#endif
}

/*:829*/ /*877:*/

void post_line_break(int final_widow_penalty) {
  pointer q, r, s;
  bool disc_break;
  bool post_disc_break;
  scaled cur_width;
  scaled cur_indent;
  quarterword t;
  int pen;
  halfword cur_line;
/*878:*/

  q = break_node(best_bet);
  cur_p = null;
  do {
    r = q;
    q = prev_break(q);
    next_break(r) = cur_p;
    cur_p = r;
  } while (!(q == null))

/*:878*/
      ;
  cur_line = prev_graf + 1;
  do { /*880:*/

/*881:*/

    q = cur_break(cur_p);
    disc_break = false;
    post_disc_break = false;
    if (q != null)
      if (type(q) == glue_node) {
        delete_glue_ref(glue_ptr(q));
        glue_ptr(q) = right_skip;
        subtype(q) = right_skip_code + 1;
        add_glue_ref(right_skip);
        goto done;
      } else {
        if (type(q) == disc_node)
/*882:*/

        {
          t = replace_count(q);
/*883:*/

          if (t == 0)
            r = link(q);
          else {
            r = q;
            while (t > 1) {
              r = link(r);
              decr(t);
            }
            s = link(r);
            r = link(s);
            link(s) = null;
            flush_node_list(link(q));
            replace_count(q) = 0;
          }

/*:883*/
          ;
          if (post_break(q) != null) /*884:*/

          {
            s = post_break(q);
            while (link(s) != null) s = link(s);
            link(s) = r;
            r = post_break(q);
            post_break(q) = null;
            post_disc_break = true;
          }

/*:884*/
          ;
          if (pre_break(q) != null) /*885:*/

          {
            s = pre_break(q);
            link(q) = s;
            while (link(s) != null) s = link(s);
            pre_break(q) = null;
            q = s;
          }

/*:885*/
          ;
          link(q) = r;
          disc_break = true;
        }

/*:882*/

        else if ((type(q) == math_node) || (type(q) == kern_node))
          width(q) = 0;
      }
    else {
      q = temp_head;
      while (link(q) != null) q = link(q);
    }
/*886:*/

    r = new_param_glue(right_skip_code);
    link(r) = link(q);
    link(q) = r;
    q = r

/*:886*/
        ;
  done:

/*:881*/
      ;
/*887:*/

    r = link(q);
    link(q) = null;
    q = link(temp_head);
    link(temp_head) = r;
    if (left_skip != zero_glue) {
      r = new_param_glue(left_skip_code);
      link(r) = q;
      q = r;
    }

/*:887*/
    ;
/*889:*/

    if (cur_line > last_special_line) {
      cur_width = second_width;
      cur_indent = second_indent;
    } else if (par_shape_ptr == null) {
      cur_width = first_width;
      cur_indent = first_indent;
    } else {
      cur_width = mem[par_shape_ptr + 2 * cur_line].sc;
      cur_indent = mem[par_shape_ptr + 2 * cur_line - 1].sc;
    }
    adjust_tail = adjust_head;
    just_box = hpack(q, cur_width, exactly);
    shift_amount(just_box) = cur_indent

/*:889*/
        ;
/*888:*/

    append_to_vlist(just_box);
    if (adjust_head != adjust_tail) {
      link(tail) = link(adjust_head);
      tail = adjust_tail;
    }
    adjust_tail = null

/*:888*/
        ;
/*890:*/

    if (cur_line + 1 != best_line) {
      pen = inter_line_penalty;
      if (cur_line == prev_graf + 1) pen = pen + club_penalty;
      if (cur_line + 2 == best_line) pen = pen + final_widow_penalty;
      if (disc_break) pen = pen + broken_penalty;
      if (pen != 0) {
        r = new_penalty(pen);
        link(tail) = r;
        tail = r;
      }
    }

/*:890*/

/*:880*/
    ;
    incr(cur_line);
    cur_p = next_break(cur_p);
    if (cur_p != null)
      if (!post_disc_break)
/*879:*/

      {
        r = temp_head;
        loop {
          q = link(r);
          if (q == cur_break(cur_p)) goto done1;

          if (is_char_node(q)) goto done1;
          if (non_discardable(q)) goto done1;
          if (type(q) == kern_node)
            if (subtype(q) != explicit) goto done1;
          r = q;
        }
      done1:
        if (r != temp_head) {
          link(r) = null;
          flush_node_list(link(temp_head));
          link(temp_head) = q;
        }
      }

/*:879*/
      ;
  } while (!(cur_p == null));
  if ((cur_line != best_line) || (link(temp_head) != null))
    confusion(/*1682:*/
              557
/*:1682*/
    );

  prev_graf = best_line - 1;
}

/*:877*/ /*895:*/

/*906:*/

small_number reconstitute(small_number j, small_number n, halfword bchar,
                          halfword hchar) {
  pointer p;
  pointer t;
  four_quarters q;
  halfword cur_rh;
  halfword test_char;
  scaled w;
  font_index k;
  hyphen_passed = 0;
  t = hold_head;
  w = 0;
  link(hold_head) = null;

/*908:*/

  cur_l = qi(hu[j]);
  cur_q = t;
  if (j == 0) {
    ligature_present = init_lig;
    p = init_list;
    if (ligature_present) lft_hit = init_lft;
    while (p > null) {
      append_charnode_to_t(character(p));
      p = link(p);
    }
  } else if (cur_l < non_char)
    append_charnode_to_t(cur_l);
  lig_stack = null;
  set_cur_r

/*:908*/
      ;
resume: /*909:*/

  if (cur_l == non_char) {
    k = bchar_label[hf];
    if (k == non_address)
      goto done;
    else
      q = font_info[k].qqqq;
  } else {
    q = char_info(hf)(cur_l);
    if (char_tag(q) != lig_tag) goto done;
    k = lig_kern_start(hf)(q);
    q = font_info[k].qqqq;
    if (skip_byte(q) > stop_flag) {
      k = lig_kern_restart(hf)(q);
      q = font_info[k].qqqq;
    }
  }
  if (cur_rh < non_char)
    test_char = cur_rh;
  else
    test_char = cur_r;
  loop {
    if (next_char(q) == test_char)
      if (skip_byte(q) <= stop_flag)
        if (cur_rh < non_char) {
          hyphen_passed = j;
          hchar = non_char;
          cur_rh = non_char;
          goto resume;
        } else {
          if (hchar < non_char)
            if (odd(hyf[j])) {
              hyphen_passed = j;
              hchar = non_char;
            }
          if (op_byte(q) < kern_flag)
/*911:*/

          {
            if (cur_l == non_char) lft_hit = true;
            if (j == n)
              if (lig_stack == null) rt_hit = true;
            check_interrupt;
            switch (op_byte(q)) {
              qi(case 1) : qi(case 5) : {
                cur_l = rem_byte(q);
                ligature_present = true;
              }
              break;
              qi(case 2) : qi(case 6) : {
                cur_r = rem_byte(q);
                if (lig_stack > null)
                  character(lig_stack) = cur_r;
                else {
                  lig_stack = new_lig_item(cur_r);
                  if (j == n)
                    bchar = non_char;
                  else {
                    p = get_avail();
                    lig_ptr(lig_stack) = p;
                    character(p) = qi(hu[j + 1]);
                    font(p) = hf;
                  }
                }
              }
              break;
              qi(case 3) : {
                cur_r = rem_byte(q);
                p = lig_stack;
                lig_stack = new_lig_item(cur_r);
                link(lig_stack) = p;
              }
              break;
              qi(case 7) : qi(case 11) : {
                wrap_lig(false);
                cur_q = t;
                cur_l = rem_byte(q);
                ligature_present = true;
              }
              break;
              default: {
                cur_l = rem_byte(q);
                ligature_present = true;
                if (lig_stack > null)
                  pop_lig_stack else if (j == n) goto done;
                else {
                  append_charnode_to_t(cur_r);
                  incr(j);
                  set_cur_r;
                }
              }
            }
            if (op_byte(q) > qi(4))
              if (op_byte(q) != qi(7)) goto done;
            goto resume;
          }

/*:911*/
          ;
          w = char_kern(hf)(q);
          goto done;
        }
    if (skip_byte(q) >= stop_flag)
      if (cur_rh == non_char)
        goto done;
      else {
        cur_rh = non_char;
        goto resume;
      }
    k = k + qo(skip_byte(q)) + 1;
    q = font_info[k].qqqq;
  }
done:

/*:909*/
    ;
/*910:*/

  wrap_lig(rt_hit);
  if (w != 0) {
    link(t) = new_kern(w);
    t = link(t);
    w = 0;
  }
  if (lig_stack > null) {
    cur_q = t;
    cur_l = character(lig_stack);
    ligature_present = true;
    pop_lig_stack;
    goto resume;
  }

/*:910*/
  ;
  return j;
}

/*:906*/

void hyphenate(void) {
/*901:*/

  int i, j, l;
  pointer q, r, s;
  halfword bchar;

/*:901*/ /*912:*/

  pointer major_tail, minor_tail;

  ASCII_code c;
  uint8_t c_loc;
  int r_count;
  pointer hyf_node;

/*:912*/ /*922:*/

  trie_pointer z;
  int v;

/*:922*/ /*929:*/

  hyph_pointer h;
  str_number k;
  pool_pointer u;

/*:929*/

/*923:*/

  for (j = 0; j <= hn; j++) hyf[j] = 0;
/*930:*/

  h = hc[1];
  incr(hn);
  hc[hn] = cur_lang;
  for (j = 2; j <= hn; j++) h = (h + h + hc[j]) % hyph_size;
  loop { /*931:*/

    k = hyph_word[h];
    if (k == 0) goto not_found;
    if (length(k) < hn) goto not_found;
    if (length(k) == hn) {
      j = 1;
      u = str_start[k];
      do {
        if (so(str_pool[u]) < hc[j]) goto not_found;
        if (so(str_pool[u]) > hc[j]) goto done;
        incr(j);
        incr(u);
      } while (!(j > hn));
/*932:*/

      s = hyph_list[h];
      while (s != null) {
        hyf[info(s)] = 1;
        s = link(s);
      }

/*:932*/
      ;
      decr(hn);
      goto found;
    }
  done:

/*:931*/
      ;
    if (h > 0)
      decr(h);
    else
      h = hyph_size;
  }
not_found:
  decr(hn)

/*:930*/
      ;
  if (trie_char(cur_lang + 1) != qi(cur_lang)) return;
  hc[0] = 0;
  hc[hn + 1] = 0;
  hc[hn + 2] = 256;
  for (j = 0; j <= hn - r_hyf + 1; j++) {
    z = trie_link(cur_lang + 1) + hc[j];
    l = j;
    while (hc[l] == qo(trie_char(z))) {
      if (trie_op(z) != min_quarterword)
/*924:*/

      {
        v = trie_op(z);
        do {
          v = v + op_start[cur_lang];
          i = l - hyf_distance[v];
          if (hyf_num[v] > hyf[i]) hyf[i] = hyf_num[v];
          v = hyf_next[v];
        } while (!(v == min_quarterword));
      }

/*:924*/
      ;
      incr(l);
      z = trie_link(z) + hc[l];
    }
  }
found:
  for (j = 0; j <= l_hyf - 1; j++) hyf[j] = 0;
  for (j = 0; j <= r_hyf - 1; j++)
    hyf[hn - j] = 0

/*:923*/
        ;
/*902:*/

  for (j = l_hyf; j <= hn - r_hyf; j++)
    if (odd(hyf[j])) goto found1;
  return;
found1:

/*:902*/
    ;
/*903:*/

  q = link(hb);
  link(hb) = null;
  r = link(ha);
  link(ha) = null;
  bchar = hyf_bchar;
  if (is_char_node(ha))
    if (font(ha) != hf)
      goto found2;
    else {
      init_list = ha;
      init_lig = false;
      hu[0] = qo(character(ha));
    }
  else if (type(ha) == ligature_node)
    if (font(lig_char(ha)) != hf)
      goto found2;
    else {
      init_list = lig_ptr(ha);
      init_lig = true;
      init_lft = (subtype(ha) > 1);
      hu[0] = qo(character(lig_char(ha)));
      if (init_list == null)
        if (init_lft) {
          hu[0] = 256;
          init_lig = false;
        }
      free_node(ha, small_node_size);
    }
  else {
    if (!is_char_node(r))
      if (type(r) == ligature_node)
        if (subtype(r) > 1) goto found2;
    j = 1;
    s = ha;
    init_list = null;
    goto common_ending;
  }
  s = cur_p;
  while (link(s) != ha) s = link(s);
  j = 0;
  goto common_ending;
found2:
  s = ha;
  j = 0;
  hu[0] = 256;
  init_lig = false;
  init_list = null;
common_ending:
  flush_node_list(r);
/*913:*/

  do {
    l = j;
    j = reconstitute(j, hn, bchar, qi(hyf_char)) + 1;
    if (hyphen_passed == 0) {
      link(s) = link(hold_head);
      while (link(s) > null) s = link(s);
      if (odd(hyf[j - 1])) {
        l = j;
        hyphen_passed = j - 1;
        link(hold_head) = null;
      }
    }
    if (hyphen_passed > 0) /*914:*/

      do {
        r = get_node(small_node_size);
        link(r) = link(hold_head);
        type(r) = disc_node;
        major_tail = r;
        r_count = 0;
        while (link(major_tail) > null) advance_major_tail;
        i = hyphen_passed;
        hyf[i] = 0;
/*915:*/

        minor_tail = null;
        pre_break(r) = null;
        hyf_node = new_character(hf, hyf_char);
        if (hyf_node != null) {
          incr(i);
          c = hu[i];
          hu[i] = hyf_char;
          free_avail(hyf_node);
        }
        while (l <= i) {
          l = reconstitute(l, i, font_bchar[hf], non_char) + 1;
          if (link(hold_head) > null) {
            if (minor_tail == null)
              pre_break(r) = link(hold_head);
            else
              link(minor_tail) = link(hold_head);
            minor_tail = link(hold_head);
            while (link(minor_tail) > null) minor_tail = link(minor_tail);
          }
        }
        if (hyf_node != null) {
          hu[i] = c;
          l = i;
          decr(i);
        }

/*:915*/
        ;
/*916:*/

        minor_tail = null;
        post_break(r) = null;
        c_loc = 0;
        if (bchar_label[hf] != non_address) {
          decr(l);
          c = hu[l];
          c_loc = l;
          hu[l] = 256;
        }
        while (l < j) {
          do {
            l = reconstitute(l, hn, bchar, non_char) + 1;
            if (c_loc > 0) {
              hu[c_loc] = c;
              c_loc = 0;
            }
            if (link(hold_head) > null) {
              if (minor_tail == null)
                post_break(r) = link(hold_head);
              else
                link(minor_tail) = link(hold_head);
              minor_tail = link(hold_head);
              while (link(minor_tail) > null) minor_tail = link(minor_tail);
            }
          } while (!(l >= j));
          while (l > j)
/*917:*/

          {
            j = reconstitute(j, hn, bchar, non_char) + 1;
            link(major_tail) = link(hold_head);
            while (link(major_tail) > null) advance_major_tail;
          }

/*:917*/
          ;
        }

/*:916*/
        ;
/*918:*/

        if (r_count > 127) {
          link(s) = link(r);
          link(r) = null;
          flush_node_list(r);
        } else {
          link(s) = r;
          replace_count(r) = r_count;
        }
        s = major_tail

/*:918*/
            ;
        hyphen_passed = j - 1;
        link(hold_head) = null;
      } while (!(!odd(hyf[j - 1])))

/*:914*/
          ;
  } while (!(j > hn));
  link(s) = q

/*:913*/
      ;
  flush_list(init_list)

/*:903*/
      ;
}

/*:895*/ /*942:*/

#ifdef INIT
/*944:*/

quarterword new_trie_op(small_number d, small_number n, quarterword v) {
  int16_t h;
  quarterword u;
  uint16_t l;
  h = abs(n + 313 * d + 361 * v + 1009 * cur_lang) %
          (trie_op_size + trie_op_size) -
      trie_op_size;
  loop {
    l = trie_op_hash[h];
    if (l == 0) {
      if (trie_op_ptr == trie_op_size)
        overflow("pattern memory ops", trie_op_size);
      u = trie_used[cur_lang];
      if (u == max_quarterword)
        overflow("pattern memory ops per language",
                 max_quarterword - min_quarterword);
      incr(trie_op_ptr);
      incr(u);
      trie_used[cur_lang] = u;
      hyf_distance[trie_op_ptr] = d;
      hyf_num[trie_op_ptr] = n;
      hyf_next[trie_op_ptr] = v;
      trie_op_lang[trie_op_ptr] = cur_lang;
      trie_op_hash[h] = trie_op_ptr;
      trie_op_val[trie_op_ptr] = u;
      return u;
    }
    if ((hyf_distance[l] == d) && (hyf_num[l] == n) && (hyf_next[l] == v) &&
        (trie_op_lang[l] == cur_lang)) {
      return trie_op_val[l];
    }
    if (h > -trie_op_size)
      decr(h);
    else
      h = trie_op_size;
  }
}

/*:944*/ /*948:*/

trie_pointer trie_node(trie_pointer p)

{
  trie_pointer h;
  trie_pointer q;
  h = abs(trie_c[p] + 1009 * trie_o[p] + 2718 * trie_l[p] + 3142 * trie_r[p]) %
      trie_size;
  loop {
    q = trie_hash[h];
    if (q == 0) {
      trie_hash[h] = p;
      return p;
    }
    if ((trie_c[q] == trie_c[p]) && (trie_o[q] == trie_o[p]) &&
        (trie_l[q] == trie_l[p]) && (trie_r[q] == trie_r[p])) {
      return q;
    }
    if (h > 0)
      decr(h);
    else
      h = trie_size;
  }
}

/*:948*/ /*949:*/

trie_pointer compress_trie(trie_pointer p) {
  if (p == 0)
    return 0;
  else {
    trie_l[p] = compress_trie(trie_l[p]);
    trie_r[p] = compress_trie(trie_r[p]);
    return trie_node(p);
  }
}

/*:949*/ /*953:*/

void first_fit(trie_pointer p) {
  trie_pointer h;
  trie_pointer z;
  trie_pointer q;
  ASCII_code c;
  trie_pointer l, r;
  uint16_t ll;
  c = so(trie_c[p]);
  z = trie_min[c];
  loop {
    h = z - c;
/*954:*/

    if (trie_max < h + 256) {
      if (trie_size <= h + 256) overflow("pattern memory", trie_size);

      do {
        incr(trie_max);
        trie_taken[trie_max] = false;
        trie_link(trie_max) = trie_max + 1;
        trie_back(trie_max) = trie_max - 1;
      } while (!(trie_max == h + 256));
    }

/*:954*/
    ;
    if (trie_taken[h]) goto not_found;
/*955:*/

    q = trie_r[p];
    while (q > 0) {
      if (trie_link(h + so(trie_c[q])) == 0) goto not_found;
      q = trie_r[q];
    }
    goto found

/*:955*/
        ;
  not_found:
    z = trie_link(z);
  }
found: /*956:*/

  trie_taken[h] = true;
  trie_ref[p] = h;
  q = p;
  do {
    z = h + so(trie_c[q]);
    l = trie_back(z);
    r = trie_link(z);
    trie_back(r) = l;
    trie_link(l) = r;
    trie_link(z) = 0;
    if (l < 256) {
      if (z < 256)
        ll = z;
      else
        ll = 256;
      do {
        trie_min[l] = r;
        incr(l);
      } while (!(l == ll));
    }
    q = trie_r[q];
  } while (!(q == 0))

/*:956*/
      ;
}

/*:953*/ /*957:*/

void trie_pack(trie_pointer p) {
  trie_pointer q;
  do {
    q = trie_l[p];
    if ((q > 0) && (trie_ref[q] == 0)) {
      first_fit(q);
      trie_pack(q);
    }
    p = trie_r[p];
  } while (!(p == 0));
}

/*:957*/ /*959:*/

void trie_fix(trie_pointer p) {
  trie_pointer q;
  ASCII_code c;
  trie_pointer z;
  z = trie_ref[p];
  do {
    q = trie_l[p];
    c = so(trie_c[p]);
    trie_link(z + c) = trie_ref[q];
    trie_char(z + c) = qi(c);
    trie_op(z + c) = trie_o[p];
    if (q > 0) trie_fix(q);
    p = trie_r[p];
  } while (!(p == 0));
}

/*:959*/ /*960:*/

void new_patterns(void) {
  uint8_t k, l;

  bool digit_sensed;
  quarterword v;
  trie_pointer p, q;
  bool first_child;
  ASCII_code c;
  if (trie_not_ready) {
    set_cur_lang;
    scan_left_brace();
/*961:*/

    k = 0;
    hyf[0] = 0;
    digit_sensed = false;
    loop {
      get_x_token();
      switch (cur_cmd) {
        case letter:
        case other_char: /*962:*/

          if (digit_sensed || (cur_chr < '0') || (cur_chr > '9')) {
            if (cur_chr == '.')
              cur_chr = 0;
            else {
              cur_chr = lc_code(cur_chr);
              if (cur_chr == 0) {
                print_err("Nonletter");

                help1("(See Appendix H.)");
                error();
              }
            }
            if (k < 63) {
              incr(k);
              hc[k] = cur_chr;
              hyf[k] = 0;
              digit_sensed = false;
            }
          } else if (k < 63) {
            hyf[k] = cur_chr - '0';
            digit_sensed = true;
          }

/*:962*/
          break;
        case spacer:
        case right_brace: {
          if (k > 0)
/*963:*/

          { /*965:*/

            if (hc[1] == 0) hyf[0] = 0;
            if (hc[k] == 0) hyf[k] = 0;
            l = k;
            v = min_quarterword;
            loop {
              if (hyf[l] != 0) v = new_trie_op(k - l, hyf[l], v);
              if (l > 0)
                decr(l);
              else
                goto done1;
            }
          done1:

/*:965*/
              ;
            q = 0;
            hc[0] = cur_lang;
            while (l <= k) {
              c = hc[l];
              incr(l);
              p = trie_l[q];
              first_child = true;
              while ((p > 0) && (c > so(trie_c[p]))) {
                q = p;
                p = trie_r[q];
                first_child = false;
              }
              if ((p == 0) || (c < so(trie_c[p])))
/*964:*/

              {
                if (trie_ptr == trie_size)
                  overflow("pattern memory", trie_size);

                incr(trie_ptr);
                trie_r[trie_ptr] = p;
                p = trie_ptr;
                trie_l[p] = 0;
                if (first_child)
                  trie_l[q] = p;
                else
                  trie_r[q] = p;
                trie_c[p] = si(c);
                trie_o[p] = min_quarterword;
              }

/*:964*/
              ;
              q = p;
            }
            if (trie_o[q] != min_quarterword) {
              print_err("Duplicate pattern");

              help1("(See Appendix H.)");
              error();
            }
            trie_o[q] = v;
          }

/*:963*/
          ;
          if (cur_cmd == right_brace) goto done;
          k = 0;
          hyf[0] = 0;
          digit_sensed = false;
        } break;
        default: {
          print_err("Bad ");
          print_esc(/*1684:*/
                    559
/*:1684*/
          );

          help1("(See Appendix H.)");
          error();
        }
      }
    }
  done:

/*:961*/
      ;
  } else {
    print_err("Too late for ");
    print_esc(/*1684:*/
              559
/*:1684*/
    );
    help1("All patterns must be given before typesetting begins.");
    error();
    link(garbage) = scan_toks(false, false);
    flush_list(def_ref);
  }
}

/*:960*/ /*966:*/

void init_trie(void) {
  trie_pointer p;
  int j, k, t;
  trie_pointer r, s;
  two_halves h;
/*952:*/

/*945:*/

  op_start[0] = -min_quarterword;
  for (j = 1; j <= 255; j++)
    op_start[j] = op_start[j - 1] + qo(trie_used[j - 1]);
  for (j = 1; j <= trie_op_ptr; j++)
    trie_op_hash[j] = op_start[trie_op_lang[j]] + trie_op_val[j];
  for (j = 1; j <= trie_op_ptr; j++)
    while (trie_op_hash[j] > j) {
      k = trie_op_hash[j];
      t = hyf_distance[k];
      hyf_distance[k] = hyf_distance[j];
      hyf_distance[j] = t;
      t = hyf_num[k];
      hyf_num[k] = hyf_num[j];
      hyf_num[j] = t;
      t = hyf_next[k];
      hyf_next[k] = hyf_next[j];
      hyf_next[j] = t;
      trie_op_hash[j] = trie_op_hash[k];
      trie_op_hash[k] = k;
    }

/*:945*/
    ;
  for (p = 0; p <= trie_size; p++) trie_hash[p] = 0;
  trie_root = compress_trie(trie_root);
  for (p = 0; p <= trie_ptr; p++) trie_ref[p] = 0;
  for (p = 0; p <= 255; p++) trie_min[p] = p + 1;
  trie_link(0) = 1;
  trie_max = 0

/*:952*/
      ;
  if (trie_root != 0) {
    first_fit(trie_root);
    trie_pack(trie_root);
  }
/*958:*/

  h.rh = 0;
  h.b0 = min_quarterword;
  h.b1 = min_quarterword;

  if (trie_root == 0) {
    for (r = 0; r <= 256; r++) trie[r] = h;
    trie_max = 256;
  } else {
    trie_fix(trie_root);
    r = 0;
    do {
      s = trie_link(r);
      trie[r] = h;
      r = s;
    } while (!(r > trie_max));
  }
  trie_char(0) = qi('?');

/*:958*/
  ;
  trie_not_ready = false;
}

/*:966*/

#endif

/*:942*/

void line_break(int final_widow_penalty) {
/*862:*/

  bool auto_breaking;
  pointer prev_p;
  pointer q, r, s, prev_s;
  internal_font_number f;

/*:862*/ /*893:*/

  small_number j;
  uint8_t c;

/*:893*/

  pack_begin_line = mode_line;
/*816:*/

  link(temp_head) = link(head);
  if (is_char_node(tail))
    tail_append(new_penalty(inf_penalty)) else if (type(tail) != glue_node)
        tail_append(new_penalty(inf_penalty)) else {
      type(tail) = penalty_node;
      delete_glue_ref(glue_ptr(tail));
      flush_node_list(leader_ptr(tail));
      penalty(tail) = inf_penalty;
    }
  link(tail) = new_param_glue(par_fill_skip_code);
  init_cur_lang = prev_graf % 0200000;
  init_l_hyf = prev_graf / 020000000;
  init_r_hyf = (prev_graf / 0200000) % 0100;
  pop_nest();

/*:816*/ /*827:*/

  no_shrink_error_yet = true;
  check_shrinkage(left_skip);
  check_shrinkage(right_skip);
  q = left_skip;
  r = right_skip;
  background[1] = width(q) + width(r);
  background[2] = 0;
  background[3] = 0;
  background[4] = 0;
  background[5] = 0;
  background[2 + stretch_order(q)] = stretch(q);
  background[2 + stretch_order(r)] =
      background[2 + stretch_order(r)] + stretch(r);
  background[6] = shrink(q) + shrink(r);

/*:827*/ /*834:*/

  minimum_demerits = awful_bad;
  minimal_demerits[tight_fit] = awful_bad;
  minimal_demerits[decent_fit] = awful_bad;
  minimal_demerits[loose_fit] = awful_bad;
  minimal_demerits[very_loose_fit] = awful_bad;

/*:834*/ /*848:*/

  if (par_shape_ptr == null)
    if (hang_indent == 0) {
      last_special_line = 0;
      second_width = hsize;
      second_indent = 0;
    } else /*849:*/

    {
      last_special_line = abs(hang_after);
      if (hang_after < 0) {
        first_width = hsize - abs(hang_indent);
        if (hang_indent >= 0)
          first_indent = hang_indent;
        else
          first_indent = 0;
        second_width = hsize;
        second_indent = 0;
      } else {
        first_width = hsize;
        first_indent = 0;
        second_width = hsize - abs(hang_indent);
        if (hang_indent >= 0)
          second_indent = hang_indent;
        else
          second_indent = 0;
      }
    }

/*:849*/

  else {
    last_special_line = info(par_shape_ptr) - 1;
    second_width = mem[par_shape_ptr + 2 * (last_special_line + 1)].sc;
    second_indent = mem[par_shape_ptr + 2 * last_special_line + 1].sc;
  }
  if (looseness == 0)
    easy_line = last_special_line;
  else
    easy_line = max_halfword

/*:848*/
        ;
/*863:*/

  threshold = pretolerance;
  if (threshold >= 0) {
#ifdef STAT
    if (tracing_paragraphs > 0) {
      begin_diagnostic();
      print_nl("@firstpass");
    }
#endif

    second_pass = false;
    final_pass = false;
  } else {
    threshold = tolerance;
    second_pass = true;
    final_pass = (emergency_stretch <= 0);

#ifdef STAT
    if (tracing_paragraphs > 0) begin_diagnostic();
#endif
  }
  loop {
    if (threshold > inf_bad) threshold = inf_bad;
    if (second_pass) /*891:*/

    {
#ifdef INIT
      if (trie_not_ready) init_trie();
#endif

      cur_lang = init_cur_lang;
      l_hyf = init_l_hyf;
      r_hyf = init_r_hyf;
    }

/*:891*/
    ;
/*864:*/

    q = get_node(active_node_size);
    type(q) = unhyphenated;
    fitness(q) = decent_fit;
    link(q) = last_active;
    break_node(q) = null;
    line_number(q) = prev_graf + 1;
    total_demerits(q) = 0;
    link(active) = q;
    do_all_six(store_background);
    passive = null;
    printed_node = temp_head;
    pass_number = 0;
    font_in_short_display = null_font

/*:864*/
        ;
    cur_p = link(temp_head);
    auto_breaking = true;
    prev_p = cur_p;
    while ((cur_p != null) && (link(active) != last_active))
/*866:*/

    {
      if (is_char_node(cur_p))
/*867:*/

      {
        prev_p = cur_p;
        do {
          f = font(cur_p);
          act_width = act_width + char_width(f)(char_info(f)(character(cur_p)));
          cur_p = link(cur_p);
        } while (!(!is_char_node(cur_p)));
      }

/*:867*/
      ;
      switch (type(cur_p)) {
        case hlist_node:
        case vlist_node:
        case rule_node:
          act_width = act_width + width(cur_p);
          break;
        case whatsit_node: /*1362:*/

          adv_past(cur_p)

/*:1362*/
              break;
        case glue_node: { /*868:*/

          if (auto_breaking) {
            if (is_char_node(prev_p))
              try_break(0, unhyphenated);
            else if (precedes_break(prev_p))
              try_break(0, unhyphenated);
            else if ((type(prev_p) == kern_node) &&
                     (subtype(prev_p) != explicit))
              try_break(0, unhyphenated);
          }
          check_shrinkage(glue_ptr(cur_p));
          q = glue_ptr(cur_p);
          act_width = act_width + width(q);
          active_width[2 + stretch_order(q)] =
              active_width[2 + stretch_order(q)] + stretch(q);
          active_width[6] = active_width[6] + shrink(q)

/*:868*/
              ;
          if (second_pass && auto_breaking)
/*894:*/

          {
            prev_s = cur_p;
            s = link(prev_s);
            if (s != null) { /*896:*/

              loop {
                if (is_char_node(s)) {
                  c = qo(character(s));
                  hf = font(s);
                } else if (type(s) == ligature_node)
                  if (lig_ptr(s) == null)
                    goto resume;
                  else {
                    q = lig_ptr(s);
                    c = qo(character(q));
                    hf = font(q);
                  }
                else if ((type(s) == kern_node) && (subtype(s) == normal))
                  goto resume;
                else if (type(s) == whatsit_node) { /*1363:*/

                  adv_past(s)

/*:1363*/
                      ;
                  goto resume;
                } else
                  goto done1;
                if (lc_code(c) != 0)
                  if ((lc_code(c) == c) || (uc_hyph > 0))
                    goto done2;
                  else
                    goto done1;
              resume:
                prev_s = s;
                s = link(prev_s);
              }
            done2:
              hyf_char = hyphen_char[hf];
              if (hyf_char < 0) goto done1;
              if (hyf_char > 255) goto done1;
              ha = prev_s

/*:896*/
                  ;
              if (l_hyf + r_hyf > 63) goto done1;
/*897:*/

              hn = 0;
              loop {
                if (is_char_node(s)) {
                  if (font(s) != hf) goto done3;
                  hyf_bchar = character(s);
                  c = qo(hyf_bchar);
                  if (lc_code(c) == 0) goto done3;
                  if (hn == 63) goto done3;
                  hb = s;
                  incr(hn);
                  hu[hn] = c;
                  hc[hn] = lc_code(c);
                  hyf_bchar = non_char;
                } else if (type(s) == ligature_node)
/*898:*/

                {
                  if (font(lig_char(s)) != hf) goto done3;
                  j = hn;
                  q = lig_ptr(s);
                  if (q > null) hyf_bchar = character(q);
                  while (q > null) {
                    c = qo(character(q));
                    if (lc_code(c) == 0) goto done3;
                    if (j == 63) goto done3;
                    incr(j);
                    hu[j] = c;
                    hc[j] = lc_code(c);
                    q = link(q);
                  }
                  hb = s;
                  hn = j;
                  if (odd(subtype(s)))
                    hyf_bchar = font_bchar[hf];
                  else
                    hyf_bchar = non_char;
                }
/*:898*/

                else if ((type(s) == kern_node) && (subtype(s) == normal)) {
                  hb = s;
                  hyf_bchar = font_bchar[hf];
                } else
                  goto done3;
                s = link(s);
              }
            done3:

/*:897*/
                ;
/*899:*/

              if (hn < l_hyf + r_hyf) goto done1;
              loop {
                if (!(is_char_node(s))) switch (type(s)) {
                    case ligature_node:
                      do_nothing;
                      break;
                    case kern_node:
                      if (subtype(s) != normal) goto done4;
                      break;
                    case whatsit_node:
                    case glue_node:
                    case penalty_node:
                    case ins_node:
                    case adjust_node:
                    case mark_node:
                      goto done4;
                    default:
                      goto done1;
                  }
                s = link(s);
              }
            done4:

/*:899*/
                ;
              hyphenate();
            }
          done1:;
          }

/*:894*/
          ;
        } break;
        case kern_node:
          if (subtype(cur_p) == explicit)
            kern_break else act_width = act_width + width(cur_p);
          break;
        case ligature_node: {
          f = font(lig_char(cur_p));
          act_width = act_width +
                      char_width(f)(char_info(f)(character(lig_char(cur_p))));
        } break;
        case disc_node: /*869:*/

        {
          s = pre_break(cur_p);
          disc_width = 0;
          if (s == null)
            try_break(ex_hyphen_penalty, hyphenated);
          else {
            do { /*870:*/

              if (is_char_node(s)) {
                f = font(s);
                disc_width =
                    disc_width + char_width(f)(char_info(f)(character(s)));
              } else
                switch (type(s)) {
                  case ligature_node: {
                    f = font(lig_char(s));
                    disc_width =
                        disc_width +
                        char_width(f)(char_info(f)(character(lig_char(s))));
                  } break;
                  case hlist_node:
                  case vlist_node:
                  case rule_node:
                  case kern_node:
                    disc_width = disc_width + width(s);
                    break;
                  default:
                    confusion(/*1680:*/
                              555
/*:1680*/
                    );
                }

/*:870*/
                ;
              s = link(s);
            } while (!(s == null));
            act_width = act_width + disc_width;
            try_break(hyphen_penalty, hyphenated);
            act_width = act_width - disc_width;
          }
          r = replace_count(cur_p);
          s = link(cur_p);
          while (r > 0) { /*871:*/

            if (is_char_node(s)) {
              f = font(s);
              act_width = act_width + char_width(f)(char_info(f)(character(s)));
            } else
              switch (type(s)) {
                case ligature_node: {
                  f = font(lig_char(s));
                  act_width =
                      act_width +
                      char_width(f)(char_info(f)(character(lig_char(s))));
                } break;
                case hlist_node:
                case vlist_node:
                case rule_node:
                case kern_node:
                  act_width = act_width + width(s);
                  break;
                default:
                  confusion(/*1681:*/
                            556
/*:1681*/
                  );
              }

/*:871*/
              ;
            decr(r);
            s = link(s);
          }
          prev_p = cur_p;
          cur_p = s;
          goto done5;
        }

/*:869*/

        case math_node: {
          auto_breaking = (subtype(cur_p) == after);
          kern_break;
        } break;
        case penalty_node:
          try_break(penalty(cur_p), unhyphenated);
          break;
        case mark_node:
        case ins_node:
        case adjust_node:
          do_nothing;
          break;
        default:
          confusion(/*1679:*/
                    554
/*:1679*/
          );
      }
      prev_p = cur_p;
      cur_p = link(cur_p);
    done5:;
    }

/*:866*/
    ;
    if (cur_p == null)
/*873:*/

    {
      try_break(eject_penalty, hyphenated);
      if (link(active) != last_active) { /*874:*/

        r = link(active);
        fewest_demerits = awful_bad;
        do {
          if (type(r) != delta_node)
            if (total_demerits(r) < fewest_demerits) {
              fewest_demerits = total_demerits(r);
              best_bet = r;
            }
          r = link(r);
        } while (!(r == last_active));
        best_line = line_number(best_bet)

/*:874*/
            ;
        if (looseness == 0) goto done;
/*875:*/

        {
          r = link(active);
          actual_looseness = 0;
          do {
            if (type(r) != delta_node) {
              line_diff = line_number(r) - best_line;
              if (((line_diff < actual_looseness) &&
                   (looseness <= line_diff)) ||
                  ((line_diff > actual_looseness) &&
                   (looseness >= line_diff))) {
                best_bet = r;
                actual_looseness = line_diff;
                fewest_demerits = total_demerits(r);
              } else if ((line_diff == actual_looseness) &&
                         (total_demerits(r) < fewest_demerits)) {
                best_bet = r;
                fewest_demerits = total_demerits(r);
              }
            }
            r = link(r);
          } while (!(r == last_active));
          best_line = line_number(best_bet);
        }

/*:875*/
        ;
        if ((actual_looseness == looseness) || final_pass) goto done;
      }
    }

/*:873*/
    ;
/*865:*/

    q = link(active);
    while (q != last_active) {
      cur_p = link(q);
      if (type(q) == delta_node)
        free_node(q, delta_node_size);
      else
        free_node(q, active_node_size);
      q = cur_p;
    }
    q = passive;
    while (q != null) {
      cur_p = link(q);
      free_node(q, passive_node_size);
      q = cur_p;
    }

/*:865*/
    ;
    if (!second_pass) {
#ifdef STAT
      if (tracing_paragraphs > 0) print_nl("@secondpass");
#endif
      threshold = tolerance;
      second_pass = true;
      final_pass = (emergency_stretch <= 0);
    } else {
#ifdef STAT
      if (tracing_paragraphs > 0) print_nl("@emergencypass");
#endif
      background[2] = background[2] + emergency_stretch;
      final_pass = true;
    }
  }
done:
#ifdef STAT
  if (tracing_paragraphs > 0) {
    end_diagnostic(true);
    normalize_selector();
  }
#endif

/*:863*/
  ;
/*876:*/

  post_line_break(final_widow_penalty)

/*:876*/
      ;
/*865:*/

  q = link(active);
  while (q != last_active) {
    cur_p = link(q);
    if (type(q) == delta_node)
      free_node(q, delta_node_size);
    else
      free_node(q, active_node_size);
    q = cur_p;
  }
  q = passive;
  while (q != null) {
    cur_p = link(q);
    free_node(q, passive_node_size);
    q = cur_p;
  }

/*:865*/
  ;
  pack_begin_line = 0;
}

/*:815*/ /*934:*/
void new_hyph_exceptions(void) {
  uint8_t n;
  int j;
  hyph_pointer h;
  str_number k;
  pointer p;
  pointer q;
  str_number s, t;
  pool_pointer u, v;
  scan_left_brace();
  set_cur_lang;
/*935:*/

  n = 0;
  p = null;
  loop {
    get_x_token();
  reswitch:
    switch (cur_cmd) {
      case letter:
      case other_char:
      case char_given: /*937:*/

        if (cur_chr == '-') /*938:*/

        {
          if (n < 63) {
            q = get_avail();
            link(q) = p;
            info(q) = n;
            p = q;
          }
        }
/*:938*/

        else {
          if (lc_code(cur_chr) == 0) {
            print_err("Not a letter");

            help2("Letters in \\hyphenation words must have \\lccode>0.")(
                "Proceed; I'll ignore the character I just read.");
            error();
          } else if (n < 63) {
            incr(n);
            hc[n] = lc_code(cur_chr);
          }
        }

/*:937*/
        break;
      case char_num: {
        scan_char_num();
        cur_chr = cur_val;
        cur_cmd = char_given;
        goto reswitch;
      }
      case spacer:
      case right_brace: {
        if (n > 1) /*939:*/

        {
          incr(n);
          hc[n] = cur_lang;
          str_room(n);
          h = 0;
          for (j = 1; j <= n; j++) {
            h = (h + h + hc[j]) % hyph_size;
            append_char(hc[j]);
          }
          s = make_string();
/*940:*/

          if (hyph_count == hyph_size)
            overflow("exception dictionary", hyph_size);

          incr(hyph_count);
          while (hyph_word[h] != 0) { /*941:*/

            k = hyph_word[h];
            if (length(k) < length(s)) goto found;
            if (length(k) > length(s)) goto not_found;
            u = str_start[k];
            v = str_start[s];
            do {
              if (str_pool[u] < str_pool[v]) goto found;
              if (str_pool[u] > str_pool[v]) goto not_found;
              incr(u);
              incr(v);
            } while (!(u == str_start[k + 1]));
          found:
            q = hyph_list[h];
            hyph_list[h] = p;
            p = q;
            t = hyph_word[h];
            hyph_word[h] = s;
            s = t;
          not_found:

/*:941*/
              ;
            if (h > 0)
              decr(h);
            else
              h = hyph_size;
          }
          hyph_word[h] = s;
          hyph_list[h] = p

/*:940*/
              ;
        }

/*:939*/
        ;
        if (cur_cmd == right_brace) return;
        n = 0;
        p = null;
      } break;
      default: /*936:*/

      {
        print_err("Improper ");
        print_esc(/*1683:*/
                  558
/*:1683*/
        );

        print_str(" will be flushed");
        help2("Hyphenation exceptions must contain only letters")(
            "and hyphens. But continue; I'll forgive and forget.");
        error();
      }

/*:936*/
    }
  }

/*:935*/
  ;
}

/*:934*/ /*968:*/
pointer prune_page_top(pointer p) {
  pointer prev_p;
  pointer q;
  prev_p = temp_head;
  link(temp_head) = p;
  while (p != null) switch (type(p)) {
      case hlist_node:
      case vlist_node:
      case rule_node: /*969:*/

      {
        q = new_skip_param(split_top_skip_code);
        link(prev_p) = q;
        link(q) = p;

        if (width(temp_ptr) > height(p))
          width(temp_ptr) = width(temp_ptr) - height(p);
        else
          width(temp_ptr) = 0;
        p = null;
      }

/*:969*/
      break;
      case whatsit_node:
      case mark_node:
      case ins_node: {
        prev_p = p;
        p = link(prev_p);
      } break;
      case glue_node:
      case kern_node:
      case penalty_node: {
        q = p;
        p = link(q);
        link(q) = null;
        link(prev_p) = p;
        flush_node_list(q);
      } break;
      default:
        confusion(/*1685:*/
                  560
/*:1685*/
        );
    }
  return link(temp_head);
}

/*:968*/ /*970:*/
pointer vert_break(pointer p, scaled h, scaled d)

{
  pointer prev_p;

  pointer q, r;
  int pi;
  int b;
  int least_cost;
  pointer best_place;
  scaled prev_dp;
  small_number t;
  prev_p = p;
  least_cost = awful_bad;
  do_all_six(set_height_zero);
  prev_dp = 0;
  loop { /*972:*/

    if (p == null)
      pi = eject_penalty;
    else /*973:*/

      switch (type(p)) {
        case hlist_node:
        case vlist_node:
        case rule_node: {
          cur_height = cur_height + prev_dp + height(p);
          prev_dp = depth(p);
          goto not_found;
        }
        case whatsit_node: /*1365:*/

          goto not_found

/*:1365*/
              ;
        case glue_node:
          if (precedes_break(prev_p))
            pi = 0;
          else
            goto update_heights;
          break;
        case kern_node: {
          if (link(p) == null)
            t = penalty_node;
          else
            t = type(link(p));
          if (t == glue_node)
            pi = 0;
          else
            goto update_heights;
        } break;
        case penalty_node:
          pi = penalty(p);
          break;
        case mark_node:
        case ins_node:
          goto not_found;
        default:
          confusion(/*1686:*/
                    561
/*:1686*/
          );
      }

/*:973*/
      ;
/*974:*/

    if (pi < inf_penalty) { /*975:*/

      if (cur_height < h)
        if ((active_height[3] != 0) || (active_height[4] != 0) ||
            (active_height[5] != 0))
          b = 0;
        else
          b = badness(h - cur_height, active_height[2]);
      else if (cur_height - h > active_height[6])
        b = awful_bad;
      else
        b = badness(cur_height - h, active_height[6])

/*:975*/
            ;
      if (b < awful_bad)
        if (pi <= eject_penalty)
          b = pi;
        else if (b < inf_bad)
          b = b + pi;
        else
          b = deplorable;
      if (b <= least_cost) {
        best_place = p;
        least_cost = b;
        best_height_plus_depth = cur_height + prev_dp;
      }
      if ((b == awful_bad) || (pi <= eject_penalty)) goto done;
    }

/*:974*/
    ;
    if ((type(p) < glue_node) || (type(p) > kern_node)) goto not_found;
  update_heights: /*976:*/

    if (type(p) == kern_node)
      q = p;
    else {
      q = glue_ptr(p);
      active_height[2 + stretch_order(q)] =
          active_height[2 + stretch_order(q)] + stretch(q);
      active_height[6] = active_height[6] + shrink(q);
      if ((shrink_order(q) != normal) && (shrink(q) != 0)) {
        print_err("Infinite glue shrinkage found in box being split");

        help4("The box you are \\vsplitting contains some infinitely")(
            "shrinkable glue, e.g., `\\vss' or `\\vskip 0pt minus 1fil'.")(
            "Such glue doesn't belong there; but you can safely proceed,")(
            "since the offensive shrinkability has been made finite.");
        error();
        r = new_spec(q);
        shrink_order(r) = normal;
        delete_glue_ref(q);
        glue_ptr(p) = r;
        q = r;
      }
    }
    cur_height = cur_height + prev_dp + width(q);
    prev_dp = 0

/*:976*/
        ;
  not_found:
    if (prev_dp > d) {
      cur_height = cur_height + prev_dp - d;
      prev_dp = d;
    }

/*:972*/
    ;
    prev_p = p;
    p = link(prev_p);
  }
done:
  return best_place;
}

/*:970*/ /*977:*/
pointer vsplit(eight_bits n, scaled h)

{
  pointer v;
  pointer p;
  pointer q;
  v = box(n);
  if (split_first_mark != null) {
    delete_token_ref(split_first_mark);
    split_first_mark = null;
    delete_token_ref(split_bot_mark);
    split_bot_mark = null;
  }
/*978:*/

  if (v == null) {
    return null;
  }
  if (type(v) != vlist_node) {
    print_err("");
    print_esc(/*1687:*/
              562
/*:1687*/
    );
    print_str(" needs a ");
    print_esc(/*1688:*/
              563
/*:1688*/
    );

    help2("The box you are trying to split is an \\hbox.")(
        "I can't split such a box, so I'll leave it alone.");
    error();
    return null;
  }

/*:978*/
  ;
  q = vert_break(list_ptr(v), h, split_max_depth);
/*979:*/

  p = list_ptr(v);
  if (p == q)
    list_ptr(v) = null;
  else
    loop {
      if (type(p) == mark_node)
        if (split_first_mark == null) {
          split_first_mark = mark_ptr(p);
          split_bot_mark = split_first_mark;
          token_ref_count(split_first_mark) =
              token_ref_count(split_first_mark) + 2;
        } else {
          delete_token_ref(split_bot_mark);
          split_bot_mark = mark_ptr(p);
          add_token_ref(split_bot_mark);
        }
      if (link(p) == q) {
        link(p) = null;
        goto done;
      }
      p = link(p);
    }
done:

/*:979*/
    ;
  q = prune_page_top(q);
  p = list_ptr(v);
  free_node(v, box_node_size);
  if (q == null)
    box(n) = null;
  else
    box(n) = vpack(q, natural);
  return vpackage(p, h, exactly, split_max_depth);
}

/*:977*/ /*985:*/
void print_totals(void) {
  print_scaled(page_total);
  print_plus(2)("");
  print_plus(3)("fil");
  print_plus(4)("fill");
  print_plus(5)("filll");
  if (page_shrink != 0) {
    print_str(" minus ");
    print_scaled(page_shrink);
  }
}

/*:985*/ /*987:*/
void freeze_page_specs(small_number s) {
  page_contents = s;
  page_goal = vsize;
  page_max_depth = max_depth;
  page_depth = 0;
  do_all_six(set_page_so_far_zero);
  least_page_cost = awful_bad;
#ifdef STAT
  if (tracing_pages > 0) {
    begin_diagnostic();
    print_nl("%% goal height=");
    print_scaled(page_goal);

    print_str(", max depth=");
    print_scaled(page_max_depth);
    end_diagnostic(false);
  }
#endif
}

/*:987*/ /*992:*/
void box_error(eight_bits n) {
  error();
  begin_diagnostic();
  print_nl("The following box has been deleted:");

  show_box(box(n));
  end_diagnostic(true);
  flush_node_list(box(n));
  box(n) = null;
}

/*:992*/ /*993:*/
void ensure_vbox(eight_bits n) {
  pointer p;
  p = box(n);
  if (p != null)
    if (type(p) == hlist_node) {
      print_err("Insertions can only be added to a vbox");

      help3("Tut tut: You're trying to \\insert into a")(
          "\\box register that now contains an \\hbox.")(
          "Proceed, and I'll discard its present contents.");
      box_error(n);
    }
}

/*:993*/ /*994:*/
/*1012:*/

void fire_up(pointer c) {
  pointer p, q, r, s;
  pointer prev_p;
  uint8_t n;
  bool wait;
  int save_vbadness;
  scaled save_vfuzz;
  pointer save_split_top_skip;
/*1013:*/

  if (type(best_page_break) == penalty_node) {
    geq_word_define(int_base + output_penalty_code, penalty(best_page_break));
    penalty(best_page_break) = inf_penalty;
  } else
    geq_word_define(int_base + output_penalty_code, inf_penalty)

/*:1013*/
        ;
  if (bot_mark != null) {
    if (top_mark != null) delete_token_ref(top_mark);
    top_mark = bot_mark;
    add_token_ref(top_mark);
    delete_token_ref(first_mark);
    first_mark = null;
  }
/*1014:*/

  if (c == best_page_break) best_page_break = null;
/*1015:*/

  if (box(255) != null) {
    print_err("");
    print_esc(/*1437:*/
              312
/*:1437*/
    );
    print_str("255 is not void");

    help2("You shouldn't use \\box255 except in \\output routines.")(
        "Proceed, and I'll discard its present contents.");
    box_error(255);
  }

/*:1015*/
  ;
  insert_penalties = 0;
  save_split_top_skip = split_top_skip;
  if (holding_inserts <= 0)
/*1018:*/

  {
    r = link(page_ins_head);
    while (r != page_ins_head) {
      if (best_ins_ptr(r) != null) {
        n = qo(subtype(r));
        ensure_vbox(n);
        if (box(n) == null) box(n) = new_null_box();
        p = box(n) + list_offset;
        while (link(p) != null) p = link(p);
        last_ins_ptr(r) = p;
      }
      r = link(r);
    }
  }

/*:1018*/
  ;
  q = hold_head;
  link(q) = null;
  prev_p = page_head;
  p = link(prev_p);
  while (p != best_page_break) {
    if (type(p) == ins_node) {
      if (holding_inserts <= 0)
/*1020:*/

      {
        r = link(page_ins_head);
        while (subtype(r) != subtype(p)) r = link(r);
        if (best_ins_ptr(r) == null)
          wait = true;
        else {
          wait = false;
          s = last_ins_ptr(r);
          link(s) = ins_ptr(p);
          if (best_ins_ptr(r) == p)
/*1021:*/

          {
            if (type(r) == split_up)
              if ((broken_ins(r) == p) && (broken_ptr(r) != null)) {
                while (link(s) != broken_ptr(r)) s = link(s);
                link(s) = null;
                split_top_skip = split_top_ptr(p);
                ins_ptr(p) = prune_page_top(broken_ptr(r));
                if (ins_ptr(p) != null) {
                  temp_ptr = vpack(ins_ptr(p), natural);
                  height(p) = height(temp_ptr) + depth(temp_ptr);
                  free_node(temp_ptr, box_node_size);
                  wait = true;
                }
              }
            best_ins_ptr(r) = null;
            n = qo(subtype(r));
            temp_ptr = list_ptr(box(n));
            free_node(box(n), box_node_size);
            box(n) = vpack(temp_ptr, natural);
          }
/*:1021*/

          else {
            while (link(s) != null) s = link(s);
            last_ins_ptr(r) = s;
          }
        }
/*1022:*/

        link(prev_p) = link(p);
        link(p) = null;
        if (wait) {
          link(q) = p;
          q = p;
          incr(insert_penalties);
        } else {
          delete_glue_ref(split_top_ptr(p));
          free_node(p, ins_node_size);
        }
        p = prev_p

/*:1022*/
            ;
      }

/*:1020*/
      ;
    } else if (type(p) == mark_node) /*1016:*/

    {
      if (first_mark == null) {
        first_mark = mark_ptr(p);
        add_token_ref(first_mark);
      }
      if (bot_mark != null) delete_token_ref(bot_mark);
      bot_mark = mark_ptr(p);
      add_token_ref(bot_mark);
    }

/*:1016*/
    ;
    prev_p = p;
    p = link(prev_p);
  }
  split_top_skip = save_split_top_skip;
/*1017:*/

  if (p != null) {
    if (link(contrib_head) == null)
      if (nest_ptr == 0)
        tail = page_tail;
      else
        contrib_tail = page_tail;
    link(page_tail) = link(contrib_head);
    link(contrib_head) = p;
    link(prev_p) = null;
  }
  save_vbadness = vbadness;
  vbadness = inf_bad;
  save_vfuzz = vfuzz;
  vfuzz = max_dimen;
  box(255) = vpackage(link(page_head), best_size, exactly, page_max_depth);
  vbadness = save_vbadness;
  vfuzz = save_vfuzz;
  if (last_glue != max_halfword) delete_glue_ref(last_glue);
/*991:*/

  page_contents = empty;
  page_tail = page_head;
  link(page_head) = null;
  last_glue = max_halfword;
  last_penalty = 0;
  last_kern = 0;
  page_depth = 0;
  page_max_depth = 0

/*:991*/
      ;
  if (q != hold_head) {
    link(page_head) = link(hold_head);
    page_tail = q;
  }

/*:1017*/
  ;
/*1019:*/

  r = link(page_ins_head);
  while (r != page_ins_head) {
    q = link(r);
    free_node(r, page_ins_node_size);
    r = q;
  }
  link(page_ins_head) = page_ins_head

/*:1019*/

/*:1014*/
      ;
  if ((top_mark != null) && (first_mark == null)) {
    first_mark = top_mark;
    add_token_ref(top_mark);
  }
  if (output_routine != null)
    if (dead_cycles >= max_dead_cycles)
/*1024:*/

    {
      print_err("Output loop---");
      print_int(dead_cycles);

      print_str(" consecutive dead cycles");
      help3("I've concluded that your \\output is awry; it never does a")(
          "\\shipout, so I'm shipping \\box255 out myself. Next time")(
          "increase \\maxdeadcycles if you want me to be more patient!");
      error();
    }
/*:1024*/

    else /*1025:*/

    {
      output_active = true;
      incr(dead_cycles);
      push_nest();
      mode = -vmode;
      prev_depth = ignore_depth;
      mode_line = -line;
      begin_token_list(output_routine, output_text);
      new_save_level(output_group);
      normal_paragraph();
      scan_left_brace();
      return;
    }

/*:1025*/
    ;
/*1023:*/

  {
    if (link(page_head) != null) {
      if (link(contrib_head) == null)
        if (nest_ptr == 0)
          tail = page_tail;
        else
          contrib_tail = page_tail;
      else
        link(page_tail) = link(contrib_head);
      link(contrib_head) = link(page_head);
      link(page_head) = null;
      page_tail = page_head;
    }
    ship_out(box(255));
    box(255) = null;
  }

/*:1023*/
  ;
}

/*:1012*/

void build_page(void) {
  pointer p;
  pointer q, r;
  int b, c;
  int pi;
  uint8_t n;
  scaled delta, h, w;
  if ((link(contrib_head) == null) || output_active) return;
  do {
  resume:
    p = link(contrib_head);
/*996:*/

    if (last_glue != max_halfword) delete_glue_ref(last_glue);
    last_penalty = 0;
    last_kern = 0;
    if (type(p) == glue_node) {
      last_glue = glue_ptr(p);
      add_glue_ref(last_glue);
    } else {
      last_glue = max_halfword;
      if (type(p) == penalty_node)
        last_penalty = penalty(p);
      else if (type(p) == kern_node)
        last_kern = width(p);
    }

/*:996*/
    ;
/*997:*/

/*1000:*/

    switch (type(p)) {
      case hlist_node:
      case vlist_node:
      case rule_node:
        if (page_contents < box_there)
/*1001:*/

        {
          if (page_contents == empty)
            freeze_page_specs(box_there);
          else
            page_contents = box_there;
          q = new_skip_param(top_skip_code);
          if (width(temp_ptr) > height(p))
            width(temp_ptr) = width(temp_ptr) - height(p);
          else
            width(temp_ptr) = 0;
          link(q) = p;
          link(contrib_head) = q;
          goto resume;
        }
/*:1001*/

        else /*1002:*/

        {
          page_total = page_total + page_depth + height(p);
          page_depth = depth(p);
          goto contribute;
        }

/*:1002*/
        break;
      case whatsit_node: /*1364:*/

        goto contribute

/*:1364*/
            ;
      case glue_node:
        if (page_contents < box_there)
          goto done1;
        else if (precedes_break(page_tail))
          pi = 0;
        else
          goto update_heights;
        break;
      case kern_node:
        if (page_contents < box_there)
          goto done1;
        else if (link(p) == null)
          return;
        else if (type(link(p)) == glue_node)
          pi = 0;
        else
          goto update_heights;
        break;
      case penalty_node:
        if (page_contents < box_there)
          goto done1;
        else
          pi = penalty(p);
        break;
      case mark_node:
        goto contribute;
      case ins_node: /*1008:*/

      {
        if (page_contents == empty) freeze_page_specs(inserts_only);
        n = subtype(p);
        r = page_ins_head;
        while (n >= subtype(link(r))) r = link(r);
        n = qo(n);
        if (subtype(r) != qi(n))
/*1009:*/

        {
          q = get_node(page_ins_node_size);
          link(q) = link(r);
          link(r) = q;
          r = q;
          subtype(r) = qi(n);
          type(r) = inserting;
          ensure_vbox(n);
          if (box(n) == null)
            height(r) = 0;
          else
            height(r) = height(box(n)) + depth(box(n));
          best_ins_ptr(r) = null;
          q = skip(n);
          if (count(n) == 1000)
            h = height(r);
          else
            h = x_over_n(height(r), 1000) * count(n);
          page_goal = page_goal - h - width(q);
          page_so_far[2 + stretch_order(q)] =
              page_so_far[2 + stretch_order(q)] + stretch(q);
          page_shrink = page_shrink + shrink(q);
          if ((shrink_order(q) != normal) && (shrink(q) != 0)) {
            print_err("Infinite glue shrinkage inserted from ");
            print_esc(/*1423:*/
                      298
/*:1423*/
            );

            print_int(n);
            help3("The correction glue for page breaking with insertions")(
                "must have finite shrinkability. But you may proceed,")(
                "since the offensive shrinkability has been made finite.");
            error();
          }
        }

/*:1009*/
        ;
        if (type(r) == split_up)
          insert_penalties = insert_penalties + float_cost(p);
        else {
          last_ins_ptr(r) = p;
          delta = page_goal - page_total - page_depth + page_shrink;

          if (count(n) == 1000)
            h = height(p);
          else
            h = x_over_n(height(p), 1000) * count(n);
          if (((h <= 0) || (h <= delta)) &&
              (height(p) + height(r) <= dimen(n))) {
            page_goal = page_goal - h;
            height(r) = height(r) + height(p);
          } else /*1010:*/

          {
            if (count(n) <= 0)
              w = max_dimen;
            else {
              w = page_goal - page_total - page_depth;
              if (count(n) != 1000) w = x_over_n(w, count(n)) * 1000;
            }
            if (w > dimen(n) - height(r)) w = dimen(n) - height(r);
            q = vert_break(ins_ptr(p), w, depth(p));
            height(r) = height(r) + best_height_plus_depth;
#ifdef STAT
            if (tracing_pages > 0) /*1011:*/

            {
              begin_diagnostic();
              print_nl("% split");
              print_int(n);

              print_str(" to ");
              print_scaled(w);
              print_char(',');
              print_scaled(best_height_plus_depth);
              print_str(" p=");
              if (q == null)
                print_int(eject_penalty);
              else if (type(q) == penalty_node)
                print_int(penalty(q));
              else
                print_char('0');
              end_diagnostic(false);
            }

/*:1011*/
            ;
#endif

            if (count(n) != 1000)
              best_height_plus_depth =
                  x_over_n(best_height_plus_depth, 1000) * count(n);
            page_goal = page_goal - best_height_plus_depth;
            type(r) = split_up;
            broken_ptr(r) = q;
            broken_ins(r) = p;
            if (q == null)
              insert_penalties = insert_penalties + eject_penalty;
            else if (type(q) == penalty_node)
              insert_penalties = insert_penalties + penalty(q);
          }

/*:1010*/
          ;
        }
        goto contribute;
      }

/*:1008*/

      default:
        confusion(/*1697:*/
                  572
/*:1697*/
        );
    }

/*:1000*/
    ;
/*1005:*/

    if (pi < inf_penalty) { /*1007:*/

      if (page_total < page_goal)
        if ((page_so_far[3] != 0) || (page_so_far[4] != 0) ||
            (page_so_far[5] != 0))
          b = 0;
        else
          b = badness(page_goal - page_total, page_so_far[2]);
      else if (page_total - page_goal > page_shrink)
        b = awful_bad;
      else
        b = badness(page_total - page_goal, page_shrink)

/*:1007*/
            ;
      if (b < awful_bad)
        if (pi <= eject_penalty)
          c = pi;
        else if (b < inf_bad)
          c = b + pi + insert_penalties;
        else
          c = deplorable;
      else
        c = b;
      if (insert_penalties >= 10000) c = awful_bad;

#ifdef STAT
      if (tracing_pages > 0) /*1006:*/

      {
        begin_diagnostic();
        print_nl("%");
        print_str(" t=");
        print_totals();
        print_str(" g=");
        print_scaled(page_goal);
        print_str(" b=");
        if (b == awful_bad)
          print_char('*');
        else
          print_int(b);

        print_str(" p=");
        print_int(pi);
        print_str(" c=");
        if (c == awful_bad)
          print_char('*');
        else
          print_int(c);
        if (c <= least_page_cost) print_char('#');
        end_diagnostic(false);
      }

/*:1006*/
      ;
#endif

      if (c <= least_page_cost) {
        best_page_break = p;
        best_size = page_goal;
        least_page_cost = c;
        r = link(page_ins_head);
        while (r != page_ins_head) {
          best_ins_ptr(r) = last_ins_ptr(r);
          r = link(r);
        }
      }
      if ((c == awful_bad) || (pi <= eject_penalty)) {
        fire_up(p);
        if (output_active) return;
        goto done;
      }
    }

/*:1005*/
    ;
    if ((type(p) < glue_node) || (type(p) > kern_node)) goto contribute;
  update_heights: /*1004:*/

    if (type(p) == kern_node)
      q = p;
    else {
      q = glue_ptr(p);
      page_so_far[2 + stretch_order(q)] =
          page_so_far[2 + stretch_order(q)] + stretch(q);
      page_shrink = page_shrink + shrink(q);
      if ((shrink_order(q) != normal) && (shrink(q) != 0)) {
        print_err("Infinite glue shrinkage found on current page");

        help4("The page about to be output contains some infinitely")(
            "shrinkable glue, e.g., `\\vss' or `\\vskip 0pt minus 1fil'.")(
            "Such glue doesn't belong there; but you can safely proceed,")(
            "since the offensive shrinkability has been made finite.");
        error();
        r = new_spec(q);
        shrink_order(r) = normal;
        delete_glue_ref(q);
        glue_ptr(p) = r;
        q = r;
      }
    }
    page_total = page_total + page_depth + width(q);
    page_depth = 0

/*:1004*/
        ;
  contribute: /*1003:*/

    if (page_depth > page_max_depth) {
      page_total = page_total + page_depth - page_max_depth;
      page_depth = page_max_depth;
    }

/*:1003*/
    ;
/*998:*/

    link(page_tail) = p;
    page_tail = p;
    link(contrib_head) = link(p);
    link(p) = null;
    goto done

/*:998*/
        ;
  done1: /*999:*/

    link(contrib_head) = link(p);
    link(p) = null;
    flush_node_list(p)

/*:999*/
        ;
  done:

/*:997*/
      ;
  } while (!(link(contrib_head) == null));
/*995:*/

  if (nest_ptr == 0)
    tail = contrib_head;
  else
    contrib_tail = contrib_head

/*:995*/
        ;
}

/*:994*/ /*1030:*/
/*1043:*/

void app_space(void) {
  pointer q;
  if ((space_factor >= 2000) && (xspace_skip != zero_glue))
    q = new_param_glue(xspace_skip_code);
  else {
    if (space_skip != zero_glue)
      main_p = space_skip;
    else /*1042:*/

    {
      main_p = font_glue[cur_font];
      if (main_p == null) {
        main_p = new_spec(zero_glue);
        main_k = param_base[cur_font] + space_code;
        width(main_p) = font_info[main_k].sc;
        stretch(main_p) = font_info[main_k + 1].sc;
        shrink(main_p) = font_info[main_k + 2].sc;
        font_glue[cur_font] = main_p;
      }
    }

/*:1042*/
    ;
    main_p = new_spec(main_p);
/*1044:*/

    if (space_factor >= 2000)
      width(main_p) = width(main_p) + extra_space(cur_font);
    stretch(main_p) = xn_over_d(stretch(main_p), space_factor, 1000);
    shrink(main_p) = xn_over_d(shrink(main_p), 1000, space_factor)

/*:1044*/
        ;
    q = new_glue(main_p);
    glue_ref_count(main_p) = null;
  }
  link(tail) = q;
  tail = q;
}

/*:1043*/ /*1047:*/

void insert_dollar_sign(void) {
  back_input();
  cur_tok = math_shift_token + '$';
  print_err("Missing $ inserted");

  help2("I've inserted a begin-math/end-math symbol since I think")(
      "you left one out. Proceed, with fingers crossed.");
  ins_error();
}

/*:1047*/ /*1049:*/

void you_cant(void) {
  print_err("You can't use `");

  print_cmd_chr(cur_cmd, cur_chr);
  print_str("' in ");
  print_mode(mode);
}

/*:1049*/ /*1050:*/

void report_illegal_case(void) {
  you_cant();
  help4("Sorry, but I'm not programmed to handle this case;")(
      "I'll just pretend that you didn't ask for it.")(
      "If you're in the wrong mode, you might be able to")(
      "return to the right one by typing `I}' or `I$' or `I\\par'.");
  error();
}

/*:1050*/ /*1051:*/

bool privileged(void) {
  if (mode > 0)
    return true;
  else {
    report_illegal_case();
    return false;
  }
}

/*:1051*/ /*1054:*/

bool its_all_over(void) {
  if (privileged()) {
    if ((page_head == page_tail) && (head == tail) && (dead_cycles == 0)) {
      return true;
    }
    back_input();
    tail_append(new_null_box());
    width(tail) = hsize;
    tail_append(new_glue(fill_glue));
    tail_append(new_penalty(-010000000000));
    build_page();
  }
  return false;
}

/*:1054*/ /*1060:*/

void append_glue(void) {
  small_number s;
  s = cur_chr;
  switch (s) {
    case fil_code:
      cur_val = fil_glue;
      break;
    case fill_code:
      cur_val = fill_glue;
      break;
    case ss_code:
      cur_val = ss_glue;
      break;
    case fil_neg_code:
      cur_val = fil_neg_glue;
      break;
    case skip_code:
      scan_glue(glue_val);
      break;
    case mskip_code:
      scan_glue(mu_val);
  }
  tail_append(new_glue(cur_val));
  if (s >= skip_code) {
    decr(glue_ref_count(cur_val));
    if (s > skip_code) subtype(tail) = mu_glue;
  }
}

/*:1060*/ /*1061:*/

void append_kern(void) {
  quarterword s;
  s = cur_chr;
  scan_dimen(s == mu_glue, false, false);
  tail_append(new_kern(cur_val));
  subtype(tail) = s;
}

/*:1061*/ /*1064:*/

void off_save(void) {
  pointer p;
  if (cur_group == bottom_level)
/*1066:*/

  {
    print_err("Extra ");
    print_cmd_chr(cur_cmd, cur_chr);

    help1("Things are pretty mixed up, but I think the worst is over.");
    error();
  }
/*:1066*/

  else {
    back_input();
    p = get_avail();
    link(temp_head) = p;
    print_err("Missing ");
/*1065:*/

    switch (cur_group) {
      case semi_simple_group: {
        info(p) = cs_token_flag + frozen_end_group;
        print_esc(/*1538:*/
                  413
/*:1538*/
        );

      } break;
      case math_shift_group: {
        info(p) = math_shift_token + '$';
        print_char('$');

      } break;
      case math_left_group: {
        info(p) = cs_token_flag + frozen_right;
        link(p) = get_avail();
        p = link(p);
        info(p) = other_token + '.';
        print_esc(/*1710:*/
                  585
/*:1710*/
        );

      } break;
      default: {
        info(p) = right_brace_token + '}';
        print_char('}');
      }
    }

/*:1065*/
    ;
    print_str(" inserted");
    ins_list(link(temp_head));
    help5("I've inserted something that you may have forgotten.")(
        "(See the <inserted text> above.)")(
        "With luck, this will get me unwedged. But if you")(
        "really didn't forget anything, try typing `2' now; then")(
        "my insertion and my current dilemma will both disappear.");
    error();
  }
}

/*:1064*/ /*1069:*/

void extra_right_brace(void) {
  print_err("Extra }, or forgotten ");

  switch (cur_group) {
    case semi_simple_group:
      print_esc(/*1538:*/
                413
/*:1538*/
      );
      break;
    case math_shift_group:
      print_char('$');
      break;
    case math_left_group:
      print_esc(/*1660:*/
                535
/*:1660*/
      );
  }
  help5("I've deleted a group-closing symbol because it seems to be")(
      "spurious, as in `$x}$'. But perhaps the } is legitimate and")(
      "you forgot something else, as in `\\hbox{$x}'. In such cases")(
      "the way to recover is to insert both the forgotten and the")(
      "deleted material, e.g., by typing `I$}'.");
  error();
  incr(align_state);
}

/*:1069*/ /*1070:*/

void normal_paragraph(void) {
  if (looseness != 0) eq_word_define(int_base + looseness_code, 0);
  if (hang_indent != 0) eq_word_define(dimen_base + hang_indent_code, 0);
  if (hang_after != 1) eq_word_define(int_base + hang_after_code, 1);
  if (par_shape_ptr != null) eq_define(par_shape_loc, shape_ref, null);
}

/*:1070*/ /*1075:*/

void box_end(int box_context) {
  pointer p;
  if (box_context < box_flag) /*1076:*/

  {
    if (cur_box != null) {
      shift_amount(cur_box) = box_context;
      if (abs(mode) == vmode) {
        append_to_vlist(cur_box);
        if (adjust_tail != null) {
          if (adjust_head != adjust_tail) {
            link(tail) = link(adjust_head);
            tail = adjust_tail;
          }
          adjust_tail = null;
        }
        if (mode > 0) build_page();
      } else {
        if (abs(mode) == hmode)
          space_factor = 1000;
        else {
          p = new_noad();
          math_type(nucleus(p)) = sub_box;
          info(nucleus(p)) = cur_box;
          cur_box = p;
        }
        link(tail) = cur_box;
        tail = cur_box;
      }
    }
  }

/*:1076*/

  else if (box_context < ship_out_flag) /*1077:*/

    if (box_context < box_flag + 256)
      eq_define(box_base - box_flag + box_context, box_ref, cur_box);
    else
      geq_define(box_base - box_flag - 256 + box_context, box_ref, cur_box)

/*:1077*/
          ;
  else if (cur_box != null)
    if (box_context > ship_out_flag) /*1078:*/

    { /*404:*/

      do {
        get_x_token();
      } while (!((cur_cmd != spacer) && (cur_cmd != relax)))

/*:404*/
          ;
      if (((cur_cmd == hskip) && (abs(mode) != vmode)) ||
          ((cur_cmd == vskip) && (abs(mode) == vmode))) {
        append_glue();
        subtype(tail) = box_context - (leader_flag - a_leaders);
        leader_ptr(tail) = cur_box;
      } else {
        print_err("Leaders not followed by proper glue");

        help3("You should say `\\leaders <box or rule><hskip or vskip>'.")(
            "I found the <box or rule>, but there's no suitable")(
            "<hskip or vskip>, so I'm ignoring these leaders.");
        back_error();
        flush_node_list(cur_box);
      }
    }

/*:1078*/

    else
      ship_out(cur_box);
}

/*:1075*/ /*1079:*/

void begin_box(int box_context) {
  pointer p, q;
  int m;
  halfword k;
  eight_bits n;
  switch (cur_chr) {
    case box_code: {
      scan_eight_bit_int();
      cur_box = box(cur_val);
      box(cur_val) = null;
    } break;
    case copy_code: {
      scan_eight_bit_int();
      cur_box = copy_node_list(box(cur_val));
    } break;
    case last_box_code: /*1080:*/

    {
      cur_box = null;
      if (abs(mode) == mmode) {
        you_cant();
        help1("Sorry; this \\lastbox will be void.");
        error();
      } else if ((mode == vmode) && (head == tail)) {
        you_cant();
        help2("Sorry...I usually can't take things from the current page.")(
            "This \\lastbox will therefore be void.");
        error();
      } else {
        if (!is_char_node(tail))
          if ((type(tail) == hlist_node) || (type(tail) == vlist_node))
/*1081:*/

          {
            q = head;
            do {
              p = q;
              if (!is_char_node(q))
                if (type(q) == disc_node) {
                  for (m = 1; m <= replace_count(q); m++) p = link(p);
                  if (p == tail) goto done;
                }
              q = link(p);
            } while (!(q == tail));
            cur_box = tail;
            shift_amount(cur_box) = 0;
            tail = p;
            link(p) = null;
          done:;
          }

/*:1081*/
          ;
      }
    }

/*:1080*/
    break;
    case vsplit_code: /*1082:*/

    {
      scan_eight_bit_int();
      n = cur_val;
      if (!scan_keyword(/*1642:*/
                        517
/*:1642*/
                        ))

      {
        print_err("Missing `to' inserted");

        help2("I'm working on `\\vsplit<box number> to <dimen>';")(
            "will look for the <dimen> next.");
        error();
      }
      scan_normal_dimen;
      cur_box = vsplit(n, cur_val);
    }

/*:1082*/
    break;
    default: /*1083:*/

    {
      k = cur_chr - vtop_code;
      saved(0) = box_context;
      if (k == hmode)
        if ((box_context < box_flag) && (abs(mode) == vmode))
          scan_spec(adjusted_hbox_group, true);
        else
          scan_spec(hbox_group, true);
      else {
        if (k == vmode)
          scan_spec(vbox_group, true);
        else {
          scan_spec(vtop_group, true);
          k = vmode;
        }
        normal_paragraph();
      }
      push_nest();
      mode = -k;
      if (k == vmode) {
        prev_depth = ignore_depth;
        if (every_vbox != null) begin_token_list(every_vbox, every_vbox_text);
      } else {
        space_factor = 1000;
        if (every_hbox != null) begin_token_list(every_hbox, every_hbox_text);
      }
      return;
    }

/*:1083*/
  }
  box_end(box_context);
}

/*:1079*/ /*1084:*/

void scan_box(int box_context)

{ /*404:*/

  do {
    get_x_token();
  } while (!((cur_cmd != spacer) && (cur_cmd != relax)))

/*:404*/
      ;
  if (cur_cmd == make_box)
    begin_box(box_context);
  else if ((box_context >= leader_flag) &&
           ((cur_cmd == hrule) || (cur_cmd == vrule))) {
    cur_box = scan_rule_spec();
    box_end(box_context);
  } else {
    print_err("A <box> was supposed to be here");

    help3("I was expecting to see \\hbox or \\vbox or \\copy or \\box or")(
        "something like that. So you might find something missing in")(
        "your output. But keep trying; you can fix this later.");
    back_error();
  }
}

/*:1084*/ /*1086:*/

void package(small_number c) {
  scaled h;
  pointer p;
  scaled d;
  d = box_max_depth;
  unsave();
  save_ptr = save_ptr - 3;
  if (mode == -hmode)
    cur_box = hpack(link(head), saved(2), saved(1));
  else {
    cur_box = vpackage(link(head), saved(2), saved(1), d);
    if (c == vtop_code) /*1087:*/

    {
      h = 0;
      p = list_ptr(cur_box);
      if (p != null)
        if (type(p) <= rule_node) h = height(p);
      depth(cur_box) = depth(cur_box) - h + height(cur_box);
      height(cur_box) = h;
    }

/*:1087*/
    ;
  }
  pop_nest();
  box_end(saved(0));
}

/*:1086*/ /*1091:*/

small_number norm_min(int h) {
  if (h <= 0)
    return 1;
  else if (h >= 63)
    return 63;
  else
    return h;
}

void new_graf(bool indented) {
  prev_graf = 0;
  if ((mode == vmode) || (head != tail))
    tail_append(new_param_glue(par_skip_code));
  push_nest();
  mode = hmode;
  space_factor = 1000;
  set_cur_lang;
  clang = cur_lang;
  prev_graf = (norm_min(left_hyphen_min) * 0100 + norm_min(right_hyphen_min)) *
                  0200000 +
              cur_lang;
  if (indented) {
    tail = new_null_box();
    link(head) = tail;
    width(tail) = par_indent;
  }
  if (every_par != null) begin_token_list(every_par, every_par_text);
  if (nest_ptr == 1) build_page();
}

/*:1091*/ /*1093:*/

void indent_in_hmode(void) {
  pointer p, q;
  if (cur_chr > 0) {
    p = new_null_box();
    width(p) = par_indent;
    if (abs(mode) == hmode)
      space_factor = 1000;
    else {
      q = new_noad();
      math_type(nucleus(q)) = sub_box;
      info(nucleus(q)) = p;
      p = q;
    }
    tail_append(p);
  }
}

/*:1093*/ /*1095:*/

void head_for_vmode(void) {
  if (mode < 0)
    if (cur_cmd != hrule)
      off_save();
    else {
      print_err("You can't use `");
      print_esc(/*1543:*/
                418
/*:1543*/
      );
      print_str("' here except with leaders");

      help2("To put a horizontal rule in an hbox or an alignment,")(
          "you should use \\leaders or \\hrulefill (see The TeXbook).");
      error();
    }
  else {
    back_input();
    cur_tok = par_token;
    back_input();
    token_type = inserted;
  }
}

/*:1095*/ /*1096:*/

void end_graf(void) {
  if (mode == hmode) {
    if (head == tail)
      pop_nest();
    else
      line_break(widow_penalty);
    normal_paragraph();
    error_count = 0;
  }
}

/*:1096*/ /*1099:*/

void begin_insert_or_adjust(void) {
  if (cur_cmd == vadjust)
    cur_val = 255;
  else {
    scan_eight_bit_int();
    if (cur_val == 255) {
      print_err("You can't ");
      print_esc(/*1390:*/
                265
/*:1390*/
      );
      print_int(255);

      help1("I'm changing to \\insert0; box 255 is special.");
      error();
      cur_val = 0;
    }
  }
  saved(0) = cur_val;
  incr(save_ptr);
  new_save_level(insert_group);
  scan_left_brace();
  normal_paragraph();
  push_nest();
  mode = -vmode;
  prev_depth = ignore_depth;
}

/*:1099*/ /*1101:*/

void make_mark(void) {
  pointer p;
  p = scan_toks(false, true);
  p = get_node(small_node_size);
  type(p) = mark_node;
  subtype(p) = 0;
  mark_ptr(p) = def_ref;
  link(tail) = p;
  tail = p;
}

/*:1101*/ /*1103:*/

void append_penalty(void) {
  scan_int();
  tail_append(new_penalty(cur_val));
  if (mode == vmode) build_page();
}

/*:1103*/ /*1105:*/

void delete_last(void) {
  pointer p, q;
  int m;
  if ((mode == vmode) && (tail == head))
/*1106:*/

  {
    if ((cur_chr != glue_node) || (last_glue != max_halfword)) {
      you_cant();
      help2("Sorry...I usually can't take things from the current page.")(
          "Try `I\\vskip-\\lastskip' instead.");
      if (cur_chr == kern_node)
        help_line[0] = ("Try `I\\kern-\\lastkern' instead.");
      else if (cur_chr != glue_node)
        help_line[0] = ("Perhaps you can make the output routine do it.");
      error();
    }
  }
/*:1106*/

  else {
    if (!is_char_node(tail))
      if (type(tail) == cur_chr) {
        q = head;
        do {
          p = q;
          if (!is_char_node(q))
            if (type(q) == disc_node) {
              for (m = 1; m <= replace_count(q); m++) p = link(p);
              if (p == tail) return;
            }
          q = link(p);
        } while (!(q == tail));
        link(p) = null;
        flush_node_list(tail);
        tail = p;
      }
  }
}

/*:1105*/ /*1110:*/

void unpackage(void) {
  pointer p;
  uint8_t c;
  c = cur_chr;
  scan_eight_bit_int();
  p = box(cur_val);
  if (p == null) return;
  if ((abs(mode) == mmode) ||
      ((abs(mode) == vmode) && (type(p) != vlist_node)) ||
      ((abs(mode) == hmode) && (type(p) != hlist_node))) {
    print_err("Incompatible list can't be unboxed");

    help3("Sorry, Pandora. (You sneaky devil.)")(
        "I refuse to unbox an \\hbox in vertical mode or vice versa.")(
        "And I can't open any boxes in math mode.");
    error();
    return;
  }
  if (c == copy_code)
    link(tail) = copy_node_list(list_ptr(p));
  else {
    link(tail) = list_ptr(p);
    box(cur_val) = null;
    free_node(p, box_node_size);
  }
  while (link(tail) != null) tail = link(tail);
}

/*:1110*/ /*1113:*/

void append_italic_correction(void) {
  pointer p;
  internal_font_number f;
  if (tail != head) {
    if (is_char_node(tail))
      p = tail;
    else if (type(tail) == ligature_node)
      p = lig_char(tail);
    else
      return;
    f = font(p);
    tail_append(new_kern(char_italic(f)(char_info(f)(character(p)))));
    subtype(tail) = explicit;
  }
}

/*:1113*/ /*1117:*/

void append_discretionary(void) {
  int c;
  tail_append(new_disc());
  if (cur_chr == 1) {
    c = hyphen_char[cur_font];
    if (c >= 0)
      if (c < 256) pre_break(tail) = new_character(cur_font, c);
  } else {
    incr(save_ptr);
    saved(-1) = 0;
    new_save_level(disc_group);
    scan_left_brace();
    push_nest();
    mode = -hmode;
    space_factor = 1000;
  }
}

/*:1117*/ /*1119:*/

void build_discretionary(void) {
  pointer p, q;
  int n;
  unsave();
/*1121:*/

  q = head;
  p = link(q);
  n = 0;
  while (p != null) {
    if (!is_char_node(p))
      if (type(p) > rule_node)
        if (type(p) != kern_node)
          if (type(p) != ligature_node) {
            print_err("Improper discretionary list");

            help1("Discretionary lists must contain only boxes and kerns.");
            error();
            begin_diagnostic();
            print_nl("The following discretionary sublist has been deleted:");

            show_box(p);
            end_diagnostic(true);
            flush_node_list(p);
            link(q) = null;
            goto done;
          }
    q = p;
    p = link(q);
    incr(n);
  }
done:

/*:1121*/
    ;
  p = link(head);
  pop_nest();
  switch (saved(-1)) {
    case 0:
      pre_break(tail) = p;
      break;
    case 1:
      post_break(tail) = p;
      break;
    case 2: /*1120:*/

    {
      if ((n > 0) && (abs(mode) == mmode)) {
        print_err("Illegal math ");
        print_esc(/*1400:*/
                  275
/*:1400*/
        );

        help2("Sorry: The third part of a discretionary break must be")(
            "empty, in math formulas. I had to delete your third part.");
        flush_node_list(p);
        n = 0;
        error();
      } else
        link(tail) = p;
      if (n <= max_quarterword)
        replace_count(tail) = n;
      else {
        print_err("Discretionary list is too long");

        help2("Wow---I never thought anybody would tweak me here.")(
            "You can't seriously need such a huge discretionary list?");
        error();
      }
      if (n > 0) tail = q;
      decr(save_ptr);
      return;
    }

/*:1120*/
    ;
  }
  incr(saved(-1));
  new_save_level(disc_group);
  scan_left_brace();
  push_nest();
  mode = -hmode;
  space_factor = 1000;
}

/*:1119*/ /*1123:*/

void make_accent(void) {
  double s, t;
  pointer p, q, r;
  internal_font_number f;
  scaled a, h, x, w, delta;
  four_quarters i;
  scan_char_num();
  f = cur_font;
  p = new_character(f, cur_val);
  if (p != null) {
    x = x_height(f);
    s = slant(f) / float_constant(65536);

    a = char_width(f)(char_info(f)(character(p)));
    do_assignments();
/*1124:*/

    q = null;
    f = cur_font;
    if ((cur_cmd == letter) || (cur_cmd == other_char) ||
        (cur_cmd == char_given))
      q = new_character(f, cur_chr);
    else if (cur_cmd == char_num) {
      scan_char_num();
      q = new_character(f, cur_val);
    } else
      back_input()

/*:1124*/
          ;
    if (q != null) /*1125:*/

    {
      t = slant(f) / float_constant(65536);

      i = char_info(f)(character(q));
      w = char_width(f)(i);
      h = char_height(f)(height_depth(i));
      if (h != x) {
        p = hpack(p, natural);
        shift_amount(p) = x - h;
      }
      delta = round((w - a) / float_constant(2) + h * t - x * s);

      r = new_kern(delta);
      subtype(r) = acc_kern;
      link(tail) = r;
      link(r) = p;
      tail = new_kern(-a - delta);
      subtype(tail) = acc_kern;
      link(p) = tail;
      p = q;
    }

/*:1125*/
    ;
    link(tail) = p;
    tail = p;
    space_factor = 1000;
  }
}

/*:1123*/ /*1127:*/

void align_error(void) {
  if (abs(align_state) > 2)
/*1128:*/

  {
    print_err("Misplaced ");
    print_cmd_chr(cur_cmd, cur_chr);

    if (cur_tok == tab_token + '&') {
      help6("I can't figure out why you would want to use a tab mark")(
          "here. If you just want an ampersand, the remedy is")(
          "simple: Just type `I\\&' now. But if some right brace")(
          "up above has ended a previous alignment prematurely,")(
          "you're probably due for more error messages, and you")(
          "might try typing `S' now just to see what is salvageable.");
    } else {
      help5("I can't figure out why you would want to use a tab mark")(
          "or \\cr or \\span just now. If something like a right brace")(
          "up above has ended a previous alignment prematurely,")(
          "you're probably due for more error messages, and you")(
          "might try typing `S' now just to see what is salvageable.");
    }
    error();
  }
/*:1128*/

  else {
    back_input();
    if (align_state < 0) {
      print_err("Missing { inserted");

      incr(align_state);
      cur_tok = left_brace_token + '{';
    } else {
      print_err("Missing } inserted");

      decr(align_state);
      cur_tok = right_brace_token + '}';
    }
    help3("I've put in what seems to be necessary to fix")(
        "the current column of the current alignment.")(
        "Try to go on, since this might almost work.");
    ins_error();
  }
}

/*:1127*/ /*1129:*/

void no_align_error(void) {
  print_err("Misplaced ");
  print_esc(/*1549:*/
            424
/*:1549*/
  );

  help2("I expect to see \\noalign only after the \\cr of")(
      "an alignment. Proceed, and I'll ignore this case.");
  error();
}
void omit_error(void) {
  print_err("Misplaced ");
  print_esc(/*1552:*/
            427
/*:1552*/
  );

  help2("I expect to see \\omit only after tab marks or the \\cr of")(
      "an alignment. Proceed, and I'll ignore this case.");
  error();
}

/*:1129*/ /*1131:*/

void do_endv(void) {
  base_ptr = input_ptr;
  input_stack[base_ptr] = cur_input;
  while ((input_stack[base_ptr].index_field != v_template) &&
         (input_stack[base_ptr].loc_field == null) &&
         (input_stack[base_ptr].state_field == token_list))
    decr(base_ptr);
  if ((input_stack[base_ptr].index_field != v_template) ||
      (input_stack[base_ptr].loc_field != null) ||
      (input_stack[base_ptr].state_field != token_list))
    fatal_error("(interwoven alignment preambles are not allowed)");

  if (cur_group == align_group) {
    end_graf();
    if (fin_col()) fin_row();
  } else
    off_save();
}

/*:1131*/ /*1135:*/

void cs_error(void) {
  print_err("Extra ");
  print_esc(/*1527:*/
            402
/*:1527*/
  );

  help1("I'm ignoring this, since I wasn't doing a \\csname.");
  error();
}

/*:1135*/ /*1136:*/

void push_math(group_code c) {
  push_nest();
  mode = -mmode;
  incompleat_noad = null;
  new_save_level(c);
}

/*:1136*/ /*1138:*/

void init_math(void) {
  scaled w;
  scaled l;
  scaled s;
  pointer p;
  pointer q;
  internal_font_number f;
  int n;
  scaled v;
  scaled d;
  get_token();
  if ((cur_cmd == math_shift) && (mode > 0)) /*1145:*/

  {
    if (head == tail) {
      pop_nest();
      w = -max_dimen;
    } else {
      line_break(display_widow_penalty);
/*1146:*/

      v = shift_amount(just_box) + 2 * quad(cur_font);
      w = -max_dimen;
      p = list_ptr(just_box);
      while (p != null) { /*1147:*/

      reswitch:
        if (is_char_node(p)) {
          f = font(p);
          d = char_width(f)(char_info(f)(character(p)));
          goto found;
        }
        switch (type(p)) {
          case hlist_node:
          case vlist_node:
          case rule_node: {
            d = width(p);
            goto found;
          }
          case ligature_node: /*652:*/

          {
            mem[lig_trick] = mem[lig_char(p)];
            link(lig_trick) = link(p);
            p = lig_trick;
            goto reswitch;
          }

/*:652*/

          case kern_node:
          case math_node:
            d = width(p);
            break;
          case glue_node: /*1148:*/

          {
            q = glue_ptr(p);
            d = width(q);
            if (glue_sign(just_box) == stretching) {
              if ((glue_order(just_box) == stretch_order(q)) &&
                  (stretch(q) != 0))
                v = max_dimen;
            } else if (glue_sign(just_box) == shrinking) {
              if ((glue_order(just_box) == shrink_order(q)) && (shrink(q) != 0))
                v = max_dimen;
            }
            if (subtype(p) >= a_leaders) goto found;
          }

/*:1148*/
          break;
          case whatsit_node: /*1361:*/
            d = 0

/*:1361*/
                ;
            break;
          default:
            d = 0;
        }

/*:1147*/
        ;
        if (v < max_dimen) v = v + d;
        goto not_found;
      found:
        if (v < max_dimen) {
          v = v + d;
          w = v;
        } else {
          w = max_dimen;
          goto done;
        }
      not_found:
        p = link(p);
      }
    done:

/*:1146*/
        ;
    }

/*1149:*/

    if (par_shape_ptr == null)
      if ((hang_indent != 0) &&
          (((hang_after >= 0) && (prev_graf + 2 > hang_after)) ||
           (prev_graf + 1 < -hang_after))) {
        l = hsize - abs(hang_indent);
        if (hang_indent > 0)
          s = hang_indent;
        else
          s = 0;
      } else {
        l = hsize;
        s = 0;
      }
    else {
      n = info(par_shape_ptr);
      if (prev_graf + 2 >= n)
        p = par_shape_ptr + 2 * n;
      else
        p = par_shape_ptr + 2 * (prev_graf + 2);
      s = mem[p - 1].sc;
      l = mem[p].sc;
    }

/*:1149*/
    ;
    push_math(math_shift_group);
    mode = mmode;
    eq_word_define(int_base + cur_fam_code, -1);
    eq_word_define(dimen_base + pre_display_size_code, w);
    eq_word_define(dimen_base + display_width_code, l);
    eq_word_define(dimen_base + display_indent_code, s);
    if (every_display != null)
      begin_token_list(every_display, every_display_text);
    if (nest_ptr == 1) build_page();
  }
/*:1145*/

  else {
    back_input(); /*1139:*/

    {
      push_math(math_shift_group);
      eq_word_define(int_base + cur_fam_code, -1);
      if (every_math != null) begin_token_list(every_math, every_math_text);
    }

/*:1139*/
    ;
  }
}

/*:1138*/ /*1142:*/

void start_eq_no(void) {
  saved(0) = cur_chr;
  incr(save_ptr);
/*1139:*/

  {
    push_math(math_shift_group);
    eq_word_define(int_base + cur_fam_code, -1);
    if (every_math != null) begin_token_list(every_math, every_math_text);
  }

/*:1139*/
  ;
}

/*:1142*/ /*1151:*/

void scan_math(pointer p) {
  int c;
restart: /*404:*/

  do {
    get_x_token();
  } while (!((cur_cmd != spacer) && (cur_cmd != relax)))

/*:404*/
      ;
reswitch:
  switch (cur_cmd) {
    case letter:
    case other_char:
    case char_given: {
      c = ho(math_code(cur_chr));
      if (c == 0100000) { /*1152:*/

        {
          cur_cs = cur_chr + active_base;
          cur_cmd = eq_type(cur_cs);
          cur_chr = equiv(cur_cs);
          x_token();
          back_input();
        }

/*:1152*/
        ;
        goto restart;
      }
    } break;
    case char_num: {
      scan_char_num();
      cur_chr = cur_val;
      cur_cmd = char_given;
      goto reswitch;
    }
    case math_char_num: {
      scan_fifteen_bit_int();
      c = cur_val;
    } break;
    case math_given:
      c = cur_chr;
      break;
    case delim_num: {
      scan_twenty_seven_bit_int();
      c = cur_val / 010000;
    } break;
    default: /*1153:*/

    {
      back_input();
      scan_left_brace();
      saved(0) = p;
      incr(save_ptr);
      push_math(math_group);
      return;
    }

/*:1153*/
  }
  math_type(p) = math_char;
  character(p) = qi(c % 256);
  if ((c >= var_code) && fam_in_range)
    fam(p) = cur_fam;
  else
    fam(p) = (c / 256) % 16;
}

/*:1151*/ /*1155:*/

void set_math_char(int c) {
  pointer p;
  if (c >= 0100000)
/*1152:*/

  {
    cur_cs = cur_chr + active_base;
    cur_cmd = eq_type(cur_cs);
    cur_chr = equiv(cur_cs);
    x_token();
    back_input();
  }
/*:1152*/

  else {
    p = new_noad();
    math_type(nucleus(p)) = math_char;
    character(nucleus(p)) = qi(c % 256);
    fam(nucleus(p)) = (c / 256) % 16;
    if (c >= var_code) {
      if (fam_in_range) fam(nucleus(p)) = cur_fam;
      type(p) = ord_noad;
    } else
      type(p) = ord_noad + (c / 010000);
    link(tail) = p;
    tail = p;
  }
}

/*:1155*/ /*1159:*/

void math_limit_switch(void) {
  if (head != tail)
    if (type(tail) == op_noad) {
      subtype(tail) = cur_chr;
      return;
    }
  print_err("Limit controls must follow a math operator");

  help1("I'm ignoring this misplaced \\limits or \\nolimits command.");
  error();
}

/*:1159*/ /*1160:*/

void scan_delimiter(pointer p, bool r) {
  if (r)
    scan_twenty_seven_bit_int();
  else { /*404:*/

    do {
      get_x_token();
    } while (!((cur_cmd != spacer) && (cur_cmd != relax)))

/*:404*/
        ;
    switch (cur_cmd) {
      case letter:
      case other_char:
        cur_val = del_code(cur_chr);
        break;
      case delim_num:
        scan_twenty_seven_bit_int();
        break;
      default:
        cur_val = -1;
    }
  }
  if (cur_val < 0) /*1161:*/

  {
    print_err("Missing delimiter (. inserted)");

    help6("I was expecting to see something like `(' or `\\{' or")(
        "`\\}' here. If you typed, e.g., `{' instead of `\\{', you")(
        "should probably delete the `{' by typing `1' now, so that")(
        "braces don't get unbalanced. Otherwise just proceed.")(
        "Acceptable delimiters are characters whose \\delcode is")(
        "nonnegative, or you can use `\\delimiter <delimiter code>'.");
    back_error();
    cur_val = 0;
  }

/*:1161*/
  ;
  small_fam(p) = (cur_val / 04000000) % 16;
  small_char(p) = qi((cur_val / 010000) % 256);
  large_fam(p) = (cur_val / 256) % 16;
  large_char(p) = qi(cur_val % 256);
}

/*:1160*/ /*1163:*/

void math_radical(void) {
  tail_append(get_node(radical_noad_size));
  type(tail) = radical_noad;
  subtype(tail) = normal;
  mem[nucleus(tail)].hh = empty_field;
  mem[subscr(tail)].hh = empty_field;
  mem[supscr(tail)].hh = empty_field;
  scan_delimiter(left_delimiter(tail), true);
  scan_math(nucleus(tail));
}

/*:1163*/ /*1165:*/

void math_ac(void) {
  if (cur_cmd == accent)
/*1166:*/

  {
    print_err("Please use ");
    print_esc(/*1545:*/
              420
/*:1545*/
    );
    print_str(" for accents in math mode");

    help2("I'm changing \\accent to \\mathaccent here; wish me luck.")(
        "(Accents are not the same in formulas as they are in text.)");
    error();
  }

/*:1166*/
  ;
  tail_append(get_node(accent_noad_size));
  type(tail) = accent_noad;
  subtype(tail) = normal;
  mem[nucleus(tail)].hh = empty_field;
  mem[subscr(tail)].hh = empty_field;
  mem[supscr(tail)].hh = empty_field;
  math_type(accent_chr(tail)) = math_char;
  scan_fifteen_bit_int();
  character(accent_chr(tail)) = qi(cur_val % 256);
  if ((cur_val >= var_code) && fam_in_range)
    fam(accent_chr(tail)) = cur_fam;
  else
    fam(accent_chr(tail)) = (cur_val / 256) % 16;
  scan_math(nucleus(tail));
}

/*:1165*/ /*1172:*/

void append_choices(void) {
  tail_append(new_choice());
  incr(save_ptr);
  saved(-1) = 0;
  push_math(math_choice_group);
  scan_left_brace();
}

/*:1172*/ /*1174:*/

/*1184:*/

pointer fin_mlist(pointer p) {
  pointer q;
  if (incompleat_noad != null) /*1185:*/

  {
    math_type(denominator(incompleat_noad)) = sub_mlist;
    info(denominator(incompleat_noad)) = link(head);
    if (p == null)
      q = incompleat_noad;
    else {
      q = info(numerator(incompleat_noad));
      if (type(q) != left_noad)
        confusion(/*1660:*/
                  535
/*:1660*/
        );

      info(numerator(incompleat_noad)) = link(q);
      link(q) = incompleat_noad;
      link(incompleat_noad) = p;
    }
  }
/*:1185*/

  else {
    link(tail) = p;
    q = link(head);
  }
  pop_nest();
  return q;
}

/*:1184*/

void build_choices(void) {
  pointer p;
  unsave();
  p = fin_mlist(null);
  switch (saved(-1)) {
    case 0:
      display_mlist(tail) = p;
      break;
    case 1:
      text_mlist(tail) = p;
      break;
    case 2:
      script_mlist(tail) = p;
      break;
    case 3: {
      script_script_mlist(tail) = p;
      decr(save_ptr);
      return;
    }
  }
  incr(saved(-1));
  push_math(math_choice_group);
  scan_left_brace();
}

/*:1174*/ /*1176:*/

void sub_sup(void) {
  small_number t;
  pointer p;
  t = empty;
  p = null;
  if (tail != head)
    if (scripts_allowed(tail)) {
      p = supscr(tail) + cur_cmd - sup_mark;
      t = math_type(p);
    }
  if ((p == null) || (t != empty)) /*1177:*/

  {
    tail_append(new_noad());
    p = supscr(tail) + cur_cmd - sup_mark;
    if (t != empty) {
      if (cur_cmd == sup_mark) {
        print_err("Double superscript");

        help1("I treat `x^1^2' essentially like `x^1{}^2'.");
      } else {
        print_err("Double subscript");

        help1("I treat `x_1_2' essentially like `x_1{}_2'.");
      }
      error();
    }
  }

/*:1177*/
  ;
  scan_math(p);
}

/*:1176*/ /*1181:*/

void math_fraction(void) {
  small_number c;
  c = cur_chr;
  if (incompleat_noad != null)
/*1183:*/

  {
    if (c >= delimited_code) {
      scan_delimiter(garbage, false);
      scan_delimiter(garbage, false);
    }
    if (c % delimited_code == above_code) scan_normal_dimen;
    print_err("Ambiguous; you need another { and }");

    help3("I'm ignoring this fraction specification, since I don't")(
        "know whether a construction like `x \\over y \\over z'")(
        "means `{x \\over y} \\over z' or `x \\over {y \\over z}'.");
    error();
  }
/*:1183*/

  else {
    incompleat_noad = get_node(fraction_noad_size);
    type(incompleat_noad) = fraction_noad;
    subtype(incompleat_noad) = normal;
    math_type(numerator(incompleat_noad)) = sub_mlist;
    info(numerator(incompleat_noad)) = link(head);
    mem[denominator(incompleat_noad)].hh = empty_field;
    mem[left_delimiter(incompleat_noad)].qqqq = null_delimiter;
    mem[right_delimiter(incompleat_noad)].qqqq = null_delimiter;
    link(head) = null;
    tail = head;
/*1182:*/

    if (c >= delimited_code) {
      scan_delimiter(left_delimiter(incompleat_noad), false);
      scan_delimiter(right_delimiter(incompleat_noad), false);
    }
    switch (c % delimited_code) {
      case above_code: {
        scan_normal_dimen;
        thickness(incompleat_noad) = cur_val;
      } break;
      case over_code:
        thickness(incompleat_noad) = default_code;
        break;
      case atop_code:
        thickness(incompleat_noad) = 0;
    }

/*:1182*/
    ;
  }
}

/*:1181*/ /*1191:*/

void math_left_right(void) {
  small_number t;
  pointer p;
  t = cur_chr;
  if ((t == right_noad) && (cur_group != math_left_group))
/*1192:*/

  {
    if (cur_group == math_shift_group) {
      scan_delimiter(garbage, false);
      print_err("Extra ");
      print_esc(/*1660:*/
                535
/*:1660*/
      );

      help1("I'm ignoring a \\right that had no matching \\left.");
      error();
    } else
      off_save();
  }
/*:1192*/

  else {
    p = new_noad();
    type(p) = t;
    scan_delimiter(delimiter(p), false);
    if (t == left_noad) {
      push_math(math_left_group);
      link(head) = p;
      tail = p;
    } else {
      p = fin_mlist(p);
      unsave();
      tail_append(new_noad());
      type(tail) = inner_noad;
      math_type(nucleus(tail)) = sub_mlist;
      info(nucleus(tail)) = p;
    }
  }
}

/*:1191*/ /*1194:*/

void after_math(void) {
  bool l;
  bool danger;
  int m;
  pointer p;
  pointer a;
/*1198:*/

  pointer b;
  scaled w;
  scaled z;
  scaled e;
  scaled q;
  scaled d;
  scaled s;
  small_number g1, g2;
  pointer r;
  pointer t;

/*:1198*/

  danger = false;
/*1195:*/

  if ((font_params[fam_fnt(2 + text_size)] < total_mathsy_params) ||
      (font_params[fam_fnt(2 + script_size)] < total_mathsy_params) ||
      (font_params[fam_fnt(2 + script_script_size)] < total_mathsy_params)) {
    print_err("Math formula deleted: Insufficient symbol fonts");

    help3("Sorry, but I can't typeset math unless \\textfont 2")(
        "and \\scriptfont 2 and \\scriptscriptfont 2 have all")(
        "the \\fontdimen values needed in math symbol fonts.");
    error();
    flush_math();
    danger = true;
  } else if ((font_params[fam_fnt(3 + text_size)] < total_mathex_params) ||
             (font_params[fam_fnt(3 + script_size)] < total_mathex_params) ||
             (font_params[fam_fnt(3 + script_script_size)] <
              total_mathex_params)) {
    print_err("Math formula deleted: Insufficient extension fonts");
    help3("Sorry, but I can't typeset math unless \\textfont 3")(
        "and \\scriptfont 3 and \\scriptscriptfont 3 have all")(
        "the \\fontdimen values needed in math extension fonts.");
    error();
    flush_math();
    danger = true;
  }

/*:1195*/
  ;
  m = mode;
  l = false;
  p = fin_mlist(null);
  if (mode == -m) { /*1197:*/

    {
      get_x_token();
      if (cur_cmd != math_shift) {
        print_err("Display math should end with $$");

        help2("The `$' that I just saw supposedly matches a previous `$$'.")(
            "So I shall assume that you typed `$$' both times.");
        back_error();
      }
    }

/*:1197*/
    ;
    cur_mlist = p;
    cur_style = text_style;
    mlist_penalties = false;
    mlist_to_hlist();
    a = hpack(link(temp_head), natural);
    unsave();
    decr(save_ptr);
    if (saved(0) == 1) l = true;
    danger = false;
/*1195:*/

    if ((font_params[fam_fnt(2 + text_size)] < total_mathsy_params) ||
        (font_params[fam_fnt(2 + script_size)] < total_mathsy_params) ||
        (font_params[fam_fnt(2 + script_script_size)] < total_mathsy_params)) {
      print_err("Math formula deleted: Insufficient symbol fonts");

      help3("Sorry, but I can't typeset math unless \\textfont 2")(
          "and \\scriptfont 2 and \\scriptscriptfont 2 have all")(
          "the \\fontdimen values needed in math symbol fonts.");
      error();
      flush_math();
      danger = true;
    } else if ((font_params[fam_fnt(3 + text_size)] < total_mathex_params) ||
               (font_params[fam_fnt(3 + script_size)] < total_mathex_params) ||
               (font_params[fam_fnt(3 + script_script_size)] <
                total_mathex_params)) {
      print_err("Math formula deleted: Insufficient extension fonts");
      help3("Sorry, but I can't typeset math unless \\textfont 3")(
          "and \\scriptfont 3 and \\scriptscriptfont 3 have all")(
          "the \\fontdimen values needed in math extension fonts.");
      error();
      flush_math();
      danger = true;
    }

/*:1195*/
    ;
    m = mode;
    p = fin_mlist(null);
  } else
    a = null;
  if (m < 0) /*1196:*/

  {
    tail_append(new_math(math_surround, before));
    cur_mlist = p;
    cur_style = text_style;
    mlist_penalties = (mode > 0);
    mlist_to_hlist();
    link(tail) = link(temp_head);
    while (link(tail) != null) tail = link(tail);
    tail_append(new_math(math_surround, after));
    space_factor = 1000;
    unsave();
  }
/*:1196*/

  else {
    if (a == null) /*1197:*/

    {
      get_x_token();
      if (cur_cmd != math_shift) {
        print_err("Display math should end with $$");

        help2("The `$' that I just saw supposedly matches a previous `$$'.")(
            "So I shall assume that you typed `$$' both times.");
        back_error();
      }
    }

/*:1197*/
    ;
/*1199:*/

    cur_mlist = p;
    cur_style = display_style;
    mlist_penalties = false;
    mlist_to_hlist();
    p = link(temp_head);
    adjust_tail = adjust_head;
    b = hpack(p, natural);
    p = list_ptr(b);
    t = adjust_tail;
    adjust_tail = null;
    w = width(b);
    z = display_width;
    s = display_indent;
    if ((a == null) || danger) {
      e = 0;
      q = 0;
    } else {
      e = width(a);
      q = e + math_quad(text_size);
    }
    if (w + q > z)
/*1201:*/

    {
      if ((e != 0) &&
          ((w - total_shrink[normal] + q <= z) || (total_shrink[fil] != 0) ||
           (total_shrink[fill] != 0) || (total_shrink[filll] != 0))) {
        free_node(b, box_node_size);
        b = hpack(p, z - q, exactly);
      } else {
        e = 0;
        if (w > z) {
          free_node(b, box_node_size);
          b = hpack(p, z, exactly);
        }
      }
      w = width(b);
    }

/*:1201*/
    ;
/*1202:*/

    d = half(z - w);
    if ((e > 0) && (d < 2 * e)) {
      d = half(z - w - e);
      if (p != null)
        if (!is_char_node(p))
          if (type(p) == glue_node) d = 0;
    }

/*:1202*/
    ;
/*1203:*/

    tail_append(new_penalty(pre_display_penalty));
    if ((d + s <= pre_display_size) || l) {
      g1 = above_display_skip_code;
      g2 = below_display_skip_code;
    } else {
      g1 = above_display_short_skip_code;
      g2 = below_display_short_skip_code;
    }
    if (l && (e == 0)) {
      shift_amount(a) = s;
      append_to_vlist(a);
      tail_append(new_penalty(inf_penalty));
    } else
      tail_append(new_param_glue(g1))

/*:1203*/
          ;
/*1204:*/

    if (e != 0) {
      r = new_kern(z - w - e - d);
      if (l) {
        link(a) = r;
        link(r) = b;
        b = a;
        d = 0;
      } else {
        link(b) = r;
        link(r) = a;
      }
      b = hpack(b, natural);
    }
    shift_amount(b) = s + d;
    append_to_vlist(b)

/*:1204*/
        ;
/*1205:*/

    if ((a != null) && (e == 0) && !l) {
      tail_append(new_penalty(inf_penalty));
      shift_amount(a) = s + z - width(a);
      append_to_vlist(a);
      g2 = 0;
    }
    if (t != adjust_head) {
      link(tail) = link(adjust_head);
      tail = t;
    }
    tail_append(new_penalty(post_display_penalty));
    if (g2 > 0)
      tail_append(new_param_glue(g2))

/*:1205*/
          ;
    resume_after_display()

/*:1199*/
        ;
  }
}

/*:1194*/ /*1200:*/

void resume_after_display(void) {
  if (cur_group != math_shift_group)
    confusion(/*1742:*/
              617
/*:1742*/
    );

  unsave();
  prev_graf = prev_graf + 3;
  push_nest();
  mode = hmode;
  space_factor = 1000;
  set_cur_lang;
  clang = cur_lang;
  prev_graf = (norm_min(left_hyphen_min) * 0100 + norm_min(right_hyphen_min)) *
                  0200000 +
              cur_lang;
/*443:*/

  {
    get_x_token();
    if (cur_cmd != spacer) back_input();
  }

/*:443*/
  ;
  if (nest_ptr == 1) build_page();
}

/*:1200*/ /*1211:*/

/*1215:*/

void get_r_token(void) {
restart:
  do {
    get_token();
  } while (!(cur_tok != space_token));
  if ((cur_cs == 0) || (cur_cs > frozen_control_sequence)) {
    print_err("Missing control sequence inserted");

    help5("Please don't say `\\def cs{...}', say `\\def\\cs{...}'.")(
        "I've inserted an inaccessible control sequence so that your")(
        "definition will be completed without mixing me up too badly.")(
        "You can recover graciously from this error, if you're")(
        "careful; see exercise 27.2 in The TeXbook.");

    if (cur_cs == 0) back_input();
    cur_tok = cs_token_flag + frozen_protection;
    ins_error();
    goto restart;
  }
}

/*:1215*/ /*1229:*/

void trap_zero_glue(void) {
  if ((width(cur_val) == 0) && (stretch(cur_val) == 0) &&
      (shrink(cur_val) == 0)) {
    add_glue_ref(zero_glue);
    delete_glue_ref(cur_val);
    cur_val = zero_glue;
  }
}

/*:1229*/ /*1236:*/

void do_register_command(small_number a) {
  pointer l, q, r, s;
  uint8_t p;
  q = cur_cmd;
/*1237:*/

  {
    if (q != register) {
      get_x_token();
      if ((cur_cmd >= assign_int) && (cur_cmd <= assign_mu_glue)) {
        l = cur_chr;
        p = cur_cmd - assign_int;
        goto found;
      }
      if (cur_cmd != register) {
        print_err("You can't use `");
        print_cmd_chr(cur_cmd, cur_chr);

        print_str("' after ");
        print_cmd_chr(q, 0);
        help1("I'm forgetting what you said and not changing anything.");
        error();
        return;
      }
    }
    p = cur_chr;
    scan_eight_bit_int();
    switch (p) {
      case int_val:
        l = cur_val + count_base;
        break;
      case dimen_val:
        l = cur_val + scaled_base;
        break;
      case glue_val:
        l = cur_val + skip_base;
        break;
      case mu_val:
        l = cur_val + mu_skip_base;
    }
  }
found:

/*:1237*/
    ;
  if (q == register)
    scan_optional_equals();
  else if (scan_keyword(/*1761:*/
                        636
/*:1761*/
                        ))
    do_nothing;

  arith_error = false;
  if (q < multiply) /*1238:*/

    if (p < glue_val) {
      if (p == int_val)
        scan_int();
      else
        scan_normal_dimen;
      if (q == advance) cur_val = cur_val + eqtb[l].i;
    } else {
      scan_glue(p);
      if (q == advance) /*1239:*/

      {
        q = new_spec(cur_val);
        r = equiv(l);
        delete_glue_ref(cur_val);
        width(q) = width(q) + width(r);
        if (stretch(q) == 0) stretch_order(q) = normal;
        if (stretch_order(q) == stretch_order(r))
          stretch(q) = stretch(q) + stretch(r);
        else if ((stretch_order(q) < stretch_order(r)) && (stretch(r) != 0)) {
          stretch(q) = stretch(r);
          stretch_order(q) = stretch_order(r);
        }
        if (shrink(q) == 0) shrink_order(q) = normal;
        if (shrink_order(q) == shrink_order(r))
          shrink(q) = shrink(q) + shrink(r);
        else if ((shrink_order(q) < shrink_order(r)) && (shrink(r) != 0)) {
          shrink(q) = shrink(r);
          shrink_order(q) = shrink_order(r);
        }
        cur_val = q;
      }

/*:1239*/
      ;
    }

/*:1238*/

  else /*1240:*/

  {
    scan_int();
    if (p < glue_val)
      if (q == multiply)
        if (p == int_val)
          cur_val = mult_integers(eqtb[l].i, cur_val);
        else
          cur_val = nx_plus_y(eqtb[l].i, cur_val, 0);
      else
        cur_val = x_over_n(eqtb[l].i, cur_val);
    else {
      s = equiv(l);
      r = new_spec(s);
      if (q == multiply) {
        width(r) = nx_plus_y(width(s), cur_val, 0);
        stretch(r) = nx_plus_y(stretch(s), cur_val, 0);
        shrink(r) = nx_plus_y(shrink(s), cur_val, 0);
      } else {
        width(r) = x_over_n(width(s), cur_val);
        stretch(r) = x_over_n(stretch(s), cur_val);
        shrink(r) = x_over_n(shrink(s), cur_val);
      }
      cur_val = r;
    }
  }

/*:1240*/
  ;
  if (arith_error) {
    print_err("Arithmetic overflow");

    help2("I can't carry out that multiplication or division,")(
        "since the result is out of range.");
    if (p >= glue_val) delete_glue_ref(cur_val);
    error();
    return;
  }
  if (p < glue_val)
    word_define(l, cur_val);
  else {
    trap_zero_glue();
    define(l, glue_ref, cur_val);
  }
}

/*:1236*/ /*1243:*/

void alter_aux(void) {
  halfword c;
  if (cur_chr != abs(mode))
    report_illegal_case();
  else {
    c = cur_chr;
    scan_optional_equals();
    if (c == vmode) {
      scan_normal_dimen;
      prev_depth = cur_val;
    } else {
      scan_int();
      if ((cur_val <= 0) || (cur_val > 32767)) {
        print_err("Bad space factor");

        help1("I allow only values in the range 1..32767 here.");
        int_error(cur_val);
      } else
        space_factor = cur_val;
    }
  }
}

/*:1243*/ /*1244:*/

void alter_prev_graf(void) {
  uint8_t p;
  nest[nest_ptr] = cur_list;
  p = nest_ptr;
  while (abs(nest[p].mode_field) != vmode) decr(p);
  scan_optional_equals();
  scan_int();
  if (cur_val < 0) {
    print_err("Bad ");
    print_esc(/*1554:*/
              429
/*:1554*/
    );

    help1("I allow only nonnegative values here.");
    int_error(cur_val);
  } else {
    nest[p].pg_field = cur_val;
    cur_list = nest[nest_ptr];
  }
}

/*:1244*/ /*1245:*/

void alter_page_so_far(void) {
  uint8_t c;
  c = cur_chr;
  scan_optional_equals();
  scan_normal_dimen;
  page_so_far[c] = cur_val;
}

/*:1245*/ /*1246:*/

void alter_integer(void) {
  uint8_t c;
  c = cur_chr;
  scan_optional_equals();
  scan_int();
  if (c == 0)
    dead_cycles = cur_val;
  else
    insert_penalties = cur_val;
}

/*:1246*/ /*1247:*/

void alter_box_dimen(void) {
  small_number c;
  eight_bits b;
  c = cur_chr;
  scan_eight_bit_int();
  b = cur_val;
  scan_optional_equals();
  scan_normal_dimen;
  if (box(b) != null) mem[box(b) + c].sc = cur_val;
}

/*:1247*/ /*1257:*/

void new_font(small_number a) {
  pointer u;
  scaled s;
  int f;
  str_number t;
  uint8_t old_setting;
  str_number flushable_string;
  if (job_name == 0) open_log_file();

  get_r_token();
  u = cur_cs;
  if (u >= hash_base)
    t = text(u);
  else if (u >= single_base)
    if (u == null_cs)
      t = /*1764:*/
          639
/*:1764*/
          ;
    else
      t = u - single_base;
  else {
    old_setting = selector;
    selector = new_string;
    print_str("FONT");
    print(u - active_base);
    selector = old_setting;

    str_room(1);
    t = make_string();
  }
  define(u, set_font, null_font);
  scan_optional_equals();
  scan_file_name();
/*1258:*/

  name_in_progress = true;
  if (scan_keyword(/*1765:*/
                   640
/*:1765*/
                   )) /*1259:*/

  {
    scan_normal_dimen;
    s = cur_val;
    if ((s <= 0) || (s >= 01000000000)) {
      print_err("Improper `at' size (");
      print_scaled(s);
      print_str("pt), replaced by 10pt");

      help2("I can only handle fonts at positive sizes that are")(
          "less than 2048pt, so I've changed what you said to 10pt.");
      error();
      s = 10 * unity;
    }
  }
/*:1259*/

  else if (scan_keyword(/*1766:*/
                        641
/*:1766*/
                        ))

  {
    scan_int();
    s = -cur_val;
    if ((cur_val <= 0) || (cur_val > 32768)) {
      print_err("Illegal magnification has been changed to 1000");

      help1("The magnification ratio must be between 1 and 32768.");
      int_error(cur_val);
      s = -1000;
    }
  } else
    s = -1000;
  name_in_progress = false

/*:1258*/
      ;
/*1260:*/

  flushable_string = str_ptr - 1;
  for (f = font_base + 1; f <= font_ptr; f++)
    if (str_eq_str(font_name[f], cur_name) &&
        str_eq_str(font_area[f], cur_area)) {
      if (cur_name == flushable_string) {
        flush_string;
        cur_name = font_name[f];
      }
      if (s > 0) {
        if (s == font_size[f]) goto common_ending;
      } else if (font_size[f] == xn_over_d(font_dsize[f], -s, 1000))
        goto common_ending;
    }

/*:1260*/
    ;
  f = read_font_info(u, cur_name, cur_area, s);
common_ending:
  equiv(u) = f;
  eqtb[font_id_base + f] = eqtb[u];
  font_id_text(f) = t;
}

/*:1257*/ /*1265:*/

void new_interaction(void) {
  print_ln();
  interaction = cur_chr;
/*75:*/

  if (interaction == batch_mode)
    selector = no_print;
  else
    selector = term_only

/*:75*/
        ;
  if (log_opened) selector = selector + 2;
}

/*:1265*/

void prefixed_command(void) {
  small_number a;
  internal_font_number f;
  int j;
  font_index k;
  pointer p, q;
  int n;
  bool e;
  a = 0;
  while (cur_cmd == prefix) {
    if (!odd(a / cur_chr)) a = a + cur_chr;
/*404:*/

    do {
      get_x_token();
    } while (!((cur_cmd != spacer) && (cur_cmd != relax)))

/*:404*/
        ;
    if (cur_cmd <= max_non_prefixed_command)
/*1212:*/

    {
      print_err("You can't use a prefix with `");

      print_cmd_chr(cur_cmd, cur_chr);
      print_char('\'');
      help1("I'll pretend you didn't say \\long or \\outer or \\global.");
      back_error();
      return;
    }

/*:1212*/
    ;
  }
/*1213:*/

  if ((cur_cmd != def) && (a % 4 != 0)) {
    print_err("You can't use `");
    print_esc(/*1743:*/
              618
/*:1743*/
    );
    print_str("' or `");
    print_esc(/*1744:*/
              619
/*:1744*/
    );
    print_str("' with `");

    print_cmd_chr(cur_cmd, cur_chr);
    print_char('\'');
    help1("I'll pretend you didn't say \\long or \\outer here.");
    error();
  }

/*:1213*/
  ;
/*1214:*/

  if (global_defs != 0)
    if (global_defs < 0) {
      if (global) a = a - 4;
    } else {
      if (!global) a = a + 4;
    }

/*:1214*/
    ;
  switch (cur_cmd) {
/*1217:*/

    case set_font:
      define(cur_font_loc, data, cur_chr);
      break;

/*:1217*/ /*1218:*/

    case def: {
      if (odd(cur_chr) && !global && (global_defs >= 0)) a = a + 4;
      e = (cur_chr >= 2);
      get_r_token();
      p = cur_cs;
      q = scan_toks(true, e);
      define(p, call + (a % 4), def_ref);
    } break;

/*:1218*/ /*1221:*/

    case let: {
      n = cur_chr;
      get_r_token();
      p = cur_cs;
      if (n == normal) {
        do {
          get_token();
        } while (!(cur_cmd != spacer));
        if (cur_tok == other_token + '=') {
          get_token();
          if (cur_cmd == spacer) get_token();
        }
      } else {
        get_token();
        q = cur_tok;
        get_token();
        back_input();
        cur_tok = q;
        back_input();
      }
      if (cur_cmd >= call) add_token_ref(cur_chr);
      define(p, cur_cmd, cur_chr);
    } break;

/*:1221*/ /*1224:*/

    case shorthand_def: {
      n = cur_chr;
      get_r_token();
      p = cur_cs;
      define(p, relax, 256);
      scan_optional_equals();
      switch (n) {
        case char_def_code: {
          scan_char_num();
          define(p, char_given, cur_val);
        } break;
        case math_char_def_code: {
          scan_fifteen_bit_int();
          define(p, math_given, cur_val);
        } break;
        default: {
          scan_eight_bit_int();
          switch (n) {
            case count_def_code:
              define(p, assign_int, count_base + cur_val);
              break;
            case dimen_def_code:
              define(p, assign_dimen, scaled_base + cur_val);
              break;
            case skip_def_code:
              define(p, assign_glue, skip_base + cur_val);
              break;
            case mu_skip_def_code:
              define(p, assign_mu_glue, mu_skip_base + cur_val);
              break;
            case toks_def_code:
              define(p, assign_toks, toks_base + cur_val);
          }
        }
      }
    } break;

/*:1224*/ /*1225:*/

    case read_to_cs: {
      scan_int();
      n = cur_val;
      if (!scan_keyword(/*1642:*/
                        517
/*:1642*/
                        ))

      {
        print_err("Missing `to' inserted");

        help2("You should have said `\\read<number> to \\cs'.")(
            "I'm going to look for the \\cs now.");
        error();
      }
      get_r_token();
      p = cur_cs;
      read_toks(n, p);
      define(p, call, cur_val);
    } break;

/*:1225*/ /*1226:*/

    case toks_register:
    case assign_toks: {
      q = cur_cs;
      if (cur_cmd == toks_register) {
        scan_eight_bit_int();
        p = toks_base + cur_val;
      } else
        p = cur_chr;
      scan_optional_equals();
/*404:*/

      do {
        get_x_token();
      } while (!((cur_cmd != spacer) && (cur_cmd != relax)))

/*:404*/
          ;
      if (cur_cmd != left_brace) /*1227:*/

      {
        if (cur_cmd == toks_register) {
          scan_eight_bit_int();
          cur_cmd = assign_toks;
          cur_chr = toks_base + cur_val;
        }
        if (cur_cmd == assign_toks) {
          q = equiv(cur_chr);
          if (q == null)
            define(p, undefined_cs, null);
          else {
            add_token_ref(q);
            define(p, call, q);
          }
          goto done;
        }
      }

/*:1227*/
      ;
      back_input();
      cur_cs = q;
      q = scan_toks(false, false);
      if (link(def_ref) == null) {
        define(p, undefined_cs, null);
        free_avail(def_ref);
      } else {
        if (p == output_routine_loc) {
          link(q) = get_avail();
          q = link(q);
          info(q) = right_brace_token + '}';
          q = get_avail();
          info(q) = left_brace_token + '{';
          link(q) = link(def_ref);
          link(def_ref) = q;
        }
        define(p, call, def_ref);
      }
    } break;

/*:1226*/ /*1228:*/

    case assign_int: {
      p = cur_chr;
      scan_optional_equals();
      scan_int();
      word_define(p, cur_val);
    } break;
    case assign_dimen: {
      p = cur_chr;
      scan_optional_equals();
      scan_normal_dimen;
      word_define(p, cur_val);
    } break;
    case assign_glue:
    case assign_mu_glue: {
      p = cur_chr;
      n = cur_cmd;
      scan_optional_equals();
      if (n == assign_mu_glue)
        scan_glue(mu_val);
      else
        scan_glue(glue_val);
      trap_zero_glue();
      define(p, glue_ref, cur_val);
    } break;

/*:1228*/ /*1232:*/

    case def_code: { /*1233:*/

      if (cur_chr == cat_code_base)
        n = max_char_code;
      else if (cur_chr == math_code_base)
        n = 0100000;
      else if (cur_chr == sf_code_base)
        n = 077777;
      else if (cur_chr == del_code_base)
        n = 077777777;
      else
        n = 255

/*:1233*/
            ;
      p = cur_chr;
      scan_char_num();
      p = p + cur_val;
      scan_optional_equals();
      scan_int();
      if (((cur_val < 0) && (p < del_code_base)) || (cur_val > n)) {
        print_err("Invalid code (");
        print_int(cur_val);

        if (p < del_code_base)
          print_str("), should be in the range 0..");
        else
          print_str("), should be at most ");
        print_int(n);
        help1("I'm going to use 0 instead of that illegal code value.");
        error();
        cur_val = 0;
      }
      if (p < math_code_base)
        define(p, data, cur_val);
      else if (p < del_code_base)
        define(p, data, hi(cur_val));
      else
        word_define(p, cur_val);
    } break;

/*:1232*/ /*1234:*/

    case def_family: {
      p = cur_chr;
      scan_four_bit_int();
      p = p + cur_val;
      scan_optional_equals();
      scan_font_ident();
      define(p, data, cur_val);
    } break;

/*:1234*/ /*1235:*/

    case register:
    case advance:
    case multiply:
    case divide:
      do_register_command(a);
      break;

/*:1235*/ /*1241:*/

    case set_box: {
      scan_eight_bit_int();
      if (global)
        n = 256 + cur_val;
      else
        n = cur_val;
      scan_optional_equals();
      if (set_box_allowed)
        scan_box(box_flag + n);
      else {
        print_err("Improper ");
        print_esc(/*1558:*/
                  433
/*:1558*/
        );

        help2("Sorry, \\setbox is not allowed after \\halign in a display,")(
            "or between \\accent and an accented character.");
        error();
      }
    } break;

/*:1241*/ /*1242:*/

    case set_aux:
      alter_aux();
      break;
    case set_prev_graf:
      alter_prev_graf();
      break;
    case set_page_dimen:
      alter_page_so_far();
      break;
    case set_page_int:
      alter_integer();
      break;
    case set_box_dimen:
      alter_box_dimen();
      break;

/*:1242*/ /*1248:*/

    case set_shape: {
      scan_optional_equals();
      scan_int();
      n = cur_val;
      if (n <= 0)
        p = null;
      else {
        p = get_node(2 * n + 1);
        info(p) = n;
        for (j = 1; j <= n; j++) {
          scan_normal_dimen;
          mem[p + 2 * j - 1].sc = cur_val;
          scan_normal_dimen;
          mem[p + 2 * j].sc = cur_val;
        }
      }
      define(par_shape_loc, shape_ref, p);
    } break;

/*:1248*/ /*1252:*/

    case hyph_data:
      if (cur_chr == 1) {
#ifdef INIT
        new_patterns();
        goto done;
#endif
        print_err("Patterns can be loaded only by INITEX");

        help0;
        error();
        do {
          get_token();
        } while (!(cur_cmd == right_brace));
        return;
      } else {
        new_hyph_exceptions();
        goto done;
      }
      break;

/*:1252*/ /*1253:*/

    case assign_font_dimen: {
      find_font_dimen(true);
      k = cur_val;
      scan_optional_equals();
      scan_normal_dimen;
      font_info[k].sc = cur_val;
    } break;
    case assign_font_int: {
      n = cur_chr;
      scan_font_ident();
      f = cur_val;
      scan_optional_equals();
      scan_int();
      if (n == 0)
        hyphen_char[f] = cur_val;
      else
        skew_char[f] = cur_val;
    } break;

/*:1253*/ /*1256:*/

    case def_font:
      new_font(a);
      break;

/*:1256*/ /*1264:*/

    case set_interaction:
      new_interaction();
      break;

/*:1264*/

    default:
      confusion(/*1750:*/
                625
/*:1750*/
      );
  }
done: /*1269:*/

  if (after_token != 0) {
    cur_tok = after_token;
    back_input();
    after_token = 0;
  }

/*:1269*/
  ;
}

/*:1211*/ /*1270:*/

void do_assignments(void) {
  loop { /*404:*/

    do {
      get_x_token();
    } while (!((cur_cmd != spacer) && (cur_cmd != relax)))

/*:404*/
        ;
    if (cur_cmd <= max_non_prefixed_command) return;
    set_box_allowed = false;
    prefixed_command();
    set_box_allowed = true;
  }
}

/*:1270*/ /*1275:*/

void open_or_close_in(void) {
  uint8_t c;
  uint8_t n;
  c = cur_chr;
  scan_four_bit_int();
  n = cur_val;
  if (read_open[n] != closed) {
    a_close(&read_file[n]);
    read_open[n] = closed;
  }
  if (c != 0) {
    scan_optional_equals();
    scan_file_name();
    if (cur_ext == empty_string)
      cur_ext = /*1637:*/
          512
/*:1637*/
          ;
    pack_cur_name;
    if (a_open_in(&read_file[n])) read_open[n] = just_open;
  }
}

/*:1275*/ /*1279:*/

void issue_message(void) {
  uint8_t old_setting;
  uint8_t c;
  str_number s;
  c = cur_chr;
  link(garbage) = scan_toks(false, true);
  old_setting = selector;
  selector = new_string;
  token_show(def_ref);
  selector = old_setting;
  flush_list(def_ref);
  str_room(1);
  s = make_string();
  if (c == 0) /*1280:*/

  {
    if (term_offset + length(s) > max_print_line - 2)
      print_ln();
    else if ((term_offset > 0) || (file_offset > 0))
      print_char(' ');
    slow_print(s);
    update_terminal;
  }
/*:1280*/

  else /*1283:*/

  {
    print_err("");
    slow_print(s);
    if (err_help != null)
      use_err_help = true;
    else if (long_help_seen)
      help1("(That was another \\errmessage.)") else {
        if (interaction < error_stop_mode) long_help_seen = true;
        help4("This error message was generated by an \\errmessage")(
            "command, so I can't give any explicit help.")(
            "Pretend that you're Hercule Poirot: Examine all clues,")

            ("and deduce the truth by order and method.");
      }
    error();
    use_err_help = false;
  }

/*:1283*/
  ;
  flush_string;
}

/*:1279*/ /*1288:*/

void shift_case(void) {
  pointer b;
  pointer p;
  halfword t;
  eight_bits c;
  b = cur_chr;
  p = scan_toks(false, false);
  p = link(def_ref);
  while (p != null) { /*1289:*/

    t = info(p);
    if (t < cs_token_flag + single_base) {
      c = t % 256;
      if (equiv(b + c) != 0) info(p) = t - c + equiv(b + c);
    }

/*:1289*/
    ;
    p = link(p);
  }
  back_list(link(def_ref));
  free_avail(def_ref);
}

/*:1288*/ /*1293:*/

void show_whatever(void) {
  pointer p;
  switch (cur_chr) {
    case show_lists_code: {
      begin_diagnostic();
      show_activities();
    } break;
    case show_box_code: /*1296:*/

    {
      scan_eight_bit_int();
      begin_diagnostic();
      print_nl("> \\box");
      print_int(cur_val);
      print_char('=');
      if (box(cur_val) == null)
        print_str("void");
      else
        show_box(box(cur_val));
    }

/*:1296*/
    break;
    case show_code: /*1294:*/

    {
      get_token();
      if (interaction == error_stop_mode) wake_up_terminal;
      print_nl("> ");
      if (cur_cs != 0) {
        sprint_cs(cur_cs);
        print_char('=');
      }
      print_meaning();
      goto common_ending;
    }

/*:1294*/

    default: /*1297:*/

    {
      p = the_toks();
      if (interaction == error_stop_mode) wake_up_terminal;
      print_nl("> ");
      token_show(temp_head);
      flush_list(link(temp_head));
      goto common_ending;
    }

/*:1297*/
  }
/*1298:*/

  end_diagnostic(true);
  print_err("OK");

  if (selector == term_and_log)
    if (tracing_online <= 0) {
      selector = term_only;
      print_str(" (see the transcript file)");
      selector = term_and_log;
    }

/*:1298*/
    ;
common_ending:
  if (interaction < error_stop_mode) {
    help0;
    decr(error_count);
  } else if (tracing_online > 0) {
    help3("This isn't an error message; I'm just \\showing something.")(
        "Type `I\\show...' to show more (e.g., \\show\\cs,")(
        "\\showthe\\count10, \\showbox255, \\showlists).");
  } else {
    help5("This isn't an error message; I'm just \\showing something.")(
        "Type `I\\show...' to show more (e.g., \\show\\cs,")(
        "\\showthe\\count10, \\showbox255, \\showlists).")(
        "And type `I\\tracingonline=1\\show...' to show boxes and")(
        "lists on your terminal as well as in the transcript file.");
  }
  error();
}

/*:1293*/ /*1302:*/

#ifdef INIT
void store_fmt_file(void) {
  int j, k, l;
  pointer p, q;
  int x;
  four_quarters w;
/*1304:*/

  if (save_ptr != 0) {
    print_err("You can't dump inside a group");

    help1("`{...\\dump}' is a no-no.");
    succumb;
  }

/*:1304*/
  ;
/*1328:*/

  selector = new_string;
  print_str(" (preloaded format=");
  print(job_name);
  print_char(' ');
  print_int(year);
  print_char('.');
  print_int(month);
  print_char('.');
  print_int(day);
  print_char(')');
  if (interaction == batch_mode)
    selector = log_only;
  else
    selector = term_and_log;
  str_room(1);
  format_ident = make_string();
  pack_job_name(format_extension);
  while (!w_open_out(&fmt_file))
    prompt_file_name("format file name", format_extension);
  print_nl("Beginning to dump on file ");

  slow_print(w_make_name_string(&fmt_file));
  flush_string;
  print_nl("");
  slow_print(format_ident)

/*:1328*/
      ;
/*1307:*/

  dump_int(0);
  dump_int(mem_bot);
  dump_int(mem_top);
  dump_int(eqtb_size);
  dump_int(hash_prime);
  dump_int(hyph_size)

/*:1307*/
      ;
/*1309:*/

  dump_int(pool_ptr);
  dump_int(str_ptr);
  for (k = 0; k <= str_ptr; k++) dump_int(str_start[k]);
  k = 0;
  while (k + 4 < pool_ptr) {
    dump_four_ASCII;
    k = k + 4;
  }
  k = pool_ptr - 4;
  dump_four_ASCII;
  print_ln();
  print_int(str_ptr);
  print_str(" strings of total length ");
  print_int(pool_ptr)

/*:1309*/
      ;
/*1311:*/

  sort_avail();
  var_used = 0;
  dump_int(lo_mem_max);
  dump_int(rover);
  p = mem_bot;
  q = rover;
  x = 0;
  do {
    for (k = p; k <= q + 1; k++) dump_wd(mem[k]);
    x = x + q + 2 - p;
    var_used = var_used + q - p;
    p = q + node_size(q);
    q = rlink(q);
  } while (!(q == rover));
  var_used = var_used + lo_mem_max - p;
  dyn_used = mem_end + 1 - hi_mem_min;
  for (k = p; k <= lo_mem_max; k++) dump_wd(mem[k]);
  x = x + lo_mem_max + 1 - p;
  dump_int(hi_mem_min);
  dump_int(avail);
  for (k = hi_mem_min; k <= mem_end; k++) dump_wd(mem[k]);
  x = x + mem_end + 1 - hi_mem_min;
  p = avail;
  while (p != null) {
    decr(dyn_used);
    p = link(p);
  }
  dump_int(var_used);
  dump_int(dyn_used);
  print_ln();
  print_int(x);
  print_str(" memory locations dumped; current usage is ");
  print_int(var_used);
  print_char('&');
  print_int(dyn_used)

/*:1311*/
      ;
/*1313:*/

/*1315:*/

  k = active_base;
  do {
    j = k;
    while (j < int_base - 1) {
      if ((equiv(j) == equiv(j + 1)) && (eq_type(j) == eq_type(j + 1)) &&
          (eq_level(j) == eq_level(j + 1)))
        goto found1;
      incr(j);
    }
    l = int_base;
    goto done1;
  found1:
    incr(j);
    l = j;
    while (j < int_base - 1) {
      if ((equiv(j) != equiv(j + 1)) || (eq_type(j) != eq_type(j + 1)) ||
          (eq_level(j) != eq_level(j + 1)))
        goto done1;
      incr(j);
    }
  done1:
    dump_int(l - k);
    while (k < l) {
      dump_wd(eqtb[k]);
      incr(k);
    }
    k = j + 1;
    dump_int(k - l);
  } while (!(k == int_base))

/*:1315*/
      ;
/*1316:*/

  do {
    j = k;
    while (j < eqtb_size) {
      if (eqtb[j].i == eqtb[j + 1].i) goto found2;
      incr(j);
    }
    l = eqtb_size + 1;
    goto done2;
  found2:
    incr(j);
    l = j;
    while (j < eqtb_size) {
      if (eqtb[j].i != eqtb[j + 1].i) goto done2;
      incr(j);
    }
  done2:
    dump_int(l - k);
    while (k < l) {
      dump_wd(eqtb[k]);
      incr(k);
    }
    k = j + 1;
    dump_int(k - l);
  } while (!(k > eqtb_size))

/*:1316*/
      ;
  dump_int(par_loc);
  dump_int(write_loc);
/*1318:*/

  dump_int(hash_used);
  cs_count = frozen_control_sequence - 1 - hash_used;
  for (p = hash_base; p <= hash_used; p++)
    if (text(p) != 0) {
      dump_int(p);
      dump_hh(hash[p]);
      incr(cs_count);
    }
  for (p = hash_used + 1; p <= undefined_control_sequence - 1; p++)
    dump_hh(hash[p]);
  dump_int(cs_count);
  print_ln();
  print_int(cs_count);
  print_str(" multiletter control sequences")

/*:1318*/

/*:1313*/
      ;
/*1320:*/

  dump_int(fmem_ptr);
  for (k = 0; k <= fmem_ptr - 1; k++) dump_wd(font_info[k]);
  dump_int(font_ptr);
  for (k = null_font; k <= font_ptr; k++)
/*1322:*/

  {
    dump_qqqq(font_check[k]);
    dump_int(font_size[k]);
    dump_int(font_dsize[k]);
    dump_int(font_params[k]);
    dump_int(hyphen_char[k]);
    dump_int(skew_char[k]);
    dump_int(font_name[k]);
    dump_int(font_area[k]);
    dump_int(font_bc[k]);
    dump_int(font_ec[k]);
    dump_int(char_base[k]);
    dump_int(width_base[k]);
    dump_int(height_base[k]);
    dump_int(depth_base[k]);
    dump_int(italic_base[k]);
    dump_int(lig_kern_base[k]);
    dump_int(kern_base[k]);
    dump_int(exten_base[k]);
    dump_int(param_base[k]);
    dump_int(font_glue[k]);
    dump_int(bchar_label[k]);
    dump_int(font_bchar[k]);
    dump_int(font_false_bchar[k]);
    print_nl("\\font");
    print_esc(font_id_text(k));
    print_char('=');
    print_file_name(font_name[k], font_area[k], empty_string);
    if (font_size[k] != font_dsize[k]) {
      print_str(" at ");
      print_scaled(font_size[k]);
      print_str("pt");
    }
  }

/*:1322*/
  ;
  print_ln();
  print_int(fmem_ptr - 7);
  print_str(" words of font info for ");
  print_int(font_ptr - font_base);
  print_str(" preloaded font");
  if (font_ptr != font_base + 1)
    print_char('s')

/*:1320*/
        ;
/*1324:*/

  dump_int(hyph_count);
  for (k = 0; k <= hyph_size; k++)
    if (hyph_word[k] != 0) {
      dump_int(k);
      dump_int(hyph_word[k]);
      dump_int(hyph_list[k]);
    }
  print_ln();
  print_int(hyph_count);
  print_str(" hyphenation exception");
  if (hyph_count != 1) print_char('s');
  if (trie_not_ready) init_trie();
  dump_int(trie_max);
  for (k = 0; k <= trie_max; k++) dump_hh(trie[k]);
  dump_int(trie_op_ptr);
  for (k = 1; k <= trie_op_ptr; k++) {
    dump_int(hyf_distance[k]);
    dump_int(hyf_num[k]);
    dump_int(hyf_next[k]);
  }
  print_nl("Hyphenation trie of length ");
  print_int(trie_max);

  print_str(" has ");
  print_int(trie_op_ptr);
  print_str(" op");
  if (trie_op_ptr != 1) print_char('s');
  print_str(" out of ");
  print_int(trie_op_size);
  for (k = 255; k >= 0; k--)
    if (trie_used[k] > min_quarterword) {
      print_nl("  ");
      print_int(qo(trie_used[k]));
      print_str(" for language ");
      print_int(k);
      dump_int(k);
      dump_int(qo(trie_used[k]));
    }

/*:1324*/
    ;
/*1326:*/

  dump_int(interaction);
  dump_int(format_ident);
  dump_int(69069);
  tracing_stats = 0

/*:1326*/
      ;
/*1329:*/

  w_close(&fmt_file)

/*:1329*/
      ;
}
#endif

/*:1302*/ /*1348:*/

/*1349:*/

void new_whatsit(small_number s, small_number w) {
  pointer p;
  p = get_node(w);
  type(p) = whatsit_node;
  subtype(p) = s;
  link(tail) = p;
  tail = p;
}

/*:1349*/ /*1350:*/

void new_write_whatsit(small_number w) {
  new_whatsit(cur_chr, w);
  if (w != write_node_size)
    scan_four_bit_int();
  else {
    scan_int();
    if (cur_val < 0)
      cur_val = 17;
    else if (cur_val > 15)
      cur_val = 16;
  }
  write_stream(tail) = cur_val;
}

/*:1350*/

void do_extension(void) {
  int k;
  pointer p;
  switch (cur_chr) {
    case open_node: /*1351:*/

    {
      new_write_whatsit(open_node_size);
      scan_optional_equals();
      scan_file_name();
      open_name(tail) = cur_name;
      open_area(tail) = cur_area;
      open_ext(tail) = cur_ext;
    }

/*:1351*/
    break;
    case write_node: /*1352:*/

    {
      k = cur_cs;
      new_write_whatsit(write_node_size);
      cur_cs = k;
      p = scan_toks(false, false);
      write_tokens(tail) = def_ref;
    }

/*:1352*/
    break;
    case close_node: /*1353:*/

    {
      new_write_whatsit(write_node_size);
      write_tokens(tail) = null;
    }

/*:1353*/
    break;
    case special_node: /*1354:*/

    {
      new_whatsit(special_node, write_node_size);
      write_stream(tail) = null;
      p = scan_toks(false, true);
      write_tokens(tail) = def_ref;
    }

/*:1354*/
    break;
    case immediate_code: /*1375:*/

    {
      get_x_token();
      if ((cur_cmd == extension) && (cur_chr <= close_node)) {
        p = tail;
        do_extension();
        out_what(tail);
        flush_node_list(tail);
        tail = p;
        link(p) = null;
      } else
        back_input();
    }

/*:1375*/
    break;
    case set_language_code: /*1377:*/

      if (abs(mode) != hmode)
        report_illegal_case();
      else {
        new_whatsit(language_node, small_node_size);
        scan_int();
        if (cur_val <= 0)
          clang = 0;
        else if (cur_val > 255)
          clang = 0;
        else
          clang = cur_val;
        what_lang(tail) = clang;
        what_lhm(tail) = norm_min(left_hyphen_min);
        what_rhm(tail) = norm_min(right_hyphen_min);
      }

/*:1377*/
      break;
    default:
      confusion(/*1788:*/
                663
/*:1788*/
      );
  }
}

/*:1348*/ /*1376:*/

void fix_language(void) {
  ASCII_code l;
  if (language <= 0)
    l = 0;
  else if (language > 255)
    l = 0;
  else
    l = language;
  if (l != clang) {
    new_whatsit(language_node, small_node_size);
    what_lang(tail) = l;
    clang = l;
    what_lhm(tail) = norm_min(left_hyphen_min);
    what_rhm(tail) = norm_min(right_hyphen_min);
  }
}

/*:1376*/

/*1068:*/

void handle_right_brace(void) {
  pointer p, q;
  scaled d;
  int f;
  switch (cur_group) {
    case simple_group:
      unsave();
      break;
    case bottom_level: {
      print_err("Too many }'s");

      help2("You've closed more groups than you opened.")(
          "Such booboos are generally harmless, so keep going.");
      error();
    } break;
    case semi_simple_group:
    case math_shift_group:
    case math_left_group:
      extra_right_brace();
      break;
/*1085:*/

    case hbox_group:
      package(0);
      break;
    case adjusted_hbox_group: {
      adjust_tail = adjust_head;
      package(0);
    } break;
    case vbox_group: {
      end_graf();
      package(0);
    } break;
    case vtop_group: {
      end_graf();
      package(vtop_code);
    } break;

/*:1085*/ /*1100:*/

    case insert_group: {
      end_graf();
      q = split_top_skip;
      add_glue_ref(q);
      d = split_max_depth;
      f = floating_penalty;
      unsave();
      decr(save_ptr);

      p = vpack(link(head), natural);
      pop_nest();
      if (saved(0) < 255) {
        tail_append(get_node(ins_node_size));
        type(tail) = ins_node;
        subtype(tail) = qi(saved(0));
        height(tail) = height(p) + depth(p);
        ins_ptr(tail) = list_ptr(p);
        split_top_ptr(tail) = q;
        depth(tail) = d;
        float_cost(tail) = f;
      } else {
        tail_append(get_node(small_node_size));
        type(tail) = adjust_node;
        subtype(tail) = 0;
        adjust_ptr(tail) = list_ptr(p);
        delete_glue_ref(q);
      }
      free_node(p, box_node_size);
      if (nest_ptr == 0) build_page();
    } break;
    case output_group: /*1026:*/

    {
      if ((loc != null) ||
          ((token_type != output_text) && (token_type != backed_up)))
/*1027:*/

      {
        print_err("Unbalanced output routine");

        help2("Your sneaky output routine has problematic {'s and/or }'s.")(
            "I can't handle that very well; good luck.");
        error();
        do {
          get_token();
        } while (!(loc == null));
      }

/*:1027*/
      ;
      end_token_list();
      end_graf();
      unsave();
      output_active = false;
      insert_penalties = 0;
/*1028:*/

      if (box(255) != null) {
        print_err("Output routine didn't use all of ");
        print_esc(/*1437:*/
                  312
/*:1437*/
        );
        print_int(255);

        help3("Your \\output commands should empty \\box255,")(
            "e.g., by saying `\\shipout\\box255'.")(
            "Proceed; I'll discard its present contents.");
        box_error(255);
      }

/*:1028*/
      ;
      if (tail != head) {
        link(page_tail) = link(head);
        page_tail = tail;
      }
      if (link(page_head) != null) {
        if (link(contrib_head) == null) contrib_tail = page_tail;
        link(page_tail) = link(contrib_head);
        link(contrib_head) = link(page_head);
        link(page_head) = null;
        page_tail = page_head;
      }
      pop_nest();
      build_page();
    }

/*:1026*/
    break;

/*:1100*/ /*1118:*/

    case disc_group:
      build_discretionary();
      break;

/*:1118*/ /*1132:*/

    case align_group: {
      back_input();
      cur_tok = cs_token_flag + frozen_cr;
      print_err("Missing ");
      print_esc(/*1670:*/
                545
/*:1670*/
      );
      print_str(" inserted");

      help1("I'm guessing that you meant to end an alignment here.");
      ins_error();
    } break;

/*:1132*/ /*1133:*/

    case no_align_group: {
      end_graf();
      unsave();
      align_peek();
    } break;

/*:1133*/ /*1168:*/

    case vcenter_group: {
      end_graf();
      unsave();
      save_ptr = save_ptr - 2;
      p = vpack(link(head), saved(1), saved(0));
      pop_nest();
      tail_append(new_noad());
      type(tail) = vcenter_noad;
      math_type(nucleus(tail)) = sub_box;
      info(nucleus(tail)) = p;
    } break;

/*:1168*/ /*1173:*/

    case math_choice_group:
      build_choices();
      break;

/*:1173*/ /*1186:*/

    case math_group: {
      unsave();
      decr(save_ptr);
      math_type(saved(0)) = sub_mlist;
      p = fin_mlist(null);
      info(saved(0)) = p;
      if (p != null)
        if (link(p) == null)
          if (type(p) == ord_noad) {
            if (math_type(subscr(p)) == empty)
              if (math_type(supscr(p)) == empty) {
                mem[saved(0)].hh = mem[nucleus(p)].hh;
                free_node(p, noad_size);
              }
          } else if (type(p) == accent_noad)
            if (saved(0) == nucleus(tail))
              if (type(tail) == ord_noad) /*1187:*/

              {
                q = head;
                while (link(q) != tail) q = link(q);
                link(q) = p;
                free_node(tail, noad_size);
                tail = p;
              }

/*:1187*/
              ;
    } break;

/*:1186*/

    default:
      confusion(/*1711:*/
                586
/*:1711*/
      );
  }
}

/*:1068*/

void main_control(void) {
  int t;
  if (every_job != null) begin_token_list(every_job, every_job_text);
big_switch:
  get_x_token();
reswitch: /*1031:*/

  if (interrupt != 0)
    if (OK_to_interrupt) {
      back_input();
      check_interrupt;
      goto big_switch;
    }
#ifdef DEBUG
  if (panicking) check_mem(false);
#endif
  if (tracing_commands > 0)
    show_cur_cmd_chr()

/*:1031*/
        ;
  switch (abs(mode) + cur_cmd) {
    case hmode + letter:
    case hmode + other_char:
    case hmode + char_given:
      goto main_loop;
    case hmode + char_num: {
      scan_char_num();
      cur_chr = cur_val;
      goto main_loop;
    }
    case hmode + no_boundary: {
      get_x_token();
      if ((cur_cmd == letter) || (cur_cmd == other_char) ||
          (cur_cmd == char_given) || (cur_cmd == char_num))
        cancel_boundary = true;
      goto reswitch;
    }
    case hmode + spacer:
      if (space_factor == 1000)
        goto append_normal_space;
      else
        app_space();
      break;
    case hmode + ex_space:
    case mmode + ex_space:
      goto append_normal_space;
/*1045:*/

    any_mode(relax) : case vmode + spacer:
    case mmode + spacer:
    case mmode + no_boundary:
      do_nothing;
      any_mode(ignore_spaces) : { /*406:*/

        do {
          get_x_token();
        } while (!(cur_cmd != spacer))

/*:406*/
            ;
        goto reswitch;
      }
    case vmode + stop:
      if (its_all_over()) return;
      break;
/*1048:*/

    case vmode + vmove:
    case hmode + hmove:
    case mmode + hmove:
    any_mode(last_item)
        :

/*:1048*/ /*1098:*/

          case vmode +
          vadjust:

/*:1098*/ /*1111:*/
    case vmode + ital_corr:

/*:1111*/ /*1144:*/
      non_math(eq_no)
          :

/*:1144*/
            any_mode(mac_param)
          : report_illegal_case();
      break;
/*1046:*/

    non_math(sup_mark)
        : non_math(sub_mark)
        : non_math(math_char_num)
        : non_math(math_given)
        : non_math(math_comp)
        : non_math(delim_num)
        : non_math(left_right)
        : non_math(above)
        : non_math(radical)
        : non_math(math_style)
        : non_math(math_choice)
        : non_math(vcenter)
        : non_math(non_script)
        : non_math(mkern)
        : non_math(limit_switch)
        : non_math(mskip) : non_math(math_accent) : case mmode + endv:
    case mmode + par_end:
    case mmode + stop:
    case mmode + vskip:
    case mmode + un_vbox:
    case mmode + valign:
    case mmode + hrule

/*:1046*/
        :
      insert_dollar_sign();
      break;
/*1056:*/

    case vmode + hrule:
    case hmode + vrule:
    case mmode + vrule: {
      tail_append(scan_rule_spec());
      if (abs(mode) == vmode)
        prev_depth = ignore_depth;
      else if (abs(mode) == hmode)
        space_factor = 1000;
    } break;

/*:1056*/ /*1057:*/

    case vmode + vskip:
    case hmode + hskip:
    case mmode + hskip:
    case mmode + mskip:
      append_glue();
      break;
    any_mode(kern) : case mmode + mkern:
      append_kern();
      break;

/*:1057*/ /*1063:*/

      non_math(left_brace) : new_save_level(simple_group);
      break;
      any_mode(begin_group) : new_save_level(semi_simple_group);
      break;
      any_mode(end_group) : if (cur_group == semi_simple_group) unsave();
      else off_save();
      break;

/*:1063*/ /*1067:*/

      any_mode(right_brace) : handle_right_brace();
      break;

/*:1067*/ /*1073:*/

    case vmode + hmove:
    case hmode + vmove:
    case mmode + vmove: {
      t = cur_chr;
      scan_normal_dimen;
      if (t == 0)
        scan_box(cur_val);
      else
        scan_box(-cur_val);
    } break;
      any_mode(leader_ship) : scan_box(leader_flag - a_leaders + cur_chr);
      break;
      any_mode(make_box) : begin_box(0);
      break;

/*:1073*/ /*1090:*/

    case vmode + start_par:
      new_graf(cur_chr > 0);
      break;
    case vmode + letter:
    case vmode + other_char:
    case vmode + char_num:
    case vmode + char_given:
    case vmode + math_shift:
    case vmode + un_hbox:
    case vmode + vrule:
    case vmode + accent:
    case vmode + discretionary:
    case vmode + hskip:
    case vmode + valign:
    case vmode + ex_space:
    case vmode + no_boundary: {
      back_input();
      new_graf(true);
    } break;

/*:1090*/ /*1092:*/

    case hmode + start_par:
    case mmode + start_par:
      indent_in_hmode();
      break;

/*:1092*/ /*1094:*/

    case vmode + par_end: {
      normal_paragraph();
      if (mode > 0) build_page();
    } break;
    case hmode + par_end: {
      if (align_state < 0) off_save();

      end_graf();
      if (mode == vmode) build_page();
    } break;
    case hmode + stop:
    case hmode + vskip:
    case hmode + hrule:
    case hmode + un_vbox:
    case hmode + halign:
      head_for_vmode();
      break;

/*:1094*/ /*1097:*/

    any_mode(insert) : case hmode + vadjust:
    case mmode + vadjust:
      begin_insert_or_adjust();
      break;
      any_mode(mark) : make_mark();
      break;

/*:1097*/ /*1102:*/

      any_mode(break_penalty) : append_penalty();
      break;

/*:1102*/ /*1104:*/

      any_mode(remove_item) : delete_last();
      break;

/*:1104*/ /*1109:*/

    case vmode + un_vbox:
    case hmode + un_hbox:
    case mmode + un_hbox:
      unpackage();
      break;

/*:1109*/ /*1112:*/

    case hmode + ital_corr:
      append_italic_correction();
      break;
    case mmode + ital_corr:
      tail_append(new_kern(0)) break;

/*:1112*/ /*1116:*/

    case hmode + discretionary:
    case mmode + discretionary:
      append_discretionary();
      break;

/*:1116*/ /*1122:*/

    case hmode + accent:
      make_accent();
      break;

/*:1122*/ /*1126:*/

      any_mode(car_ret) : any_mode(tab_mark) : align_error();
      break;
      any_mode(no_align) : no_align_error();
      break;
      any_mode(omit) : omit_error();
      break;

/*:1126*/ /*1130:*/

    case vmode + halign:
    case hmode + valign:
      init_align();
      break;
    case mmode + halign:
      if (privileged())
        if (cur_group == math_shift_group)
          init_align();
        else
          off_save();
      break;
    case vmode + endv:
    case hmode + endv:
      do_endv();
      break;

/*:1130*/ /*1134:*/

      any_mode(end_cs_name) : cs_error();
      break;

/*:1134*/ /*1137:*/

    case hmode + math_shift:
      init_math();
      break;

/*:1137*/ /*1140:*/

    case mmode + eq_no:
      if (privileged())
        if (cur_group == math_shift_group)
          start_eq_no();
        else
          off_save();
      break;

/*:1140*/ /*1150:*/

    case mmode + left_brace: {
      tail_append(new_noad());
      back_input();
      scan_math(nucleus(tail));
    } break;

/*:1150*/ /*1154:*/

    case mmode + letter:
    case mmode + other_char:
    case mmode + char_given:
      set_math_char(ho(math_code(cur_chr)));
      break;
    case mmode + char_num: {
      scan_char_num();
      cur_chr = cur_val;
      set_math_char(ho(math_code(cur_chr)));
    } break;
    case mmode + math_char_num: {
      scan_fifteen_bit_int();
      set_math_char(cur_val);
    } break;
    case mmode + math_given:
      set_math_char(cur_chr);
      break;
    case mmode + delim_num: {
      scan_twenty_seven_bit_int();
      set_math_char(cur_val / 010000);
    } break;

/*:1154*/ /*1158:*/

    case mmode + math_comp: {
      tail_append(new_noad());
      type(tail) = cur_chr;
      scan_math(nucleus(tail));
    } break;
    case mmode + limit_switch:
      math_limit_switch();
      break;

/*:1158*/ /*1162:*/

    case mmode + radical:
      math_radical();
      break;

/*:1162*/ /*1164:*/

    case mmode + accent:
    case mmode + math_accent:
      math_ac();
      break;

/*:1164*/ /*1167:*/

    case mmode + vcenter: {
      scan_spec(vcenter_group, false);
      normal_paragraph();
      push_nest();
      mode = -vmode;
      prev_depth = ignore_depth;
      if (every_vbox != null) begin_token_list(every_vbox, every_vbox_text);
    } break;

/*:1167*/ /*1171:*/

    case mmode + math_style:
      tail_append(new_style(cur_chr)) break;
    case mmode + non_script: {
      tail_append(new_glue(zero_glue));
      subtype(tail) = cond_math_glue;
    } break;
    case mmode + math_choice:
      append_choices();
      break;

/*:1171*/ /*1175:*/

    case mmode + sub_mark:
    case mmode + sup_mark:
      sub_sup();
      break;

/*:1175*/ /*1180:*/

    case mmode + above:
      math_fraction();
      break;

/*:1180*/ /*1190:*/

    case mmode + left_right:
      math_left_right();
      break;

/*:1190*/ /*1193:*/

    case mmode + math_shift:
      if (cur_group == math_shift_group)
        after_math();
      else
        off_save();
      break;

/*:1193*/

/*1210:*/

      any_mode(toks_register)
          : any_mode(assign_toks)
          : any_mode(assign_int)
          : any_mode(assign_dimen)
          : any_mode(assign_glue)
          : any_mode(assign_mu_glue)
          : any_mode(assign_font_dimen)
          : any_mode(assign_font_int)
          : any_mode(set_aux)
          : any_mode(set_prev_graf)
          : any_mode(set_page_dimen)
          : any_mode(set_page_int)
          : any_mode(set_box_dimen)
          : any_mode(set_shape)
          : any_mode(def_code)
          : any_mode(def_family)
          : any_mode(set_font)
          : any_mode(def_font)
          : any_mode(register)
          : any_mode(advance)
          : any_mode(multiply)
          : any_mode(divide)
          : any_mode(prefix)
          : any_mode(let)
          : any_mode(shorthand_def)
          : any_mode(read_to_cs)
          : any_mode(def)
          : any_mode(set_box)
          : any_mode(hyph_data)
          : any_mode(set_interaction) : prefixed_command();
      break;

/*:1210*/ /*1268:*/

      any_mode(after_assignment) : {
        get_token();
        after_token = cur_tok;
      }
      break;

/*:1268*/ /*1271:*/

      any_mode(after_group) : {
        get_token();
        save_for_after(cur_tok);
      }
      break;

/*:1271*/ /*1274:*/

      any_mode(in_stream) : open_or_close_in();
      break;

/*:1274*/ /*1276:*/

      any_mode(message) : issue_message();
      break;

/*:1276*/ /*1285:*/

      any_mode(case_shift) : shift_case();
      break;

/*:1285*/ /*1290:*/

      any_mode(xray) : show_whatever();
      break;

/*:1290*/

/*1347:*/

      any_mode(extension) : do_extension();

/*:1347*/

/*:1045*/
  }
  goto big_switch;
main_loop: /*1034:*/

  adjust_space_factor;
  main_f = cur_font;
  bchar = font_bchar[main_f];
  false_bchar = font_false_bchar[main_f];
  if (mode > 0)
    if (language != clang) fix_language();
  fast_get_avail(lig_stack);
  font(lig_stack) = main_f;
  cur_l = qi(cur_chr);
  character(lig_stack) = cur_l;
  cur_q = tail;
  if (cancel_boundary) {
    cancel_boundary = false;
    main_k = non_address;
  } else
    main_k = bchar_label[main_f];
  if (main_k == non_address) goto main_loop_move2;
  cur_r = cur_l;
  cur_l = non_char;
  goto main_lig_loop1;

main_loop_wrapup: /*1035:*/

  wrapup(rt_hit)

/*:1035*/
      ;
main_loop_move: /*1036:*/

  if (lig_stack == null) goto reswitch;
  cur_q = tail;
  cur_l = character(lig_stack);
main_loop_move1:
  if (!is_char_node(lig_stack)) goto main_loop_move_lig;
main_loop_move2:
  if ((cur_chr < font_bc[main_f]) || (cur_chr > font_ec[main_f])) {
    char_warning(main_f, cur_chr);
    free_avail(lig_stack);
    goto big_switch;
  }
  main_i = char_info(main_f)(cur_l);
  if (!char_exists(main_i)) {
    char_warning(main_f, cur_chr);
    free_avail(lig_stack);
    goto big_switch;
  }
  link(tail) = lig_stack;
  tail = lig_stack

/*:1036*/
      ;
main_loop_lookahead: /*1038:*/

  get_next();
  if (cur_cmd == letter) goto main_loop_lookahead1;
  if (cur_cmd == other_char) goto main_loop_lookahead1;
  if (cur_cmd == char_given) goto main_loop_lookahead1;
  x_token();
  if (cur_cmd == letter) goto main_loop_lookahead1;
  if (cur_cmd == other_char) goto main_loop_lookahead1;
  if (cur_cmd == char_given) goto main_loop_lookahead1;
  if (cur_cmd == char_num) {
    scan_char_num();
    cur_chr = cur_val;
    goto main_loop_lookahead1;
  }
  if (cur_cmd == no_boundary) bchar = non_char;
  cur_r = bchar;
  lig_stack = null;
  goto main_lig_loop;
main_loop_lookahead1:
  adjust_space_factor;
  fast_get_avail(lig_stack);
  font(lig_stack) = main_f;
  cur_r = qi(cur_chr);
  character(lig_stack) = cur_r;
  if (cur_r == false_bchar)
    cur_r = non_char

/*:1038*/
        ;
main_lig_loop: /*1039:*/

  if (char_tag(main_i) != lig_tag) goto main_loop_wrapup;
  if (cur_r == non_char) goto main_loop_wrapup;
  main_k = lig_kern_start(main_f)(main_i);
  main_j = font_info[main_k].qqqq;
  if (skip_byte(main_j) <= stop_flag) goto main_lig_loop2;
  main_k = lig_kern_restart(main_f)(main_j);
main_lig_loop1:
  main_j = font_info[main_k].qqqq;
main_lig_loop2:
  if (next_char(main_j) == cur_r)
    if (skip_byte(main_j) <= stop_flag)
/*1040:*/

    {
      if (op_byte(main_j) >= kern_flag) {
        wrapup(rt_hit);
        tail_append(new_kern(char_kern(main_f)(main_j)));
        goto main_loop_move;
      }
      if (cur_l == non_char)
        lft_hit = true;
      else if (lig_stack == null)
        rt_hit = true;
      check_interrupt;
      switch (op_byte(main_j)) {
        qi(case 1) : qi(case 5) : {
          cur_l = rem_byte(main_j);
          main_i = char_info(main_f)(cur_l);
          ligature_present = true;
        }
        break;
        qi(case 2) : qi(case 6) : {
          cur_r = rem_byte(main_j);
          if (lig_stack == null) {
            lig_stack = new_lig_item(cur_r);
            bchar = non_char;
          } else if (is_char_node(lig_stack)) {
            main_p = lig_stack;
            lig_stack = new_lig_item(cur_r);
            lig_ptr(lig_stack) = main_p;
          } else
            character(lig_stack) = cur_r;
        }
        break;
        qi(case 3) : {
          cur_r = rem_byte(main_j);
          main_p = lig_stack;
          lig_stack = new_lig_item(cur_r);
          link(lig_stack) = main_p;
        }
        break;
        qi(case 7) : qi(case 11) : {
          wrapup(false);
          cur_q = tail;
          cur_l = rem_byte(main_j);
          main_i = char_info(main_f)(cur_l);
          ligature_present = true;
        }
        break;
        default: {
          cur_l = rem_byte(main_j);
          ligature_present = true;
          if (lig_stack == null)
            goto main_loop_wrapup;
          else
            goto main_loop_move1;
        }
      }
      if (op_byte(main_j) > qi(4))
        if (op_byte(main_j) != qi(7)) goto main_loop_wrapup;
      if (cur_l < non_char) goto main_lig_loop;
      main_k = bchar_label[main_f];
      goto main_lig_loop1;
    }

/*:1040*/
    ;
  if (skip_byte(main_j) == qi(0))
    incr(main_k);
  else {
    if (skip_byte(main_j) >= stop_flag) goto main_loop_wrapup;
    main_k = main_k + qo(skip_byte(main_j)) + 1;
  }
  goto main_lig_loop1

/*:1039*/
      ;
main_loop_move_lig: /*1037:*/

  main_p = lig_ptr(lig_stack);
  if (main_p > null) tail_append(main_p);
  temp_ptr = lig_stack;
  lig_stack = link(temp_ptr);
  free_node(temp_ptr, small_node_size);
  main_i = char_info(main_f)(cur_l);
  ligature_present = true;
  if (lig_stack == null)
    if (main_p > null)
      goto main_loop_lookahead;
    else
      cur_r = bchar;
  else
    cur_r = character(lig_stack);
  goto main_lig_loop

/*:1037*/

/*:1034*/
      ;
append_normal_space: /*1041:*/

  if (space_skip == zero_glue) { /*1042:*/

    {
      main_p = font_glue[cur_font];
      if (main_p == null) {
        main_p = new_spec(zero_glue);
        main_k = param_base[cur_font] + space_code;
        width(main_p) = font_info[main_k].sc;
        stretch(main_p) = font_info[main_k + 1].sc;
        shrink(main_p) = font_info[main_k + 2].sc;
        font_glue[cur_font] = main_p;
      }
    }

/*:1042*/
    ;
    temp_ptr = new_glue(main_p);
  } else
    temp_ptr = new_param_glue(space_skip_code);
  link(tail) = temp_ptr;
  tail = temp_ptr;
  goto big_switch

/*:1041*/
      ;
}

/*:1030*/ /*1284:*/
void give_err_help(void) { token_show(err_help); }

/*:1284*/ /*1303:*/
/*523:*/

bool open_fmt_file(void) {
  uint16_t j;
  j = loc;
  if (buffer[loc] == '&') {
    incr(loc);
    j = loc;
    buffer[last] = ' ';
    while (buffer[j] != ' ') incr(j);
    pack_buffered_name(0, loc, j - 1);
    if (w_open_in(&fmt_file)) goto found;
    pack_buffered_name(format_area_length, loc, j - 1);

    if (w_open_in(&fmt_file)) goto found;
    wake_up_terminal;
    wterm_ln("Sorry, I can't find that format; will try PLAIN.");

    update_terminal;
  }

  pack_buffered_name(format_default_length - format_ext_length, 1, 0);
  if (!w_open_in(&fmt_file)) {
    wake_up_terminal;
    wterm_ln("I can't find the PLAIN format file!");

    return false;
  }
found:
  loc = j;
  return true;
}

/*:523*/

bool load_fmt_file(void) {
  int j, k;
  pointer p, q;
  int x;
  four_quarters w;
/*1308:*/

  x = fmt_file.d.i;
  if (x != 0) goto bad_fmt;
  undump_int(x);
  if (x != mem_bot) goto bad_fmt;
  undump_int(x);
  if (x != mem_top) goto bad_fmt;
  undump_int(x);
  if (x != eqtb_size) goto bad_fmt;
  undump_int(x);
  if (x != hash_prime) goto bad_fmt;
  undump_int(x);
  if (x != hyph_size)
    goto bad_fmt

/*:1308*/
        ;
/*1310:*/

  undump_size(0)(pool_size)("string pool size")(pool_ptr);
  undump_size(0)(max_strings)("max strings")(str_ptr);
  for (k = 0; k <= str_ptr; k++) undump(0)(pool_ptr)(str_start[k]);
  k = 0;
  while (k + 4 < pool_ptr) {
    undump_four_ASCII;
    k = k + 4;
  }
  k = pool_ptr - 4;
  undump_four_ASCII;
  init_str_ptr = str_ptr;
  init_pool_ptr = pool_ptr

/*:1310*/
      ;
/*1312:*/

  undump(lo_mem_stat_max + 1000)(hi_mem_stat_min - 1)(lo_mem_max);
  undump(lo_mem_stat_max + 1)(lo_mem_max)(rover);
  p = mem_bot;
  q = rover;
  do {
    for (k = p; k <= q + 1; k++) undump_wd(mem[k]);
    p = q + node_size(q);
    if ((p > lo_mem_max) || ((q >= rlink(q)) && (rlink(q) != rover)))
      goto bad_fmt;
    q = rlink(q);
  } while (!(q == rover));
  for (k = p; k <= lo_mem_max; k++) undump_wd(mem[k]);
  if (mem_min < mem_bot - 2) {
    p = llink(rover);
    q = mem_min + 1;
    link(mem_min) = null;
    info(mem_min) = null;
    rlink(p) = q;
    llink(rover) = q;
    rlink(q) = rover;
    llink(q) = p;
    link(q) = empty_flag;
    node_size(q) = mem_bot - q;
  }
  undump(lo_mem_max + 1)(hi_mem_stat_min)(hi_mem_min);
  undump(null)(mem_top)(avail);
  mem_end = mem_top;
  for (k = hi_mem_min; k <= mem_end; k++) undump_wd(mem[k]);
  undump_int(var_used);
  undump_int(dyn_used)

/*:1312*/
      ;
/*1314:*/

/*1317:*/

  k = active_base;
  do {
    undump_int(x);
    if ((x < 1) || (k + x > eqtb_size + 1)) goto bad_fmt;
    for (j = k; j <= k + x - 1; j++) undump_wd(eqtb[j]);
    k = k + x;
    undump_int(x);
    if ((x < 0) || (k + x > eqtb_size + 1)) goto bad_fmt;
    for (j = k; j <= k + x - 1; j++) eqtb[j] = eqtb[k - 1];
    k = k + x;
  } while (!(k > eqtb_size))

/*:1317*/
      ;
  undump(hash_base)(frozen_control_sequence)(par_loc);
  par_token = cs_token_flag + par_loc;
  undump(hash_base)(frozen_control_sequence)(write_loc);
/*1319:*/

  undump(hash_base)(frozen_control_sequence)(hash_used);
  p = hash_base - 1;
  do {
    undump(p + 1)(hash_used)(p);
    undump_hh(hash[p]);
  } while (!(p == hash_used));
  for (p = hash_used + 1; p <= undefined_control_sequence - 1; p++)
    undump_hh(hash[p]);
  undump_int(cs_count)

/*:1319*/

/*:1314*/
      ;
/*1321:*/

  undump_size(7)(font_mem_size)("font mem size")(fmem_ptr);
  for (k = 0; k <= fmem_ptr - 1; k++) undump_wd(font_info[k]);
  undump_size(font_base)(font_max)("font max")(font_ptr);
  for (k = null_font; k <= font_ptr; k++)
/*1323:*/

  {
    undump_qqqq(font_check[k]);
    undump_int(font_size[k]);
    undump_int(font_dsize[k]);
    undump(min_halfword)(max_halfword)(font_params[k]);
    undump_int(hyphen_char[k]);
    undump_int(skew_char[k]);
    undump(0)(str_ptr)(font_name[k]);
    undump(0)(str_ptr)(font_area[k]);
    undump(0)(255)(font_bc[k]);
    undump(0)(255)(font_ec[k]);
    undump_int(char_base[k]);
    undump_int(width_base[k]);
    undump_int(height_base[k]);
    undump_int(depth_base[k]);
    undump_int(italic_base[k]);
    undump_int(lig_kern_base[k]);
    undump_int(kern_base[k]);
    undump_int(exten_base[k]);
    undump_int(param_base[k]);
    undump(min_halfword)(lo_mem_max)(font_glue[k]);
    undump(0)(fmem_ptr - 1)(bchar_label[k]);
    undump(min_quarterword)(non_char)(font_bchar[k]);
    undump(min_quarterword)(non_char)(font_false_bchar[k]);
  }

/*:1323*/

/*:1321*/
  ;
/*1325:*/

  undump(0)(hyph_size)(hyph_count);
  for (k = 1; k <= hyph_count; k++) {
    undump(0)(hyph_size)(j);
    undump(0)(str_ptr)(hyph_word[j]);
    undump(min_halfword)(max_halfword)(hyph_list[j]);
  }
  undump_size(0)(trie_size)("trie size")(j);
#ifdef INIT
  trie_max = j;
#endif
  for (k = 0; k <= j; k++) undump_hh(trie[k]);
  undump_size(0)(trie_op_size)("trie op size")(j);
#ifdef INIT
  trie_op_ptr = j;
#endif
  for (k = 1; k <= j; k++) {
    undump(0)(63)(hyf_distance[k]);
    undump(0)(63)(hyf_num[k]);
    undump(min_quarterword)(max_quarterword)(hyf_next[k]);
  }
#ifdef INIT
  for (k = 0; k <= 255; k++) trie_used[k] = min_quarterword;
#endif

  k = 256;
  while (j > 0) {
    undump(0)(k - 1)(k);
    undump(1)(j)(x);
#ifdef INIT
    trie_used[k] = qi(x);
#endif

    j = j - x;
    op_start[k] = qo(j);
  }
#ifdef INIT
  trie_not_ready = false
#endif

/*:1325*/
      ;
/*1327:*/

  undump(batch_mode)(error_stop_mode)(interaction);
  undump(0)(str_ptr)(format_ident);
  undump_int(x);
  if ((x != 69069) || eof(fmt_file))
    goto bad_fmt

/*:1327*/
        ;
  return true;
bad_fmt:
  wake_up_terminal;
  wterm_ln("(Fatal format file error; I'm stymied)");

  return false;
}

/*:1303*/ /*1330:*/
/*1333:*/

void close_files_and_terminate(void) {
  int k;
/*1378:*/

  for (k = 0; k <= 15; k++)
    if (write_open[k])
      a_close(&write_file[k])

/*:1378*/
          ;
  new_line_char = -1;
#ifdef STAT
  if (tracing_stats > 0) /*1334:*/

    if (log_opened) {
      wlog_ln(" ");
      wlog_ln("Here is how much of TeX's memory you used:");

      wlog(" %d string", str_ptr - init_str_ptr);
      if (str_ptr != init_str_ptr + 1) wlog("s");
      wlog_ln(" out of %d", max_strings - init_str_ptr);
      wlog_ln(" %d string characters out of %d", pool_ptr - init_pool_ptr,
              pool_size - init_pool_ptr);
      wlog_ln(" %d words of memory out of %d",
              lo_mem_max - mem_min + mem_end - hi_mem_min + 2,
              mem_end + 1 - mem_min);
      wlog_ln(" %d multiletter control sequences out of %d", cs_count,
              hash_size);
      wlog(" %d words of font info for %d font", fmem_ptr,
           font_ptr - font_base);
      if (font_ptr != font_base + 1) wlog("s");
      wlog_ln(", out of %d for %d", font_mem_size, font_max - font_base);
      wlog(" %d hyphenation exception", hyph_count);
      if (hyph_count != 1) wlog("s");
      wlog_ln(" out of %d", hyph_size);
      wlog_ln(" %di,%dn,%dp,%db,%ds stack positions out of %di,%dn,%dp,%db,%ds",
              max_in_stack, max_nest_stack, max_param_stack, max_buf_stack + 1,
              max_save_stack + 6, stack_size, nest_size, param_size, buf_size,
              save_size);
    }

/*:1334*/
    ;
#endif
  wake_up_terminal; /*642:*/

  while (cur_s > -1) {
    if (cur_s > 0) dvi_out(pop) else {
        dvi_out(eop);
        incr(total_pages);
      }
    decr(cur_s);
  }
  if (total_pages == 0)
    print_nl("No pages of output.");

  else {
    dvi_out(post);
    dvi_four(last_bop);
    last_bop = dvi_offset + dvi_ptr - 5;
    dvi_four(25400000);
    dvi_four(473628672);
    prepare_mag();
    dvi_four(mag);
    dvi_four(max_v);
    dvi_four(max_h);
    dvi_out(max_push / 256);
    dvi_out(max_push % 256);
    dvi_out((total_pages / 256) % 256);
    dvi_out(total_pages % 256);
/*643:*/

    while (font_ptr > font_base) {
      if (font_used[font_ptr]) dvi_font_def(font_ptr);
      decr(font_ptr);
    }

/*:643*/
    ;
    dvi_out(post_post);
    dvi_four(last_bop);
    dvi_out(id_byte);
    k = 4 + ((dvi_buf_size - dvi_ptr) % 4);
    while (k > 0) {
      dvi_out(223);
      decr(k);
    }
/*599:*/

    if (dvi_limit == half_buf) write_dvi(half_buf, dvi_buf_size - 1);
    if (dvi_ptr > 0)
      write_dvi(0, dvi_ptr - 1)

/*:599*/
          ;
    print_nl("Output written on ");
    slow_print(output_file_name);

    print_str(" (");
    print_int(total_pages);
    print_str(" page");
    if (total_pages != 1) print_char('s');
    print_str(", ");
    print_int(dvi_offset + dvi_ptr);
    print_str(" bytes).");
    b_close(&dvi_file);
  }

/*:642*/
  ;
  if (log_opened) {
    wlog_cr;
    a_close(&log_file);
    selector = selector - 2;
    if (selector == term_only) {
      print_nl("Transcript written on ");

      slow_print(log_name);
      print_char('.');
    }
  }
}

/*:1333*/ /*1335:*/

void final_cleanup(void) {
  small_number c;
  c = cur_chr;
  if (c != 1) new_line_char = -1;
  if (job_name == 0) open_log_file();
  while (input_ptr > 0)
    if (state == token_list)
      end_token_list();
    else
      end_file_reading();
  while (open_parens > 0) {
    print_str(" )");
    decr(open_parens);
  }
  if (cur_level > level_one) {
    print_nl("(");
    print_esc(/*1782:*/
              657
/*:1782*/
    );
    print_str("inside a group at level ");

    print_int(cur_level - level_one);
    print_char(')');
  }
  while (cond_ptr != null) {
    print_nl("(");
    print_esc(/*1782:*/
              657
/*:1782*/
    );
    print_str("when ");
    print_cmd_chr(if_test, cur_if);
    if (if_line != 0) {
      print_str(" on line ");
      print_int(if_line);
    }
    print_str(" was incomplete)");
    if_line = if_line_field(cond_ptr);
    cur_if = subtype(cond_ptr);
    temp_ptr = cond_ptr;
    cond_ptr = link(cond_ptr);
    free_node(temp_ptr, if_node_size);
  }
  if (history != spotless)
    if (((history == warning_issued) || (interaction < error_stop_mode)))
      if (selector == term_and_log) {
        selector = term_only;
        print_nl("(see the transcript file for additional information)");

        selector = term_and_log;
      }
  if (c == 1) {
#ifdef INIT
    for (c = top_mark_code; c <= split_bot_mark_code; c++)
      if (cur_mark[c] != null) delete_token_ref(cur_mark[c]);
    if (last_glue != max_halfword) delete_glue_ref(last_glue);
    store_fmt_file();
    return;
#endif
    print_nl("(\\dump is performed only by INITEX)");
    return;
  }
}

/*:1335*/ /*1336:*/

#ifdef INIT
void init_prim(void) {
  no_new_control_sequence = false;
/*226:*/

  primitive(/*1405:*/
            280
/*:1405*/
            ,
            assign_glue, glue_base + line_skip_code);

  primitive(/*1406:*/
            281
/*:1406*/
            ,
            assign_glue, glue_base + baseline_skip_code);

  primitive(/*1407:*/
            282
/*:1407*/
            ,
            assign_glue, glue_base + par_skip_code);

  primitive(/*1408:*/
            283
/*:1408*/
            ,
            assign_glue, glue_base + above_display_skip_code);

  primitive(/*1409:*/
            284
/*:1409*/
            ,
            assign_glue, glue_base + below_display_skip_code);

  primitive(/*1410:*/
            285
/*:1410*/
            ,
            assign_glue, glue_base + above_display_short_skip_code);

  primitive(/*1411:*/
            286
/*:1411*/
            ,
            assign_glue, glue_base + below_display_short_skip_code);

  primitive(/*1412:*/
            287
/*:1412*/
            ,
            assign_glue, glue_base + left_skip_code);

  primitive(/*1413:*/
            288
/*:1413*/
            ,
            assign_glue, glue_base + right_skip_code);

  primitive(/*1414:*/
            289
/*:1414*/
            ,
            assign_glue, glue_base + top_skip_code);

  primitive(/*1415:*/
            290
/*:1415*/
            ,
            assign_glue, glue_base + split_top_skip_code);

  primitive(/*1416:*/
            291
/*:1416*/
            ,
            assign_glue, glue_base + tab_skip_code);

  primitive(/*1417:*/
            292
/*:1417*/
            ,
            assign_glue, glue_base + space_skip_code);

  primitive(/*1418:*/
            293
/*:1418*/
            ,
            assign_glue, glue_base + xspace_skip_code);

  primitive(/*1419:*/
            294
/*:1419*/
            ,
            assign_glue, glue_base + par_fill_skip_code);

  primitive(/*1420:*/
            295
/*:1420*/
            ,
            assign_mu_glue, glue_base + thin_mu_skip_code);

  primitive(/*1421:*/
            296
/*:1421*/
            ,
            assign_mu_glue, glue_base + med_mu_skip_code);

  primitive(/*1422:*/
            297
/*:1422*/
            ,
            assign_mu_glue, glue_base + thick_mu_skip_code);

/*:226*/ /*230:*/

  primitive(/*1426:*/
            301
/*:1426*/
            ,
            assign_toks, output_routine_loc);

  primitive(/*1427:*/
            302
/*:1427*/
            ,
            assign_toks, every_par_loc);

  primitive(/*1428:*/
            303
/*:1428*/
            ,
            assign_toks, every_math_loc);

  primitive(/*1429:*/
            304
/*:1429*/
            ,
            assign_toks, every_display_loc);

  primitive(/*1430:*/
            305
/*:1430*/
            ,
            assign_toks, every_hbox_loc);

  primitive(/*1431:*/
            306
/*:1431*/
            ,
            assign_toks, every_vbox_loc);

  primitive(/*1432:*/
            307
/*:1432*/
            ,
            assign_toks, every_job_loc);

  primitive(/*1433:*/
            308
/*:1433*/
            ,
            assign_toks, every_cr_loc);

  primitive(/*1434:*/
            309
/*:1434*/
            ,
            assign_toks, err_help_loc);

/*:230*/ /*238:*/

  primitive(/*1446:*/
            321
/*:1446*/
            ,
            assign_int, int_base + pretolerance_code);

  primitive(/*1447:*/
            322
/*:1447*/
            ,
            assign_int, int_base + tolerance_code);

  primitive(/*1448:*/
            323
/*:1448*/
            ,
            assign_int, int_base + line_penalty_code);

  primitive(/*1449:*/
            324
/*:1449*/
            ,
            assign_int, int_base + hyphen_penalty_code);

  primitive(/*1450:*/
            325
/*:1450*/
            ,
            assign_int, int_base + ex_hyphen_penalty_code);

  primitive(/*1451:*/
            326
/*:1451*/
            ,
            assign_int, int_base + club_penalty_code);

  primitive(/*1452:*/
            327
/*:1452*/
            ,
            assign_int, int_base + widow_penalty_code);

  primitive(/*1453:*/
            328
/*:1453*/
            ,
            assign_int, int_base + display_widow_penalty_code);

  primitive(/*1454:*/
            329
/*:1454*/
            ,
            assign_int, int_base + broken_penalty_code);

  primitive(/*1455:*/
            330
/*:1455*/
            ,
            assign_int, int_base + bin_op_penalty_code);

  primitive(/*1456:*/
            331
/*:1456*/
            ,
            assign_int, int_base + rel_penalty_code);

  primitive(/*1457:*/
            332
/*:1457*/
            ,
            assign_int, int_base + pre_display_penalty_code);

  primitive(/*1458:*/
            333
/*:1458*/
            ,
            assign_int, int_base + post_display_penalty_code);

  primitive(/*1459:*/
            334
/*:1459*/
            ,
            assign_int, int_base + inter_line_penalty_code);

  primitive(/*1460:*/
            335
/*:1460*/
            ,
            assign_int, int_base + double_hyphen_demerits_code);

  primitive(/*1461:*/
            336
/*:1461*/
            ,
            assign_int, int_base + final_hyphen_demerits_code);

  primitive(/*1462:*/
            337
/*:1462*/
            ,
            assign_int, int_base + adj_demerits_code);

  primitive(/*1463:*/
            338
/*:1463*/
            ,
            assign_int, int_base + mag_code);

  primitive(/*1464:*/
            339
/*:1464*/
            ,
            assign_int, int_base + delimiter_factor_code);

  primitive(/*1465:*/
            340
/*:1465*/
            ,
            assign_int, int_base + looseness_code);

  primitive(/*1466:*/
            341
/*:1466*/
            ,
            assign_int, int_base + time_code);

  primitive(/*1467:*/
            342
/*:1467*/
            ,
            assign_int, int_base + day_code);

  primitive(/*1468:*/
            343
/*:1468*/
            ,
            assign_int, int_base + month_code);

  primitive(/*1469:*/
            344
/*:1469*/
            ,
            assign_int, int_base + year_code);

  primitive(/*1470:*/
            345
/*:1470*/
            ,
            assign_int, int_base + show_box_breadth_code);

  primitive(/*1471:*/
            346
/*:1471*/
            ,
            assign_int, int_base + show_box_depth_code);

  primitive(/*1472:*/
            347
/*:1472*/
            ,
            assign_int, int_base + hbadness_code);

  primitive(/*1473:*/
            348
/*:1473*/
            ,
            assign_int, int_base + vbadness_code);

  primitive(/*1474:*/
            349
/*:1474*/
            ,
            assign_int, int_base + pausing_code);

  primitive(/*1475:*/
            350
/*:1475*/
            ,
            assign_int, int_base + tracing_online_code);

  primitive(/*1476:*/
            351
/*:1476*/
            ,
            assign_int, int_base + tracing_macros_code);

  primitive(/*1477:*/
            352
/*:1477*/
            ,
            assign_int, int_base + tracing_stats_code);

  primitive(/*1478:*/
            353
/*:1478*/
            ,
            assign_int, int_base + tracing_paragraphs_code);

  primitive(/*1479:*/
            354
/*:1479*/
            ,
            assign_int, int_base + tracing_pages_code);

  primitive(/*1480:*/
            355
/*:1480*/
            ,
            assign_int, int_base + tracing_output_code);

  primitive(/*1481:*/
            356
/*:1481*/
            ,
            assign_int, int_base + tracing_lost_chars_code);

  primitive(/*1482:*/
            357
/*:1482*/
            ,
            assign_int, int_base + tracing_commands_code);

  primitive(/*1483:*/
            358
/*:1483*/
            ,
            assign_int, int_base + tracing_restores_code);

  primitive(/*1484:*/
            359
/*:1484*/
            ,
            assign_int, int_base + uc_hyph_code);

  primitive(/*1485:*/
            360
/*:1485*/
            ,
            assign_int, int_base + output_penalty_code);

  primitive(/*1486:*/
            361
/*:1486*/
            ,
            assign_int, int_base + max_dead_cycles_code);

  primitive(/*1487:*/
            362
/*:1487*/
            ,
            assign_int, int_base + hang_after_code);

  primitive(/*1488:*/
            363
/*:1488*/
            ,
            assign_int, int_base + floating_penalty_code);

  primitive(/*1489:*/
            364
/*:1489*/
            ,
            assign_int, int_base + global_defs_code);

  primitive(/*1490:*/
            365
/*:1490*/
            ,
            assign_int, int_base + cur_fam_code);

  primitive(/*1491:*/
            366
/*:1491*/
            ,
            assign_int, int_base + escape_char_code);

  primitive(/*1492:*/
            367
/*:1492*/
            ,
            assign_int, int_base + default_hyphen_char_code);

  primitive(/*1493:*/
            368
/*:1493*/
            ,
            assign_int, int_base + default_skew_char_code);

  primitive(/*1494:*/
            369
/*:1494*/
            ,
            assign_int, int_base + end_line_char_code);

  primitive(/*1495:*/
            370
/*:1495*/
            ,
            assign_int, int_base + new_line_char_code);

  primitive(/*1496:*/
            371
/*:1496*/
            ,
            assign_int, int_base + language_code);

  primitive(/*1497:*/
            372
/*:1497*/
            ,
            assign_int, int_base + left_hyphen_min_code);

  primitive(/*1498:*/
            373
/*:1498*/
            ,
            assign_int, int_base + right_hyphen_min_code);

  primitive(/*1499:*/
            374
/*:1499*/
            ,
            assign_int, int_base + holding_inserts_code);

  primitive(/*1500:*/
            375
/*:1500*/
            ,
            assign_int, int_base + error_context_lines_code);

/*:238*/ /*248:*/

  primitive(/*1503:*/
            378
/*:1503*/
            ,
            assign_dimen, dimen_base + par_indent_code);

  primitive(/*1504:*/
            379
/*:1504*/
            ,
            assign_dimen, dimen_base + math_surround_code);

  primitive(/*1505:*/
            380
/*:1505*/
            ,
            assign_dimen, dimen_base + line_skip_limit_code);

  primitive(/*1506:*/
            381
/*:1506*/
            ,
            assign_dimen, dimen_base + hsize_code);

  primitive(/*1507:*/
            382
/*:1507*/
            ,
            assign_dimen, dimen_base + vsize_code);

  primitive(/*1508:*/
            383
/*:1508*/
            ,
            assign_dimen, dimen_base + max_depth_code);

  primitive(/*1509:*/
            384
/*:1509*/
            ,
            assign_dimen, dimen_base + split_max_depth_code);

  primitive(/*1510:*/
            385
/*:1510*/
            ,
            assign_dimen, dimen_base + box_max_depth_code);

  primitive(/*1511:*/
            386
/*:1511*/
            ,
            assign_dimen, dimen_base + hfuzz_code);

  primitive(/*1512:*/
            387
/*:1512*/
            ,
            assign_dimen, dimen_base + vfuzz_code);

  primitive(/*1513:*/
            388
/*:1513*/
            ,
            assign_dimen, dimen_base + delimiter_shortfall_code);

  primitive(/*1514:*/
            389
/*:1514*/
            ,
            assign_dimen, dimen_base + null_delimiter_space_code);

  primitive(/*1515:*/
            390
/*:1515*/
            ,
            assign_dimen, dimen_base + script_space_code);

  primitive(/*1516:*/
            391
/*:1516*/
            ,
            assign_dimen, dimen_base + pre_display_size_code);

  primitive(/*1517:*/
            392
/*:1517*/
            ,
            assign_dimen, dimen_base + display_width_code);

  primitive(/*1518:*/
            393
/*:1518*/
            ,
            assign_dimen, dimen_base + display_indent_code);

  primitive(/*1519:*/
            394
/*:1519*/
            ,
            assign_dimen, dimen_base + overfull_rule_code);

  primitive(/*1520:*/
            395
/*:1520*/
            ,
            assign_dimen, dimen_base + hang_indent_code);

  primitive(/*1521:*/
            396
/*:1521*/
            ,
            assign_dimen, dimen_base + h_offset_code);

  primitive(/*1522:*/
            397
/*:1522*/
            ,
            assign_dimen, dimen_base + v_offset_code);

  primitive(/*1523:*/
            398
/*:1523*/
            ,
            assign_dimen, dimen_base + emergency_stretch_code);

/*:248*/ /*265:*/

  primitive(' ', ex_space, 0);

  primitive('/', ital_corr, 0);

  primitive(/*1530:*/
            405
/*:1530*/
            ,
            accent, 0);

  primitive(/*1531:*/
            406
/*:1531*/
            ,
            advance, 0);

  primitive(/*1532:*/
            407
/*:1532*/
            ,
            after_assignment, 0);

  primitive(/*1533:*/
            408
/*:1533*/
            ,
            after_group, 0);

  primitive(/*1534:*/
            409
/*:1534*/
            ,
            begin_group, 0);

  primitive(/*1535:*/
            410
/*:1535*/
            ,
            char_num, 0);

  primitive(/*1526:*/
            401
/*:1526*/
            ,
            cs_name, 0);

  primitive(/*1536:*/
            411
/*:1536*/
            ,
            delim_num, 0);

  primitive(/*1537:*/
            412
/*:1537*/
            ,
            divide, 0);

  primitive(/*1527:*/
            402
/*:1527*/
            ,
            end_cs_name, 0);

  primitive(/*1538:*/
            413
/*:1538*/
            ,
            end_group, 0);

  text(frozen_end_group) = /*1538:*/
      413
/*:1538*/
      ;
  eqtb[frozen_end_group] = eqtb[cur_val];
  primitive(/*1539:*/
            414
/*:1539*/
            ,
            expand_after, 0);

  primitive(/*1540:*/
            415
/*:1540*/
            ,
            def_font, 0);

  primitive(/*1541:*/
            416
/*:1541*/
            ,
            assign_font_dimen, 0);

  primitive(/*1542:*/
            417
/*:1542*/
            ,
            halign, 0);

  primitive(/*1543:*/
            418
/*:1543*/
            ,
            hrule, 0);

  primitive(/*1544:*/
            419
/*:1544*/
            ,
            ignore_spaces, 0);

  primitive(/*1390:*/
            265
/*:1390*/
            ,
            insert, 0);

  primitive(/*1401:*/
            276
/*:1401*/
            ,
            mark, 0);

  primitive(/*1545:*/
            420
/*:1545*/
            ,
            math_accent, 0);

  primitive(/*1546:*/
            421
/*:1546*/
            ,
            math_char_num, 0);

  primitive(/*1547:*/
            422
/*:1547*/
            ,
            math_choice, 0);

  primitive(/*1548:*/
            423
/*:1548*/
            ,
            multiply, 0);

  primitive(/*1549:*/
            424
/*:1549*/
            ,
            no_align, 0);

  primitive(/*1550:*/
            425
/*:1550*/
            ,
            no_boundary, 0);

  primitive(/*1551:*/
            426
/*:1551*/
            ,
            no_expand, 0);

  primitive(/*1392:*/
            267
/*:1392*/
            ,
            non_script, 0);

  primitive(/*1552:*/
            427
/*:1552*/
            ,
            omit, 0);

  primitive(/*1436:*/
            311
/*:1436*/
            ,
            set_shape, 0);

  primitive(/*1553:*/
            428
/*:1553*/
            ,
            break_penalty, 0);

  primitive(/*1554:*/
            429
/*:1554*/
            ,
            set_prev_graf, 0);

  primitive(/*1555:*/
            430
/*:1555*/
            ,
            radical, 0);

  primitive(/*1556:*/
            431
/*:1556*/
            ,
            read_to_cs, 0);

  primitive(/*1557:*/
            432
/*:1557*/
            ,
            relax, 256);

  text(frozen_relax) = /*1557:*/
      432
/*:1557*/
      ;
  eqtb[frozen_relax] = eqtb[cur_val];
  primitive(/*1558:*/
            433
/*:1558*/
            ,
            set_box, 0);

  primitive(/*1559:*/
            434
/*:1559*/
            ,
            the, 0);

  primitive(/*1435:*/
            310
/*:1435*/
            ,
            toks_register, 0);

  primitive(/*1402:*/
            277
/*:1402*/
            ,
            vadjust, 0);

  primitive(/*1560:*/
            435
/*:1560*/
            ,
            valign, 0);

  primitive(/*1561:*/
            436
/*:1561*/
            ,
            vcenter, 0);

  primitive(/*1562:*/
            437
/*:1562*/
            ,
            vrule, 0);

/*:265*/ /*334:*/

  primitive(/*1569:*/
            444
/*:1569*/
            ,
            par_end, 256);

  par_loc = cur_val;
  par_token = cs_token_flag + par_loc;

/*:334*/ /*376:*/

  primitive(/*1570:*/
            445
/*:1570*/
            ,
            input, 0);

  primitive(/*1571:*/
            446
/*:1571*/
            ,
            input, 1);

/*:376*/ /*384:*/

  primitive(/*1572:*/
            447
/*:1572*/
            ,
            top_bot_mark, top_mark_code);

  primitive(/*1573:*/
            448
/*:1573*/
            ,
            top_bot_mark, first_mark_code);

  primitive(/*1574:*/
            449
/*:1574*/
            ,
            top_bot_mark, bot_mark_code);

  primitive(/*1575:*/
            450
/*:1575*/
            ,
            top_bot_mark, split_first_mark_code);

  primitive(/*1576:*/
            451
/*:1576*/
            ,
            top_bot_mark, split_bot_mark_code);

/*:384*/ /*411:*/

  primitive(/*1501:*/
            376
/*:1501*/
            ,
            register, int_val);

  primitive(/*1524:*/
            399
/*:1524*/
            ,
            register, dimen_val);

  primitive(/*1423:*/
            298
/*:1423*/
            ,
            register, glue_val);

  primitive(/*1424:*/
            299
/*:1424*/
            ,
            register, mu_val);

/*:411*/ /*416:*/

  primitive(/*1577:*/
            452
/*:1577*/
            ,
            set_aux, hmode);

  primitive(/*1578:*/
            453
/*:1578*/
            ,
            set_aux, vmode);

  primitive(/*1579:*/
            454
/*:1579*/
            ,
            set_page_int, 0);

  primitive(/*1580:*/
            455
/*:1580*/
            ,
            set_page_int, 1);

  primitive(/*1581:*/
            456
/*:1581*/
            ,
            set_box_dimen, width_offset);

  primitive(/*1582:*/
            457
/*:1582*/
            ,
            set_box_dimen, height_offset);

  primitive(/*1583:*/
            458
/*:1583*/
            ,
            set_box_dimen, depth_offset);

  primitive(/*1584:*/
            459
/*:1584*/
            ,
            last_item, int_val);

  primitive(/*1585:*/
            460
/*:1585*/
            ,
            last_item, dimen_val);

  primitive(/*1586:*/
            461
/*:1586*/
            ,
            last_item, glue_val);

  primitive(/*1587:*/
            462
/*:1587*/
            ,
            last_item, input_line_no_code);

  primitive(/*1588:*/
            463
/*:1588*/
            ,
            last_item, badness_code);

/*:416*/ /*468:*/

  primitive(/*1605:*/
            480
/*:1605*/
            ,
            convert, number_code);

  primitive(/*1606:*/
            481
/*:1606*/
            ,
            convert, roman_numeral_code);

  primitive(/*1607:*/
            482
/*:1607*/
            ,
            convert, string_code);

  primitive(/*1608:*/
            483
/*:1608*/
            ,
            convert, meaning_code);

  primitive(/*1609:*/
            484
/*:1609*/
            ,
            convert, font_name_code);

  primitive(/*1610:*/
            485
/*:1610*/
            ,
            convert, job_name_code);

/*:468*/ /*487:*/

  primitive(/*1611:*/
            486
/*:1611*/
            ,
            if_test, if_char_code);

  primitive(/*1612:*/
            487
/*:1612*/
            ,
            if_test, if_cat_code);

  primitive(/*1613:*/
            488
/*:1613*/
            ,
            if_test, if_int_code);

  primitive(/*1614:*/
            489
/*:1614*/
            ,
            if_test, if_dim_code);

  primitive(/*1615:*/
            490
/*:1615*/
            ,
            if_test, if_odd_code);

  primitive(/*1616:*/
            491
/*:1616*/
            ,
            if_test, if_vmode_code);

  primitive(/*1617:*/
            492
/*:1617*/
            ,
            if_test, if_hmode_code);

  primitive(/*1618:*/
            493
/*:1618*/
            ,
            if_test, if_mmode_code);

  primitive(/*1619:*/
            494
/*:1619*/
            ,
            if_test, if_inner_code);

  primitive(/*1620:*/
            495
/*:1620*/
            ,
            if_test, if_void_code);

  primitive(/*1621:*/
            496
/*:1621*/
            ,
            if_test, if_hbox_code);

  primitive(/*1622:*/
            497
/*:1622*/
            ,
            if_test, if_vbox_code);

  primitive(/*1623:*/
            498
/*:1623*/
            ,
            if_test, ifx_code);

  primitive(/*1624:*/
            499
/*:1624*/
            ,
            if_test, if_eof_code);

  primitive(/*1625:*/
            500
/*:1625*/
            ,
            if_test, if_true_code);

  primitive(/*1626:*/
            501
/*:1626*/
            ,
            if_test, if_false_code);

  primitive(/*1627:*/
            502
/*:1627*/
            ,
            if_test, if_case_code);

/*:487*/ /*491:*/

  primitive(/*1628:*/
            503
/*:1628*/
            ,
            fi_or_else, fi_code);

  text(frozen_fi) = /*1628:*/
      503
/*:1628*/
      ;
  eqtb[frozen_fi] = eqtb[cur_val];
  primitive(/*1629:*/
            504
/*:1629*/
            ,
            fi_or_else, or_code);

  primitive(/*1630:*/
            505
/*:1630*/
            ,
            fi_or_else, else_code);

/*:491*/ /*553:*/

  primitive(/*1639:*/
            514
/*:1639*/
            ,
            set_font, null_font);

  text(frozen_null_font) = /*1639:*/
      514
/*:1639*/
      ;
  eqtb[frozen_null_font] = eqtb[cur_val];

/*:553*/ /*780:*/

  primitive(/*1669:*/
            544
/*:1669*/
            ,
            tab_mark, span_code);

  primitive(/*1670:*/
            545
/*:1670*/
            ,
            car_ret, cr_code);

  text(frozen_cr) = /*1670:*/
      545
/*:1670*/
      ;
  eqtb[frozen_cr] = eqtb[cur_val];
  primitive(/*1671:*/
            546
/*:1671*/
            ,
            car_ret, cr_cr_code);

  text(frozen_end_template) = /*1672:*/
      547
/*:1672*/
      ;
  text(frozen_endv) = /*1672:*/
      547
/*:1672*/
      ;

  eq_type(frozen_endv) = endv;
  equiv(frozen_endv) = null_list;
  eq_level(frozen_endv) = level_one;
  eqtb[frozen_end_template] = eqtb[frozen_endv];
  eq_type(frozen_end_template) = end_template;

/*:780*/ /*983:*/

  primitive(/*1689:*/
            564
/*:1689*/
            ,
            set_page_dimen, 0);

  primitive(/*1690:*/
            565
/*:1690*/
            ,
            set_page_dimen, 1);

  primitive(/*1691:*/
            566
/*:1691*/
            ,
            set_page_dimen, 2);

  primitive(/*1692:*/
            567
/*:1692*/
            ,
            set_page_dimen, 3);

  primitive(/*1693:*/
            568
/*:1693*/
            ,
            set_page_dimen, 4);

  primitive(/*1694:*/
            569
/*:1694*/
            ,
            set_page_dimen, 5);

  primitive(/*1695:*/
            570
/*:1695*/
            ,
            set_page_dimen, 6);

  primitive(/*1696:*/
            571
/*:1696*/
            ,
            set_page_dimen, 7);

/*:983*/ /*1052:*/

  primitive(/*1698:*/
            573
/*:1698*/
            ,
            stop, 0);

  primitive(/*1699:*/
            574
/*:1699*/
            ,
            stop, 1);

/*:1052*/ /*1058:*/

  primitive(/*1700:*/
            575
/*:1700*/
            ,
            hskip, skip_code);

  primitive(/*1701:*/
            576
/*:1701*/
            ,
            hskip, fil_code);

  primitive(/*1702:*/
            577
/*:1702*/
            ,
            hskip, fill_code);

  primitive(/*1703:*/
            578
/*:1703*/
            ,
            hskip, ss_code);

  primitive(/*1704:*/
            579
/*:1704*/
            ,
            hskip, fil_neg_code);

  primitive(/*1705:*/
            580
/*:1705*/
            ,
            vskip, skip_code);

  primitive(/*1706:*/
            581
/*:1706*/
            ,
            vskip, fil_code);

  primitive(/*1707:*/
            582
/*:1707*/
            ,
            vskip, fill_code);

  primitive(/*1708:*/
            583
/*:1708*/
            ,
            vskip, ss_code);

  primitive(/*1709:*/
            584
/*:1709*/
            ,
            vskip, fil_neg_code);

  primitive(/*1393:*/
            268
/*:1393*/
            ,
            mskip, mskip_code);

  primitive(/*1396:*/
            271
/*:1396*/
            ,
            kern, explicit);

  primitive(/*1397:*/
            272
/*:1397*/
            ,
            mkern, mu_glue);

/*:1058*/ /*1071:*/

  primitive(/*1712:*/
            587
/*:1712*/
            ,
            hmove, 1);

  primitive(/*1713:*/
            588
/*:1713*/
            ,
            hmove, 0);

  primitive(/*1714:*/
            589
/*:1714*/
            ,
            vmove, 1);

  primitive(/*1715:*/
            590
/*:1715*/
            ,
            vmove, 0);

  primitive(/*1437:*/
            312
/*:1437*/
            ,
            make_box, box_code);

  primitive(/*1716:*/
            591
/*:1716*/
            ,
            make_box, copy_code);

  primitive(/*1717:*/
            592
/*:1717*/
            ,
            make_box, last_box_code);

  primitive(/*1687:*/
            562
/*:1687*/
            ,
            make_box, vsplit_code);

  primitive(/*1718:*/
            593
/*:1718*/
            ,
            make_box, vtop_code);

  primitive(/*1688:*/
            563
/*:1688*/
            ,
            make_box, vtop_code + vmode);

  primitive(/*1719:*/
            594
/*:1719*/
            ,
            make_box, vtop_code + hmode);

  primitive(/*1720:*/
            595
/*:1720*/
            ,
            leader_ship, a_leaders - 1);

  primitive(/*1721:*/
            596
/*:1721*/
            ,
            leader_ship, a_leaders);

  primitive(/*1722:*/
            597
/*:1722*/
            ,
            leader_ship, c_leaders);

  primitive(/*1723:*/
            598
/*:1723*/
            ,
            leader_ship, x_leaders);

/*:1071*/ /*1088:*/

  primitive(/*1724:*/
            599
/*:1724*/
            ,
            start_par, 1);

  primitive(/*1725:*/
            600
/*:1725*/
            ,
            start_par, 0);

/*:1088*/ /*1107:*/

  primitive(/*1726:*/
            601
/*:1726*/
            ,
            remove_item, penalty_node);

  primitive(/*1727:*/
            602
/*:1727*/
            ,
            remove_item, kern_node);

  primitive(/*1728:*/
            603
/*:1728*/
            ,
            remove_item, glue_node);

  primitive(/*1729:*/
            604
/*:1729*/
            ,
            un_hbox, box_code);

  primitive(/*1730:*/
            605
/*:1730*/
            ,
            un_hbox, copy_code);

  primitive(/*1731:*/
            606
/*:1731*/
            ,
            un_vbox, box_code);

  primitive(/*1732:*/
            607
/*:1732*/
            ,
            un_vbox, copy_code);

/*:1107*/ /*1114:*/

  primitive('-', discretionary, 1);

  primitive(/*1400:*/
            275
/*:1400*/
            ,
            discretionary, 0);

/*:1114*/ /*1141:*/

  primitive(/*1733:*/
            608
/*:1733*/
            ,
            eq_no, 0);

  primitive(/*1734:*/
            609
/*:1734*/
            ,
            eq_no, 1);

/*:1141*/ /*1156:*/

  primitive(/*1649:*/
            524
/*:1649*/
            ,
            math_comp, ord_noad);

  primitive(/*1650:*/
            525
/*:1650*/
            ,
            math_comp, op_noad);

  primitive(/*1651:*/
            526
/*:1651*/
            ,
            math_comp, bin_noad);

  primitive(/*1652:*/
            527
/*:1652*/
            ,
            math_comp, rel_noad);

  primitive(/*1653:*/
            528
/*:1653*/
            ,
            math_comp, open_noad);

  primitive(/*1654:*/
            529
/*:1654*/
            ,
            math_comp, close_noad);

  primitive(/*1655:*/
            530
/*:1655*/
            ,
            math_comp, punct_noad);

  primitive(/*1656:*/
            531
/*:1656*/
            ,
            math_comp, inner_noad);

  primitive(/*1658:*/
            533
/*:1658*/
            ,
            math_comp, under_noad);

  primitive(/*1657:*/
            532
/*:1657*/
            ,
            math_comp, over_noad);

  primitive(/*1735:*/
            610
/*:1735*/
            ,
            limit_switch, normal);

  primitive(/*1661:*/
            536
/*:1661*/
            ,
            limit_switch, limits);

  primitive(/*1662:*/
            537
/*:1662*/
            ,
            limit_switch, no_limits);

/*:1156*/ /*1169:*/

  primitive(/*1645:*/
            520
/*:1645*/
            ,
            math_style, display_style);

  primitive(/*1646:*/
            521
/*:1646*/
            ,
            math_style, text_style);

  primitive(/*1647:*/
            522
/*:1647*/
            ,
            math_style, script_style);

  primitive(/*1648:*/
            523
/*:1648*/
            ,
            math_style, script_script_style);

/*:1169*/ /*1178:*/

  primitive(/*1736:*/
            611
/*:1736*/
            ,
            above, above_code);

  primitive(/*1737:*/
            612
/*:1737*/
            ,
            above, over_code);

  primitive(/*1738:*/
            613
/*:1738*/
            ,
            above, atop_code);

  primitive(/*1739:*/
            614
/*:1739*/
            ,
            above, delimited_code + above_code);

  primitive(/*1740:*/
            615
/*:1740*/
            ,
            above, delimited_code + over_code);

  primitive(/*1741:*/
            616
/*:1741*/
            ,
            above, delimited_code + atop_code);

/*:1178*/ /*1188:*/

  primitive(/*1659:*/
            534
/*:1659*/
            ,
            left_right, left_noad);

  primitive(/*1660:*/
            535
/*:1660*/
            ,
            left_right, right_noad);

  text(frozen_right) = /*1660:*/
      535
/*:1660*/
      ;
  eqtb[frozen_right] = eqtb[cur_val];

/*:1188*/ /*1208:*/

  primitive(/*1743:*/
            618
/*:1743*/
            ,
            prefix, 1);

  primitive(/*1744:*/
            619
/*:1744*/
            ,
            prefix, 2);

  primitive(/*1745:*/
            620
/*:1745*/
            ,
            prefix, 4);

  primitive(/*1746:*/
            621
/*:1746*/
            ,
            def, 0);

  primitive(/*1747:*/
            622
/*:1747*/
            ,
            def, 1);

  primitive(/*1748:*/
            623
/*:1748*/
            ,
            def, 2);

  primitive(/*1749:*/
            624
/*:1749*/
            ,
            def, 3);

/*:1208*/ /*1219:*/

  primitive(/*1752:*/
            627
/*:1752*/
            ,
            let, normal);

  primitive(/*1753:*/
            628
/*:1753*/
            ,
            let, normal + 1);

/*:1219*/ /*1222:*/

  primitive(/*1754:*/
            629
/*:1754*/
            ,
            shorthand_def, char_def_code);

  primitive(/*1755:*/
            630
/*:1755*/
            ,
            shorthand_def, math_char_def_code);

  primitive(/*1756:*/
            631
/*:1756*/
            ,
            shorthand_def, count_def_code);

  primitive(/*1757:*/
            632
/*:1757*/
            ,
            shorthand_def, dimen_def_code);

  primitive(/*1758:*/
            633
/*:1758*/
            ,
            shorthand_def, skip_def_code);

  primitive(/*1759:*/
            634
/*:1759*/
            ,
            shorthand_def, mu_skip_def_code);

  primitive(/*1760:*/
            635
/*:1760*/
            ,
            shorthand_def, toks_def_code);

/*:1222*/ /*1230:*/

  primitive(/*1441:*/
            316
/*:1441*/
            ,
            def_code, cat_code_base);

  primitive(/*1445:*/
            320
/*:1445*/
            ,
            def_code, math_code_base);

  primitive(/*1442:*/
            317
/*:1442*/
            ,
            def_code, lc_code_base);

  primitive(/*1443:*/
            318
/*:1443*/
            ,
            def_code, uc_code_base);

  primitive(/*1444:*/
            319
/*:1444*/
            ,
            def_code, sf_code_base);

  primitive(/*1502:*/
            377
/*:1502*/
            ,
            def_code, del_code_base);

  primitive(/*1438:*/
            313
/*:1438*/
            ,
            def_family, math_font_base);

  primitive(/*1439:*/
            314
/*:1439*/
            ,
            def_family, math_font_base + script_size);

  primitive(/*1440:*/
            315
/*:1440*/
            ,
            def_family, math_font_base + script_script_size);

/*:1230*/ /*1250:*/

  primitive(/*1683:*/
            558
/*:1683*/
            ,
            hyph_data, 0);

  primitive(/*1684:*/
            559
/*:1684*/
            ,
            hyph_data, 1);

/*:1250*/ /*1254:*/

  primitive(/*1762:*/
            637
/*:1762*/
            ,
            assign_font_int, 0);

  primitive(/*1763:*/
            638
/*:1763*/
            ,
            assign_font_int, 1);

/*:1254*/ /*1262:*/

  primitive(/*1383:*/
            258
/*:1383*/
            ,
            set_interaction, batch_mode);

  primitive(/*1384:*/
            259
/*:1384*/
            ,
            set_interaction, nonstop_mode);

  primitive(/*1385:*/
            260
/*:1385*/
            ,
            set_interaction, scroll_mode);

  primitive(/*1767:*/
            642
/*:1767*/
            ,
            set_interaction, error_stop_mode);

/*:1262*/ /*1272:*/

  primitive(/*1768:*/
            643
/*:1768*/
            ,
            in_stream, 1);

  primitive(/*1769:*/
            644
/*:1769*/
            ,
            in_stream, 0);

/*:1272*/ /*1277:*/

  primitive(/*1770:*/
            645
/*:1770*/
            ,
            message, 0);

  primitive(/*1771:*/
            646
/*:1771*/
            ,
            message, 1);

/*:1277*/ /*1286:*/

  primitive(/*1772:*/
            647
/*:1772*/
            ,
            case_shift, lc_code_base);

  primitive(/*1773:*/
            648
/*:1773*/
            ,
            case_shift, uc_code_base);

/*:1286*/ /*1291:*/

  primitive(/*1774:*/
            649
/*:1774*/
            ,
            xray, show_code);

  primitive(/*1775:*/
            650
/*:1775*/
            ,
            xray, show_box_code);

  primitive(/*1776:*/
            651
/*:1776*/
            ,
            xray, show_the_code);

  primitive(/*1777:*/
            652
/*:1777*/
            ,
            xray, show_lists_code);

/*:1291*/ /*1344:*/

  primitive(/*1783:*/
            658
/*:1783*/
            ,
            extension, open_node);

  primitive(/*1568:*/
            443
/*:1568*/
            ,
            extension, write_node);
  write_loc = cur_val;

  primitive(/*1784:*/
            659
/*:1784*/
            ,
            extension, close_node);

  primitive(/*1785:*/
            660
/*:1785*/
            ,
            extension, special_node);

  primitive(/*1786:*/
            661
/*:1786*/
            ,
            extension, immediate_code);

  primitive(/*1787:*/
            662
/*:1787*/
            ,
            extension, set_language_code);

/*:1344*/
  ;
  no_new_control_sequence = true;
}
#endif

/*:1336*/ /*1338:*/

#ifdef DEBUG
void debug_help(void) {
  int k, l, m, n;
  clear_terminal;
  loop {
    wake_up_terminal;
    print_nl("debug # (-1 to exit):");
    update_terminal;

    if (fscanf(term_in.f, " %d", &m) < 1 || m < 0)
      return;
    else if (m == 0) {
      goto breakpoint;
    breakpoint:
      m = 0;
    } else {
      fscanf(term_in.f, " %d", &n);
      switch (m) {
/*1339:*/

        case 1:
          print_word(mem[n]);
          break;
        case 2:
          print_int(info(n));
          break;
        case 3:
          print_int(link(n));
          break;
        case 4:
          print_word(eqtb[n]);
          break;
        case 5:
          print_word(font_info[n]);
          break;
        case 6:
          print_word(save_stack[n]);
          break;
        case 7:
          show_box(n);
          break;

        case 8: {
          breadth_max = 10000;
          depth_threshold = pool_size - pool_ptr - 10;
          show_node_list(n);
        } break;
        case 9:
          show_token_list(n, null, 1000);
          break;
        case 10:
          slow_print(n);
          break;
        case 11:
          check_mem(n > 0);
          break;
        case 12:
          search_mem(n);
          break;
        case 13: {
          fscanf(term_in.f, " %d", &l);
          print_cmd_chr(n, l);
        } break;
        case 14:
          for (k = 0; k <= n; k++) print(buffer[k]);
          break;
        case 15: {
          font_in_short_display = null_font;
          short_display(n);
        } break;
        case 16:
          panicking = !panicking;
          break;

/*:1339*/

        default:
          print_str("?");
      }
    }
  }
}
#endif

/*:1338*/

/*:1330*/ /*1332:*/
int main(void) {
  history = fatal_error_stop;
  t_open_out;
  if (ready_already == 314159) goto start_of_TEX;
/*14:*/

  bad = 0;
  if ((half_error_line < 30) || (half_error_line > error_line - 15)) bad = 1;
  if (max_print_line < 60) bad = 2;
  if (dvi_buf_size % 8 != 0) bad = 3;
  if (mem_bot + 1100 > mem_top) bad = 4;
  if (hash_prime > hash_size) bad = 5;
  if (max_in_open >= 128) bad = 6;
  if (mem_top < 256 + 11) bad = 7;

/*:14*/ /*111:*/

#ifdef INIT
  if ((mem_min != mem_bot) || (mem_max != mem_top)) bad = 10;
#endif

  if ((mem_min > mem_bot) || (mem_max < mem_top)) bad = 10;
  if ((min_quarterword > 0) || (max_quarterword < 127)) bad = 11;
  if ((min_halfword > 0) || (max_halfword < 32767)) bad = 12;
  if ((min_quarterword < min_halfword) || (max_quarterword > max_halfword))
    bad = 13;
  if ((mem_min < min_halfword) || (mem_max >= max_halfword) ||
      (mem_bot - mem_min > max_halfword + 1))
    bad = 14;
  if ((font_base < min_quarterword) || (font_max > max_quarterword)) bad = 15;
  if (font_max > font_base + 256) bad = 16;
  if ((save_size > max_halfword) || (max_strings > max_halfword)) bad = 17;
  if (buf_size > max_halfword) bad = 18;
  if (max_quarterword - min_quarterword < 255) bad = 19;

/*:111*/ /*290:*/

  if (cs_token_flag + undefined_control_sequence > max_halfword) bad = 21;

/*:290*/ /*521:*/

  if (format_default_length > file_name_size) bad = 31;

/*:521*/ /*1249:*/

  if (2 * max_halfword < mem_top - mem_min) bad = 41;

/*:1249*/

  if (bad > 0) {
    wterm_ln(
        "Ouch---my internal constants have been clobbered!"
        "---case %d",
        bad);

    exit(0);
  }
  initialize();
#ifdef INIT
  init_prim();
  init_str_ptr = str_ptr;
  init_pool_ptr = pool_ptr;
  fix_date_and_time();
#endif
  ready_already = 314159;
start_of_TEX: /*55:*/

  selector = term_only;
  tally = 0;
  term_offset = 0;
  file_offset = 0;

/*:55*/ /*61:*/

  wterm("%s", banner);
  if (format_ident == 0)
    wterm_ln(" (no format preloaded)");
  else {
    slow_print(format_ident);
    print_ln();
  }
  update_terminal;

/*:61*/ /*527:*/

  job_name = 0;
  name_in_progress = false;
  log_opened = false;

/*:527*/ /*533:*/
  output_file_name = 0;

/*:533*/
  ;
/*1337:*/

  { /*331:*/

    {
      input_ptr = 0;
      max_in_stack = 0;
      in_open = 0;
      open_parens = 0;
      max_buf_stack = 0;
      param_ptr = 0;
      max_param_stack = 0;
      first = buf_size;
      do {
        buffer[first] = 0;
        decr(first);
      } while (!(first == 0));
      scanner_status = normal;
      warning_index = null;
      first = 1;
      state = new_line;
      start = 1;
      index = 0;
      line = 0;
      name = 0;
      force_eof = false;
      align_state = 1000000;
      if (!init_terminal()) exit(0);
      limit = last;
      first = last + 1;
    }

/*:331*/
    ;
    if ((format_ident == 0) || (buffer[loc] == '&')) {
      if (format_ident != 0) initialize();
      if (!open_fmt_file()) exit(0);
      if (!load_fmt_file()) {
        w_close(&fmt_file);
        exit(0);
      }
      w_close(&fmt_file);
      while ((loc < limit) && (buffer[loc] == ' ')) incr(loc);
    }
    if (end_line_char_inactive)
      decr(limit);
    else
      buffer[limit] = end_line_char;
    fix_date_and_time();
/*765:*/

    magic_offset = str_start[math_spacing] - 9 * ord_noad

/*:765*/
        ;
/*75:*/

    if (interaction == batch_mode)
      selector = no_print;
    else
      selector = term_only

/*:75*/
          ;
    if ((loc < limit) && (cat_code(buffer[loc]) != escape)) start_input();
  }

/*:1337*/
  ;
  history = spotless;
  main_control();
  final_cleanup();
  close_files_and_terminate();
  ready_already = 0;
  return 0;
}

/*:1332*/
