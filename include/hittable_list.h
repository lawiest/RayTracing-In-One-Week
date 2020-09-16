#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "./common/hittable.h"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list :public hittable
{
public:
	hittable_list() {}
	hittable_list(shared_ptr<hittable> object)
	{
		add(object);
	}

	void clear()
	{
		objects.clear();
	}
	void add(shared_ptr<hittable> object)
	{
		objects.push_back(object);
	}

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec)const override;

private:
	std::vector<shared_ptr<hittable> > objects;

};

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
	hit_record temp_tec;
	bool hit_anything = false;
	auto closest_so_far = t_max;

	//这个地方初看好像有问题，但其实很妙，如果求得的t在其他问题前面后面的物体就不会交到，
	//如果求得的t在物体后面会接着去求更近的t,所有求得的t永远是最接近相机的
	//唯一缺点是没必要的计算量会增大
	for (const auto& object : objects)
	{
		if (object->hit(r, t_min, closest_so_far, temp_tec))
		{
			hit_anything = true;
			closest_so_far = temp_tec.t;
			rec = temp_tec;
		}
	}

	return hit_anything;
}

#endif