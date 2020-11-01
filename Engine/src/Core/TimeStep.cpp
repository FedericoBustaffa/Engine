#include "TimeStep.h"

#include <GLFW/glfw3.h>

TimeStep::TimeStep()
	: time(0.0f), last_frame_time(0.0f), time_step(0.0f)
{
}

void TimeStep::UpdateTime()
{
	time = (float)glfwGetTime();
	time_step = time - last_frame_time;
	last_frame_time = time;
}

float TimeStep::GetSeconds() const
{
	return time_step;
}

float TimeStep::GetMilliSeconds() const
{
	return time_step * 1000.0f;
}

float TimeStep::operator()() const
{
	return time_step;
}
