#ifndef LIST_CONTAINER_H
#define LIST_CONTAINER_H

#include "scene/gui/box_container.h"

class ListItem;
class ButtonGroup;
class BaseButton;

class ListContainer : public VBoxContainer {
	GDCLASS(ListContainer, VBoxContainer);

private:
	Ref<ButtonGroup> item_group;
	ListItem *selected_item = nullptr;

	void _button_group_item_pressed(BaseButton *p_item);

protected:
	static void _bind_methods();

	virtual void add_child_notify(Node *p_child) override;
	virtual void remove_child_notify(Node *p_child) override;

public:
	void clear();

	ListItem *get_selected_item() const;
	void set_selected_item(ListItem *p_item);
	void _set_selected_item_nogroup(ListItem *p_item);

	Ref<ButtonGroup> get_item_group() const;
	void set_item_group(Ref<ButtonGroup> p_group);	

	explicit ListContainer();
};

#endif // LIST_CONTAINER_H
