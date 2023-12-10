#include "list_item.h"
#include "scene/theme/theme_db.h"

void ListItem::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_body", "body"), &ListItem::set_body);
	ClassDB::bind_method(D_METHOD("get_body"), &ListItem::get_body);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "body", PROPERTY_HINT_NODE_TYPE, "Control", PROPERTY_USAGE_NONE), "set_body", "get_body");

	BIND_THEME_ITEM(Theme::DATA_TYPE_STYLEBOX, ListItem, normal);
	BIND_THEME_ITEM(Theme::DATA_TYPE_STYLEBOX, ListItem, pressed);
	BIND_THEME_ITEM(Theme::DATA_TYPE_STYLEBOX, ListItem, hover);
	BIND_THEME_ITEM(Theme::DATA_TYPE_STYLEBOX, ListItem, disabled);
}

void ListItem::_notification(int p_what) {
	switch (p_what) {

		case NOTIFICATION_THEME_CHANGED: {
			update_minimum_size();
			queue_redraw();
		} break;

		case NOTIFICATION_DRAW: {
			RID ci = get_canvas_item();
			Size2 size = get_size();

			switch (get_draw_mode()) {
				case DRAW_NORMAL: {
					theme_cache.normal->draw(ci, Rect2(Point2(0, 0), size));
				} break;
				case DRAW_HOVER_PRESSED:
					[[fallthrough]];
				case DRAW_PRESSED: {
					theme_cache.pressed->draw(ci, Rect2(Point2(0, 0), size));
				} break;
				case DRAW_HOVER: {
					theme_cache.hover->draw(ci, Rect2(Point2(0, 0), size));
				} break;
				case DRAW_DISABLED: {
					theme_cache.disabled->draw(ci, Rect2(Point2(0, 0), size));
				} break;
			}
		} break;
	}
}

void ListItem::add_child_notify(Node *p_child) {
	Control::add_child_notify(p_child);
	Control *c = Object::cast_to<Control>(p_child);

	// Normally you set the body directly with set_body(), but it's also possible to set the body by
	// adding a child directly to the ListItem (usually via the editor).
	if (c && body != c) {
		_set_body_noadd(c);
	}
}

void ListItem::remove_child_notify(Node *p_child) {
	Control::remove_child_notify(p_child);
	if (body == p_child) {
		body = nullptr;
	}
}

Size2 ListItem::get_minimum_size() const {
	if (body) {
		return body->get_combined_minimum_size();
	}
	return Size2();
}

void ListItem::set_body(Control *p_body) {
	if (body == p_body) {
		return;
	}

	_set_body_noadd(p_body);
	if (body) {
		add_child(body, false, INTERNAL_MODE_FRONT);
		body->set_h_size_flags(SIZE_EXPAND_FILL);
	}
}

void ListItem::_set_body_noadd(Control *p_body) {
	if (body == p_body) {
		return;
	}

	if (body) {
		body->queue_free();
	}

	body = p_body;
	queue_redraw();
}

Control *ListItem::get_body() const {
	return body;
}

ListItem::ListItem() {
	set_focus_mode(FOCUS_ALL);
	set_h_size_flags(SIZE_EXPAND_FILL);
	set_toggle_mode(true);
}
