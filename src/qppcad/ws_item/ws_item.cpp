#include <qppcad/ws_item/ws_item.hpp>
#include <qppcad/core/app_state.hpp>
#include <data/color.hpp>
#include <qppcad/core/workspace.hpp>
#include <qppcad/core/json_helpers.hpp>

using namespace qpp;
using namespace qpp::cad;

vector3<float> ws_item_t::get_pos() {
  return m_pos;
}

void ws_item_t::set_pos(vector3<float> new_pos) {

  app_state_t* astate = app_state_t::get_inst();
  m_pos = new_pos;

  //notify followers about changes
  updated_externally(ws_item_updf_pos_changed);

  astate->make_viewport_dirty();

}

void ws_item_t::target_view(cam_tv_e target_view,
                            vector3<float> &look_from,
                            vector3<float> &look_to,
                            vector3<float> &look_up,
                            bool &need_to_update_camera) {

}

void ws_item_t::apply_target_view(cam_tv_e target_view_src) {

  app_state_t* astate = app_state_t::get_inst();

  vector3<float> look_from;
  vector3<float> look_to;
  vector3<float> look_up{0.0, 1.0, 0.0};
  bool need_to_update_camera{false};

  target_view(target_view_src, look_from, look_to, look_up, need_to_update_camera);

  if (need_to_update_camera && m_parent_ws && m_parent_ws->m_camera) {

      m_parent_ws->m_camera->m_view_point = look_from;
      m_parent_ws->m_camera->m_look_at = look_to;
      m_parent_ws->m_camera->m_look_up = look_up;
      m_parent_ws->m_camera->orthogonalize_gs();
      m_parent_ws->m_camera->update_camera();

      astate->make_viewport_dirty();

    }

}

void ws_item_t::set_parent_workspace(workspace_t *_parent_ws){
  m_parent_ws = _parent_ws;
}

const std::string ws_item_t::get_name() {
  return m_name;
}

void ws_item_t::set_name(const std::string &_name) {

  if (m_name != _name){
      m_name = _name;
      m_parent_ws->ws_changed();
    }

}

void ws_item_t::set_name(const char *_name) {

  if (m_name != _name){
      m_name = std::string(_name);
      m_parent_ws->ws_changed();
    }

}

void ws_item_t::add_connected_item(std::shared_ptr<ws_item_t> new_item) {
  if (!is_connected(new_item)) m_connected_items.push_back(new_item);
}

void ws_item_t::rm_connected_item(std::shared_ptr<ws_item_t> item_to_remove) {

  auto idx = get_connected_idx(item_to_remove);
  if (idx) m_connected_items.erase(m_connected_items.begin() + *idx);

}

std::optional<size_t> ws_item_t::get_connected_idx(std::shared_ptr<ws_item_t> item_to_find) {

  for (size_t i = 0; i < m_connected_items.size(); i++)
    if (m_connected_items[i].get() == item_to_find.get()) return std::optional<size_t>(i);
  return std::nullopt;

}

bool ws_item_t::is_connected(std::shared_ptr<ws_item_t> item_to_find) {
  return (get_connected_idx(item_to_find) != std::nullopt);
}

void ws_item_t::add_follower(std::shared_ptr<ws_item_t> new_item) {

  if (!is_follower(new_item)) m_followers.push_back(new_item);
  new_item->m_leader = shared_from_this();
  new_item->on_leader_changed();

}

std::optional<size_t> ws_item_t::get_follower_idx(std::shared_ptr<ws_item_t> item_to_find) {

  for (size_t i = 0; i < m_followers.size(); i++)
    if (m_followers[i].get() == item_to_find.get())
      return std::optional<size_t>(i);

  return std::nullopt;

}

bool ws_item_t::is_follower(std::shared_ptr<ws_item_t> item_to_find) {
  return (get_follower_idx(item_to_find) != std::nullopt);
}

