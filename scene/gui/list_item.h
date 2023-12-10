#ifndef LIST_ITEM_H
#define LIST_ITEM_H

#include "scene/gui/base_button.h"

class ListItem : public BaseButton {
	GDCLASS(ListItem, BaseButton);

	struct ThemeCache {
		Ref<StyleBox> normal;
		Ref<StyleBox> pressed;
		Ref<StyleBox> hover;
		Ref<StyleBox> disabled;
	} theme_cache;

private:
	Control *body = nullptr;

protected:
	static void _bind_methods();
	void _notification(int p_what);

	virtual void add_child_notify(Node *p_child) override;
	virtual void remove_child_notify(Node *p_child) override;

public:
	virtual Size2 get_minimum_size() const override;
	
	void set_body(Control *p_body);
	void _set_body_noadd(Control *p_body);
	Control *get_body() const;

	explicit ListItem();
};

#endif
