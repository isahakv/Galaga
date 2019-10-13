#ifndef INSTANCEID_H
#define INSTANCEID_H

class InstanceID
{
public:
	InstanceID() : id(count++) {}
	inline int Get() const { return id; }

private:
	static int count;
	int id;
};

#endif // !INSTANCEID_H
