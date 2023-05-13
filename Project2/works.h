#pragma once
void m();
class tasks
{
public:
	decltype(m) *task;
	tasks* next;
	tasks();
	tasks(decltype(m) t);
	void add(tasks* t);
	void run() { task(); }
};
class works
{private:
	tasks *t;
public:
	works() { t = new tasks(); }
	void add(decltype(m) t);
	void run();
};

