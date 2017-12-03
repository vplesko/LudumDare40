#pragma once

class Observed;

class Observer {
public:

	virtual void notify(Observed *subject) =0;

	virtual ~Observer() {}
};