void ws_item_t::rm_follower(std::shared_ptr<ws_item_t> item_to_remove) {

  auto idx = get_follower_idx(item_to_remove);
  if (idx) {
      m_followers.erase(m_followers.begin() + *idx);
      item_to_remove->m_leader = nullptr;
      item_to_remove->on_leader_changed();
    }

}

void ws_item_t::set_bounded_to_leader(bool bounding) {

  if (bounding) {
      unset_flag(ws_item_flags_support_tr);
      unset_flag(ws_item_flags_translate_emit_upd_event);
      set_flag(ws_item_flags_fetch_leader_pos);
    }
  else {
      set_flag(ws_item_flags_support_tr);
      set_flag(ws_item_flags_translate_emit_upd_event);
      unset_flag(ws_item_flags_fetch_leader_pos);
    }

}

bool ws_item_t::is_bounded() {
  return p_flags & ws_item_flags_fetch_leader_pos;
}

bool ws_item_t::is_selected() {

  if (m_parent_ws) {
      return m_parent_ws->get_selected() == this;
    }
  else {
      return false;
    }

}

void ws_item_t::render () {

  app_state_t* astate = app_state_t::get_inst();

  if (m_selected &&
      (get_flags() & ws_item_flags_support_sel) &&
      (get_flags() & ws_item_flags_support_render_bb) &&
      is_bb_visible()
      && m_show_bb) {

      astate->dp->begin_render_aabb();

      (m_parent_ws->m_edit_type == ws_edit_e::edit_item) ?
            astate->dp->render_aabb(clr_fuchsia, m_pos + m_aabb.min, m_pos + m_aabb.max  )
          : astate->dp->render_aabb_segmented(clr_olive, m_pos + m_aabb.min, m_pos + m_aabb.max);

      astate->dp->end_render_aabb();

    }

}

void ws_item_t::render_overlay(QPainter &painter) {

}

void ws_item_t::mouse_double_click(ray_t<float> *ray) {

  app_state_t* astate = app_state_t::get_inst();
  astate->tlog("ws_item_t::mouse_double_click, name = {}", m_name);

}


void ws_item_t::set_default_flags(uint32_t flags){
  p_flags = flags;
}

uint32_t ws_item_t::get_flags() const {
  return p_flags;
}

void ws_item_t::set_flag(uint32_t flag) {
  p_flags |= flag;
}

void ws_item_t::unset_flag(uint32_t flag) {
  p_flags &= ~flag;
}

void ws_item_t::on_leader_changed() {

}

void ws_item_t::on_leader_call() {
  updated_externally(ws_item_updf_leader_changed);
}

void ws_item_t::call_followers() {
  for (auto follower : m_followers) follower->on_leader_call();
}


void ws_item_t::update (float delta_time) {

}

float ws_item_t::get_bb_prescaller(){
  return 1.0f;
}

bool ws_item_t::is_bb_visible() {
  return true;
}

const vector3<float> ws_item_t::get_gizmo_content_barycenter() {
  return vector3<float>::Zero();
}

void ws_item_t::updated_externally(uint32_t update_reason) {

  if (update_reason & ws_item_updf_pos_changed) {
      //notify followers about changes
      for (auto &follower : m_followers)
        if (follower) follower->updated_externally(ws_item_updf_leader_changed);
    }

  if ((update_reason & ws_item_updf_leader_changed) &&
      m_leader &&
      p_flags & ws_item_flags_fetch_leader_pos) {
      //copy pos from leader and apply offset
      m_pos = m_leader->m_pos + m_leader_offset;
    }

}

void ws_item_t::on_begin_node_gizmo_translate() {
  m_pos_old = m_pos;
}

void ws_item_t::on_end_node_gizmo_translate() {

}

void ws_item_t::on_begin_content_gizmo_translate() {

}

void ws_item_t::apply_intermediate_translate_content(const vector3<float> &new_pos) {

}

void ws_item_t::on_end_content_gizmo_translate() {

}

