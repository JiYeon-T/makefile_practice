#include "Wrapper.h"
#include "Person.h"

void *call_Person_Create()
{
	//C 接口内部调用 C++
	return new Person("abc", 100);
}

void call_Person_Destroy(void *p)
{
	delete static_cast<Person *>(p);
	return;
}

int call_Person_GetAge(void *p)
{
	return static_cast<Person*>(p)->GetAge();
}

const char *call_Person_GetName(void *p)
{
	return static_cast<Person *>(p)->GetName();
}
