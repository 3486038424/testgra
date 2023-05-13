#include "works.h"
tasks::tasks() { tasks(nullptr); };
tasks::tasks(decltype(m) t) { task = t; next = nullptr; };
void tasks::add(tasks* t) { next = t; }
void works::add(decltype(m) task)
{
	tasks *g = new tasks (task),*t=this->t;
	while (t->next != nullptr)t = t->next;
	t->add(g);
}
void works::run()
{
	tasks * t = this->t;
	while (t->next != nullptr)
	{
		t = t->next;
		t->run();
	}
}