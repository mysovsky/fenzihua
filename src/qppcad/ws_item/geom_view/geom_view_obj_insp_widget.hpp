#ifndef QPPCAD_WS_ATOMS_LIST_OBJ_INSP_H
#define QPPCAD_WS_ATOMS_LIST_OBJ_INSP_H

#include <qppcad/ws_item/ws_item_obj_insp_widget.hpp>
#include <qppcad/ws_item/geom_view/geom_view.hpp>
#include <qppcad/ui/qrealspinbox_delegate.hpp>
#include <qppcad/ui/qspoiler_widget.hpp>
//#include <qppcad/ws_item/geom_view/qtype_summary_model.hpp>

#include <QTableWidget>
#include <QTableView>
#include <QHeaderView>
#include <QSlider>
#include <QButtonGroup>

namespace qpp {

  namespace cad {

    class qtype_specific_rendering_model_t;
    class qbonding_table_model_t;
    class qxgeom_fields_model_t;

    class geom_view_obj_insp_widget_t final: public ws_item_obj_insp_widget_t {

      Q_OBJECT

      public:

        geom_view_t *b_al{nullptr}; // binded atoms list

        qspoiler_widget_t *tg_geom_summary_widget;
        QFormLayout *tg_geom_summary_lt;

        QLabel *tg_geom_summary_total_atoms;
        QLabel *tg_geom_summary_total_types;

        qspoiler_widget_t *tg_type_summary_widget;
        QVBoxLayout *tg_type_summary_lt;
        QTableWidget *tg_type_summary_tbl;
      //QTableView *tg_type_summary_tbl1;
        QPushButton *type_summary_clear_tclr_override;

        qspoiler_widget_t *tg_gb_cell;
        QVBoxLayout *tg_gb_cell_lt;
        QTableWidget *tg_gb_cell_tbl;

        //START: Display tab
        ws_item_tab_widget_t *tab_disp;

        QButtonGroup *tdisp_switch;

        qspoiler_widget_t *gb_disp_s;
        QFormLayout *gb_disp_s_lt;
        qbinded_checkbox_t *disp_s_draw_atoms;
        qbinded_checkbox_t *disp_s_draw_bonds;
        qbinded_checkbox_t *disp_s_draw_img_atoms;
        qbinded_checkbox_t *disp_s_draw_img_bonds;
        qbinded_float_spinbox_t *disp_s_atom_scale;
        qbinded_float_spinbox_t *disp_s_bond_scale;
        qbinded_combobox_t *disp_s_render_style;
        qbinded_combobox_t *disp_s_color_mode;

        qspoiler_widget_t *gb_disp_labels;
        QFormLayout *gb_disp_labels_lt;
        qbinded_combobox_t *disp_labels_style;
        qbinded_checkbox_t *disp_inplace_labels;
        qbinded_float2_input_t *disp_inplace_offset;
        qbinded_int_spinbox_t *disp_labels_size;
        qbinded_checkbox_t *disp_sl_labels;
        qbinded_checkbox_t *disp_labels_screen_scale;
        qbinded_checkbox_t *disp_labels_draw_outline;
        qbinded_float_spinbox_t *disp_labels_outline_size;

        qbinded_checkbox_t *disp_s_sel_vis;
        qbinded_checkbox_t *disp_s_sel_vis_affect_bonds;

        // Periodic related render
        qspoiler_widget_t *gb_periodic_related_render;
        QFormLayout *gb_periodic_related_render_lt;
        qbinded_checkbox_t *periodic_draw_cell_v;
        qbinded_float_spinbox_t *periodic_cell_v_ratio;
        qbinded_color3_input_t *periodic_cell_vectors_color;

        qbinded_checkbox_t *periodic_draw_cell;
        qbinded_color3_input_t *periodic_cell_color;
        qbinded_float3_input_t *periodic_cell_offset;
        qbinded_checkbox_t *periodic_draw_subcells;
        QLabel *periodic_subcells_idx_lbl;
        qbinded_int3_input_t *periodic_subcells_idx;
        QLabel *periodic_subcells_color_lbl;
        qbinded_color3_input_t *periodic_subcells_clr;
        // End of Periodic related render