void ws_item_t::translate(const vector3<float> &tr_vec) {

  app_state_t* astate = app_state_t::get_inst();
  if (get_flags() & ws_item_flags_support_tr) m_pos += tr_vec;
  if (get_flags() & ws_item_flags_translate_emit_upd_event) updated_externally();
  if (is_selected()) astate->astate_evd->cur_ws_selected_item_position_changed();

  //notify followers about changes
  updated_externally(ws_item_updf_pos_changed);

  astate->make_viewport_dirty();

}

void ws_item_t::save_to_json(json &data) {

  json_helper::save_var(JSON_WS_ITEM_NAME, m_name, data);
  json_helper::save_var(JSON_WS_ITEM_TYPE, get_type_name(), data);
  json_helper::save_var(JSON_IS_VISIBLE, m_is_visible, data);

  if (get_flags() & ws_item_flags_support_render_bb)
    json_helper::save_var(JSON_WS_ITEM_SHOW_BB, m_show_bb, data);

  json_helper::save_vec3(JSON_POS, m_pos, data);

  if (m_leader)
    json_helper::save_var(JSON_WS_ITEM_LEADER, m_leader->m_name, data);

  if (!m_connected_items.empty()) {
      json _con_items = json::array({});
      for (auto &elem : m_connected_items) if(elem) _con_items.push_back(elem->m_name);
      data[JSON_WS_ITEM_CONNECTED_ITEMS] = _con_items;
    }

  if (!m_followers.empty()) {
      json _flw_items = json::array({});
      for (auto &elem : m_followers) if(elem) _flw_items.push_back(elem->m_name);
      data[JSON_WS_ITEM_CONNECTED_ITEMS] = _flw_items;
    }

}

void ws_item_t::load_from_json(json &data, repair_connection_info_t &rep_info) {

  json_helper::load_var(JSON_WS_ITEM_NAME, m_name, data);
  json_helper::load_var(JSON_IS_VISIBLE, m_is_visible, data);

  if (get_flags() & ws_item_flags_support_render_bb)
    json_helper::load_var(JSON_WS_ITEM_SHOW_BB, m_show_bb, data);

  if (get_flags() | ws_item_flags_support_tr)
    json_helper::load_vec3(JSON_POS, m_pos, data);

  auto _con_items = data.find(JSON_WS_ITEM_CONNECTED_ITEMS);
  if (_con_items != data.end()) {
      std::vector<std::string> rc_ci;
      auto &val = _con_items.value();
      std::transform(val.begin(), val.end(), std::back_inserter(rc_ci),
                     [](auto &_elem)->STRING_EX{return _elem.template get<STRING_EX>();});
      rep_info.m_connected_items[m_name] = rc_ci;
    }

}


void ws_item_t::load_from_stream(std::basic_istream<char, TRAITS> &stream) {

}

void ws_item_t::save_to_stream(std::basic_istream<char, TRAITS> &stream) {

}

void ws_item_t::load_from_file(std::string &file_name) {

}

void ws_item_t::save_from_file(std::string &file_name) {

}

void ws_item_t::update_oi() {

  if (m_selected)
    app_state_t::get_inst()->astate_evd->cur_ws_selected_item_need_to_update_obj_insp();

}

bool ws_item_t::can_be_written_to_json() {
  return false;
}

void ws_item_t::save_ws_item_field(const std::string &field_name,
                                   std::shared_ptr<ws_item_t> field_ws_item,
                                   json &data) {

  if (field_ws_item) data[field_name] = field_ws_item->m_name;

}

void ws_item_t::load_ws_item_field(const std::string &field_name,
                                   std::shared_ptr<ws_item_t> *field_ws_item,
                                   json &data,
                                   repair_connection_info_t &rep_info) {

  auto it = data.find(field_name);
  if (it != data.end()) {
      repair_ws_item_field_t rep_ws_item;
      rep_ws_item.m_field_name = it.value();
      rep_ws_item.m_field = field_ws_item;
      rep_info.m_fields.emplace_back(std::move(rep_ws_item));
    }

}

std::string ws_item_t::py_get_repr() {
  return fmt::format("[ws_item, type=\"{}\", name=\"{}\"]", get_type_name(), m_name);
}
