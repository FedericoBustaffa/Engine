#pragma once

class TimeStep
{
public:
	TimeStep();

	void UpdateTime();
	float GetSeconds() const;
	float GetMilliSeconds() const;

private:
	float time, last_frame_time, time_step;
};