        qspoiler_widget_t *gb_disp_shading;
        QFormLayout *gb_disp_shading_lt;
        qbinded_checkbox_t *disp_shading_spec;
        qbinded_float_spinbox_t *disp_shading_spec_value;

        qspoiler_widget_t *gb_disp_type_spec_rend;
        QTableView *disp_type_spec_tv;
        qtype_specific_rendering_model_t *disp_type_spec_mdl;
        QVBoxLayout *gb_disp_type_spec_rend_lt;

        qspoiler_widget_t *gb_disp_bt;
        QPushButton *disp_bt_rebond_btn;
        QVBoxLayout *disp_bt_lt;
        QTableView *disp_bt;
        qbonding_table_model_t *bt_mdl;
        qrealspinbox_delegate_t *bt_dist_delegate;
        //END: Display tab
        //asm
        //qtype_summary_model_t *ts_mdl;

        ws_item_tab_widget_t *tab_anim;
        qspoiler_widget_t *gb_anim_summary;
        QLabel *gb_anim_total_anims;
        qbinded_checkbox_t *gb_rebuild_bonds;
        qbinded_checkbox_t *gb_play_cyclic;
        qbinded_float_spinbox_t *gb_anim_speed;
        QComboBox *gb_current_anim;
        QHBoxLayout *anim_act_lt;
        QPushButton *anim_act_ren;
        QPushButton *anim_act_del;
        QFormLayout *gb_anim_summary_lt;

        qspoiler_widget_t *gb_anim_timeline;
        QHBoxLayout *gb_anim_timeline_lt;
        QLabel *gb_anim_total_frames_in_anim;
        QLabel *gb_anim_cur_frame;
        QSlider *gb_anim_timeline_slider;
        qspoiler_widget_t *gb_anim_buttons;
        QHBoxLayout *gb_anim_buttons_lt;

        QPushButton *anim_play;
        QPushButton *anim_to_start;
        QPushButton *anim_to_end;
        QPushButton *anim_frame_forward;
        QPushButton *anim_frame_backward;

        //START TAB MEASUREMENT
        ws_item_tab_widget_t *tab_measurement;

        QButtonGroup *tms_switch;

        //common measurements settings
        qspoiler_widget_t *tms_common_settings_gb;
        QFormLayout *tms_common_settings_gb_lt;
        qbinded_checkbox_t *tms_render_dist;
        qbinded_checkbox_t *tms_render_angle;
        qbinded_checkbox_t *tms_render_dist_legend;
        qbinded_checkbox_t *tms_render_angle_legend;

        //pair dist
        qspoiler_widget_t *tms_pair_dist_gb;
        QFormLayout *tms_pair_dist_gb_lt;
        QComboBox *tms_pair_cur_msr;
        QLabel *tms_pair_at1_info;
        QLabel *tms_pair_at2_info;
        QLabel *tms_pair_dist;

        qbinded_color3_input_t *tms_pair_dist_color;
        qbinded_checkbox_t *tms_pair_enabled;
        qbinded_checkbox_t *tms_pair_label_enabled;
        qbinded_combobox_t *tms_pair_line_style;
        qbinded_int_spinbox_t *tms_pair_line_size;
        qbinded_int_spinbox_t *tms_font_screen_size;
        qbinded_float_spinbox_t *tms_pair_delta_angle;
        qbinded_int2b_input_t *tms_pair_delta_offset;
        qbinded_combobox_t *tms_pair_label_style;
        qbinded_combobox_t *tms_pair_term_style;
        qbinded_int_spinbox_t *tms_pair_term_size;
        qbinded_line_edit_t *tms_pair_custom_text_edit;
        qbinded_checkbox_t *tms_pair_custom_text_enabled;

        QHBoxLayout *tms_pair_action_lt;
        QPushButton *tms_pair_action_sel;
        QPushButton *tms_pair_action_copy;
        QPushButton *tms_pair_action_del;

        //interatomic angle
        qspoiler_widget_t *tms_angle_gb;
        QFormLayout *tms_angle_gb_lt;
        QComboBox *tms_angle_cur_msr;
        QLabel *tms_angle_at1_info;
        QLabel *tms_angle_at2_info;
        QLabel *tms_angle_at3_info;
        qbinded_checkbox_t *tms_angle_enabled;
        qbinded_int_spinbox_t *tms_angle_order;
        //END TAB MEASUREMENT

