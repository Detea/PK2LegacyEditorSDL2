#pragma once
#include "Layout.h"
class VerticalLayout : public Layout {
public:
	VerticalLayout();
	VerticalLayout(int x, int y);
	~VerticalLayout();

	virtual void calculate() override;

	void setSpacing(int spacing);
private:
	int spacing = 0;
};

