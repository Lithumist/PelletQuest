/*
	state.h

	An abstract base class to represent a state.
*/

#pragma once

// includes here

class State
{
public:

	virtual void Initialize() = 0;
	virtual void Uninitialize() = 0;

	virtual void OnPause() = 0;
	virtual void OnResume() = 0;

	virtual void Events() = 0;
	virtual void Update() = 0; // called by D() if not paused
	virtual void Draw() = 0; // ^



	void Pause();
	void Resume();

	void U(); // general state update code called by engine
	void D(); // ^

protected:

    State();

    bool is_paused_m;

private:
};