        // start tab modify
        ws_item_tab_widget_t *tab_modify;

        qspoiler_widget_t *tm_gb_add_atom;
        QFormLayout *tm_gb_add_atom_lt;
        QComboBox *tm_add_atom_combo;
        qbinded_float3_input_t *tm_add_atom_vec3;
        QPushButton *tm_add_atom_button;

        qspoiler_widget_t *tm_gb_single_atom;
        QFormLayout *tm_gb_single_atom_lt;
        QLabel *tm_single_atom_info;
        QComboBox *tm_single_atom_combo;
        qbinded_float3_input_t *tm_single_atom_vec3;
        QHBoxLayout *tm_single_atom_btn_lt;
        QPushButton *tm_single_atom_commit;
        QPushButton *tm_single_atom_delete;

        qspoiler_widget_t *tm_gb_pair_dist;
        QFormLayout *tm_gb_pair_dist_lt;
        QLabel *tm_pair_dist_atom1;
        QLabel *tm_pair_dist_atom2;
        QComboBox *tm_pair_dist_t_mode;
        QDoubleSpinBox *tm_pair_dist_spinbox;
        QLabel *tm_pair_dist_note_label;
        QHBoxLayout *tm_pair_dist_cmb_lt;
        QPushButton *tm_pair_dist_swap_atoms;

        qspoiler_widget_t *tm_gb_pair_creation;
        QFormLayout *tm_gb_pair_creation_lt;
        QComboBox *tm_pair_creation_combo;
        QHBoxLayout *tm_pair_creation_combo_btn_lt;
        QPushButton *tm_pair_creation_button;

        qspoiler_widget_t *tm_gb_u_scale;
        QFormLayout *tm_gb_u_scale_lt;
        qbinded_float3_input_t *tm_u_scale_vec;
        vector3<float> tm_u_scale_vec_val{1};
        QPushButton *tm_u_apply_scale_button;

        qspoiler_widget_t *tm_gb_translate;
        QFormLayout *tm_gb_translate_lt;
        qbinded_float3_input_t *tm_translate_vec3;
        QComboBox *tm_translate_coord_type;
        QPushButton *tm_translate_apply_button;
        QHBoxLayout *tm_translate_combo_btn_lt;

        qspoiler_widget_t *tm_gb_bc_rot;
        QFormLayout *tm_gb_bc_rot_lt;
        QComboBox *tm_bc_rot_axis;
        QComboBox *tm_bc_rot_angle_type;
        QDoubleSpinBox *tm_bc_rot_angle;
        QPushButton *tm_bc_rot_apply;
        QHBoxLayout *tm_bc_rot_cmb_lt1;
        QHBoxLayout *tm_bc_rot_cmb_lt2;

        qspoiler_widget_t *tm_gb_group_op;
        QGridLayout *tm_group_op_lt;
        QPushButton *tm_group_op_sv_show;
        QPushButton *tm_group_op_sv_hide;
        QPushButton *tm_group_op_sv_hide_invert;
        QPushButton *tm_group_op_sel_ngbs;
        QPushButton *tm_group_op_del_sel;
        QPushButton *tm_group_make_animable;
        QPushButton *tm_group_op_flip_a_p;
        QPushButton *tm_group_op_flip_b_p;
        QPushButton *tm_group_op_flip_c_p;
        QPushButton *tm_group_op_flip_a_n;
        QPushButton *tm_group_op_flip_b_n;
        QPushButton *tm_group_op_flip_c_n;

        qspoiler_widget_t *tm_gb_override_atom;
        QFormLayout *tm_gb_override_atom_lt;
        qbinded_xgeom_color3_input_t *tm_override_atom_color;
        qbinded_xgeom_float_spinbox_t *tm_override_atom_radii;
        // end tab modify

        // start tab sels
        ws_item_tab_widget_t *tab_select;
        qspoiler_widget_t *ts_gb_general;
        QFormLayout *ts_gb_general_lt;
        QLabel *ts_total_groups;
        qbinded_checkbox_t *ts_auto_apply;
        QComboBox *ts_cur_sel_grp;

