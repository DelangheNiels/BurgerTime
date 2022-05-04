#pragma once
namespace dae
{
	class PointsObserver
	{
	public:
		virtual ~PointsObserver() = default;
		virtual void AddPoints(int ) = 0;
	};

}

