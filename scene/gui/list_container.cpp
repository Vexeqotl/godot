#include "list_container.h"
#include "list_item.h"

void ListContainer::_button_group_item_pressed(BaseButton *p_item) {
	ListItem *item = Object::cast_to<ListItem>(p_item);
	if (!item) {
		return;
	}

	if (item->is_pressed()) {
		_set_selected_item_nogroup(item);
	} else {
		_set_selected_item_nogroup(nullptr);
	}
}

void ListContainer::_bind_methods() {
	ClassDB::bind_method(D_METHOD("clear"), &ListContainer::clear);
	ClassDB::bind_method(D_METHOD("set_selected_item", "item"), &ListContainer::set_selected_item);
	ClassDB::bind_method(D_METHOD("get_selected_item"), &ListContainer::get_selected_item);
	ClassDB::bind_method(D_METHOD("set_item_group", "group"), &ListContainer::set_item_group);
	ClassDB::bind_method(D_METHOD("get_item_group"), &ListContainer::get_item_group);

	ADD_SIGNAL(MethodInfo("selected_item_changed", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_NODE_TYPE, "ListItem")));

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "selected_item", PROPERTY_HINT_NODE_TYPE, "ListItem", PROPERTY_USAGE_NONE), "set_selected_item", "get_selected_item");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item_group", PROPERTY_HINT_RESOURCE_TYPE, "ButtonGroup"), "set_item_group", "get_item_group");
}

void ListContainer::add_child_notify(Node *p_child) {
	VBoxContainer::add_child_notify(p_child);

	ListItem *item = Object::cast_to<ListItem>(p_child);
	if (!item) {
		return;
	}

	item->set_button_group(item_group);
}

void ListContainer::remove_child_notify(Node *p_child) {
	VBoxContainer::remove_child_notify(p_child);

	ListItem *item = Object::cast_to<ListItem>(p_child);
	if (!item) {
		return;
	}

	if (item == selected_item) {
		_set_selected_item_nogroup(nullptr);
	}
	item->set_button_group(Ref<ButtonGroup>());
}

void ListContainer::clear() {
	_set_selected_item_nogroup(nullptr);

	for (int i = 0; i < get_child_count(); i++) {
		auto *c = Object::cast_to<Node>(get_child(i));
		if (c) {
			c->queue_free();
		}		
	}
}

ListItem *ListContainer::get_selected_item() const {
	return selected_item;
}

void ListContainer::set_selected_item(ListItem *p_item) {
	if (selected_item == p_item) {
		return;
	}

	selected_item = p_item;

	if (selected_item) {
		selected_item->set_pressed(true);
	} else if (item_group.is_valid()) {
		auto *pressed_item = item_group->get_pressed_button();
		if (pressed_item) {
			pressed_item->set_pressed(false);
		}
	}
	emit_signal(SNAME("selected_item_changed"), selected_item);
}

void ListContainer::_set_selected_item_nogroup(ListItem *p_item) {
	if (selected_item == p_item) {
		return;
	}

	selected_item = p_item;
	emit_signal(SNAME("selected_item_changed"), selected_item);
}

Ref<ButtonGroup> ListContainer::get_item_group() const {
	return item_group;
}

void ListContainer::set_item_group(Ref<ButtonGroup> p_group) {
	if (item_group == p_group) {
		return;
	}

	if (item_group.is_valid()) {
		item_group->disconnect(SNAME("pressed"), callable_mp(this, &ListContainer::_button_group_item_pressed));
	}

	set_selected_item(nullptr);

	item_group = p_group;

	for (int i = 0; i < get_child_count(); i++) {
		auto *c = Object::cast_to<ListItem>(get_child(i));
		if (c) {
			c->set_button_group(p_group);
		}
	}
	
	if (item_group.is_valid()) {
		item_group->connect(SNAME("pressed"), callable_mp(this, &ListContainer::_button_group_item_pressed));
	}
}

ListContainer::ListContainer() {
	set_mouse_filter(MOUSE_FILTER_STOP);
}