        qspoiler_widget_t *ts_gb_sel_grp_details;
        QFormLayout *ts_gb_sel_grp_details_lt;
        // end tab sels

        // start tab xgeom
        ws_item_tab_widget_t *tab_xgeom;
        qspoiler_widget_t *txg_gb_info;
        QVBoxLayout *txg_gb_info_lt;
        QTableView *txg_info_tv;
        qxgeom_fields_model_t *txg_info_tmdl;

        qspoiler_widget_t *txg_gb_comp_prop;
        QVBoxLayout *txg_gb_comp_prop_lt;

        // end tab xgeom

        void construct_general_tab();
        void construct_display_tab();
        void construct_anim_tab();
        void construct_measure_tab();
        void construct_modify_tab();
        void construct_select_tab();
        void construct_xgeom_tab();

        void bind_to_item(ws_item_t *_binding_item) override;
        void update_from_ws_item() override;

        void unbind_item() override;

        void bind_dist_measure_tab();
        void unbind_dist_measure_tab();
        void bind_angle_measure_tab();
        void unbind_angle_measure_tab();

        void bind_select_tab();
        void unbind_select_tab();

        void update_anim_tab();
        void update_anim_tab_visibility();
        //
        void update_modify_tab();
        void update_measurement_tab();
        void update_dist_measurement_tab_info();
        void update_angle_measurement_tab_info();
        void update_select_tab();
        void update_xgeom_tab();
        void fill_combo_with_atom_types(QComboBox *combo, geom_view_t *_al);

        void tab_modify_flip_cell_clicked(size_t flip_dim, float flip_magn = 1);

        geom_view_obj_insp_widget_t();

      public slots:

        void cur_anim_index_changed(int index);
        void play_anim_button_toggle(bool value);
        void anim_updated_external();
        void cur_ws_sel_item_frame_changed();

        void anim_timeline_slider_value_changed(int value);
        void anim_button_begin_clicked();
        void anim_button_end_clicked();
        void anim_button_frame_move_forward_clicked();
        void anim_button_frame_move_backward_clicked();
        void anim_act_ren_clicked();
        void anim_act_del_clicked();

        void disp_switch_current_changed(int index);
        void cell_changed();
        void draw_subcells_changed(int state);
        void update_animate_section_status();
        void cur_it_list_selection_changed();

        void modify_add_atom_button_clicked();
        void modify_single_atom_button_clicked();
        void modify_single_atom_delete_button_clicked();
        void modify_pair_dist_spinbox_value_changed(double newval);
        void modify_pair_dist_swap_button_clicked();
        void modify_add_atom_between_pair();
        void modify_barycentric_scale_button_clicked();
        void modify_translate_selected_atoms_clicked();
        void modify_translate_coord_type_changed(int coord_type);
        void modify_bc_rot_angle_type_change(int new_angle_type);
        void modify_bc_rot_apply();

        void modify_group_op_sv_show();
        void modify_group_op_sv_hide();
        void modify_group_op_sv_hide_invert();
        void modify_group_op_sel_ngbs();
        void modify_group_op_del_sel();
        void modify_group_op_make_static_anim();

        void msr_switch_current_changed(int index);
        void msr_pair_cur_idx_changed(int index);
        void msr_angle_cur_idx_changed(int index);
        void msr_pair_select_clicked();
        void msr_pair_delete_clicked();
        void msr_pair_copy_clicked();

        void cur_ws_edit_mode_changed();
        void cur_it_selected_content_changed();

        void type_summary_clicked(const QModelIndex &index);
        void rebond_button_clicked();
        void clear_color_override_button_clicked();

        //asm
        void atomic_radius_modified(int i, int j, double d);

    };

    class qrealspinidx : public QDoubleSpinBox{

      Q_OBJECT
  
    public:
      int i{0},j{0};
  
      qrealspinidx(int _i, int _j, QWidget *parent = nullptr);

      void bind(int _i, int _j);

    signals:
		  
      void valueChanged_ij(int __i, int __j, double d);

    public slots:

      void valueChangedEmit(double d);
  
    };
    
  } // namespace qpp::cad

} // namespace qpp

#endif
