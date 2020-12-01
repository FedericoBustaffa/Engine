#pragma once

class TimeStep
{
public:
	TimeStep();

	void UpdateTime();
	float GetTime() const { return time; }
	float GetSeconds() const { return time_step; }
	float operator()() const { return time_step; }
	float GetMilliSeconds() const { return time_step * 1000.0f; }

private:
	float time, last_frame_time, time_step;
};